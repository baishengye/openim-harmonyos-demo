import {
  GroupType,
  SessionType,
  MessageType,
  Platform,
  MessageStatus,
  GroupStatus,
  GroupVerificationType,
  AllowType,
  GroupJoinSource,
  GroupMemberRole,
  MessageReceiveOptType,
  GroupAtType,
  LogLevel,
  ApplicationHandleResult,
  Relationship,
  OnlineState,
  CbEvents,
} from './enum';


export interface SDKError {
  errCode: number;
  errMsg: string;
};

export interface WsResponse<T = string>  {
  event: string;
  errCode: number;
  errMsg: string;
  data: T;
  operationID: string;
};
export interface IMConfig {
  platformID: Platform;
  apiAddr: string;
  wsAddr: string;
  dataDir: string;
  logLevel: LogLevel;
  isLogStandardOutput: boolean;
  logFilePath: string;
  isExternalExtensions: boolean;
};
export interface MessageEntity {
  type: string;
  offset: number;
  length: number;
  url?: string;
  info?: string;
};
export interface PicBaseInfo {
  uuid: string;
  type: string;
  size: number;
  width: number;
  height: number;
  url: string;
};
export interface AtUsersInfoItem {
  atUserID: string;
  groupNickname: string;
};
export interface GroupApplicationItem {
  createTime: number;
  creatorUserID: string;
  ex: string;
  groupFaceURL: string;
  groupID: string;
  groupName: string;
  groupType: GroupType;
  handleResult: ApplicationHandleResult;
  handleUserID: string;
  handledMsg: string;
  handledTime: number;
  introduction: string;
  memberCount: number;
  nickname: string;
  notification: string;
  ownerUserID: string;
  reqMsg: string;
  reqTime: number;
  joinSource: GroupJoinSource;
  status: GroupStatus;
  userFaceURL: string;
  userID: string;
};
export interface FriendApplicationItem {
  createTime: number;
  ex: string;
  fromFaceURL: string;
  fromNickname: string;
  fromUserID: string;
  handleMsg: string;
  handleResult: ApplicationHandleResult;
  handleTime: number;
  handlerUserID: string;
  reqMsg: string;
  toFaceURL: string;
  toNickname: string;
  toUserID: string;
};
export interface PublicUserItem {
  nickname: string;
  userID: string;
  faceURL: string;
  ex: string;
};
export interface SelfUserInfo {
  createTime: number;
  ex: string;
  faceURL: string;
  nickname: string;
  userID: string;
  globalRecvMsgOpt: MessageReceiveOptType;
};

export interface PartialUserInfo {
  userID: string;
  createTime?: number;
  ex?: string;
  faceURL?: string;
  nickname?: string;
  globalRecvMsgOpt?: MessageReceiveOptType;
}

