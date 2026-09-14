//
// Created on 2026/7/27.
//

//#include "include/libopenimsdk.h"
#include "napi/native_api.h"
#include "hilog/log.h"
#include "callback.h"
#include "utils.h"

static napi_status GetBoundCallbackProperty(napi_env env, napi_value receiver,
                                             const char* name, napi_value* result) {
    napi_value callback = nullptr;
    napi_status status = napi_get_named_property(env, receiver, name, &callback);
    if (status != napi_ok) return status;
    *result = BindCallbackFunction(env, receiver, callback);
    return *result ? napi_ok : napi_generic_failure;
}

#define napi_get_named_property GetBoundCallbackProperty
#include <string>
#include <chrono>

// ==================== Misc Functions ====================

napi_value NAPI_updateFcmToken(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string fcmToken = GetStringFromJS(env, args[2]);
    long long expireTime = GetInt64FromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_updateFcmToken_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    if (cbId == INVALID_CALLBACK_ID) return nullptr;
    // New signature: UpdateFcmToken(int baseCallbackID, char* operationID, char* fcmToken, long long expireTime)
    UpdateFcmToken(cbId, (char*)operationID.c_str(), (char*)fcmToken.c_str(), expireTime);
    return CreateJSUndefined(env);
}

napi_value NAPI_setAppBadge(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    int appUnreadCount = GetIntFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setAppBadge_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    if (cbId == INVALID_CALLBACK_ID) return nullptr;
    // New signature: SetAppBadge(int baseCallbackID, char* operationID, int appUnreadCount)
    SetAppBadge(cbId, (char*)operationID.c_str(), appUnreadCount);
    return CreateJSUndefined(env);
}

napi_value NAPI_uploadLogs(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_uploadLogs_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int line = GetIntFromJS(env, args[2]);
    std::string ex = GetStringFromJS(env, args[3]);
    // args[0] = baseCallback, args[4] = uploadLogProgress
    napi_value baseCallback = args[0];
    napi_value uploadLogProgress = args[4];
    // 提取 uploadLogProgress 中的 onProgress
    napi_value onProgress;
    napi_get_named_property(env, uploadLogProgress, "onProgress", &onProgress);
    int baseCbId = StoreBaseCallback(env, baseCallback);
    if (baseCbId == INVALID_CALLBACK_ID) return nullptr;
    int uploadCbId = StoreUploadLogCallback(env, onProgress);
    if (uploadCbId == INVALID_CALLBACK_ID) {
        DeleteBaseCallback(baseCbId);
        return nullptr;
    }
    // New signature: UploadLogs(int baseCallbackID, int uploadLogCallbackID, char* operationID, int line, char* ex)
    UploadLogs(baseCbId, uploadCbId, (char*)operationID.c_str(), line, (char*)ex.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_uploadFile(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string reqData = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_uploadFile_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }

    // args[0] is baseCallback (onSuccess/onError), args[3] is uploadFileCallback
    napi_value baseCallback = args[0];
    napi_value uploadFileCallback = (argc > 3) ? args[3] : nullptr;

    // 存储 Base 回调
    int baseCbId = StoreBaseCallback(env, baseCallback);
    if (baseCbId == INVALID_CALLBACK_ID) return nullptr;

    // 从 uploadFileCallback 中提取 8 个回调方法
    napi_value onOpen = nullptr, onPartSize = nullptr, onHashPartProgress = nullptr, onHashPartComplete = nullptr;
    napi_value onUploadID = nullptr, onUploadPartComplete = nullptr, onUploadComplete = nullptr, onComplete = nullptr;

    if (uploadFileCallback) {
        napi_get_named_property(env, uploadFileCallback, "open", &onOpen);
        napi_get_named_property(env, uploadFileCallback, "partSize", &onPartSize);
        napi_get_named_property(env, uploadFileCallback, "hashPartProgress", &onHashPartProgress);
        napi_get_named_property(env, uploadFileCallback, "hashPartComplete", &onHashPartComplete);
        napi_get_named_property(env, uploadFileCallback, "uploadID", &onUploadID);
        napi_get_named_property(env, uploadFileCallback, "uploadPartComplete", &onUploadPartComplete);
        napi_get_named_property(env, uploadFileCallback, "uploadComplete", &onUploadComplete);
        napi_get_named_property(env, uploadFileCallback, "complete", &onComplete);
    }

    // 存储上传文件回调
    int uploadCbId = StoreUploadCallbacks(
        env, onOpen, onPartSize, onHashPartProgress, onHashPartComplete,
        onUploadID, onUploadPartComplete, onUploadComplete, onComplete
    );
    if (uploadCbId == INVALID_CALLBACK_ID) {
        DeleteBaseCallback(baseCbId);
        return nullptr;
    }

    // 调用 SDK
    UploadFile(baseCbId, uploadCbId, (char*)operationID.c_str(), (char*)reqData.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_logs(napi_env env, napi_callback_info info) {
    size_t argc = 8;
    napi_value args[8] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    int cbId = StoreBaseCallback(env, args[0]);
    if (cbId == INVALID_CALLBACK_ID) return nullptr;
    int logLevel = GetIntFromJS(env, args[2]);
    std::string file = GetStringFromJS(env, args[3]);
    long long line = GetInt64FromJS(env, args[4]);
    std::string msgs = GetStringFromJS(env, args[5]);
    std::string err = GetStringFromJS(env, args[6]);
    std::string keyAndValue = GetStringFromJS(env, args[7]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_logs_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    // New signature: Logs(int baseCallbackID, char* operationID, int logLevel, char* file, long long line, char* msgs, char* err, char* ex)
    Logs(cbId, (char*)operationID.c_str(), logLevel, (char*)file.c_str(), line, (char*)msgs.c_str(), (char*)err.c_str(), (char*)keyAndValue.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getSdkVersion(napi_env env, napi_callback_info info) {
    SdkString version(GetSdkVersion());
    return CreateJSString(env, version.str());
}

napi_value NAPI_unInitSDK(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[0]);
    if (operationID.empty()) {
        operationID = "napi_unInitSDK_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    // New signature: UnInitSDK(char* operationID)
    UnInitSDK((char*)operationID.c_str());
    DeleteAllCallbacks();
    return CreateJSUndefined(env);
}

napi_value NAPI_getAtAllTag(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[0]);
    if (operationID.empty()) {
        operationID = "napi_getAtAllTag_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    SdkString result(GetAtAllTag(MutableCString(operationID)));
    return CreateJSString(env, result.str());
}

napi_value NAPI_changeInputStates(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    int focus = GetIntFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_changeInputStates_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    if (cbId == INVALID_CALLBACK_ID) return nullptr;
    // New signature: ChangeInputStates(int baseCallbackID, char* operationID, char* conversationID, int focus)
    ChangeInputStates(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), focus);
    return CreateJSUndefined(env);
}

napi_value NAPI_getInputStates(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string conversationID = GetStringFromJS(env, args[2]);
    std::string userID = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getInputStates_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    if (cbId == INVALID_CALLBACK_ID) return nullptr;
    // New signature: GetInputStates(int baseCallbackID, char* operationID, char* conversationID, char* userID)
    GetInputStates(cbId, (char*)operationID.c_str(), (char*)conversationID.c_str(), (char*)userID.c_str());
    return CreateJSUndefined(env);
}
