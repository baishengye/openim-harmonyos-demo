/**
 * OpenIM SDK for HarmonyOS
 * 枚举定义 - 参考 Android SDK 实现
 */

/**
 * 好友类型
 */
export enum AllowType {
  /** 允许 */
  Allowed = 1,
  /** 不允许 */
  NotAllowed = 2
}

/**
 * 申请处理结果
 */
export enum ApplyHandleResult {
  /** 未处理 */
  Unprocessed = -1,
  /** 同意 */
  Agree = 0,
  /** 拒绝 */
  Reject = 1
}

/**
 * 会话类型
 */
export enum ConversationType {
  /** 单聊 */
  SINGLE_CHAT = 1,
  /** 群聊 */
  GROUP_CHAT = 2,
  /** 超级群聊 */
  SUPER_GROUP_CHAT = 3,
  /** 通知 */
  NOTIFICATION = 4
}

/**
 * 会话强提醒
 */
export enum GroupAtType {
  /** 清除所有 */
  AT_NORMAL = 0,
  /** at我 */
  AT_ME = 1,
  /** at所有人 */
  AT_ALL = 2,
  /** at所有人，at我 */
  AT_ALL_AT_ME = 3,
  /** 群公告提示 */
  GROUP_NOTIFICATION = 4
}

/**
 * 群成员过滤类型
 */
export enum GroupMemberFilter {
  /** 全部 */
  All = 0,
  /** 群主 */
  Owner = 1,
  /** 管理员 */
  Admin = 2,
  /** 普通成员 */
  Nomal = 3,
  /** 管理员和普通成员 */
  AdminAndNomal = 4,
  /** 管理员和群主 */
  AdminAndOwner = 5
}

/**
 * 组成员角色
 */
export enum GroupRole {
  /** 群主 */
  OWNER = 100,
  /** 群管理员 */
  ADMIN = 60,
  /** 群成员 */
  MEMBER = 20
}

/**
 * 群状态
 */
export enum GroupStatus {
  /** 正常 */
  GROUP_OK = 0,
  /** 被封 */
  GROUP_BANNED = 1,
  /** 解散 */
  GROUP_DISSOLVE = 2,
  /** 禁言 */
  GROUP_MUTED = 3
}

/**
 * 群类型
 */
export enum GroupType {
  /** 普通群 */
  GENERAL = 0,
  /** 工作群 */
  WORK = 2
}

/**
 * 进群验证方式
 */
export enum GroupVerification {
  /** 申请需要同意，邀请直接进 */
  APPLY_NEED_VERIFICATION_INVITE_DIRECTLY = 0,
  /** 所有人进群需要验证 */
  ALL_NEED_VERIFICATION = 1,
  /** 直接进群 */
  DIRECTLY = 2
}

/**
 * 入群来源
 */
export enum JoinSource {
  /** 邀请 */
  Invitation = 2,
  /** 搜索 */
  Search = 3,
  /** 扫码 */
  QrCode = 4
}

/**
 * 日志级别
 */
export enum LogLevel {
  /** 致命 */
  Fatal = 0,
  /** 恐慌 */
  Panic = 1,
  /** 错误 */
  Error = 2,
  /** 警告 */
  Warn = 3,
  /** 信息 */
  Info = 4,
  /** 调试 */
  Debug = 5,
  /** 带SQL的调试 */
  DebugWithSQL = 6
}

/**
 * 登录状态
 */
export enum LoginStatus {
  /** 未登录 */
  Logout = 1,
  /** 登录中 */
  Logging = 2,
  /** 已登录 */
  Logged = 3
}

/**
 * 消息发送状态
 */
export enum MessageStatus {
  /** 发送中 */
  SENDING = 1,
  /** 发送成功 */
  SUCCEEDED = 2,
  /** 发送失败 */
  FAILED = 3,
  /** 已删除 */
  DELETED = 4
}

/**
 * 消息类型
 */
export enum MessageType {
  /** 文本 */
  TEXT = 101,
  /** 图片 */
  PICTURE = 102,
  /** 语音 */
  VOICE = 103,
  /** 视频 */
  VIDEO = 104,
  /** 文件 */
  FILE = 105,
  /** @消息 */
  AT_TEXT = 106,
  /** 合并 */
  MERGER = 107,
  /** 名片 */
  CARD = 108,
  /** 位置 */
  LOCATION = 109,
  /** 自定义类型 */
  CUSTOM = 110,
  /** 已读回执 */
  HAS_READ_RECEIPT = 112,
  /** 正在输入 */
  TYPING = 113,
  /** 引用 */
  QUOTE = 114,
  /** 自定义表情包 */
  CUSTOM_FACE = 115,
  /** 群消息已读回执 */
  GROUP_HAS_READ_RECEIPT = 116,
  /** 富文本消息 */
  ADVANCED_TEXT = 117,
  /** 不触发会话的自定义消息 */
  CUSTOM_MSG_NOT_TRIGGER_CONVERSATION = 119,
  /** 仅在线自定义消息 */
  CUSTOM_MSG_ONLINE_ONLY = 120,

