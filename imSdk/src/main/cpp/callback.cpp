//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "callback.h"
template<typename K, typename V>
class ThreadSafeMap {
private:
    std::unordered_map<K, V> map_;
    mutable std::mutex mutex_;

public:
    // 插入或更新
    void insert(const K& key, const V& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        map_[key] = value;
    }

    // 查找并移除（类似你的 pop）
    bool pop(const K& key, V& out_value) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = map_.find(key);
        if (it == map_.end()) {
            return false;
        }
        out_value = std::move(it->second);
        map_.erase(it);
        return true;
    }

    // 只查找（不修改）
    bool find(const K& key, V& out_value) const {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = map_.find(key);
        if (it == map_.end()) {
            return false;
        }
        out_value = it->second;
        return true;
    }

    // 获取大小（调试用）
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return map_.size();
    }

    // 清空（用于 cleanup）
    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        map_.clear();
    }
};

// 存储 TSF 和 Deferred 的数据结构
struct TSFData {
    napi_threadsafe_function tsf = nullptr;
    napi_deferred deferred = nullptr;
    std::atomic<bool> completed{false};
    std::string message;  // 保存原始 message，用于 progress 回调
    TSFData() = default;
    TSFData(napi_threadsafe_function t, napi_deferred d) : tsf(t), deferred(d) {}
    TSFData(napi_threadsafe_function t, napi_deferred d, const std::string& msg) : tsf(t), deferred(d), message(msg) {}
};

struct CBSISSIData{
    std::string opID;
    int errCode;
    std::string errMsg;
    std::string data;
    int progress;
};
static ThreadSafeMap<std::string, TSFData*>& getTsfMap() {
    static ThreadSafeMap<std::string, TSFData*> instance;
    return instance;
}

void ThrowError(napi_env env, int32_t errCode, const char* errorMsg) {
    napi_value result;
    if (napi_create_object(env, &result) != napi_ok) {
        return;
    }
    napi_set_named_property(env, result, "errCode",  SetJSInt32(env, errCode));
    napi_set_named_property(env, result, "errMsg", SetJSString(env, std::string(errorMsg ? errorMsg : "")));
    napi_value error;
    napi_create_error(env, nullptr, result, &error);
    napi_throw(env, error);
}

napi_value ReturnVoid(napi_env env) {
    napi_value undefined;
    napi_get_undefined(env, &undefined);
    return undefined;    
}

static void RejectPromise(napi_env env, napi_deferred deferred, int32_t errCode, const char* errorMsg) {
    if (!env || !deferred) return;
    napi_value result;
    if (napi_create_object(env, &result) != napi_ok) {
        return;
    }
    napi_set_named_property(env, result, "errCode",  SetJSInt32(env, errCode));
    napi_set_named_property(env, result, "errMsg", SetJSString(env, std::string(errorMsg ? errorMsg : "")));
    napi_reject_deferred(env, deferred, result);
}


static void ResolvePromise(napi_env env, napi_deferred deferred, const char* data) {
    if (!env || !deferred) return;
    napi_resolve_deferred(env, deferred, SetJSString(env, data));
}

TsfRegistration CreateTSF(napi_env env, const std::string& opID, napi_value jsCB) {
    napi_deferred deferred;
    napi_value promise;
    napi_create_promise(env, &deferred, &promise);
    TsfRegistration result{promise, false};

    if (jsCB != nullptr) {
        napi_valuetype type;
        napi_typeof(env, jsCB, &type);
        if (type != napi_function) {
            RejectPromise(env, deferred, -1, "argument must be a function");
            return result;
        }        
    }

    if (opID.empty()) {
        RejectPromise(env, deferred, -1, "operationID cannot be empty");
        return result;
    }
    TSFData *tsfCheck = nullptr;
    if (getTsfMap().find(opID, tsfCheck)) {
        RejectPromise(env, deferred, -1, "operationID is duplicate");
        return result;
    }
    napi_value resource_name;
    napi_create_string_utf8(
        env,
        opID.c_str(),
        NAPI_AUTO_LENGTH,
        &resource_name
    );
    napi_threadsafe_function tsf;
    napi_status status = napi_create_threadsafe_function(env, jsCB, NULL, resource_name, 0, 1, NULL,NULL, NULL,
                                                         jsCB != nullptr ? OnCallJSSISSI: OnCallJSSISS, &tsf);
    if (status != napi_ok || tsf == nullptr) {
        RejectPromise(env, deferred, -1, "Failed to create threadsafe function");
        return result;
    }
    getTsfMap().insert(opID, new TSFData(tsf, deferred));
    result.should_proceed = true;
    return result;
}

