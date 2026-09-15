#include "callback.h"
#include "include/libopenimsdk.h"
#include <string.h>
#include <memory>
#include <mutex>
#include <stdint.h>
#include <vector>

template <typename Callback>
static uintptr_t CallbackAddress(Callback callback) {
    return reinterpret_cast<uintptr_t>(callback);
}

// ============================================================
// C API 回调前向声明
// ============================================================
extern "C" {
// Base 回调
void CAPI_OnBaseSuccess(int cbId, char* data);
void CAPI_OnBaseError(int cbId, int code, char* message);

// 上传文件回调（SDK 现在传递 cbId 作为第一个参数）
void CAPI_OnUploadOpen(int cbId, long long fileSize);
void CAPI_OnUploadPartSize(int cbId, long long partSize, long long partNumber);
void CAPI_OnUploadHashProgress(int cbId, long long index, long long size, char* partHash);
void CAPI_OnUploadHashComplete(int cbId, char* partsHash, char* fileHash);
void CAPI_OnUploadID(int cbId, char* uploadID);
void CAPI_OnUploadPartComplete(int cbId, long long index, long long partSize, char* partHash);
void CAPI_OnUploadComplete(int cbId, long long fileSize, long long streamSize, long long storageSize);
void CAPI_OnUploadFinish(int cbId, long long size, char* url, long long fileType);

// 日志上传回调（SDK 现在传递 cbId 作为第一个参数）
void CAPI_OnUploadLogProgress(int cbId, long long current, long long total);

// 发送进度回调
void CAPI_OnSendMsg(int cbId, long long progress);

// 连接回调
void CAPI_OnConnConnecting(int value);
void CAPI_OnConnConnectSuccess(int value);
void CAPI_OnConnConnectFailed(int errCode, char* message);
void CAPI_OnConnKickedOffline(int value);
void CAPI_OnConnUserTokenExpired(int value);
void CAPI_OnConnUserTokenInvalid(int value, char* message);

// 消息回调
void CAPI_OnRecvNewMsg(char* msg);
void CAPI_OnRecvReceipt(char* receipt);
void CAPI_OnMsgRevoked(char* msg);
void CAPI_OnRecvOffline(char* msg);
void CAPI_OnMsgDeleted(char* msg);
void CAPI_OnRecvOnline(char* msg);
void CAPI_OnRecvNewMessages(char* messages);
void CAPI_OnRecvOfflineNewMessages(char* messages);

// 会话回调
void CAPI_OnConvSyncStart(int reinstalled);
void CAPI_OnConvSyncFinish(int reinstalled);
void CAPI_OnConvSyncProgress(long long progress);
void CAPI_OnConvSyncFailed(int reinstalled);
void CAPI_OnConvChanged(char* conv);
void CAPI_OnNewConv(char* conv);
void CAPI_OnUnreadChanged(int totalUnreadCount);
void CAPI_OnInputStatus(char* status);

// 群组回调
void CAPI_OnGroupJoinedAdd(char* group);
void CAPI_OnGroupJoinedDel(char* group);
void CAPI_OnGroupMemberAdd(char* member);
void CAPI_OnGroupMemberDel(char* member);
void CAPI_OnGroupAppAdd(char* application);
void CAPI_OnGroupAppDel(char* application);
void CAPI_OnGroupInfoChanged(char* info);
void CAPI_OnGroupDismissed(char* group);
void CAPI_OnGroupMemberInfo(char* info);
void CAPI_OnGroupAppAccept(char* application);
void CAPI_OnGroupAppReject(char* application);

// 好友回调
void CAPI_OnFriendAppAdd(char* application);
void CAPI_OnFriendAppDel(char* application);
void CAPI_OnFriendAppAccept(char* application);
void CAPI_OnFriendAppReject(char* application);
void CAPI_OnFriendAdd(char* friendInfo);
void CAPI_OnFriendDel(char* friendInfo);
void CAPI_OnFriendInfo(char* info);
void CAPI_OnBlackAdd(char* black);
void CAPI_OnBlackDel(char* black);

// 用户回调
void CAPI_OnUserSelfInfoUpdated(char* userInfo);
void CAPI_OnUserStatusChanged(char* status);
void CAPI_OnUserCommandAdd(char* command);
void CAPI_OnUserCommandDelete(char* command);
void CAPI_OnUserCommandUpdate(char* command);

// 信令回调
void CAPI_OnSignalingReceiveNewInvitation(char* invitation);
void CAPI_OnSignalingInviteeAccepted(char* invitation);
void CAPI_OnSignalingInviteeAcceptedByOtherDevice(char* invitation);
void CAPI_OnSignalingInviteeRejected(char* invitation);
void CAPI_OnSignalingInviteeRejectedByOtherDevice(char* invitation);
void CAPI_OnSignalingInvitationCancelled(char* invitation);
void CAPI_OnSignalingInvitationTimeout(char* invitation);
void CAPI_OnSignalingHangUp(char* info);
void CAPI_OnSignalingRoomParticipantConnected(char* info);
void CAPI_OnSignalingRoomParticipantDisconnected(char* info);

// 自定义业务回调
void CAPI_OnRecvCustomBusinessMessage(char* message);

// 消息 KV 信息回调
void CAPI_OnMessageKvInfoChanged(char* kvInfo);
}

// ============================================================
// 全局变量定义
// ============================================================
BaseCallbackContext g_baseCallbacks[CB_MAX];
UploadCallbackContext g_upload_callbacks[CB_MAX];
UploadLogCallbackContext g_uploadLog_callbacks[CB_MAX];
SendMsgCallbackContext g_sendMsg_callbacks[CB_MAX];

// Listener 回调引用（固定使用 index 0）
struct ListenerCallbacks {
    napi_ref onConnecting;
    napi_ref onConnectSuccess;
    napi_ref onConnectFailed;
    napi_ref onKickedOffline;
    napi_ref onUserTokenExpired;
    napi_ref onUserTokenInvalid;

    napi_ref onRecvNewMsg;
    napi_ref onRecvReceipt;
    napi_ref onMsgRevoked;
    napi_ref onRecvOffline;
    napi_ref onMsgDeleted;
    napi_ref onRecvOnline;
    napi_ref onRecvNewMessages;
    napi_ref onRecvOfflineNewMessages;

    napi_ref onSyncStart;
    napi_ref onSyncFinish;
    napi_ref onSyncProgress;
    napi_ref onSyncFailed;
    napi_ref onConvChanged;
    napi_ref onNewConv;
    napi_ref onUnreadChanged;
    napi_ref onInputStatus;

    napi_ref onJoinedAdd;
    napi_ref onJoinedDel;
    napi_ref onMemberAdd;
    napi_ref onMemberDel;
    napi_ref onAppAdd;
    napi_ref onAppDel;
    napi_ref onInfoChanged;
    napi_ref onDismissed;
    napi_ref onMemberInfo;
    napi_ref onAppAccept;
    napi_ref onAppReject;

    napi_ref onFriendAppAdd;
    napi_ref onFriendAppDel;
    napi_ref onFriendAppAccept;
    napi_ref onFriendAppReject;
    napi_ref onFriendAdd;
    napi_ref onFriendDel;
    napi_ref onFriendInfo;
    napi_ref onBlackAdd;
    napi_ref onBlackDel;

    napi_ref onSelfInfo;
    napi_ref onUserStatus;
    napi_ref onUserCommandAdd;
    napi_ref onUserCommandDelete;
    napi_ref onUserCommandUpdate;

