//
// Created on 2026/7/27.
//

#include "libs/include/libopenimsdk.h"
#include "napi/native_api.h"
#include "hilog/log.h"
#include "callback.h"
#include "utils.h"
#include <string>
#include <chrono>

// ==================== Login Functions ====================

napi_value NAPI_initSdk(napi_env env, napi_callback_info info) {
    LogError("OpenIM", "NAPI_initSdk called");
    size_t argc = 3;
    napi_value args[3];
    napi_status status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    LogError("OpenIM", "NAPI_initSdk napi_get_cb_info status: %{public}d, argc: %{public}zu", status, argc);

    // Extract and register connection listener from args[0]
    if (argc > 0 && args[0]) {
        LogError("OpenIM", "NAPI_initSdk extracting connection listener");
        napi_value onConnecting, onConnectSuccess, onConnectFailed, onKickedOffline, onUserTokenExpired, onUserTokenInvalid;
        napi_get_named_property(env, args[0], "onConnecting", &onConnecting);
        napi_get_named_property(env, args[0], "onConnectSuccess", &onConnectSuccess);
        napi_get_named_property(env, args[0], "onConnectFailed", &onConnectFailed);
        napi_get_named_property(env, args[0], "onKickedOffline", &onKickedOffline);
        napi_get_named_property(env, args[0], "onUserTokenExpired", &onUserTokenExpired);
        napi_get_named_property(env, args[0], "onUserTokenInvalid", &onUserTokenInvalid);

        // Delete existing listener and register new one
        DeleteConnListener();
        StoreConnListener(env, onConnecting, onConnectSuccess, onConnectFailed, onKickedOffline, onUserTokenExpired, onUserTokenInvalid);
        LogError("OpenIM", "NAPI_initSdk connection listener registered");
    }

    std::string config = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    LogError("OpenIM", "NAPI_initSdk config: %{public}s, operationID: %{public}s", config.c_str(), operationID.c_str());
    if (operationID.empty()) {
        operationID = "napi_init_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int result = InitSDK((char*)config.c_str(), (char*)operationID.c_str());
    LogError("OpenIM", "NAPI_initSdk InitSDK result: %{public}d", result);
    napi_value ret;
    napi_create_int32(env, result, &ret);
    return ret;
}

napi_value NAPI_login(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userID = GetStringFromJS(env, args[2]);
    std::string token = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_login_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    // Store callback and register with SDK - callback ID is passed to SDK
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: Login(int baseCallbackID, char* uid, char* token, char* operationID)
    Login(cbId, (char*)userID.c_str(), (char*)token.c_str(), (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_logout(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_logout_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    // Store callback and register with SDK
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: Logout(int baseCallbackID, char* operationID)
    Logout(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getLoginStatus(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[0]);
    int status = GetLoginStatus((char*)operationID.c_str());
    return CreateJSInt(env, status);
}

napi_value NAPI_getLoginUserID(napi_env env, napi_callback_info info) {
    char* userID = GetLoginUserID();
    std::string result = userID ? userID : "";
    if (userID) FreeString(userID);
    return CreateJSString(env, result);
}