  // ========== 通知消息开始 ==========
  /** 通知消息开始 */
  NTF_BEGIN = 1000,

  // 好友通知
  /** 好友通知开始 */
  FRIEND_NTF_BEGIN = 1200,
  /** 好友申请被同意通知 */
  FRIEND_APPLICATION_APPROVED_NTF = 1201,
  /** 好友申请被拒绝通知 */
  FRIEND_APPLICATION_REJECTED_NTF = 1202,
  /** 好友申请通知 */
  FRIEND_APPLICATION_NTF = 1203,
  /** 好友添加通知 */
  FRIEND_ADDED_NTF = 1204,
  /** 好友删除通知 */
  FRIEND_DELETED_NTF = 1205,
  /** 好友备注设置通知 */
  FRIEND_REMARK_SET_NTF = 1206,
  /** 黑名单添加通知 */
  BLACK_ADDED_NTF = 1207,
  /** 黑名单删除通知 */
  BLACK_DELETED_NTF = 1208,
  /** 好友通知结束 */
  FRIEND_NTF_END = 1299,

  /** 会话变更通知 */
  CONVERSATION_CHANGE_NTF = 1300,

  // 用户通知
  /** 用户通知开始 */
  USER_NTF_BEGIN = 1301,
  /** 用户信息更新通知 */
  USERINFO_UPDATED_NTF = 1303,
  /** 用户通知结束 */
  USER_NTF_END = 1399,

  /** OA通知 */
  OA_NTF = 1400,

  // 群组通知
  /** 群组通知开始 */
  GROUP_NTF_BEGIN = 1500,
  /** 群创建通知 */
  GROUP_CREATED_NTF = 1501,
  /** 群信息设置通知 */
  GROUP_INFO_SET_NTF = 1502,
  /** 入群申请通知 */
  JOIN_GROUP_APPLICATION_NTF = 1503,
  /** 成员退出通知 */
  MEMBER_QUIT_NTF = 1504,
  /** 入群申请被接受通知 */
  GROUP_APPLICATION_ACCEPTED_NTF = 1505,
  /** 入群申请被拒绝通知 */
  GROUP_APPLICATION_REJECTED_NTF = 1506,
  /** 群主转让通知 */
  GROUP_OWNER_TRANSFERRED_NTF = 1507,
  /** 成员被踢通知 */
  MEMBER_KICKED_NTF = 1508,
  /** 成员被邀请通知 */
  MEMBER_INVITED_NTF = 1509,
  /** 成员进入通知 */
  MEMBER_ENTER_NTF = 1510,
  /** 群解散通知 */
  GROUP_DISBAND_NTF = 1511,
  /** 群成员禁言通知 */
  GROUP_MEMBER_MUTED_NTF = 1512,
  /** 群成员取消禁言通知 */
  GROUP_MEMBER_CANCEL_MUTED_NTF = 1513,
  /** 群全员禁言通知 */
  GROUP_MUTED_NTF = 1514,
  /** 群取消全员禁言通知 */
  GROUP_CANCEL_MUTED_NTF = 1515,
  /** 群成员信息变更通知 */
  GROUP_MEMBER_INFO_CHANGED_NTF = 1516,
  /** 群公告通知 */
  GROUP_ANNOUNCEMENT_NTF = 1519,
  /** 群名变更通知 */
  GROUP_NAME_CHANGED_NTF = 1520,
  /** 群组通知结束 */
  GROUP_NTF_END = 1599,

  // 信令通知
  /** 信令通知开始 */
  SIGNALING_NTF_BEGIN = 1600,
  /** 信令通知 */
  SIGNALING_NTF = 1601,
  /** 信令通知结束 */
  SIGNALING_NTF_END = 1699,

  /** 阅后即焚通知 */
  BURN_AFTER_READING_NTF = 1701,

  /** 通知消息结束 */
  NTF_END = 2000,

  /** 3.0版本消息撤回类型 */
  REVOKE_MESSAGE_NTF = 2101
}

/**
 * 接收消息选项
 */
export enum Opt {
  /** 默认值，正常接收 */
  NORMAL = 0,
  /** 不接受消息 */
  NotReceiveMessage = 1,
  /** 接受但不通知 */
  ReceiveNotNotifyMessage = 2
}

/**
 * 平台类型
 */
export enum Platform {
  /** iOS */
  IOS = 1,
  /** Android */
  ANDROID = 2,
  /** Windows */
  WIN = 3,
  /** macOS */
  XOS = 4,
  /** Web */
  WEB = 5,
  /** 小程序 */
  MINI_WEB = 6,
  /** Linux */
  LINUX = 7,
  /** Android平板 */
  ANDROID_PAD = 8,
  /** iPad */
  IPAD = 9
}

/**
 * 关系类型
 */
export enum Relationship {
  /** 黑名单 */
  Black = 0,
  /** 好友 */
  Friend = 1
}

/**
 * 视图类型
 */
export enum ViewType {
  /** 历史 */
  History = 0,
  /** 搜索 */
  Search = 1
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
