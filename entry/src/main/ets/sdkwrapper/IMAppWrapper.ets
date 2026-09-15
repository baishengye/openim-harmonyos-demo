/** Promise 风格的 OpenIM SDK 门面，页面层不直接处理原生回调。 */
import {
  getSDK, OpenIMClient, InitConfig, Message, ConversationInfo, FriendInfo,
  FriendApplication, GroupInfo, GroupApplication, UserInfo, UsersOnlineStatus,
  SendMsgCallBack, ConnListener, MsgListener, ConvListener, GroupListener,
  FriendListener, UserListener, PromiseBaseCallback, PromiseCompletionCallback,
  FriendshipInfo, SearchResult, buildOperationID
} from 'imsdk';

export class ConversationInputStatusResult {
  conversationID: string = '';
  userID: string = '';
  platformIDs: number[] = [];
}

export class HistoryMessageResult {
  messageList: Message[] = [];
  isEnd: boolean = true;
  errCode: number = 0;
  errMsg: string = '';
}

class PromiseSendMessageCallback implements SendMsgCallBack<Message> {
  private resolve: (value: Message) => void;
  private reject: (reason: Error) => void;
  constructor(resolve: (value: Message) => void, reject: (reason: Error) => void) {
    this.resolve = resolve;
    this.reject = reject;
  }
  onSuccess(data: Message): void {
    if (data) this.resolve(data);
    else this.reject(new Error('OpenIM 返回了空消息'));
  }
  onError(code: number, message: string): void { this.reject(new Error(`Code: ${code}, Message: ${message}`)); }
  onProgress(_progress: number): void {}
}

export class OpenIMAppWrapper {
  private static instance: OpenIMAppWrapper | null = null;
  private constructor() {}

  static getInstance(): OpenIMAppWrapper {
    if (OpenIMAppWrapper.instance === null) OpenIMAppWrapper.instance = new OpenIMAppWrapper();
    return OpenIMAppWrapper.instance;
  }

  getSDK() { return getSDK(); }
  get loginManager() { return OpenIMClient.loginManager; }
  get messageManager() { return OpenIMClient.messageManager; }
  get conversationManager() { return OpenIMClient.conversationManager; }
  get friendshipManager() { return OpenIMClient.friendshipManager; }
  get groupManager() { return OpenIMClient.groupManager; }
  get userInfoManager() { return OpenIMClient.userInfoManager; }
  get miscManager() { return OpenIMClient.miscManager; }

  init(config: InitConfig, listener: ConnListener): Promise<number> {
    return Promise.resolve(this.loginManager.initSdk(listener, buildOperationID(), config));
  }
  login(userID: string, token: string): Promise<void> {
    return new Promise<void>((resolve, reject) => this.loginManager.login(new PromiseCompletionCallback(resolve, reject), buildOperationID(), userID, token));
  }
  logout(): Promise<void> {
    return new Promise<void>((resolve, reject) => this.loginManager.logout(new PromiseCompletionCallback(resolve, reject), buildOperationID()));
  }
  getLoginStatus(): number { return this.loginManager.getLoginStatus(buildOperationID()); }
  getLoginUserID(): string { return this.loginManager.getLoginUserID(); }
  getSdkVersion(): string { return this.loginManager.getSdkVersion(); }
  unInitSDK(): void { this.loginManager.unInitSDK(buildOperationID()); }

  setAdvancedMsgListener(listener: MsgListener): void { this.messageManager.setAdvancedMsgListener(listener); }
  setConversationListener(listener: ConvListener): void { this.conversationManager.setConversationListener(listener); }
  setFriendListener(listener: FriendListener): void { this.friendshipManager.setFriendListener(listener); }
  setGroupListener(listener: GroupListener): void { this.groupManager.setGroupListener(listener); }
  setUserListener(listener: UserListener): void { this.userInfoManager.setUserListener(listener); }

