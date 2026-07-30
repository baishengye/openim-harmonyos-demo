/**
 * OpenIM SDK for HarmonyOS
 * SDK主入口 - 提供SDK初始化、登录、管理器等功能
 */

import im from 'libimsdk.so';
import { buildOperationID } from './utils/Utils';
import { info, debug, error } from './internal/log/Logger';
import { toString } from './utils/JsonUtil';
import { InitConfig } from './models/entity';
import { MessageManager } from './MessageManager';
import { ConversationManager } from './ConversationManager';
import { FriendshipManager } from './FriendshipManager';
import { GroupManager } from './GroupManager';
import { UserInfoManager } from './UserInfoManager';
import { LoginStatus } from './enums/enum';

/**
 * 连接状态监听器
 */
export interface OnConnListener {
  onConnecting?: () => void;
  onConnectSuccess?: () => void;
  onConnectFailed?: (errCode: number, errMsg: string) => void;
  onKickedOffline?: () => void;
  onUserTokenExpired?: () => void;
  onUserTokenInvalid?: (errMsg: string) => void;
}

/**
 * 消息监听器
 */
export interface OnMsgListener {
  onRecvNewMessage?: (msg: string) => void;
  onRecvC2CReadReceipt?: (msgReceiptList: string) => void;
  onMsgRevoked?: (msgRevoked: string) => void;
  onRecvOfflineNewMessage?: (msg: string) => void;
  onMsgDeleted?: (msg: string) => void;
  onRecvOnlineOnlyMessage?: (msg: string) => void;
}

/**
 * 会话监听器
 */
export interface OnConvListener {
  onSyncServerStart?: (reinstalled: boolean) => void;
  onSyncServerFinish?: (reinstalled: boolean) => void;
  onSyncServerProgress?: (progress: number) => void;
  onSyncServerFailed?: (reinstalled: boolean) => void;
  onNewConversation?: (convList: string) => void;
  onConversationChanged?: (convList: string) => void;
  onTotalUnreadChanged?: (count: number) => void;
  onInputStatusChanged?: (change: string) => void;
}

/**
 * 群组监听器
 */
export interface OnGroupListener {
  onJoinedGroupAdded?: (groupInfo: string) => void;
  onJoinedGroupDeleted?: (groupInfo: string) => void;
  onGroupMemberAdded?: (memberInfo: string) => void;
  onGroupMemberDeleted?: (memberInfo: string) => void;
  onGroupApplicationAdded?: (application: string) => void;
  onGroupApplicationDeleted?: (application: string) => void;
  onGroupInfoChanged?: (groupInfo: string) => void;
  onGroupDismissed?: (groupInfo: string) => void;
  onGroupMemberInfoChanged?: (memberInfo: string) => void;
  onGroupApplicationAccepted?: (application: string) => void;
  onGroupApplicationRejected?: (application: string) => void;
}

/**
 * 好友监听器
 */
export interface OnFriendListener {
  onFriendApplicationAdded?: (application: string) => void;
  onFriendApplicationDeleted?: (application: string) => void;
  onFriendApplicationAccepted?: (application: string) => void;
  onFriendApplicationRejected?: (application: string) => void;
  onFriendAdded?: (friendInfo: string) => void;
  onFriendDeleted?: (friendInfo: string) => void;
  onFriendInfoChanged?: (friendInfo: string) => void;
  onBlackAdded?: (blackInfo: string) => void;
  onBlackDeleted?: (blackInfo: string) => void;
}

/**
 * 用户监听器
 */
export interface OnUserListener {
  onSelfInfoUpdated?: (userInfo: string) => void;
  onUserStatusChanged?: (status: string) => void;
}

/**
 * SDK事件监听器
 */
export interface SDKListener {
  onConnListener?: OnConnListener;
  onMsgListener?: OnMsgListener;
  onConvListener?: OnConvListener;
  onGroupListener?: OnGroupListener;
  onFriendListener?: OnFriendListener;
  onUserListener?: OnUserListener;
}

