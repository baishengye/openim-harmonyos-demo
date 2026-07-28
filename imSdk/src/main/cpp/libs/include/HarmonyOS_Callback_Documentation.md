# OpenIM SDK Core - HarmonyOS CGO 回调机制文档

## 概述

本文档说明如何将 NAPI/ArkUI 的回调接口转换为 HarmonyOS 平台上 CGO 可使用的函数指针。

---

## 1. 回调机制架构

### 1.1 回调分类

SDK 中的回调分为三类：

| 类型 | 说明 | 注册方式 | 使用索引 |
|------|------|----------|----------|
| **Listener 回调** | SDK 事件监听器（连接、消息、群组等） | 全局注册一次 | 固定使用 index 0 |
| **Base 回调** | 操作成功/失败的通用回调 | 按需注册 | 动态 callbackID (1-63) |
| **特定业务回调** | 上传进度、发送进度等 | 按需注册 | 动态 callbackID (1-63) |

### 1.2 回调存储结构

```c
#define CB_MAX 64

// Listener 回调 - 固定使用 gXxx[0]
static InfoCb gRecvNewMsg[CB_MAX];  // gRecvNewMsg[0] 有效

// Base 回调 - 动态使用 gBaseSuccess[1-63], gBaseError[1-63]
static BaseSuccessCb gBaseSuccess[CB_MAX];
static BaseErrorCb gBaseError[CB_MAX];

// 特定业务回调
static UploadOpenCb gUploadOpen[CB_MAX];
static SendProgressWithIDCb gSendProgressWithID[CB_MAX];
```

---

## 2. 回调类型定义

### 2.1 Base 回调类型（OnSuccess / OnError）

```c
// 成功回调：callbackID + JSON 数据
typedef void (*BaseSuccessCb)(int callbackID, char* data);

// 失败回调：callbackID + 错误码 + 错误信息
typedef void (*BaseErrorCb)(int callbackID, int code, char* message);
```

### 2.2 上传文件回调类型

```c
// 文件开始上传
typedef void (*UploadOpenCb)(long long fileSize);

// 分片大小确定
typedef void (*UploadPartSizeCb)(long long partSize, int partNumber);

// 文件分片 Hash 进度
typedef void (*UploadHashProgressCb)(int index, long long size, char* partHash);

// 文件分片 Hash 完成
typedef void (*UploadHashCompleteCb)(char* partsHash, char* fileHash);

// 获取上传 ID
typedef void (*UploadIDCb)(char* uploadID);

// 分片上传完成
typedef void (*UploadPartCompleteCb)(int index, long long partSize, char* partHash);

// 所有分片上传完成
typedef void (*UploadCompleteCb)(long long fileSize, long long streamSize, long long storageSize);

// 上传完成（获取 URL）
typedef void (*UploadFinishCb)(long long size, char* url, int fileType);

// 上传进度
typedef void (*UploadProgressCb)(long long current, long long total);
```

### 2.3 发送消息进度回调

```c
// 带 ID 的发送进度回调：callbackID + 进度值
typedef void (*SendProgressWithIDCb)(int callbackID, int progress);
```

### 2.4 日志上传进度回调

```c
typedef void (*UploadLogProgressCb)(long long current, long long total);
```

---

## 3. 注册与注销函数

### 3.1 Base 回调注册/注销

```c
// 注册 Base 回调（包含 OnSuccess 和 OnError）
extern void RegisterBaseCallback(int baseCallbackID, int onSuccess, int onError);

// 注销 Base 回调
extern void UnregisterBaseCallback(int baseCallbackID);
```

### 3.2 上传文件回调注册/注销

