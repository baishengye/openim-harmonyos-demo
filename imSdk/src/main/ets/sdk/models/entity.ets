/**
 * OpenIM SDK for HarmonyOS
 * SDK数据模型 - 与Android SDK保持一致
 */
import { ViewType } from "../enums/enum";

/**
 * SDK初始化配置
 */
export class InitConfig {
  /** 平台ID {@link Platform} */
  platformID: number = 0;
  /** API地址，如：http://xxx:10000 */
  apiAddr: string = "";
  /** WebSocket地址，如：ws://xxx:17778 */
  wsAddr: string = "";
  /** 数据存储目录路径 */
  dataDir: string = "";
  /** 日志等级 {@link LogLevel} */
  logLevel: number = 5;
  /** 控制台是否输出日志 */
  isLogStandardOutput: boolean = false;
  /** 日志输出的路径 */
  logFilePath: string = "";
}

/**
 * 消息对象
 */
export class Message {
  /** 消息唯一ID */
  clientMsgID: string = "";
  /** 消息服务器ID */
  serverMsgID: string = "";
  /** 消息创建时间，单位纳秒 */
  createTime: number = 0;
  /** 消息发送时间，单位ms */
  sendTime: number = 0;
  /** 会话类型 1:单聊 2:群聊 {@link ConversationType} */
  sessionType: number = 0;
  /** 发送者ID */
  sendID: string = "";
  /** 接收者ID */
  recvID: string = "";
  /** 标识消息是用户级别还是系统级别 100:用户 200:系统 */
  msgFrom: number = 0;
  /** 消息类型 {@link MessageType} */
  contentType: number = 0;
  /** 平台类型 {@link Platform} */
  platformID: number = 0;
  /** 发送者昵称 */
  senderNickname: string = "";
  /** 发送者头像 */
  senderFaceUrl: string = "";
  /** 群聊ID */
  groupID: string = "";
  /** 消息唯一序列号 */
  seq: number = 0;
  /** 是否已读 */
  isRead: boolean = false;
  /** 消息状态 {@link MessageStatus} */
  status: number = 0;
  /** 是否React */
  isReact: boolean = false;
  /** 是否外部扩展 */
  isExternalExtensions: boolean = false;
  /** 离线消息推送内容 */
  offlinePush: OfflinePushInfo | null = null;
  /** 附加信息 */
  attachedInfo: string = "";
  /** android附加字段 */
  ext: string = "";
  /** go附加字段 */
  ex: string = "";
  /** 本地消息拓展信息 */
  localEx: string = "";
  /** 图片信息 */
  pictureElem: PictureElem | null = null;
  /** 语音信息 */
  soundElem: SoundElem | null = null;
  /** 视频信息 */
  videoElem: VideoElem | null = null;
  /** 文件信息 */
  fileElem: FileElem | null = null;
  /** @信息 */
  atTextElem: AtTextElem | null = null;
  /** 位置信息 */
  locationElem: LocationElem | null = null;
  /** 自定义信息 */
  customElem: CustomElem | null = null;
  /** 引用消息 */
  quoteElem: QuoteElem | null = null;
  /** 合并信息 */
  mergeElem: MergeElem | null = null;
  /** 通知 */
  notificationElem: NotificationElem | null = null;
  /** 自定义表情 */
  faceElem: FaceElem | null = null;
  /** 附加信息 如：群消息已读 */
  attachedInfoElem: AttachedInfoElem | null = null;
  /** 文本信息 */
  textElem: TextElem | null = null;
  /** 个人名片 */
  cardElem: CardElem | null = null;
  /** 高级文本信息 */
  advancedTextElem: AdvancedTextElem | null = null;
  /** 正在输入状态 */
  typingElem: TypingElem | null = null;
}

/**
 * 图片元素
 */
export class PictureElem {
  /** 本地资源地址 */
  sourcePath: string = "";
  /** 本地图片详情 */
  sourcePicture: PictureInfo | null = null;
  /** 大图详情 */
  bigPicture: PictureInfo | null = null;
  /** 缩略图详情 */
  snapshotPicture: PictureInfo | null = null;
}

/**
 * 图片信息
 */
export class PictureInfo {
  /** 唯一ID */
  uuid: string = "";
  /** 图片类型 */
  type: string = "";
  /** 图片大小 */
  size: number = 0;
  /** 图片宽度 */
  width: number = 0;
  /** 图片高度 */
  height: number = 0;
  /** 图片oss地址 */
  url: string = "";
}

/**
 * 语音元素
 */