/**
 * OpenIM客户端SDK
 * 单例模式，提供SDK的所有功能
 */
export class OpenIM {
  private static instance: OpenIM;

  /** 消息管理器 */
  public messageManager: MessageManager = new MessageManager();
  /** 会话管理器 */
  public conversationManager: ConversationManager = new ConversationManager();
  /** 好友管理器 */
  public friendshipManager: FriendshipManager = new FriendshipManager();
  /** 群组管理器 */
  public groupManager: GroupManager = new GroupManager();
  /** 用户信息管理器 */
  public userInfoManager: UserInfoManager = new UserInfoManager();

  private sdkListener: SDKListener = {};
  private initialized: boolean = false;

  private constructor() {}

  /**
   * 获取OpenIM单例实例
   */
  static getInstance(): OpenIM {
    if (!OpenIM.instance) {
      OpenIM.instance = new OpenIM();
    }
    return OpenIM.instance;
  }

  /**
   * 设置SDK事件监听器（统一入口）
   * @param listener SDK事件监听器
   */
  setListener(listener: SDKListener): void {
    this.sdkListener = listener;

    // 设置连接监听器（通过initSdk传入）
    // 设置消息监听器
    if (listener.onMsgListener) {
      this.setAdvancedMsgListener(listener.onMsgListener);
    }

    // 设置会话监听器
    if (listener.onConvListener) {
      this.setConversationListener(listener.onConvListener);
    }

    // 设置群组监听器
    if (listener.onGroupListener) {
      this.setGroupListener(listener.onGroupListener);
    }

    // 设置好友监听器
    if (listener.onFriendListener) {
      this.setFriendListener(listener.onFriendListener);
    }

    // 设置用户监听器
    if (listener.onUserListener) {
      this.setUserListener(listener.onUserListener);
    }
  }

  /**
   * 设置连接监听器
   * @param listener 连接监听器
   */
  private setConnListener(listener: OnConnListener): void {
    this.sdkListener.onConnListener = listener;
  }

  /**
   * 设置消息监听器
   * @param listener 消息监听器
   */
  setAdvancedMsgListener(listener: OnMsgListener): void {
    this.sdkListener.onMsgListener = listener;

    im.setAdvancedMsgListener({
      onRecvNewMessage: (message: string) => {
        this.sdkListener.onMsgListener?.onRecvNewMessage?.(message);
      },
      onRecvC2CReadReceipt: (msgReceiptList: string) => {
        this.sdkListener.onMsgListener?.onRecvC2CReadReceipt?.(msgReceiptList);
      },
      onNewRecvMessageRevoked: (messageRevoked: string) => {
        this.sdkListener.onMsgListener?.onMsgRevoked?.(messageRevoked);
      },
      onRecvOfflineNewMessage: (message: string) => {
        this.sdkListener.onMsgListener?.onRecvOfflineNewMessage?.(message);
      },
      onMsgDeleted: (message: string) => {
        this.sdkListener.onMsgListener?.onMsgDeleted?.(message);
      },
      onRecvOnlineOnlyMessage: (message: string) => {
        this.sdkListener.onMsgListener?.onRecvOnlineOnlyMessage?.(message);
      }
    });
  }

  /**
   * 设置会话监听器
   * @param listener 会话监听器
   */
  setConversationListener(listener: OnConvListener): void {
    this.sdkListener.onConvListener = listener;

    im.setConversationListener({
      onSyncServerStart: (reinstalled: boolean) => {
        this.sdkListener.onConvListener?.onSyncServerStart?.(reinstalled);
      },
      onSyncServerFinish: (reinstalled: boolean) => {
        this.sdkListener.onConvListener?.onSyncServerFinish?.(reinstalled);
      },
      onSyncServerProgress: (progress: number) => {
        this.sdkListener.onConvListener?.onSyncServerProgress?.(progress);
      },
      onSyncServerFailed: (reinstalled: boolean) => {
        this.sdkListener.onConvListener?.onSyncServerFailed?.(reinstalled);
      },
      onNewConversation: (conversationList: string) => {
        this.sdkListener.onConvListener?.onNewConversation?.(conversationList);
      },
      onConversationChanged: (conversationList: string) => {
        this.sdkListener.onConvListener?.onConversationChanged?.(conversationList);
      },
      onTotalUnreadMessageCountChanged: (totalUnreadCount: number) => {
        this.sdkListener.onConvListener?.onTotalUnreadChanged?.(totalUnreadCount);
      },
      onConversationUserInputStatusChanged: (change: string) => {
        this.sdkListener.onConvListener?.onInputStatusChanged?.(change);
      }
    });
  }