    napi_ref onReceiveNewInvitation;
    napi_ref onInviteeAccepted;
    napi_ref onInviteeAcceptedByOtherDevice;
    napi_ref onInviteeRejected;
    napi_ref onInviteeRejectedByOtherDevice;
    napi_ref onInvitationCancelled;
    napi_ref onInvitationTimeout;
    napi_ref onHangUp;
    napi_ref onRoomParticipantConnected;
    napi_ref onRoomParticipantDisconnected;

    napi_ref onRecvCustomBusinessMessage;
    napi_ref onMessageKvInfoChanged;

    napi_env env;
    bool isValid;
} g_listeners = {0};

static std::mutex g_callback_mutex;
static bool g_callback_ids[CB_MAX] = {false};

namespace {
enum class JsArgType { Int32, Int64, String, Boolean };
enum class CleanupType { None, Base, SendMessage, Upload, UploadLog };

struct JsArg {
    JsArgType type;
    int64_t number = 0;
    std::string text;

    static JsArg Int(int value) { return {JsArgType::Int32, value, {}}; }
    static JsArg Long(long long value) { return {JsArgType::Int64, value, {}}; }
    static JsArg String(const char* value) { return {JsArgType::String, 0, value ? value : ""}; }
    static JsArg Bool(bool value) { return {JsArgType::Boolean, value ? 1 : 0, {}}; }
};

struct CallbackEvent {
    napi_ref callback = nullptr;
    std::vector<JsArg> args;
    CleanupType cleanup = CleanupType::None;
    int callbackId = INVALID_CALLBACK_ID;
};

static napi_threadsafe_function g_callbackDispatcher = nullptr;

static bool CreateFunctionReference(napi_env env, napi_value value, napi_ref* reference) {
    napi_valuetype type = napi_undefined;
    if (!value || napi_typeof(env, value, &type) != napi_ok || type != napi_function) {
        napi_throw_type_error(env, nullptr, "OpenIM callback must be a function");
        return false;
    }
    if (napi_create_reference(env, value, 1, reference) != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to retain OpenIM callback");
        return false;
    }
    return true;
}

static void DeleteReference(napi_env env, napi_ref& reference) {
    if (!reference) return;
    napi_delete_reference(env, reference);
    reference = nullptr;
}

static void ShutdownCallbackDispatcher(void*) {
    DeleteAllCallbacks();
    if (g_callbackDispatcher) {
        napi_release_threadsafe_function(g_callbackDispatcher, napi_tsfn_abort);
        g_callbackDispatcher = nullptr;
    }
}

static void CleanupAfterCallback(const CallbackEvent& event) {
    switch (event.cleanup) {
        case CleanupType::Base:
            DeleteBaseCallback(event.callbackId);
            break;
        case CleanupType::SendMessage:
            DeleteSendMsgCallback(event.callbackId);
            break;
        case CleanupType::Upload:
            DeleteUploadCallbacks(event.callbackId);
            break;
        case CleanupType::UploadLog:
            DeleteUploadLogCallback(event.callbackId);
            break;
        case CleanupType::None:
            break;
    }
}

static void DispatchOnJsThread(napi_env env, napi_value, void*, void* data) {
    std::unique_ptr<CallbackEvent> event(static_cast<CallbackEvent*>(data));
    if (!env || !event || !event->callback) return;

    napi_value callback = nullptr;
    if (napi_get_reference_value(env, event->callback, &callback) != napi_ok || !callback) {
        CleanupAfterCallback(*event);
        return;
    }

    std::vector<napi_value> argv(event->args.size());
    for (size_t i = 0; i < event->args.size(); ++i) {
        const auto& arg = event->args[i];
        switch (arg.type) {
            case JsArgType::Int32:
                napi_create_int32(env, static_cast<int32_t>(arg.number), &argv[i]);
                break;
            case JsArgType::Int64:
                napi_create_int64(env, arg.number, &argv[i]);
                break;
            case JsArgType::String:
                napi_create_string_utf8(env, arg.text.c_str(), arg.text.size(), &argv[i]);
                break;
            case JsArgType::Boolean:
                napi_get_boolean(env, arg.number != 0, &argv[i]);
                break;
        }
    }

    napi_value receiver = nullptr;
    napi_get_undefined(env, &receiver);
    napi_value result = nullptr;
    napi_call_function(env, receiver, callback, argv.size(), argv.empty() ? nullptr : argv.data(), &result);
    CleanupAfterCallback(*event);
}

static void QueueCallback(napi_ref callback, std::initializer_list<JsArg> args = {},
                          CleanupType cleanup = CleanupType::None, int callbackId = INVALID_CALLBACK_ID) {
    if (!callback || !g_callbackDispatcher) return;
    auto* event = new CallbackEvent{callback, std::vector<JsArg>(args), cleanup, callbackId};
    if (napi_call_threadsafe_function(g_callbackDispatcher, event, napi_tsfn_nonblocking) != napi_ok) {
        delete event;
    }
}
} // namespace

bool InitializeCallbackDispatcher(napi_env env) {
    if (g_callbackDispatcher) return true;
    napi_value name = nullptr;
    napi_create_string_utf8(env, "OpenIMCallbackDispatcher", NAPI_AUTO_LENGTH, &name);
    const napi_status status = napi_create_threadsafe_function(
        env, nullptr, nullptr, name, 0, 1, nullptr, nullptr, nullptr,
        DispatchOnJsThread, &g_callbackDispatcher);
    if (status != napi_ok) return false;
    napi_add_env_cleanup_hook(env, ShutdownCallbackDispatcher, nullptr);
    return true;
}

napi_value BindCallbackFunction(napi_env env, napi_value receiver, napi_value callback) {
    if (!receiver || !callback) return nullptr;
    napi_value bind = nullptr;
    napi_value bound = nullptr;
    if (napi_get_named_property(env, callback, "bind", &bind) != napi_ok || !bind) return nullptr;
    if (napi_call_function(env, callback, bind, 1, &receiver, &bound) != napi_ok) return nullptr;
    return bound;
}

// ============================================================
// 工具函数实现
// ============================================================

int AllocateCallbackId() {
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    for (int i = 1; i < CB_MAX; i++) {
        if (!g_callback_ids[i]) {
            g_callback_ids[i] = true;
            return i;
        }
    }
    return INVALID_CALLBACK_ID;
}

void FreeCallbackId(int cbId) {
    if (cbId <= 0 || cbId >= CB_MAX) return;
    std::lock_guard<std::mutex> lock(g_callback_mutex);
    g_callback_ids[cbId] = false;
}

// ============================================================
// Base 回调实现
// ============================================================

int StoreBaseCallback(napi_env env, napi_value onSuccess, napi_value onError) {
    int cbId = AllocateCallbackId();
    if (cbId < 0) {
        napi_throw_error(env, nullptr, "OpenIM callback capacity exhausted");
        return INVALID_CALLBACK_ID;
    }

    auto& ctx = g_baseCallbacks[cbId];
    ctx.env = env;
    if (!CreateFunctionReference(env, onSuccess, &ctx.onSuccessRef) ||
        !CreateFunctionReference(env, onError, &ctx.onErrorRef)) {
        DeleteReference(env, ctx.onSuccessRef);
        DeleteReference(env, ctx.onErrorRef);
        FreeCallbackId(cbId);
        return INVALID_CALLBACK_ID;
    }

    RegisterBaseCallback(cbId, CallbackAddress(CAPI_OnBaseSuccess), CallbackAddress(CAPI_OnBaseError));
    ctx.isValid = true;

    return cbId;
}