  getAllConversationList(): Promise<ConversationInfo[]> {
    return new Promise<ConversationInfo[]>((resolve, reject) => this.conversationManager.getAllConversationList(new PromiseBaseCallback<ConversationInfo[]>(resolve, reject), buildOperationID()));
  }
  getOneConversation(sessionType: number, sourceID: string): Promise<ConversationInfo> {
    return new Promise<ConversationInfo>((resolve, reject) => this.conversationManager.getOneConversation(new PromiseBaseCallback<ConversationInfo>(resolve, reject), buildOperationID(), sessionType, sourceID));
  }
  markConversationMessageAsRead(conversationID: string): Promise<void> {
    return new Promise<void>((resolve, reject) => this.conversationManager.markConversationMessageAsRead(new PromiseCompletionCallback(resolve, reject), buildOperationID(), conversationID));
  }
  getFriendList(): Promise<FriendInfo[]> {
    return new Promise<FriendInfo[]>((resolve, reject) => this.friendshipManager.getFriendList(new PromiseBaseCallback<FriendInfo[]>(resolve, reject), buildOperationID()));
  }
  addFriend(userID: string, reqMsg: string): Promise<void> {
    return new Promise<void>((resolve, reject) => this.friendshipManager.addFriend(new PromiseCompletionCallback(resolve, reject), buildOperationID(), JSON.stringify({ toUserID: userID, reqMsg: reqMsg, ex: '' })));
  }
  getFriendApplicationListAsRecipient(offset: number = 0, count: number = 100): Promise<FriendApplication[]> {
    return new Promise<FriendApplication[]>((resolve, reject) => this.friendshipManager.getFriendApplicationListAsRecipient(new PromiseBaseCallback<FriendApplication[]>(resolve, reject), buildOperationID(), JSON.stringify({ offset: offset, count: count })));
  }
  getFriendApplicationListAsApplicant(offset: number = 0, count: number = 100): Promise<FriendApplication[]> {
    return new Promise<FriendApplication[]>((resolve, reject) => this.friendshipManager.getFriendApplicationListAsApplicant(new PromiseBaseCallback<FriendApplication[]>(resolve, reject), buildOperationID(), JSON.stringify({ offset: offset, count: count })));
  }
  acceptFriendApplication(userID: string, handleMsg: string = ''): Promise<void> { return this.handleFriendApplication(true, userID, handleMsg); }
  refuseFriendApplication(userID: string, handleMsg: string = ''): Promise<void> { return this.handleFriendApplication(false, userID, handleMsg); }
  private handleFriendApplication(accept: boolean, userID: string, handleMsg: string): Promise<void> {
    return new Promise<void>((resolve, reject) => {
      const callback = new PromiseCompletionCallback(resolve, reject);
      const params = JSON.stringify({ toUserID: userID, handleMsg: handleMsg });
      if (accept) this.friendshipManager.acceptFriendApplication(callback, buildOperationID(), params);
      else this.friendshipManager.refuseFriendApplication(callback, buildOperationID(), params);
    });
  }
  getJoinedGroupList(): Promise<GroupInfo[]> {
    return new Promise<GroupInfo[]>((resolve, reject) => this.groupManager.getJoinedGroupList(new PromiseBaseCallback<GroupInfo[]>(resolve, reject), buildOperationID()));
  }
  joinGroup(groupID: string, reqMsg: string = ''): Promise<void> {
    return new Promise<void>((resolve, reject) => this.groupManager.joinGroup(new PromiseCompletionCallback(resolve, reject), buildOperationID(), groupID, reqMsg));
  }
  getGroupApplicationListAsRecipient(offset: number = 0, count: number = 100): Promise<GroupApplication[]> {
    return new Promise<GroupApplication[]>((resolve, reject) => this.groupManager.getGroupApplicationListAsRecipient(new PromiseBaseCallback<GroupApplication[]>(resolve, reject), buildOperationID(), JSON.stringify({ offset: offset, count: count })));
  }
  acceptGroupApplication(groupID: string, userID: string): Promise<void> {
    return new Promise<void>((resolve, reject) => this.groupManager.acceptGroupApplication(new PromiseCompletionCallback(resolve, reject), buildOperationID(), groupID, userID));
  }
  refuseGroupApplication(groupID: string, userID: string): Promise<void> {
    return new Promise<void>((resolve, reject) => this.groupManager.refuseGroupApplication(new PromiseCompletionCallback(resolve, reject), buildOperationID(), groupID, userID));
  }
  getSelfUserInfo(): Promise<UserInfo> {
    return new Promise<UserInfo>((resolve, reject) => this.userInfoManager.getSelfUserInfo(new PromiseBaseCallback<UserInfo>(resolve, reject), buildOperationID()));
  }
  getSubscribeUsersStatus(): Promise<UsersOnlineStatus[]> {
    return new Promise<UsersOnlineStatus[]>((resolve, reject) => this.userInfoManager.getSubscribeUsersStatus(new PromiseBaseCallback<UsersOnlineStatus[]>(resolve, reject), buildOperationID()));
  }
  setAppBackgroundStatus(isBackground: boolean): Promise<void> {
    return new Promise<void>((resolve, reject) => this.userInfoManager.setAppBackgroundStatus(new PromiseCompletionCallback(resolve, reject), buildOperationID(), isBackground));
  }
  networkStatusChanged(): Promise<void> {
    return new Promise<void>((resolve, reject) => this.userInfoManager.networkStatusChanged(new PromiseCompletionCallback(resolve, reject), buildOperationID()));
  }
  getInputStates(conversationID: string, userID: string): Promise<ConversationInputStatusResult[]> {
    return new Promise<ConversationInputStatusResult[]>((resolve, reject) => this.miscManager.getInputStates(new PromiseBaseCallback<ConversationInputStatusResult[]>(resolve, reject), conversationID, userID));
  }
  getUsersInGroup(groupID: string, userIDList: string[]): Promise<string[]> {
    return new Promise<string[]>((resolve, reject) => this.groupManager.getUsersInGroup(new PromiseBaseCallback<string[]>(resolve, reject), buildOperationID(), groupID, userIDList));
  }
  createTextMessage(text: string): Message { return this.messageManager.createTextMessage(buildOperationID(), text); }