```c
// 注册上传文件回调（10 个回调一次性注册）
extern void RegisterUploadFileCallback(
    int baseCallbackID,
    int onOpen,                    // UploadOpenCb
    int onPartSize,                // UploadPartSizeCb
    int onHashPartProgress,        // UploadHashProgressCb
    int onHashPartComplete,        // UploadHashCompleteCb
    int onUploadID,               // UploadIDCb
    int onUploadPartComplete,     // UploadPartCompleteCb
    int onUploadComplete,         // UploadCompleteCb
    int onComplete,               // UploadFinishCb
    int onUploadProgress          // UploadProgressCb
);

// 注销上传文件回调
extern void UnregisterUploadFileCallback(int baseCallbackID);
```

### 3.3 发送进度回调注册/注销

```c
// 注册发送进度回调
extern void RegisterSendProgress(int callbackID, int onProgress);

// 注销发送进度回调
extern void UnregisterSendProgress(int baseCallbackID);
```

### 3.4 日志上传回调注册/注销

```c
// 注册日志上传进度回调
extern void RegisterUploadLogProgress(int baseCallbackID, int onProgress);

// 注销日志上传进度回调
extern void UnregisterUploadLogProgress(int baseCallbackID);
```

### 3.5 Listener 回调注册（全局，无需注销）

```c
extern void RegisterConnListener(int onConnecting, int onConnectSuccess, 
    int onConnectFailed, int onKickedOffline, int onUserTokenExpired, int onUserTokenInvalid);

extern void RegisterMsgListener(int onRecvNewMsg, int onRecvReceipt, 
    int onMsgRevoked, int onRecvOffline, int onMsgDeleted, int onRecvOnline);

extern void RegisterConvListener(int onSyncStart, int onSyncFinish, 
    int onSyncProgress, int onSyncFailed, int onConvChanged, int onNewConv, 
    int onUnreadChanged, int onInputStatus);

extern void RegisterGroupListener(int onJoinedAdd, int onJoinedDel, 
    int onMemberAdd, int onMemberDel, int onAppAdd, int onAppDel, 
    int onInfoChanged, int onDismissed, int onMemberInfo, 
    int onAppAccept, int onAppReject);

extern void RegisterFriendListener(int onAppAdd, int onAppDel, 
    int onAppAccept, int onAppReject, int onFriendAdd, int onFriendDel, 
    int onFriendInfo, int onBlackAdd, int onBlackDel);

extern void RegisterUserListener(int onSelfInfo, int onUserStatus);

extern void RegisterSignalingListener(int onReceiveNewInvitation, 
    int onInviteeAccepted, int onInviteeAcceptedByOtherDevice, 
    int onInviteeRejected, int onInviteeRejectedByOtherDevice, 
    int onInvitationCancelled, int onInvitationTimeout, 
    int onHangUp, int onRoomParticipantConnected, 
    int onRoomParticipantDisconnected);
```

---

## 4. SDK 函数签名中的 Callback 参数

### 4.1 需要 Base 回调的函数

```c
// baseCallbackID: 成功/失败回调的索引
extern void Login(int baseCallbackID, char* uid, char* token, char* operationID);
extern void Logout(int baseCallbackID, char* operationID);
extern void GetAllConversationList(int baseCallbackID, char* operationID);
extern void CreateGroup(int baseCallbackID, char* operationID, char* groupInfo);
extern void JoinGroup(int baseCallbackID, char* operationID, char* groupID, 
    char* reqMsg, int joinSource, char* ex);
// ... 更多函数参见 libopenimsdk.h
```

### 4.2 需要双回调的函数

```c
// baseCallbackID: 成功/失败回调索引
// uploadCallbackID: 上传进度回调索引
extern void UploadFile(int baseCallbackID, int uploadCallbackID, 
    char* operationID, char* reqData);

// baseCallbackID: 成功/失败回调索引
// sendReceiptCallbackID: 发送进度回调索引
extern void SendMessage(int baseCallbackID, int sendReceiptCallbackID, 
    char* message, char* recvID, char* groupID, char* offlinePushInfo, 
    char* operationID, int isOnlineOnly);

extern void SendMessageNotOss(int baseCallbackID, int sendReceiptCallbackID, 
    char* message, char* recvID, char* groupID, char* offlinePushInfo, 
    char* operationID, int isOnlineOnly);

// baseCallbackID: 成功/失败回调索引
// uploadLogsCallbackID: 日志上传进度回调索引
extern void UploadLogs(int baseCallbackID, int uploadLogsCallbackID, 
    char* operationID, int line, char* ex);
```