int StoreBaseCallback(napi_env env, napi_value callback) {
    napi_value onSuccess, onError;
    napi_get_named_property(env, callback, "onSuccess", &onSuccess);
    napi_get_named_property(env, callback, "onError", &onError);
    return StoreBaseCallback(env,
        BindCallbackFunction(env, callback, onSuccess),
        BindCallbackFunction(env, callback, onError));
}

BaseCallbackContext* GetBaseCallback(int cbId) {
    if (cbId <= 0 || cbId >= CB_MAX) return nullptr;
    if (!g_baseCallbacks[cbId].isValid) return nullptr;
    return &g_baseCallbacks[cbId];
}

void DeleteBaseCallback(int cbId) {
    if (cbId <= 0 || cbId >= CB_MAX) return;
    if (!g_baseCallbacks[cbId].isValid) return;

    UnregisterBaseCallback(cbId);

    if (g_baseCallbacks[cbId].onSuccessRef) {
        napi_delete_reference(g_baseCallbacks[cbId].env, g_baseCallbacks[cbId].onSuccessRef);
    }
    if (g_baseCallbacks[cbId].onErrorRef) {
        napi_delete_reference(g_baseCallbacks[cbId].env, g_baseCallbacks[cbId].onErrorRef);
    }

    g_baseCallbacks[cbId].isValid = false;
    FreeCallbackId(cbId);
}

// ============================================================
// 上传文件回调实现
// ============================================================

int StoreUploadCallbacks(
    napi_env env,
    napi_value onOpen,
    napi_value onPartSize,
    napi_value onHashPartProgress,
    napi_value onHashPartComplete,
    napi_value onUploadID,
    napi_value onUploadPartComplete,
    napi_value onUploadComplete,
    napi_value onComplete
) {
    int cbId = AllocateCallbackId();
    if (cbId < 0) {
        napi_throw_error(env, nullptr, "OpenIM callback capacity exhausted");
        return INVALID_CALLBACK_ID;
    }

    auto& ctx = g_upload_callbacks[cbId];
    ctx.env = env;
    if (!CreateFunctionReference(env, onOpen, &ctx.onOpenRef) ||
        !CreateFunctionReference(env, onPartSize, &ctx.onPartSizeRef) ||
        !CreateFunctionReference(env, onHashPartProgress, &ctx.onHashPartProgressRef) ||
        !CreateFunctionReference(env, onHashPartComplete, &ctx.onHashPartCompleteRef) ||
        !CreateFunctionReference(env, onUploadID, &ctx.onUploadIDRef) ||
        !CreateFunctionReference(env, onUploadPartComplete, &ctx.onUploadPartCompleteRef) ||
        !CreateFunctionReference(env, onUploadComplete, &ctx.onUploadCompleteRef) ||
        !CreateFunctionReference(env, onComplete, &ctx.onCompleteRef)) {
        DeleteReference(env, ctx.onOpenRef);
        DeleteReference(env, ctx.onPartSizeRef);
        DeleteReference(env, ctx.onHashPartProgressRef);
        DeleteReference(env, ctx.onHashPartCompleteRef);
        DeleteReference(env, ctx.onUploadIDRef);
        DeleteReference(env, ctx.onUploadPartCompleteRef);
        DeleteReference(env, ctx.onUploadCompleteRef);
        DeleteReference(env, ctx.onCompleteRef);
        FreeCallbackId(cbId);
        return INVALID_CALLBACK_ID;
    }

    RegisterUploadFileCallback(
        cbId,
        CallbackAddress(CAPI_OnUploadOpen),
        CallbackAddress(CAPI_OnUploadPartSize),
        CallbackAddress(CAPI_OnUploadHashProgress),
        CallbackAddress(CAPI_OnUploadHashComplete),
        CallbackAddress(CAPI_OnUploadID),
        CallbackAddress(CAPI_OnUploadPartComplete),
        CallbackAddress(CAPI_OnUploadComplete),
        CallbackAddress(CAPI_OnUploadFinish));
    ctx.isValid = true;

    return cbId;
}

UploadCallbackContext* GetUploadCallback(int cbId) {
    if (cbId <= 0 || cbId >= CB_MAX) return nullptr;
    if (!g_upload_callbacks[cbId].isValid) return nullptr;
    return &g_upload_callbacks[cbId];
}

void DeleteUploadCallbacks(int cbId) {
    if (cbId <= 0 || cbId >= CB_MAX) return;
    auto& ctx = g_upload_callbacks[cbId];
    if (!ctx.isValid) return;

    UnregisterUploadFileCallback(cbId);

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(ctx.env, ref); ref = nullptr; }
    DELETE_REF(ctx.onOpenRef);
    DELETE_REF(ctx.onPartSizeRef);
    DELETE_REF(ctx.onHashPartProgressRef);
    DELETE_REF(ctx.onHashPartCompleteRef);
    DELETE_REF(ctx.onUploadIDRef);
    DELETE_REF(ctx.onUploadPartCompleteRef);
    DELETE_REF(ctx.onUploadCompleteRef);
    DELETE_REF(ctx.onCompleteRef);
    #undef DELETE_REF

    ctx.isValid = false;
    FreeCallbackId(cbId);
}

// ============================================================
// 日志上传回调实现
// ============================================================

int StoreUploadLogCallback(napi_env env, napi_value onProgress) {
    int cbId = AllocateCallbackId();
    if (cbId < 0) {
        napi_throw_error(env, nullptr, "OpenIM callback capacity exhausted");
        return INVALID_CALLBACK_ID;
    }

    auto& ctx = g_uploadLog_callbacks[cbId];
    ctx.env = env;
    if (!CreateFunctionReference(env, onProgress, &ctx.onProgressRef)) {
        FreeCallbackId(cbId);
        return INVALID_CALLBACK_ID;
    }

    RegisterUploadLogProgress(cbId, CallbackAddress(CAPI_OnUploadLogProgress));
    ctx.isValid = true;

    return cbId;
}

UploadLogCallbackContext* GetUploadLogCallback(int cbId) {
    if (cbId <= 0 || cbId >= CB_MAX) return nullptr;
    if (!g_uploadLog_callbacks[cbId].isValid) return nullptr;
    return &g_uploadLog_callbacks[cbId];
}

void DeleteUploadLogCallback(int cbId) {
    if (cbId <= 0 || cbId >= CB_MAX) return;
    auto& ctx = g_uploadLog_callbacks[cbId];
    if (!ctx.isValid) return;

    UnregisterUploadLogProgress(cbId);

    if (ctx.onProgressRef) {
        napi_delete_reference(ctx.env, ctx.onProgressRef);
        ctx.onProgressRef = nullptr;
    }

    ctx.isValid = false;
    FreeCallbackId(cbId);
}

// ============================================================
// 发送消息回调实现（包含 Base + OnProgress）
// ============================================================

