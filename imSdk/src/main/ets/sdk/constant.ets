/**
 * OpenIM SDK for HarmonyOS
 * 平台枚举 - 定义支持的平台类型
 */

/**
 * 平台类型枚举
 */
export enum Platform {
  /** iOS平台 */
  iOS = 1,
  /** Android平台 */
  Android = 2,
  /** Windows平台 */
  Windows = 3,
  /** macOS平台 */
  macOS = 4,
  /** Web平台 */
  Web = 5,
  /** 小程序平台 */
  MiniProgram = 6,
  /** Linux平台 */
  Linux = 7
}

/**
 * 会话类型枚举
 */
export enum ConversationType {
  /** 单聊 */
  Single = 1,
  /** 群聊 */
  Group = 2
}

/**
 * 消息类型枚举
 */
export enum MessageType {
  /** 文本消息 */
  TEXT = 101,
  /** 图片消息 */
  PICTURE = 102,
  /** 语音消息 */
  VOICE = 103,
  /** 视频消息 */
  VIDEO = 104,
  /** 文件消息 */
  FILE = 105,
  /** @消息 */
  AT = 106,
  /** 合并消息 */
  MERGER = 107,
  /** 转发消息 */
  FORWARD = 108,
  /** 位置消息 */
  LOCATION = 109,
  /** 自定义消息 */
  CUSTOM = 110,
  /** 撤回消息回执 */
  REVOKE = 111,
  /** C2C已读回执 */
  READ_RECEIPT = 112,
  /** 正在输入状态 */
  TYPING = 113
}

/**
 * 消息状态枚举
 */
export enum MessageStatus {
  /** 发送中 */
  SENDING = 1,
  /** 发送成功 */
  SUCCEED = 2,
  /** 发送失败 */
  FAILED = 3,
  /** 已删除 */
  DELETED = 4,
  /** 已撤回 */
  REVOKED = 5
}

/**
 * 登录状态枚举
 */
export enum LoginStatus {
  /** 未登录 */
  IDLE = 0,
  /** 登录中 */
  LOGINING = 1,
  /** 已登录 */
  SUCCESS = 2,
  /** 被踢出 */
  BE_KICKED = 3
}

/**
 * 群成员过滤类型枚举
 */
export enum GroupMemberFilter {
  /** 不过滤 */
  NONE = 0,
  /** 群主 */
  OWNER = 1,
  /** 群主和管理员 */
  OWNER_AND_ADMIN = 2,
  /** 普通群成员 */
  NORMAL = 3,
  /** 群主、管理员和普通成员 */
  ALL = 4
}

/**
 * 入群来源枚举
 */
export enum JoinSource {
  /** 邀请 */
  INVITE = 0,
  /** 搜索 */
  SEARCH = 1,
  /** 扫码 */
  QR_CODE = 2,
  /** 管理员操作 */
  ADMIN = 3
}

/**
 * 操作类型枚举
 */
export enum OperationType {
  /** 发送消息 */
  SEND_MESSAGE = 0,
  /** 加入群组 */
  JOIN_GROUP = 1,
  /** 创建群组 */
  CREATE_GROUP = 2,
  /** 好友申请 */
  FRIEND_APPLICATION = 3
}
