/**
 * OpenIM SDK for HarmonyOS
 * 监听器实现类 - 封装用户监听器并代理到原生层
 */

import { ConnListener,
  MsgListener,
  BatchMsgListener,
  ConvListener,
  GroupListener,
  FriendListener,
  UserListener,
  SignalingListener ,
  MsgKvInfoListener ,
  BaseCallback,
  CompletionCallback,
  UploadFileCallback,
  UploadLogProgress,
  CustomBusinessListener,
  SendMsgCallBack} from './listener';
import { ConnListener as NativeConnListener,
  MsgListener as NativeMsgListener,
  BatchMsgListener as NativeBatchMsgListener,
  ConvListener as NativeConvListener,
  GroupListener as NativeGroupListener,
  FriendListener as NativeFriendListener,
  UserListener as NativeUserListener,
  SignalingListener as NativeSignalingListener,
  CustomBusinessListener as NativeCustomBusinessListener,
  MsgKvInfoListener  as NativeMsgKvInfoListener,
  BaseCallback as NativeBaseCallback,
  UploadFileCallback as NativeUploadFileCallback,
  UploadLogProgress as NativeUploadLogProgress,
  SendMsgCallBack as NativeSendMsgCallBack
} from 'libimsdk.so';
import { info, debug } from '../internal/log/Logger';
import { JSON } from '@kit.ArkTS';
import { ConversationInfo, Message, MessageEntity, RevokedInfo, UserCommand } from '../models/entity';
import { toArray, toObject } from '../utils/JsonUtil';

/**
 * 连接状态监听器包装类
 */
export class ConnListenerWrapper implements NativeConnListener {
  private listener: ConnListener | null = null;

  constructor(listener: ConnListener | null) {
    this.listener = listener;
  }

  onConnecting(): void {
    debug('ConnListener', 'onConnecting');
    if (this.listener != null) {
      this.listener.onConnecting();
    }
  }

  onConnectSuccess(): void {
    info('ConnListener', 'onConnectSuccess');
    if (this.listener != null) {
      this.listener.onConnectSuccess();
    }
  }

  onConnectFailed(errCode: number, errMsg: string): void {
    info('ConnListener', `onConnectFailed: ${errCode} - ${errMsg}`);
    if (this.listener != null) {
      this.listener.onConnectFailed(errCode, errMsg);
    }
  }

  onKickedOffline(): void {
    info('ConnListener', 'onKickedOffline');
    if (this.listener != null) {
      this.listener.onKickedOffline();
    }
  }

  onUserTokenExpired(): void {
    info('ConnListener', 'onUserTokenExpired');
    if (this.listener != null) {
      this.listener.onUserTokenExpired();
    }
  }

  onUserTokenInvalid(errMsg: string): void {
    info('ConnListener', `onUserTokenInvalid: ${errMsg}`);
    if (this.listener != null) {
      this.listener.onUserTokenInvalid(errMsg);
    }
  }
}

/**
 * 消息监听器包装类
 */
export class MsgListenerWrapper implements NativeMsgListener {
  private listener: MsgListener | null = null;

  constructor(listener: MsgListener | null) {
    this.listener = listener;
  }

  onRecvNewMessage(message: string): void {
    debug('MsgListener', `onRecvNewMessage: ${message}`);
    const parsed = toObject<Message>(message);
    if (this.listener != null && parsed != null) {
      this.listener.onRecvNewMessage(parsed);
    }
  }

  onRecvC2CReadReceipt(msgReceiptList: string): void {
    debug('MsgListener', `onRecvC2CReadReceipt: ${msgReceiptList}`);
    if (this.listener != null) {
      this.listener.onRecvC2CReadReceipt(toArray(msgReceiptList));
    }
  }

  onNewRecvMessageRevoked(messageRevoked: string): void {
    debug('MsgListener', `onNewRecvMessageRevoked: ${messageRevoked}`);
    const parsed = toObject<RevokedInfo>(messageRevoked);
    if (this.listener != null && parsed != null) {
      this.listener.onNewRecvMessageRevoked(parsed);
    }
  }