int StoreSendMsgCallback(napi_env env, napi_value onSuccess, napi_value onError, napi_value onProgress) {
    int cbId = AllocateCallbackId();
    if (cbId < 0) {
        napi_throw_error(env, nullptr, "OpenIM callback capacity exhausted");
        return INVALID_CALLBACK_ID;
    }

    auto& ctx = g_sendMsg_callbacks[cbId];
    ctx.env = env;
    if (!CreateFunctionReference(env, onSuccess, &ctx.onSuccessRef) ||
        !CreateFunctionReference(env, onError, &ctx.onErrorRef) ||
        !CreateFunctionReference(env, onProgress, &ctx.onProgressRef)) {
        DeleteReference(env, ctx.onSuccessRef);
        DeleteReference(env, ctx.onErrorRef);
        DeleteReference(env, ctx.onProgressRef);
        FreeCallbackId(cbId);
        return INVALID_CALLBACK_ID;
    }

    RegisterBaseCallback(cbId, CallbackAddress(CAPI_OnBaseSuccess), CallbackAddress(CAPI_OnBaseError));
    RegisterSendMsgCallback(cbId, CallbackAddress(CAPI_OnSendMsg));
    ctx.isValid = true;

    return cbId;
}

// 重载：从对象中提取 onSuccess/onError/onProgress
int StoreSendMsgCallback(napi_env env, napi_value callback) {
    napi_value onSuccess, onError, onProgress;
    napi_get_named_property(env, callback, "onSuccess", &onSuccess);
    napi_get_named_property(env, callback, "onError", &onError);
    napi_get_named_property(env, callback, "onProgress", &onProgress);
    return StoreSendMsgCallback(env,
        BindCallbackFunction(env, callback, onSuccess),
        BindCallbackFunction(env, callback, onError),
        BindCallbackFunction(env, callback, onProgress));
}

SendMsgCallbackContext* GetSendMsgCallback(int cbId) {
    if (cbId <= 0 || cbId >= CB_MAX) return nullptr;
    if (!g_sendMsg_callbacks[cbId].isValid) return nullptr;
    return &g_sendMsg_callbacks[cbId];
}

void DeleteSendMsgCallback(int cbId) {
    if (cbId <= 0 || cbId >= CB_MAX) return;
    auto& ctx = g_sendMsg_callbacks[cbId];
    if (!ctx.isValid) return;

    UnregisterSendMsgCallback(cbId);
    UnregisterBaseCallback(cbId);

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(ctx.env, ref); ref = nullptr; }
    DELETE_REF(ctx.onSuccessRef);
    DELETE_REF(ctx.onErrorRef);
    DELETE_REF(ctx.onProgressRef);
    #undef DELETE_REF

    ctx.isValid = false;
    FreeCallbackId(cbId);
}

// ============================================================
// 连接监听器实现
// ============================================================

int StoreConnListener(
    napi_env env,
    napi_value onConnecting,
    napi_value onConnectSuccess,
    napi_value onConnectFailed,
    napi_value onKickedOffline,
    napi_value onUserTokenExpired,
    napi_value onUserTokenInvalid
) {
    DeleteConnListener();
    napi_create_reference(env, onConnecting, 1, &g_listeners.onConnecting);
    napi_create_reference(env, onConnectSuccess, 1, &g_listeners.onConnectSuccess);
    napi_create_reference(env, onConnectFailed, 1, &g_listeners.onConnectFailed);
    napi_create_reference(env, onKickedOffline, 1, &g_listeners.onKickedOffline);
    napi_create_reference(env, onUserTokenExpired, 1, &g_listeners.onUserTokenExpired);
    napi_create_reference(env, onUserTokenInvalid, 1, &g_listeners.onUserTokenInvalid);
    g_listeners.env = env;
    g_listeners.isValid = true;

    // Register with SDK
    RegisterConnListener(
        CallbackAddress(CAPI_OnConnConnecting),
        CallbackAddress(CAPI_OnConnConnectSuccess),
        CallbackAddress(CAPI_OnConnConnectFailed),
        CallbackAddress(CAPI_OnConnKickedOffline),
        CallbackAddress(CAPI_OnConnUserTokenExpired),
        CallbackAddress(CAPI_OnConnUserTokenInvalid));

    return 0;
}

void DeleteConnListener() {
    UnregisterConnListener();

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(g_listeners.env, ref); ref = nullptr; }
    DELETE_REF(g_listeners.onConnecting);
    DELETE_REF(g_listeners.onConnectSuccess);
    DELETE_REF(g_listeners.onConnectFailed);
    DELETE_REF(g_listeners.onKickedOffline);
    DELETE_REF(g_listeners.onUserTokenExpired);
    DELETE_REF(g_listeners.onUserTokenInvalid);
    #undef DELETE_REF

}

// ============================================================
// 消息监听器实现
// ============================================================

int StoreMsgListener(
    napi_env env,
    napi_value onRecvNewMsg,
    napi_value onRecvReceipt,
    napi_value onMsgRevoked,
    napi_value onRecvOffline,
    napi_value onMsgDeleted,
    napi_value onRecvOnline
) {
    DeleteMsgListener();
    napi_create_reference(env, onRecvNewMsg, 1, &g_listeners.onRecvNewMsg);
    napi_create_reference(env, onRecvReceipt, 1, &g_listeners.onRecvReceipt);
    napi_create_reference(env, onMsgRevoked, 1, &g_listeners.onMsgRevoked);
    napi_create_reference(env, onRecvOffline, 1, &g_listeners.onRecvOffline);
    napi_create_reference(env, onMsgDeleted, 1, &g_listeners.onMsgDeleted);
    napi_create_reference(env, onRecvOnline, 1, &g_listeners.onRecvOnline);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterMsgListener(
        CallbackAddress(CAPI_OnRecvNewMsg),
        CallbackAddress(CAPI_OnRecvReceipt),
        CallbackAddress(CAPI_OnMsgRevoked),
        CallbackAddress(CAPI_OnRecvOffline),
        CallbackAddress(CAPI_OnMsgDeleted),
        CallbackAddress(CAPI_OnRecvOnline));

    return 0;
}

void DeleteMsgListener() {
    UnregisterMsgListener();

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(g_listeners.env, ref); ref = nullptr; }
    DELETE_REF(g_listeners.onRecvNewMsg);
    DELETE_REF(g_listeners.onRecvReceipt);
    DELETE_REF(g_listeners.onMsgRevoked);
    DELETE_REF(g_listeners.onRecvOffline);
    DELETE_REF(g_listeners.onMsgDeleted);
    DELETE_REF(g_listeners.onRecvOnline);
    #undef DELETE_REF
}

int StoreBatchMsgListener(napi_env env, napi_value onRecvNewMessages, napi_value onRecvOfflineNewMessages) {
    DeleteBatchMsgListener();
    napi_create_reference(env, onRecvNewMessages, 1, &g_listeners.onRecvNewMessages);
    napi_create_reference(env, onRecvOfflineNewMessages, 1, &g_listeners.onRecvOfflineNewMessages);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterBatchMsgListener(CallbackAddress(CAPI_OnRecvNewMessages),
                             CallbackAddress(CAPI_OnRecvOfflineNewMessages));
    return 0;
}

void DeleteBatchMsgListener() {
    UnregisterBatchMsgListener();

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(g_listeners.env, ref); ref = nullptr; }
    DELETE_REF(g_listeners.onRecvNewMessages);
    DELETE_REF(g_listeners.onRecvOfflineNewMessages);
    #undef DELETE_REF
}

// ============================================================
// 会话监听器实现
// ============================================================