---

## 5. 使用示例

### 5.1 完整流程示例：登录

```c
#include "libopenimsdk.h"
#include <stdio.h>
#include <string.h>

// 定义全局变量存储回调 ID
static int g_loginCallbackID = -1;

// ==================== Base 回调实现 ====================

void onLoginSuccess(int callbackID, char* data) {
    printf("[Login] Success! callbackID=%d, data=%s\n", callbackID, data);
    // 在此处理登录成功逻辑
}

void onLoginError(int callbackID, int code, char* message) {
    printf("[Login] Error! callbackID=%d, code=%d, message=%s\n", 
           callbackID, code, message);
    // 在此处理登录失败逻辑
}

// ==================== 完整登录流程 ====================

void doLogin() {
    const char* uid = "user123";
    const char* token = "your_token_here";
    const char* operationID = "login_001";

    // Step 1: 注册 Base 回调（使用动态 ID）
    g_loginCallbackID = 1;  // 实际应用中应该动态分配 1-63 的空闲 ID
    RegisterBaseCallback(
        g_loginCallbackID,          // callbackID
        (int)onLoginSuccess,        // onSuccess 函数指针
        (int)onLoginError           // onError 函数指针
    );

    // Step 2: 调用登录函数
    Login(g_loginCallbackID, uid, token, operationID);

    // Step 3: 回调触发后，注销回调
    // 注意：通常在收到回调后或超时后注销
    // UnregisterBaseCallback(g_loginCallbackID);
    // g_loginCallbackID = -1;
}
```

### 5.2 完整流程示例：上传文件

```c
#include "libopenimsdk.h"
#include <stdio.h>

static int g_uploadCallbackID = -1;

// ==================== Base 回调 ====================

void onUploadSuccess(int callbackID, char* data) {
    printf("[Upload] Success! data=%s\n", data);
}

void onUploadError(int callbackID, int code, char* message) {
    printf("[Upload] Error! code=%d, message=%s\n", code, message);
}

// ==================== 上传进度回调 ====================

void onUploadOpen(long long fileSize) {
    printf("[Upload] Open: fileSize=%lld\n", fileSize);
}

void onUploadPartSize(long long partSize, int partNumber) {
    printf("[Upload] PartSize: partSize=%lld, parts=%d\n", partSize, partNumber);
}

void onUploadHashProgress(int index, long long size, char* partHash) {
    printf("[Upload] HashProgress: index=%d, size=%lld\n", index, size);
}

void onUploadHashComplete(char* partsHash, char* fileHash) {
    printf("[Upload] HashComplete: partsHash=%s, fileHash=%s\n", partsHash, fileHash);
}

void onUploadID(char* uploadID) {
    printf("[Upload] UploadID: %s\n", uploadID);
}

void onUploadPartComplete(int index, long long partSize, char* partHash) {
    printf("[Upload] PartComplete: index=%d\n", index);
}

void onUploadComplete(long long fileSize, long long streamSize, long long storageSize) {
    printf("[Upload] Complete: fileSize=%lld, streamSize=%lld, storageSize=%lld\n",
           fileSize, streamSize, storageSize);
}

void onUploadFinish(long long size, char* url, int fileType) {
    printf("[Upload] Finish: size=%lld, url=%s, type=%d\n", size, url, fileType);
    // 保存 url 用于后续业务
}

void onUploadProgress(long long current, long long total) {
    int percent = (int)((current * 100) / total);
    printf("[Upload] Progress: %d%% (%lld/%lld)\n", percent, current, total);
}

// ==================== 完整上传流程 ====================

void doUploadFile() {
    const char* operationID = "upload_001";
    const char* reqData = "{\"filePath\": \"/data/test.jpg\"}";

    // Step 1: 分配回调 ID
    g_uploadCallbackID = 2;

    // Step 2: 注册 Base 回调
    RegisterBaseCallback(
        g_uploadCallbackID,
        (int)onUploadSuccess,
        (int)onUploadError
    );

    // Step 3: 注册上传进度回调
    RegisterUploadFileCallback(
        g_uploadCallbackID,        // callbackID
        (int)onUploadOpen,
        (int)onUploadPartSize,
        (int)onUploadHashProgress,
        (int)onUploadHashComplete,
        (int)onUploadID,
        (int)onUploadPartComplete,
        (int)onUploadComplete,
        (int)onUploadFinish,
        (int)onUploadProgress
    );

    // Step 4: 调用上传函数（传入 baseCallbackID 和 uploadCallbackID）
    UploadFile(g_uploadCallbackID, g_uploadCallbackID, operationID, reqData);

    // Step 5: 上传完成后注销回调
    // UnregisterUploadFileCallback(g_uploadCallbackID);
    // UnregisterBaseCallback(g_uploadCallbackID);
}
```

