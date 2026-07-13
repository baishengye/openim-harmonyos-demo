//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "utils.h"
#ifndef IMDEMO_CONVERSATION_H
#define IMDEMO_CONVERSATION_H

napi_value GetAllConversationList(napi_env env, napi_callback_info info);
napi_value GetConversationListSplit(napi_env env, napi_callback_info info);
napi_value GetOneConversation(napi_env env, napi_callback_info info);
napi_value GetMultipleConversation(napi_env env, napi_callback_info info);
napi_value SetConversation(napi_env env, napi_callback_info info);
napi_value HideConversation(napi_env env, napi_callback_info info);
napi_value SetConversationDraft(napi_env env, napi_callback_info info);
napi_value GetTotalUnreadMsgCount(napi_env env, napi_callback_info info);
napi_value GetAtAllTag(napi_env env, napi_callback_info info);
napi_value GetConversationIdBySessionType(napi_env env, napi_callback_info info);

#endif //IMDEMO_CONVERSATION_H