int StoreConvListener(
    napi_env env,
    napi_value onSyncStart,
    napi_value onSyncFinish,
    napi_value onSyncProgress,
    napi_value onSyncFailed,
    napi_value onConvChanged,
    napi_value onNewConv,
    napi_value onUnreadChanged,
    napi_value onInputStatus
) {
    DeleteConvListener();
    napi_create_reference(env, onSyncStart, 1, &g_listeners.onSyncStart);
    napi_create_reference(env, onSyncFinish, 1, &g_listeners.onSyncFinish);
    napi_create_reference(env, onSyncProgress, 1, &g_listeners.onSyncProgress);
    napi_create_reference(env, onSyncFailed, 1, &g_listeners.onSyncFailed);
    napi_create_reference(env, onConvChanged, 1, &g_listeners.onConvChanged);
    napi_create_reference(env, onNewConv, 1, &g_listeners.onNewConv);
    napi_create_reference(env, onUnreadChanged, 1, &g_listeners.onUnreadChanged);
    napi_create_reference(env, onInputStatus, 1, &g_listeners.onInputStatus);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterConvListener(
        CallbackAddress(CAPI_OnConvSyncStart),
        CallbackAddress(CAPI_OnConvSyncFinish),
        CallbackAddress(CAPI_OnConvSyncProgress),
        CallbackAddress(CAPI_OnConvSyncFailed),
        CallbackAddress(CAPI_OnConvChanged),
        CallbackAddress(CAPI_OnNewConv),
        CallbackAddress(CAPI_OnUnreadChanged),
        CallbackAddress(CAPI_OnInputStatus));

    return 0;
}

void DeleteConvListener() {
    UnregisterConvListener();

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(g_listeners.env, ref); ref = nullptr; }
    DELETE_REF(g_listeners.onSyncStart);
    DELETE_REF(g_listeners.onSyncFinish);
    DELETE_REF(g_listeners.onSyncProgress);
    DELETE_REF(g_listeners.onSyncFailed);
    DELETE_REF(g_listeners.onConvChanged);
    DELETE_REF(g_listeners.onNewConv);
    DELETE_REF(g_listeners.onUnreadChanged);
    DELETE_REF(g_listeners.onInputStatus);
    #undef DELETE_REF
}

// ============================================================
// 群组监听器实现
// ============================================================

int StoreGroupListener(
    napi_env env,
    napi_value onJoinedAdd,
    napi_value onJoinedDel,
    napi_value onMemberAdd,
    napi_value onMemberDel,
    napi_value onAppAdd,
    napi_value onAppDel,
    napi_value onInfoChanged,
    napi_value onDismissed,
    napi_value onMemberInfo,
    napi_value onAppAccept,
    napi_value onAppReject
) {
    DeleteGroupListener();
    napi_create_reference(env, onJoinedAdd, 1, &g_listeners.onJoinedAdd);
    napi_create_reference(env, onJoinedDel, 1, &g_listeners.onJoinedDel);
    napi_create_reference(env, onMemberAdd, 1, &g_listeners.onMemberAdd);
    napi_create_reference(env, onMemberDel, 1, &g_listeners.onMemberDel);
    napi_create_reference(env, onAppAdd, 1, &g_listeners.onAppAdd);
    napi_create_reference(env, onAppDel, 1, &g_listeners.onAppDel);
    napi_create_reference(env, onInfoChanged, 1, &g_listeners.onInfoChanged);
    napi_create_reference(env, onDismissed, 1, &g_listeners.onDismissed);
    napi_create_reference(env, onMemberInfo, 1, &g_listeners.onMemberInfo);
    napi_create_reference(env, onAppAccept, 1, &g_listeners.onAppAccept);
    napi_create_reference(env, onAppReject, 1, &g_listeners.onAppReject);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterGroupListener(
        CallbackAddress(CAPI_OnGroupJoinedAdd),
        CallbackAddress(CAPI_OnGroupJoinedDel),
        CallbackAddress(CAPI_OnGroupMemberAdd),
        CallbackAddress(CAPI_OnGroupMemberDel),
        CallbackAddress(CAPI_OnGroupAppAdd),
        CallbackAddress(CAPI_OnGroupAppDel),
        CallbackAddress(CAPI_OnGroupInfoChanged),
        CallbackAddress(CAPI_OnGroupDismissed),
        CallbackAddress(CAPI_OnGroupMemberInfo),
        CallbackAddress(CAPI_OnGroupAppAccept),
        CallbackAddress(CAPI_OnGroupAppReject));

    return 0;
}

void DeleteGroupListener() {
    UnregisterGroupListener();

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(g_listeners.env, ref); ref = nullptr; }
    DELETE_REF(g_listeners.onJoinedAdd);
    DELETE_REF(g_listeners.onJoinedDel);
    DELETE_REF(g_listeners.onMemberAdd);
    DELETE_REF(g_listeners.onMemberDel);
    DELETE_REF(g_listeners.onAppAdd);
    DELETE_REF(g_listeners.onAppDel);
    DELETE_REF(g_listeners.onInfoChanged);
    DELETE_REF(g_listeners.onDismissed);
    DELETE_REF(g_listeners.onMemberInfo);
    DELETE_REF(g_listeners.onAppAccept);
    DELETE_REF(g_listeners.onAppReject);
    #undef DELETE_REF
}

// ============================================================
// 好友监听器实现
// ============================================================

int StoreFriendListener(
    napi_env env,
    napi_value onAppAdd,
    napi_value onAppDel,
    napi_value onAppAccept,
    napi_value onAppReject,
    napi_value onFriendAdd,
    napi_value onFriendDel,
    napi_value onFriendInfo,
    napi_value onBlackAdd,
    napi_value onBlackDel
) {
    DeleteFriendListener();
    napi_create_reference(env, onAppAdd, 1, &g_listeners.onFriendAppAdd);
    napi_create_reference(env, onAppDel, 1, &g_listeners.onFriendAppDel);
    napi_create_reference(env, onAppAccept, 1, &g_listeners.onFriendAppAccept);
    napi_create_reference(env, onAppReject, 1, &g_listeners.onFriendAppReject);
    napi_create_reference(env, onFriendAdd, 1, &g_listeners.onFriendAdd);
    napi_create_reference(env, onFriendDel, 1, &g_listeners.onFriendDel);
    napi_create_reference(env, onFriendInfo, 1, &g_listeners.onFriendInfo);
    napi_create_reference(env, onBlackAdd, 1, &g_listeners.onBlackAdd);
    napi_create_reference(env, onBlackDel, 1, &g_listeners.onBlackDel);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterFriendListener(
        CallbackAddress(CAPI_OnFriendAppAdd),
        CallbackAddress(CAPI_OnFriendAppDel),
        CallbackAddress(CAPI_OnFriendAppAccept),
        CallbackAddress(CAPI_OnFriendAppReject),
        CallbackAddress(CAPI_OnFriendAdd),
        CallbackAddress(CAPI_OnFriendDel),
        CallbackAddress(CAPI_OnFriendInfo),
        CallbackAddress(CAPI_OnBlackAdd),
        CallbackAddress(CAPI_OnBlackDel));

    return 0;
}

void DeleteFriendListener() {
    UnregisterFriendListener();

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(g_listeners.env, ref); ref = nullptr; }
    DELETE_REF(g_listeners.onFriendAppAdd);
    DELETE_REF(g_listeners.onFriendAppDel);
    DELETE_REF(g_listeners.onFriendAppAccept);
    DELETE_REF(g_listeners.onFriendAppReject);
    DELETE_REF(g_listeners.onFriendAdd);
    DELETE_REF(g_listeners.onFriendDel);
    DELETE_REF(g_listeners.onFriendInfo);
    DELETE_REF(g_listeners.onBlackAdd);
    DELETE_REF(g_listeners.onBlackDel);
    #undef DELETE_REF
}

// ============================================================
// 用户监听器实现
// ============================================================