export interface FriendUserItem {
  addSource: number;
  createTime: number;
  ex: string;
  faceURL: string;
  userID: string;
  nickname: string;
  operatorUserID: string;
  ownerUserID: string;
  remark: string;
  isPinned: boolean;
  attachedInfo: string;
};
export interface SearchedFriendsInfo extends FriendUserItem {
  relationship: Relationship;
}
export interface FriendshipInfo {
  result: number;
  userID: string;
};
export interface BlackUserItem {
  addSource: number;
  userID: string;
  createTime: number;
  ex: string;
  faceURL: string;
  nickname: string;
  operatorUserID: string;
  ownerUserID: string;
};
export interface GroupItem {
  groupID: string;
  groupName: string;
  notification: string;
  notificationUserID: string;
  notificationUpdateTime: number;
  introduction: string;
  faceURL: string;
  ownerUserID: string;
  createTime: number;
  memberCount: number;
  status: GroupStatus;
  creatorUserID: string;
  groupType: GroupType;
  needVerification: GroupVerificationType;
  ex: string;
  applyMemberFriend: AllowType;
  lookMemberInfo: AllowType;
  displayIsRead: boolean;
};
export interface GroupMemberItem {
  groupID: string;
  userID: string;
  nickname: string;
  faceURL: string;
  roleLevel: GroupMemberRole;
  muteEndTime: number;
  joinTime: number;
  joinSource: GroupJoinSource;
  inviterUserID: string;
  operatorUserID: string;
  ex: string;
};
export interface ConversationItem {
  conversationID: string;
  conversationType: SessionType;
  userID: string;
  groupID: string;
  showName: string;
  faceURL: string;
  recvMsgOpt: MessageReceiveOptType;
  unreadCount: number;
  groupAtType: GroupAtType;
  latestMsg: string;
  latestMsgSendTime: number;
  draftText: string;
  draftTextTime: number;
  burnDuration: number;
  msgDestructTime: number;
  isPinned: boolean;
  isNotInGroup: boolean;
  isPrivateChat: boolean;
  isMsgDestruct: boolean;
  attachedInfo: string;
  ex?: string;
};
export interface MessageItem {
  clientMsgID: string;
  serverMsgID: string;
  createTime: number;
  sendTime: number;
  sessionType: SessionType;
  sendID: string;
  recvID: string;
  msgFrom: number;
  contentType: MessageType;
  senderPlatformID: Platform;
  senderNickname: string;
  senderFaceUrl: string;
  groupID: string;
  content: string;
  seq: number;
  isRead: boolean;
  status: MessageStatus;
  isReact?: boolean;
  isExternalExtensions?: boolean;
  offlinePush?: OfflinePush;
  ex?: string;
  localEx?: string;
  textElem?: TextElem;
  cardElem?: CardElem;
  pictureElem?: PictureElem;
  soundElem?: SoundElem;
  videoElem?: VideoElem;
  fileElem?: FileElem;
  mergeElem?: MergeElem;
  atTextElem?: AtTextElem;
  faceElem?: FaceElem;
  locationElem?: LocationElem;
  customElem?: CustomElem;
  quoteElem?: QuoteElem;
  notificationElem?: NotificationElem;
  advancedTextElem?: AdvancedTextElem;
  typingElem?: TypingElem;
  attachedInfoElem: AttachedInfoElem;
};
export interface TextElem {
  content: string;
};
export interface CardElem {
  userID: string;
  nickname: string;
  faceURL: string;
  ex: string;
};
export interface AtTextElem {
  text: string;
  atUserList: string[];
  atUsersInfo?: AtUsersInfoItem[];
  quoteMessage?: MessageItem;
  isAtSelf?: boolean;
};
export interface NotificationElem {
  detail: string;
};
export interface AdvancedTextElem {
  text: string;
  messageEntityList: MessageEntity[];
};
export interface TypingElem {
  msgTips: string;
};
export interface CustomElem {
  data: string;
  description: string;
  extension: string;
};
export interface FileElem {
  filePath: string;
  uuid: string;
  sourceUrl: string;
  fileName: string;
  fileSize: number;
};
export interface FaceElem {
  index: number;
  data: string;
};
export interface LocationElem {
  description: string;
  longitude: number;
  latitude: number;
};
export interface MergeElem {
  title: string;
  abstractList: string[];
  multiMessage: MessageItem[];
  messageEntityList: MessageEntity[];
};
export interface OfflinePush {
  title: string;
  desc: string;
  ex: string;
  iOSPushSound: string;
  iOSBadgeCount: boolean;
};
export interface PictureElem {
  sourcePath: string;
  sourcePicture: Picture;
  bigPicture: Picture;
  snapshotPicture: Picture;
};
export interface AttachedInfoElem {
  groupHasReadInfo: GroupHasReadInfo;
  isPrivateChat: boolean;
  isEncryption: boolean;
  inEncryptStatus: boolean;
  burnDuration: number;
  hasReadTime: number;
  messageEntityList?: MessageEntity[];
  uploadProgress?: UploadProgress;
};
export interface UploadProgress {
  total: number;
  save: number;
  current: number;
};
export interface ProgressEvent {
  progress: number;
  clientMsgID: string;
}
export interface GroupHasReadInfo {
  hasReadCount: number;
  unreadCount: number;
  hasReadUserIDList: string[];
  groupMemberCount: number;
};
export interface Picture {
  uuid: string;
  type: string;
  size: number;
  width: number;
  height: number;
  url: string;
};
export interface QuoteElem {
  text: string;
  quoteMessage: MessageItem;
};
export interface SoundElem {
  uuid: string;
  soundPath: string;
  sourceUrl: string;
  dataSize: number;
  duration: number;
};
export interface VideoElem {
  videoPath: string;
  videoUUID: string;
  videoUrl: string;
  videoType: string;
  videoSize: number;
  duration: number;
  snapshotPath: string;
  snapshotUUID: string;
  snapshotSize: number;
  snapshotUrl: string;
  snapshotWidth: number;
  snapshotHeight: number;
};
export interface AdvancedRevokeContent {
  clientMsgID: string;
  revokeTime: number;
  revokerID: string;
  revokerNickname: string;
  revokerRole: number;
  seq: number;
  sessionType: SessionType;
  sourceMessageSendID: string;
  sourceMessageSendTime: number;
  sourceMessageSenderNickname: string;
};

