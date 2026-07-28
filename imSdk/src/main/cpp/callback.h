#ifndef OPENIM_CALLBACK_H
#define OPENIM_CALLBACK_H

#include <napi/native_api.h>
#include <string>
#include <functional>

// ============================================================
// 常量定义
// ============================================================
#define CB_MAX 64
#define INVALID_CALLBACK_ID (-1)

// ============================================================
// 回调类型定义
// ============================================================

// Base 回调
typedef void (*BaseSuccessCb)(int callbackID, const char* data);
typedef void (*BaseErrorCb)(int callbackID, int code, const char* message);

// 上传文件回调（SDK UploadFileCallback 接口，8个方法，第一个参数为 cbId）
typedef void (*UploadOpenCb)(int cbId, long long fileSize);
typedef void (*UploadPartSizeCb)(int cbId, long long partSize, int partNumber);
typedef void (*UploadHashProgressCb)(int cbId, int index, long long size, const char* partHash);
typedef void (*UploadHashCompleteCb)(int cbId, const char* partsHash, const char* fileHash);
typedef void (*UploadIDCb)(int cbId, const char* uploadID);
typedef void (*UploadPartCompleteCb)(int cbId, int index, long long partSize, const char* partHash);
typedef void (*UploadCompleteCb)(int cbId, long long fileSize, long long streamSize, long long storageSize);
typedef void (*UploadFinishCb)(int cbId, long long size, const char* url, int fileType);

// 日志上传回调（第一个参数为 cbId）
typedef void (*UploadLogProgressCb)(int cbId, long long current, long long total);

// 发送进度回调（第一个参数为 cbId）
typedef void (*SendMsgWithIDCb)(int cbId, int progress);

// 连接回调
typedef void (*ConnNoMsgCb)();
typedef void (*ConnWithMsgCb)(int callbackID, const char* message);

// 消息回调
typedef void (*InfoCb)(int callbackID, const char* data);
typedef void (*ReceiptCb)(int callbackID, const char* data);
typedef void (*DeletedCb)(int callbackID, const char* msg);
typedef void (*UnreadCb)(int totalUnreadCount);

// 会话回调
typedef void (*SyncBoolCb)();
typedef void (*SyncProgressCb)(int progress);

// 群组回调
typedef void (*SignalingCb)(int callbackID, const char* data);

// 自定义业务回调
typedef void (*CustomBusinessCb)(int callbackID, const char* message);

// 消息 KV 信息回调
typedef void (*MsgKvInfoCb)(int callbackID, const char* kvInfo);

// ============================================================
// Base 回调上下文
// ============================================================
struct BaseCallbackContext {
    napi_ref onSuccessRef;
    napi_ref onErrorRef;
    napi_env env;
    bool isValid;
};

// ============================================================
// 上传文件回调上下文（SDK UploadFileCallback 接口）
// ============================================================
struct UploadCallbackContext {
    napi_ref onOpenRef;
    napi_ref onPartSizeRef;
    napi_ref onHashPartProgressRef;
    napi_ref onHashPartCompleteRef;
    napi_ref onUploadIDRef;
    napi_ref onUploadPartCompleteRef;
    napi_ref onUploadCompleteRef;
    napi_ref onCompleteRef;
    napi_env env;
    bool isValid;
};

// ============================================================
// 日志上传回调上下文
// ============================================================
struct UploadLogCallbackContext {
    napi_ref onProgressRef;
    napi_env env;
    bool isValid;
};

// ============================================================
// 发送消息回调上下文（包含 Base + OnProgress）
// ============================================================
struct SendMsgCallbackContext {
    napi_ref onSuccessRef;
    napi_ref onErrorRef;
    napi_ref onProgressRef;
    napi_env env;
    bool isValid;
};

// ============================================================
// 全局变量声明
// ============================================================
extern BaseCallbackContext g_baseCallbacks[CB_MAX];
extern UploadCallbackContext g_upload_callbacks[CB_MAX];
extern UploadLogCallbackContext g_uploadLog_callbacks[CB_MAX];
extern SendMsgCallbackContext g_sendMsg_callbacks[CB_MAX];

// ============================================================
// 工具函数声明
// ============================================================

// 分配回调 ID
int AllocateCallbackId();

// 释放回调 ID
void FreeCallbackId(int cbId);

// 获取回调上下文
BaseCallbackContext* GetBaseCallback(int cbId);
UploadCallbackContext* GetUploadCallback(int cbId);
UploadLogCallbackContext* GetUploadLogCallback(int cbId);
SendMsgCallbackContext* GetSendMsgCallback(int cbId);