int StoreUserListener(napi_env env, napi_value onSelfInfo, napi_value onUserStatus,
                      napi_value onUserCommandAdd, napi_value onUserCommandDelete,
                      napi_value onUserCommandUpdate) {
    DeleteUserListener();
    napi_create_reference(env, onSelfInfo, 1, &g_listeners.onSelfInfo);
    napi_create_reference(env, onUserStatus, 1, &g_listeners.onUserStatus);
    napi_create_reference(env, onUserCommandAdd, 1, &g_listeners.onUserCommandAdd);
    napi_create_reference(env, onUserCommandDelete, 1, &g_listeners.onUserCommandDelete);
    napi_create_reference(env, onUserCommandUpdate, 1, &g_listeners.onUserCommandUpdate);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterUserListener(CallbackAddress(CAPI_OnUserSelfInfoUpdated),
                         CallbackAddress(CAPI_OnUserStatusChanged),
                         CallbackAddress(CAPI_OnUserCommandAdd),
                         CallbackAddress(CAPI_OnUserCommandDelete),
                         CallbackAddress(CAPI_OnUserCommandUpdate));

    return 0;
}

void DeleteUserListener() {
    UnregisterUserListener();

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(g_listeners.env, ref); ref = nullptr; }
    DELETE_REF(g_listeners.onSelfInfo);
    DELETE_REF(g_listeners.onUserStatus);
    DELETE_REF(g_listeners.onUserCommandAdd);
    DELETE_REF(g_listeners.onUserCommandDelete);
    DELETE_REF(g_listeners.onUserCommandUpdate);
    #undef DELETE_REF
}

// ============================================================
// 信令监听器实现
// ============================================================

int StoreSignalingListener(
    napi_env env,
    napi_value onReceiveNewInvitation,
    napi_value onInviteeAccepted,
    napi_value onInviteeAcceptedByOtherDevice,
    napi_value onInviteeRejected,
    napi_value onInviteeRejectedByOtherDevice,
    napi_value onInvitationCancelled,
    napi_value onInvitationTimeout,
    napi_value onHangUp,
    napi_value onRoomParticipantConnected,
    napi_value onRoomParticipantDisconnected
) {
    DeleteSignalingListener();
    napi_create_reference(env, onReceiveNewInvitation, 1, &g_listeners.onReceiveNewInvitation);
    napi_create_reference(env, onInviteeAccepted, 1, &g_listeners.onInviteeAccepted);
    napi_create_reference(env, onInviteeAcceptedByOtherDevice, 1, &g_listeners.onInviteeAcceptedByOtherDevice);
    napi_create_reference(env, onInviteeRejected, 1, &g_listeners.onInviteeRejected);
    napi_create_reference(env, onInviteeRejectedByOtherDevice, 1, &g_listeners.onInviteeRejectedByOtherDevice);
    napi_create_reference(env, onInvitationCancelled, 1, &g_listeners.onInvitationCancelled);
    napi_create_reference(env, onInvitationTimeout, 1, &g_listeners.onInvitationTimeout);
    napi_create_reference(env, onHangUp, 1, &g_listeners.onHangUp);
    napi_create_reference(env, onRoomParticipantConnected, 1, &g_listeners.onRoomParticipantConnected);
    napi_create_reference(env, onRoomParticipantDisconnected, 1, &g_listeners.onRoomParticipantDisconnected);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterSignalingListener(
        CallbackAddress(CAPI_OnSignalingReceiveNewInvitation),
        CallbackAddress(CAPI_OnSignalingInviteeAccepted),
        CallbackAddress(CAPI_OnSignalingInviteeAcceptedByOtherDevice),
        CallbackAddress(CAPI_OnSignalingInviteeRejected),
        CallbackAddress(CAPI_OnSignalingInviteeRejectedByOtherDevice),
        CallbackAddress(CAPI_OnSignalingInvitationCancelled),
        CallbackAddress(CAPI_OnSignalingInvitationTimeout),
        CallbackAddress(CAPI_OnSignalingHangUp),
        CallbackAddress(CAPI_OnSignalingRoomParticipantConnected),
        CallbackAddress(CAPI_OnSignalingRoomParticipantDisconnected));

    return 0;
}

void DeleteSignalingListener() {
    UnregisterSignalingListener();

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(g_listeners.env, ref); ref = nullptr; }
    DELETE_REF(g_listeners.onReceiveNewInvitation);
    DELETE_REF(g_listeners.onInviteeAccepted);
    DELETE_REF(g_listeners.onInviteeAcceptedByOtherDevice);
    DELETE_REF(g_listeners.onInviteeRejected);
    DELETE_REF(g_listeners.onInviteeRejectedByOtherDevice);
    DELETE_REF(g_listeners.onInvitationCancelled);
    DELETE_REF(g_listeners.onInvitationTimeout);
    DELETE_REF(g_listeners.onHangUp);
    DELETE_REF(g_listeners.onRoomParticipantConnected);
    DELETE_REF(g_listeners.onRoomParticipantDisconnected);
    #undef DELETE_REF
}

// ============================================================
// 自定义业务监听器实现
// ============================================================

int StoreCustomBusinessListener(napi_env env, napi_value onRecvCustomBusinessMessage) {
    DeleteCustomBusinessListener();
    napi_create_reference(env, onRecvCustomBusinessMessage, 1, &g_listeners.onRecvCustomBusinessMessage);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterCustomBusinessListener(CallbackAddress(CAPI_OnRecvCustomBusinessMessage));

    return 0;
}

void DeleteCustomBusinessListener() {
    UnregisterCustomBusinessListener();

    if (g_listeners.onRecvCustomBusinessMessage) {
        napi_delete_reference(g_listeners.env, g_listeners.onRecvCustomBusinessMessage);
        g_listeners.onRecvCustomBusinessMessage = nullptr;
    }
}

// ============================================================
// 消息 KV 信息监听器实现
// ============================================================

int StoreMsgKvInfoListener(napi_env env, napi_value onMessageKvInfoChanged) {
    DeleteMsgKvInfoListener();
    napi_create_reference(env, onMessageKvInfoChanged, 1, &g_listeners.onMessageKvInfoChanged);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterMsgKvInfoListener(CallbackAddress(CAPI_OnMessageKvInfoChanged));

    return 0;
}

void DeleteMsgKvInfoListener() {
    UnregisterMsgKvInfoListener();

    if (g_listeners.onMessageKvInfoChanged) {
        napi_delete_reference(g_listeners.env, g_listeners.onMessageKvInfoChanged);
        g_listeners.onMessageKvInfoChanged = nullptr;
    }
}

// ============================================================
// 清理所有回调
// ============================================================

void DeleteAllCallbacks() {
    // 清理所有 Base 回调
    for (int i = 1; i < CB_MAX; i++) {
        if (g_baseCallbacks[i].isValid) {
            DeleteBaseCallback(i);
        }
        if (g_upload_callbacks[i].isValid) {
            DeleteUploadCallbacks(i);
        }
        if (g_uploadLog_callbacks[i].isValid) {
            DeleteUploadLogCallback(i);
        }
        if (g_sendMsg_callbacks[i].isValid) {
            DeleteSendMsgCallback(i);
        }
    }

    // 清理所有 Listener
    DeleteConnListener();
    DeleteMsgListener();
    DeleteBatchMsgListener();
    DeleteConvListener();
    DeleteGroupListener();
    DeleteFriendListener();
    DeleteUserListener();
    DeleteSignalingListener();
    DeleteCustomBusinessListener();
    DeleteMsgKvInfoListener();
}

