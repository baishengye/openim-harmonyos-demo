#include "callback.h"
#include "include/libopenimsdk.h"
#include <string.h>
#include <memory>
#include <mutex>
#include <stdint.h>
#include <vector>

// ============================================================
// C API 回调前向声明
// ============================================================
extern "C" {
// Base 回调
void CAPI_OnBaseSuccess(int cbId, const char* data);
void CAPI_OnBaseError(int cbId, int code, const char* message);

// 上传文件回调（SDK 现在传递 cbId 作为第一个参数）
void CAPI_OnUploadOpen(int cbId, long long fileSize);
void CAPI_OnUploadPartSize(int cbId, long long partSize, int partNumber);
void CAPI_OnUploadHashProgress(int cbId, int index, long long size, const char* partHash);
void CAPI_OnUploadHashComplete(int cbId, const char* partsHash, const char* fileHash);
void CAPI_OnUploadID(int cbId, const char* uploadID);
void CAPI_OnUploadPartComplete(int cbId, int index, long long partSize, const char* partHash);
void CAPI_OnUploadComplete(int cbId, long long fileSize, long long streamSize, long long storageSize);
void CAPI_OnUploadFinish(int cbId, long long size, const char* url, int fileType);

// 日志上传回调（SDK 现在传递 cbId 作为第一个参数）
void CAPI_OnUploadLogProgress(int cbId, long long current, long long total);

// 发送进度回调
void CAPI_OnSendMsg(int cbId, int progress);

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

// 会话回调
void CAPI_OnConvSyncStart(int reinstalled);
void CAPI_OnConvSyncFinish(int reinstalled);
void CAPI_OnConvSyncProgress(int progress);
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
    if (cbId < 0) return INVALID_CALLBACK_ID;

    napi_create_reference(env, onSuccess, 1, &g_baseCallbacks[cbId].onSuccessRef);
    napi_create_reference(env, onError, 1, &g_baseCallbacks[cbId].onErrorRef);
    g_baseCallbacks[cbId].env = env;
    g_baseCallbacks[cbId].isValid = true;

    // Register with SDK
    RegisterBaseCallback(cbId, reinterpret_cast<uintptr_t>(CAPI_OnBaseSuccess),
                         reinterpret_cast<uintptr_t>(CAPI_OnBaseError));

    return cbId;
}

int StoreBaseCallback(napi_env env, napi_value callback) {
    napi_value onSuccess, onError;
    napi_get_named_property(env, callback, "onSuccess", &onSuccess);
    napi_get_named_property(env, callback, "onError", &onError);
    return StoreBaseCallback(env, onSuccess, onError);
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
    if (cbId < 0) return INVALID_CALLBACK_ID;

    auto& ctx = g_upload_callbacks[cbId];
    napi_create_reference(env, onOpen, 1, &ctx.onOpenRef);
    napi_create_reference(env, onPartSize, 1, &ctx.onPartSizeRef);
    napi_create_reference(env, onHashPartProgress, 1, &ctx.onHashPartProgressRef);
    napi_create_reference(env, onHashPartComplete, 1, &ctx.onHashPartCompleteRef);
    napi_create_reference(env, onUploadID, 1, &ctx.onUploadIDRef);
    napi_create_reference(env, onUploadPartComplete, 1, &ctx.onUploadPartCompleteRef);
    napi_create_reference(env, onUploadComplete, 1, &ctx.onUploadCompleteRef);
    napi_create_reference(env, onComplete, 1, &ctx.onCompleteRef);
    ctx.env = env;
    ctx.isValid = true;

    // Register with SDK
    RegisterUploadFileCallback(
        cbId,
        reinterpret_cast<uintptr_t>(CAPI_OnUploadOpen),
        reinterpret_cast<uintptr_t>(CAPI_OnUploadPartSize),
        reinterpret_cast<uintptr_t>(CAPI_OnUploadHashProgress),
        reinterpret_cast<uintptr_t>(CAPI_OnUploadHashComplete),
        reinterpret_cast<uintptr_t>(CAPI_OnUploadID),
        reinterpret_cast<uintptr_t>(CAPI_OnUploadPartComplete),
        reinterpret_cast<uintptr_t>(CAPI_OnUploadComplete),
        reinterpret_cast<uintptr_t>(CAPI_OnUploadFinish));

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
    if (cbId < 0) return INVALID_CALLBACK_ID;

    auto& ctx = g_uploadLog_callbacks[cbId];
    napi_create_reference(env, onProgress, 1, &ctx.onProgressRef);
    ctx.env = env;
    ctx.isValid = true;

    // Register with SDK
    RegisterUploadLogProgress(cbId, reinterpret_cast<uintptr_t>(CAPI_OnUploadLogProgress));

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
    if (cbId < 0) return INVALID_CALLBACK_ID;

    auto& ctx = g_sendMsg_callbacks[cbId];
    napi_create_reference(env, onSuccess, 1, &ctx.onSuccessRef);
    napi_create_reference(env, onError, 1, &ctx.onErrorRef);
    napi_create_reference(env, onProgress, 1, &ctx.onProgressRef);
    ctx.env = env;
    ctx.isValid = true;

    // Register with SDK
    RegisterBaseCallback(cbId, reinterpret_cast<uintptr_t>(CAPI_OnBaseSuccess),
                         reinterpret_cast<uintptr_t>(CAPI_OnBaseError));
    RegisterSendMsgCallback(cbId, reinterpret_cast<uintptr_t>(CAPI_OnSendMsg));

    return cbId;
}

