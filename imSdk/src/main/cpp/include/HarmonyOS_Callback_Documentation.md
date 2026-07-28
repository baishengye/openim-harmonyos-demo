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

SDK 的 `UploadFileCallback` 接口包含 8 个方法：

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
```

> **注意**：SDK 的 UploadFileCallback 不包含 `onUploadProgress` 进度回调。

### 2.3 发送消息进度回调

```c
// 成功回调：callbackID + JSON 数据
typedef void (*BaseSuccessCb)(int callbackID, char* data);

// 失败回调：callbackID + 错误码 + 错误信息
typedef void (*BaseErrorCb)(int callbackID, int code, char* message);

// 发送进度回调：callbackID + 进度值 (0-100)
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
// 注册上传文件回调（8 个回调）
extern void RegisterUploadFileCallback(
    int uploadCallbackID,
    int onOpen,                    // UploadOpenCb
    int onPartSize,                // UploadPartSizeCb
    int onHashPartProgress,        // UploadHashProgressCb
    int onHashPartComplete,        // UploadHashCompleteCb
    int onUploadID,               // UploadIDCb
    int onUploadPartComplete,     // UploadPartCompleteCb
    int onUploadComplete,         // UploadCompleteCb
    int onComplete                // UploadFinishCb
);

// 注销上传文件回调
extern void UnregisterUploadFileCallback(int uploadCallbackID);
```

### 3.3 发送消息回调注册/注销

```c
// 注册发送消息回调（Base + OnProgress）
extern void RegisterSendMsgCallback(
    int sendMsgCallbackID,
    int onSuccess,                 // BaseSuccessCb
    int onError,                   // BaseErrorCb
    int onProgress                 // SendProgressWithIDCb
);

// 注销发送消息回调
extern void UnregisterSendMsgCallback(int sendMsgCallbackID);
```

> **说明**：`SendMsgCallBack` 接口同时包含 Base 回调（OnSuccess/OnError）和 OnProgress，
> 回调完成后会自动清理，无需手动注销。

### 3.4 日志上传回调注册/注销

```c
// 注册日志上传进度回调
extern void RegisterUploadLogProgress(int uploadLogsCallbackID, int onProgress);

// 注销日志上传进度回调
extern void UnregisterUploadLogProgress(int uploadLogsCallbackID);
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

    // 注意：OnSuccess 或 OnError 触发后会自动清理，无需手动注销
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
    // 上传完成时回调会自动清理，无需手动注销
}

// ==================== 完整上传流程 ====================

void doUploadFile() {
    const char* operationID = "upload_001";
    const char* reqData = "{\"filePath\": \"/data/test.jpg\"}";

    // Step 1: 分配独立的回调 ID
    int baseCallbackID = 2;      // 用于 base 回调（成功/失败）
    int uploadCallbackID = 3;    // 用于上传进度回调

    // Step 2: 注册 Base 回调
    RegisterBaseCallback(
        baseCallbackID,
        (int)onUploadSuccess,
        (int)onUploadError
    );

    // Step 3: 注册上传进度回调（使用独立的 uploadCallbackID，8 个方法）
    RegisterUploadFileCallback(
        uploadCallbackID,        // uploadCallbackID - 上传进度回调专用
        (int)onUploadOpen,
        (int)onUploadPartSize,
        (int)onUploadHashProgress,
        (int)onUploadHashComplete,
        (int)onUploadID,
        (int)onUploadPartComplete,
        (int)onUploadComplete,
        (int)onUploadFinish
        // 注意：SDK 的 UploadFileCallback 不包含 onUploadProgress
    );

    // Step 4: 调用上传函数（分别传入 baseCallbackID 和 uploadCallbackID）
    UploadFile(baseCallbackID, uploadCallbackID, operationID, reqData);

    // 注意：上传完成后回调会自动清理，无需手动注销
}
```

### 5.3 完整流程示例：发送消息

```c
#include "libopenimsdk.h"
#include <stdio.h>

// ==================== 发送消息回调（Base + OnProgress）====================

void onSendSuccess(int callbackID, char* data) {
    printf("[Send] Success! data=%s\n", data);
}

void onSendError(int callbackID, int code, char* message) {
    printf("[Send] Error! code=%d, message=%s\n", code, message);
}

void onSendProgress(int callbackID, int progress) {
    printf("[Send] Progress: callbackID=%d, progress=%d%%\n", callbackID, progress);
    // 当 progress >= 100 时，回调会自动清理
}

// ==================== 完整发送流程 ====================

void doSendMessage() {
    const char* operationID = "send_001";
    const char* message = "{\"msg\":\"hello\"}";
    const char* recvID = "user456";
    const char* groupID = "";  // 单聊为空，群聊为群ID
    const char* offlinePushInfo = "{}";
    int isOnlineOnly = 0;

    // Step 1: 分配回调 ID（用于 SendMsgCallback，包含 Base + OnProgress）
    int sendMsgCallbackID = 5;

    // Step 2: 注册发送消息回调（同时包含 Base 和 OnProgress）
    RegisterSendMsgCallback(
        sendMsgCallbackID,
        (int)onSendSuccess,    // Base 成功回调
        (int)onSendError,      // Base 错误回调
        (int)onSendProgress    // 发送进度回调
    );

    // Step 3: 调用发送函数
    SendMessage(
        sendMsgCallbackID,     // 同时用于 Base 和发送进度
        message, recvID, groupID, offlinePushInfo, operationID, isOnlineOnly
    );

    // 注意：回调完成后会自动清理，无需手动注销
}
```

> **说明**：`SendMsgCallback` 接口同时包含 Base（OnSuccess/OnError）和 OnProgress。
> 回调执行完成后会根据进度值自动清理，无需手动调用 Unregister。

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

| SDK 函数参数 | 说明 | 对应回调类型 | 自动清理 |
|--------------|------|--------------|----------|
| `baseCallbackID` | 成功/失败回调索引 | `RegisterBaseCallback` | OnSuccess/OnError 后自动清理 |
| `uploadCallbackID` | 文件上传进度回调索引 | `RegisterUploadFileCallback` | onComplete 后自动清理 |
| `sendMsgCallbackID` | 发送消息回调索引 | `RegisterSendMsgCallback` | progress >= 100 或 OnSuccess/OnError 后自动清理 |
| `uploadLogsCallbackID` | 日志上传进度回调索引 | `RegisterUploadLogProgress` | current >= total 后自动清理 |

### 6.3 推荐使用模式

```c
// 模式 1: 同一 ID 用于 Base + 特定回调（会自动清理）
int callbackID = allocateCallbackID();
RegisterBaseCallback(callbackID, onSuccess, onError);
RegisterUploadFileCallback(callbackID, ...);
UploadFile(callbackID, callbackID, operationID, reqData);
// 注意：上传完成后会自动清理，无需手动注销

// 模式 2: 不同 ID 分别使用
int baseID = allocateCallbackID();
int uploadID = allocateCallbackID();
RegisterBaseCallback(baseID, onSuccess, onError);
RegisterUploadFileCallback(uploadID, ...);
UploadFile(baseID, uploadID, operationID, reqData);