export interface RevokedInfo {
  revokerID: string;
  revokerRole: number;
  clientMsgID: string;
  revokerNickname: string;
  revokeTime: number;
  sourceMessageSendTime: number;
  sourceMessageSendID: string;
  sourceMessageSenderNickname: string;
  sessionType: number;
  seq: number;
  ex: string;
};

export interface ReceiptInfo {
  userID: string;
  groupID: string;
  msgIDList: string[];
  readTime: number;
  msgFrom: number;
  contentType: MessageType;
  sessionType: SessionType;
};

export interface SearchMessageResult {
  totalCount: number;
  searchResultItems?: SearchMessageResultItem[];
  findResultItems?: SearchMessageResultItem[];
};

export interface SearchMessageResultItem {
  conversationID: string;
  messageCount: number;
  conversationType: SessionType;
  showName: string;
  faceURL: string;
  messageList: MessageItem[];
};

export interface AdvancedGetMessageResult {
  isEnd: boolean;
  lastMinSeq: number;
  errCode: number;
  errMsg: string;
  messageList: MessageItem[];
};

export interface RtcInvite {
  inviterUserID: string;
  inviteeUserIDList: string[];
  customData?: string;
  groupID: string;
  roomID: string;
  timeout: number;
  mediaType: string;
  sessionType: number;
  platformID: number;
  initiateTime?: number;
  busyLineUserIDList?: string[];
};

export interface UserOnlineState {
  platformIDs?: Platform[];
  status: OnlineState;
  userID: string;
};

export interface ConversationInputStatus {
  conversationID: string;
  userID: string;
  platformIDs: Platform[];
};

export interface GroupMessageReceiptInfo {
  conversationID: string;
  groupMessageReadInfo: GroupMessageReadInfo[];
};
export interface GroupMessageReadInfo {
  clientMsgID: string;
  hasReadCount: number;
  unreadCount: number;
  readMembers: GroupMemberItem[];
};

export interface RtcInviteResults {
  liveURL: string;
  roomID: string;
  token: string;
  busyLineUserIDList?: string[];
};

export interface ParticipantInfo {
  userInfo: PublicUserItem;
  groupMemberInfo?: GroupMemberItem;
  groupInfo?: GroupItem;
};

export interface CallingRoomData {
  participant?: ParticipantInfo[];
  invitation?: RtcInvite;
  roomID: string;
};

export interface MsgProgress {
  progress: number;
  clientMsgID: string;
};

export interface WSEvent {
  errCode: number;
  errMsg: string;
};

export interface MessageProgress {
  progress: number;
  message: MessageItem;
};

export type CbEventData =
    | SDKError
    | MessageProgress
    | MsgProgress
    | WSEvent
    | BlackUserItem
    | ConversationItem[]
    | FriendUserItem
    | FriendApplicationItem
    | GroupApplicationItem
    | GroupItem
    | GroupMemberItem
    | ConversationInputStatus
    | RevokedInfo
    | ReceiptInfo[]
    | GroupMessageReceiptInfo
    | MessageItem
    | MessageItem[]
    | SelfUserInfo
    | boolean
    | number
    | UserOnlineState
    | void;