// ============================================================
// Base 回调封装声明
// ============================================================

// 存储 Base 回调（分开传入 onSuccess 和 onError）
int StoreBaseCallback(napi_env env, napi_value onSuccess, napi_value onError);

// 存储 Base 回调（合并为对象传入 callback.onSuccess, callback.onError）
int StoreBaseCallback(napi_env env, napi_value callback);

// 删除 Base 回调
void DeleteBaseCallback(int cbId);

// ============================================================
// 上传文件回调封装声明
// ============================================================

// 存储上传文件回调（SDK UploadFileCallback 接口）
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
);

// 删除上传文件回调
void DeleteUploadCallbacks(int cbId);

// ============================================================
// 日志上传回调封装声明
// ============================================================

// 存储日志上传回调
int StoreUploadLogCallback(napi_env env, napi_value onProgress);

// 删除日志上传回调
void DeleteUploadLogCallback(int cbId);

// ============================================================
// 发送消息回调封装声明（包含 Base + OnProgress）
// ============================================================

// 存储发送消息回调（分开传入 onSuccess, onError, onProgress）
int StoreSendMsgCallback(napi_env env, napi_value onSuccess, napi_value onError, napi_value onProgress);

// 存储发送消息回调（合并为对象传入 callback.onSuccess, callback.onError, callback.onProgress）
int StoreSendMsgCallback(napi_env env, napi_value callback);

// 删除发送消息回调
void DeleteSendMsgCallback(int cbId);

// ============================================================
// Listener 回调封装声明
// ============================================================

// 连接监听器
int StoreConnListener(
    napi_env env,
    napi_value onConnecting,
    napi_value onConnectSuccess,
    napi_value onConnectFailed,
    napi_value onKickedOffline,
    napi_value onUserTokenExpired,
    napi_value onUserTokenInvalid
);
void DeleteConnListener();

// 消息监听器
int StoreMsgListener(
    napi_env env,
    napi_value onRecvNewMsg,
    napi_value onRecvReceipt,
    napi_value onMsgRevoked,
    napi_value onRecvOffline,
    napi_value onMsgDeleted,
    napi_value onRecvOnline
);
void DeleteMsgListener();

// 会话监听器
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
);
void DeleteConvListener();

// 群组监听器
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
);
void DeleteGroupListener();

// 好友监听器
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
);
void DeleteFriendListener();

// 用户监听器
int StoreUserListener(napi_env env, napi_value onSelfInfo, napi_value onUserStatus);
void DeleteUserListener();

// 信令监听器
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
);
void DeleteSignalingListener();

// 自定义业务监听器
int StoreCustomBusinessListener(napi_env env, napi_value onRecvCustomBusinessMessage);
void DeleteCustomBusinessListener();

// 消息 KV 信息监听器
int StoreMsgKvInfoListener(napi_env env, napi_value onMessageKvInfoChanged);
void DeleteMsgKvInfoListener();

// ============================================================
// 清理所有回调
// ============================================================
void DeleteAllCallbacks();

// ============================================================
// JavaScript 回调调用辅助函数
// ============================================================

// 调用无参数回调
void CallVoidCallback(napi_env env, napi_ref callbackRef);

// 调用单个参数回调（int）
void CallIntCallback(napi_env env, napi_ref callbackRef, int value);

// 调用单个参数回调（long long）
void CallLongLongCallback(napi_env env, napi_ref callbackRef, long long value);

// 调用字符串参数回调
void CallStringCallback(napi_env env, napi_ref callbackRef, const char* value);

// 调用 Base 成功回调
void CallBaseSuccessCallback(int cbId, const char* data);

// 调用 Base 错误回调
void CallBaseErrorCallback(int cbId, int code, const char* message);

// 调用上传文件回调
void CallUploadOpenCallback(int cbId, long long fileSize);
void CallUploadPartSizeCallback(int cbId, long long partSize, int partNumber);
void CallUploadHashProgressCallback(int cbId, int index, long long size, const char* partHash);
void CallUploadHashCompleteCallback(int cbId, const char* partsHash, const char* fileHash);
void CallUploadIDCallback(int cbId, const char* uploadID);
void CallUploadPartCompleteCallback(int cbId, int index, long long partSize, const char* partHash);
void CallUploadCompleteCallback(int cbId, long long fileSize, long long streamSize, long long storageSize);
void CallUploadFinishCallback(int cbId, long long size, const char* url, int fileType);

// 调用日志上传回调
void CallUploadLogProgressCallback(int cbId, long long current, long long total);

// 调用发送进度回调
void CallSendMsgCallback(int cbId, int progress);

#endif // OPENIM_CALLBACK_H