### 5.3 完整流程示例：发送消息

```c
#include "libopenimsdk.h"
#include <stdio.h>

static int g_sendCallbackID = -1;

// ==================== Base 回调 ====================

void onSendSuccess(int callbackID, char* data) {
    printf("[Send] Success! data=%s\n", data);
}

void onSendError(int callbackID, int code, char* message) {
    printf("[Send] Error! code=%d, message=%s\n", code, message);
}

// ==================== 发送进度回调 ====================

void onSendProgress(int callbackID, int progress) {
    printf("[Send] Progress: callbackID=%d, progress=%d%%\n", callbackID, progress);
}

// ==================== 完整发送流程 ====================

void doSendMessage() {
    const char* operationID = "send_001";
    const char* message = "{\"msg\":\"hello\"}";
    const char* recvID = "user456";
    const char* groupID = "";  // 单聊为空，群聊为群ID
    const char* offlinePushInfo = "{}";
    int isOnlineOnly = 0;

    // Step 1: 分配回调 ID
    g_sendCallbackID = 3;

    // Step 2: 注册 Base 回调
    RegisterBaseCallback(
        g_sendCallbackID,
        (int)onSendSuccess,
        (int)onSendError
    );

    // Step 3: 注册发送进度回调
    RegisterSendProgress(g_sendCallbackID, (int)onSendProgress);

    // Step 4: 调用发送函数
    SendMessage(
        g_sendCallbackID,    // baseCallbackID - 成功/失败回调
        g_sendCallbackID,    // sendReceiptCallbackID - 发送进度回调
        message, recvID, groupID, offlinePushInfo, operationID, isOnlineOnly
    );

    // Step 5: 发送完成后注销回调
    // UnregisterSendProgress(g_sendCallbackID);
    // UnregisterBaseCallback(g_sendCallbackID);
}
```

### 5.4 Listener 回调注册（一次性设置）

