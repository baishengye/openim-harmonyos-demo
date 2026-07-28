#include "callback.h"
#include "libopenimsdk.h"
#include <string.h>
#include <mutex>
#include <stdint.h>

// ============================================================
// C API 回调前向声明
// ============================================================
extern "C" {
// Base 回调
void CAPI_OnBaseSuccess(int cbId, const char* data);
void CAPI_OnBaseError(int cbId, int code, const char* message);

// 上传文件回调
void CAPI_OnUploadOpen(long long fileSize);
void CAPI_OnUploadPartSize(long long partSize, int partNumber);
void CAPI_OnUploadHashProgress(int index, long long size, const char* partHash);
void CAPI_OnUploadHashComplete(const char* partsHash, const char* fileHash);
void CAPI_OnUploadID(const char* uploadID);
void CAPI_OnUploadPartComplete(int index, long long partSize, const char* partHash);
void CAPI_OnUploadComplete(long long fileSize, long long streamSize, long long storageSize);
void CAPI_OnUploadFinish(long long size, const char* url, int fileType);

// 日志上传回调
void CAPI_OnUploadLogProgress(long long current, long long total);

// 发送进度回调
void CAPI_OnSendMsg(int cbId, int progress);

// 连接回调
void CAPI_OnConnConnecting();
void CAPI_OnConnConnectSuccess();
void CAPI_OnConnConnectFailed(int cbId, const char* message);
void CAPI_OnConnKickedOffline();
void CAPI_OnConnUserTokenExpired();
void CAPI_OnConnUserTokenInvalid(int cbId, const char* message);

// 消息回调
void CAPI_OnRecvNewMsg(int cbId, const char* msg);
void CAPI_OnRecvReceipt(int cbId, const char* receipt);
void CAPI_OnMsgRevoked(int cbId, const char* msg);
void CAPI_OnRecvOffline(int cbId, const char* msg);
void CAPI_OnMsgDeleted(int cbId, const char* msg);
void CAPI_OnRecvOnline(int cbId, const char* msg);

// 会话回调
void CAPI_OnConvSyncStart();
void CAPI_OnConvSyncFinish();
void CAPI_OnConvSyncProgress(int progress);
void CAPI_OnConvSyncFailed(int cbId, const char* err);
void CAPI_OnConvChanged(int cbId, const char* conv);
void CAPI_OnNewConv(int cbId, const char* conv);
void CAPI_OnUnreadChanged(int totalUnreadCount);
void CAPI_OnInputStatus(int cbId, const char* status);

// 群组回调
void CAPI_OnGroupJoinedAdd(int cbId, const char* group);
void CAPI_OnGroupJoinedDel(int cbId, const char* group);
void CAPI_OnGroupMemberAdd(int cbId, const char* member);
void CAPI_OnGroupMemberDel(int cbId, const char* member);
void CAPI_OnGroupAppAdd(int cbId, const char* application);
void CAPI_OnGroupAppDel(int cbId, const char* application);
void CAPI_OnGroupInfoChanged(int cbId, const char* info);
void CAPI_OnGroupDismissed(int cbId, const char* group);
void CAPI_OnGroupMemberInfo(int cbId, const char* info);
void CAPI_OnGroupAppAccept(int cbId, const char* application);
void CAPI_OnGroupAppReject(int cbId, const char* application);

// 好友回调
void CAPI_OnFriendAppAdd(int cbId, const char* application);
void CAPI_OnFriendAppDel(int cbId, const char* application);
void CAPI_OnFriendAppAccept(int cbId, const char* application);
void CAPI_OnFriendAppReject(int cbId, const char* application);
void CAPI_OnFriendAdd(int cbId, const char* frient);
void CAPI_OnFriendDel(int cbId, const char* frient);
void CAPI_OnFriendInfo(int cbId, const char* info);
void CAPI_OnBlackAdd(int cbId, const char* black);
void CAPI_OnBlackDel(int cbId, const char* black);

// 用户回调
void CAPI_OnUserSelfInfoUpdated(int cbId, const char* userInfo);
void CAPI_OnUserStatusChanged(int cbId, const char* status);

// 信令回调
void CAPI_OnSignalingReceiveNewInvitation(int cbId, const char* invitation);
void CAPI_OnSignalingInviteeAccepted(int cbId, const char* invitation);
void CAPI_OnSignalingInviteeAcceptedByOtherDevice(int cbId, const char* invitation);
void CAPI_OnSignalingInviteeRejected(int cbId, const char* invitation);
void CAPI_OnSignalingInviteeRejectedByOtherDevice(int cbId, const char* invitation);
void CAPI_OnSignalingInvitationCancelled(int cbId, const char* invitation);
void CAPI_OnSignalingInvitationTimeout(int cbId, const char* invitation);
void CAPI_OnSignalingHangUp(int cbId, const char* info);
void CAPI_OnSignalingRoomParticipantConnected(int cbId, const char* info);
void CAPI_OnSignalingRoomParticipantDisconnected(int cbId, const char* info);

// 自定义业务回调
void CAPI_OnRecvCustomBusinessMessage(int cbId, const char* message);

// 消息 KV 信息回调
void CAPI_OnMessageKvInfoChanged(int cbId, const char* kvInfo);
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

// 当前上传回调 ID（SDK 的上传回调不包含 cbId 参数，需要从上下文获取）
static int g_currentUploadCallbackId = INVALID_CALLBACK_ID;
static std::mutex g_upload_mutex;

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
    RegisterBaseCallback(cbId, (intptr_t)CAPI_OnBaseSuccess, (intptr_t)CAPI_OnBaseError);

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

// ============================================================
// 上传回调上下文管理
// ============================================================

// 设置当前上传回调 ID（SDK 上传回调不包含 cbId，需从上下文获取）
void SetCurrentUploadCallbackId(int cbId) {
    std::lock_guard<std::mutex> lock(g_upload_mutex);
    g_currentUploadCallbackId = cbId;
}

// 获取当前上传回调 ID
int GetCurrentUploadCallbackId() {
    std::lock_guard<std::mutex> lock(g_upload_mutex);
    return g_currentUploadCallbackId;
}

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

    // 设置当前上传回调 ID
    SetCurrentUploadCallbackId(cbId);

    // Register with SDK
    RegisterUploadFileCallback(
        cbId,
        (intptr_t)CAPI_OnUploadOpen,
        (intptr_t)CAPI_OnUploadPartSize,
        (intptr_t)CAPI_OnUploadHashProgress,
        (intptr_t)CAPI_OnUploadHashComplete,
        (intptr_t)CAPI_OnUploadID,
        (intptr_t)CAPI_OnUploadPartComplete,
        (intptr_t)CAPI_OnUploadComplete,
        (intptr_t)CAPI_OnUploadFinish
    );

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
    RegisterUploadLogProgress(cbId, (intptr_t)CAPI_OnUploadLogProgress);

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
    RegisterBaseCallback(cbId, (intptr_t)CAPI_OnBaseSuccess, (intptr_t)CAPI_OnBaseError);
    RegisterSendMsgCallback(cbId, (intptr_t)CAPI_OnSendMsg);

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
        (intptr_t)CAPI_OnConnConnecting,
        (intptr_t)CAPI_OnConnConnectSuccess,
        (intptr_t)CAPI_OnConnConnectFailed,
        (intptr_t)CAPI_OnConnKickedOffline,
        (intptr_t)CAPI_OnConnUserTokenExpired,
        (intptr_t)CAPI_OnConnUserTokenInvalid
    );

    return 0;
}