  onRecvOfflineNewMessage(message: string): void {
    debug('MsgListener', `onRecvOfflineNewMessage: ${message}`);
    if (this.listener != null) {
      this.listener.onRecvOfflineNewMessage(toArray<Message>(message));
    }
  }

  onMsgDeleted(message: string): void {
    debug('MsgListener', `onMsgDeleted: ${message}`);
    const parsed = toObject<Message>(message);
    if (this.listener != null && parsed != null) {
      this.listener.onMsgDeleted(parsed);
    }
  }

  onRecvOnlineOnlyMessage(message: string): void {
    debug('MsgListener', `onRecvOnlineOnlyMessage: ${message}`);
    if (this.listener != null) {
      this.listener.onRecvOnlineOnlyMessage(message);
    }
  }
}

export class BatchMsgListenerWrapper implements NativeBatchMsgListener {
  private listener: BatchMsgListener | null = null;

  constructor(listener: BatchMsgListener | null) {
    this.listener = listener;
  }

  onRecvNewMessages(messageList: string): void {
    debug('BatchMsgListener', `onRecvNewMessages: ${messageList}`);
    if (this.listener != null) {
      this.listener.onRecvNewMessages(toArray<Message>(messageList));
    }
  }

  onRecvOfflineNewMessages(messageList: string): void {
    debug('BatchMsgListener', `onRecvOfflineNewMessages: ${messageList}`);
    if (this.listener != null) {
      this.listener.onRecvOfflineNewMessages(toArray<Message>(messageList));
    }
  }
}

/**
 * 会话监听器包装类
 */
export class ConvListenerWrapper implements NativeConvListener {
  private listener: ConvListener | null = null;

  constructor(listener: ConvListener | null) {
    this.listener = listener;
  }

  onSyncServerStart(reinstalled: boolean): void {
    debug('ConvListener', `onSyncServerStart: ${reinstalled}`);
    if (this.listener != null) {
      this.listener.onSyncServerStart(reinstalled);
    }
  }

  onSyncServerFinish(reinstalled: boolean): void {
    info('ConvListener', `onSyncServerFinish: ${reinstalled}`);
    if (this.listener != null) {
      this.listener.onSyncServerFinish(reinstalled);
    }
  }

  onSyncServerProgress(progress: number): void {
    debug('ConvListener', `onSyncServerProgress: ${progress}`);
    if (this.listener != null) {
      this.listener.onSyncServerProgress(progress);
    }
  }

  onSyncServerFailed(reinstalled: boolean): void {
    info('ConvListener', `onSyncServerFailed: ${reinstalled}`);
    if (this.listener != null) {
      this.listener.onSyncServerFailed(reinstalled);
    }
  }

  onNewConversation(conversationList: string): void {
    debug('ConvListener', `onNewConversation: ${conversationList}`);
    if (this.listener != null) {
      this.listener.onNewConversation(toArray<ConversationInfo>(conversationList));
    }
  }

  onConversationChanged(conversationList: string): void {
    debug('ConvListener', `onConversationChanged: ${conversationList}`);
    if (this.listener != null) {
      this.listener.onConversationChanged(toArray<ConversationInfo>(conversationList));
    }
  }

  onTotalUnreadMessageCountChanged(totalUnreadCount: number): void {
    debug('ConvListener', `onTotalUnreadMessageCountChanged: ${totalUnreadCount}`);
    if (this.listener != null) {
      this.listener.onTotalUnreadMessageCountChanged(totalUnreadCount);
    }
  }

  onConversationUserInputStatusChanged(change: string): void {
    debug('ConvListener', `onConversationUserInputStatusChanged: ${change}`);
    if (this.listener != null) {
      this.listener.onConversationUserInputStatusChanged(change);
    }
  }
}

/**
 * 群组监听器包装类
 */
export class GroupListenerWrapper implements NativeGroupListener {
  private listener: GroupListener | null = null;

  constructor(listener: GroupListener | null) {
    this.listener = listener;
  }

  onJoinedGroupAdded(groupInfo: string): void {
    info('GroupListener', `onJoinedGroupAdded: ${groupInfo}`);
    if (this.listener != null) {
      this.listener.onJoinedGroupAdded(toObject(groupInfo)!!);
    }
  }