```c
#include "libopenimsdk.h"

// ==================== 连接状态回调 ====================

void onConnecting(int value) {
    printf("[Conn] Connecting...\n");
}

void onConnectSuccess(int value) {
    printf("[Conn] Connected!\n");
}

void onConnectFailed(int value, char* message) {
    printf("[Conn] Failed: %s\n", message);
}

void onKickedOffline(int value) {
    printf("[Conn] Kicked offline\n");
}

void onUserTokenExpired(int value) {
    printf("[Conn] Token expired\n");
}

void onUserTokenInvalid(int value, char* message) {
    printf("[Conn] Token invalid: %s\n", message);
}

// ==================== 消息接收回调 ====================

void onRecvNewMsg(char* msg) {
    printf("[Msg] New message: %s\n", msg);
}

void onRecvReceipt(char* receipt) {
    printf("[Msg] Receipt: %s\n", receipt);
}

void onMsgRevoked(char* msg) {
    printf("[Msg] Revoked: %s\n", msg);
}

void onRecvOffline(char* msg) {
    printf("[Msg] Offline message: %s\n", msg);
}

void onMsgDeleted(char* msg) {
    printf("[Msg] Deleted: %s\n", msg);
}

void onRecvOnline(char* msg) {
    printf("[Msg] Online message: %s\n", msg);
}

// ==================== 注册所有 Listener ====================

void setupListeners() {
    // 连接状态监听
    RegisterConnListener(
        (int)onConnecting,
        (int)onConnectSuccess,
        (int)onConnectFailed,
        (int)onKickedOffline,
        (int)onUserTokenExpired,
        (int)onUserTokenInvalid
    );

    // 消息监听
    RegisterMsgListener(
        (int)onRecvNewMsg,
        (int)onRecvReceipt,
        (int)onMsgRevoked,
        (int)onRecvOffline,
        (int)onMsgDeleted,
        (int)onRecvOnline
    );

    // 注意：Listener 回调使用 index 0，无需注销
    // 如果需要注销，使用对应的 UnregisterXxxListener() 函数
}
```

---

## 6. 回调 ID 管理

### 6.1 ID 分配规则

```
Index 0: 保留给全局 Listener 回调
Index 1-63: 可用于 Base 回调和特定业务回调
```

### 6.2 回调 ID 命名对照表

| SDK 函数参数 | 说明 | 对应回调类型 |
|--------------|------|--------------|
| `baseCallbackID` | 成功/失败回调索引 | `RegisterBaseCallback` |
| `uploadCallbackID` | 文件上传进度回调索引 | `RegisterUploadFileCallback` |
| `sendReceiptCallbackID` | 消息发送进度回调索引 | `RegisterSendProgress` |
| `uploadLogsCallbackID` | 日志上传进度回调索引 | `RegisterUploadLogProgress` |

### 6.3 推荐使用模式

```c
// 模式 1: 同一 ID 用于 Base + 特定回调
int callbackID = allocateCallbackID();
RegisterBaseCallback(callbackID, onSuccess, onError);
RegisterUploadFileCallback(callbackID, ...);
UploadFile(callbackID, callbackID, operationID, reqData);
// 完成后注销
UnregisterUploadFileCallback(callbackID);
UnregisterBaseCallback(callbackID);

// 模式 2: 不同 ID 分别使用
int baseID = allocateCallbackID();
int uploadID = allocateCallbackID();
RegisterBaseCallback(baseID, onSuccess, onError);
RegisterUploadFileCallback(uploadID, ...);
UploadFile(baseID, uploadID, operationID, reqData);
```

---

## 7. 注意事项

### 7.1 回调必须显式注销

**以下回调类型用完必须调用对应的 Unregister 函数注销：**

| 回调类型 | 注销函数 |
|----------|----------|
| Base 回调 | `UnregisterBaseCallback(baseCallbackID)` |
| 上传文件回调 | `UnregisterUploadFileCallback(baseCallbackID)` |
| 发送进度回调 | `UnregisterSendProgress(baseCallbackID)` |
| 日志上传回调 | `UnregisterUploadLogProgress(baseCallbackID)` |

### 7.2 Listener 回调的注册时机

- Listener 回调在 SDK 初始化后注册一次即可
- 建议在 `InitSDK` 成功后立即注册所有 Listener
- 如果需要更换 Listener 回调，先调用 `UnregisterXxxListener()` 再重新注册

### 7.3 线程安全

- 回调在 Go 协程中触发
- 确保回调实现是线程安全的
- 建议在回调中使用队列机制，将事件投递到主线程处理

### 7.4 内存管理

- NAPI 层传递的字符串 `char*` 在回调完成后仍然有效
- 如需持久化保存，请在回调中复制字符串内容
- 使用 `FreeString()` 释放 SDK 返回的字符串

