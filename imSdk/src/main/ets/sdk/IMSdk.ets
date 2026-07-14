// src/main/ets/sdk/NativeSdk.ts
import imapi from 'libimsdk.so';
import { AdvancedGetMessageResult,
  BlackUserItem,
  ConversationItem,
  FriendApplicationItem,
  FriendshipInfo,
  FriendUserItem,
  GroupApplicationItem,
  GroupItem, GroupMemberItem, IMConfig,
  MessageItem,
  PublicUserItem,
  SearchedFriendsInfo,
  SearchMessageResult,
  SelfUserInfo,
  UserOnlineState} from './entity';
import { CbEvents, GroupAtType, LoginStatus, MessageReceiveOptType, Platform } from './enum';
import {
  AccessFriendApplicationParams,
  AccessGroupApplicationParams,
  AccessMessageParams,
  AccessToGroupParams,
  AddBlackParams,
  AddFriendParams,
  AdvancedMsgParams,
  AdvancedQuoteMsgParams,
  AtMsgParams,
  ChangeGroupMuteParams,
  ChangeInputStatesParams,
  CreateGroupParams,
  CustomMsgParams,
  FaceMessageParams,
  FileMsgParamsByURL,
  FindMessageParams,
  FriendApplicationListAsApplicantParams,
  FriendApplicationListAsRecipientParams,
  GetAdvancedHistoryMsgParams,
  GetGroupMemberByTimeParams,
  GetGroupMemberParams,
  GetHistoryMsgParams,
  GetInputstatesParams,
  GetOneConversationParams,
  GetSpecifiedFriendsParams,
  ImageMsgParamsByURL,
  InitAndLoginConfig,
  InsertGroupMsgParams,
  InsertSingleMsgParams,
  JoinGroupParams,
  LocationMsgParams,
  MergerMsgParams,
  CardElem,
  OffsetParams,
  PartialUserItem,
  PinFriendParams,
  QuoteMsgParams,
  RemarkFriendParams,
  SearchFriendParams,
  SearchGroupMemberParams,
  SearchGroupParams,
  SearchLocalParams,
  SendMsgParams,
  SetBurnDurationParams,
  SetConversationDraftParams,
  SetConversationExParams,
  SetConversationMsgDestructParams,
  SetConversationMsgDestructTimeParams,
  SetConversationParams,
  SetConversationPinParams,
  SetConversationPrivateStateParams,
  SetConversationRecvOptParams,
  SetFriendExParams,
  SetGroupMemberNickParams,
  SetGroupRoleParams,
  SetGroupVerificationParams,
  SetMemberPermissionParams,
  SetMessageLocalExParams,
  SoundMsgParamsByURL,
  SplitConversationParams,
  TransferGroupParams,
  UpdateFriendsParams,
  UpdateMemberInfoParams,
  VideoMsgParamsByURL,
  VideoMsgParamsByFullPath,
  SoundMsgParamsByFullPath,
  ChangeGroupMemberMuteParams,
  TypingUpdateParams,
  LogsParams,
  UploadFileParams,
  UploadLogsParams } from './params';
import { uuidV4 } from './Utils';
import { JSON } from '@kit.ArkTS';
import { Listener } from './listener';
import { Logger } from './Logger';
import { notificationManager } from '@kit.NotificationKit';

export function getSDK() { return IMSdk.getInstance(); }

