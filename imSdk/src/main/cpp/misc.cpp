//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "misc.h"
#include "callback.h"

/*
@napi-ts
订阅用户在线状态.
@param operationID - 唯一操作标识
@param userIDs - 用户ID列表
@returns Promise<string>
@signature export function subscribeUsersStatus(operationID: string, userIDs: string): Promise<string>;
*/
napi_value SubscribeUsersStatus(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userIDs = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        subscribe_users_status(RegisterSISS,
                             const_cast<char*>(operationID.c_str()),
                             const_cast<char*>(userIDs.c_str()));
    }
    return result.promise;   
}

/*
@napi-ts
取消订阅用户在线状态.
@param operationID - 唯一操作标识
@param userIDs - 用户ID列表
@returns Promise<string>
@signature export function unSubscribeUsersStatus(operationID: string, userIDs: string): Promise<string>;
*/
napi_value UnSubscribeUsersStatus(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userIDs = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        unsubscribe_users_status(RegisterSISS,
                             const_cast<char*>(operationID.c_str()),
                             const_cast<char*>(userIDs.c_str()));
    }
    return result.promise;   
}

/*
@napi-ts
获取订阅的用户在线状态.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function getSubscribeUsersStatus(operationID: string): Promise<string>;
*/
napi_value GetSubscribeUsersStatus(napi_env env, napi_callback_info info) {
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
        get_subscribe_users_status(RegisterSISS,
                             const_cast<char*>(operationID.c_str()));
    }
    return result.promise;   
}

/*
@napi-ts
获取指定用户在线状态.
@param operationID - 唯一操作标识
@param userIDs - 用户ID列表
@returns Promise<string>
@signature export function getUserStatus(operationID: string, userIDs: string): Promise<string>;
*/
napi_value GetUserStatus(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userIDs = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_user_status(RegisterSISS,
                             const_cast<char*>(operationID.c_str()),
                             const_cast<char*>(userIDs.c_str()));
    }
    return result.promise;   
}

/*
@napi-ts
获取用户信息.
@param operationID - 唯一操作标识
@param userIDs - 用户ID列表
@returns Promise<string>
@signature export function getUsersInfo(operationID: string, userIDs: string): Promise<string>;
*/
napi_value GetUsersInfo(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userIDs = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_users_info(RegisterSISS,
                             const_cast<char*>(operationID.c_str()),
                             const_cast<char*>(userIDs.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
设置我的信息.
@param operationID - 唯一操作标识
@param userInfo - 用户信息
@returns Promise<string>
@signature export function setSelfInfo(operationID: string, userInfo: string): Promise<string>;
*/
napi_value SetSelfInfo(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userIDs = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        set_self_info(RegisterSISS,
                             const_cast<char*>(operationID.c_str()),
                             const_cast<char*>(userIDs.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取我的信息.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function getSelfUserInfo(operationID: string): Promise<string>;
*/
napi_value GetSelfUserInfo(napi_env env, napi_callback_info info) {
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
        get_self_user_info(RegisterSISS,
                             const_cast<char*>(operationID.c_str()));
    }
    return result.promise;
}
napi_value UploadFile(napi_env env, napi_callback_info info) {
//    constexpr size_t kArgc = 2;
//    napi_value args[kArgc];
//    size_t argc = kArgc;
//    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
//    if (argc < kArgc) {
//        ThrowError(env, ARG_ERR, "missing arguments");
//        return nullptr;
//    }
//    auto operationID = GetJSString(env, args[0]);
//    auto req = GetJSString(env, args[2]);
//    auto result = CreateTSF(env, operationID, nullptr);
//    if (result.should_proceed) {
//        upload_file(RegisterSISS,
//                             const_cast<char*>(operationID.c_str()),
//                             const_cast<char*>(req.c_str()));
//    }
//    return result.promise;
    return nullptr;
}
napi_value UpdateFcmToken(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto expireTime = GetJSInt64(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        update_fcm_token(RegisterSISS,
                             const_cast<char*>(operationID.c_str()),
                             const_cast<char*>(conversationID.c_str()),
                             expireTime);
    }
    return result.promise;
}

/*
@napi-ts
设置APP角标.
@param operationID - 唯一操作标识
@param appUnreadCount - 未读数量
@returns Promise<string>
@signature export function setAppBadge(operationID: string, appUnreadCount: number): Promise<string>;
*/
napi_value SetAppBadge(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto appUnreadCount = GetJSInt32(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        set_app_Badge(RegisterSISS,
                             const_cast<char*>(operationID.c_str()),
                             appUnreadCount);
    }
    return result.promise;
}
napi_value UploadLogs(napi_env env, napi_callback_info info) {
    return nullptr;
}
napi_value Logs(napi_env env, napi_callback_info info) {
    return nullptr;
}