---

## 8. 错误码参考

```c
// 通用错误码（BaseErrorCb 的 code 参数）
#define ERR_OK                    0      // 成功
#define ERR_FAILED               10001   // 失败
#define ERR_TIMEOUT              10002   // 超时
#define ERR_NETWORK              10003   // 网络错误
#define ERR_PARAM                10004   // 参数错误
#define ERR_TOKEN_EXPIRED        20001   // Token 过期
#define ERR_TOKEN_INVALID        20002   // Token 无效
```

---

## 9. NAPI 完整实现示例

以下是一个完整的 HarmonyOS NAPI 集成示例，展示如何实现 `StoreBaseCallback` 和调用 SDK 函数。

### 9.1 TypeScript 接口定义

```typescript
// OpenIMSDK.ets
export interface BaseCallback {
  onError(errCode: number, errMsg: string): void;
  onSuccess(data: string): void;
}

export function login(baseCallback: BaseCallback, operationID: string, userID: string, token: string): void;
export function logout(baseCallback: BaseCallback, operationID: string): void;
```

### 9.2 NAPI 模块实现

```cpp
// openimsdk_napi.cpp
#include <string>
#include <memory>
#include "libopenimsdk.h"

// 回调上下文结构体
struct CallbackContext {
    napi_ref successCallback;
    napi_ref errorCallback;
    napi_env env;
};

// C 回调函数实现 - 成功回调
void CAPI_OnSuccess(int cbId, char* data) {
    CallbackContext* ctx = (CallbackContext*)GetCallbackData(cbId);
    if (!ctx) return;
    
    napi_env env = ctx->env;
    napi_value jsData;
    napi_create_string_utf8(env, data ? data : "", NAPI_AUTO_LENGTH, &jsData);
    
    // 调用 JS 的 onSuccess
    napi_value callback;
    napi_get_reference_value(env, ctx->successCallback, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value result;
    napi_call_function(env, global, callback, 1, &jsData, &result);
    
    // 自动释放回调
    UnregisterBaseCallback(cbId);
}

// C 回调函数实现 - 错误回调
void CAPI_OnError(int cbId, int errCode, char* errMsg) {
    CallbackContext* ctx = (CallbackContext*)GetCallbackData(cbId);
    if (!ctx) return;
    
    napi_env env = ctx->env;
    napi_value jsErrCode;
    napi_value jsErrMsg;
    napi_create_int32(env, errCode, &jsErrCode);
    napi_create_string_utf8(env, errMsg ? errMsg : "", NAPI_AUTO_LENGTH, &jsErrMsg);
    
    // 调用 JS 的 onError
    napi_value callback;
    napi_get_reference_value(env, ctx->errorCallback, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[2] = {jsErrCode, jsErrMsg};
    napi_value result;
    napi_call_function(env, global, callback, 2, argv, &result);
    
    // 自动释放回调
    UnregisterBaseCallback(cbId);
}

// 注册回调到 SDK
int StoreBaseCallback(napi_env env, napi_value callback) {
    // 创建上下文
    CallbackContext* ctx = new CallbackContext();
    ctx->env = env;
    
    // 提取 onSuccess 和 onError
    napi_value onSuccess, onError;
    napi_get_named_property(env, callback, "onSuccess", &onSuccess);
    napi_get_named_property(env, callback, "onError", &onError);
    
    // 创建 JS 引用
    napi_create_reference(env, onSuccess, 1, &ctx->successCallback);
    napi_create_reference(env, onError, 1, &ctx->errorCallback);
    
    // 注册到 SDK，分配回调 ID
    int cbId = RegisterBaseCallback((void*)ctx, CAPI_OnSuccess, CAPI_OnError);
    return cbId;
}

// login 函数实现
napi_value Login(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value argv[4];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    // 存储回调
    int cbId = StoreBaseCallback(env, argv[0]);  // 回调完成后自动释放
    
    // 获取参数
    char operationID[64], userID[64], token[256];
    get_string(env, argv[1], operationID, 64);
    get_string(env, argv[2], userID, 64);
    get_string(env, argv[3], token, 256);
    
    // 调用 SDK
    Login(cbId, userID, token, operationID);
    
    return nullptr;
}

// logout 函数实现
napi_value Logout(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value argv[2];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    int cbId = StoreBaseCallback(env, argv[0]);
    
    char operationID[64];
    get_string(env, argv[1], operationID, 64);
    
    Logout(cbId, operationID);
    
    return nullptr;
}
```