void DeleteConnListener() {
    if (!g_listeners.isValid) return;

    UnregisterConnListener();

    #define DELETE_REF(ref) if (ref) { napi_delete_reference(g_listeners.env, ref); ref = nullptr; }
    DELETE_REF(g_listeners.onConnecting);
    DELETE_REF(g_listeners.onConnectSuccess);
    DELETE_REF(g_listeners.onConnectFailed);
    DELETE_REF(g_listeners.onKickedOffline);
    DELETE_REF(g_listeners.onUserTokenExpired);
    DELETE_REF(g_listeners.onUserTokenInvalid);
    #undef DELETE_REF

    g_listeners.isValid = false;
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
        (intptr_t)CAPI_OnRecvNewMsg,
        (intptr_t)CAPI_OnRecvReceipt,
        (intptr_t)CAPI_OnMsgRevoked,
        (intptr_t)CAPI_OnRecvOffline,
        (intptr_t)CAPI_OnMsgDeleted,
        (intptr_t)CAPI_OnRecvOnline
    );

    return 0;
}

void DeleteMsgListener() {
    if (!g_listeners.isValid) return;

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
        (intptr_t)CAPI_OnConvSyncStart,
        (intptr_t)CAPI_OnConvSyncFinish,
        (intptr_t)CAPI_OnConvSyncProgress,
        (intptr_t)CAPI_OnConvSyncFailed,
        (intptr_t)CAPI_OnConvChanged,
        (intptr_t)CAPI_OnNewConv,
        (intptr_t)CAPI_OnUnreadChanged,
        (intptr_t)CAPI_OnInputStatus
    );

    return 0;
}