// 带 message 参数的 CreateTSF，用于 sendMessage 等需要保存原始 message 的场景
TsfRegistration CreateTSFWithMessage(napi_env env, const std::string& opID, napi_value jsCB, const std::string& message) {
    napi_deferred deferred;
    napi_value promise;
    napi_create_promise(env, &deferred, &promise);
    TsfRegistration result{promise, false};

    if (jsCB != nullptr) {
        napi_valuetype type;
        napi_typeof(env, jsCB, &type);
        if (type != napi_function) {
            RejectPromise(env, deferred, -1, "argument must be a function");
            return result;
        }
    }

    if (opID.empty()) {
        RejectPromise(env, deferred, -1, "operationID cannot be empty");
        return result;
    }
    TSFData *tsfCheck = nullptr;
    if (getTsfMap().find(opID, tsfCheck)) {
        RejectPromise(env, deferred, -1, "operationID is duplicate");
        return result;
    }
    napi_value resource_name;
    napi_create_string_utf8(
        env,
        opID.c_str(),
        NAPI_AUTO_LENGTH,
        &resource_name
    );
    napi_threadsafe_function tsf;
    napi_status status = napi_create_threadsafe_function(env, jsCB, NULL, resource_name, 0, 1, NULL,NULL, NULL,
                                                         jsCB != nullptr ? OnCallJSSISSI: OnCallJSSISS, &tsf);
    if (status != napi_ok || tsf == nullptr) {
        RejectPromise(env, deferred, -1, "Failed to create threadsafe function");
        return result;
    }
    getTsfMap().insert(opID, new TSFData(tsf, deferred, message));
    result.should_proceed = true;
    return result;
}

napi_ref g_progressCallbackRef = nullptr;  // 进度回调引用
napi_env g_progressCallbackEnv = nullptr;
std::string g_progressOpID;  // 存储当前 progress 回调的 operationID

void SendProgressEvent(int eventCode, const std::string& operationID, const std::string& payload) {
    if (g_progressCallbackRef == nullptr) return;

    napi_handle_scope scope = nullptr;
    napi_status status = napi_open_handle_scope(g_progressCallbackEnv, &scope);
    if (status != napi_ok || scope == nullptr) return;

    napi_value callback = nullptr;
    status = napi_get_reference_value(g_progressCallbackEnv, g_progressCallbackRef, &callback);
    if (status != napi_ok || callback == nullptr) {
        napi_close_handle_scope(g_progressCallbackEnv, scope);
        return;
    }

    napi_value operationIDVal = SetJSString(g_progressCallbackEnv, operationID);
    napi_value payloadVal = SetJSString(g_progressCallbackEnv, payload);
    napi_value eventCodeVal = SetJSInt32(g_progressCallbackEnv, eventCode);

    napi_value global = nullptr;
    napi_get_global(g_progressCallbackEnv, &global);

    napi_value argv[3] = { eventCodeVal, operationIDVal, payloadVal };
    napi_call_function(g_progressCallbackEnv, global, callback, 3, argv, nullptr);

    napi_close_handle_scope(g_progressCallbackEnv, scope);
}

void SetProgressCallback(napi_env env, napi_value callback, const std::string& opID) {
    if (g_progressCallbackRef != nullptr) {
        napi_delete_reference(env, g_progressCallbackRef);
    }
    napi_create_reference(env, callback, 1, &g_progressCallbackRef);
    g_progressCallbackEnv = env;
    g_progressOpID = opID;  // 存储 operationID
}

// 符合 CB_I_S 签名的进度回调（C 风格）
void UploadProgressCallback(int eventCode, char* data) {
    std::string payload = data ? std::string(data) : "";
    SendProgressEvent(eventCode, g_progressOpID, payload);  // 使用存储的 operationID
}

// 注册上传进度回调（返回函数指针给 C 库调用）
CB_I_S GetUploadProgressCallback() {
    return UploadProgressCallback;
}