export class SoundElem {
  /** 唯一ID */
  uuid: string = "";
  /** 本地资源地址 */
  soundPath: string = "";
  /** oss地址 */
  sourceUrl: string = "";
  /** 音频大小 */
  dataSize: number = 0;
  /** 音频时长 s */
  duration: number = 0;
}

/**
 * 视频元素
 */
export class VideoElem {
  /** 视频本地资源地址 */
  videoPath: string = "";
  /** 视频唯一ID */
  videoUUID: string = "";
  /** 视频oss地址 */
  videoUrl: string = "";
  /** 视频类型 */
  videoType: string = "";
  /** 视频大小 */
  videoSize: number = 0;
  /** 视频时长 */
  duration: number = 0;
  /** 视频快照本地地址 */
  snapshotPath: string = "";
  /** 视频快照唯一ID */
  snapshotUUID: string = "";
  /** 视频快照大小 */
  snapshotSize: number = 0;
  /** 视频快照oss地址 */
  snapshotUrl: string = "";
  /** 视频快照宽度 */
  snapshotWidth: number = 0;
  /** 视频快照高度 */
  snapshotHeight: number = 0;
}

/**
 * 文件元素
 */
export class FileElem {
  /** 文件本地资源地址 */
  filePath: string = "";
  /** id */
  uuid: string = "";
  /** oss地址 */
  sourceUrl: string = "";
  /** 文件名称 */
  fileName: string = "";
  /** 文件大小 */
  fileSize: number = 0;
}

/**
 * @文本元素
 */
export class AtTextElem {
  /** at消息内容 */
  text: string = "";
  /** 被@的用户id集合 */
  atUserList: string[] = [];
  /** 被@的用户信息 */
  atUsersInfo: AtUserInfo[] = [];
  /** 自己是否被@了 */
  isAtSelf: boolean = false;
  /** 引用消息 */
  quoteMessage: Message | null = null;
}

/**
 * At用户信息
 */
export class AtUserInfo {
  /** 被at的用户的id */
  atUserID: string = "";
  /** 被at的用户的昵称 */
  groupNickname: string = "";
}

/**
 * 位置元素
 */
export class LocationElem {
  /** 位置描述 */
  description: string = "";
  /** 经度 */
  longitude: number = 0;
  /** 纬度 */
  latitude: number = 0;
}

/**
 * 自定义元素
 */
export class CustomElem {
  /** 自定义数据 */
  data: string = "";
  /** 扩展数据 */
  extension: string = "";
  /** 描述 */
  description: string = "";
}

/**
 * 引用元素
 */
export class QuoteElem {
  /** 回复内容 */
  text: string = "";
  /** 被回复的消息 */
  quoteMessage: Message | null = null;
}

/**
 * 合并元素
 */
export class MergeElem {
  /** 标题 */
  title: string = "";
  /** 摘要 */
  abstractList: string[] = [];
  /** 具体选择合并的消息列表 */
  multiMessage: Message[] = [];
}

/**
 * 通知元素
 */
export class NotificationElem {
  /** 通知内容详情 */
  detail: string = "";
  /** 默认提示内容 */
  defaultTips: string = "";
}

/**
 * 表情元素
 */
export class FaceElem {
  /** app内嵌表情包，根据index匹配显示表情图 */
  index: number = 0;
  /** 其他表情，如url表情，直接加载url即可 */
  data: string = "";
}

/**
 * 附加信息元素
 */
export class AttachedInfoElem {
  /** 组信息已读详细 */
  groupHasReadInfo: GroupHasReadInfo | null = null;
  /** 是否是私聊消息（阅后即焚消息） */
  isPrivateChat: boolean = false;
  /** 消息已读时间 */
  hasReadTime: number = 0;
  /** 阅读时长 s 从hasReadTime时间算起，超过了burnDuration秒触发销毁 */
  burnDuration: number = 0;
  /** 不发送通知推送 */
  notSenderNotificationPush: boolean = false;
  /** 是否加密 */
  isEncryption: boolean = false;
  /** 是否在加密状态 */
  inEncryptStatus: boolean = false;
}

/**
 * 群组已读信息
 */
export class GroupHasReadInfo {
  /** 已读数 */
  hasReadCount: number = 0;
  /** 未读数 */
  unreadCount: number = 0;
}

/**
 * 文本元素
 */
export class TextElem {
  /** 文本内容 */
  content: string = "";
}

/**
 * 名片元素
 */
export class CardElem {
  /** 用户ID */
  userID: string = "";
  /** 昵称 */
  nickname: string = "";
  /** 头像 */
  faceURL: string = "";
  /** 扩展字段 */
  ex: string = "";
}

/**
 * 消息实体
 */
