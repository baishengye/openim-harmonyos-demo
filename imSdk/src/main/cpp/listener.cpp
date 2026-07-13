//
// Created on 2025/12/28.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "listener.h"
#include "utils.h"
static napi_threadsafe_function tsfOnListener = nullptr;

void releaseTSF() {
    if (tsfOnListener != nullptr) {
        napi_release_threadsafe_function(tsfOnListener,  napi_tsfn_release);
    }
}
static void callJsCallbackIS(napi_env env, napi_value js_callback, void* /*context*/, void* data) {
    if (!data) {
        OH_LOG_INFO(LOG_APP, "callJsCallbackIS received null data");
        return;
    }

    auto* payload = static_cast<CBDataIS*>(data);
    //OH_LOG_INFO(LOG_APP, "executing js callback, event:%{public}d, data:%{public}s",payload->event, payload->data.c_str());

    napi_value argv[2];
    napi_status value1 = napi_create_int64(env, payload->event, &argv[0]);
    napi_status value2 = napi_create_string_utf8(env, payload->data.c_str(), NAPI_AUTO_LENGTH, &argv[1]);

    if (value1 != napi_ok || value2 != napi_ok) {
        OH_LOG_INFO(LOG_APP, "failed to create js callback args");
        delete payload;
        return;
    }

    napi_value global;
    napi_get_global(env, &global);

    napi_value result;
    napi_status call_status = napi_call_function(env, global, js_callback, 2, argv, &result);
    if (call_status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "failed to call js callback function");
        napi_value error;
        napi_get_and_clear_last_exception(env, &error);
    }

    delete payload;    
}
static void callJsCallbackSISSS(napi_env env, napi_value js_callback, void* /*context*/, void* data) {
    if (!data) {
        OH_LOG_INFO(LOG_APP, "callJsCallbackIS received null data");
        return;
    }

    auto* payload = static_cast<CBDataSISS*>(data);
    //OH_LOG_INFO(LOG_APP, "executing js callback, operationID:%{public}s, errCode:%{public}d, errMsg:%{public}s, data:%{public}s",
    //            payload->operationID.c_str(), payload->errCode, payload->errMsg.c_str(), payload->data.c_str());

    napi_value argv[4];
    napi_status value1 = napi_create_string_utf8(env, payload->operationID.c_str(), NAPI_AUTO_LENGTH, &argv[0]);
    napi_status value2 = napi_create_int64(env, payload->errCode, &argv[1]);
    napi_status value3 = napi_create_string_utf8(env, payload->errMsg.c_str(), NAPI_AUTO_LENGTH, &argv[2]);
    napi_status value4 = napi_create_string_utf8(env, payload->data.c_str(), NAPI_AUTO_LENGTH, &argv[3]);

    if (value1 != napi_ok || value2 != napi_ok || value3 != napi_ok || value4 != napi_ok) {
        OH_LOG_INFO(LOG_APP, "failed to create js callback args");
        delete payload;
        return;
    }

    napi_value global;
    napi_get_global(env, &global);

    napi_value result;
    napi_status call_status = napi_call_function(env, global, js_callback, 4, argv, &result);
    if (call_status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "failed to call js callback function");
        napi_value error;
        napi_get_and_clear_last_exception(env, &error);
    }

    delete payload;     
}

static napi_value setListener(napi_env env, napi_callback_info info, char *tsf_name, napi_threadsafe_function_call_js call_js_cb) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc != 1) {
        napi_throw_error(env, nullptr, "expected 1 argument");
        return nullptr;
    }

    napi_valuetype type;
    napi_typeof(env, args[0], &type);
    if (type != napi_function) {
        napi_throw_error(env, nullptr, "argument must be a function");
        return nullptr;
    }

    if (tsfOnListener != nullptr) {
        OH_LOG_INFO(LOG_APP, "tsf [%{public}s] default is not null", tsf_name);
        napi_release_threadsafe_function(tsfOnListener, napi_tsfn_release);
        tsfOnListener = nullptr;
    }
    napi_value resource_name;
    napi_create_string_utf8(
        env,
        tsf_name,
        NAPI_AUTO_LENGTH,
        &resource_name
    );
    napi_status status = napi_create_threadsafe_function(
        env,
        args[0],
        nullptr,
        resource_name,
        0,
        1,
        nullptr,
        nullptr,
        nullptr,
        call_js_cb,
        &tsfOnListener
    );

    if (status != napi_ok || tsfOnListener == nullptr) {
        OH_LOG_ERROR(LOG_APP, "tsf [%{public}s] create failed, status=%{public}d", tsf_name, static_cast<int>(status));
        napi_throw_error(env, nullptr, "failed to create tsf");
        return nullptr;
    }

    OH_LOG_INFO(LOG_APP, "im_sdk tsf [%{public}s] create success", tsf_name);
    return nullptr;   
}
static void onListenerIS(int event, char* data, napi_threadsafe_function tsf) {
    if (tsfOnListener == nullptr) {
        OH_LOG_INFO(LOG_APP, "im_sdk onListenerIS event: %{public}d, data: %{public}s, onListenerIS == nullptr", event, data);
        return;
    }
    auto* payload = new CBDataIS{event, data ? std::string(data) : std::string()};
    napi_status status = napi_call_threadsafe_function(tsf, payload, napi_tsfn_nonblocking);

    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "napi_call_threadsafe_function failed: %{public}d", static_cast<int>(status));
        delete payload;
    }
}
static void onListenerSISS(char * operationID ,int errCode,char * errMsg,char *data, napi_threadsafe_function tsf) {
    if (tsf == nullptr) {
        return;
    }
    auto* payload = new CBDataSISS{
        operationID ? std::string(operationID) : std::string(), 
        errCode,
        errMsg ? std::string(errMsg) : std::string(), 
        data ? std::string(data) : std::string(),
    };
    napi_status status = napi_call_threadsafe_function(tsf, payload, napi_tsfn_nonblocking);

    if (status != napi_ok) {
        OH_LOG_INFO(LOG_APP, "napi_call_threadsafe_function failed: %{public}d", static_cast<int>(status));
        delete payload;
    }
}
void onListener(int event, char* data) {
    //OH_LOG_INFO(LOG_APP, "imsdk onListener event: %{public}d, data: %{public}s", event, data);
    onListenerIS(event, data, tsfOnListener);
}

/*
@napi-ts
设置连接状态回调监听函数.
@param callback - 监听函数
@param callback.event - 状态类型
@param callback.data - 状态描述
@returns void
@signature export function setListener(callback: (event: number, data: string) => void): void;
*/
napi_value setListener(napi_env env, napi_callback_info info) {
    char tsf_name[] = "tsfOnListener";
    napi_value result = setListener(env, info, tsf_name, callJsCallbackIS);    
    set_group_listener(onListener);
    set_conversation_listener(onListener);
    set_advanced_msg_listener(onListener);
    set_batch_msg_listener(onListener);
    set_user_listener(onListener);
    set_friend_listener(onListener);
    set_custom_business_listener(onListener);
    return result;
}