void DeleteConvListener() {
    if (!g_listeners.isValid) return;

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
        (intptr_t)CAPI_OnGroupJoinedAdd,
        (intptr_t)CAPI_OnGroupJoinedDel,
        (intptr_t)CAPI_OnGroupMemberAdd,
        (intptr_t)CAPI_OnGroupMemberDel,
        (intptr_t)CAPI_OnGroupAppAdd,
        (intptr_t)CAPI_OnGroupAppDel,
        (intptr_t)CAPI_OnGroupInfoChanged,
        (intptr_t)CAPI_OnGroupDismissed,
        (intptr_t)CAPI_OnGroupMemberInfo,
        (intptr_t)CAPI_OnGroupAppAccept,
        (intptr_t)CAPI_OnGroupAppReject
    );

    return 0;
}

void DeleteGroupListener() {
    if (!g_listeners.isValid) return;

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
        (intptr_t)CAPI_OnFriendAppAdd,
        (intptr_t)CAPI_OnFriendAppDel,
        (intptr_t)CAPI_OnFriendAppAccept,
        (intptr_t)CAPI_OnFriendAppReject,
        (intptr_t)CAPI_OnFriendAdd,
        (intptr_t)CAPI_OnFriendDel,
        (intptr_t)CAPI_OnFriendInfo,
        (intptr_t)CAPI_OnBlackAdd,
        (intptr_t)CAPI_OnBlackDel
    );

    return 0;
}

void DeleteFriendListener() {
    if (!g_listeners.isValid) return;

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

    RegisterUserListener(
        (intptr_t)CAPI_OnUserSelfInfoUpdated,
        (intptr_t)CAPI_OnUserStatusChanged
    );

    return 0;
}

void DeleteUserListener() {
    if (!g_listeners.isValid) return;

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
        (intptr_t)CAPI_OnSignalingReceiveNewInvitation,
        (intptr_t)CAPI_OnSignalingInviteeAccepted,
        (intptr_t)CAPI_OnSignalingInviteeAcceptedByOtherDevice,
        (intptr_t)CAPI_OnSignalingInviteeRejected,
        (intptr_t)CAPI_OnSignalingInviteeRejectedByOtherDevice,
        (intptr_t)CAPI_OnSignalingInvitationCancelled,
        (intptr_t)CAPI_OnSignalingInvitationTimeout,
        (intptr_t)CAPI_OnSignalingHangUp,
        (intptr_t)CAPI_OnSignalingRoomParticipantConnected,
        (intptr_t)CAPI_OnSignalingRoomParticipantDisconnected
    );

    return 0;
}

void DeleteSignalingListener() {
    if (!g_listeners.isValid) return;

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

    RegisterCustomBusinessListener((intptr_t)CAPI_OnRecvCustomBusinessMessage);

    return 0;
}

void DeleteCustomBusinessListener() {
    if (!g_listeners.isValid) return;

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

    RegisterMsgKvInfoListener((intptr_t)CAPI_OnMessageKvInfoChanged);

    return 0;
}

