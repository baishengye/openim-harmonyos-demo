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

// 文件上传进度数据结构
struct UploadProgressData {
    std::string opID;
    int progress;
    std::string info;
};

static ThreadSafeMap<std::string, TSFData*>& getTsfMap() {
    static ThreadSafeMap<std::string, TSFData*> instance;
    return instance;
}

// 当前上传操作的 opID（用于 CB_I_S 回调适配器）
thread_local std::string g_currentUploadOpID;

// 注册上传进度回调
void RegisterUploadProgress(char *opID, int progress, char* info) {
    if (!opID) return;
    std::string opID_str(opID);
    std::string info_str(info ? info : "");

    TSFData *tsf = nullptr;
    if (!getTsfMap().find(opID_str, tsf) || tsf == nullptr || tsf->tsf == nullptr) {
        return;
    }

    auto* data = new UploadProgressData{std::move(opID_str), progress, std::move(info_str)};
    napi_status status = napi_call_threadsafe_function(tsf->tsf, data, napi_tsfn_nonblocking);
    if (status != napi_ok) {
        delete data;
    }
}

// CB_I_S 适配器：符合 void (*)(int, char*) 签名，供 upload_file/upload_logs 调用
void UploadProgressCBAdapter(int eventCode, char* data) {
    // 构建进度信息
    // eventCode 作为进度值，data 作为额外信息
    RegisterUploadProgress(
        g_currentUploadOpID.empty() ? nullptr : const_cast<char*>(g_currentUploadOpID.c_str()),
        eventCode,
        data);
}

// 上传进度回调的 JS 调用处理
void OnCallJSUploadProgress(napi_env env, napi_value js_callback, void* /*context*/, void* data) {
    auto* uploadData = static_cast<UploadProgressData*>(data);
    if (!uploadData) return;

    // 构造 JSON 字符串传递给 JS: {"progress": number, "info": "string"}
    char jsonBuffer[256];
    snprintf(jsonBuffer, sizeof(jsonBuffer),
             "{\"progress\":%d,\"info\":\"%s\"}",
             uploadData->progress,
             uploadData->info.c_str());

    napi_value result = SetJSString(env, std::string(jsonBuffer));
    napi_call_function(env, nullptr, js_callback, 1, &result, nullptr);

    delete uploadData;
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

// 创建上传进度的 TSF（使用 UploadProgressData 和 OnCallJSUploadProgress）
TsfRegistration CreateUploadTSF(napi_env env, const std::string& opID, napi_value jsCB) {
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
    napi_status status = napi_create_threadsafe_function(env, jsCB, NULL, resource_name, 0, 1, NULL, NULL, NULL,
                                                         OnCallJSUploadProgress, &tsf);
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