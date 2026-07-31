/**
 * OpenIM SDK for HarmonyOS
 * SDK主入口 - 提供SDK初始化、登录、管理器等功能
 */

import im from 'libimsdk.so';
import { buildOperationID } from './utils/Utils';
import { info, debug, error } from './internal/log/Logger';
import { toString } from './utils/JsonUtil';
import { InitConfig } from './models/entity';
import { LoginStatus } from './enums/enum';
import { ConnListenerWrapper, ConvListenerWrapper,
  FriendListenerWrapper,
  GroupListenerWrapper,
  MsgListenerWrapper,
  UserListenerWrapper} from './listeners/ListenerImpl';
import { MessageManager } from './manager/MessageManager';
import { ConversationManager } from './manager/ConversationManager';
import { FriendshipManager } from './manager/FriendshipManager';
import { GroupManager } from './manager/GroupManager';
import { UserInfoManager } from './manager/UserInfoManager';
import { ConnListener, ConvListener, FriendListener, GroupListener, MsgListener,
  UserListener } from './listeners/listener';
import { MiscManager } from './manager/MiscManager';
import { LoginManager } from './manager/LoginManager';

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
  /** 登陆管理器*/
  public loginManager:LoginManager = new LoginManager();
  /**
   * 工具管理
   */
  public miscManager:MiscManager = new MiscManager();

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
