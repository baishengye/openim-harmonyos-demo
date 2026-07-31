// src/main/ets/index.ets - OpenIM SDK for HarmonyOS 导出文件

// SDK主入口
export { OpenIM, OpenIMClient, getSDK } from './sdk/IMSdk';

// 管理器
export { MessageManager } from './sdk/manager/MessageManager';
export { ConversationManager } from './sdk/manager/ConversationManager';
export { FriendshipManager } from './sdk/manager/FriendshipManager';
export { GroupManager } from './sdk/manager/GroupManager';
export { UserInfoManager } from './sdk/manager/UserInfoManager';
export { LoginManager } from './sdk/manager/LoginManager';
export { MiscManager } from './sdk/manager/MiscManager';

// 枚举
export {
  AllowType,
  ApplyHandleResult,
  ConversationType,
  GroupAtType,
  GroupMemberFilter,
  GroupRole,
  GroupStatus,
  GroupType,
  GroupVerification,
  JoinSource,
  LogLevel,
  LoginStatus,
  MessageStatus,
  MessageType,
  Opt,
  Platform,
  Relationship,
  ViewType,
  SortOrder
} from './sdk/enums/enum';

// 数据模型
export {
  InitConfig,
  Message,
  PictureElem,
  PictureInfo,
  SoundElem,
  VideoElem,
  FileElem,
  AtTextElem,
  AtUserInfo,
  LocationElem,
  CustomElem,
  QuoteElem,
  MergeElem,
  NotificationElem,
  FaceElem,
  AttachedInfoElem,
  CardElem,
  AdvancedTextElem,
  TypingElem,
  TextElem,
  GroupInfo,
  GroupMemberInfo,
  ConversationInfo,
  FriendInfo,
  FriendApplication,
  BlackInfo,
  UserExInfo,
  SingleTypeKeyInfoSum,
  MessageKv,
  UsersOnlineStatus,
  UserInfo,
  PublicUserInfo,
  OfflinePushInfo,
  GetAdvancedHistoryMessageParams,
  SearchLocalMessagesParams
} from './sdk/models/entity';

// 监听器接口
export {
  BaseCallback,
  SendMsgCallBack,
  UploadFileCallback,
  UploadLogProgress,
  ConnListener,
  MsgListener,
  ConvListener,
  GroupListener,
  FriendListener,
  UserListener,
  SignalingListener,
  CustomBusinessListener,
  MsgKvInfoListener
} from './sdk/listeners/listener';

// 监听器实现
export {
  ConnListenerWrapper,
  MsgListenerWrapper,
  ConvListenerWrapper,
  GroupListenerWrapper,
  FriendListenerWrapper,
  UserListenerWrapper
} from './sdk/listeners/ListenerImpl';

// 工具函数
export { buildOperationID } from './sdk/utils/Utils';
