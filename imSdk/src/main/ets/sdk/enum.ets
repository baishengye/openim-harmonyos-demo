export enum MessageReceiveOptType {
  Normal = 0,
  NotReceive = 1,
  NotNotify = 2,
}
export enum AllowType {
  Allowed = 0,
  NotAllowed = 1,
}
export enum GroupType {
  Group = 2,
  WorkingGroup = 2,
}
export enum GroupJoinSource {
  Invitation = 2,
  Search = 3,
  QrCode = 4,
}
export enum GroupMemberRole {
  Normal = 20,
  Admin = 60,
  Owner = 100,
}
export enum GroupVerificationType {
  ApplyNeedInviteNot = 0,
  AllNeed = 1,
  AllNot = 2,
}
export enum MessageStatus {
  Sending = 1,
  Succeed = 2,
  Failed = 3,
}
export enum Platform {
  iOS = 1,
  Android = 2,
  Windows = 3,
  MacOSX = 4,
  Web = 5,
  Linux = 7,
  AndroidPad = 8,
  iPad = 9,
  Admin = 10,
  HarmonyOS = 11
}
export enum LogLevel {
  Verbose = 6,
  Debug = 5,
  Info = 4,
  Warn = 3,
  Error = 2,
  Fatal = 1,
  Panic = 0,
}
export enum ApplicationHandleResult {
  Unprocessed = 0,
  Agree = 1,
  Reject = -1,
}
export enum MessageType {
  TextMessage = 101,
  PictureMessage = 102,
  VoiceMessage = 103,
  VideoMessage = 104,
  FileMessage = 105,
  AtTextMessage = 106,
  MergeMessage = 107,
  CardMessage = 108,
  LocationMessage = 109,
  CustomMessage = 110,
  TypingMessage = 113,
  QuoteMessage = 114,
  FaceMessage = 115,
  FriendAdded = 1201,
  OANotification = 1400,
  GroupCreated = 1501,
  GroupInfoUpdated = 1502,
  MemberQuit = 1504,
  GroupOwnerTransferred = 1507,
  MemberKicked = 1508,
  MemberInvited = 1509,
  MemberEnter = 1510,
  GroupDismissed = 1511,
  GroupMemberMuted = 1512,
  GroupMemberCancelMuted = 1513,
  GroupMuted = 1514,
  GroupCancelMuted = 1515,
  GroupAnnouncementUpdated = 1519,
  GroupNameUpdated = 1520,
  BurnMessageChange = 1701,
  RevokeMessage = 2101,
}
export enum SessionType {
  Single = 1,
  Group = 3,
  WorkingGroup = 3,
  Notification = 4,
}
export enum GroupStatus {
  Normal = 0,
  Banned = 1,
  Dismissed = 2,
  Muted = 3,
}
export enum GroupAtType {
  AtNormal = 0,
  AtMe = 1,
  AtAll = 2,
  AtAllAtMe = 3,
  AtGroupNotice = 4,
}
export enum GroupMemberFilter {
  All = 0,
  Owner = 1,
  Admin = 2,
  Normal = 3,
  AdminAndNormal = 4,
  AdminAndOwner = 5,
}
export enum Relationship {
  isBlack = 0,
  isFriend = 1,
}
export enum LoginStatus {
  Logout = 1,
  Logging = 2,
  Logged = 3,
}
export enum OnlineState {
  Online = 1,
  Offline = 0,
}
export enum GroupMessageReaderFilter {
  Read = 0,
  UnRead = 1,
}

// CbEvents.ts
export enum CbEvents {
  OnConnecting = 0,
  OnConnectSuccess = 1,
  OnConnectFailed = 2,
  OnKickedOffline = 3,
  OnUserTokenExpired = 4,
  OnJoinedGroupAdded = 5,
  OnJoinedGroupDeleted = 6,
  OnGroupMemberAdded = 7,
  OnGroupMemberDeleted = 8,
  OnGroupApplicationAdded = 9,
  OnGroupApplicationDeleted = 10,
  OnGroupInfoChanged = 11,
  OnGroupDismissed = 12,
  OnGroupMemberInfoChanged = 13,
  OnGroupApplicationAccepted = 14,
  OnGroupApplicationRejected = 15,
  OnFriendApplicationAdded = 16,
  OnFriendApplicationDeleted = 17,
  OnFriendApplicationAccepted = 18,
  OnFriendApplicationRejected = 19,
  OnFriendAdded = 20,
  OnFriendDeleted = 21,
  OnFriendInfoChanged = 22,
  OnBlackAdded = 23,
  OnBlackDeleted = 24,
  OnSyncServerStart = 25,
  OnSyncServerFinish = 26,
  OnSyncServerProgress = 27,
  OnSyncServerFailed = 28,
  OnNewConversation = 29,
  OnConversationChanged = 30,
  OnTotalUnreadMessageCountChanged = 31,
  OnRecvNewMessage = 32,
  OnRecvC2CReadReceipt = 33,
  OnRecvGroupReadReceipt = 34,
  OnNewRecvMessageRevoked = 35,
  OnRecvMessageExtensionsChanged = 36,
  OnRecvMessageExtensionsDeleted = 37,
  OnRecvMessageExtensionsAdded = 38,
  OnRecvOfflineNewMessage = 39,
  OnMsgDeleted = 40,
  OnRecvNewMessages = 41,
  OnRecvOfflineNewMessages = 42,
  OnSelfInfoUpdated = 43,
  OnUserStatusChanged = 44,
  OnRecvCustomBusinessMessage = 45,
  OnMessageKVInfoChanged = 46,
  OnOpen = 47,
  OnPartSize = 48,
  OnHashPartProgress = 49,
  OnHashPartComplete = 50,
  OnUploadID = 51,
  OnUploadPartComplete = 52,
  OnUploadComplete = 53,
  OnComplete = 54,
  OnConversationUserInputStatusChanged = 55,
  OnRecvOnlineOnlyMessage = 56,
  OnUserTokenInvalid = 57,
  OnProgress = 58
}