// 重载：从对象中提取 onSuccess/onError/onProgress
int StoreSendMsgCallback(napi_env env, napi_value callback) {
    napi_value onSuccess, onError, onProgress;
    napi_get_named_property(env, callback, "onSuccess", &onSuccess);
    napi_get_named_property(env, callback, "onError", &onError);
    napi_get_named_property(env, callback, "onProgress", &onProgress);
    return StoreSendMsgCallback(env, onSuccess, onError, onProgress);
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
        reinterpret_cast<uintptr_t>(CAPI_OnConnConnecting),
        reinterpret_cast<uintptr_t>(CAPI_OnConnConnectSuccess),
        reinterpret_cast<uintptr_t>(CAPI_OnConnConnectFailed),
        reinterpret_cast<uintptr_t>(CAPI_OnConnKickedOffline),
        reinterpret_cast<uintptr_t>(CAPI_OnConnUserTokenExpired),
        reinterpret_cast<uintptr_t>(CAPI_OnConnUserTokenInvalid));

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
    napi_create_reference(env, onRecvNewMsg, 1, &g_listeners.onRecvNewMsg);
    napi_create_reference(env, onRecvReceipt, 1, &g_listeners.onRecvReceipt);
    napi_create_reference(env, onMsgRevoked, 1, &g_listeners.onMsgRevoked);
    napi_create_reference(env, onRecvOffline, 1, &g_listeners.onRecvOffline);
    napi_create_reference(env, onMsgDeleted, 1, &g_listeners.onMsgDeleted);
    napi_create_reference(env, onRecvOnline, 1, &g_listeners.onRecvOnline);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterMsgListener(
        reinterpret_cast<uintptr_t>(CAPI_OnRecvNewMsg),
        reinterpret_cast<uintptr_t>(CAPI_OnRecvReceipt),
        reinterpret_cast<uintptr_t>(CAPI_OnMsgRevoked),
        reinterpret_cast<uintptr_t>(CAPI_OnRecvOffline),
        reinterpret_cast<uintptr_t>(CAPI_OnMsgDeleted),
        reinterpret_cast<uintptr_t>(CAPI_OnRecvOnline));

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
        reinterpret_cast<uintptr_t>(CAPI_OnConvSyncStart),
        reinterpret_cast<uintptr_t>(CAPI_OnConvSyncFinish),
        reinterpret_cast<uintptr_t>(CAPI_OnConvSyncProgress),
        reinterpret_cast<uintptr_t>(CAPI_OnConvSyncFailed),
        reinterpret_cast<uintptr_t>(CAPI_OnConvChanged),
        reinterpret_cast<uintptr_t>(CAPI_OnNewConv),
        reinterpret_cast<uintptr_t>(CAPI_OnUnreadChanged),
        reinterpret_cast<uintptr_t>(CAPI_OnInputStatus));

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
        reinterpret_cast<uintptr_t>(CAPI_OnGroupJoinedAdd),
        reinterpret_cast<uintptr_t>(CAPI_OnGroupJoinedDel),
        reinterpret_cast<uintptr_t>(CAPI_OnGroupMemberAdd),
        reinterpret_cast<uintptr_t>(CAPI_OnGroupMemberDel),
        reinterpret_cast<uintptr_t>(CAPI_OnGroupAppAdd),
        reinterpret_cast<uintptr_t>(CAPI_OnGroupAppDel),
        reinterpret_cast<uintptr_t>(CAPI_OnGroupInfoChanged),
        reinterpret_cast<uintptr_t>(CAPI_OnGroupDismissed),
        reinterpret_cast<uintptr_t>(CAPI_OnGroupMemberInfo),
        reinterpret_cast<uintptr_t>(CAPI_OnGroupAppAccept),
        reinterpret_cast<uintptr_t>(CAPI_OnGroupAppReject));

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
        reinterpret_cast<uintptr_t>(CAPI_OnFriendAppAdd),
        reinterpret_cast<uintptr_t>(CAPI_OnFriendAppDel),
        reinterpret_cast<uintptr_t>(CAPI_OnFriendAppAccept),
        reinterpret_cast<uintptr_t>(CAPI_OnFriendAppReject),
        reinterpret_cast<uintptr_t>(CAPI_OnFriendAdd),
        reinterpret_cast<uintptr_t>(CAPI_OnFriendDel),
        reinterpret_cast<uintptr_t>(CAPI_OnFriendInfo),
        reinterpret_cast<uintptr_t>(CAPI_OnBlackAdd),
        reinterpret_cast<uintptr_t>(CAPI_OnBlackDel));

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