void DeleteMsgKvInfoListener() {
    if (!g_listeners.isValid) return;

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

static napi_value GetCallbackValue(napi_env env, napi_ref ref) {
    if (!ref) return nullptr;
    napi_value value;
    napi_get_reference_value(env, ref, &value);
    return value;
}

void CallVoidCallback(napi_env env, napi_ref callbackRef) {
    if (!callbackRef) return;
    napi_value callback = GetCallbackValue(env, callbackRef);
    if (!callback) return;

    napi_value result;
    napi_call_function(env, nullptr, callback, 0, nullptr, &result);
}

void CallIntCallback(napi_env env, napi_ref callbackRef, int value) {
    if (!callbackRef) return;
    napi_value callback = GetCallbackValue(env, callbackRef);
    if (!callback) return;

    napi_value argv[1];
    napi_create_int32(env, value, &argv[0]);
    napi_value result;
    napi_call_function(env, nullptr, callback, 1, argv, &result);
}

void CallLongLongCallback(napi_env env, napi_ref callbackRef, long long value) {
    if (!callbackRef) return;
    napi_value callback = GetCallbackValue(env, callbackRef);
    if (!callback) return;

    napi_value argv[1];
    napi_create_int64(env, value, &argv[0]);
    napi_value result;
    napi_call_function(env, nullptr, callback, 1, argv, &result);
}

void CallStringCallback(napi_env env, napi_ref callbackRef, const char* value) {
    if (!callbackRef) return;
    napi_value callback = GetCallbackValue(env, callbackRef);
    if (!callback) return;

    napi_value argv[1];
    napi_create_string_utf8(env, value, NAPI_AUTO_LENGTH, &argv[0]);
    napi_value result;
    napi_call_function(env, nullptr, callback, 1, argv, &result);
}

void CallBaseSuccessCallback(int cbId, const char* data) {
    auto* ctx = GetBaseCallback(cbId);
    if (!ctx || !ctx->onSuccessRef) return;

    napi_value argv[2];
    napi_create_int32(ctx->env, cbId, &argv[0]);
    napi_create_string_utf8(ctx->env, data, NAPI_AUTO_LENGTH, &argv[1]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onSuccessRef), 2, argv, &result);

    // 检查是否是 SendMsgCallback，如果是则清理 SendMsgCallback
    if (g_sendMsg_callbacks[cbId].isValid) {
        DeleteSendMsgCallback(cbId);
    } else {
        DeleteBaseCallback(cbId);
    }
}

void CallBaseErrorCallback(int cbId, int code, const char* message) {
    auto* ctx = GetBaseCallback(cbId);
    if (!ctx || !ctx->onErrorRef) return;

    napi_value argv[3];
    napi_create_int32(ctx->env, cbId, &argv[0]);
    napi_create_int32(ctx->env, code, &argv[1]);
    napi_create_string_utf8(ctx->env, message, NAPI_AUTO_LENGTH, &argv[2]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onErrorRef), 3, argv, &result);

    // 检查是否是 SendMsgCallback，如果是则清理 SendMsgCallback
    if (g_sendMsg_callbacks[cbId].isValid) {
        DeleteSendMsgCallback(cbId);
    } else {
        DeleteBaseCallback(cbId);
    }
}

void CallUploadOpenCallback(int cbId, long long fileSize) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onOpenRef) return;

    napi_value argv[1];
    napi_create_int64(ctx->env, fileSize, &argv[0]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onOpenRef), 1, argv, &result);
}

void CallUploadPartSizeCallback(int cbId, long long partSize, int partNumber) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onPartSizeRef) return;

    napi_value argv[2];
    napi_create_int64(ctx->env, partSize, &argv[0]);
    napi_create_int32(ctx->env, partNumber, &argv[1]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onPartSizeRef), 2, argv, &result);
}

void CallUploadHashProgressCallback(int cbId, int index, long long size, const char* partHash) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onHashPartProgressRef) return;

    napi_value argv[3];
    napi_create_int32(ctx->env, index, &argv[0]);
    napi_create_int64(ctx->env, size, &argv[1]);
    napi_create_string_utf8(ctx->env, partHash, NAPI_AUTO_LENGTH, &argv[2]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onHashPartProgressRef), 3, argv, &result);
}

void CallUploadHashCompleteCallback(int cbId, const char* partsHash, const char* fileHash) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onHashPartCompleteRef) return;

    napi_value argv[2];
    napi_create_string_utf8(ctx->env, partsHash, NAPI_AUTO_LENGTH, &argv[0]);
    napi_create_string_utf8(ctx->env, fileHash, NAPI_AUTO_LENGTH, &argv[1]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onHashPartCompleteRef), 2, argv, &result);
}

