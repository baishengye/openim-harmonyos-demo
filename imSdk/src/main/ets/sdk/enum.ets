/**
 * OpenIM SDK for HarmonyOS
 * 枚举定义
 */

/**
 * 会话接收消息选项
 */
export enum ConversationRecvMessageOpt {
  /** 正常接收 */
  NORMAL = 0,
  /** 不接收消息 */
  NOT_RECEIVE = 1,
  /** 仅接收在线消息 */
  RECEIVE_ONLY_ONLINE_MESSAGE = 2
}

/**
 * 好友验证方式
 */
export enum FriendAllowType {
  /** 需要验证 */
  NEED_VERIFY = 0,
  /** 直接添加 */
  ALLOW_ANY = 1,
  /** 拒绝添加 */
  DENY_ANY = 2
}

/**
 * 群验证方式
 */
export enum GroupVerificationType {
  /** 需要验证 */
  NEED_VERIFY = 0,
  /** 直接加入 */
  JOIN_ANY = 1,
  /** 禁止加入 */
  JOIN_FORBIDDEN = 2
}

/**
 * 群聊类型
 */
export enum GroupType {
  /** 正常工作群 */
  NORMAL_GROUP = 0,
  /** 超级群 */
  SUPER_GROUP = 1
}

/**
 * 消息范围
 */
export enum MessageRange {
  /** 全局搜索 */
  GLOBAL = 0,
  /** 仅搜索会话内 */
  IN_CONVERSATION = 1
}

/**
 * 排序方式
 */
export enum SortOrder {
  /** 升序 */
  ASCEND = 0,
  /** 降序 */
  DESCEND = 1
}