  onJoinedGroupDeleted(groupInfo: string): void {
    info('GroupListener', `onJoinedGroupDeleted: ${groupInfo}`);
    if (this.listener != null) {
      this.listener.onJoinedGroupDeleted(toObject(groupInfo)!!);
    }
  }

  onGroupMemberAdded(groupMemberInfo: string): void {
    info('GroupListener', `onGroupMemberAdded: ${groupMemberInfo}`);
    if (this.listener != null) {
      this.listener.onGroupMemberAdded(toObject(groupMemberInfo)!!);
    }
  }

  onGroupMemberDeleted(groupMemberInfo: string): void {
    info('GroupListener', `onGroupMemberDeleted: ${groupMemberInfo}`);
    if (this.listener != null) {
      this.listener.onGroupMemberDeleted(toObject(groupMemberInfo)!!);
    }
  }

  onGroupApplicationAdded(groupApplication: string): void {
    info('GroupListener', `onGroupApplicationAdded: ${groupApplication}`);
    if (this.listener != null) {
      this.listener.onGroupApplicationAdded(toObject(groupApplication)!!);
    }
  }

  onGroupApplicationDeleted(groupApplication: string): void {
    info('GroupListener', `onGroupApplicationDeleted: ${groupApplication}`);
    if (this.listener != null) {
      this.listener.onGroupApplicationDeleted(toObject(groupApplication)!!);
    }
  }

  onGroupInfoChanged(groupInfo: string): void {
    info('GroupListener', `onGroupInfoChanged: ${groupInfo}`);
    if (this.listener != null) {
      this.listener.onGroupInfoChanged(toObject(groupInfo)!!);
    }
  }

  onGroupDismissed(groupInfo: string): void {
    info('GroupListener', `onGroupDismissed: ${groupInfo}`);
    if (this.listener != null) {
      this.listener.onGroupDismissed(toObject(groupInfo)!!);
    }
  }

  onGroupMemberInfoChanged(groupMemberInfo: string): void {
    info('GroupListener', `onGroupMemberInfoChanged: ${groupMemberInfo}`);
    if (this.listener != null) {
      this.listener.onGroupMemberInfoChanged(toObject(groupMemberInfo)!!);
    }
  }

  onGroupApplicationAccepted(groupApplication: string): void {
    info('GroupListener', `onGroupApplicationAccepted: ${groupApplication}`);
    if (this.listener != null) {
      this.listener.onGroupApplicationAccepted(toObject(groupApplication)!!);
    }
  }

  onGroupApplicationRejected(groupApplication: string): void {
    info('GroupListener', `onGroupApplicationRejected: ${groupApplication}`);
    if (this.listener != null) {
      this.listener.onGroupApplicationRejected(toObject(groupApplication)!!);
    }
  }
}

/**
 * 好友监听器包装类
 */
export class FriendListenerWrapper implements NativeFriendListener {
  private listener: FriendListener | null = null;

  constructor(listener: FriendListener | null) {
    this.listener = listener;
  }

  onFriendApplicationAdded(friendApplication: string): void {
    info('FriendListener', `onFriendApplicationAdded: ${friendApplication}`);
    if (this.listener != null) {
      this.listener.onFriendApplicationAdded(toObject(friendApplication)!!);
    }
  }

  onFriendApplicationDeleted(friendApplication: string): void {
    info('FriendListener', `onFriendApplicationDeleted: ${friendApplication}`);
    if (this.listener != null) {
      this.listener.onFriendApplicationDeleted(toObject(friendApplication)!!);
    }
  }

  onFriendApplicationAccepted(friendApplication: string): void {
    info('FriendListener', `onFriendApplicationAccepted: ${friendApplication}`);
    if (this.listener != null) {
      this.listener.onFriendApplicationAccepted(toObject(friendApplication)!!);
    }
  }

  onFriendApplicationRejected(friendApplication: string): void {
    info('FriendListener', `onFriendApplicationRejected: ${friendApplication}`);
    if (this.listener != null) {
      this.listener.onFriendApplicationRejected(toObject(friendApplication)!!);
    }
  }

