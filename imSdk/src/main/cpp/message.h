//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "utils.h"
#ifndef IMDEMO_MESSAGE_H
#define IMDEMO_MESSAGE_H

napi_value CreateTextMessage(napi_env env, napi_callback_info info);
napi_value CreateAdvancedTextMessage(napi_env env, napi_callback_info info);
napi_value CreateTextAtMessage(napi_env env, napi_callback_info info);
napi_value CreateLocationMessage(napi_env env, napi_callback_info info);
napi_value CreateCustomMessage(napi_env env, napi_callback_info info);
napi_value CreateQuoteMessage(napi_env env, napi_callback_info info);
napi_value CreateAdvancedQuoteMessage(napi_env env, napi_callback_info info);
napi_value CreateCardMessage(napi_env, napi_callback_info info);
napi_value CreateVideoMessageFromFullPath(napi_env env, napi_callback_info info);
napi_value CreateImageMessageFromFullPath(napi_env env, napi_callback_info info);
napi_value CreateSoundMessageFromFullPath(napi_env env, napi_callback_info info);
napi_value CreateFileMessageFromFullPath(napi_env env, napi_callback_info info);
napi_value CreateImageMessage(napi_env env, napi_callback_info info);
napi_value CreateImageMessageByUrl(napi_env env, napi_callback_info info);
napi_value CreateSoundMessageByUrl(napi_env env, napi_callback_info info);
napi_value CreateSoundMessage(napi_env env, napi_callback_info info);
napi_value CreateVideoMessageByUrl(napi_env env, napi_callback_info info);
napi_value CreateVideoMessage(napi_env env, napi_callback_info info);
napi_value CreateFileMessageByUrl(napi_env env, napi_callback_info info);
napi_value CreateFileMessage(napi_env env, napi_callback_info info);
napi_value CreateMergerMessage(napi_env env, napi_callback_info info);
napi_value CreateFaceMessage(napi_env env, napi_callback_info info);
napi_value CreateForwardMessage(napi_env env, napi_callback_info info);

napi_value SendMessage(napi_env env, napi_callback_info info);
napi_value SendMessageNotOss(napi_env env, napi_callback_info info);
napi_value FindMessageList(napi_env env, napi_callback_info info);
napi_value GetAdvancedHistoryMessageList(napi_env env, napi_callback_info info);
napi_value GetAdvancedHistoryMessageListReverse(napi_env env, napi_callback_info info);
napi_value RevokeMessage(napi_env env, napi_callback_info info);
napi_value TypingStatusUpdate(napi_env env, napi_callback_info info);
napi_value MarkConversationMessageAsRead(napi_env env, napi_callback_info info);
napi_value DeleteMessageFromLocalStorage(napi_env env, napi_callback_info info);
napi_value DeleteMessage(napi_env env, napi_callback_info info);
napi_value HideAllConversations(napi_env env, napi_callback_info info);
napi_value DeleteAllMsgFromLocalAndSvr(napi_env env, napi_callback_info info);
napi_value DeleteAllMsgFromLocal(napi_env env, napi_callback_info info);
napi_value ClearConversationAndDeleteAllMsg(napi_env env, napi_callback_info info);
napi_value DeleteConversationAndDeleteAllMsg(napi_env env, napi_callback_info info);
napi_value InsertSingleMessageToLocalStorage(napi_env env, napi_callback_info info);
napi_value InsertGroupMessageToLocalStorage(napi_env env, napi_callback_info info);
napi_value SearchLocalMessages(napi_env env, napi_callback_info info);
napi_value SetMessageLocalEx(napi_env env, napi_callback_info info);
napi_value ChangeInputStates(napi_env env, napi_callback_info info);
napi_value GetInputStates(napi_env env, napi_callback_info info);
#endif //IMDEMO_MESSAGE_H