void CallUploadIDCallback(int cbId, const char* uploadID) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onUploadIDRef) return;

    napi_value argv[1];
    napi_create_string_utf8(ctx->env, uploadID, NAPI_AUTO_LENGTH, &argv[0]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onUploadIDRef), 1, argv, &result);
}

void CallUploadPartCompleteCallback(int cbId, int index, long long partSize, const char* partHash) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onUploadPartCompleteRef) return;

    napi_value argv[3];
    napi_create_int32(ctx->env, index, &argv[0]);
    napi_create_int64(ctx->env, partSize, &argv[1]);
    napi_create_string_utf8(ctx->env, partHash, NAPI_AUTO_LENGTH, &argv[2]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onUploadPartCompleteRef), 3, argv, &result);
}

void CallUploadCompleteCallback(int cbId, long long fileSize, long long streamSize, long long storageSize) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onUploadCompleteRef) return;

    napi_value argv[3];
    napi_create_int64(ctx->env, fileSize, &argv[0]);
    napi_create_int64(ctx->env, streamSize, &argv[1]);
    napi_create_int64(ctx->env, storageSize, &argv[2]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onUploadCompleteRef), 3, argv, &result);
}

void CallUploadFinishCallback(int cbId, long long size, const char* url, int fileType) {
    auto* ctx = GetUploadCallback(cbId);
    if (!ctx || !ctx->onCompleteRef) return;

    napi_value argv[3];
    napi_create_int64(ctx->env, size, &argv[0]);
    napi_create_string_utf8(ctx->env, url, NAPI_AUTO_LENGTH, &argv[1]);
    napi_create_int32(ctx->env, fileType, &argv[2]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onCompleteRef), 3, argv, &result);

    // 回调执行完毕后自动清理
    DeleteUploadCallbacks(cbId);
}

void CallUploadLogProgressCallback(int cbId, long long current, long long total) {
    auto* ctx = GetUploadLogCallback(cbId);
    if (!ctx || !ctx->onProgressRef) return;

    napi_value argv[2];
    napi_create_int64(ctx->env, current, &argv[0]);
    napi_create_int64(ctx->env, total, &argv[1]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onProgressRef), 2, argv, &result);

    // 进度达到100%时，完成回调后自动清理
    if (total > 0 && current >= total) {
        DeleteUploadLogCallback(cbId);
    }
}

