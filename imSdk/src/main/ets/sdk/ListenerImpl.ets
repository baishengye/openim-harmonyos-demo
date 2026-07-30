/**
 * OpenIM SDK for HarmonyOS
 * 监听器实现类 - 封装用户监听器并代理到原生层
 */

import { ConnListener, MsgListener, ConvListener, GroupListener, FriendListener, UserListener, SignalingListener } from './listener';
import { info, debug } from './Logger';

/**
 * 连接状态监听器包装类
 */
export class ConnListenerWrapper implements ConnListener {
  private listener: ConnListener | null = null;

  constructor(listener: ConnListener | null) {
    this.listener = listener;
  }

  setListener(listener: ConnListener | null): void {
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
export class MsgListenerWrapper implements MsgListener {
  private listener: MsgListener | null = null;

  constructor(listener: MsgListener | null) {
    this.listener = listener;
  }

  setListener(listener: MsgListener | null): void {
    this.listener = listener;
  }

  onRecvNewMessage(message: string): void {
    debug('MsgListener', `onRecvNewMessage: ${message}`);
    if (this.listener != null) {
      this.listener.onRecvNewMessage(message);
    }
  }

  onRecvC2CReadReceipt(msgReceiptList: string): void {
    debug('MsgListener', `onRecvC2CReadReceipt: ${msgReceiptList}`);
    if (this.listener != null) {
      this.listener.onRecvC2CReadReceipt(msgReceiptList);
    }
  }

  onNewRecvMessageRevoked(messageRevoked: string): void {
    debug('MsgListener', `onNewRecvMessageRevoked: ${messageRevoked}`);
    if (this.listener != null) {
      this.listener.onNewRecvMessageRevoked(messageRevoked);
    }
  }

  onRecvOfflineNewMessage(message: string): void {
    debug('MsgListener', `onRecvOfflineNewMessage: ${message}`);
    if (this.listener != null) {
      this.listener.onRecvOfflineNewMessage(message);
    }
  }

  onMsgDeleted(message: string): void {
    debug('MsgListener', `onMsgDeleted: ${message}`);
    if (this.listener != null) {
      this.listener.onMsgDeleted(message);
    }
  }

  onRecvOnlineOnlyMessage(message: string): void {
    debug('MsgListener', `onRecvOnlineOnlyMessage: ${message}`);
    if (this.listener != null) {
      this.listener.onRecvOnlineOnlyMessage(message);
    }
  }
}

/**
 * 会话监听器包装类
 */
export class ConvListenerWrapper implements ConvListener {
  private listener: ConvListener | null = null;

  constructor(listener: ConvListener | null) {
    this.listener = listener;
  }

  setListener(listener: ConvListener | null): void {
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
      this.listener.onNewConversation(conversationList);
    }
  }

  onConversationChanged(conversationList: string): void {
    debug('ConvListener', `onConversationChanged: ${conversationList}`);
    if (this.listener != null) {
      this.listener.onConversationChanged(conversationList);
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
export class GroupListenerWrapper implements GroupListener {
  private listener: GroupListener | null = null;

  constructor(listener: GroupListener | null) {
    this.listener = listener;
  }

  setListener(listener: GroupListener | null): void {
    this.listener = listener;
  }

  onJoinedGroupAdded(groupInfo: string): void {
    info('GroupListener', `onJoinedGroupAdded: ${groupInfo}`);
    if (this.listener != null) {
      this.listener.onJoinedGroupAdded(groupInfo);
    }
  }

  onJoinedGroupDeleted(groupInfo: string): void {
    info('GroupListener', `onJoinedGroupDeleted: ${groupInfo}`);
    if (this.listener != null) {
      this.listener.onJoinedGroupDeleted(groupInfo);
    }
  }

  onGroupMemberAdded(groupMemberInfo: string): void {
    info('GroupListener', `onGroupMemberAdded: ${groupMemberInfo}`);
    if (this.listener != null) {
      this.listener.onGroupMemberAdded(groupMemberInfo);
    }
  }

  onGroupMemberDeleted(groupMemberInfo: string): void {
    info('GroupListener', `onGroupMemberDeleted: ${groupMemberInfo}`);
    if (this.listener != null) {
      this.listener.onGroupMemberDeleted(groupMemberInfo);
    }
  }

  onGroupApplicationAdded(groupApplication: string): void {
    info('GroupListener', `onGroupApplicationAdded: ${groupApplication}`);
    if (this.listener != null) {
      this.listener.onGroupApplicationAdded(groupApplication);
    }
  }

  onGroupApplicationDeleted(groupApplication: string): void {
    info('GroupListener', `onGroupApplicationDeleted: ${groupApplication}`);
    if (this.listener != null) {
      this.listener.onGroupApplicationDeleted(groupApplication);
    }
  }

  onGroupInfoChanged(groupInfo: string): void {
    info('GroupListener', `onGroupInfoChanged: ${groupInfo}`);
    if (this.listener != null) {
      this.listener.onGroupInfoChanged(groupInfo);
    }
  }

  onGroupDismissed(groupInfo: string): void {
    info('GroupListener', `onGroupDismissed: ${groupInfo}`);
    if (this.listener != null) {
      this.listener.onGroupDismissed(groupInfo);
    }
  }

  onGroupMemberInfoChanged(groupMemberInfo: string): void {
    info('GroupListener', `onGroupMemberInfoChanged: ${groupMemberInfo}`);
    if (this.listener != null) {
      this.listener.onGroupMemberInfoChanged(groupMemberInfo);
    }
  }

  onGroupApplicationAccepted(groupApplication: string): void {
    info('GroupListener', `onGroupApplicationAccepted: ${groupApplication}`);
    if (this.listener != null) {
      this.listener.onGroupApplicationAccepted(groupApplication);
    }
  }

  onGroupApplicationRejected(groupApplication: string): void {
    info('GroupListener', `onGroupApplicationRejected: ${groupApplication}`);
    if (this.listener != null) {
      this.listener.onGroupApplicationRejected(groupApplication);
    }
  }
}

/**
 * 好友监听器包装类
 */
export class FriendListenerWrapper implements FriendListener {
  private listener: FriendListener | null = null;

  constructor(listener: FriendListener | null) {
    this.listener = listener;
  }

  setListener(listener: FriendListener | null): void {
    this.listener = listener;
  }

  onFriendApplicationAdded(friendApplication: string): void {
    info('FriendListener', `onFriendApplicationAdded: ${friendApplication}`);
    if (this.listener != null) {
      this.listener.onFriendApplicationAdded(friendApplication);
    }
  }

  onFriendApplicationDeleted(friendApplication: string): void {
    info('FriendListener', `onFriendApplicationDeleted: ${friendApplication}`);
    if (this.listener != null) {
      this.listener.onFriendApplicationDeleted(friendApplication);
    }
  }

  onFriendApplicationAccepted(friendApplication: string): void {
    info('FriendListener', `onFriendApplicationAccepted: ${friendApplication}`);
    if (this.listener != null) {
      this.listener.onFriendApplicationAccepted(friendApplication);
    }
  }

  onFriendApplicationRejected(friendApplication: string): void {
    info('FriendListener', `onFriendApplicationRejected: ${friendApplication}`);
    if (this.listener != null) {
      this.listener.onFriendApplicationRejected(friendApplication);
    }
  }

  onFriendAdded(friendInfo: string): void {
    info('FriendListener', `onFriendAdded: ${friendInfo}`);
    if (this.listener != null) {
      this.listener.onFriendAdded(friendInfo);
    }
  }

  onFriendDeleted(friendInfo: string): void {
    info('FriendListener', `onFriendDeleted: ${friendInfo}`);
    if (this.listener != null) {
      this.listener.onFriendDeleted(friendInfo);
    }
  }

  onFriendInfoChanged(friendInfo: string): void {
    info('FriendListener', `onFriendInfoChanged: ${friendInfo}`);
    if (this.listener != null) {
      this.listener.onFriendInfoChanged(friendInfo);
    }
  }

  onBlackAdded(blackInfo: string): void {
    info('FriendListener', `onBlackAdded: ${blackInfo}`);
    if (this.listener != null) {
      this.listener.onBlackAdded(blackInfo);
    }
  }

  onBlackDeleted(blackInfo: string): void {
    info('FriendListener', `onBlackDeleted: ${blackInfo}`);
    if (this.listener != null) {
      this.listener.onBlackDeleted(blackInfo);
    }
  }
}

/**
 * 用户监听器包装类
 */
export class UserListenerWrapper implements UserListener {
  private listener: UserListener | null = null;

  constructor(listener: UserListener | null) {
    this.listener = listener;
  }

  setListener(listener: UserListener | null): void {
    this.listener = listener;
  }

  onSelfInfoUpdated(userInfo: string): void {
    info('UserListener', `onSelfInfoUpdated: ${userInfo}`);
    if (this.listener != null) {
      this.listener.onSelfInfoUpdated(userInfo);
    }
  }

  onUserStatusChanged(userOnlineStatus: string): void {
    info('UserListener', `onUserStatusChanged: ${userOnlineStatus}`);
    if (this.listener != null) {
      this.listener.onUserStatusChanged(userOnlineStatus);
    }
  }
}

/**
 * 信令监听器包装类
 */
export class SignalingListenerWrapper implements SignalingListener {
  private listener: SignalingListener | null = null;

  constructor(listener: SignalingListener | null) {
    this.listener = listener;
  }

  setListener(listener: SignalingListener | null): void {
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