  onFriendAdded(friendInfo: string): void {
    info('FriendListener', `onFriendAdded: ${friendInfo}`);
    if (this.listener != null) {
      this.listener.onFriendAdded(toObject(friendInfo)!!);
    }
  }

  onFriendDeleted(friendInfo: string): void {
    info('FriendListener', `onFriendDeleted: ${friendInfo}`);
    if (this.listener != null) {
      this.listener.onFriendDeleted(toObject(friendInfo)!!);
    }
  }

  onFriendInfoChanged(friendInfo: string): void {
    info('FriendListener', `onFriendInfoChanged: ${friendInfo}`);
    if (this.listener != null) {
      this.listener.onFriendInfoChanged(toObject(friendInfo)!!);
    }
  }

  onBlackAdded(blackInfo: string): void {
    info('FriendListener', `onBlackAdded: ${blackInfo}`);
    if (this.listener != null) {
      this.listener.onBlackAdded(toObject(blackInfo)!!);
    }
  }

  onBlackDeleted(blackInfo: string): void {
    info('FriendListener', `onBlackDeleted: ${blackInfo}`);
    if (this.listener != null) {
      this.listener.onBlackDeleted(toObject(blackInfo)!!);
    }
  }
}

/**
 * 用户监听器包装类
 */
export class UserListenerWrapper implements NativeUserListener {
  private listener: UserListener | null = null;

  constructor(listener: UserListener | null) {
    this.listener = listener;
  }

  onSelfInfoUpdated(userInfo: string): void {
    info('UserListener', `onSelfInfoUpdated: ${userInfo}`);
    if (this.listener != null) {
      this.listener.onSelfInfoUpdated(toObject(userInfo)!!);
    }
  }

  onUserStatusChanged(userOnlineStatus: string): void {
    info('UserListener', `onUserStatusChanged: ${userOnlineStatus}`);
    if (this.listener != null) {
      this.listener.onUserStatusChanged(toObject(userOnlineStatus)!!);
    }
  }

  onUserCommandAdd(userCommand: string): void {
    const parsed = toObject<UserCommand>(userCommand);
    if (this.listener != null && parsed != null) {
      this.listener.onUserCommandAdd(parsed);
    }
  }

  onUserCommandDelete(userCommand: string): void {
    const parsed = toObject<UserCommand>(userCommand);
    if (this.listener != null && parsed != null) {
      this.listener.onUserCommandDelete(parsed);
    }
  }

  onUserCommandUpdate(userCommand: string): void {
    const parsed = toObject<UserCommand>(userCommand);
    if (this.listener != null && parsed != null) {
      this.listener.onUserCommandUpdate(parsed);
    }
  }
}

/**
 * 信令监听器包装类
 */
export class SignalingListenerWrapper implements NativeSignalingListener {
  private listener: SignalingListener | null = null;

  constructor(listener: SignalingListener | null) {
    this.listener = listener;
  }

  onReceiveNewInvitation(receiveNewInvitationCallback: string): void {
    info('SignalingListener', `onReceiveNewInvitation: ${receiveNewInvitationCallback}`);
    if (this.listener != null) {
      this.listener.onReceiveNewInvitation(receiveNewInvitationCallback);
    }
  }

  onInviteeAccepted(inviteeAcceptedCallback: string): void {
    info('SignalingListener', `onInviteeAccepted: ${inviteeAcceptedCallback}`);
    if (this.listener != null) {
      this.listener.onInviteeAccepted(inviteeAcceptedCallback);
    }
  }

  onInviteeAcceptedByOtherDevice(inviteeAcceptedCallback: string): void {
    info('SignalingListener', `onInviteeAcceptedByOtherDevice: ${inviteeAcceptedCallback}`);
    if (this.listener != null) {
      this.listener.onInviteeAcceptedByOtherDevice(inviteeAcceptedCallback);
    }
  }

  onInviteeRejected(inviteeRejectedCallback: string): void {
    info('SignalingListener', `onInviteeRejected: ${inviteeRejectedCallback}`);
    if (this.listener != null) {
      this.listener.onInviteeRejected(inviteeRejectedCallback);
    }
  }