void CallSendMsgCallback(int cbId, int progress) {
    auto* ctx = GetSendMsgCallback(cbId);
    if (!ctx || !ctx->onProgressRef) return;

    napi_value argv[2];
    napi_create_int32(ctx->env, cbId, &argv[0]);
    napi_create_int32(ctx->env, progress, &argv[1]);
    napi_value result;
    napi_call_function(ctx->env, nullptr, GetCallbackValue(ctx->env, ctx->onProgressRef), 2, argv, &result);

    // 进度达到100%时，完成回调后自动清理
    if (progress >= 100) {
        DeleteSendMsgCallback(cbId);
    }
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

// 上传文件回调
void CAPI_OnUploadOpen(long long fileSize) {
    int cbId = GetCurrentUploadCallbackId();
    CallUploadOpenCallback(cbId, fileSize);
}

void CAPI_OnUploadPartSize(long long partSize, int partNumber) {
    int cbId = GetCurrentUploadCallbackId();
    CallUploadPartSizeCallback(cbId, partSize, partNumber);
}

void CAPI_OnUploadHashProgress(int index, long long size, const char* partHash) {
    int cbId = GetCurrentUploadCallbackId();
    CallUploadHashProgressCallback(cbId, index, size, partHash);
}

void CAPI_OnUploadHashComplete(const char* partsHash, const char* fileHash) {
    int cbId = GetCurrentUploadCallbackId();
    CallUploadHashCompleteCallback(cbId, partsHash, fileHash);
}

void CAPI_OnUploadID(const char* uploadID) {
    int cbId = GetCurrentUploadCallbackId();
    CallUploadIDCallback(cbId, uploadID);
}

void CAPI_OnUploadPartComplete(int index, long long partSize, const char* partHash) {
    int cbId = GetCurrentUploadCallbackId();
    CallUploadPartCompleteCallback(cbId, index, partSize, partHash);
}

void CAPI_OnUploadComplete(long long fileSize, long long streamSize, long long storageSize) {
    int cbId = GetCurrentUploadCallbackId();
    CallUploadCompleteCallback(cbId, fileSize, streamSize, storageSize);
}

void CAPI_OnUploadFinish(long long size, const char* url, int fileType) {
    int cbId = GetCurrentUploadCallbackId();
    CallUploadFinishCallback(cbId, size, url, fileType);
    // 上传完成后清除当前上传回调 ID
    SetCurrentUploadCallbackId(INVALID_CALLBACK_ID);
}

// 日志上传回调
void CAPI_OnUploadLogProgress(long long current, long long total) {
    // 日志上传回调也需要类似处理，但 SDK 中没有包含 cbId
    // 这里需要使用一个单独的机制来跟踪
}

// 发送进度回调
void CAPI_OnSendMsg(int cbId, int progress) {
    CallSendMsgCallback(cbId, progress);
}

// 连接回调
void CAPI_OnConnConnecting() {
    CallVoidCallback(g_listeners.env, g_listeners.onConnecting);
}

void CAPI_OnConnConnectSuccess() {
    CallVoidCallback(g_listeners.env, g_listeners.onConnectSuccess);
}

void CAPI_OnConnConnectFailed(int cbId, const char* message) {
    CallStringCallback(g_listeners.env, g_listeners.onConnectFailed, message);
}

void CAPI_OnConnKickedOffline() {
    CallVoidCallback(g_listeners.env, g_listeners.onKickedOffline);
}

void CAPI_OnConnUserTokenExpired() {
    CallVoidCallback(g_listeners.env, g_listeners.onUserTokenExpired);
}

void CAPI_OnConnUserTokenInvalid(int cbId, const char* message) {
    CallStringCallback(g_listeners.env, g_listeners.onUserTokenInvalid, message);
}

// 消息回调
void CAPI_OnRecvNewMsg(int cbId, const char* msg) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvNewMsg, msg);
}

void CAPI_OnRecvReceipt(int cbId, const char* receipt) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvReceipt, receipt);
}

void CAPI_OnMsgRevoked(int cbId, const char* msg) {
    CallStringCallback(g_listeners.env, g_listeners.onMsgRevoked, msg);
}

void CAPI_OnRecvOffline(int cbId, const char* msg) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvOffline, msg);
}

void CAPI_OnMsgDeleted(int cbId, const char* msg) {
    CallStringCallback(g_listeners.env, g_listeners.onMsgDeleted, msg);
}

void CAPI_OnRecvOnline(int cbId, const char* msg) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvOnline, msg);
}

// 会话回调
void CAPI_OnConvSyncStart() {
    CallVoidCallback(g_listeners.env, g_listeners.onSyncStart);
}

void CAPI_OnConvSyncFinish() {
    CallVoidCallback(g_listeners.env, g_listeners.onSyncFinish);
}

void CAPI_OnConvSyncProgress(int progress) {
    CallIntCallback(g_listeners.env, g_listeners.onSyncProgress, progress);
}

void CAPI_OnConvSyncFailed(int cbId, const char* err) {
    CallStringCallback(g_listeners.env, g_listeners.onSyncFailed, err);
}

void CAPI_OnConvChanged(int cbId, const char* conv) {
    CallStringCallback(g_listeners.env, g_listeners.onConvChanged, conv);
}

void CAPI_OnNewConv(int cbId, const char* conv) {
    CallStringCallback(g_listeners.env, g_listeners.onNewConv, conv);
}

void CAPI_OnUnreadChanged(int totalUnreadCount) {
    CallIntCallback(g_listeners.env, g_listeners.onUnreadChanged, totalUnreadCount);
}

void CAPI_OnInputStatus(int cbId, const char* status) {
    CallStringCallback(g_listeners.env, g_listeners.onInputStatus, status);
}

// 群组回调
void CAPI_OnGroupJoinedAdd(int cbId, const char* group) {
    CallStringCallback(g_listeners.env, g_listeners.onJoinedAdd, group);
}

void CAPI_OnGroupJoinedDel(int cbId, const char* group) {
    CallStringCallback(g_listeners.env, g_listeners.onJoinedDel, group);
}

