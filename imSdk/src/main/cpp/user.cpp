//
// Created on 2026/7/27.
//

#include "libs/include/libopenimsdk.h"
#include "napi/native_api.h"
#include "hilog/log.h"
#include <string>
#include <chrono>
#include "callback.h"
#include "utils.h"

// ==================== User Functions ====================

napi_value NAPI_getUsersInfo(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userIDList = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getUsersInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetUsersInfo(int baseCallbackID, char* operationID, char* userIDList)
    GetUsersInfo(cbId, (char*)operationID.c_str(), (char*)userIDList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getSelfUserInfo(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getSelfUserInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetSelfUserInfo(int baseCallbackID, char* operationID)
    GetSelfUserInfo(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_setSelfInfo(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userInfo = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setSelfInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SetSelfInfo(int baseCallbackID, char* operationID, char* userInfo)
    SetSelfInfo(cbId, (char*)operationID.c_str(), (char*)userInfo.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getUserStatus(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userIDList = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getUserStatus_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetUserStatus(int baseCallbackID, char* operationID, char* userIDList)
    GetUserStatus(cbId, (char*)operationID.c_str(), (char*)userIDList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_subscribeUsersStatus(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userIDList = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_subscribeUsersStatus_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SubscribeUsersStatus(int baseCallbackID, char* operationID, char* userIDList)
    SubscribeUsersStatus(cbId, (char*)operationID.c_str(), (char*)userIDList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_unsubscribeUsersStatus(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userIDList = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_unsubscribeUsersStatus_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: UnsubscribeUsersStatus(int baseCallbackID, char* operationID, char* userIDList)
    UnsubscribeUsersStatus(cbId, (char*)operationID.c_str(), (char*)userIDList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getSubscribeUsersStatus(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getSubscribeUsersStatus_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetSubscribeUsersStatus(int baseCallbackID, char* operationID)
    GetSubscribeUsersStatus(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_setAppBackgroundStatus(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    bool isBackground = GetBoolFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setAppBackgroundStatus_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SetAppBackgroundStatus(int baseCallbackID, char* operationID, int isBackground)
    SetAppBackgroundStatus(cbId, (char*)operationID.c_str(), isBackground ? 1 : 0);
    return CreateJSUndefined(env);
}

napi_value NAPI_networkStatusChanged(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_networkStatusChanged_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: NetworkStatusChanged(int baseCallbackID, char* operationID)
    NetworkStatusChanged(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}
