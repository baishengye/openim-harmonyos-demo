//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "conversation.h"
#include "callback.h"
#include "utils.h"

/*
@napi-ts
获取所有会话列表.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function getAllConversationList(operationID: string): Promise<string>;
*/
napi_value GetAllConversationList(napi_env env, napi_callback_info info) {
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
        get_all_conversation_list(RegisterSISS, const_cast<char*>(operationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
分页获取会话列表.
@param operationID - 唯一操作标识
@param offset - 页码
@param count - 每页大小
@returns Promise<string>
@signature export function getConversationListSplit(operationID: string, offset: number, count: number): Promise<string>;
*/
napi_value GetConversationListSplit(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
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
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_conversation_list_split(RegisterSISS, const_cast<char*>(operationID.c_str()), offset, count);
    }
    return result.promise;
}

/*
@napi-ts
获取指定会话.
@param operationID - 唯一操作标识
@param sessionType - 会话类型
@param sourceID - 会话ID
@returns Promise<string>
@signature export function getOneConversation(operationID: string, sessionType: number, sourceID: string): Promise<string>;
*/
napi_value GetOneConversation(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto sessionType = GetJSInt32(env, args[1]);
    auto sourceID = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_one_conversation(RegisterSISS, const_cast<char*>(operationID.c_str()), sessionType, const_cast<char*>(sourceID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取多个会话.
@param operationID - 唯一操作标识
@param conversationIDList - 会话ID列表
@returns Promise<string>
@signature export function getMultipleConversation(operationID: string, conversationIDList: string): Promise<string>;
*/
napi_value GetMultipleConversation(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationIDList = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_multiple_conversation(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(conversationIDList.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取多个会话.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@param req - 设置参数
@returns Promise<string>
@signature export function setConversation(operationID: string, conversationID: string, req: string): Promise<string>;
*/
napi_value SetConversation(napi_env env, napi_callback_info info) {
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
    auto req = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        set_conversation(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(conversationID.c_str()), const_cast<char*>(req.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
隐藏会话.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@returns Promise<string>
@signature export function hideConversation(operationID: string, conversationID: string): Promise<string>;
*/
napi_value HideConversation(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        hide_conversation(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(conversationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
设置会话草稿.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@param draftText - 会话ID
@returns Promise<string>
@signature export function setConversationDraft(operationID: string, conversationID: string, draftText: string): Promise<string>;
*/
napi_value SetConversationDraft(napi_env env, napi_callback_info info) {
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
    auto draftText = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        set_conversation_draft(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(conversationID.c_str()), const_cast<char*>(draftText.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取消息总未读数量.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function getTotalUnreadMsgCount(operationID: string): Promise<string>;
*/
napi_value GetTotalUnreadMsgCount(napi_env env, napi_callback_info info) {
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
        get_total_unread_msg_count(RegisterSISS, const_cast<char*>(operationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取At所有标记.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function getAtAllTag(operationID: string): Promise<string>;
*/
napi_value GetAtAllTag(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 1;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    const char *tag= get_at_all_tag(const_cast<char*>(operationID.c_str()));
    return SetJSString(env, std::string(tag));
}

/*
@napi-ts
根据指定类型会话ID.
@param operationID - 唯一操作标识
@param sourceID - 
@param sessionType - 会话类型
@returns Promise<string>
@signature export function getConversationIdBySessionType(operationID: string, sourceID: string, sessionType: number): Promise<string>;
*/
napi_value GetConversationIdBySessionType(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto sourceID = GetJSString(env, args[1]);
    auto sessionType = GetJSInt32(env, args[2]);
    const char *tag= get_conversation_id_by_session_type(const_cast<char*>(operationID.c_str()),const_cast<char*>(sourceID.c_str()), sessionType);
    return SetJSString(env, std::string(tag));
}