void RegisterSISSI(char *opID, int errCode, char* errMsg, char* data, int progress) {
    if (!opID) return;
    std::string opID_str = opID ? std::string(opID) : "";
    std::string errMsg_str = errMsg ? std::string(errMsg) : "";
    std::string data_str = data ? std::string(data) : "";

    TSFData *tsf = nullptr;
    if (!getTsfMap().find(opID_str, tsf) || tsf == nullptr) {
        return;
    }
    auto* msg = new CBSISSIData{
        std::move(opID_str),
        errCode,
        std::move(errMsg_str),
        std::move(data_str),
        progress
    };
    napi_status status = napi_call_threadsafe_function(tsf->tsf, msg, napi_tsfn_nonblocking);
    if (status != napi_ok) {
        delete msg;
    }
}

void OnCallJSSISSI(napi_env env,napi_value js_callback,void* /*context*/,void* data) {
    auto* msg = static_cast<CBSISSIData*>(data);
    if (!msg) {
        return;
    }

    TSFData* tsf = nullptr;

    // 判断是否 final 回调
    const bool isProgress = (msg->errCode == NO_ERR && msg->data == NO_DATA);

    if (isProgress) {
        // progress 只查，不移除
        if (!getTsfMap().find(msg->opID, tsf) || tsf == nullptr) {
            delete msg;
            return;
        }

        // 发送 { progress: number, message: string } 对象，与 Android SendMsgCallBack.onProgress 一致
        // message 使用保存的原始 message，而非回调中的 data
        napi_value result;
        napi_create_object(env, &result);
        napi_set_named_property(env, result, "progress", SetJSInt32(env, msg->progress));
        napi_set_named_property(env, result, "message", SetJSString(env, tsf->message));
        napi_status s = napi_call_function(env, nullptr, js_callback, 1, &result, nullptr);

        if (s != napi_ok) {
            OH_LOG_ERROR(LOG_APP,"progress callback failed, opID=%{public}s",msg->opID.c_str());
            napi_value error;
            napi_get_and_clear_last_exception(env, &error);
        }

        delete msg;
        return;
    }

    // -------- Final 回调路径 --------
    if (!getTsfMap().pop(msg->opID, tsf) || tsf == nullptr) {
        delete msg;
        return;
    }

    // 确保 Promise 只被 settle 一次
    if (!tsf->completed.exchange(true)) {
        if (msg->errCode != NO_ERR) {
            RejectPromise(env,tsf->deferred,msg->errCode,msg->errMsg.c_str());
        } else {
            ResolvePromise(env,tsf->deferred,msg->data.c_str());
        }
    }
    napi_release_threadsafe_function(tsf->tsf,napi_tsfn_release);
    delete tsf;
    delete msg;
}

void RegisterSISS(char *opID, int errCode, char* errMsg, char* data) {
    if (!opID) return;
    std::string opID_str = opID ? std::string(opID) : "";
    std::string errMsg_str = errMsg ? std::string(errMsg) : "";
    std::string data_str = data ? std::string(data) : "";

    TSFData *tsf = nullptr;
    if (!getTsfMap().find(opID_str, tsf) || tsf == nullptr) {
        return;
    }
    auto* msg = new CBSISSIData{
        std::move(opID_str),
        errCode,
        std::move(errMsg_str),
        std::move(data_str),
    };
    napi_status status = napi_call_threadsafe_function(tsf->tsf, msg, napi_tsfn_nonblocking);
    if (status != napi_ok) {
        delete msg;
    }
}
void OnCallJSSISS(napi_env env,napi_value js_callback,void* /*context*/,void* data) {
    auto* msg = static_cast<CBSISSIData*>(data);
    if (!msg) {
        return;
    }

    TSFData* tsf = nullptr;
     if (!getTsfMap().pop(msg->opID, tsf) || tsf == nullptr) {
        delete msg;
        return;
    }
    if (msg->errCode == NO_ERR) {
        ResolvePromise(env,tsf->deferred,msg->data.c_str());
    } else {
        RejectPromise(env,tsf->deferred,msg->errCode,msg->errMsg.c_str());
    }
    napi_release_threadsafe_function(tsf->tsf,napi_tsfn_release);
    delete tsf;
    delete msg;
}