export class IMSdk extends Listener{
  private static _instance: IMSdk | null = null;
  public static getInstance(): IMSdk {
    if (IMSdk._instance === null) {
      IMSdk._instance = new IMSdk();
    }
    return IMSdk._instance;
  }
  private constructor() {
    super(); // 必须调用父类构造函数
  }
  initSDK(config: IMConfig, operationID: string = uuidV4()): number {
    const state = imapi.initSdk(operationID, JSON.stringify(config))
    Logger.print(`startListener`)
    this.startListener();
    return state
  }
  unInitSDK(operationID: string = uuidV4()) {
    return imapi.unInitSdk(operationID)
  }
  async login(params: InitAndLoginConfig, operationID: string = uuidV4()): Promise<string> {
    return imapi.login(operationID, params.userID, params.token);
  }
  async logout(operationID: string = uuidV4()): Promise<string> {
    return imapi.logout(operationID);
  }
  async getAllConversationList(operationID: string = uuidV4()): Promise<ConversationItem[]> {
    const result = await imapi.getAllConversationList(operationID);
    return JSON.parse(result) as ConversationItem[];
  }
  async getOneConversation(params: GetOneConversationParams, operationID: string = uuidV4()): Promise<ConversationItem> {
    const result = await imapi.getOneConversation(operationID, params.sessionType, params.sourceID);
    return JSON.parse(result) as ConversationItem;
  }
  async getAdvancedHistoryMessageList(params: GetAdvancedHistoryMsgParams, operationID: string = uuidV4()): Promise<AdvancedGetMessageResult> {
    const result = await imapi.getAdvancedHistoryMessageList(operationID, JSON.stringify(params));
    return JSON.parse(result) as AdvancedGetMessageResult;
  }
  async getAdvancedHistoryMessageListReverse(params: GetAdvancedHistoryMsgParams, operationID: string = uuidV4()): Promise<AdvancedGetMessageResult> {
    const result = await imapi.getAdvancedHistoryMessageListReverse(operationID, JSON.stringify(params));
    return JSON.parse(result) as AdvancedGetMessageResult;
  }
  async getSpecifiedGroupsInfo(params: string[], operationID: string = uuidV4()): Promise<GroupItem[]> {
    const result = await imapi.getSpecifiedGroupsInfo(operationID, JSON.stringify(params));
    return JSON.parse(result) as GroupItem[];
  }
  async deleteConversationAndDeleteAllMsg(conversationID: string, operationID: string = uuidV4()): Promise<string> {
   return imapi.deleteConversationAndDeleteAllMsg(operationID, conversationID);
  }
  async markConversationMessageAsRead(conversationID: string, operationID: string = uuidV4()): Promise<string> {
    return imapi.markConversationMessageAsRead(operationID, conversationID);
  }
  async getGroupMemberList(params: GetGroupMemberParams, operationID: string = uuidV4()): Promise<GroupMemberItem[]> {
    const result = await  imapi.getGroupMemberList(operationID, params.groupID, params.filter, params.offset, params.count);
    return JSON.parse(result) as GroupMemberItem[];
  }
  async createTextMessage(text: string, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createTextMessage(operationID, text);
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createImageMessageByURL(params: ImageMsgParamsByURL, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createImageMessageByUrl(operationID,  params.sourcePath,
          JSON.stringify(params.sourcePicture),
          JSON.stringify(params.bigPicture),
          JSON.stringify(params.snapshotPicture));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createImageMessageByFile(params: ImageMsgParamsByURL, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createImageMessageByUrl(operationID,  params.sourcePath,
          JSON.stringify(params.sourcePicture),
          JSON.stringify(params.bigPicture),
          JSON.stringify(params.snapshotPicture));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createImageMessageFromFullPath(imageFullPath: string, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createImageMessageFromFullPath(operationID,  imageFullPath);
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createCustomMessage(params: CustomMsgParams, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createCustomMessage(operationID,  params.data, params.extension, params.description);
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createQuoteMessage(params: QuoteMsgParams, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createQuoteMessage(operationID,  params.text, JSON.stringify(params.message));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createAdvancedQuoteMessage(params: AdvancedQuoteMsgParams, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createAdvancedQuoteMessage(operationID,  params.text, JSON.stringify(params.message), JSON.stringify(params.messageEntityList));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createAdvancedTextMessage(params: AdvancedMsgParams, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createAdvancedTextMessage(operationID,  params.text, JSON.stringify(params.messageEntityList));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async sendMessage(params: SendMsgParams, operationID: string = uuidV4()): Promise<MessageItem> {
    const offlinePushInfo = params.offlinePushInfo ?? {
      title: 'You have a new message.',
      desc: '',
      ex: '',
      iOSPushSound: '+1',
      iOSBadgeCount: true,
    };
    const result = await imapi.sendMessage(operationID, JSON.stringify(params.message),
      params.recvID,
      params.groupID,
      JSON.stringify(offlinePushInfo),
      params.isOnlineOnly ?? false,
      (data: string) => {
        this.callback(CbEvents.OnMessageProgress, data);
      });
    return JSON.parse(result) as MessageItem;
  }
  async sendMessageNotOss(params: SendMsgParams, operationID: string = uuidV4()): Promise<MessageItem> {
    const offlinePushInfo = params.offlinePushInfo ?? {
      title: 'You have a new message.',
      desc: '',
      ex: '',
      iOSPushSound: '+1',
      iOSBadgeCount: true,
    };
    const result = await imapi.sendMessageNotOss(operationID, JSON.stringify(params.message),
      params.recvID,
      params.groupID,
      JSON.stringify(offlinePushInfo),
      params.isOnlineOnly ?? false,
      (data: string) => {
        this.callback(CbEvents.OnMessageProgress, data);
      });
    return JSON.parse(result) as MessageItem;
  }
  async setMessageLocalEx(params: SetMessageLocalExParams, operationID: string = uuidV4()): Promise<MessageItem> {
    const result = await imapi.setMessageLocalEx(operationID,  params.conversationID, params.clientMsgID, params.localEx);
    return JSON.parse(result) as MessageItem;
  }
  async getHistoryMessageListReverse(params: GetHistoryMsgParams, operationID: string = uuidV4()): Promise<AdvancedGetMessageResult> {
    const result = await imapi.getAdvancedHistoryMessageListReverse(operationID,  JSON.stringify(params));
    return JSON.parse(result) as AdvancedGetMessageResult;
  }
  async revokeMessage(params: AccessMessageParams, operationID: string = uuidV4()): Promise<string> {
    return imapi.revokeMessage(operationID, params.conversationID, params.clientMsgID);
  }
  async setConversation(params: SetConversationParams, operationID: string = uuidV4()): Promise<string> {
    return imapi.setConversation(operationID, params.conversationID, JSON.stringify(params));
  }
  async setConversationPrivateChat(params: SetConversationPrivateStateParams, operationID: string = uuidV4()): Promise<string> {
    return imapi.setConversation(operationID, params.conversationID, JSON.stringify({isPrivateChat: params.isPrivate}));
  }
  async setConversationBurnDuration(params: SetBurnDurationParams, operationID: string = uuidV4()): Promise<string> {
    return imapi.setConversation(operationID, params.conversationID, JSON.stringify({burnDuration: params.burnDuration}));
  }
  async getLoginStatus(operationID: string = uuidV4()): Promise<LoginStatus> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.getLoginStatus(operationID);
        resolve(result)
      } catch (e) {
        reject(e)
      }
    });
  }
  async setAppBackgroundStatus(operationID: string = uuidV4(), status: boolean): Promise<string> {
    return imapi.setAppBackgroundStatus(operationID, status);
  }
  async networkStatusChanged(operationID: string = uuidV4()): Promise<string> {
    return imapi.networkStatusChanged(operationID);
  }
  async getLoginUserID(operationID: string = uuidV4()): Promise<string> {
    return imapi.getLoginUser(operationID);
  }
  async getSelfUserInfo(operationID: string = uuidV4()): Promise<SelfUserInfo> {
    const result = await imapi.getSelfUserInfo(operationID);
    return JSON.parse(result) as SelfUserInfo;
  }
  async getUsersInfo(data: string[], operationID: string = uuidV4()): Promise<PublicUserItem> {
    const result = await imapi.getUsersInfo(operationID,  JSON.stringify(data));
    return JSON.parse(result) as PublicUserItem;
  }
  async setSelfInfoEx(data: PartialUserItem, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setSelfInfo(operationID,  JSON.stringify(data));
    return result
  }
  async setSelfInfo(data: PartialUserItem, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setSelfInfo(operationID,  JSON.stringify(data));
    return result
  }
  async createTextAtMessage(data: AtMsgParams, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createTextAtMessage(operationID, data.text, JSON.stringify(data.atUserIDList), JSON.stringify(data.atUsersInfo), JSON.stringify(data.message) ?? '');
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createSoundMessageByURL(data: SoundMsgParamsByURL, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createSoundMessageByUrl(operationID, JSON.stringify(data));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createSoundMessageByFile(data: SoundMsgParamsByURL, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createSoundMessageByUrl(operationID, JSON.stringify(data));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createSoundMessageFromFullPath(data:SoundMsgParamsByFullPath,operationID: string = uuidV4()): Promise<MessageItem>{
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createSoundMessageFromFullPath(operationID,data.soundPath,data.duration);
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createVideoMessageByURL(data: VideoMsgParamsByURL, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createVideoMessageByUrl(operationID, JSON.stringify(data));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createVideoMessageByFile(data: VideoMsgParamsByURL, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createVideoMessageByUrl(operationID, JSON.stringify(data));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createVideoMessageFromFullPath(data:VideoMsgParamsByFullPath,operationID: string = uuidV4()): Promise<MessageItem>{
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createVideoMessageFromFullPath(operationID,data.videoFullPath,data.videoType,data.duration,data.snapshotFullPath);
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createFileMessageByURL(data: FileMsgParamsByURL, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createFileMessageByUrl(operationID, JSON.stringify(data));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createFileMessageByFile(data: FileMsgParamsByURL, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createFileMessageByUrl(operationID, JSON.stringify(data));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createMergerMessage(data: MergerMsgParams, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createMergerMessage(operationID, JSON.stringify(data.messageList), data.title, JSON.stringify(data.summaryList));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createForwardMessage(data: MessageItem, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createForwardMessage(operationID, JSON.stringify(data));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createFaceMessage(data: FaceMessageParams, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createFaceMessage(operationID, data.index, data.data);
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createLocationMessage(data: LocationMsgParams, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createLocationMessage(operationID, data.description, data.longitude, data.latitude);
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async createCardMessage(data: CardElem, operationID: string = uuidV4()): Promise<MessageItem> {
    return new Promise((resolve, reject) => {
      try {
        const result = imapi.createCardMessage(operationID, JSON.stringify(data));
        resolve(JSON.parse(result) as MessageItem)
      } catch (e) {
        reject(e)
      }
    });
  }
  async deleteMessageFromLocalStorage(data: AccessMessageParams, operationID: string = uuidV4()): Promise<string> {
    return imapi.deleteMessageFromLocalStorage(operationID, data.conversationID, data.clientMsgID);
  }
  async deleteMessage(data: AccessMessageParams, operationID: string = uuidV4()): Promise<string> {
    return imapi.deleteMessage(operationID, data.conversationID, data.clientMsgID);
  }
  async deleteAllMsgFromLocal(operationID: string = uuidV4()): Promise<string> {
    return imapi.deleteAllMsgFromLocal(operationID);
  }
  async deleteAllMsgFromLocalAndSvr(operationID: string = uuidV4()): Promise<string> {
    return imapi.deleteAllMsgFromLocalAndSvr(operationID);
  }
  async insertSingleMessageToLocalStorage( data: InsertSingleMsgParams,  operationID: string = uuidV4()): Promise<string> {
    return imapi.insertSingleMessageToLocalStorage(operationID, JSON.stringify(data.message), data.recvID, data.sendID);
  }
  async insertGroupMessageToLocalStorage( data: InsertGroupMsgParams,  operationID: string = uuidV4()): Promise<string> {
    return imapi.insertGroupMessageToLocalStorage(operationID, JSON.stringify(data.message), data.groupID, data.sendID);
  }
  async changeInputStates( data: ChangeInputStatesParams,  operationID: string = uuidV4()): Promise<string> {
    return imapi.changeInputStates(operationID, data.conversationID, data.focus);
  }
  async getInputStates( data: GetInputstatesParams,  operationID: string = uuidV4()): Promise<Platform[]> {
    const result = await imapi.getInputStates(operationID, data.conversationID, data.userID);
    return JSON.parse(result) as Platform[];
  }
  async clearConversationAndDeleteAllMsg( data: string,  operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.clearConversationAndDeleteAllMsg(operationID, data);
    return result;
  }
  async hideConversation( data: string,  operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.hideConversation(operationID, data);
    return result;
  }
  async getConversationListSplit( data: SplitConversationParams,  operationID: string = uuidV4()): Promise<ConversationItem[]> {
    const result = await imapi.getConversationListSplit(operationID, data.offset, data.count);
    return JSON.parse(result) as ConversationItem[];
  }
  async setConversationEx( data: SetConversationExParams,  operationID: string = uuidV4()): Promise<ConversationItem[]> {
    const result = await imapi.setConversation(operationID, data.conversationID, JSON.stringify({ ex: data.ex}));
    return JSON.parse(result) as ConversationItem[];
  }
  async getConversationIDBySessionType( data: GetOneConversationParams,  operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.getConversationIdBySessionType(operationID, data.sourceID, data.sessionType);
    return result;
  }
  async getMultipleConversation( data: string[],  operationID: string = uuidV4()): Promise<ConversationItem[]> {
    const result = await imapi.getMultipleConversation(operationID, JSON.stringify(data));
    return JSON.parse(result) as ConversationItem[];
  }
  async deleteConversation( conversationID: string,  operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.deleteConversationAndDeleteAllMsg(operationID, conversationID);
    return result;
  }
  async setConversationDraft( data: SetConversationDraftParams,  operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setConversationDraft(operationID, data.conversationID, data.draftText);
    return result;
  }
  async pinConversation( data: SetConversationPinParams,  operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setConversation(operationID, data.conversationID, JSON.stringify({ isPinned: data.isPinned}));
    return result;
  }
  async getTotalUnreadMsgCount(operationID: string = uuidV4()): Promise<number> {
    const result = await imapi.getTotalUnreadMsgCount(operationID);
    return Number(result);
  }
  async setConversationRecvMessageOpt( data: SetConversationRecvOptParams,  operationID: string = uuidV4()): Promise<ConversationItem[]> {
    const result = await imapi.setConversation(operationID, data.conversationID, JSON.stringify({ recvMsgOpt: data.opt}));
    return JSON.parse(result) as ConversationItem[];
  }
  async searchLocalMessages( data: SearchLocalParams,  operationID: string = uuidV4()): Promise<SearchMessageResult> {
    const result = await imapi.searchLocalMessages(operationID, JSON.stringify(data));
    return JSON.parse(result) as SearchMessageResult;
  }
  async addFriend( data: AddFriendParams,  operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.addFriend(operationID, JSON.stringify(data));
    return result;
  }
  async searchFriends( data: SearchFriendParams,  operationID: string = uuidV4()): Promise<SearchedFriendsInfo[]> {
    const result = await imapi.searchFriends(operationID, JSON.stringify(data));
    return JSON.parse(result) as SearchedFriendsInfo[];
  }
  async getSpecifiedFriendsInfo(data: GetSpecifiedFriendsParams,  operationID: string = uuidV4()): Promise<FriendUserItem[]> {
    const result = await imapi.getSpecifiedFriendsInfo(operationID, JSON.stringify(data.friendUserIDList), data.filterBlack);
    return JSON.parse(result) as SearchedFriendsInfo[];
  }
  async getFriendApplicationListAsRecipient(data: FriendApplicationListAsRecipientParams, operationID: string = uuidV4()): Promise<FriendApplicationItem[]> {
    const result = await imapi.getFriendApplicationListAsRecipient(operationID, JSON.stringify(data));
    return JSON.parse(result) as FriendApplicationItem[];
  }
  async getFriendApplicationListAsApplicant(data: FriendApplicationListAsApplicantParams, operationID: string = uuidV4()): Promise<FriendApplicationItem[]> {
    const result = await imapi.getFriendApplicationListAsApplicant(operationID, JSON.stringify(data));
    return JSON.parse(result) as FriendApplicationItem[];
  }
  async getFriendList(filterBlack = false, operationID: string = uuidV4()): Promise<FriendUserItem[]> {
    const result = await imapi.getFriendList(operationID, filterBlack);
    return JSON.parse(result) as FriendUserItem[];
  }
  async getFriendListPage(offset: number, count: number, filterBlack = false, operationID: string = uuidV4()): Promise<FriendUserItem[]> {
    const result = await imapi.getFriendListPage(operationID, offset, count, filterBlack);
    return JSON.parse(result) as FriendUserItem[];
  }
  async updateFriends(data: UpdateFriendsParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.updateFriends(operationID, JSON.stringify(data));
    return result;
  }
  async setFriendRemark(data: RemarkFriendParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.updateFriends(operationID, JSON.stringify({ friendUserIDs: [data.toUserID], remark: data.remark, }));
    return result;
  }
  async pinFriends(data: PinFriendParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.updateFriends(operationID, JSON.stringify({friendUserIDs: data.toUserIDs,isPinned: data.isPinned}));
    return result;
  }
  async setFriendsEx(data: SetFriendExParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.updateFriends(operationID, JSON.stringify({ friendUserIDs: data.toUserIDs, ex: data.ex}));
    return result;
  }
  async checkFriend(data: string[], operationID: string = uuidV4()): Promise<FriendshipInfo[]> {
    const result = await imapi.checkFriend(operationID, JSON.stringify(data));
    return JSON.parse(result) as FriendshipInfo[];
  }
  async acceptFriendApplication(data: AccessFriendApplicationParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.acceptFriendApplication(operationID, JSON.stringify(data));
    return result;
  }
  async refuseFriendApplication(data: AccessFriendApplicationParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.refuseFriendApplication(operationID, JSON.stringify(data));
    return result;
  }
  async getFriendApplicationUnhandledCount(req: string, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.getFriendApplicationUnhandledCount(operationID, req);
    return result;
  }
  async deleteFriend(data: string, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.deleteFriend(operationID, JSON.stringify(data));
    return result;
  }
  async addBlack(data: AddBlackParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.addBlack(operationID, data.toUserID, data.ex ?? '');
    return result;
  }
  async removeBlack(removeUserID: string, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.removeBlack(operationID, removeUserID);
    return result;
  }
  async getBlackList(operationID: string = uuidV4()): Promise<BlackUserItem[]> {
    const result = await imapi.getBlackList(operationID);
    return JSON.parse(result) as BlackUserItem[];
  }
  async inviteUserToGroup(data: AccessToGroupParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.inviteUserToGroup(operationID, data.groupID, data.reason, JSON.stringify(data.userIDList));
    return result;
  }
  async kickGroupMember(data: AccessToGroupParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.kickGroupMember(operationID, data.groupID, data.reason, JSON.stringify(data.userIDList));
    return result;
  }
  async isJoinGroup(groupID: string, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.isJoinGroup(operationID, groupID);
    return result;
  }
  async getSpecifiedGroupMembersInfo(data: AccessToGroupParams, operationID: string = uuidV4()): Promise<GroupMemberItem[]> {
    const result = await imapi.getSpecifiedGroupMembersInfo(operationID, data.groupID, JSON.stringify(data.userIDList));
    return JSON.parse(result) as GroupMemberItem[];
  }
  async getUsersInGroup(data: AccessToGroupParams, operationID: string = uuidV4()): Promise<string[]> {
    const result = await imapi.getUsersInGroup(operationID, data.groupID, JSON.stringify(data.userIDList));
    return JSON.parse(result) as string[];
  }
  async getGroupMemberListByJoinTimeFilter(data: GetGroupMemberByTimeParams, operationID: string = uuidV4()): Promise<GroupMemberItem[]> {
    const result = await imapi.getGroupMemberListByJoinTimeFilter(operationID, data.groupID,
      data.offset,
      data.count,
      data.joinTimeBegin,
      data.joinTimeEnd,
      JSON.stringify(data.filterUserIDList));
    return JSON.parse(result) as GroupMemberItem[];
  }
  async searchGroupMembers(data: SearchGroupMemberParams, operationID: string = uuidV4()): Promise<GroupMemberItem[]> {
    const result = await imapi.searchGroupMembers(operationID, JSON.stringify(data));
    return JSON.parse(result) as GroupMemberItem[];
  }
  async setGroupApplyMemberFriend(data: SetMemberPermissionParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.searchGroupMembers(operationID, JSON.stringify(data));
    return result;
  }
  async setGroupLookMemberInfo(data: SetMemberPermissionParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setGroupInfo(operationID, JSON.stringify({
      groupID: data.groupID,
      lookMemberInfo: data.rule,
    }));
    return result;
  }
  async getJoinedGroupList(operationID: string = uuidV4()): Promise<GroupItem[]> {
    const result = await imapi.getJoinedGroupList(operationID);
    return JSON.parse(result) as GroupItem[];
  }
  async getJoinedGroupListPage(data: OffsetParams, operationID: string = uuidV4()): Promise<GroupItem[]> {
    const result = await imapi.getJoinedGroupListPage(operationID, data.offset, data.count);
    return JSON.parse(result) as GroupItem[];
  }
  async createGroup(data: CreateGroupParams, operationID: string = uuidV4()): Promise<GroupItem> {
    const result = await imapi.createGroup(operationID, JSON.stringify(data));
    return JSON.parse(result) as GroupItem;
  }
  async setGroupInfo(data: GroupItem, operationID: string = uuidV4()): Promise<GroupItem> {
    const result = await imapi.setGroupInfo(operationID, JSON.stringify(data));
    return JSON.parse(result) as GroupItem;
  }
  async setGroupMemberNickname(data: SetGroupMemberNickParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setGroupMemberInfo(operationID, JSON.stringify({
      groupID: data.groupID,
      userID: data.userID,
      nickname: data.groupMemberNickname,
    }));
    return result;
  }
  async setGroupMemberInfo(data: UpdateMemberInfoParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setGroupMemberInfo(operationID, JSON.stringify(data));
    return result;
  }
  async joinGroup(data: JoinGroupParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.joinGroup(operationID, data.groupID,
      data.reqMsg,
      data.joinSource,
      data.ex ?? '');
    return result;
  }
  async searchGroups(data: SearchGroupParams, operationID: string = uuidV4()): Promise<GroupItem[]> {
    const result = await imapi.searchGroups(operationID, JSON.stringify(data));
    return JSON.parse(result) as GroupItem[];
  }
  async quitGroup(data: string, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.quitGroup(operationID, data);
    return result;
  }
  async dismissGroup(data: string, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.dismissGroup(operationID, data);
    return result;
  }
  async changeGroupMute(data: ChangeGroupMuteParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.changeGroupMute(operationID, data.groupID, data.isMute);
    return result;
  }
  async changeGroupMemberMute(data: ChangeGroupMemberMuteParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.changeGroupMemberMute(operationID, data.groupID, data.userID, data.mutedSeconds);
    return result;
  }
  async typingStatusUpdate(data: TypingUpdateParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.typingStatusUpdate(operationID, data.recvID, data.msgTip);
    return result;
  }

  async transferGroupOwner(data: TransferGroupParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.transferGroupOwner(operationID, data.groupID, data.newOwnerUserID);
    return result;
  }
  async getGroupApplicationListAsApplicant(operationID: string = uuidV4()): Promise<GroupApplicationItem[]> {
    const result = await imapi.getGroupApplicationListAsApplicant(operationID, "");
    return JSON.parse(result) as GroupApplicationItem[];
  }
  async getGroupApplicationListAsRecipient(operationID: string = uuidV4()): Promise<GroupApplicationItem[]> {
    const result = await imapi.getGroupApplicationListAsRecipient(operationID, "");
    return JSON.parse(result) as GroupApplicationItem[];
  }
  async acceptGroupApplication(data: AccessGroupApplicationParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.acceptGroupApplication(operationID, data.groupID, data.fromUserID, data.handleMsg);
    return result;
  }
  async refuseGroupApplication(data: AccessGroupApplicationParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.refuseGroupApplication(operationID, data.groupID, data.fromUserID, data.handleMsg);
    return result;
  }
  async resetConversationGroupAtType(data: string, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setConversation(operationID,  data, JSON.stringify({
      groupAtType: GroupAtType.AtNormal,
    }));
    return result;
  }
  async setGroupMemberRoleLevel(data: SetGroupRoleParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setGroupMemberInfo(operationID,  JSON.stringify({
      groupID: data.groupID,
      userID: data.userID,
      roleLevel: data.roleLevel,
    }));
    return result;
  }
  async setGroupVerification(data: SetGroupVerificationParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setGroupMemberInfo(operationID, JSON.stringify({
      groupID: data.groupID,
      needVerification: data.verification,
    }));
    return result;
  }
  async getGroupMemberOwnerAndAdmin(data: string, operationID: string = uuidV4()): Promise<GroupMemberItem[]> {
    const result = await imapi.getGroupMemberOwnerAndAdmin(operationID, data);
    return JSON.parse(result) as GroupMemberItem[];
  }
  async setGlobalRecvMessageOpt(opt: MessageReceiveOptType, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setSelfInfo(operationID, JSON.stringify({ globalRecvMsgOpt: opt }));
    return result;
  }
  async findMessageList(data: FindMessageParams[], operationID: string = uuidV4()): Promise<SearchMessageResult> {
    const result = await imapi.findMessageList(operationID, JSON.stringify(data));
    return JSON.parse(result) as SearchMessageResult;
  }
  async subscribeUsersStatus(data: string[], operationID: string = uuidV4()): Promise<UserOnlineState[]> {
    const result = await imapi.subscribeUsersStatus(operationID, JSON.stringify(data));
    return JSON.parse(result) as UserOnlineState[];
  }
  async unsubscribeUsersStatus(data: string[], operationID: string = uuidV4()): Promise<UserOnlineState[]> {
    const result = await imapi.unSubscribeUsersStatus(operationID, JSON.stringify(data));
    return JSON.parse(result) as UserOnlineState[];
  }
  async getUserStatus(data: string[], operationID: string = uuidV4()): Promise<UserOnlineState[]> {
    const result = await imapi.getUserStatus(operationID, JSON.stringify(data));
    return JSON.parse(result) as UserOnlineState[];
  }
  async getSubscribeUsersStatus(operationID: string = uuidV4()): Promise<UserOnlineState[]> {
    const result = await imapi.getSubscribeUsersStatus(operationID);
    return JSON.parse(result) as UserOnlineState[];
  }
  async setConversationIsMsgDestruct(data: SetConversationMsgDestructParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setConversation(operationID, data.conversationID, JSON.stringify({ isMsgDestruct: data.isMsgDestruct }));
    return result;
  }
  async setConversationMsgDestructTime(data: SetConversationMsgDestructTimeParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.setConversation(operationID, data.conversationID, JSON.stringify({ msgDestructTime: data.msgDestructTime }));
    return result;
  }
  async setAppBadge(appUnreadCount: number, operationID: string = uuidV4()): Promise<boolean> {
    try {
      await notificationManager.setBadgeNumber(appUnreadCount);
      return true;
    } catch (error) {
      return false;
    }
  }

  async uploadFile(data: UploadFileParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.uploadFile(operationID, JSON.stringify(data), (data: string) => {
      Logger.print(`uploadFile progress: ${data}`);
    });
    return result;
  }

  async uploadLogs(data: UploadLogsParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.uploadLogs(operationID, data.line, data.ex ?? '', (data: string) => {
      Logger.print(`uploadLogs progress: ${data}`);
    });
    return result;
  }

  async logs(data: LogsParams, operationID: string = uuidV4()): Promise<string> {
    const result = await imapi.logs(operationID, data.logLevel, data.file, data.line, data.msgs, data.err, JSON.stringify(data.keyAndValue));
    return result;
  }

}