### 9.3 带上传进度的 UploadFile 示例

```cpp
// upload_progress_callback.h
struct UploadProgressContext {
    napi_ref progressCallback;  // 进度回调
    napi_ref baseCallback;      // 完成回调（成功/失败）
    napi_env env;
};

// C 进度回调 - 每次切片上传完成时触发
void CAPI_OnUploadProgress(int cbId, char* fileHash, int current, int total, int speed) {
    UploadProgressContext* ctx = (UploadProgressContext*)GetCallbackData(cbId);
    if (!ctx) return;
    
    napi_env env = ctx->env;
    
    napi_value jsFileHash, jsCurrent, jsTotal, jsSpeed;
    napi_create_string_utf8(env, fileHash, NAPI_AUTO_LENGTH, &jsFileHash);
    napi_create_int32(env, current, &jsCurrent);
    napi_create_int32(env, total, &jsTotal);
    napi_create_int32(env, speed, &jsSpeed);
    
    // 构建进度对象
    napi_value progressObj;
    napi_create_object(env, &progressObj);
    napi_set_named_property(env, progressObj, "fileHash", jsFileHash);
    napi_set_named_property(env, progressObj, "current", jsCurrent);
    napi_set_named_property(env, progressObj, "total", jsTotal);
    napi_set_named_property(env, progressObj, "speed", jsSpeed);
    
    // 调用 JS 的 onProgress
    napi_value callback;
    napi_get_reference_value(env, ctx->progressCallback, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value result;
    napi_call_function(env, global, callback, 1, &progressObj, &result);
}

// C 成功回调 - 上传完成时触发
void CAPI_OnUploadSuccess(int cbId, char* data) {
    UploadProgressContext* ctx = (UploadProgressContext*)GetCallbackData(cbId);
    if (!ctx) return;
    
    napi_env env = ctx->env;
    
    // 调用 baseCallback 的 onSuccess
    napi_value baseCb;
    napi_get_reference_value(env, ctx->baseCallback, &baseCb);
    
    napi_value jsData;
    napi_create_string_utf8(env, data, NAPI_AUTO_LENGTH, &jsData);
    
    napi_value onSuccess;
    napi_get_named_property(env, baseCb, "onSuccess", &onSuccess);
    
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value result;
    napi_call_function(env, global, onSuccess, 1, &jsData, &result);
    
    // 释放上传回调（进度回调ID和base回调ID）
    UnregisterUploadFileCallback(cbId);
    UnregisterBaseCallback(ctx->baseCallbackId);
}

// C 错误回调
void CAPI_OnUploadError(int cbId, int errCode, char* errMsg) {
    UploadProgressContext* ctx = (UploadProgressContext*)GetCallbackData(cbId);
    if (!ctx) return;
    
    napi_env env = ctx->env;
    
    napi_value baseCb;
    napi_get_reference_value(env, ctx->baseCallback, &baseCb);
    
    napi_value jsErrCode, jsErrMsg;
    napi_create_int32(env, errCode, &jsErrCode);
    napi_create_string_utf8(env, errMsg, NAPI_AUTO_LENGTH, &jsErrMsg);
    
    napi_value onError;
    napi_get_named_property(env, baseCb, "onError", &onError);
    
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[2] = {jsErrCode, jsErrMsg};
    napi_value result;
    napi_call_function(env, global, onError, 2, argv, &result);
    
    // 释放回调
    UnregisterUploadFileCallback(cbId);
    UnregisterBaseCallback(ctx->baseCallbackId);
}

// 注册上传文件回调
int StoreUploadFileCallback(napi_env env, napi_value baseCallback, napi_value progressCallback) {
    UploadProgressContext* ctx = new UploadProgressContext();
    ctx->env = env;
    
    // 存储 baseCallback 引用
    napi_create_reference(env, baseCallback, 1, &ctx->baseCallback);
    
    // 存储进度回调引用
    if (progressCallback) {
        napi_create_reference(env, progressCallback, 1, &ctx->progressCallback);
    }
    
    // 注册上传回调（进度）
    int uploadCbId = RegisterUploadFileCallback(
        (void*)ctx, 
        CAPI_OnUploadProgress, 
        CAPI_OnUploadSuccess, 
        CAPI_OnUploadError
    );
    
    // 注册 base 回调（完成）
    ctx->baseCallbackId = RegisterBaseCallback(
        (void*)ctx,
        CAPI_OnUploadSuccess,  // base 成功
        CAPI_OnUploadError     // base 失败
    );
    
    return uploadCbId;  // 返回的是 uploadCbId，baseCallbackId 存储在 ctx 中
}

// UploadFile 函数实现
napi_value UploadFile(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value argv[3];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    // 存储回调
    int uploadCbId = StoreUploadFileCallback(env, argv[0], argv[1]);
    
    // 获取 reqData
    char reqData[8192];
    get_string(env, argv[2], reqData, 8192);
    
    // 调用 SDK - 注意参数顺序
    // UploadFile(baseCallbackID, uploadCallbackID, operationID, reqData)
    UploadFile(uploadCbId, uploadCbId, "op_upload_001", reqData);
    
    return nullptr;
}
```