  onInviteeRejectedByOtherDevice(inviteeRejectedCallback: string): void {
    info('SignalingListener', `onInviteeRejectedByOtherDevice: ${inviteeRejectedCallback}`);
    if (this.listener != null) {
      this.listener.onInviteeRejectedByOtherDevice(inviteeRejectedCallback);
    }
  }

  onInvitationCancelled(invitationCancelledCallback: string): void {
    info('SignalingListener', `onInvitationCancelled: ${invitationCancelledCallback}`);
    if (this.listener != null) {
      this.listener.onInvitationCancelled(invitationCancelledCallback);
    }
  }

  onInvitationTimeout(invitationTimeoutCallback: string): void {
    info('SignalingListener', `onInvitationTimeout: ${invitationTimeoutCallback}`);
    if (this.listener != null) {
      this.listener.onInvitationTimeout(invitationTimeoutCallback);
    }
  }

  onHangUp(hangUpCallback: string): void {
    info('SignalingListener', `onHangUp: ${hangUpCallback}`);
    if (this.listener != null) {
      this.listener.onHangUp(hangUpCallback);
    }
  }

  onRoomParticipantConnected(onRoomParticipantConnectedCallback: string): void {
    info('SignalingListener', `onRoomParticipantConnected: ${onRoomParticipantConnectedCallback}`);
    if (this.listener != null) {
      this.listener.onRoomParticipantConnected(onRoomParticipantConnectedCallback);
    }
  }

  onRoomParticipantDisconnected(onRoomParticipantDisconnectedCallback: string): void {
    info('SignalingListener', `onRoomParticipantDisconnected: ${onRoomParticipantDisconnectedCallback}`);
    if (this.listener != null) {
      this.listener.onRoomParticipantDisconnected(onRoomParticipantDisconnectedCallback);
    }
  }
}

/**
 * 自定义业务监听器包装类
 */
export class CustomBusinessListenerWrapper implements NativeCustomBusinessListener {
  private listener: CustomBusinessListener | null = null;

  constructor(listener: CustomBusinessListener | null) {
    this.listener = listener;
  }

  onRecvCustomBusinessMessage(businessMessage: string): void {
    info('CustomBusinessListener', `onRecvCustomBusinessMessage: ${businessMessage}`);
    if (this.listener != null) {
      this.listener.onRecvCustomBusinessMessage(businessMessage);
    }
  }
}

/**
 * 消息KV信息监听器包装类
 */
export class MsgKvInfoListenerWrapper implements NativeMsgKvInfoListener {
  private listener: MsgKvInfoListener | null = null;

  constructor(listener: MsgKvInfoListener | null) {
    this.listener = listener;
  }

  onMessageKvInfoChanged(messageChangedList: string): void {
    info('MsgKvInfoListener', `onMessageKvInfoChanged: ${messageChangedList}`);
    if (this.listener != null) {
      this.listener.onMessageKvInfoChanged(toObject(messageChangedList)!!);
    }
  }
}

/**
 * 基础回调包装类
 * 支持callback模式和Promise模式
 */
export class BaseCallbackWrapper<T> implements NativeBaseCallback {
  private callback: BaseCallback<T> | null = null;
  private decoder: (data: string) => T;

  constructor(callback: BaseCallback<T> | null, decoder: (data: string) => T) {
    if (callback) {
      this.callback = callback;
    }
    this.decoder = decoder;
  }

  onError(errCode: number, errMsg: string): void {
    if (this.callback != null) {
      this.callback.onError(errCode, errMsg);
    }
  }

  onSuccess(data: string): void {
    if (this.callback != null) {
      try {
        this.callback.onSuccess(this.decoder(data));
      } catch (error) {
        this.callback.onError(-1, `OpenIM 返回数据解析失败: ${error}`);
      }
    }
  }
}

/** 原生成功回调不含业务数据时使用，忽略其空字符串响应。 */
export class CompletionCallbackWrapper implements NativeBaseCallback {
  private callback: CompletionCallback | null = null;