int StoreUserListener(napi_env env, napi_value onSelfInfo, napi_value onUserStatus) {
    napi_create_reference(env, onSelfInfo, 1, &g_listeners.onSelfInfo);
    napi_create_reference(env, onUserStatus, 1, &g_listeners.onUserStatus);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterUserListener(reinterpret_cast<uintptr_t>(CAPI_OnUserSelfInfoUpdated),
                         reinterpret_cast<uintptr_t>(CAPI_OnUserStatusChanged));

    return 0;
}

void DeleteUserListener() {
    UnregisterUserListener();

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(g_listeners.env, ref); ref = nullptr; }
    DELETE_REF(g_listeners.onSelfInfo);
    DELETE_REF(g_listeners.onUserStatus);
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
        reinterpret_cast<uintptr_t>(CAPI_OnSignalingReceiveNewInvitation),
        reinterpret_cast<uintptr_t>(CAPI_OnSignalingInviteeAccepted),
        reinterpret_cast<uintptr_t>(CAPI_OnSignalingInviteeAcceptedByOtherDevice),
        reinterpret_cast<uintptr_t>(CAPI_OnSignalingInviteeRejected),
        reinterpret_cast<uintptr_t>(CAPI_OnSignalingInviteeRejectedByOtherDevice),
        reinterpret_cast<uintptr_t>(CAPI_OnSignalingInvitationCancelled),
        reinterpret_cast<uintptr_t>(CAPI_OnSignalingInvitationTimeout),
        reinterpret_cast<uintptr_t>(CAPI_OnSignalingHangUp),
        reinterpret_cast<uintptr_t>(CAPI_OnSignalingRoomParticipantConnected),
        reinterpret_cast<uintptr_t>(CAPI_OnSignalingRoomParticipantDisconnected));

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
    napi_create_reference(env, onRecvCustomBusinessMessage, 1, &g_listeners.onRecvCustomBusinessMessage);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterCustomBusinessListener(reinterpret_cast<uintptr_t>(CAPI_OnRecvCustomBusinessMessage));

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
    napi_create_reference(env, onMessageKvInfoChanged, 1, &g_listeners.onMessageKvInfoChanged);
    g_listeners.env = env;
    g_listeners.isValid = true;

    RegisterMsgKvInfoListener(reinterpret_cast<uintptr_t>(CAPI_OnMessageKvInfoChanged));

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

void CallIntStringCallback(napi_env env, napi_ref callbackRef, int value, const char* text) {
    (void)env;
    QueueCallback(callbackRef, {JsArg::Int(value), JsArg::String(text)});
    if (text) FreeString(const_cast<char*>(text));
}

void CallLongLongCallback(napi_env env, napi_ref callbackRef, long long value) {
    (void)env;
    QueueCallback(callbackRef, {JsArg::Long(value)});
}

void CallStringCallback(napi_env env, napi_ref callbackRef, const char* value) {
    (void)env;
    QueueCallback(callbackRef, {JsArg::String(value)});
    if (value) FreeString(const_cast<char*>(value));
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
    if (data) FreeString(const_cast<char*>(data));
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
    if (message) FreeString(const_cast<char*>(message));
}

void CallUploadOpenCallback(int cbId, long long fileSize) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onOpenRef) return;
    QueueCallback(ctx->onOpenRef, {JsArg::Long(fileSize)});
}

void CallUploadPartSizeCallback(int cbId, long long partSize, int partNumber) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onPartSizeRef) return;

    QueueCallback(ctx->onPartSizeRef, {JsArg::Long(partSize), JsArg::Int(partNumber)});
}

void CallUploadHashProgressCallback(int cbId, int index, long long size, const char* partHash) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onHashPartProgressRef) return;

    QueueCallback(ctx->onHashPartProgressRef,
                  {JsArg::Int(index), JsArg::Long(size), JsArg::String(partHash)});
    if (partHash) FreeString(const_cast<char*>(partHash));
}

void CallUploadHashCompleteCallback(int cbId, const char* partsHash, const char* fileHash) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onHashPartCompleteRef) return;

    QueueCallback(ctx->onHashPartCompleteRef, {JsArg::String(partsHash), JsArg::String(fileHash)});
    if (partsHash) FreeString(const_cast<char*>(partsHash));
    if (fileHash) FreeString(const_cast<char*>(fileHash));
}