export class MessageEntity {
  /** 类型 */
  type: string = "";
  /** 偏移量 */
  offset: number = 0;
  /** 长度 */
  length: number = 0;
  /** URL */
  url: string = "";
  /** 扩展字段 */
  ex: string = "";
}

/**
 * 高级文本元素
 */
export class AdvancedTextElem {
  /** 文本内容 */
  text: string = "";
  /** 消息实体列表 */
  messageEntityList: MessageEntity[] = [];
}

/**
 * 正在输入元素
 */
export class TypingElem {
  /** 消息提示 */
  msgTips: string = "";
}

/**
 * 离线推送信息
 */
export class OfflinePushInfo {
  /** 推送标题 */
  title: string = "";
  /** 推送描述 */
  desc: string = "";
  /** 扩展字段 */
  ex: string = "";
  /** iOS推送音效 */
  iOSPushSound: string = "";
  /** iOS角标数量 */
  iOSBadgeCount: boolean = false;
}

/**
 * 会话信息
 */
export class ConversationInfo {
  /** 会话ID */
  conversationID: string = "";
  /** 会话类型 {@link ConversationType} */
  conversationType: number = 0;
  /** 用户ID */
  userID: string = "";
  /** 群ID */
  groupID: string = "";
  /** 显示名称 */
  showName: string = "";
  /** 头像URL */
  faceUrl: string = "";
  /** 接收消息选项 {@link MessageReceiveOptType} */
  recvMsgOpt: number = 0;
  /** 未读消息数 */
  unreadCount: number = 0;
  /** 群@类型 {@link GroupAtType} */
  groupAtType: number = 0;
  /** 最新消息 */
  latestMsg: string = "";
  /** 最新消息发送时间 */
  latestMsgSendTime: number = 0;
  /** 草稿文本 */
  draftText: string = "";
  /** 草稿文本时间 */
  draftTextTime: number = 0;
  /** 是否置顶 */
  isPinned: boolean = false;
  /** 是否私聊 */
  isPrivateChat: boolean = false;
  /** 扩展字段 */
  ex: string = "";
  /** 是否不在群中 */
  isNotInGroup: boolean = false;
  /** 阅后即焚时长 */
  burnDuration: number = 0;
  /** 消息销毁时间 */
  msgDestructTime: number = 0;
  /** 是否消息销毁 */
  isMsgDestruct: boolean = false;
}

/**
 * 群组@信息
 */
export class GroupAtInfo {
  /** 群ID */
  groupID: string = "";
  /** @类型 {@link GroupAtType} */
  atType: number = 0;
  /** 序列号 */
  seq: number = 0;
}

/**
 * 好友信息
 */
export class FriendInfo {
  /** 好友id */
  userID: string = "";
  /** 好友昵称 */
  nickname: string = "";
  /** 好友头像 */
  faceURL: string = "";
  /** 性别 */
  gender: number = 0;
  /** 手机号 */
  phoneNumber: string = "";
  /** 出生日期 */
  birth: number = 0;
  /** 邮箱 */
  email: string = "";
  /** 好友备注名 */
  remark: string = "";
  /** 扩展字段 */
  ex: string = "";
  /** 创建时间 */
  createTime: number = 0;
  /** 添加方式 */
  addSource: number = 0;
  /** 操作者id */
  operatorUserID: string = "";
}

/**
 * 好友申请信息
 */
export class FriendApplication {
  /** 请求用户id */
  fromUserID: string = "";
  /** 请求用户昵称 */
  fromNickname: string = "";
  /** 请求用户头像 */
  fromFaceURL: string = "";
  /** 请求用户性别 */
  fromGender: number = 0;
  /** 接受用户id */
  toUserID: string = "";
  /** 接受用户昵称 */
  toNickname: string = "";
  /** 接受用户头像 */
  toFaceURL: string = "";
  /** 接受用户性别 */
  toGender: number = 0;
  /** 处理结果 0:等待处理，1:已同意，2:已拒绝 {@link ApplyHandleResult} */
  handleResult: number = 0;
  /** 请求备注 */
  reqMsg: string = "";
  /** 创建时间 */
  createTime: number = 0;
  /** 处理者id */
  handlerUserID: string = "";
  /** 处理备注 */
  handleMsg: string = "";
  /** 处理时间 */
  handleTime: number = 0;
  /** 扩展字段 */
  ex: string = "";
}

/**
 * 黑名单信息
 */
