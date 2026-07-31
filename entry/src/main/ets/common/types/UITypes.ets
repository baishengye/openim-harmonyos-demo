/**
 * OpenIM HarmonyOS Demo
 * UI层数据类型定义 - 用于界面展示
 *
 * 注意：这些类型用于UI展示层，从SDK类型转换而来
 * SDK级别的数据类定义在 imSdk 模块中
 */

/**
 * 会话列表项（用于UI展示）
 */
export class ConversationItem {
  /** 会话ID */
  conversationID: string = "";
  /** 会话类型 */
  conversationType: number = 0;
  /** 用户ID */
  userID: string = "";
  /** 群ID */
  groupID: string = "";
  /** 显示名称 */
  showName: string = "";
  /** 头像URL */
  faceUrl: string = "";
  /** 最新消息 */
  latestMsg: string = "";
  /** 最新消息发送时间 */
  latestMsgSendTime: number = 0;
  /** 未读消息数 */
  unreadCount: number = 0;
  /** 是否置顶 */
  isPinned: boolean = false;
  /** 是否免打扰 */
  isMute: boolean = false;
  /** 草稿文本 */
  draftText: string = "";
  /** 是否正在输入 */
  isTyping: boolean = false;
}

/**
 * 消息列表项（用于UI展示）
 */
export class MessageItem {
  /** 消息ID */
  clientMsgID: string = "";
  /** 发送者ID */
  sendID: string = "";
  /** 发送者昵称 */
  senderNickname: string = "";
  /** 发送者头像 */
  senderFaceUrl: string = "";
  /** 会话ID */
  conversationID: string = "";
  /** 会话类型 */
  sessionType: number = 0;
  /** 群ID */
  groupID: string = "";
  /** 消息类型 */
  contentType: number = 0;
  /** 消息发送时间 */
  sendTime: number = 0;
  /** 消息状态 */
  status: number = 0;
  /** 是否自己发送的消息 */
  isSelf: boolean = false;
  /** 消息内容 */
  content: string = "";
  /** 消息气泡位置 */
  bubblePosition: string = "";
  /** 引用消息内容 */
  quoteContent: string = "";
  /** 媒体URL（如图片、视频、语音） */
  mediaUrl: string = "";
  /** 媒体时长（语音、视频） */
  mediaDuration: number = 0;
  /** 媒体大小 */
  mediaSize: number = 0;
  /** 是否显示时间戳 */
  showTimestamp: boolean = false;

  isRead:boolean = false;
}

/**
 * 好友用户项（用于UI展示）
 */
export class FriendUserItem {
  /** 用户ID */
  userID: string = "";
  /** 昵称 */
  nickname: string = "";
  /** 头像URL */
  faceUrl: string = "";
  /** 备注名 */
  remark: string = "";
  /** 显示名称（优先显示备注名） */
  showName: string = "";
}

/**
 * 好友申请项（用于UI展示）
 */
export class FriendApplicationItem {
  /** 用户ID */
  userID: string = "";
  /** 昵称 */
  nickname: string = "";
  /** 头像URL */
  faceUrl: string = "";
  /** 申请原因 */
  reqMsg: string = "";
  /** 处理状态 */
  handleStatus: number = 0;
  /** 申请时间 */
  createTime: number = 0;
  /** 是否是自己的申请 */
  isMyRequest: boolean = false;
}

/**
 * 用户信息项（用于UI展示）
 */
export class UserItem {
  /** 用户ID */
  userID: string = "";
  /** 昵称 */
  nickname: string = "";
  /** 头像URL */
  faceUrl: string = "";
  /** 显示名称 */
  showName: string = "";
  /** 在线状态 */
  isOnline: boolean = false;
}

/**
 * 群组项（用于UI展示）
 */
export class GroupItem {
  /** 群ID */
  groupID: string = "";
  /** 群名称 */
  groupName: string = "";
  /** 群头像 */
  faceUrl: string = "";
  /** 成员数量 */
  memberCount: number = 0;
  /** 群状态 */
  status: number = 0;
  /** 是否管理员 */
  isAdmin: boolean = false;
}

/**
 * 群组成员项（用于UI展示）
 */
export class GroupMemberItem {
  /** 用户ID */
  userID: string = "";
  /** 昵称 */
  nickname: string = "";
  /** 群内昵称 */
  groupNickname: string = "";
  /** 头像URL */
  faceUrl: string = "";
  /** 角色：100-群主，60-管理员，20-普通成员 */
  roleLevel: number = 0;
  /** 是否是群主 */
  isOwner: boolean = false;
  /** 是否是管理员 */
  isAdmin: boolean = false;
  /** 入群时间 */
  joinTime: number = 0;
}

/**
 * 群申请项（用于UI展示）
 */
export class GroupApplicationItem {
  /** 群ID */
  groupID: string = "";
  /** 群名称 */
  groupName: string = "";
  /** 申请人ID */
  userID: string = "";
  /** 申请人昵称 */
  nickname: string = "";
  /** 申请人头像 */
  faceUrl: string = "";
  /** 申请原因 */
  reqMsg: string = "";
  /** 处理状态 */
  handleStatus: number = 0;
  /** 申请时间 */
  createTime: number = 0;
}

/**
 * 获取消息结果（用于聊天界面）
 */
export class AdvancedGetMessageResult {
  /** 消息列表 */
  messageList: string = "";
  /** 消息数量 */
  count: number = 0;
  /** 是否还有更多消息 */
  isEnd: boolean = false;
}

/**
 * 消息选项
 */
export class MessageOptions {
  /** 是否发送Push */
  sendPushMsg: boolean = true;
  /** 是否支持多端已读 */
  supportMessageReceipt: boolean = true;
  /** 是否离线发送 */
  offlinePush: boolean = true;
  /** 扩展数据 */
  ex: string = "";
}