  constructor(callback: CompletionCallback | null) {
    this.callback = callback;
  }

  onError(errCode: number, errMsg: string): void {
    if (this.callback != null) this.callback.onError(errCode, errMsg);
  }

  onSuccess(_data: string): void {
    if (this.callback != null) this.callback.onSuccess();
  }
}

/** 以下解码器是 Manager 层唯一允许的原生 JSON 结果入口。 */
export function decodeObject<T>(data: string): T {
  const value = toObject<T>(data);
  if (value == null) throw new Error('期望 JSON 对象');
  return value;
}

export function decodeArray<T>(data: string): T[] {
  const value = JSON.parse(data);
  if (!Array.isArray(value)) throw new Error('期望 JSON 数组');
  return value as T[];
}

export function decodeNumber(data: string): number {
  const value = JSON.parse(data);
  if (typeof value !== 'number') throw new Error('期望数字');
  return value;
}

export function decodeBoolean(data: string): boolean {
  const value = JSON.parse(data);
  if (typeof value !== 'boolean') throw new Error('期望布尔值');
  return value;
}

export function decodeString(data: string): string {
  try {
    const value = JSON.parse(data);
    if (typeof value === 'string') return value;
  } catch (_) {}
  return data;
}

/**
 * 上传文件回调包装类
 */
export class UploadFileCallbackWrapper implements NativeUploadFileCallback {
  private callback: UploadFileCallback | null = null;

  constructor(callback: UploadFileCallback | null) {
    this.callback = callback;
  }

  setCallback(callback: UploadFileCallback | null): void {
    this.callback = callback;
  }

  open(size: number): void {
    if (this.callback != null) {
      this.callback.open(size);
    }
  }

  partSize(partSize: number, num: number): void {
    if (this.callback != null) {
      this.callback.partSize(partSize, num);
    }
  }

  hashPartProgress(index: number, size: number, partHash: string): void {
    if (this.callback != null) {
      this.callback.hashPartProgress(index, size, partHash);
    }
  }

  hashPartComplete(partsHash: string, fileHash: string): void {
    if (this.callback != null) {
      this.callback.hashPartComplete(partsHash, fileHash);
    }
  }

  uploadID(uploadID: string): void {
    if (this.callback != null) {
      this.callback.uploadID(uploadID);
    }
  }

  uploadPartComplete(index: number, partSize: number, partHash: string): void {
    if (this.callback != null) {
      this.callback.uploadPartComplete(index, partSize, partHash);
    }
  }

  uploadComplete(fileSize: number, streamSize: number, storageSize: number): void {
    if (this.callback != null) {
      this.callback.uploadComplete(fileSize, streamSize, storageSize);
    }
  }

  complete(size: number, url: string, typ: number): void {
    if (this.callback != null) {
      this.callback.complete(size, url, typ);
    }
  }
}

/**
 * 上传日志进度包装类
 */
export class UploadLogProgressWrapper implements NativeUploadLogProgress {
  private callback: UploadLogProgress | null = null;

  constructor(callback: UploadLogProgress | null) {
    this.callback = callback;
  }

  setCallback(callback: UploadLogProgress | null): void {
    this.callback = callback;
  }

  onProgress(current: number, size: number): void {
    if (this.callback != null) {
      this.callback.onProgress(current, size);
    }
  }
}

/**
 * 发送消息回调包装类
 */
export class SendMsgCallBackWrapper implements NativeSendMsgCallBack {
  private callback: SendMsgCallBack<Message> | null = null;

  constructor(callback: SendMsgCallBack<Message> | null) {
    this.callback = callback;
  }

  onError(errCode: number, errMsg: string): void {
    if (this.callback != null) {
      this.callback.onError(errCode, errMsg);
    }
  }

  onSuccess(data: string): void {
    if (this.callback != null) {
      try {
        this.callback.onSuccess(decodeObject<Message>(data));
      } catch (error) {
        this.callback.onError(-1, `OpenIM 消息解析失败: ${error}`);
      }
    }
  }

  onProgress(progress: number): void {
    if (this.callback != null) {
      this.callback.onProgress(progress);
    }
  }
}