void CallUploadIDCallback(int cbId, const char* uploadID) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onUploadIDRef) return;

    QueueCallback(ctx->onUploadIDRef, {JsArg::String(uploadID)});
    if (uploadID) FreeString(const_cast<char*>(uploadID));
}

void CallUploadPartCompleteCallback(int cbId, int index, long long partSize, const char* partHash) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onUploadPartCompleteRef) return;

    QueueCallback(ctx->onUploadPartCompleteRef,
                  {JsArg::Int(index), JsArg::Long(partSize), JsArg::String(partHash)});
    if (partHash) FreeString(const_cast<char*>(partHash));
}

void CallUploadCompleteCallback(int cbId, long long fileSize, long long streamSize, long long storageSize) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onUploadCompleteRef) return;

    QueueCallback(ctx->onUploadCompleteRef,
                  {JsArg::Long(fileSize), JsArg::Long(streamSize), JsArg::Long(storageSize)});
}

void CallUploadFinishCallback(int cbId, long long size, const char* url, int fileType) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onCompleteRef) return;

    QueueCallback(ctx->onCompleteRef,
                  {JsArg::Long(size), JsArg::String(url), JsArg::Int(fileType)},
                  CleanupType::Upload, cbId);
    if (url) FreeString(const_cast<char*>(url));
}

void CallUploadLogProgressCallback(int cbId, long long current, long long total) {
    auto* ctx = GetUploadLogCallback(cbId);
    if (!ctx || !ctx->onProgressRef) return;

    QueueCallback(ctx->onProgressRef, {JsArg::Long(current), JsArg::Long(total)},
                  total > 0 && current >= total ? CleanupType::UploadLog : CleanupType::None, cbId);
}

void CallSendMsgCallback(int cbId, int progress) {
    auto* ctx = GetSendMsgCallback(cbId);
    if (!ctx || !ctx->onProgressRef) return;

    QueueCallback(ctx->onProgressRef, {JsArg::Int(progress)});

    // The terminal success/error callback owns cleanup. A 100% progress event
    // can arrive before the final result and must not invalidate its callbacks.
}

// ============================================================
// C API 回调入口点 (供 Go 层调用)
// ============================================================

extern "C" {

// Base 回调
void CAPI_OnBaseSuccess(int cbId, const char* data) {
    CallBaseSuccessCallback(cbId, data);
}

void CAPI_OnBaseError(int cbId, int code, const char* message) {
    CallBaseErrorCallback(cbId, code, message);
}

// 上传文件回调（SDK 现在传递 cbId）
void CAPI_OnUploadOpen(int cbId, long long fileSize) {
    CallUploadOpenCallback(cbId, fileSize);
}

void CAPI_OnUploadPartSize(int cbId, long long partSize, int partNumber) {
    CallUploadPartSizeCallback(cbId, partSize, partNumber);
}

void CAPI_OnUploadHashProgress(int cbId, int index, long long size, const char* partHash) {
    CallUploadHashProgressCallback(cbId, index, size, partHash);
}

void CAPI_OnUploadHashComplete(int cbId, const char* partsHash, const char* fileHash) {
    CallUploadHashCompleteCallback(cbId, partsHash, fileHash);
}

void CAPI_OnUploadID(int cbId, const char* uploadID) {
    CallUploadIDCallback(cbId, uploadID);
}

void CAPI_OnUploadPartComplete(int cbId, int index, long long partSize, const char* partHash) {
    CallUploadPartCompleteCallback(cbId, index, partSize, partHash);
}

void CAPI_OnUploadComplete(int cbId, long long fileSize, long long streamSize, long long storageSize) {
    CallUploadCompleteCallback(cbId, fileSize, streamSize, storageSize);
}

void CAPI_OnUploadFinish(int cbId, long long size, const char* url, int fileType) {
    CallUploadFinishCallback(cbId, size, url, fileType);
}

// 日志上传回调（SDK 现在传递 cbId）
void CAPI_OnUploadLogProgress(int cbId, long long current, long long total) {
    CallUploadLogProgressCallback(cbId, current, total);
}

// 发送进度回调
void CAPI_OnSendMsg(int cbId, int progress) {
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

// 会话回调
void CAPI_OnConvSyncStart(int reinstalled) {
    CallBoolCallback(g_listeners.env, g_listeners.onSyncStart, reinstalled != 0);
}

void CAPI_OnConvSyncFinish(int reinstalled) {
    CallBoolCallback(g_listeners.env, g_listeners.onSyncFinish, reinstalled != 0);
}

void CAPI_OnConvSyncProgress(int progress) {
    CallIntCallback(g_listeners.env, g_listeners.onSyncProgress, progress);
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