// ============================================================
// JavaScript 回调调用辅助函数实现
// ============================================================

void CallVoidCallback(napi_env env, napi_ref callbackRef) {
    (void)env;
    QueueCallback(callbackRef);
}

void CallIntCallback(napi_env env, napi_ref callbackRef, int value) {
    (void)env;
    QueueCallback(callbackRef, {JsArg::Int(value)});
}

void CallBoolCallback(napi_env env, napi_ref callbackRef, bool value) {
    (void)env;
    QueueCallback(callbackRef, {JsArg::Bool(value)});
}

void CallIntStringCallback(napi_env env, napi_ref callbackRef, int value, char* text) {
    (void)env;
    QueueCallback(callbackRef, {JsArg::Int(value), JsArg::String(text)});
    FreeString(text);
}

void CallLongLongCallback(napi_env env, napi_ref callbackRef, long long value) {
    (void)env;
    QueueCallback(callbackRef, {JsArg::Long(value)});
}

void CallStringCallback(napi_env env, napi_ref callbackRef, char* value) {
    (void)env;
    QueueCallback(callbackRef, {JsArg::String(value)});
    FreeString(value);
}

void CallBaseSuccessCallback(int cbId, const char* data) {
    napi_ref callbackRef = nullptr;
    const bool isSendMessage = cbId > 0 && cbId < CB_MAX && g_sendMsg_callbacks[cbId].isValid;
    if (isSendMessage) {
        callbackRef = g_sendMsg_callbacks[cbId].onSuccessRef;
    } else if (auto* ctx = GetBaseCallback(cbId)) {
        callbackRef = ctx->onSuccessRef;
    }
    QueueCallback(callbackRef, {JsArg::String(data)},
                  isSendMessage ? CleanupType::SendMessage : CleanupType::Base, cbId);
}

void CallBaseErrorCallback(int cbId, int code, const char* message) {
    napi_ref callbackRef = nullptr;
    const bool isSendMessage = cbId > 0 && cbId < CB_MAX && g_sendMsg_callbacks[cbId].isValid;
    if (isSendMessage) {
        callbackRef = g_sendMsg_callbacks[cbId].onErrorRef;
    } else if (auto* ctx = GetBaseCallback(cbId)) {
        callbackRef = ctx->onErrorRef;
    }
    QueueCallback(callbackRef, {JsArg::Int(code), JsArg::String(message)},
                  isSendMessage ? CleanupType::SendMessage : CleanupType::Base, cbId);
}

void CallUploadOpenCallback(int cbId, long long fileSize) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onOpenRef) return;
    QueueCallback(ctx->onOpenRef, {JsArg::Long(fileSize)});
}

void CallUploadPartSizeCallback(int cbId, long long partSize, long long partNumber) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onPartSizeRef) return;

    QueueCallback(ctx->onPartSizeRef, {JsArg::Long(partSize), JsArg::Long(partNumber)});
}

void CallUploadHashProgressCallback(int cbId, long long index, long long size, const char* partHash) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onHashPartProgressRef) return;

    QueueCallback(ctx->onHashPartProgressRef,
                  {JsArg::Long(index), JsArg::Long(size), JsArg::String(partHash)});
}

void CallUploadHashCompleteCallback(int cbId, const char* partsHash, const char* fileHash) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onHashPartCompleteRef) return;

    QueueCallback(ctx->onHashPartCompleteRef, {JsArg::String(partsHash), JsArg::String(fileHash)});
}

void CallUploadIDCallback(int cbId, const char* uploadID) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onUploadIDRef) return;

    QueueCallback(ctx->onUploadIDRef, {JsArg::String(uploadID)});
}

void CallUploadPartCompleteCallback(int cbId, long long index, long long partSize, const char* partHash) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onUploadPartCompleteRef) return;

    QueueCallback(ctx->onUploadPartCompleteRef,
                  {JsArg::Long(index), JsArg::Long(partSize), JsArg::String(partHash)});
}

void CallUploadCompleteCallback(int cbId, long long fileSize, long long streamSize, long long storageSize) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onUploadCompleteRef) return;

    QueueCallback(ctx->onUploadCompleteRef,
                  {JsArg::Long(fileSize), JsArg::Long(streamSize), JsArg::Long(storageSize)});
}

void CallUploadFinishCallback(int cbId, long long size, const char* url, long long fileType) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onCompleteRef) return;

    QueueCallback(ctx->onCompleteRef,
                  {JsArg::Long(size), JsArg::String(url), JsArg::Long(fileType)},
                  CleanupType::Upload, cbId);
}

void CallUploadLogProgressCallback(int cbId, long long current, long long total) {
    auto* ctx = GetUploadLogCallback(cbId);
    if (!ctx || !ctx->onProgressRef) return;

    QueueCallback(ctx->onProgressRef, {JsArg::Long(current), JsArg::Long(total)},
                  total > 0 && current >= total ? CleanupType::UploadLog : CleanupType::None, cbId);
}

void CallSendMsgCallback(int cbId, long long progress) {
    auto* ctx = GetSendMsgCallback(cbId);
    if (!ctx || !ctx->onProgressRef) return;

    QueueCallback(ctx->onProgressRef, {JsArg::Long(progress)});

    // The terminal success/error callback owns cleanup. A 100% progress event
    // can arrive before the final result and must not invalidate its callbacks.
}

// ============================================================
// C API 回调入口点 (供 Go 层调用)
// ============================================================

extern "C" {

// Base 回调
void CAPI_OnBaseSuccess(int cbId, char* data) {
    CallBaseSuccessCallback(cbId, data);
    FreeString(data);
}

void CAPI_OnBaseError(int cbId, int code, char* message) {
    CallBaseErrorCallback(cbId, code, message);
    FreeString(message);
}

// 上传文件回调（SDK 现在传递 cbId）
void CAPI_OnUploadOpen(int cbId, long long fileSize) {
    CallUploadOpenCallback(cbId, fileSize);
}

void CAPI_OnUploadPartSize(int cbId, long long partSize, long long partNumber) {
    CallUploadPartSizeCallback(cbId, partSize, partNumber);
}

void CAPI_OnUploadHashProgress(int cbId, long long index, long long size, char* partHash) {
    CallUploadHashProgressCallback(cbId, index, size, partHash);
    FreeString(partHash);
}

void CAPI_OnUploadHashComplete(int cbId, char* partsHash, char* fileHash) {
    CallUploadHashCompleteCallback(cbId, partsHash, fileHash);
    FreeString(partsHash);
    FreeString(fileHash);
}

void CAPI_OnUploadID(int cbId, char* uploadID) {
    CallUploadIDCallback(cbId, uploadID);
    FreeString(uploadID);
}

void CAPI_OnUploadPartComplete(int cbId, long long index, long long partSize, char* partHash) {
    CallUploadPartCompleteCallback(cbId, index, partSize, partHash);
    FreeString(partHash);
}

void CAPI_OnUploadComplete(int cbId, long long fileSize, long long streamSize, long long storageSize) {
    CallUploadCompleteCallback(cbId, fileSize, streamSize, storageSize);
}

void CAPI_OnUploadFinish(int cbId, long long size, char* url, long long fileType) {
    CallUploadFinishCallback(cbId, size, url, fileType);
    FreeString(url);
}

// 日志上传回调（SDK 现在传递 cbId）
void CAPI_OnUploadLogProgress(int cbId, long long current, long long total) {
    CallUploadLogProgressCallback(cbId, current, total);
}

// 发送进度回调
void CAPI_OnSendMsg(int cbId, long long progress) {
    CallSendMsgCallback(cbId, progress);
}

// 连接回调
void CAPI_OnConnConnecting(int) {
    CallVoidCallback(g_listeners.env, g_listeners.onConnecting);
}

void CAPI_OnConnConnectSuccess(int) {
    CallVoidCallback(g_listeners.env, g_listeners.onConnectSuccess);
}

void CAPI_OnConnConnectFailed(int errCode, char* message) {
    CallIntStringCallback(g_listeners.env, g_listeners.onConnectFailed, errCode, message);
}

void CAPI_OnConnKickedOffline(int) {
    CallVoidCallback(g_listeners.env, g_listeners.onKickedOffline);
}

void CAPI_OnConnUserTokenExpired(int) {
    CallVoidCallback(g_listeners.env, g_listeners.onUserTokenExpired);
}

void CAPI_OnConnUserTokenInvalid(int, char* message) {
    CallStringCallback(g_listeners.env, g_listeners.onUserTokenInvalid, message);
}

// 消息回调
void CAPI_OnRecvNewMsg(char* msg) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvNewMsg, msg);
}