export class BlackInfo {
  /** 用户id */
  userID: string = "";
  /** 昵称 */
  nickname: string = "";
  /** 头像 */
  faceURL: string = "";
  /** 性别 */
  gender: number = 0;
  /** 创建时间 */
  createTime: number = 0;
  /** 添加方式 */
  addSource: number = 0;
  /** 操作者 */
  operatorUserID: string = "";
  /** 附加信息 */
  ex: string = "";
}

/**
 * 群组信息
 */
export class GroupInfo {
  /** 群ID */
  groupID: string = "";
  /** 群名 */
  groupName: string = "";
  /** 群公告 */
  notification: string = "";
  /** 群简介 */
  introduction: string = "";
  /** 群头像 */
  faceURL: string = "";
  /** 群主id */
  ownerUserID: string = "";
  /** 创建时间 */
  createTime: number = 0;
  /** 群成员数量 */
  memberCount: number = 0;
  /** 群状态：0:正常 1:禁用 2:解散 3:禁言 {@link GroupStatus} */
  status: number = 0;
  /** 创建者id */
  creatorUserID: string = "";
  /** 群类型 {@link GroupType} */
  groupType: number = 0;
  /** 扩展字段 */
  ex: string = "";
  /** 进群验证方式 {@link GroupVerification} */
  needVerification: number = 0;
  /** 不允许通过群获取成员资料 0:关闭，1:打开 */
  lookMemberInfo: number = 0;
  /** 不允许通过群添加好友 0:关闭，1:打开 */
  applyMemberFriend: number = 0;
  /** 通知更新时间 */
  notificationUpdateTime: number = 0;
  /** 通知更新人 */
  notificationUserID: string = "";
}

/**
 * 群组成员信息
 */
export class GroupMemberInfo {
  /** 群id */
  groupID: string = "";
  /** 用户id */
  userID: string = "";
  /** 群内昵称 */
  nickname: string = "";
  /** 头像 */
  faceURL: string = "";
  /** 群角色 {@link GroupRole} */
  roleLevel: number = 0;
  /** 入群时间 */
  joinTime: number = 0;
  /** 加入方式 2:邀请加入 3:搜索加入 4:通过二维码加入 {@link JoinSource} */
  joinSource: number = 0;
  /** 操作者id */
  operatorUserID: string = "";
  /** 扩展字段 */
  ex: string = "";
  /** 禁言结束时间 */
  muteEndTime: number = 0;
  /** 邀请人id */
  inviterUserID: string = "";
}

/**
 * 群组申请信息
 */
export class GroupApplication {
  /** 群id */
  groupID: string = "";
  /** 群名 */
  groupName: string = "";
  /** 群公告 */
  notification: string = "";
  /** 群简介 */
  introduction: string = "";
  /** 群头像 */
  groupFaceURL: string = "";
  /** 创建时间 */
  createTime: number = 0;
  /** 状态 */
  status: number = 0;
  /** 创建者id */
  creatorUserID: string = "";
  /** 群类型 */
  groupType: number = 0;
  /** 拥有者id */
  ownerUserID: string = "";
  /** 成员数量 */
  memberCount: number = 0;
  /** 申请者的id */
  userID: string = "";
  /** 申请者的昵称 */
  nickname: string = "";
  /** 申请者的头像 */
  userFaceURL: string = "";
  /** 申请者的性别 */
  gender: number = 0;
  /** 处理结果 -1:拒绝 1:同意 {@link ApplyHandleResult} */
  handleResult: number = 0;
  /** 申请原因 */
  reqMsg: string = "";
  /** 处理结果描述 */
  handledMsg: string = "";
  /** 申请时间 */
  reqTime: number = 0;
  /** 处理者的id */
  handleUserID: string = "";
  /** 处理时间 */
  handledTime: number = 0;
  /** 扩展字段 */
  ex: string = "";
  /** 加入来源 2:通过邀请 3:通过搜索 4:通过二维码 {@link JoinSource} */
  joinSource: number = 0;
  /** 邀请进群用户ID */
  inviterUserID: string = "";
}

/**
 * 用户公开信息
 */
export class PublicUserInfo {
  /** 用户id */
  userID: string = "";
  /** 昵称 */
  nickname: string = "";
  /** 头像 */
  faceURL: string = "";
  /** 扩展字段 */
  ex: string = "";
  /** 创建时间 */
  createTime: number = 0;
}

/**
 * 用户信息
 */
