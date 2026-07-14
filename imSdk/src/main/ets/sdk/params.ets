import {
  MessageEntity,
  OfflinePush,
  PicBaseInfo,
  AtUsersInfoItem,
  MessageItem,
  SelfUserInfo,
  RtcInvite,
  GroupItem,
} from './entity';
import {
  AllowType,
  GroupJoinSource,
  GroupVerificationType,
  MessageType,
  MessageReceiveOptType,
  GroupMemberRole,
  GroupMemberFilter,
  LogLevel,
  GroupMessageReaderFilter,
  GroupAtType,
} from './enum';

export interface WasmPathConfig {
  coreWasmPath?: string;
  sqlWasmPath?: string;
  debug?: boolean;
};

export interface InitAndLoginConfig {
  userID: string;
  token: string;
  platformID: number;
  apiAddr: string;
  wsAddr: string;
  logLevel?: LogLevel;
  isLogStandardOutput?: boolean;
  isExternalExtensions?: boolean;
  tryParse?: boolean;
};

export interface GetOneConversationParams {
  sourceID: string;
  sessionType: number;
};
export interface GetAdvancedHistoryMsgParams {
  userID?: string;
  groupID?: string;
  lastMinSeq: number;
  count: number;
  startClientMsgID: string;
  conversationID: string;
};
export interface GetHistoryMsgParams {
  userID: string;
  groupID: string;
  count: number;
  startClientMsgID: string;
  conversationID?: string;
};
export interface SendGroupReadReceiptParams {
  conversationID: string;
  clientMsgIDList: string[];
};
export interface GetGroupMessageReaderParams {
  conversationID: string;
  clientMsgID: string;
  filter: GroupMessageReaderFilter;
  offset: number;
  count: number;
};
export interface GetGroupMemberParams {
  groupID: string;
  filter: GroupMemberFilter;
  offset: number;
  count: number;
};
export interface SendMsgParams {
  recvID: string;
  groupID: string;
  offlinePushInfo?: OfflinePush;
  message: MessageItem;
  isOnlineOnly?: boolean;
};
export interface SetMessageLocalExParams {
  conversationID: string;
  clientMsgID: string;
  localEx: string;
};
export interface ImageMsgParamsByURL {
  sourcePicture: PicBaseInfo;
  bigPicture: PicBaseInfo;
  snapshotPicture: PicBaseInfo;
  sourcePath: string;
};
export interface VideoMsgParamsByURL {
  videoPath: string;
  duration: number;
  videoType: string;
  snapshotPath: string;
  videoUUID: string;
  videoUrl: string;
  videoSize: number;
  snapshotUUID: string;
  snapshotSize: number;
  snapshotUrl: string;
  snapshotWidth: number;
  snapshotHeight: number;
  snapShotType?: string;
};
export interface VideoMsgParamsByFullPath {
  videoFullPath: string;
  videoType: string;
  duration: number;
  snapshotFullPath: string;
};
export interface CustomMsgParams {
  data: string;
  extension: string;
  description: string;
};
export interface QuoteMsgParams {
  text: string;
  message: MessageItem;
};
export interface AdvancedQuoteMsgParams {
  text: string;
  message: MessageItem;
  messageEntityList?: MessageEntity[];
};
export interface AdvancedMsgParams {
  text: string;
  messageEntityList?: MessageEntity[];
};
export interface SetConversationParams {
  conversationID: string;
  recvMsgOpt?: MessageReceiveOptType;
  groupAtType?: GroupAtType;
  burnDuration?: number;
  msgDestructTime?: number;
  isPinned?: boolean;
  isPrivateChat?: boolean;
  isMsgDestruct?: boolean;
  ex?: string;
};
export interface SetConversationPrivateStateParams {
  conversationID: string;
  isPrivate: boolean;
};
export interface SplitConversationParams {
  offset: number;
  count: number;
};
export interface SetConversationDraftParams {
  conversationID: string;
  draftText: string;
};
export interface SetConversationPinParams {
  conversationID: string;
  isPinned: boolean;
};
export interface JoinGroupParams {
  groupID: string;
  reqMsg: string;
  joinSource: GroupJoinSource;
  ex?: string;
};
export interface SearchGroupParams {
  keywordList: string[];
  isSearchGroupID: boolean;
  isSearchGroupName: boolean;
};
export interface ChangeGroupMuteParams {
  groupID: string;
  isMute: boolean;
};
export interface ChangeGroupMemberMuteParams {
  groupID: string;
  userID: string;
  mutedSeconds: number;
};
export interface TransferGroupParams {
  groupID: string;
  newOwnerUserID: string;
};
export interface AccessGroupApplicationParams {
  groupID: string;
  fromUserID: string;
  handleMsg: string;
};
export interface SetGroupRoleParams {
  groupID: string;
  userID: string;
  roleLevel: GroupMemberRole;
};
export interface SetGroupVerificationParams {
  verification: GroupVerificationType;
  groupID: string;
};
export interface SetBurnDurationParams {
  conversationID: string;
  burnDuration: number;
};
export interface AtMsgParams {
  text: string;
  atUserIDList: string[];
  atUsersInfo?: AtUsersInfoItem[];
  message?: MessageItem;
};
export interface SoundMsgParamsByURL {
  uuid: string;
  soundPath: string;
  sourceUrl: string;
  dataSize: number;
  duration: number;
  soundType?: string;
};
export interface FileMsgParamsByURL {
  filePath: string;
  fileName: string;
  uuid: string;
  sourceUrl: string;
  fileSize: number;
  fileType?: string;
};
export interface FileMsgParamsByFullPath {
  fileFullPath: string;
  fileName: string;
};
export interface SoundMsgParamsByFullPath {
  soundPath: string;
  duration: number;
};
export interface MergerMsgParams {
  messageList: MessageItem[];
  title: string;
  summaryList: string[];
};
export interface FaceMessageParams {
  index: number;
  data: string;
};
export interface LocationMsgParams {
  description: string;
  longitude: number;
  latitude: number;
};
export interface CardElem{
  userID: string;
  nickname: string;
  faceURL: string;
  ex: string;
}
export interface InsertSingleMsgParams {
  message: MessageItem;
  recvID: string;
  sendID: string;
};
export interface InsertGroupMsgParams {
  message: MessageItem;
  groupID: string;
  sendID: string;
};
export interface AccessMessageParams {
  conversationID: string;
  clientMsgID: string;
};
export interface TypingUpdateParams {
  recvID: string;
  msgTip: string;
};
export interface ChangeInputStatesParams {
  conversationID: string;
  focus: boolean;
};
export interface GetInputstatesParams {
  conversationID: string;
  userID: string;
};
export interface SetConversationExParams {
  conversationID: string;
  ex: string;
};
export interface SetConversationRecvOptParams {
  conversationID: string;
  opt: MessageReceiveOptType;
};
export interface SearchLocalParams {
  conversationID: string;
  keywordList: string[];
  keywordListMatchType?: number;
  senderUserIDList?: string[];
  messageTypeList?: MessageType[];
  searchTimePosition?: number;
  searchTimePeriod?: number;
  pageIndex?: number;
  count?: number;
};
export interface AddFriendParams {
  toUserID: string;
  reqMsg: string;
};
export interface SearchFriendParams {
  keywordList: string[];
  isSearchUserID: boolean;
  isSearchNickname: boolean;
  isSearchRemark: boolean;
};
export interface GetSpecifiedFriendsParams {
  friendUserIDList: string[];
  filterBlack?: boolean;
};
export interface UpdateFriendsParams {
  friendUserIDs: string[];
  isPinned?: boolean;
  remark?: string;
  ex?: string;
};
export interface FriendApplicationListAsRecipientParams {
  handleResults: number[];
  offset: number;
  count: number;
};
export interface FriendApplicationListAsApplicantParams {
  offset: number;
  count: number;
};
export interface RemarkFriendParams {
  toUserID: string;
  remark: string;
};
export interface PinFriendParams {
  toUserIDs: string[];
  isPinned: boolean;
};
export interface SetFriendExParams {
  toUserIDs: string[];
  ex: string;
};
export interface AccessFriendApplicationParams {
  toUserID: string;
  handleMsg: string;
};
export interface AddBlackParams {
  toUserID: string;
  ex?: string;
};
export interface AccessToGroupParams {
  groupID: string;
  reason: string;
  userIDList: string[];
};
export interface GetGroupMemberByTimeParams {
  groupID: string;
  filterUserIDList: string[];
  offset: number;
  count: number;
  joinTimeBegin: number;
  joinTimeEnd: number;
};
export interface SearchGroupMemberParams {
  groupID: string;
  keywordList: string[];
  isSearchUserID: boolean;
  isSearchMemberNickname: boolean;
  offset: number;
  count: number;
};
export interface SetMemberPermissionParams {
  rule: AllowType;
  groupID: string;
};
export interface OffsetParams {
  offset: number;
  count: number;
};
export interface CreateGroupParams {
  memberUserIDs: string[];
  groupInfo: Partial<GroupItem>;
  adminUserIDs?: string[];
  ownerUserID?: string;
};
export interface SetGroupMemberNickParams {
  groupID: string;
  userID: string;
  groupMemberNickname: string;
};
export interface UpdateMemberInfoParams {
  groupID: string;
  userID: string;
  nickname?: string;
  faceURL?: string;
  roleLevel?: GroupMemberRole;
  ex?: string;
};
export interface FindMessageParams {
  conversationID: string;
  clientMsgIDList: string[];
};
export interface UploadFileParams {
  name: string;
  contentType: string;
  uuid: string;
  filepath?: string;
  cause?: string;
  token:string;
};
export interface PartialUserItem {
  createTime: number;
  ex: string;
  faceURL: string;
  nickname: string;
  userID: string;
  globalRecvMsgOpt: MessageReceiveOptType;
};
export interface SignalingInviteParams {
  invitation: RtcInvite;
  offlinePushInfo?: OfflinePush;
};
export interface RtcActionParams {
  opUserID: string;
  invitation: RtcInvite;
};
export interface CustomSignalParams {
  roomID: string;
  customInfo: string;
};

export interface SetConversationMsgDestructParams {
  conversationID: string;
  isMsgDestruct: boolean;
};

export interface SetConversationMsgDestructTimeParams {
  conversationID: string;
  msgDestructTime: number;
};

export interface UploadLogsParams {
  line: number;
  ex?: string;
};

export interface LogsParams {
  logLevel: number;
  file: string;
  line: number;
  msgs: string;
  err: string;
  keyAndValue: string[];
};
