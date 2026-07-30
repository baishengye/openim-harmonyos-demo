/**
 * OpenIM SDK for HarmonyOS
 * 消息相关实体类
 */

/**
 * SDK初始化配置
 */
export class InitConfig {
  /** 平台ID，1:Android, 2:iOS, 3:Windows, 4:MacOSX, 5:Linux, 6:Web, 7:Linux */
  platformID: number = 7;
  /** API地址，如：http://xxx:10000 */
  apiAddr: string = "";
  /** WebSocket地址，如：ws://xxx:17778 */
  wsAddr: string = "";
  /** 数据存储目录路径 */
  dataDir: string = "";
  /** 日志等级，如：5(Debug), 3(Error) */
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
  /** 消息创建时间（纳秒） */
  createTime: number = 0;
  /** 消息发送时间（毫秒） */
  sendTime: number = 0;
  /** 会话类型 1:单聊 2:群聊 */
  sessionType: number = 0;
  /** 发送者ID */
  sendID: string = "";
  /** 接收者ID */
  recvID: string = "";
  /** 消息来源 100:用户 200:系统 */
  msgFrom: number = 0;
  /** 消息类型 */
  contentType: number = 0;
  /** 平台类型 */
  platformID: number = 0;
  /** 发送者昵称 */
  senderNickname: string = "";
  /** 发送者头像 */
  senderFaceUrl: string = "";
  /** 群聊ID */
  groupID: string = "";
  /** 消息序列号 */
  seq: number = 0;
  /** 是否已读 */
  isRead: boolean = false;
  /** 消息状态 */
  status: number = 0;
  /** 是否React */
  isReact: boolean = false;
  /** 是否外部扩展 */
  isExternalExtensions: boolean = false;
  /** 离线推送信息 */
  offlinePush: OfflinePushInfo = new OfflinePushInfo();
  /** 附加信息 */
  attachedInfo: string = "";
  /** 附加字段 */
  ext: string = "";
  /** Go附加字段 */
  ex: string = "";
  /** 本地扩展信息 */
  localEx: string = "";
  /** 图片信息 */
  pictureElem: PictureElem = new PictureElem();
  /** 语音信息 */
  soundElem: SoundElem = new SoundElem();
  /** 视频信息 */
  videoElem: VideoElem = new VideoElem();
  /** 文件信息 */
  fileElem: FileElem = new FileElem();
  /** @信息 */
  atTextElem: AtTextElem = new AtTextElem();
  /** 位置信息 */
  locationElem: LocationElem = new LocationElem();
  /** 自定义信息 */
  customElem: CustomElem = new CustomElem();
  /** 引用消息 */
  quoteElem: QuoteElem = new QuoteElem();
  /** 合并消息 */
  mergeElem: MergeElem = new MergeElem();
  /** 通知信息 */
  notificationElem: NotificationElem = new NotificationElem();
  /** 表情信息 */
  faceElem: FaceElem = new FaceElem();
  /** 附加信息 */
  attachedInfoElem: AttachedInfoElem = new AttachedInfoElem();
  /** 文本信息 */
  textElem: TextElem = new TextElem();
  /** 名片信息 */
  cardElem: CardElem = new CardElem();
}

/**
 * 图片元素
 */
export class PictureElem {
  /** 图片路径 */
  sourcePath: string = "";
  /** 原图信息 */
  sourcePicture: ImageInfo = new ImageInfo();
  /** 大图信息 */
  bigPicture: ImageInfo = new ImageInfo();
  /** 缩略图信息 */
  snapshotPicture: ImageInfo = new ImageInfo();
}

/**
 * 图片信息
 */
export class ImageInfo {
  /** UUID */
  uuid: string = "";
  /** 图片类型 */
  type: string = "";
  /** 大小 */
  size: number = 0;
  /** 宽度 */
  width: number = 0;
  /** 高度 */
  height: number = 0;
  /** URL */
  url: string = "";
}

/**
 * 语音元素
 */
export class SoundElem {
  /** UUID */
  uuid: string = "";
  /** 语音路径 */
  soundPath: string = "";
  /** 来源 */
  sourceUrl: string = "";
  /** 大小 */
  dataSize: number = 0;
  /** 时长（秒） */
  duration: number = 0;
  /** URL */
  url: string = "";
}

/**
 * 视频元素
 */
export class VideoElem {
  /** UUID */
  uuid: string = "";
  /** 视频路径 */
  videoPath: string = "";
  /** 视频类型 */
  videoType: string = "";
  /** 缩略图路径 */
  snapshotPath: string = "";
  /** 视频时长（秒） */
  duration: number = 0;
  /** 缩略图信息 */
  snapshotSize: Size = new Size();
  /** 缩略图URL */
  snapshotUrl: string = "";
  /** 视频大小 */
  videoSize: number = 0;
  /** 视频URL */
  videoUrl: string = "";
}

