# OpenIM SDK API 参考文档

本文档基于 `Open_im_sdk` 库的 API 编写，包含所有可用的方法。

---

## 目录

- [初始化与登录](#初始化与登录)
- [用户](#用户)
- [会话](#会话)
- [消息](#消息)
- [好友](#好友)
- [群组](#群组)
- [工具](#工具)

---

## 初始化与登录

| 方法名 | 说明 |
|--------|------|
| `initSDK` | 初始化 SDK |
| `login` | 登录 |
| `logout` | 登出 |
| `getLoginStatus` | 获取登录状态 |
| `getLoginUserID` | 获取当前登录用户 ID |
| `uploadFile` | 上传文件 |

---

## 用户

| 方法名 | 说明 |
|--------|------|
| `setUserListener` | 设置用户监听器 |
| `setCustomBusinessListener` | 设置自定义业务监听器 |
| `getUsersInfo` | 获取用户信息 |
| `getSelfUserInfo` | 获取当前用户信息 |
| `setSelfInfo` | 设置当前用户信息 |
| `getUserStatus` | 获取用户在线状态 |
| `subscribeUsersStatus` | 订阅用户状态 |
| `unsubscribeUsersStatus` | 取消订阅用户状态 |
| `getSubscribeUsersStatus` | 获取已订阅的用户状态 |
| `setAppBackgroundStatus` | 设置应用后台状态 |
| `networkStatusChanged` | 网络状态变化 |

---

## 会话

| 方法名 | 说明 |
|--------|------|
| `setConversationListener` | 设置会话监听器 |
| `getAllConversationList` | 获取所有会话列表 |
| `getConversationListSplit` | 分页获取会话列表 |
| `getOneConversation` | 获取单个会话 |
| `getMultipleConversation` | 获取多个会话 |
| `getConversationIDBySessionType` | 根据会话类型获取会话 ID |
| `getTotalUnreadMsgCount` | 获取未读消息总数 |
| `markConversationMessageAsRead` | 标记会话消息已读 |
| `setConversation` | 设置会话属性 |
| `setConversationDraft` | 设置会话草稿 |
| `pinConversation` | 置顶/取消置顶会话 |
| `setConversationRecvMessageOpt` | 设置会话消息接收选项 |
| `setConversationPrivateChat` | 设置会话私密聊天 |
| `setConversationBurnDuration` | 设置会话阅后即焚时长 |
| `resetConversationGroupAtType` | 重置会话@提醒类型 |
| `hideConversation` | 隐藏会话 |
| `hideAllConversations` | 隐藏所有会话 |
| `clearConversationAndDeleteAllMsg` | 清除会话并删除所有消息 |
| `deleteConversationAndDeleteAllMsg` | 删除会话并删除所有消息 |

---

## 消息

| 方法名 | 说明 |
|--------|------|
| `setAdvancedMsgListener` | 设置高级消息监听器 |
| `setBatchMsgListener` | 设置批量消息监听器 |
| `setSignalingListener` | 设置信令监听器 |

### 消息创建

| 方法名 | 说明 |
|--------|------|
| `createTextMessage` | 创建文本消息 |
| `createTextAtMessage` | 创建@消息 |
| `createQuoteMessage` | 创建引用消息 |
| `createCardMessage` | 创建卡片消息 |
| `createImageMessageFromFullPath` | 从本地路径创建图片消息 |
| `createImageMessageByURL` | 从 URL 创建图片消息 |
| `createSoundMessageFromFullPath` | 从本地路径创建语音消息 |
| `createSoundMessageByURL` | 从 URL 创建语音消息 |
| `createVideoMessageFromFullPath` | 从本地路径创建视频消息 |
| `createVideoMessageByURL` | 从 URL 创建视频消息 |
| `createFileMessageFromFullPath` | 从本地路径创建文件消息 |
| `createFileMessageByURL` | 从 URL 创建文件消息 |
| `createMergerMessage` | 创建合并消息 |
| `createForwardMessage` | 创建转发消息 |
| `createLocationMessage` | 创建位置消息 |
| `createCustomMessage` | 创建自定义消息 |
| `createFaceMessage` | 创建表情消息 |

### 消息操作

| 方法名 | 说明 |
|--------|------|
| `sendMessage` | 发送消息 |
| `sendMessageNotOss` | 发送消息（不通过 OSS） |
| `typingStatusUpdate` | 更新输入状态 |
| `changeInputStates` | 更改输入状态 |
| `getInputStates` | 获取输入状态 |
| `revokeMessage` | 撤回消息 |
| `deleteMessage` | 删除消息 |
| `deleteMessageFromLocalStorage` | 从本地存储删除消息 |
| `deleteAllMsgFromLocal` | 删除本地所有消息 |
| `deleteAllMsgFromLocalAndSvr` | 删除本地和服务器所有消息 |
| `searchLocalMessages` | 搜索本地消息 |
| `getAdvancedHistoryMessageList` | 获取高级历史消息列表 |
| `getAdvancedHistoryMessageListReverse` | 反向获取高级历史消息列表 |
| `findMessageList` | 查找消息列表 |
| `insertSingleMessageToLocalStorage` | 插入单聊消息到本地存储 |
| `insertGroupMessageToLocalStorage` | 插入群聊消息到本地存储 |
| `setMessageLocalEx` | 设置消息本地扩展信息 |

---

## 好友

| 方法名 | 说明 |
|--------|------|
| `setFriendListener` | 设置好友监听器 |
| `getFriendList` | 获取好友列表 |
| `getFriendListPage` | 分页获取好友列表 |
| `getSpecifiedFriendsInfo` | 获取指定好友信息 |
| `searchFriends` | 搜索好友 |
| `addFriend` | 添加好友 |
| `checkFriend` | 检查好友关系 |
| `updateFriends` | 更新好友信息 |
| `getFriendApplicationUnhandledCount` | 获取未处理好友申请数量 |
| `deleteFriend` | 删除好友 |
| `setFriendRemark` | 设置好友备注 |
| `getFriendApplicationListAsApplicant` | 获取作为申请人的好友申请列表 |
| `getFriendApplicationListAsRecipient` | 获取作为接收人的好友申请列表 |
| `acceptFriendApplication` | 接受好友申请 |
| `refuseFriendApplication` | 拒绝好友申请 |
| `addBlack` | 添加黑名单 |
| `getBlackList` | 获取黑名单 |
| `removeBlack` | 移除黑名单 |

---

## 群组

| 方法名 | 说明 |
|--------|------|
| `setGroupListener` | 设置群组监听器 |
| `createGroup` | 创建群组 |
| `joinGroup` | 加入群组 |
| `quitGroup` | 退出群组 |
| `dismissGroup` | 解散群组 |
| `getJoinedGroupList` | 获取已加入的群组列表 |
| `getJoinedGroupListPage` | 分页获取已加入的群组列表 |
| `getSpecifiedGroupsInfo` | 获取指定群组信息 |
| `getGroupMemberList` | 获取群成员列表 |
| `getGroupMemberOwnerAndAdmin` | 获取群主和管理员 |
| `getSpecifiedGroupMembersInfo` | 获取指定群成员信息 |
| `getUsersInGroup` | 获取群内指定用户 |
| `searchGroupMembers` | 搜索群成员 |
| `setGroupInfo` | 设置群组信息 |
| `changeGroupMute` | 更改群组禁言状态 |
| `changeGroupMemberMute` | 更改群成员禁言状态 |
| `setGroupMemberInfo` | 设置群成员信息 |
| `inviteUserToGroup` | 邀请用户入群 |
| `kickGroupMember` | 踢出群成员 |
| `transferGroupOwner` | 转让群主 |
| `getGroupApplicationListAsApplicant` | 获取作为申请人的群申请列表 |
| `getGroupApplicationListAsRecipient` | 获取作为接收人的群申请列表 |
| `getGroupApplicationUnhandledCount` | 获取未处理群申请数量 |
| `acceptGroupApplication` | 接受群申请 |
| `refuseGroupApplication` | 拒绝群申请 |
| `searchGroups` | 搜索群组 |
| `getGroupMemberListByJoinTimeFilter` | 按加入时间过滤获取群成员列表 |
| `isJoinGroup` | 检查是否已加入群组 |

---

## 工具

| 方法名 | 说明 |
|--------|------|
| `updateFcmToken` | 更新 FCM 令牌 |
| `setAppBadge` | 设置应用角标 |
| `uploadLogs` | 上传日志 |
| `logs` | 记录日志 |
| `getSdkVersion` | 获取 SDK 版本 |
| `unInitSDK` | 反初始化 SDK |
| `getAtAllTag` | 获取@所有人标签 |