### 9.4 使用示例（ArkTS 端）

```typescript
// MainAbility/pages/Index.ets
import lib from './libopenimsdk'

// 定义回调对象
const loginCallback = {
  onSuccess: (data: string) => {
    console.info(`登录成功: ${data}`)
  },
  onError: (errCode: number, errMsg: string) => {
    console.error(`登录失败: ${errCode} - ${errMsg}`)
  }
}

// 登录
lib.login(loginCallback, "op_login_001", "user123", "token_xxx")

// 上传文件带进度
const uploadCallback = {
  onProgress: (progress: {
    fileHash: string,
    current: number,
    total: number,
    speed: number
  }) => {
    console.info(`上传进度: ${progress.current}/${progress.total} (${progress.speed}KB/s)`)
  },
  base: {
    onSuccess: (data: string) => {
      console.info(`上传完成: ${data}`)
    },
    onError: (errCode: number, errMsg: string) => {
      console.error(`上传失败: ${errCode} - ${errMsg}`)
    }
  }
}

const reqData = JSON.stringify({
  filePath: "/data/file.pdf",
  fileType: 1
})
lib.uploadFile(uploadCallback, "op_upload_001", reqData)
```

### 9.5 回调 ID 管理机制

```
┌─────────────────────────────────────────────────────────────┐
│                    回调 ID 分配表                            │
├─────────────────────────────────────────────────────────────┤
│ Index 0     │ Listeners（监听器，全局单例）                 │
├─────────────────────────────────────────────────────────────┤
│ Index 1-63  │ 动态回调（用完即释放）                        │
│             │ - Login/Logout 的 baseCallback               │
│             │ - UploadFile 的 baseCallback + uploadCallback │
│             │ - SendMessage 的 baseCallback + sendReceipt   │
└─────────────────────────────────────────────────────────────┘

自动释放时机：
1. 回调执行完成后，NAPI 层自动调用 UnregisterBaseCallback()
2. 上下文结构体被 delete 释放
3. JS 引用计数减少，等待 GC 回收
```

---

## 10. 完整示例代码

参见 [example/harmony_example.c](example/harmony_example.c)（如存在）