export class UserInfo {
  /** 用户id */
  userID: string = "";
  /** 用户名 */
  nickname: string = "";
  /** 用户头像 */
  faceURL: string = "";
  /** 性别：1男，2女 */
  gender: number = 0;
  /** 手机号 */
  phoneNumber: string = "";
  /** 生日 */
  birth: number = 0;
  /** 邮箱 */
  email: string = "";
  /** 扩展字段 */
  ex: string = "";
  /** 备注 */
  remark: string = "";
  /** 公开的信息 */
  publicInfo: PublicUserInfo | null = null;
  /** 仅好友可见的信息 */
  friendInfo: FriendInfo | null = null;
  /** 黑名单信息 */
  blackInfo: BlackInfo | null = null;
  /** 全局免打扰 */
  globalRecvMsgOpt: number = 0;
  /** 是否允许添加为好友 1:允许，2:否 */
  allowAddFriend: number = 0;
  /** 新消息铃声 1:允许，2:否 */
  allowBeep: number = 0;
  /** 新消息震动 1:允许，2:否 */
  allowVibration: number = 0;
  /** 禁止登录 */
  forbidden: number = 0;
  /** 创建日期 */
  createTime: number = 0;
}

/**
 * 订阅用户状态信息
 */
export class SubscribeUsersStatus {
  /** 用户ID */
  userID: string = "";
  /** 状态 */
  status: number = 0;
  /** 平台ID列表 */
  platformIDs: number[] = [];
}

/**
 * 用户在线状态
 */
export class UserStatus {
  /** 用户ID */
  userID: string = "";
  /** 状态 */
  status: number = 0;
  /** 扩展信息 */
  ext: string = "";
}

/**
 * 消息已读回执
 */
export class MsgReceipt {
  /** 会话ID */
  conversationID: string = "";
  /** 消息ID */
  clientMsgID: string = "";
  /** 已读时间 */
  readTime: number = 0;
}

/**
 * 撤回消息信息
 */
export class RevokedInfo {
  /** 撤回者ID */
  revokerID: string = "";
  /** 撤回者群角色 {@link GroupRole} */
  revokerRole: number = 0;
  /** 撤回者昵称 */
  revokerNickname: string = "";
  /** 消息id */
  clientMsgID: string = "";
  /** 撤回时间 */
  revokeTime: number = 0;
  /** 消息发送时间 */
  sourceMessageSendTime: number = 0;
  /** 消息发送者 */
  sourceMessageSendID: string = "";
  /** 消息发送者昵称 */
  sourceMessageSenderNickname: string = "";
  /** 会话类型 {@link ConversationType} */
  sessionType: number = 0;
}

/**
 * 本地消息搜索参数
 */
export class SearchLocalMessagesParams {
  /** 会话ID */
  conversationID: string = "";
  /** 关键词列表 */
  keywordList: string[] = [];
  /** 关键词匹配类型 0:精确匹配 1:模糊匹配 */
  keywordListMatchType: number = 0;
  /** 发送者用户ID列表 */
  senderUserIDList: string[] = [];
  /** 消息类型列表 */
  messageTypeList: number[] = [];
  /** 搜索时间位置（时间戳） */
  searchTimePosition: number = 0;
  /** 搜索时间范围（毫秒） */
  searchTimePeriod: number = 0;
  /** 页索引 */
  pageIndex: number = 1;
  /** 每页数量 */
  count: number = 20;
}

/**
 * 获取历史消息参数
 */
export class GetAdvancedHistoryMessageParams {
  /** 会话ID */
  conversationID: string = "";
  /** 起始消息ID */
  startClientMsgID: string = "";
  /** 消息数量 */
  count: number = 20;
  /** 视图类型*/
  viewType:ViewType = ViewType.Search;
}

/**
 * C2C已读回执信息
 */
export class C2CReadReceiptInfo {
  /** 用户id */
  userID: string = "";
  /** 组id */
  groupID: string = "";
  /** 已读消息id列表 */
  msgIDList: string[] = [];
  /** 阅读时间 */
  readTime: number = 0;
  /** 消息来源 100:用户 200:系统 */
  msgFrom: number = 0;
  /** 消息类型 {@link MessageType} */
  contentType: number = 0;
  /** 会话类型 1:单聊 2:群聊 {@link ConversationType} */
  sessionType: number = 0;
}

/**
 * 群消息回执
 */
export class GroupMessageReceipt {
  /** 会话ID */
  conversationID: string = "";
  /** 群消息已读信息列表 */
  groupMessageReadInfo: GroupMessageReadInfo[] = [];
}

/**
 * 群消息已读信息
 */
export class GroupMessageReadInfo {
  /** 客户端消息ID */
  clientMsgID: string = "";
  /** 已读数量 */
  hasReadCount: number = 0;
  /** 未读数量 */
  unreadCount: number = 0;
  /** 已读成员列表 */
  readMembers: GroupMemberInfo[] = [];
}