  checkFriend(userIDList: string[]): Promise<FriendshipInfo[]> {
    return new Promise<FriendshipInfo[]>((resolve, reject) => this.friendshipManager.checkFriend(new PromiseBaseCallback<FriendshipInfo[]>(resolve, reject), buildOperationID(), userIDList));
  }
  searchLocalMessages(conversationID: string, keywordList: string[]): Promise<SearchResult> {
    return new Promise<SearchResult>((resolve, reject) => this.messageManager.searchLocalMessages(new PromiseBaseCallback<SearchResult>(resolve, reject), buildOperationID(), conversationID, keywordList, 0, [], [], 0, 0, 1, 20));
  }
  findMessageList(searchParams: string): Promise<SearchResult> {
    return new Promise<SearchResult>((resolve, reject) => this.messageManager.findMessageList(new PromiseBaseCallback<SearchResult>(resolve, reject), buildOperationID(), searchParams));
  }
  insertSingleMessageToLocalStorage(message: Message, recvID: string, sendID: string): Promise<Message> {
    return new Promise<Message>((resolve, reject) => this.messageManager.insertSingleMessageToLocalStorage(new PromiseBaseCallback<Message>(resolve, reject), buildOperationID(), JSON.stringify(message), recvID, sendID));
  }
  insertGroupMessageToLocalStorage(message: Message, groupID: string, sendID: string): Promise<Message> {
    return new Promise<Message>((resolve, reject) => this.messageManager.insertGroupMessageToLocalStorage(new PromiseBaseCallback<Message>(resolve, reject), buildOperationID(), JSON.stringify(message), groupID, sendID));
  }
  sendMessage(message: Message, recvUserID: string, recvGroupID: string): Promise<Message> {
    return new Promise<Message>((resolve, reject) => {
      const callback = new PromiseSendMessageCallback(resolve, reject);
      this.messageManager.sendMessage(callback, buildOperationID(), JSON.stringify(message), recvUserID, recvGroupID, '{}', false);
    });
  }
  getAdvancedHistoryMessageList(conversationID: string, startClientMsgID: string = '', count: number = 50): Promise<HistoryMessageResult> {
    return new Promise<HistoryMessageResult>((resolve, reject) => {
      this.messageManager.getAdvancedHistoryMessageList(new PromiseBaseCallback<HistoryMessageResult>(resolve, reject), buildOperationID(), conversationID, startClientMsgID, count, 0);
    });
  }
}

export const IM = OpenIMAppWrapper.getInstance();