  /**
   * 设置群组监听器
   * @param listener 群组监听器
   */
  setGroupListener(listener: OnGroupListener): void {
    this.sdkListener.onGroupListener = listener;

    im.setGroupListener({
      onJoinedGroupAdded: (groupInfo: string) => {
        this.sdkListener.onGroupListener?.onJoinedGroupAdded?.(groupInfo);
      },
      onJoinedGroupDeleted: (groupInfo: string) => {
        this.sdkListener.onGroupListener?.onJoinedGroupDeleted?.(groupInfo);
      },
      onGroupMemberAdded: (groupMemberInfo: string) => {
        this.sdkListener.onGroupListener?.onGroupMemberAdded?.(groupMemberInfo);
      },
      onGroupMemberDeleted: (groupMemberInfo: string) => {
        this.sdkListener.onGroupListener?.onGroupMemberDeleted?.(groupMemberInfo);
      },
      onGroupApplicationAdded: (groupApplication: string) => {
        this.sdkListener.onGroupListener?.onGroupApplicationAdded?.(groupApplication);
      },
      onGroupApplicationDeleted: (groupApplication: string) => {
        this.sdkListener.onGroupListener?.onGroupApplicationDeleted?.(groupApplication);
      },
      onGroupInfoChanged: (groupInfo: string) => {
        this.sdkListener.onGroupListener?.onGroupInfoChanged?.(groupInfo);
      },
      onGroupDismissed: (groupInfo: string) => {
        this.sdkListener.onGroupListener?.onGroupDismissed?.(groupInfo);
      },
      onGroupMemberInfoChanged: (groupMemberInfo: string) => {
        this.sdkListener.onGroupListener?.onGroupMemberInfoChanged?.(groupMemberInfo);
      },
      onGroupApplicationAccepted: (groupApplication: string) => {
        this.sdkListener.onGroupListener?.onGroupApplicationAccepted?.(groupApplication);
      },
      onGroupApplicationRejected: (groupApplication: string) => {
        this.sdkListener.onGroupListener?.onGroupApplicationRejected?.(groupApplication);
      }
    });
  }

  /**
   * 设置好友监听器
   * @param listener 好友监听器
   */
  setFriendListener(listener: OnFriendListener): void {
    this.sdkListener.onFriendListener = listener;

    im.setFriendListener({
      onFriendApplicationAdded: (friendApplication: string) => {
        this.sdkListener.onFriendListener?.onFriendApplicationAdded?.(friendApplication);
      },
      onFriendApplicationDeleted: (friendApplication: string) => {
        this.sdkListener.onFriendListener?.onFriendApplicationDeleted?.(friendApplication);
      },
      onFriendApplicationAccepted: (friendApplication: string) => {
        this.sdkListener.onFriendListener?.onFriendApplicationAccepted?.(friendApplication);
      },
      onFriendApplicationRejected: (friendApplication: string) => {
        this.sdkListener.onFriendListener?.onFriendApplicationRejected?.(friendApplication);
      },
      onFriendAdded: (friendInfo: string) => {
        this.sdkListener.onFriendListener?.onFriendAdded?.(friendInfo);
      },
      onFriendDeleted: (friendInfo: string) => {
        this.sdkListener.onFriendListener?.onFriendDeleted?.(friendInfo);
      },
      onFriendInfoChanged: (friendInfo: string) => {
        this.sdkListener.onFriendListener?.onFriendInfoChanged?.(friendInfo);
      },
      onBlackAdded: (blackInfo: string) => {
        this.sdkListener.onFriendListener?.onBlackAdded?.(blackInfo);
      },
      onBlackDeleted: (blackInfo: string) => {
        this.sdkListener.onFriendListener?.onBlackDeleted?.(blackInfo);
      }
    });
  }

