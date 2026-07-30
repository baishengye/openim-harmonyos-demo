/**
 * OpenIM SDK for HarmonyOS
 * 监听器接口 - 定义SDK事件回调接口
 */

/**
 * 基础回调接口
 */
export interface BaseCallback {
  /** 错误回调 */
  onError(errCode: number, errMsg: string): void;
  /** 成功回调 */
  onSuccess(data: string): void;
}

/**
 * 发送消息回调接口
 */
export interface SendMsgCallBack extends BaseCallback {
  /** 发送进度回调 */
  onProgress(progress: number): void;
}

/**
 * 上传文件回调接口
 */
export interface UploadFileCallback {
  /** 开始上传 */
  open(size: number): void;
  /** 分片大小回调 */
  partSize(partSize: number, num: number): void;
  /** 分片哈希进度回调 */
  hashPartProgress(index: number, size: number, partHash: string): void;
  /** 分片哈希完成回调 */
  hashPartComplete(partsHash: string, fileHash: string): void;
  /** 上传ID回调 */
  uploadID(uploadID: string): void;
  /** 分片上传完成回调 */
  uploadPartComplete(index: number, partSize: number, partHash: string): void;
  /** 上传完成回调 */
  uploadComplete(fileSize: number, streamSize: number, storageSize: number): void;
  /** 结束回调 */
  complete(size: number, url: string, typ: number): void;
}

/**
 * 上传日志进度回调接口
 */
export interface UploadLogProgress {
  /** 上传进度回调 */
  onProgress(current: number, size: number): void;
}

/**
 * 连接状态监听器接口
 */
export interface ConnListener {
  /** 正在连接中 */
  onConnecting(): void;
  /** 连接成功 */
  onConnectSuccess(): void;
  /** 连接失败 */
  onConnectFailed(errCode: number, errMsg: string): void;
  /** 被踢下线 */
  onKickedOffline(): void;
  /** 用户Token过期 */
  onUserTokenExpired(): void;
  /** 用户Token无效 */
  onUserTokenInvalid(errMsg: string): void;
}

/**
 * 消息监听器接口
 */
export interface MsgListener {
  /** 收到新消息 */
  onRecvNewMessage(message: string): void;
  /** 收到C2C消息已读回执 */
  onRecvC2CReadReceipt(msgReceiptList: string): void;
  /** 收到消息撤回通知 */
  onNewRecvMessageRevoked(messageRevoked: string): void;
  /** 收到离线新消息 */
  onRecvOfflineNewMessage(message: string): void;
  /** 消息被删除 */
  onMsgDeleted(message: string): void;
  /** 收到仅在线消息 */
  onRecvOnlineOnlyMessage(message: string): void;
}

/**
 * 会话监听器接口
 */
export interface ConvListener {
  /** 开始同步服务器会话 */
  onSyncServerStart(reinstalled: boolean): void;
  /** 同步服务器会话完成 */
  onSyncServerFinish(reinstalled: boolean): void;
  /** 同步服务器会话进度 */
  onSyncServerProgress(progress: number): void;
  /** 同步服务器会话失败 */
  onSyncServerFailed(reinstalled: boolean): void;
  /** 收到新会话 */
  onNewConversation(conversationList: string): void;
  /** 会话发生变化 */
  onConversationChanged(conversationList: string): void;
  /** 总未读消息数变化 */
  onTotalUnreadMessageCountChanged(totalUnreadCount: number): void;
  /** 会话用户输入状态变化 */
  onConversationUserInputStatusChanged(change: string): void;
}

/**
 * 群组监听器接口
 */
export interface GroupListener {
  /** 加入群组增加 */
  onJoinedGroupAdded(groupInfo: string): void;
  /** 加入群组删除 */
  onJoinedGroupDeleted(groupInfo: string): void;
  /** 群组成员增加 */
  onGroupMemberAdded(groupMemberInfo: string): void;
  /** 群组成员删除 */
  onGroupMemberDeleted(groupMemberInfo: string): void;
  /** 收到群申请 */
  onGroupApplicationAdded(groupApplication: string): void;
  /** 群申请被删除 */
  onGroupApplicationDeleted(groupApplication: string): void;
  /** 群组信息变化 */
  onGroupInfoChanged(groupInfo: string): void;
  /** 群组被解散 */
  onGroupDismissed(groupInfo: string): void;
  /** 群组成员信息变化 */
  onGroupMemberInfoChanged(groupMemberInfo: string): void;
  /** 群申请被接受 */
  onGroupApplicationAccepted(groupApplication: string): void;
  /** 群申请被拒绝 */
  onGroupApplicationRejected(groupApplication: string): void;
}

/**
 * 好友监听器接口
 */
export interface FriendListener {
  /** 收到好友申请 */
  onFriendApplicationAdded(friendApplication: string): void;
  /** 好友申请被删除 */
  onFriendApplicationDeleted(friendApplication: string): void;
  /** 好友申请被接受 */
  onFriendApplicationAccepted(friendApplication: string): void;
  /** 好友申请被拒绝 */
  onFriendApplicationRejected(friendApplication: string): void;
  /** 添加好友 */
  onFriendAdded(friendInfo: string): void;
  /** 删除好友 */
  onFriendDeleted(friendInfo: string): void;
  /** 好友信息变化 */
  onFriendInfoChanged(friendInfo: string): void;
  /** 被加入黑名单 */
  onBlackAdded(blackInfo: string): void;
  /** 从黑名单移除 */
  onBlackDeleted(blackInfo: string): void;
}

/**
 * 用户监听器接口
 */
export interface UserListener {
  /** 自身信息更新 */
  onSelfInfoUpdated(userInfo: string): void;
  /** 用户在线状态变化 */
  onUserStatusChanged(userOnlineStatus: string): void;
}

/**
 * 信令监听器接口
 */
export interface SignalingListener {
  /** 收到新的邀请 */
  onReceiveNewInvitation(receiveNewInvitationCallback: string): void;
  /** 被邀请者接受 */
  onInviteeAccepted(inviteeAcceptedCallback: string): void;
  /** 被邀请者在其他设备上接受 */
  onInviteeAcceptedByOtherDevice(inviteeAcceptedCallback: string): void;
  /** 被邀请者拒绝 */
  onInviteeRejected(inviteeRejectedCallback: string): void;
  /** 被邀请者在其他设备上拒绝 */
  onInviteeRejectedByOtherDevice(inviteeRejectedCallback: string): void;
  /** 邀请被取消 */
  onInvitationCancelled(invitationCancelledCallback: string): void;
  /** 邀请超时 */
  onInvitationTimeout(invitationTimeoutCallback: string): void;
  /** 挂断 */
  onHangUp(hangUpCallback: string): void;
  /** 房间参与者连接 */
  onRoomParticipantConnected(onRoomParticipantConnectedCallback: string): void;
  /** 房间参与者断开 */
  onRoomParticipantDisconnected(onRoomParticipantDisconnectedCallback: string): void;
}

/**
 * 自定义业务监听器接口
 */
export interface CustomBusinessListener {
  /** 收到自定义业务消息 */
  onRecvCustomBusinessMessage(businessMessage: string): void;
}

/**
 * 消息KV信息监听器接口
 */
export interface MsgKvInfoListener {
  /** 消息KV信息变化 */
  onMessageKvInfoChanged(messageChangedList: string): void;
}
