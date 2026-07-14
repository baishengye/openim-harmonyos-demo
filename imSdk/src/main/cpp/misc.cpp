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
/*
@napi-ts
上传文件.
@param operationID - 唯一操作标识
@param req - 上传请求JSON字符串
@param onProgress - 进度回调 (event: number, operationID: string, data: string) => void
@returns Promise<string>
@signature export function uploadFile(operationID: string, req: string, onProgress: (event: number, operationID: string, data: string) => void): Promise<string>;
*/
napi_value UploadFile(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < 2) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto opID = GetJSString(env, args[0]);
    auto req = GetJSString(env, args[1]);
    napi_value onProgress = args[2];

    // 设置进度回调
    if (onProgress != nullptr) {
        napi_valuetype type;
        napi_typeof(env, onProgress, &type);
        if (type == napi_function) {
            SetProgressCallback(env, onProgress, opID);
        }
    }

    auto result = CreateTSF(env, opID, nullptr);
    if (result.should_proceed) {
        upload_file(RegisterSISS,
                    const_cast<char*>(opID.c_str()),
                    const_cast<char*>(req.c_str()),
                    GetUploadProgressCallback());  // 使用进度回调
    }
    return result.promise;
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
/*
@napi-ts
上传日志.
@param operationID - 唯一操作标识
@param line - 日志行数
@param ex - 额外信息
@param onProgress - 进度回调 (event: number, operationID: string, data: string) => void
@returns Promise<string>
@signature export function uploadLogs(operationID: string, line: number, ex: string, onProgress: (event: number, operationID: string, data: string) => void): Promise<string>;
*/
napi_value UploadLogs(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < 3) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto opID = GetJSString(env, args[0]);
    auto line = GetJSInt32(env, args[1]);
    auto ex = GetJSString(env, args[2]);
    napi_value onProgress = args[3];

    // 设置进度回调
    if (onProgress != nullptr) {
        napi_valuetype type;
        napi_typeof(env, onProgress, &type);
        if (type == napi_function) {
            SetProgressCallback(env, onProgress, opID);
        }
    }

    auto result = CreateTSF(env, opID, nullptr);
    if (result.should_proceed) {
        upload_logs(RegisterSISS,
                    const_cast<char*>(opID.c_str()),
                    line,
                    const_cast<char*>(ex.c_str()),
                    GetUploadProgressCallback());
    }
    return result.promise;
}
/*
@napi-ts
记录日志.
@param operationID - 唯一操作标识
@param logLevel - 日志级别
@param file - 文件名
@param line - 行号
@param msgs - 消息内容
@param err - 错误信息
@param keyAndValue - 键值对
@returns Promise<string>
@signature export function logs(operationID: string, logLevel: number, file: string, line: number, msgs: string, err: string, keyAndValue: string): Promise<string>;
*/
napi_value Logs(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 7;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto logLevel = GetJSInt32(env, args[1]);
    auto file = GetJSString(env, args[2]);
    auto line = GetJSInt32(env, args[3]);
    auto msgs = GetJSString(env, args[4]);
    auto err = GetJSString(env, args[5]);
    auto keyAndValue = GetJSString(env, args[6]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        logs(RegisterSISS,
             const_cast<char*>(operationID.c_str()),
             logLevel,
             const_cast<char*>(file.c_str()),
             line,
             const_cast<char*>(msgs.c_str()),
             const_cast<char*>(err.c_str()),
             const_cast<char*>(keyAndValue.c_str()));
    }
    return result.promise;
}
