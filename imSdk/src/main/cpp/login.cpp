//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "login.h"
#include "listener.h"
#include "callback.h"

/*
@napi-ts
初始化SDK.
@param operationID - 唯一操作标识
@param config - 配置参数
@returns number
@signature export function initSdk(operationID: string, config: string): number;
*/
napi_value InitSdk(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto config = GetJSString(env, args[1]);
    int32_t result = init_sdk(onListener, const_cast<char*>(operationID.c_str()), const_cast<char*>(config.c_str()));
    return SetJSInt32(env, result);
}

/*
@napi-ts
反初始化SDK.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function unInitSdk(operationID: string): void;
*/
napi_value UnInitSdk(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 1;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    un_init_sdk(const_cast<char*>(operationID.c_str()));
    return ReturnVoid(env);
}

/*
@napi-ts
登录.
@param operationID - 唯一操作标识
@param userID - 用户ID
@param token - token
@returns Promise<string>
@signature export function login(operationID: string, userID: string, token: string): Promise<string>;
*/
napi_value Login(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userID = GetJSString(env, args[1]);
    auto token = GetJSString(env, args[2]);
    
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        login(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(userID.c_str()),const_cast<char*>(token.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
登出.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function logout(operationID: string): Promise<string>;
*/
napi_value Logout(napi_env env, napi_callback_info info){
    constexpr size_t kArgc = 1;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);

    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        logout(RegisterSISS, const_cast<char*>(operationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
设置后台运行状态.
@param operationID - 唯一操作标识
@param isBackground - 是否后台运行
@returns Promise<string>
@signature export function setAppBackgroundStatus(operationID: string, isBackground: boolean): Promise<string>;
*/
napi_value SetAppBackgroundStatus(napi_env env, napi_callback_info info){
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto isBackground = GetJSBoolean(env, args[1]);

    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        set_app_background_status(RegisterSISS, const_cast<char*>(operationID.c_str()), isBackground);
    }
    return result.promise;
}

/*
@napi-ts
连接状态改变.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function networkStatusChanged(operationID: string): Promise<string>;
*/
napi_value NetworkStatusChanged(napi_env env, napi_callback_info info){
    constexpr size_t kArgc = 1;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);

    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        network_status_changed(RegisterSISS, const_cast<char*>(operationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取登录状态.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function getLoginStatus(operationID: string): number;
*/
napi_value GetLoginStatus(napi_env env, napi_callback_info info){
    constexpr size_t kArgc = 1;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);

    int status = get_login_status(const_cast<char*>(operationID.c_str()));
    return SetJSInt32(env, status);
}

/*
@napi-ts
获取当前登录用户.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function getLoginUser(operationID: string): string;
*/
napi_value GetLoginUser(napi_env env, napi_callback_info info){
    const char *user = get_login_user();
    return SetJSString(env, std::string(user));
}