// 模式 3: SendMsgCallback（同时包含 Base + OnProgress）
int sendMsgID = allocateCallbackID();
RegisterSendMsgCallback(sendMsgID, onSuccess, onError, onProgress);
SendMessage(sendMsgID, message, recvID, groupID, ...);
// 注意：发送完成后会自动清理
```

---

## 7. 回调自动清理机制

### 7.1 自动清理规则

回调执行完成后会自动清理，无需手动注销：

| 回调类型 | 清理时机 | 说明 |
|----------|----------|------|
| **Base 回调** | OnSuccess 或 OnError 触发后 | 自动调用 `DeleteBaseCallback(cbId)` |
| **上传文件回调** | `onComplete` (UploadFinish) 触发后 | 自动调用 `DeleteUploadCallbacks(cbId)` |
| **日志上传回调** | `onProgress` 中 `current >= total` 时 | 自动调用 `DeleteUploadLogCallback(cbId)` |
| **发送消息回调** | OnProgress 中 `progress >= 100` 时清理 OnProgress；OnSuccess/OnError 触发后清理 Base | 自动清理，无需手动操作 |

### 7.2 自动清理流程

```
回调触发
    ↓
执行 JavaScript 回调
    ↓
检查清理条件
    ├── OnSuccess/OnError → DeleteBaseCallback + DeleteSendMsgCallback（如有）
    ├── UploadFinish → DeleteUploadCallbacks
    ├── UploadLog current >= total → DeleteUploadLogCallback
    └── SendProgress >= 100 → DeleteSendMsgCallback
    ↓
释放 napi_ref 和内存
```

### 7.3 Listener 回调说明

- Listener 回调在 SDK 初始化后注册一次即可
- 建议在 `InitSDK` 成功后立即注册所有 Listener
- 如果需要更换 Listener 回调，先调用 `UnregisterXxxListener()` 再重新注册
- Listener 回调固定使用 index 0，无需手动注销

### 7.4 线程安全

- 回调在 Go 协程中触发
- 确保回调实现是线程安全的
- 建议在回调中使用队列机制，将事件投递到主线程处理

### 7.5 内存管理

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

以下是一个完整的 HarmonyOS NAPI 集成示例，展示如何实现回调存储和调用 SDK 函数。

### 9.1 TypeScript 接口定义

```typescript
// OpenIMSDK.ets

// 基础回调接口 - 包含成功和失败回调
export interface BaseCallback {
  onError(errCode: number, errMsg: string): void;
  onSuccess(data: string): void;
}

// 上传进度回调接口（SDK 的 UploadFileCallback 包含 8 个方法）
export interface UploadFileCallback {
  onOpen(fileSize: number): void;
  onPartSize(partSize: number, num: int): void;
  onHashPartProgress(index: number, size: number, partHash: string): void;
  onHashPartComplete(partsHash: string, fileHash: string): void;
  onUploadID(uploadID: string): void;
  onUploadPartComplete(index: number, partSize: number, partHash: string): void;
  onUploadComplete(fileSize: number, streamSize: number, storageSize: number): void;
  onComplete(size: number, url: string, type: int): void;
  // 注意：SDK 的 UploadFileCallback 不包含 onUploadProgress
}

// 上传日志进度回调接口
export interface UploadLogCallback {
  onProgress(current: number, size: number): void;
}

// 发送消息回调接口（SDK 的 SendMsgCallBack 包含 Base + OnProgress）
export interface SendMsgCallback {
  onSuccess(data: string): void;
  onError(errCode: number, errMsg: string): void;
  onProgress(progress: number): void;
  // 注意：progress 到达 100 时会自动清理
}

// SDK 函数声明
export function login(baseCallback: BaseCallback, operationID: string, userID: string, token: string): void;
export function logout(baseCallback: BaseCallback, operationID: string): void;
export function uploadFile(baseCallback: BaseCallback, uploadCallback: UploadFileCallback, operationID: string, reqData: string): void;
export function uploadLogs(baseCallback: BaseCallback, uploadLogCallback: UploadLogCallback, operationID: string, line: number, ex: string): void;
export function sendMessage(sendMsgCallback: SendMsgCallback, message: string, recvID: string, groupID: string, offlinePushInfo: string, operationID: string, isOnlineOnly: boolean): void;
```

### 9.2 NAPI 模块实现 - 回调存储机制

```cpp
// openimsdk_napi.cpp
#include <string>
#include <memory>
#include <unordered_map>
#include "libopenimsdk.h"

// ============================================
// 回调上下文存储 - 用于存储 JS 回调引用
// ============================================

// 通用回调上下文（用于 BaseCallback）
struct BaseCallbackContext {
    napi_ref successRef;   // onSuccess 的 JS 引用
    napi_ref errorRef;     // onError 的 JS 引用
    napi_env env;
};

// 上传文件回调上下文
struct UploadFileCallbackContext {
    napi_ref openRef;              // onOpen
    napi_ref partSizeRef;          // onPartSize
    napi_ref hashProgressRef;      // onHashPartProgress
    napi_ref hashCompleteRef;      // onHashPartComplete
    napi_ref uploadIDRef;          // onUploadID
    napi_ref uploadPartRef;        // onUploadPartComplete
    napi_ref uploadCompleteRef;    // onUploadComplete
    napi_ref completeRef;          // onComplete
    napi_ref progressRef;          // onUploadProgress
    napi_ref baseSuccessRef;       // base onSuccess
    napi_ref baseErrorRef;         // base onError
    napi_env env;
    int baseCallbackID;            // 保存 base 回调 ID
};

// 上传日志回调上下文
struct UploadLogCallbackContext {
    napi_ref progressRef;          // onProgress
    napi_ref baseSuccessRef;       // base onSuccess
    napi_ref baseErrorRef;         // base onError
    napi_env env;
    int baseCallbackID;
};

// 发送消息回调上下文
struct SendMessageCallbackContext {
    napi_ref progressRef;          // onProgress
    napi_ref baseSuccessRef;       // base onSuccess
    napi_ref baseErrorRef;         // base onError
    napi_env env;
    int baseCallbackID;
};

// ============================================
// 回调 ID 管理
// ============================================

static std::unordered_map<int, void*> gCallbackContexts;
static int gNextCallbackID = 1;  // 从 1 开始，0 保留给 Listeners
static std::mutex gCallbackMutex;

// 分配回调 ID 并存储上下文
int AllocCallbackID(void* ctx) {
    std::lock_guard<std::mutex> lock(gCallbackMutex);
    int id = gNextCallbackID++;
    gCallbackContexts[id] = ctx;
    return id;
}

// 获取回调上下文
void* GetCallbackContext(int cbId) {
    std::lock_guard<std::mutex> lock(gCallbackMutex);
    auto it = gCallbackContexts.find(cbId);
    if (it != gCallbackContexts.end()) {
        return it->second;
    }
    return nullptr;
}

// 释放回调上下文
void FreeCallbackContext(int cbId) {
    std::lock_guard<std::mutex> lock(gCallbackMutex);
    gCallbackContexts.erase(cbId);
}

// 释放 JS 引用
void DeleteBaseCallbackContext(BaseCallbackContext* ctx) {
    if (!ctx) return;
    napi_delete_reference(ctx->env, ctx->successRef);
    napi_delete_reference(ctx->env, ctx->errorRef);
    delete ctx;
}
```

### 9.3 StoreBaseCallback 实现

```cpp
// ============================================
// BaseCallback 回调实现
// ============================================