void CAPI_OnRecvReceipt(char* receipt) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvReceipt, receipt);
}

void CAPI_OnMsgRevoked(char* msg) {
    CallStringCallback(g_listeners.env, g_listeners.onMsgRevoked, msg);
}

void CAPI_OnRecvOffline(char* msg) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvOffline, msg);
}

void CAPI_OnMsgDeleted(char* msg) {
    CallStringCallback(g_listeners.env, g_listeners.onMsgDeleted, msg);
}

void CAPI_OnRecvOnline(char* msg) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvOnline, msg);
}

void CAPI_OnRecvNewMessages(char* messages) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvNewMessages, messages);
}

void CAPI_OnRecvOfflineNewMessages(char* messages) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvOfflineNewMessages, messages);
}

// 会话回调
void CAPI_OnConvSyncStart(int reinstalled) {
    CallBoolCallback(g_listeners.env, g_listeners.onSyncStart, reinstalled != 0);
}

void CAPI_OnConvSyncFinish(int reinstalled) {
    CallBoolCallback(g_listeners.env, g_listeners.onSyncFinish, reinstalled != 0);
}

void CAPI_OnConvSyncProgress(long long progress) {
    CallLongLongCallback(g_listeners.env, g_listeners.onSyncProgress, progress);
}

void CAPI_OnConvSyncFailed(int reinstalled) {
    CallBoolCallback(g_listeners.env, g_listeners.onSyncFailed, reinstalled != 0);
}

void CAPI_OnConvChanged(char* conv) {
    CallStringCallback(g_listeners.env, g_listeners.onConvChanged, conv);
}

void CAPI_OnNewConv(char* conv) {
    CallStringCallback(g_listeners.env, g_listeners.onNewConv, conv);
}

void CAPI_OnUnreadChanged(int totalUnreadCount) {
    CallIntCallback(g_listeners.env, g_listeners.onUnreadChanged, totalUnreadCount);
}

void CAPI_OnInputStatus(char* status) {
    CallStringCallback(g_listeners.env, g_listeners.onInputStatus, status);
}

// 群组回调
void CAPI_OnGroupJoinedAdd(char* group) {
    CallStringCallback(g_listeners.env, g_listeners.onJoinedAdd, group);
}

void CAPI_OnGroupJoinedDel(char* group) {
    CallStringCallback(g_listeners.env, g_listeners.onJoinedDel, group);
}

void CAPI_OnGroupMemberAdd(char* member) {
    CallStringCallback(g_listeners.env, g_listeners.onMemberAdd, member);
}

void CAPI_OnGroupMemberDel(char* member) {
    CallStringCallback(g_listeners.env, g_listeners.onMemberDel, member);
}

void CAPI_OnGroupAppAdd(char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onAppAdd, application);
}

void CAPI_OnGroupAppDel(char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onAppDel, application);
}

void CAPI_OnGroupInfoChanged(char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onInfoChanged, info);
}

void CAPI_OnGroupDismissed(char* group) {
    CallStringCallback(g_listeners.env, g_listeners.onDismissed, group);
}

void CAPI_OnGroupMemberInfo(char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onMemberInfo, info);
}

void CAPI_OnGroupAppAccept(char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onAppAccept, application);
}

void CAPI_OnGroupAppReject(char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onAppReject, application);
}

// 好友回调
void CAPI_OnFriendAppAdd(char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendAppAdd, application);
}

void CAPI_OnFriendAppDel(char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendAppDel, application);
}

void CAPI_OnFriendAppAccept(char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendAppAccept, application);
}

void CAPI_OnFriendAppReject(char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendAppReject, application);
}

void CAPI_OnFriendAdd(char* friendInfo) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendAdd, friendInfo);
}

void CAPI_OnFriendDel(char* friendInfo) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendDel, friendInfo);
}

void CAPI_OnFriendInfo(char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendInfo, info);
}

void CAPI_OnBlackAdd(char* black) {
    CallStringCallback(g_listeners.env, g_listeners.onBlackAdd, black);
}

void CAPI_OnBlackDel(char* black) {
    CallStringCallback(g_listeners.env, g_listeners.onBlackDel, black);
}

// 用户回调
void CAPI_OnUserSelfInfoUpdated(char* userInfo) {
    CallStringCallback(g_listeners.env, g_listeners.onSelfInfo, userInfo);
}

void CAPI_OnUserStatusChanged(char* status) {
    CallStringCallback(g_listeners.env, g_listeners.onUserStatus, status);
}

void CAPI_OnUserCommandAdd(char* command) {
    CallStringCallback(g_listeners.env, g_listeners.onUserCommandAdd, command);
}

void CAPI_OnUserCommandDelete(char* command) {
    CallStringCallback(g_listeners.env, g_listeners.onUserCommandDelete, command);
}

void CAPI_OnUserCommandUpdate(char* command) {
    CallStringCallback(g_listeners.env, g_listeners.onUserCommandUpdate, command);
}

// 信令回调
void CAPI_OnSignalingReceiveNewInvitation(char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onReceiveNewInvitation, invitation);
}

void CAPI_OnSignalingInviteeAccepted(char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInviteeAccepted, invitation);
}

void CAPI_OnSignalingInviteeAcceptedByOtherDevice(char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInviteeAcceptedByOtherDevice, invitation);
}

void CAPI_OnSignalingInviteeRejected(char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInviteeRejected, invitation);
}

void CAPI_OnSignalingInviteeRejectedByOtherDevice(char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInviteeRejectedByOtherDevice, invitation);
}

void CAPI_OnSignalingInvitationCancelled(char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInvitationCancelled, invitation);
}

void CAPI_OnSignalingInvitationTimeout(char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInvitationTimeout, invitation);
}

void CAPI_OnSignalingHangUp(char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onHangUp, info);
}

void CAPI_OnSignalingRoomParticipantConnected(char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onRoomParticipantConnected, info);
}

void CAPI_OnSignalingRoomParticipantDisconnected(char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onRoomParticipantDisconnected, info);
}

// 自定义业务回调
void CAPI_OnRecvCustomBusinessMessage(char* message) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvCustomBusinessMessage, message);
}

// 消息 KV 信息回调
void CAPI_OnMessageKvInfoChanged(char* kvInfo) {
    CallStringCallback(g_listeners.env, g_listeners.onMessageKvInfoChanged, kvInfo);
}

}