  /**
   * 设置用户监听器
   * @param listener 用户监听器
   */
  setUserListener(listener: OnUserListener): void {
    this.sdkListener.onUserListener = listener;

    im.setUserListener({
      onSelfInfoUpdated: (userInfo: string) => {
        this.sdkListener.onUserListener?.onSelfInfoUpdated?.(userInfo);
      },
      onUserStatusChanged: (userOnlineStatus: string) => {
        this.sdkListener.onUserListener?.onUserStatusChanged?.(userOnlineStatus);
      }
    });
  }

  /**
   * 初始化SDK
   * @param config 初始化配置
   * @returns 初始化结果，0表示成功
   */
  initSdk(listener: OnConnListener,config: InitConfig): number {
    this.setConnListener(listener)
    const operationID = buildOperationID();
    debug('OpenIM', `initSdk with operationID: ${operationID}`);

    const result = im.initSdk(
      {
        onConnecting: () => {
          this.sdkListener.onConnListener?.onConnecting?.();
        },
        onConnectSuccess: () => {
          this.sdkListener.onConnListener?.onConnectSuccess?.();
        },
        onConnectFailed: (errCode: number, errMsg: string) => {
          this.sdkListener.onConnListener?.onConnectFailed?.(errCode, errMsg);
          error('OpenIM', `initSdk failed: ${errCode} - ${errMsg}`);
        },
        onKickedOffline: () => {
          this.sdkListener.onConnListener?.onKickedOffline?.();
        },
        onUserTokenExpired: () => {
          this.sdkListener.onConnListener?.onUserTokenExpired?.();
        },
        onUserTokenInvalid: (errMsg: string) => {
          this.sdkListener.onConnListener?.onUserTokenInvalid?.(errMsg);
        }
      },
      operationID,
      toString(config)
    );

    this.initialized = true;
    info('OpenIM', `SDK initialized successfully with result: ${result}`);
    return result;
  }

  /**
   * 登录
   * @param userID 用户ID
   * @param token 登录令牌
   */
  login(userID: string, token: string): Promise<void> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('OpenIM', `login with userID: ${userID}, operationID: ${operationID}`);

      im.login(
        {
          onError: (errCode: number, errMsg: string) => {
            error('OpenIM', `login failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('OpenIM', `login success`);
            resolve();
          }
        },
        operationID,
        userID,
        token
      );
    });
  }

  /**
   * 登出
   */
  logout(): Promise<void> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('OpenIM', `logout with operationID: ${operationID}`);

      im.logout(
        {
          onError: (errCode: number, errMsg: string) => {
            error('OpenIM', `logout failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('OpenIM', `logout success`);
            resolve();
          }
        },
        operationID
      );
    });
  }

  /**
   * 获取登录状态
   */
  getLoginStatus(): LoginStatus {
    const operationID = buildOperationID();
    return im.getLoginStatus(operationID) as LoginStatus;
  }

  /**
   * 获取当前登录用户ID
   */
  getLoginUserID(): string {
    return im.getLoginUserID();
  }

  /**
   * 反初始化SDK
   */
  unInitSDK(): void {
    const operationID = buildOperationID();
    debug('OpenIM', `unInitSDK with operationID: ${operationID}`);
    im.unInitSDK(operationID);
    this.initialized = false;
    info('OpenIM', 'SDK uninitialized');
  }

  /**
   * 获取SDK版本
   */
  getSdkVersion(): string {
    return im.getSdkVersion();
  }
}

/**
 * 导出OpenIM单例实例
 */
export const OpenIMClient = OpenIM.getInstance();

/**
 * 获取SDK实例（兼容旧API）
 */
export function getSDK(): OpenIM {
  return OpenIMClient;
}
