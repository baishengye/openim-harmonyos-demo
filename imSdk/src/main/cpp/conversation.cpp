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

// ==================== Conversation Functions ====================

napi_value NAPI_getAllConversationList(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getAllConversationList_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetAllConversationList(int baseCallbackID, char* operationID)
    GetAllConversationList(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getConversationListSplit(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    int offset = GetIntFromJS(env, args[2]);
    int count = GetIntFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getConversationListSplit_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetConversationListSplit(int baseCallbackID, char* operationID, int offset, int count)
    GetConversationListSplit(cbId, (char*)operationID.c_str(), offset, count);
    return CreateJSUndefined(env);
}

napi_value NAPI_getOneConversation(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    int sessionType = GetIntFromJS(env, args[2]);
    std::string sourceID = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getOneConversation_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetOneConversation(int baseCallbackID, char* operationID, int sessionType, char* isSession)
    GetOneConversation(cbId, (char*)operationID.c_str(), sessionType, (char*)sourceID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getMultipleConversation(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationIDList = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getMultipleConversation_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetMultipleConversation(int baseCallbackID, char* operationID, char* conversationIDList)
    GetMultipleConversation(cbId, (char*)operationID.c_str(), (char*)conversationIDList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getConversationIDBySessionType(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string sourceID = GetStringFromJS(env, args[1]);
    int sessionType = GetIntFromJS(env, args[2]);
    std::string operationID = "napi_getConvID_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    char* result = GetConversationIDBySessionType((char*)operationID.c_str(), (char*)sourceID.c_str(), sessionType);
    std::string convID = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, convID);
}

napi_value NAPI_getTotalUnreadMsgCount(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getTotalUnreadMsgCount_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetTotalUnreadMsgCount(int baseCallbackID, char* operationID)
    GetTotalUnreadMsgCount(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_markConversationMessageAsRead(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_markRead_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: MarkConversationMessageAsRead(int baseCallbackID, char* operationID, char* conversationID)
    MarkConversationMessageAsRead(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_setConversation(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    std::string params = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setConversation_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SetConversation(int baseCallbackID, char* operationID, char* conversationID, char* params)
    SetConversation(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)params.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_setConversationDraft(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    std::string draftText = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setDraft_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SetConversationDraft(int baseCallbackID, char* operationID, char* conversationID, char* draftText)
    SetConversationDraft(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)draftText.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_pinConversation(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    bool isPinned = GetBoolFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_pinConv_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SetPinnedConversation(int baseCallbackID, char* operationID, char* conversationID, int isPinned)
    SetPinnedConversation(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), isPinned ? 1 : 0);
    return CreateJSUndefined(env);
}

napi_value NAPI_setConversationRecvMessageOpt(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    int opt = GetIntFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setRecvOpt_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    std::string convIDList = "[\"" + conversationID + "\"]";
    int cbId = StoreBaseCallback(env, args[0]);
    // Note: GetConversationRecvMessageOpt doesn't need baseCallbackID based on the .h
    GetConversationRecvMessageOpt((char*)operationID.c_str(), (char*)convIDList.c_str());
    (void)cbId; // suppress unused warning
    return CreateJSUndefined(env);
}

napi_value NAPI_setConversationPrivateChat(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    bool isPrivate = GetBoolFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setPrivate_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    std::string params = "{\"isPrivate\":" + std::string(isPrivate ? "true" : "false") + "}";
    // New signature: SetConversation(int baseCallbackID, char* operationID, char* conversationID, char* params)
    SetConversation(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)params.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_setConversationBurnDuration(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    int burnDuration = GetIntFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setBurn_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    std::string params = "{\"burnDuration\":" + std::to_string(burnDuration) + "}";
    // New signature: SetConversation(int baseCallbackID, char* operationID, char* conversationID, char* params)
    SetConversation(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)params.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_resetConversationGroupAtType(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_resetAt_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    std::string params = "{\"groupAtType\":0}";
    // New signature: SetConversation(int baseCallbackID, char* operationID, char* conversationID, char* params)
    SetConversation(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)params.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_hideConversation(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_hideConv_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: HideAllConversations(int baseCallbackID, char* operationID)
    HideAllConversations(cbId, (char*)operationID.c_str());
    (void)conversationID; // suppress unused warning
    return CreateJSUndefined(env);
}

napi_value NAPI_hideAllConversations(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_hideAll_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: HideAllConversations(int baseCallbackID, char* operationID)
    HideAllConversations(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_clearConversationAndDeleteAllMsg(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_clearConv_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: ClearConversationAndDeleteAllMsg(int baseCallbackID, char* operationID, char* conversationID)
    ClearConversationAndDeleteAllMsg(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_deleteConversationAndDeleteAllMsg(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_deleteConv_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: DeleteConversationAndDeleteAllMsg(int baseCallbackID, char* operationID, char* conversationID)
    DeleteConversationAndDeleteAllMsg(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str());
    return CreateJSUndefined(env);
}
