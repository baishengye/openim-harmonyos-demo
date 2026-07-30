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

// ==================== Message Functions ====================

napi_value NAPI_createTextMessage(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string text = GetStringFromJS(env, args[1]);
    std::string operationID = GetStringFromJS(env, args[2]);
    if (operationID.empty()) {
        operationID = "napi_createText_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateTextMessage((char*)text.c_str(), (char*)operationID.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createImageMessage(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string imagePath = GetStringFromJS(env, args[1]);
    std::string operationID = GetStringFromJS(env, args[2]);
    if (operationID.empty()) {
        operationID = "napi_createImage_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateImageMessage((char*)imagePath.c_str(), (char*)operationID.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createImageMessageFromFullPath(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string fileFullPath = GetStringFromJS(env, args[1]);
    std::string operationID = GetStringFromJS(env, args[2]);
    if (operationID.empty()) {
        operationID = "napi_createImageFullPath_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateImageMessage((char*)fileFullPath.c_str(), (char*)operationID.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createImageMessageByURL(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    std::string params = GetStringFromJS(env, args[0]);
    if (operationID.empty()) {
        operationID = "napi_createImageByURL_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateImageMessageByURL((char*)operationID.c_str(), (char*)params.c_str(), nullptr, nullptr, nullptr);
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createSoundMessage(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string soundPath = GetStringFromJS(env, args[1]);
    long long duration = GetInt64FromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_createSound_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateSoundMessage((char*)soundPath.c_str(), duration, (char*)operationID.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createSoundMessageFromFullPath(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string soundPath = GetStringFromJS(env, args[1]);
    long long duration = GetInt64FromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_createSoundFullPath_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateSoundMessageFromFullPath((char*)operationID.c_str(), (char*)soundPath.c_str(), duration);
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createSoundMessageByURL(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    std::string params = GetStringFromJS(env, args[0]);
    if (operationID.empty()) {
        operationID = "napi_createSoundByURL_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateSoundMessageByURL((char*)operationID.c_str(), (char*)params.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createFileMessage(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string filePath = GetStringFromJS(env, args[1]);
    std::string fileName = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_createFile_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateFileMessage((char*)filePath.c_str(), (char*)fileName.c_str(), (char*)operationID.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createFileMessageFromFullPath(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string fileFullPath = GetStringFromJS(env, args[1]);
    std::string fileName = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_createFileFullPath_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateFileMessageFromFullPath((char*)operationID.c_str(), (char*)fileFullPath.c_str(), (char*)fileName.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createFileMessageByURL(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    std::string params = GetStringFromJS(env, args[0]);
    if (operationID.empty()) {
        operationID = "napi_createFileByURL_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateFileMessageByURL((char*)operationID.c_str(), (char*)params.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createVideoMessage(napi_env env, napi_callback_info info) {
    size_t argc = 6;
    napi_value args[6];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string videoPath = GetStringFromJS(env, args[1]);
    std::string videoType = GetStringFromJS(env, args[2]);
    long long duration = GetInt64FromJS(env, args[3]);
    std::string snapshotPath = GetStringFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[5]);
    if (operationID.empty()) {
        operationID = "napi_createVideo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateVideoMessage((char*)videoPath.c_str(), (char*)videoType.c_str(), duration, (char*)snapshotPath.c_str(), (char*)operationID.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createVideoMessageByURL(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    std::string params = GetStringFromJS(env, args[0]);
    if (operationID.empty()) {
        operationID = "napi_createVideoMessageByURL_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateVideoMessageByURL((char*)operationID.c_str(), (char*)params.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createVideoMessageFromFullPath(napi_env env, napi_callback_info info) {
    size_t argc = 6;
    napi_value args[6];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string videoFullPath = GetStringFromJS(env, args[1]);
    std::string videoType = GetStringFromJS(env, args[2]);
    long long duration = GetInt64FromJS(env, args[3]);
    std::string snapshotFullPath = GetStringFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[5]);
    if (operationID.empty()) {
        operationID = "napi_createVideoFullPath_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateVideoMessageFromFullPath((char*)operationID.c_str(), (char*)videoFullPath.c_str(), (char*)videoType.c_str(), duration, (char*)snapshotFullPath.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createLocationMessage(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string description = GetStringFromJS(env, args[1]);
    double longitude = std::stod(GetStringFromJS(env, args[2]));
    double latitude = std::stod(GetStringFromJS(env, args[3]));
    std::string operationID = GetStringFromJS(env, args[4]);
    if (operationID.empty()) {
        operationID = "napi_createLoc_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateLocationMessage((char*)operationID.c_str(), (char*)description.c_str(), longitude, latitude);
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createCustomMessage(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string data = GetStringFromJS(env, args[1]);
    std::string extension = GetStringFromJS(env, args[2]);
    std::string description = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[4]);
    if (operationID.empty()) {
        operationID = "napi_createCustom_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateCustomMessage((char*)data.c_str(), (char*)extension.c_str(), (char*)description.c_str(), (char*)operationID.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createQuoteMessage(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string text = GetStringFromJS(env, args[1]);
    std::string message = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_createQuote_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateQuoteMessage((char*)text.c_str(), (char*)message.c_str(), (char*)operationID.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createFaceMessage(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    int index = GetIntFromJS(env, args[1]);
    std::string data = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_createFace_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateFaceMessage((char*)operationID.c_str(), index, (char*)data.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createMergerMessage(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string messageList = GetStringFromJS(env, args[1]);
    std::string title = GetStringFromJS(env, args[2]);
    std::string summaryList = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[4]);
    if (operationID.empty()) {
        operationID = "napi_createMerger_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateMergerMessage((char*)messageList.c_str(), (char*)title.c_str(), (char*)summaryList.c_str(), (char*)operationID.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createForwardMessage(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string message = GetStringFromJS(env, args[1]);
    std::string operationID = GetStringFromJS(env, args[2]);
    if (operationID.empty()) {
        operationID = "napi_createForward_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateForwardMessage((char*)message.c_str(), (char*)operationID.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createCardMessage(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string params = GetStringFromJS(env, args[1]);
    std::string operationID = GetStringFromJS(env, args[2]);
    if (operationID.empty()) {
        operationID = "napi_createCard_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateCardMessage((char*)operationID.c_str(), (char*)params.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createTextAtMessage(napi_env env, napi_callback_info info) {
    size_t argc = 6;
    napi_value args[6];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string text = GetStringFromJS(env, args[1]);
    std::string atUserIDList = GetStringFromJS(env, args[2]);
    std::string atUsersInfo = GetStringFromJS(env, args[3]);
    std::string quoteMessage = GetStringFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[5]);
    if (operationID.empty()) {
        operationID = "napi_createTextAt_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateTextAtMessage((char*)operationID.c_str(), (char*)text.c_str(), (char*)atUserIDList.c_str(), (char*)atUsersInfo.c_str(), (char*)quoteMessage.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_sendMessage(napi_env env, napi_callback_info info) {
    size_t argc = 8;
    napi_value args[8];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string message = GetStringFromJS(env, args[1]);
    std::string recvID = GetStringFromJS(env, args[2]);
    std::string groupID = GetStringFromJS(env, args[3]);
    std::string offlinePushInfo = GetStringFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[5]);
    int isOnlineOnly = GetIntFromJS(env, args[6]);
    if (operationID.empty()) {
        operationID = "napi_sendMsg_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    // Store SendMsgCallBack callback (extracts onSuccess, onError, onProgress from args[0])
    int cbId = StoreSendMsgCallback(env, args[0]);
    // New signature: SendMessage(int baseCallbackID, int sendReceiptCallbackID, char* message, char* recvID, char* groupID, char* offlinePushInfo, char* operationID, int isOnlineOnly)
    SendMessage(cbId, cbId, (char*)message.c_str(), (char*)recvID.c_str(), (char*)groupID.c_str(), (char*)offlinePushInfo.c_str(), (char*)operationID.c_str(), isOnlineOnly);
    return CreateJSUndefined(env);
}

napi_value NAPI_sendMessageNotOss(napi_env env, napi_callback_info info) {
    size_t argc = 8;
    napi_value args[8];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string message = GetStringFromJS(env, args[1]);
    std::string recvID = GetStringFromJS(env, args[2]);
    std::string groupID = GetStringFromJS(env, args[3]);
    std::string offlinePushInfo = GetStringFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[5]);
    int isOnlineOnly = GetIntFromJS(env, args[6]);
    if (operationID.empty()) {
        operationID = "napi_sendMsgNotOss_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    // Store SendMsgCallBack callback (extracts onSuccess, onError, onProgress from args[0])
    int cbId = StoreSendMsgCallback(env, args[0]);
    // New signature: SendMessageNotOss(int baseCallbackID, int sendReceiptCallbackID, char* message, char* recvID, char* groupID, char* offlinePushInfo, char* operationID, int isOnlineOnly)
    SendMessageNotOss(cbId, cbId, (char*)message.c_str(), (char*)recvID.c_str(), (char*)groupID.c_str(), (char*)offlinePushInfo.c_str(), (char*)operationID.c_str(), isOnlineOnly);
    return CreateJSUndefined(env);
}

napi_value NAPI_typingStatusUpdate(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[1]);
    std::string msgTip = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_typing_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: TypingStatusUpdate(int baseCallbackID, char* operationID, char* conversationID, char* msgTip)
    TypingStatusUpdate(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)msgTip.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_markMessageAsRead(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[1]);
    std::string clientMsgID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_markRead_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: MarkConversationMessageAsRead(int baseCallbackID, char* operationID, char* conversationID)
    MarkConversationMessageAsRead(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_markAllMessageAsRead(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_markAllRead_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: MarkAllConversationMessageAsRead(int baseCallbackID, char* operationID)
    MarkAllConversationMessageAsRead(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_revokeMessage(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[1]);
    std::string clientMsgID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_revoke_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: RevokeMessage(int baseCallbackID, char* operationID, char* conversationID, char* clientMsgID)
    RevokeMessage(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)clientMsgID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_deleteMessageFromLocal(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[1]);
    std::string clientMsgID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_deleteLocal_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: DeleteMessageFromLocal(int baseCallbackID, char* operationID, char* conversationID, char* clientMsgID)
    DeleteMessageFromLocal(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)clientMsgID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_deleteMessage(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[1]);
    std::string clientMsgID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_deleteMsg_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: DeleteMessage(int baseCallbackID, char* operationID, char* conversationID, char* seqList)
    DeleteMessage(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)clientMsgID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_deleteAllMessageFromLocal(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_deleteAllLocal_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: DeleteAllMsgFromLocal(int baseCallbackID, char* operationID)
    DeleteAllMsgFromLocal(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_deleteAllMsgFromLocalAndSvr(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_deleteAll_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    DeleteAllMsgFromLocalAndSvr(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_deleteAllMsgFromLocal(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_deleteAllLocal_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    DeleteAllMsgFromLocal(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_insertSingleMessageToLocal(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string message = GetStringFromJS(env, args[1]);
    std::string recvID = GetStringFromJS(env, args[2]);
    std::string sendID = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[4]);
    if (operationID.empty()) {
        operationID = "napi_insertSingle_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    InsertSingleMessageToLocal(cbId, (char*)operationID.c_str(), (char*)message.c_str(), (char*)recvID.c_str(), (char*)sendID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_insertSingleMessageToLocalStorage(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string message = GetStringFromJS(env, args[1]);
    std::string recvID = GetStringFromJS(env, args[2]);
    std::string sendID = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[4]);
    if (operationID.empty()) {
        operationID = "napi_insertSingleStorage_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    InsertSingleMessageToLocal(cbId, (char*)operationID.c_str(), (char*)message.c_str(), (char*)recvID.c_str(), (char*)sendID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_findMessageList(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string findOptions = GetStringFromJS(env, args[1]);
    std::string operationID = GetStringFromJS(env, args[2]);
    if (operationID.empty()) {
        operationID = "napi_findMsg_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: FindMessageList(int baseCallbackID, char* operationID, char* findOptions)
    FindMessageList(cbId, (char*)operationID.c_str(), (char*)findOptions.c_str());
    return CreateJSUndefined(env);
}

/**
 * @deprecated 此 API 已在 SDK 中废弃，请使用 NAPI_getAdvancedHistoryMessageList
 */
napi_value NAPI_getHistoryMessageList(napi_env env, napi_callback_info info) {
    // Deprecated: 此 API 已在 SDK 中废弃
    return CreateJSUndefined(env);
}

napi_value NAPI_getAdvancedHistoryMessageList(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string getOptions = GetStringFromJS(env, args[1]);
    std::string operationID = GetStringFromJS(env, args[2]);
    if (operationID.empty()) {
        operationID = "napi_getAdvHistory_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetAdvancedHistoryMessageList(int baseCallbackID, char* operationID, char* getMessageOptions)
    GetAdvancedHistoryMessageList(cbId, (char*)operationID.c_str(), (char*)getOptions.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getAdvancedHistoryMessageListReverse(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string getOptions = GetStringFromJS(env, args[1]);
    std::string operationID = GetStringFromJS(env, args[2]);
    if (operationID.empty()) {
        operationID = "napi_getAdvHistoryRev_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetAdvancedHistoryMessageListReverse(int baseCallbackID, char* operationID, char* getMessageOptions)
    GetAdvancedHistoryMessageListReverse(cbId, (char*)operationID.c_str(), (char*)getOptions.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_searchLocalMessages(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string searchParam = GetStringFromJS(env, args[1]);
    std::string operationID = GetStringFromJS(env, args[2]);
    if (operationID.empty()) {
        operationID = "napi_searchLocal_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SearchLocalMessages(int baseCallbackID, char* operationID, char* searchParam)
    SearchLocalMessages(cbId, (char*)operationID.c_str(), (char*)searchParam.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_searchConversation(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string searchParam = GetStringFromJS(env, args[1]);
    std::string operationID = GetStringFromJS(env, args[2]);
    if (operationID.empty()) {
        operationID = "napi_searchConv_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SearchConversation(int baseCallbackID, char* operationID, char* searchParam)
    SearchConversation(cbId, (char*)operationID.c_str(), (char*)searchParam.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_setMessageLocalEx(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[1]);
    std::string clientMsgID = GetStringFromJS(env, args[2]);
    std::string localEx = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[4]);
    if (operationID.empty()) {
        operationID = "napi_setLocalEx_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SetMessageLocalEx(int baseCallbackID, char* operationID, char* conversationID, char* clientMsgID, char* localEx)
    SetMessageLocalEx(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)clientMsgID.c_str(), (char*)localEx.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_deleteMessageFromLocalStorage(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    std::string seqList = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_deleteMessageFromLocalStorage_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: DeleteMessageFromLocalStorage(int baseCallbackID, char* operationID, char* conversationID, char* seqList)
    DeleteMessageFromLocalStorage(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)seqList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_insertGroupMessageToLocalStorage(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string message = GetStringFromJS(env, args[2]);
    std::string groupID = GetStringFromJS(env, args[3]);
    std::string sendID = GetStringFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_insertGroupMessageToLocalStorage_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: InsertGroupMessageToLocalStorage(int baseCallbackID, char* operationID, char* message, char* groupID, char* sendID)
    InsertGroupMessageToLocalStorage(cbId, (char*)operationID.c_str(), (char*)message.c_str(), (char*)groupID.c_str(), (char*)sendID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_markMessagesAsReadByMsgID(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[1]);
    std::string clientMsgIDs = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_markMsgsReadById_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: MarkMessagesAsReadByMsgID(int baseCallbackID, char* operationID, char* conversationID, char* clientMsgIDs)
    MarkMessagesAsReadByMsgID(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)clientMsgIDs.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_createAdvancedQuoteMessage(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    std::string text = GetStringFromJS(env, args[2]);
    std::string message = GetStringFromJS(env, args[3]);
    std::string messageEntityList = GetStringFromJS(env, args[4]);
    if (operationID.empty()) {
        operationID = "napi_createAdvancedQuote_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateAdvancedQuoteMessage((char*)operationID.c_str(), (char*)text.c_str(), (char*)message.c_str(), (char*)messageEntityList.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}

napi_value NAPI_createAdvancedTextMessage(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    std::string text = GetStringFromJS(env, args[2]);
    std::string messageEntityList = GetStringFromJS(env, args[3]);
    if (operationID.empty()) {
        operationID = "napi_createAdvancedText_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    char* result = CreateAdvancedTextMessage((char*)operationID.c_str(), (char*)text.c_str(), (char*)messageEntityList.c_str());
    std::string msg = result ? result : "";
    if (result) FreeString(result);
    return CreateJSString(env, msg);
}