// C 成功回调
extern "C" void CAPI_BaseSuccess(int cbId, char* data) {
    BaseCallbackContext* ctx = (BaseCallbackContext*)GetCallbackContext(cbId);
    if (!ctx) return;
    
    napi_env env = ctx->env;
    
    // 创建 JS 字符串
    napi_value jsData;
    napi_create_string_utf8(env, data ? data : "", NAPI_AUTO_LENGTH, &jsData);
    
    // 获取 onSuccess 回调并调用
    napi_value callback;
    napi_get_reference_value(env, ctx->successRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value result;
    napi_call_function(env, global, callback, 1, &jsData, &result);
    
    // 释放资源
    FreeCallbackContext(cbId);
    DeleteBaseCallbackContext(ctx);
}

// C 错误回调
extern "C" void CAPI_BaseError(int cbId, int errCode, char* errMsg) {
    BaseCallbackContext* ctx = (BaseCallbackContext*)GetCallbackContext(cbId);
    if (!ctx) return;
    
    napi_env env = ctx->env;
    
    napi_value jsErrCode, jsErrMsg;
    napi_create_int32(env, errCode, &jsErrCode);
    napi_create_string_utf8(env, errMsg ? errMsg : "", NAPI_AUTO_LENGTH, &jsErrMsg);
    
    // 获取 onError 回调并调用
    napi_value callback;
    napi_get_reference_value(env, ctx->errorRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[2] = {jsErrCode, jsErrMsg};
    napi_value result;
    napi_call_function(env, global, callback, 2, argv, &result);
    
    // 释放资源
    FreeCallbackContext(cbId);
    DeleteBaseCallbackContext(ctx);
}

// 存储 BaseCallback - 分配回调 ID 并注册
int StoreBaseCallback(napi_env env, napi_value callback) {
    // 创建上下文
    BaseCallbackContext* ctx = new BaseCallbackContext();
    ctx->env = env;
    
    // 提取 onSuccess 和 onError
    napi_value onSuccess, onError;
    napi_get_named_property(env, callback, "onSuccess", &onSuccess);
    napi_get_named_property(env, callback, "onError", &onError);
    
    // 创建 JS 引用
    napi_create_reference(env, onSuccess, 1, &ctx->successRef);
    napi_create_reference(env, onError, 1, &ctx->errorRef);
    
    // 分配回调 ID
    int cbId = AllocCallbackID(ctx);
    
    // 注册到 SDK
    RegisterBaseCallback(cbId, (int)&CAPI_BaseSuccess, (int)&CAPI_BaseError);
    
    return cbId;
}

// Login 函数实现
napi_value Login(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value argv[4];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    // 存储回调（回调执行后自动释放）
    int cbId = StoreBaseCallback(env, argv[0]);
    
    // 获取参数
    char operationID[64], userID[64], token[256];
    get_string(env, argv[1], operationID, 64);
    get_string(env, argv[2], userID, 64);
    get_string(env, argv[3], token, 256);
    
    // 调用 SDK
    Login(cbId, userID, token, operationID);
    
    return nullptr;
}

// Logout 函数实现
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

### 9.4 StoreUploadFileCallback 实现

```cpp
// ============================================
// UploadFile 回调实现
// ============================================

// C 回调 - onOpen
extern "C" void CAPI_UploadOpen(int cbId, long long size) {
    UploadFileCallbackContext* ctx = (UploadFileCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->openRef) return;
    
    napi_env env = ctx->env;
    napi_value jsSize;
    napi_create_int64(env, size, &jsSize);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->openRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value result;
    napi_call_function(env, global, callback, 1, &jsSize, &result);
}

// C 回调 - onPartSize
extern "C" void CAPI_UploadPartSize(int cbId, long long partSize, int num) {
    UploadFileCallbackContext* ctx = (UploadFileCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->partSizeRef) return;
    
    napi_env env = ctx->env;
    napi_value jsPartSize, jsNum;
    napi_create_int64(env, partSize, &jsPartSize);
    napi_create_int32(env, num, &jsNum);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->partSizeRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[2] = {jsPartSize, jsNum};
    napi_value result;
    napi_call_function(env, global, callback, 2, argv, &result);
}

// C 回调 - onHashPartProgress
extern "C" void CAPI_UploadHashProgress(int cbId, int index, long long size, char* partHash) {
    UploadFileCallbackContext* ctx = (UploadFileCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->hashProgressRef) return;
    
    napi_env env = ctx->env;
    napi_value jsIndex, jsSize, jsPartHash;
    napi_create_int32(env, index, &jsIndex);
    napi_create_int64(env, size, &jsSize);
    napi_create_string_utf8(env, partHash, NAPI_AUTO_LENGTH, &jsPartHash);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->hashProgressRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[3] = {jsIndex, jsSize, jsPartHash};
    napi_value result;
    napi_call_function(env, global, callback, 3, argv, &result);
}

// C 回调 - onHashPartComplete
extern "C" void CAPI_UploadHashComplete(int cbId, char* partsHash, char* fileHash) {
    UploadFileCallbackContext* ctx = (UploadFileCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->hashCompleteRef) return;
    
    napi_env env = ctx->env;
    napi_value jsPartsHash, jsFileHash;
    napi_create_string_utf8(env, partsHash, NAPI_AUTO_LENGTH, &jsPartsHash);
    napi_create_string_utf8(env, fileHash, NAPI_AUTO_LENGTH, &jsFileHash);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->hashCompleteRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[2] = {jsPartsHash, jsFileHash};
    napi_value result;
    napi_call_function(env, global, callback, 2, argv, &result);
}

// C 回调 - onUploadID
extern "C" void CAPI_UploadID(int cbId, char* uploadID) {
    UploadFileCallbackContext* ctx = (UploadFileCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->uploadIDRef) return;
    
    napi_env env = ctx->env;
    napi_value jsUploadID;
    napi_create_string_utf8(env, uploadID, NAPI_AUTO_LENGTH, &jsUploadID);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->uploadIDRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value result;
    napi_call_function(env, global, callback, 1, &jsUploadID, &result);
}

// C 回调 - onUploadPartComplete
extern "C" void CAPI_UploadPartComplete(int cbId, int index, long long partSize, char* partHash) {
    UploadFileCallbackContext* ctx = (UploadFileCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->uploadPartRef) return;
    
    napi_env env = ctx->env;
    napi_value jsIndex, jsPartSize, jsPartHash;
    napi_create_int32(env, index, &jsIndex);
    napi_create_int64(env, partSize, &jsPartSize);
    napi_create_string_utf8(env, partHash, NAPI_AUTO_LENGTH, &jsPartHash);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->uploadPartRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[3] = {jsIndex, jsPartSize, jsPartHash};
    napi_value result;
    napi_call_function(env, global, callback, 3, argv, &result);
}

// C 回调 - onUploadComplete
extern "C" void CAPI_UploadComplete(int cbId, long long fileSize, long long streamSize, long long storageSize) {
    UploadFileCallbackContext* ctx = (UploadFileCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->uploadCompleteRef) return;
    
    napi_env env = ctx->env;
    napi_value jsFileSize, jsStreamSize, jsStorageSize;
    napi_create_int64(env, fileSize, &jsFileSize);
    napi_create_int64(env, streamSize, &jsStreamSize);
    napi_create_int64(env, storageSize, &jsStorageSize);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->uploadCompleteRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[3] = {jsFileSize, jsStreamSize, jsStorageSize};
    napi_value result;
    napi_call_function(env, global, callback, 3, argv, &result);
}

// C 回调 - onComplete (上传完成)
extern "C" void CAPI_UploadFinish(int cbId, long long size, char* url, int type) {
    UploadFileCallbackContext* ctx = (UploadFileCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->completeRef) return;
    
    napi_env env = ctx->env;
    napi_value jsSize, jsUrl, jsType;
    napi_create_int64(env, size, &jsSize);
    napi_create_string_utf8(env, url, NAPI_AUTO_LENGTH, &jsUrl);
    napi_create_int32(env, type, &jsType);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->completeRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[3] = {jsSize, jsUrl, jsType};
    napi_value result;
    napi_call_function(env, global, callback, 3, argv, &result);
}

// C 回调 - onUploadProgress
extern "C" void CAPI_UploadProgress(int cbId, long long current, long long total) {
    UploadFileCallbackContext* ctx = (UploadFileCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->progressRef) return;
    
    napi_env env = ctx->env;
    napi_value jsCurrent, jsTotal;
    napi_create_int64(env, current, &jsCurrent);
    napi_create_int64(env, total, &jsTotal);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->progressRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[2] = {jsCurrent, jsTotal};
    napi_value result;
    napi_call_function(env, global, callback, 2, argv, &result);
}

// 存储上传文件回调 - 返回两个回调 ID
// 注意：需要同时分配两个回调 ID（base 和 upload）
UploadFileCallbackResult StoreUploadFileCallback(napi_env env, napi_value baseCallback, napi_value uploadCallback) {
    // 创建上传回调上下文
    UploadFileCallbackContext* ctx = new UploadFileCallbackContext();
    ctx->env = env;
    
    // 提取 uploadCallback 的各个方法
    napi_value onOpen, onPartSize, onHashProgress, onHashComplete;
    napi_value onUploadID, onUploadPart, onUploadComplete, onComplete, onProgress;
    
    napi_get_named_property(env, uploadCallback, "onOpen", &onOpen);
    napi_get_named_property(env, uploadCallback, "onPartSize", &onPartSize);
    napi_get_named_property(env, uploadCallback, "onHashPartProgress", &onHashProgress);
    napi_get_named_property(env, uploadCallback, "onHashPartComplete", &onHashComplete);
    napi_get_named_property(env, uploadCallback, "onUploadID", &onUploadID);
    napi_get_named_property(env, uploadCallback, "onUploadPartComplete", &onUploadPart);
    napi_get_named_property(env, uploadCallback, "onUploadComplete", &onUploadComplete);
    napi_get_named_property(env, uploadCallback, "onComplete", &onComplete);
    napi_get_named_property(env, uploadCallback, "onUploadProgress", &onProgress);
    
    // 创建 JS 引用
    if (napi_check_type(env, onOpen)) napi_create_reference(env, onOpen, 1, &ctx->openRef);
    if (napi_check_type(env, onPartSize)) napi_create_reference(env, onPartSize, 1, &ctx->partSizeRef);
    if (napi_check_type(env, onHashProgress)) napi_create_reference(env, onHashProgress, 1, &ctx->hashProgressRef);
    if (napi_check_type(env, onHashComplete)) napi_create_reference(env, onHashComplete, 1, &ctx->hashCompleteRef);
    if (napi_check_type(env, onUploadID)) napi_create_reference(env, onUploadID, 1, &ctx->uploadIDRef);
    if (napi_check_type(env, onUploadPart)) napi_create_reference(env, onUploadPart, 1, &ctx->uploadPartRef);
    if (napi_check_type(env, onUploadComplete)) napi_create_reference(env, onUploadComplete, 1, &ctx->uploadCompleteRef);
    if (napi_check_type(env, onComplete)) napi_create_reference(env, onComplete, 1, &ctx->completeRef);
    if (napi_check_type(env, onProgress)) napi_create_reference(env, onProgress, 1, &ctx->progressRef);
    
    // 分配回调 ID
    int uploadCbId = AllocCallbackID(ctx);
    
    // 注册上传回调
    RegisterUploadFileCallback(
        uploadCbId,
        (int)&CAPI_UploadOpen,
        (int)&CAPI_UploadPartSize,
        (int)&CAPI_UploadHashProgress,
        (int)&CAPI_UploadHashComplete,
        (int)&CAPI_UploadID,
        (int)&CAPI_UploadPartComplete,
        (int)&CAPI_UploadComplete,
        (int)&CAPI_UploadFinish,
        (int)&CAPI_UploadProgress
    );
    
    // 存储 base 回调信息
    napi_value onSuccess, onError;
    napi_get_named_property(env, baseCallback, "onSuccess", &onSuccess);
    napi_get_named_property(env, baseCallback, "onError", &onError);
    napi_create_reference(env, onSuccess, 1, &ctx->baseSuccessRef);
    napi_create_reference(env, onError, 1, &ctx->baseErrorRef);
    
    // 分配 base 回调 ID
    int baseCbId = AllocCallbackID(ctx);
    ctx->baseCallbackID = baseCbId;
    
    // 注册 base 回调
    RegisterBaseCallback(baseCbId, (int)&CAPI_BaseSuccess, (int)&CAPI_BaseError);
    
    // 返回两个回调 ID
    UploadFileCallbackResult result;
    result.baseCallbackID = baseCbId;
    result.uploadCallbackID = uploadCbId;
    return result;
}

// 上传文件函数实现
napi_value UploadFile(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value argv[4];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    // 存储回调
    UploadFileCallbackResult cbResult = StoreUploadFileCallback(env, argv[0], argv[1]);
    
    // 获取参数
    char operationID[64], reqData[8192];
    get_string(env, argv[2], operationID, 64);
    get_string(env, argv[3], reqData, 8192);
    
    // 调用 SDK - 注意参数顺序
    // UploadFile(baseCallbackID, uploadCallbackID, operationID, reqData)
    UploadFile(cbResult.baseCallbackID, cbResult.uploadCallbackID, operationID, reqData);
    
    return nullptr;
}
```

### 9.5 StoreUploadLogCallback 实现

```cpp
// ============================================
// UploadLogs 回调实现
// ============================================

// C 回调 - onProgress
extern "C" void CAPI_UploadLogProgress(int cbId, long long current, long long size) {
    UploadLogCallbackContext* ctx = (UploadLogCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->progressRef) return;
    
    napi_env env = ctx->env;
    napi_value jsCurrent, jsSize;
    napi_create_int64(env, current, &jsCurrent);
    napi_create_int64(env, size, &jsSize);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->progressRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value argv[2] = {jsCurrent, jsSize};
    napi_value result;
    napi_call_function(env, global, callback, 2, argv, &result);
}

// 存储上传日志回调
UploadLogCallbackResult StoreUploadLogCallback(napi_env env, napi_value baseCallback, napi_value logCallback) {
    UploadLogCallbackContext* ctx = new UploadLogCallbackContext();
    ctx->env = env;
    
    // 提取 logCallback 的 onProgress
    napi_value onProgress;
    napi_get_named_property(env, logCallback, "onProgress", &onProgress);
    napi_create_reference(env, onProgress, 1, &ctx->progressRef);
    
    // 分配回调 ID
    int uploadCbId = AllocCallbackID(ctx);
    
    // 注册上传日志进度回调
    RegisterUploadLogProgress(uploadCbId, (int)&CAPI_UploadLogProgress);
    
    // 存储 base 回调
    napi_value onSuccess, onError;
    napi_get_named_property(env, baseCallback, "onSuccess", &onSuccess);
    napi_get_named_property(env, baseCallback, "onError", &onError);
    napi_create_reference(env, onSuccess, 1, &ctx->baseSuccessRef);
    napi_create_reference(env, onError, 1, &ctx->baseErrorRef);
    
    int baseCbId = AllocCallbackID(ctx);
    ctx->baseCallbackID = baseCbId;
    
    RegisterBaseCallback(baseCbId, (int)&CAPI_BaseSuccess, (int)&CAPI_BaseError);
    
    UploadLogCallbackResult result;
    result.baseCallbackID = baseCbId;
    result.uploadLogsCallbackID = uploadCbId;
    return result;
}

// 上传日志函数实现
napi_value UploadLogs(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value argv[5];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    UploadLogCallbackResult cbResult = StoreUploadLogCallback(env, argv[0], argv[1]);
    
    char operationID[64], ex[1024];
    int line;
    get_string(env, argv[2], operationID, 64);
    
    napi_value jsLine;
    napi_get_value_int32(env, argv[3], &line);
    
    get_string(env, argv[4], ex, 1024);
    
    // UploadLogs(baseCallbackID, uploadLogsCallbackID, operationID, line, ex)
    UploadLogs(cbResult.baseCallbackID, cbResult.uploadLogsCallbackID, operationID, line, ex);
    
    return nullptr;
}
```

### 9.6 StoreSendMessageCallback 实现

```cpp
// ============================================
// SendMessage 回调实现
// ============================================

// C 回调 - onProgress
extern "C" void CAPI_SendProgress(int cbId, int progress) {
    SendMessageCallbackContext* ctx = (SendMessageCallbackContext*)GetCallbackContext(cbId);
    if (!ctx || !ctx->progressRef) return;
    
    napi_env env = ctx->env;
    napi_value jsProgress;
    napi_create_int32(env, progress, &jsProgress);
    
    napi_value callback;
    napi_get_reference_value(env, ctx->progressRef, &callback);
    napi_value global;
    napi_get_global(env, &global);
    
    napi_value result;
    napi_call_function(env, global, callback, 1, &jsProgress, &result);
}

// 存储发送消息回调
SendMessageCallbackResult StoreSendMessageCallback(napi_env env, napi_value baseCallback, napi_value progressCallback) {
    SendMessageCallbackContext* ctx = new SendMessageCallbackContext();
    ctx->env = env;
    
    // 提取 progressCallback 的 onProgress
    napi_value onProgress;
    napi_get_named_property(env, progressCallback, "onProgress", &onProgress);
    napi_create_reference(env, onProgress, 1, &ctx->progressRef);
    
    // 分配回调 ID
    int progressCbId = AllocCallbackID(ctx);
    
    // 注册发送进度回调
    RegisterSendProgress(progressCbId, (int)&CAPI_SendProgress);
    
    // 存储 base 回调
    napi_value onSuccess, onError;
    napi_get_named_property(env, baseCallback, "onSuccess", &onSuccess);
    napi_get_named_property(env, baseCallback, "onError", &onError);
    napi_create_reference(env, onSuccess, 1, &ctx->baseSuccessRef);
    napi_create_reference(env, onError, 1, &ctx->baseErrorRef);
    
    int baseCbId = AllocCallbackID(ctx);
    ctx->baseCallbackID = baseCbId;
    
    RegisterBaseCallback(baseCbId, (int)&CAPI_BaseSuccess, (int)&CAPI_BaseError);
    
    SendMessageCallbackResult result;
    result.baseCallbackID = baseCbId;
    result.sendReceiptCallbackID = progressCbId;
    return result;
}

// 发送消息函数实现
napi_value SendMessage(napi_env env, napi_callback_info info) {
    size_t argc = 8;
    napi_value argv[8];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    
    SendMessageCallbackResult cbResult = StoreSendMessageCallback(env, argv[0], argv[1]);
    
    char message[8192], recvID[64], groupID[64], offlinePushInfo[1024], operationID[64];
    int isOnlineOnly;
    
    get_string(env, argv[2], message, 8192);
    get_string(env, argv[3], recvID, 64);
    get_string(env, argv[4], groupID, 64);
    get_string(env, argv[5], offlinePushInfo, 1024);
    get_string(env, argv[6], operationID, 64);
    
    napi_get_value_bool(env, argv[7], (bool*)&isOnlineOnly);
    
    // SendMessage(baseCallbackID, sendReceiptCallbackID, message, recvID, groupID, offlinePushInfo, operationID, isOnlineOnly)
    SendMessage(cbResult.baseCallbackID, cbResult.sendReceiptCallbackID,
                message, recvID, groupID, offlinePushInfo, operationID, isOnlineOnly);
    
    return nullptr;
}
```

### 9.7 ArkTS 使用示例

```typescript
// MainAbility/pages/Index.ets
import lib from './libopenimsdk'

// 基础回调示例
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

// 上传文件示例（SDK 的 UploadFileCallback 包含 8 个方法，不含 onUploadProgress）
const uploadFileCallback = {
  onOpen: (fileSize: number) => {
    console.info(`开始上传, 文件大小: ${fileSize}`)
  },
  onPartSize: (partSize: number, num: number) => {
    console.info(`分片大小: ${partSize}, 数量: ${num}`)
  },
  onHashPartProgress: (index: number, size: number, partHash: string) => {
    console.info(`Hash进度: ${index}, ${size}`)
  },
  onHashPartComplete: (partsHash: string, fileHash: string) => {
    console.info(`Hash完成: ${fileHash}`)
  },
  onUploadID: (uploadID: string) => {
    console.info(`UploadID: ${uploadID}`)
  },
  onUploadPartComplete: (index: number, partSize: number, partHash: string) => {
    console.info(`分片完成: ${index}`)
  },
  onUploadComplete: (fileSize: number, streamSize: number, storageSize: number) => {
    console.info(`上传完成: ${fileSize}`)
  },
  onComplete: (size: number, url: string, type: number) => {
    console.info(`完成: ${url}`)
    // 上传完成时回调会自动清理
  }
}

const reqData = JSON.stringify({
  filePath: "/data/file.pdf",
  fileType: 1
})
lib.uploadFile(loginCallback, uploadFileCallback, "op_upload_001", reqData)
// 注意：上传完成后回调会自动清理

// 上传日志示例
const uploadLogCallback = {
  onProgress: (current: number, size: number) => {
    console.info(`日志上传进度: ${current}/${size}`)
  }
}
lib.uploadLogs(loginCallback, uploadLogCallback, "op_upload_log_001", 100, "{}")

// 发送消息示例（SendMsgCallback 包含 Base + OnProgress）
const sendMsgCallback = {
  onSuccess: (data: string) => {
    console.info(`发送成功: ${data}`)
  },
  onError: (errCode: number, errMsg: string) => {
    console.error(`发送失败: ${errCode} - ${errMsg}`)
  },
  onProgress: (progress: number) => {
    console.info(`发送进度: ${progress}%`)
    // 当 progress >= 100 时，回调会自动清理
  }
}

const message = JSON.stringify({
  text: "Hello"
})
lib.sendMessage(sendMsgCallback, message, "user456", "", "", "op_send_001", false)
```

### 9.8 回调 ID 管理机制

```
┌─────────────────────────────────────────────────────────────┐
│                    回调 ID 分配表                            │
├─────────────────────────────────────────────────────────────┤
│ Index 0     │ Listeners（监听器，全局单例）                 │
├─────────────────────────────────────────────────────────────┤
│ Index 1-N   │ 动态回调（大部分自动清理）                    │
│             │ - StoreBaseCallback 分配                      │
│             │ - StoreUploadFileCallback 分配                │
│             │ - StoreUploadLogCallback 分配                 │
│             │ - StoreSendMsgCallback 分配（Base + OnProgress）│
└─────────────────────────────────────────────────────────────┘

自动清理流程：

1. C 回调函数被调用
2. 从 GetCallbackContext(cbId) 获取上下文
3. 调用对应的 JS 回调
4. 检查清理条件
   ├── OnSuccess/OnError → DeleteBaseCallback（如有 SendMsgCallback，一并清理）
   ├── UploadFinish → DeleteUploadCallbacks
   ├── UploadLog current >= total → DeleteUploadLogCallback
   └── SendProgress >= 100 → DeleteSendMsgCallback
5. 释放 napi_ref 和内存
6. 释放回调 ID（FreeCallbackContext）
```

---

## 10. 完整示例代码

### 10.1 所有回调注册示例

```c
#include "libopenimsdk.h"
#include <stdio.h>

// ============================================================
// 全局变量 - 用于保存回调 ID
// ============================================================
static int g_baseCallbackID = -1;         // Base 回调 ID
static int g_uploadCallbackID = -1;       // 上传进度回调 ID
static int g_uploadLogsCallbackID = -1;   // 日志上传回调 ID
static int g_sendReceiptCallbackID = -1;  // 发送进度回调 ID

// ============================================================
// 10.1.1 连接监听器 (Connection Listener)
// ============================================================
void onConnecting() {
    printf("[Conn] Connecting...\n");
}

void onConnectSuccess() {
    printf("[Conn] Connected successfully!\n");
}

void onConnectFailed(int callbackID, char* err) {
    printf("[Conn] Connect failed: %s\n", err);
}

void onKickedOffline() {
    printf("[Conn] Kicked offline!\n");
}

void onUserTokenExpired() {
    printf("[Conn] User token expired!\n");
}

void onUserTokenInvalid(int callbackID, char* err) {
    printf("[Conn] Token invalid: %s\n", err);
}

// 注册连接监听器
void registerConnListener() {
    RegisterConnListener(
        (int)onConnecting,
        (int)onConnectSuccess,
        (int)onConnectFailed,
        (int)onKickedOffline,
        (int)onUserTokenExpired,
        (int)onUserTokenInvalid
    );
    printf("Connection listener registered\n");
}

// ============================================================
// 10.1.2 消息监听器 (Message Listener)
// ============================================================
void onRecvNewMessage(int callbackID, char* msg) {
    printf("[Msg] New message: %s\n", msg);
}

void onRecvReceipt(int callbackID, char* receipt) {
    printf("[Msg] Receipt: %s\n", receipt);
}

void onMsgRevoked(int callbackID, char* msg) {
    printf("[Msg] Message revoked: %s\n", msg);
}

void onRecvOffline(int callbackID, char* msg) {
    printf("[Msg] Offline message: %s\n", msg);
}

void onMsgDeleted(int callbackID, char* msg) {
    printf("[Msg] Message deleted: %s\n", msg);
}

void onRecvOnline(int callbackID, char* msg) {
    printf("[Msg] Online message: %s\n", msg);
}

// 注册消息监听器
void registerMsgListener() {
    RegisterMsgListener(
        (int)onRecvNewMessage,
        (int)onRecvReceipt,
        (int)onMsgRevoked,
        (int)onRecvOffline,
        (int)onMsgDeleted,
        (int)onRecvOnline
    );
    printf("Message listener registered\n");
}

// ============================================================
// 10.1.3 会话监听器 (Conversation Listener)
// ============================================================
void onSyncStart() {
    printf("[Conv] Sync start\n");
}

void onSyncFinish() {
    printf("[Conv] Sync finish\n");
}

void onSyncProgress(int progress) {
    printf("[Conv] Sync progress: %d%%\n", progress);
}

void onSyncFailed(int callbackID, char* err) {
    printf("[Conv] Sync failed: %s\n", err);
}

void onConvChanged(int callbackID, char* conv) {
    printf("[Conv] Changed: %s\n", conv);
}

void onNewConv(int callbackID, char* conv) {
    printf("[Conv] New conversation: %s\n", conv);
}

void onUnreadChanged(int totalUnreadCount) {
    printf("[Conv] Unread count: %d\n", totalUnreadCount);
}

void onInputStatusChanged(int callbackID, char* status) {
    printf("[Conv] Input status: %s\n", status);
}

// 注册会话监听器
void registerConvListener() {
    RegisterConvListener(
        (int)onSyncStart,
        (int)onSyncFinish,
        (int)onSyncProgress,
        (int)onSyncFailed,
        (int)onConvChanged,
        (int)onNewConv,
        (int)onUnreadChanged,
        (int)onInputStatusChanged
    );
    printf("Conversation listener registered\n");
}

// ============================================================
// 10.1.4 群组监听器 (Group Listener)
// ============================================================
void onJoinedGroupAdded(int callbackID, char* group) {
    printf("[Group] Joined (added): %s\n", group);
}

void onJoinedGroupDeleted(int callbackID, char* group) {
    printf("[Group] Joined (deleted): %s\n", group);
}

void onGroupMemberAdded(int callbackID, char* member) {
    printf("[Group] Member added: %s\n", member);
}

void onGroupMemberDeleted(int callbackID, char* member) {
    printf("[Group] Member deleted: %s\n", member);
}

void onGroupApplicationAdded(int callbackID, char* application) {
    printf("[Group] Application added: %s\n", application);
}

void onGroupApplicationDeleted(int callbackID, char* application) {
    printf("[Group] Application deleted: %s\n", application);
}

void onGroupInfoChanged(int callbackID, char* info) {
    printf("[Group] Info changed: %s\n", info);
}

void onGroupDismissed(int callbackID, char* group) {
    printf("[Group] Dismissed: %s\n", group);
}

void onGroupMemberInfoChanged(int callbackID, char* info) {
    printf("[Group] Member info changed: %s\n", info);
}

void onGroupApplicationAccepted(int callbackID, char* application) {
    printf("[Group] Application accepted: %s\n", application);
}

void onGroupApplicationRejected(int callbackID, char* application) {
    printf("[Group] Application rejected: %s\n", application);
}

// 注册群组监听器
void registerGroupListener() {
    RegisterGroupListener(
        (int)onJoinedGroupAdded,
        (int)onJoinedGroupDeleted,
        (int)onGroupMemberAdded,
        (int)onGroupMemberDeleted,
        (int)onGroupApplicationAdded,
        (int)onGroupApplicationDeleted,
        (int)onGroupInfoChanged,
        (int)onGroupDismissed,
        (int)onGroupMemberInfoChanged,
        (int)onGroupApplicationAccepted,
        (int)onGroupApplicationRejected
    );
    printf("Group listener registered\n");
}

// ============================================================
// 10.1.5 好友监听器 (Friend Listener)
// ============================================================
void onFriendApplicationAdded(int callbackID, char* application) {
    printf("[Friend] Application added: %s\n", application);
}

void onFriendApplicationDeleted(int callbackID, char* application) {
    printf("[Friend] Application deleted: %s\n", application);
}

void onFriendApplicationAccepted(int callbackID, char* application) {
    printf("[Friend] Application accepted: %s\n", application);
}

void onFriendApplicationRejected(int callbackID, char* application) {
    printf("[Friend] Application rejected: %s\n", application);
}

void onFriendAdded(int callbackID, char* friend) {
    printf("[Friend] Added: %s\n", friend);
}

void onFriendDeleted(int callbackID, char* friend) {
    printf("[Friend] Deleted: %s\n", friend);
}

void onFriendInfoChanged(int callbackID, char* info) {
    printf("[Friend] Info changed: %s\n", info);
}

void onBlackAdded(int callbackID, char* black) {
    printf("[Friend] Black added: %s\n", black);
}

void onBlackDeleted(int callbackID, char* black) {
    printf("[Friend] Black deleted: %s\n", black);
}

// 注册好友监听器
void registerFriendListener() {
    RegisterFriendListener(
        (int)onFriendApplicationAdded,
        (int)onFriendApplicationDeleted,
        (int)onFriendApplicationAccepted,
        (int)onFriendApplicationRejected,
        (int)onFriendAdded,
        (int)onFriendDeleted,
        (int)onFriendInfoChanged,
        (int)onBlackAdded,
        (int)onBlackDeleted
    );
    printf("Friend listener registered\n");
}

// ============================================================
// 10.1.6 用户监听器 (User Listener)
// ============================================================
void onUserSelfInfoUpdated(int callbackID, char* userInfo) {
    printf("[User] Self info updated: %s\n", userInfo);
}

void onUserStatusChanged(int callbackID, char* status) {
    printf("[User] Status changed: %s\n", status);
}

// 注册用户监听器
void registerUserListener() {
    RegisterUserListener(
        (int)onUserSelfInfoUpdated,
        (int)onUserStatusChanged
    );
    printf("User listener registered\n");
}

// ============================================================
// 10.1.7 信令监听器 (Signaling Listener)
// ============================================================
void onSignalingReceiveNewInvitation(int callbackID, char* invitation) {
    printf("[Signaling] New invitation: %s\n", invitation);
}

void onSignalingInviteeAccepted(int callbackID, char* invitation) {
    printf("[Signaling] Invitee accepted: %s\n", invitation);
}

void onSignalingInviteeAcceptedByOtherDevice(int callbackID, char* invitation) {
    printf("[Signaling] Accepted by other device: %s\n", invitation);
}

void onSignalingInviteeRejected(int callbackID, char* invitation) {
    printf("[Signaling] Invitee rejected: %s\n", invitation);
}

void onSignalingInviteeRejectedByOtherDevice(int callbackID, char* invitation) {
    printf("[Signaling] Rejected by other device: %s\n", invitation);
}

void onSignalingInvitationCancelled(int callbackID, char* invitation) {
    printf("[Signaling] Invitation cancelled: %s\n", invitation);
}

void onSignalingInvitationTimeout(int callbackID, char* invitation) {
    printf("[Signaling] Invitation timeout: %s\n", invitation);
}

void onSignalingHangUp(int callbackID, char* info) {
    printf("[Signaling] Hang up: %s\n", info);
}

void onSignalingRoomParticipantConnected(int callbackID, char* info) {
    printf("[Signaling] Room participant connected: %s\n", info);
}

void onSignalingRoomParticipantDisconnected(int callbackID, char* info) {
    printf("[Signaling] Room participant disconnected: %s\n", info);
}

// 注册信令监听器
void registerSignalingListener() {
    RegisterSignalingListener(
        (int)onSignalingReceiveNewInvitation,
        (int)onSignalingInviteeAccepted,
        (int)onSignalingInviteeAcceptedByOtherDevice,
        (int)onSignalingInviteeRejected,
        (int)onSignalingInviteeRejectedByOtherDevice,
        (int)onSignalingInvitationCancelled,
        (int)onSignalingInvitationTimeout,
        (int)onSignalingHangUp,
        (int)onSignalingRoomParticipantConnected,
        (int)onSignalingRoomParticipantDisconnected
    );
    printf("Signaling listener registered\n");
}

// ============================================================
// 10.1.8 自定义业务监听器 (Custom Business Listener)
// ============================================================
void onRecvCustomBusinessMessage(int callbackID, char* message) {
    printf("[Custom] Received: %s\n", message);
}

// 注册自定义业务监听器
void registerCustomBusinessListener() {
    RegisterCustomBusinessListener((int)onRecvCustomBusinessMessage);
    printf("Custom business listener registered\n");
}

// ============================================================
// 10.1.9 消息 KV 信息监听器 (Message KV Info Listener)
// ============================================================
void onMessageKvInfoChanged(int callbackID, char* kvInfo) {
    printf("[MsgKV] Info changed: %s\n", kvInfo);
}

// 注册消息 KV 信息监听器
void registerMsgKvInfoListener() {
    RegisterMsgKvInfoListener((int)onMessageKvInfoChanged);
    printf("Message KV info listener registered\n");
}

// ============================================================
// 10.1.10 Base 回调 (Base Callback)
// ============================================================
void onSuccess(int callbackID, char* data) {
    printf("[Base] Success: callbackID=%d, data=%s\n", callbackID, data);
}

void onError(int callbackID, int code, char* message) {
    printf("[Base] Error: callbackID=%d, code=%d, message=%s\n", callbackID, code, message);
}

// ============================================================
// 10.1.11 上传文件回调 (Upload File Callbacks - 8个方法)
// ============================================================
void onUploadOpen(long long fileSize) {
    printf("[Upload] Open: fileSize=%lld\n", fileSize);
}

void onUploadPartSize(long long partSize, int partNumber) {
    printf("[Upload] Part size: size=%lld, number=%d\n", partSize, partNumber);
}

void onUploadHashProgress(int index, long long size, char* partHash) {
    printf("[Upload] Hash progress: index=%d, size=%lld\n", index, size);
}

void onUploadHashComplete(char* partsHash, char* fileHash) {
    printf("[Upload] Hash complete: fileHash=%s\n", fileHash);
}

void onUploadID(char* uploadID) {
    printf("[Upload] Upload ID: %s\n", uploadID);
}

void onUploadPartComplete(int index, long long partSize, char* partHash) {
    printf("[Upload] Part complete: index=%d, size=%lld\n", index, partSize);
}

void onUploadComplete(long long fileSize, long long streamSize, long long storageSize) {
    printf("[Upload] Complete: fileSize=%lld, storageSize=%lld\n", fileSize, storageSize);
}

void onUploadFinish(long long size, char* url, int fileType) {
    printf("[Upload] Finish: size=%lld, url=%s, type=%d\n", size, url, fileType);
    // 上传完成时回调会自动清理，无需手动注销
}

// ============================================================
// 10.1.12 日志上传回调 (Upload Log Callback)
// ============================================================
void onUploadLogProgress(long long current, long long total) {
    printf("[UploadLog] Progress: %lld/%lld (%.1f%%)\n", current, total,
           total > 0 ? (float)current / total * 100 : 0);
}

// ============================================================
// 10.1.13 发送消息回调 (SendMsgCallback - Base + OnProgress)
// ============================================================
void onSendSuccess(int callbackID, char* data) {
    printf("[Send] Success: callbackID=%d, data=%s\n", callbackID, data);
}

void onSendError(int callbackID, int code, char* message) {
    printf("[Send] Error: callbackID=%d, code=%d, message=%s\n", callbackID, code, message);
}

void onSendProgress(int callbackID, int progress) {
    printf("[Send] Progress: callbackID=%d, progress=%d%%\n", callbackID, progress);
    // 当 progress >= 100 时，回调会自动清理
}

// ============================================================
// 10.2 注册所有回调的完整流程
// ============================================================

void registerAllCallbacks() {
    printf("\n=== Registering All Callbacks ===\n");
    
    // Step 1: 注册所有 Listener（全局，只需注册一次）
    registerConnListener();
    registerMsgListener();
    registerConvListener();
    registerGroupListener();
    registerFriendListener();
    registerUserListener();
    registerSignalingListener();
    registerCustomBusinessListener();
    registerMsgKvInfoListener();
    
    // Step 2: 分配独立的回调 ID
    g_baseCallbackID = 2;           // Base 回调 ID (范围 1-63)
    g_uploadCallbackID = 3;         // 上传进度回调 ID
    g_uploadLogsCallbackID = 4;     // 日志上传回调 ID
    g_sendReceiptCallbackID = 5;    // 发送进度回调 ID
    
    // Step 3: 注册 Base 回调
    RegisterBaseCallback(
        g_baseCallbackID,
        (int)onSuccess,
        (int)onError
    );
    printf("Base callback registered (ID=%d)\n", g_baseCallbackID);
    
    // Step 4: 注册上传文件回调（8 个方法）
    RegisterUploadFileCallback(
        g_uploadCallbackID,
        (int)onUploadOpen,
        (int)onUploadPartSize,
        (int)onUploadHashProgress,
        (int)onUploadHashComplete,
        (int)onUploadID,
        (int)onUploadPartComplete,
        (int)onUploadComplete,
        (int)onUploadFinish
        // 注意：SDK 的 UploadFileCallback 不包含 onUploadProgress
    );
    printf("Upload file callbacks registered (ID=%d)\n", g_uploadCallbackID);
    
    // Step 5: 注册日志上传回调
    RegisterUploadLogProgress(
        g_uploadLogsCallbackID,
        (int)onUploadLogProgress
    );
    printf("Upload log callback registered (ID=%d)\n", g_uploadLogsCallbackID);
    
    // Step 6: 注册发送消息回调（Base + OnProgress）
    RegisterSendMsgCallback(
        g_sendReceiptCallbackID,
        (int)onSendSuccess,     // Base 成功回调
        (int)onSendError,       // Base 错误回调
        (int)onSendProgress     // 发送进度回调
    );
    printf("Send message callback registered (ID=%d)\n", g_sendReceiptCallbackID);
    // 注意：回调完成后会自动清理，无需手动注销

    printf("\n=== All Callbacks Registered Successfully ===\n");
}

// ============================================================
// 10.3 注销回调（仅适用于需要手动管理的回调）
// ============================================================

void unregisterCallbacks() {
    printf("\n=== Unregistering Callbacks ===\n");
    
    // 仅 Base 回调和上传文件回调需要手动注销
    // 发送消息回调会在 progress >= 100 时自动清理
    if (g_baseCallbackID >= 0) {
        UnregisterBaseCallback(g_baseCallbackID);
        printf("Base callback unregistered (ID=%d)\n", g_baseCallbackID);
    }
    
    if (g_uploadCallbackID >= 0) {
        UnregisterUploadFileCallback(g_uploadCallbackID);
        printf("Upload callbacks unregistered (ID=%d)\n", g_uploadCallbackID);
    }
    
    if (g_uploadLogsCallbackID >= 0) {
        UnregisterUploadLogProgress(g_uploadLogsCallbackID);
        printf("Upload log callback unregistered (ID=%d)\n", g_uploadLogsCallbackID);
    }
    
    // 注意：SendMsgCallback 无需手动注销，会自动清理
    
    // 注销所有 Listener
    UnregisterConnListener();
    UnregisterMsgListener();
    UnregisterConvListener();
    UnregisterGroupListener();
    UnregisterFriendListener();
    UnregisterUserListener();
    UnregisterSignalingListener();
    UnregisterCustomBusinessListener();
    UnregisterMsgKvInfoListener();
    
    printf("\n=== All Callbacks Unregistered ===\n");
}

// ============================================================
// 10.4 SendMsgCallback 完整示例
// ============================================================

void exampleSendMessageCallback() {
    const char* operationID = "send_msg_001";
    const char* message = "{\"msg\":\"hello\"}";
    const char* recvID = "user456";
    const char* groupID = "";  // 单聊为空
    const char* offlinePushInfo = "{}";
    int isOnlineOnly = 0;
    
    // 分配回调 ID
    int sendMsgCallbackID = 10;
    
    // 注册发送消息回调（同时包含 Base 和 OnProgress）
    RegisterSendMsgCallback(
        sendMsgCallbackID,
        (int)onSendSuccess,
        (int)onSendError,
        (int)onSendProgress
    );
    
    // 调用发送函数
    SendMessage(
        sendMsgCallbackID,
        message, recvID, groupID, offlinePushInfo, operationID, isOnlineOnly
    );
    
    // 注意：
    // 1. 当 onProgress 回调的 progress >= 100 时，会自动清理 OnProgress
    // 2. 当 onSuccess 或 onError 触发时，会自动清理 Base 回调
    // 3. 无需手动调用 UnregisterSendMsgCallback
}

// ============================================================
// 10.5 完整使用示例
// ============================================================

void exampleUsage() {
    const char* operationID = "example_001";
    
    // 初始化 SDK
    // InitSDK(config, operationID);
    
    // 注册所有回调
    registerAllCallbacks();
    
    // ========== 示例 1: 上传文件 ==========
    const char* uploadReq = "{\"filePath\": \"/data/test.jpg\"}";
    // UploadFile(g_baseCallbackID, g_uploadCallbackID, operationID, uploadReq);
    // 注意：上传完成后回调会自动清理
    
    // ========== 示例 2: 发送消息 ==========
    exampleSendMessageCallback();
    // 注意：发送完成后回调会自动清理
    
    // ========== 示例 3: 上传日志 ==========
    // UploadLog(g_baseCallbackID, g_uploadLogsCallbackID, operationID);
    // 注意：日志上传完成后回调会自动清理
    
    // 业务完成后注销 Base 回调和上传回调（如果需要提前取消）
    // unregisterCallbacks();
}

// ============================================================
// 10.5 回调 ID 分配策略
// ============================================================

/*
回调 ID 分配建议：

| 回调类型 | ID 范围 | 说明 | 自动清理 |
|----------|---------|------|----------|
| Listener | 0 | 固定为 0，全局共享 | 否 |
| Base 回调 | 1-20 | 基础操作回调 | 是 |
| 上传回调 | 21-40 | 文件上传相关 | 是 |
| 发送回调 | 41-50 | 消息发送相关 | 是 |
| 其他 | 51-63 | 预留 | - |

示例分配：
- g_baseCallbackID = 2
- g_uploadCallbackID = 3
- g_uploadLogsCallbackID = 4
- g_sendReceiptCallbackID = 5
- g_sendMsgCallbackID = 10

注意：SendMsgCallback 同时包含 Base 和 OnProgress，统一使用一个 callbackID。
*/
```

// ============================================================
// 10.6 FriendListener 使用示例
// ============================================================

void exampleFriendListenerUsage() {
    printf("\n=== FriendListener Example ===\n");
    
    // 注册好友监听器
    // 注意：Listener 回调使用 index 0，只需注册一次
    RegisterFriendListener(
        (int)onFriendApplicationAdded,     // 好友申请新增
        (int)onFriendApplicationDeleted,   // 好友申请删除
        (int)onFriendApplicationAccepted,  // 好友申请被接受
        (int)onFriendApplicationRejected,  // 好友申请被拒绝
        (int)onFriendAdded,                // 好友新增
        (int)onFriendDeleted,              // 好友删除
        (int)onFriendInfoChanged,          // 好友信息变更
        (int)onBlackAdded,                 // 黑名单新增
        (int)onBlackDeleted                // 黑名单删除
    );
    
    printf("Friend listener registered successfully\n");
    
    // 好友监听器是全局的，一旦注册会持续接收事件
    // 直到调用 UnregisterFriendListener() 注销
}

// 注销好友监听器
void unregisterFriendListener() {
    UnregisterFriendListener();
    printf("Friend listener unregistered\n");
}

// ============================================================
// 10.7 完整 SDK 初始化流程示例
// ============================================================

void initializeSDKWithCallbacks() {
    const char* operationID = "init_001";
    
    printf("\n=== SDK Initialization Flow ===\n");
    
    // Step 1: 初始化 SDK
    // InitSDK(config, operationID);
    
    // Step 2: 注册所有 Listener（全局，只需一次）
    registerConnListener();        // 连接状态监听
    registerMsgListener();         // 消息监听
    registerConvListener();        // 会话监听
    registerGroupListener();       // 群组监听
    registerFriendListener();      // 好友监听
    registerUserListener();        // 用户监听
    registerSignalingListener();   // 信令监听
    
    // Step 3: 分配动态回调 ID（用于需要回调的操作）
    int baseCallbackID = 2;
    
    // Step 4: 注册 Base 回调
    RegisterBaseCallback(baseCallbackID, (int)onSuccess, (int)onError);
    
    // Step 5: 调用需要回调的 SDK 函数
    // Login(baseCallbackID, uid, token, operationID);
    // GetAllConversationList(baseCallbackID, operationID);
    
    // Step 6: SDK 运行中，Listener 会持续接收事件
    // Base 回调会在操作完成后自动清理
    
    // Step 7: SDK 销毁时注销所有回调
    // UnregisterBaseCallback(baseCallbackID);
    // UnregisterConnListener();
    // UnregisterMsgListener();
    // ... 其他 Listener
}
```