void CAPI_OnGroupMemberAdd(int cbId, const char* member) {
    CallStringCallback(g_listeners.env, g_listeners.onMemberAdd, member);
}

void CAPI_OnGroupMemberDel(int cbId, const char* member) {
    CallStringCallback(g_listeners.env, g_listeners.onMemberDel, member);
}

void CAPI_OnGroupAppAdd(int cbId, const char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onAppAdd, application);
}

void CAPI_OnGroupAppDel(int cbId, const char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onAppDel, application);
}

void CAPI_OnGroupInfoChanged(int cbId, const char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onInfoChanged, info);
}

void CAPI_OnGroupDismissed(int cbId, const char* group) {
    CallStringCallback(g_listeners.env, g_listeners.onDismissed, group);
}

void CAPI_OnGroupMemberInfo(int cbId, const char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onMemberInfo, info);
}

void CAPI_OnGroupAppAccept(int cbId, const char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onAppAccept, application);
}

void CAPI_OnGroupAppReject(int cbId, const char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onAppReject, application);
}

// 好友回调
void CAPI_OnFriendAppAdd(int cbId, const char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendAppAdd, application);
}

void CAPI_OnFriendAppDel(int cbId, const char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendAppDel, application);
}

void CAPI_OnFriendAppAccept(int cbId, const char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendAppAccept, application);
}

void CAPI_OnFriendAppReject(int cbId, const char* application) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendAppReject, application);
}

void CAPI_OnFriendAdd(int cbId, const char* frient) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendAdd, frient);
}

void CAPI_OnFriendDel(int cbId, const char* frient) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendDel, frient);
}

void CAPI_OnFriendInfo(int cbId, const char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onFriendInfo, info);
}

void CAPI_OnBlackAdd(int cbId, const char* black) {
    CallStringCallback(g_listeners.env, g_listeners.onBlackAdd, black);
}

void CAPI_OnBlackDel(int cbId, const char* black) {
    CallStringCallback(g_listeners.env, g_listeners.onBlackDel, black);
}

// 用户回调
void CAPI_OnUserSelfInfoUpdated(int cbId, const char* userInfo) {
    CallStringCallback(g_listeners.env, g_listeners.onSelfInfo, userInfo);
}

void CAPI_OnUserStatusChanged(int cbId, const char* status) {
    CallStringCallback(g_listeners.env, g_listeners.onUserStatus, status);
}

// 信令回调
void CAPI_OnSignalingReceiveNewInvitation(int cbId, const char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onReceiveNewInvitation, invitation);
}

void CAPI_OnSignalingInviteeAccepted(int cbId, const char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInviteeAccepted, invitation);
}

void CAPI_OnSignalingInviteeAcceptedByOtherDevice(int cbId, const char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInviteeAcceptedByOtherDevice, invitation);
}

void CAPI_OnSignalingInviteeRejected(int cbId, const char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInviteeRejected, invitation);
}

void CAPI_OnSignalingInviteeRejectedByOtherDevice(int cbId, const char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInviteeRejectedByOtherDevice, invitation);
}

void CAPI_OnSignalingInvitationCancelled(int cbId, const char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInvitationCancelled, invitation);
}

void CAPI_OnSignalingInvitationTimeout(int cbId, const char* invitation) {
    CallStringCallback(g_listeners.env, g_listeners.onInvitationTimeout, invitation);
}

void CAPI_OnSignalingHangUp(int cbId, const char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onHangUp, info);
}

void CAPI_OnSignalingRoomParticipantConnected(int cbId, const char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onRoomParticipantConnected, info);
}

void CAPI_OnSignalingRoomParticipantDisconnected(int cbId, const char* info) {
    CallStringCallback(g_listeners.env, g_listeners.onRoomParticipantDisconnected, info);
}

// 自定义业务回调
void CAPI_OnRecvCustomBusinessMessage(int cbId, const char* message) {
    CallStringCallback(g_listeners.env, g_listeners.onRecvCustomBusinessMessage, message);
}

// 消息 KV 信息回调
void CAPI_OnMessageKvInfoChanged(int cbId, const char* kvInfo) {
    CallStringCallback(g_listeners.env, g_listeners.onMessageKvInfoChanged, kvInfo);
}

}