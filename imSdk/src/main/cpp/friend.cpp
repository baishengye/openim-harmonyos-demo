//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "friend.h"
#include "callback.h"

/*
@napi-ts
获取指定好友信息.
@param operationID - 唯一操作标识
@param userIDList - 好友ID
@param filterBlack - 过滤黑名单
@returns Promise<string>
@signature export function getSpecifiedFriendsInfo(operationID: string, userIDList: string, filterBlack: boolean): Promise<string>;
*/
napi_value GetSpecifiedFriendsInfo(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userIDList = GetJSString(env, args[1]);
    auto filterBlack = GetJSBoolean(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_specified_friends_info(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(userIDList.c_str()), filterBlack);
    }
    return result.promise;
}

/*
@napi-ts
获取好友列表.
@param operationID - 唯一操作标识
@param filterBlack - 过滤黑名单
@returns Promise<string>
@signature export function getFriendList(operationID: string, filterBlack: boolean): Promise<string>;
*/
napi_value GetFriendList(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto filterBlack = GetJSBoolean(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_friend_list(RegisterSISS, const_cast<char*>(operationID.c_str()), filterBlack);
    }
    return result.promise;
}

/*
@napi-ts
分页获取好友列表.
@param operationID - 唯一操作标识
@param offset - 页码
@param count - 每页大小
@param filterBlack - 过滤黑名单
@returns Promise<string>
@signature export function getFriendListPage(operationID: string, offset: number, count: number, filterBlack: boolean): Promise<string>;
*/
napi_value GetFriendListPage(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto offset = GetJSInt32(env, args[1]);
    auto count = GetJSInt32(env, args[2]);
    auto filterBlack = GetJSBoolean(env, args[3]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_friend_list_page(RegisterSISS, const_cast<char*>(operationID.c_str()), offset, count, filterBlack);
    }
    return result.promise;
}

/*
@napi-ts
搜索好友.
@param operationID - 唯一操作标识
@param searchParam - 搜索条件
@returns Promise<string>
@signature export function searchFriends(operationID: string, searchParam: string): Promise<string>;
*/
napi_value SearchFriends(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto searchParam = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        search_friends(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(searchParam.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
好友检查.
@param operationID - 唯一操作标识
@param userIDList - 好友ID
@returns Promise<string>
@signature export function checkFriend(operationID: string, userIDList: string): Promise<string>;
*/
napi_value CheckFriend(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userIDList = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        check_friend(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(userIDList.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
添加好友.
@param operationID - 唯一操作标识
@param userIDReqMsg - 好友请求参数
@returns Promise<string>
@signature export function addFriend(operationID: string, userIDReqMsg: string): Promise<string>;
*/
napi_value AddFriend(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userIDReqMsg = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        add_friend(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(userIDReqMsg.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
更新好友.
@param operationID - 唯一操作标识
@param userIDReqMsg - 好友请求参数
@returns Promise<string>
@signature export function updateFriends(operationID: string, userIDReqMsg: string): Promise<string>;
*/
napi_value UpdateFriends(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto req = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        update_friends(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(req.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
删除好友.
@param operationID - 唯一操作标识
@param friendUserID - 好友ID
@returns Promise<string>
@signature export function deleteFriend(operationID: string, friendUserID: string): Promise<string>;
*/
napi_value DeleteFriend(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto friendUserID = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        delete_friend(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(friendUserID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取好友添加请求列表（接受者）.
@param operationID - 唯一操作标识
@param req - 好友ID
@returns Promise<string>
@signature export function getFriendApplicationListAsRecipient(operationID: string, req: string): Promise<string>;
*/
napi_value GetFriendApplicationListAsRecipient(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto req = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        
        get_friend_application_list_as_recipient(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(req.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取好友添加请求申请列表，（申请者）.
@param operationID - 唯一操作标识
@param req - 好友ID
@returns Promise<string>
@signature export function getFriendApplicationListAsApplicant(operationID: string, req: string): Promise<string>;
*/
napi_value GetFriendApplicationListAsApplicant(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto req = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_friend_application_list_as_applicant(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(req.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
接受好友添加请求.
@param operationID - 唯一操作标识
@param userIDHandleMsg - 好友ID
@returns Promise<string>
@signature export function acceptFriendApplication(operationID: string, userIDHandleMsg: string): Promise<string>;
*/
napi_value AcceptFriendApplication(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userIDHandleMsg = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        accept_friend_application(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(userIDHandleMsg.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
拒绝好友添加请求.
@param operationID - 唯一操作标识
@param userIDHandleMsg - 好友ID
@returns Promise<string>
@signature export function refuseFriendApplication(operationID: string, userIDHandleMsg: string): Promise<string>;
*/
napi_value RefuseFriendApplication(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto userIDHandleMsg = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        refuse_friend_application(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(userIDHandleMsg.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取好友请求未处理数量.
@param operationID - 唯一操作标识
@param req - 好友ID
@returns Promise<string>
@signature export function getFriendApplicationUnhandledCount(operationID: string, req: string): Promise<string>;
*/
napi_value GetFriendApplicationUnhandledCount(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto req = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_friend_application_unhandled_count(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(req.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
添加黑名单.
@param operationID - 唯一操作标识
@param blackUserID - 黑名单用户ID
@param ex - 扩展信息
@returns Promise<string>
@signature export function addBlack(operationID: string, blackUserID: string, ex: string): Promise<string>;
*/
napi_value AddBlack(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto blackUserID = GetJSString(env, args[1]);
    auto ex = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        add_black(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(blackUserID.c_str()), const_cast<char*>(ex.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取黑名单列表.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function getBlackList(operationID: string): Promise<string>;
*/
napi_value GetBlackList(napi_env env, napi_callback_info info) { 
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
        get_black_list(RegisterSISS, const_cast<char*>(operationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
移除黑名单.
@param operationID - 唯一操作标识
@param removeUserID - 用户ID
@returns Promise<string>
@signature export function removeBlack(operationID: string, removeUserID: string): Promise<string>;
*/
napi_value RemoveBlack(napi_env env, napi_callback_info info) { 
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto removeUserID = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        remove_black(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(removeUserID.c_str()));
    }
    return result.promise;
}