/**
 * 文件元素
 */
export class FileElem {
  /** UUID */
  uuid: string = "";
  /** 文件路径 */
  filePath: string = "";
  /** 文件名 */
  fileName: string = "";
  /** 文件大小 */
  fileSize: number = 0;
  /** 过期时间 */
  expireTime: number = 0;
  /** URL */
  url: string = "";
}

/**
 * @文本元素
 */
export class AtTextElem {
  /** 文本内容 */
  text: string = "";
  /** @用户列表 */
  atUserList: string[] = [];
  /** 是否@所有人 */
  isAtSelf: boolean = false;
}

/**
 * 位置元素
 */
export class LocationElem {
  /** 描述 */
  description: string = "";
  /** 纬度 */
  latitude: number = 0;
  /** 经度 */
  longitude: number = 0;
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
  /** 引用文本 */
  quoteText: string = "";
  /** 引用消息 */
  quoteMessage: Message = new Message();
}

/**
 * 合并元素
 */
export class MergeElem {
  /** 标题 */
  title: string = "";
  /** 摘要列表 */
  summaryList: string[] = [];
  /** 消息列表 */
  messageList: Message[] = [];
}

/**
 * 通知元素
 */
export class NotificationElem {
  /** 详情 */
  detail: string = "";
  /** 群ID */
  groupID: string = "";
  /** 操作者ID */
  opUserID: string = "";
  /** 群类型 */
  groupType: string = "";
}

/**
 * 表情元素
 */
export class FaceElem {
  /** 索引 */
  index: number = 0;
  /** 数据 */
  data: string = "";
  /** URL */
  url: string = "";
}

/**
 * 附加信息元素
 */
export class AttachedInfoElem {
  /** 群组已读数量 */
  groupHasReadCount: number = 0;
  /** 群组未读数量 */
  groupHasNotReadCount: number = 0;
  /** 私聊已读数量 */
  privateHasReadCount: number = 0;
  /** 是否已读 */
  isRead: boolean = false;
  /** 消息发送者在线状态 */
  messageFromApp: string = "";
  /** 消息到达人数 */
  participantNumber: number = 0;
  /** 消息ID */
  messageEntityList: MessageEntity[] = [];
}

/**
 * 消息实体
 */
export class MessageEntity {
  /** 起始位置 */
  startIndex: number = 0;
  /** 结束位置 */
  endIndex: number = 0;
  /** 类型 */
  type: string = "";
  /** 数据 */
  data: string = "";
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
  faceUrl: string = "";
  /** 附加信息 */
  ex: string = "";
}

/**
 * 尺寸
 */
export class Size {
  /** 宽度 */
  width: number = 0;
  /** 高度 */
  height: number = 0;
}

/**
 * 离线推送信息
 */
export class OfflinePushInfo {
  /** 推送内容 */
  pushContent: string = "";
  /** 推送数据 */
  pushData: string = "";
  /** 是否禁用 */
  disablePush: boolean = false;
  /** iOS推送音效 */
  iosSound: string = "";
  /** iOS角标 */
  iosBadgeMode: number = 0;
  /** iOS通知名称 */
  iosNotificationType: number = 0;
  /** 安卓通知通道 */
  androidNotificationChannelID: string = "";
  /** 安卓声音 */
  androidSound: string = "";
  /** 安卓重要性 */
  androidImportance: number = 0;
  /** 过滤表达式 */
  androidNotificationFilter: string = "";
  /** 苹果徽章数量 */
  iosBadgeCount: number = 0;
  /** 信令 */
  signalInfo: string = "";
  /** 安卓背景图 */
  androidBackgroundUri: string = "";
  /** 标题 */
  title: string = "";
  /** 苹果角标名称 */
  iosSubtitle: string = "";
}

/**
 * 消息已读回执
 */
export class MsgReceipt {
  /** 会话ID */
  conversationID: string = "";
  /** 消息ID */
  clientMsgID: string = "";
  /** 读取时间 */
  readTime: number = 0;
  /** 已读数量 */
  readCount: number = 0;
}

/**
 * 撤回消息
 */
export class RevokedInfo {
  /** 撤回者ID */
  revokerID: string = "";
  /** 撤回者客户端 */
  revokerClientMsgID: string = "";
  /** 消息ID */
  serverMsgID: string = "";
  /** 撤回时间 */
  revokeTime: number = 0;
  /** 是否是发送者撤回 */
  isSelfRevoke: boolean = false;
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
  /** 视图类型 */
  viewType: number = 0;
}
