/**
 * OpenIM App SDK Wrapper
 * 将回调式API封装为Promise风格，方便UI层使用
 */
import {
  OpenIM,
  OpenIMClient,
  getSDK,
  InitConfig,
  Message,
  ConversationInfo,
  FriendInfo,
  FriendApplication,
  GroupInfo,
  GroupMemberInfo,
  BlackInfo,
  UserInfo,
  UsersOnlineStatus,
  BaseCallback,
  SendMsgCallBack,
  ConnListener,
  MsgListener,
  ConvListener,
  GroupListener,
  FriendListener,
  UserListener,
  ConversationType,
  Platform,
  LogLevel,
  PromiseBaseCallback,
  buildOperationID,
} from "imsdk";

/**
 * SDK包装类，提供Promise风格的API
 */
export class OpenIMAppWrapper {
  private static instance: OpenIMAppWrapper | null = null;
  private initCallback: (() => void) | null = null;

  private constructor() {}

  static getInstance(): OpenIMAppWrapper {
    if (!OpenIMAppWrapper.instance) {
      OpenIMAppWrapper.instance = new OpenIMAppWrapper();
    }
    return OpenIMAppWrapper.instance;
  }

  /**
   * 获取SDK实例
   */
  getSDK() {
    return getSDK();
  }
  //
  // /**
  //  * 获取登录管理器
  //  */
  // get loginManager() {
  //   return OpenIMClient.loginManager;
  // }
  //
  // /**
  //  * 获取消息管理器
  //  */
  // get messageManager() {
  //   return OpenIMClient.messageManager;
  // }

  /**
   * 获取会话管理器
   */
  get conversationManager() {
    return OpenIMClient.conversationManager;
  }

  /**
   * 获取好友管理器
   */
  get friendshipManager() {
    return OpenIMClient.friendshipManager;
  }

  /**
   * 获取群组管理器
   */
  get groupManager() {
    return OpenIMClient.groupManager;
  }

  /**
   * 获取用户信息管理器
   */
  get userInfoManager() {
    return OpenIMClient.userInfoManager;
  }

  /**
   * 初始化SDK
   */
  init(config: InitConfig, listener: ConnListener): Promise<number> {
    return new Promise<number>((resolve) => {
      const result = getSDK().loginManager.initSdk(
        listener,Date.now().toString(),config
      )
      resolve(result);
    });
  }

  /**
   * 登录
   */
  login(userID: string, token: string): Promise<string> {
    return new Promise<string>((resolve, reject) => {
      OpenIMClient.loginManager.login(
        new PromiseBaseCallback<string>(resolve,reject),
        buildOperationID(),
        userID,
        token
      );
    });
  }

  /**
   * 登出
   */
  logout(): Promise<string> {
    return new Promise<string>((resolve, reject) => {
      OpenIMClient.loginManager.logout(
        new PromiseBaseCallback<string>(resolve,reject),
        buildOperationID()
      );
    });
  }

  /**
   * 获取登录状态
   */
  getLoginStatus(): number {
    const operationID = buildOperationID();
    return OpenIMClient.loginManager.getLoginStatus(operationID);
  }

  /**
   * 获取当前用户ID
   */
  getLoginUserID(): string {
    return OpenIMClient.loginManager.getLoginUserID();
  }
  //
  // /**
  //  * 获取所有会话列表
  //  */
  // getAllConversationList(): Promise<ConversationInfo[]> {
  //   const operationID = buildOperationID();
  //   return new Promise<ConversationInfo[]>((resolve, reject) => {
  //     OpenIMClient.conversationManager.getAllConversationList(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getAllConversationList failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: ConversationInfo[]) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID
  //     );
  //   });
  // }
  //
  // kickGroupMember(groupID: string, userID: string): Promise<>
  //
  // /**
  //  * 分页获取会话列表
  //  */
  // getConversationListSplit(offset: number, count: number): Promise<ConversationInfo[]> {
  //   const operationID = buildOperationID();
  //   return new Promise<ConversationInfo[]>((resolve, reject) => {
  //     OpenIMClient.conversationManager.getConversationListSplit(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getConversationListSplit failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: ConversationInfo[]) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       offset,
  //       count
  //     );
  //   });
  // }
  //
  // /**
  //  * 获取单个会话
  //  */
  // getOneConversation(sessionType: number, sourceID: string): Promise<ConversationInfo> {
  //   const operationID = buildOperationID();
  //   return new Promise<ConversationInfo>((resolve, reject) => {
  //     OpenIMClient.conversationManager.getOneConversation(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getOneConversation failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: ConversationInfo) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       sessionType,
  //       sourceID
  //     );
  //   });
  // }
  //
  // /**
  //  * 设置会话监听器
  //  */
  // setConversationListener(listener: ConvListener): void {
  //   OpenIMClient.conversationManager.setConversationListener(listener);
  // }
  //
  // /**
  //  * 设置消息监听器
  //  */
  // setAdvancedMsgListener(listener: MsgListener): void {
  //   OpenIMClient.messageManager.setAdvancedMsgListener(listener);
  // }
  //
  // /**
  //  * 设置连接监听器
  //  */
  // setConnListener(listener: ConnListener): void {
  //   // 连接监听器在init时设置
  // }
  //
  // /**
  //  * 创建文本消息
  //  */
  // createTextMessage(text: string): Message {
  //   const operationID = buildOperationID();
  //   const msgStr = OpenIMClient.messageManager.createTextMessage(text, operationID);
  //   return JSON.parse(msgStr) as Message;
  // }
  //
  // /**
  //  * 发送消息
  //  */
  // sendMessage(
  //   message: string,
  //   recvUid: string,
  //   recvGid: string,
  //   offlinePushInfo: string = "",
  //   isOnlineOnly: boolean = false
  // ): Promise<Message> {
  //   const operationID = buildOperationID();
  //   return new Promise<Message>((resolve, reject) => {
  //     OpenIMClient.messageManager.sendMessage(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`sendMessage failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: Message) => {
  //           resolve(data);
  //         },
  //         onProgress: (progress: number) => {
  //           // 发送进度回调
  //         }
  //       },
  //       operationID,
  //       message,
  //       recvUid,
  //       recvGid,
  //       offlinePushInfo,
  //       isOnlineOnly
  //     );
  //   });
  // }
  //
  // /**
  //  * 获取历史消息
  //  */
  // getAdvancedHistoryMessageListReverse(
  //   conversationID: string,
  //   lastMsgSeq: string,
  //   count: number
  // ): Promise<Message[]> {
  //   const operationID = buildOperationID();
  //   return new Promise<Message[]>((resolve, reject) => {
  //     OpenIMClient.messageManager.getAdvancedHistoryMessageListReverse(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getAdvancedHistoryMessageListReverse failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: string) => {
  //           try {
  //             const result = JSON.parse(data);
  //             const msgList: Message[] = JSON.parse(result.data);
  //             resolve(msgList);
  //           } catch (e) {
  //             reject(new Error(`parse message failed: ${e}`));
  //           }
  //         }
  //       },
  //       operationID,
  //       conversationID,
  //       lastMsgSeq,
  //       count
  //     );
  //   });
  // }
  //
  // /**
  //  * 获取好友列表
  //  */
  // getFriendList(): Promise<FriendInfo[]> {
  //   const operationID = buildOperationID();
  //   return new Promise<FriendInfo[]>((resolve, reject) => {
  //     OpenIMClient.friendshipManager.getFriendList(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getFriendList failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: FriendInfo[]) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID
  //     );
  //   });
  // }
  //
  // /**
  //  * 获取好友申请列表（作为接收人）
  //  */
  // getFriendApplicationListAsRecipient(offset: number, count: number): Promise<FriendApplication[]> {
  //   const operationID = buildOperationID();
  //   const params = JSON.stringify({ offset: offset, count: count, handleResults: [] });
  //   return new Promise<FriendApplication[]>((resolve, reject) => {
  //     OpenIMClient.friendshipManager.getFriendApplicationListAsRecipient(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getFriendApplicationListAsRecipient failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: FriendApplication[]) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       params
  //     );
  //   });
  // }
  //
  // /**
  //  * 获取好友申请列表（作为申请人）
  //  */
  // getFriendApplicationListAsApplicant(offset: number, count: number): Promise<FriendApplication[]> {
  //   const operationID = buildOperationID();
  //   const params = JSON.stringify({ offset: offset, count: count });
  //   return new Promise<FriendApplication[]>((resolve, reject) => {
  //     OpenIMClient.friendshipManager.getFriendApplicationListAsApplicant(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getFriendApplicationListAsApplicant failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: FriendApplication[]) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       params
  //     );
  //   });
  // }
  //
  // /**
  //  * 同意好友申请
  //  */
  // acceptFriendApplication(userID: string, handleMsg: string = ""): Promise<string> {
  //   const operationID = buildOperationID();
  //   const params = JSON.stringify({ userID: userID, handleMsg: handleMsg });
  //   return new Promise<string>((resolve, reject) => {
  //     OpenIMClient.friendshipManager.acceptFriendApplication(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`acceptFriendApplication failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: string) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       params
  //     );
  //   });
  // }
  //
  // /**
  //  * 拒绝好友申请
  //  */
  // refuseFriendApplication(userID: string, handleMsg: string = ""): Promise<string> {
  //   const operationID = buildOperationID();
  //   const params = JSON.stringify({ userID: userID, handleMsg: handleMsg });
  //   return new Promise<string>((resolve, reject) => {
  //     OpenIMClient.friendshipManager.refuseFriendApplication(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`refuseFriendApplication failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: string) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       params
  //     );
  //   });
  // }
  //
  // /**
  //  * 添加好友
  //  */
  // addFriend(userID: string, reqMsg: string, ex: string = ""): Promise<string> {
  //   const operationID = buildOperationID();
  //   const params = JSON.stringify({ userID: userID, reqMsg: reqMsg, ex: ex });
  //   return new Promise<string>((resolve, reject) => {
  //     OpenIMClient.friendshipManager.addFriend(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`addFriend failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: string) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       params
  //     );
  //   });
  // }
  //
  // /**
  //  * 获取黑名单
  //  */
  // getBlackList(): Promise<BlackInfo[]> {
  //   const operationID = buildOperationID();
  //   return new Promise<BlackInfo[]>((resolve, reject) => {
  //     OpenIMClient.friendshipManager.getBlackList(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getBlackList failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: BlackInfo[]) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID
  //     );
  //   });
  // }
  //
  // /**
  //  * 获取加入的群组列表
  //  */
  // getJoinedGroupList(): Promise<GroupInfo[]> {
  //   const operationID = buildOperationID();
  //   return new Promise<GroupInfo[]>((resolve, reject) => {
  //     OpenIMClient.groupManager.getJoinedGroupList(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getJoinedGroupList failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: GroupInfo[]) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID
  //     );
  //   });
  // }
  //
  // /**
  //  * 获取群成员列表
  //  */
  // getGroupMemberList(groupID: string): Promise<GroupMemberInfo[]> {
  //   const operationID = buildOperationID();
  //   return new Promise<GroupMemberInfo[]>((resolve, reject) => {
  //     OpenIMClient.groupManager.getGroupMemberList(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getGroupMemberList failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: GroupMemberInfo[]) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       groupID,
  //       0,
  //       9999
  //     );
  //   });
  // }
  //
  // /**
  //  * 创建群组
  //  */
  // createGroup(groupName: string, memberList: string[]): Promise<GroupInfo> {
  //   const operationID = buildOperationID();
  //   return new Promise<GroupInfo>((resolve, reject) => {
  //     OpenIMClient.groupManager.createGroup(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`createGroup failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: GroupInfo) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       groupName,
  //       "",
  //       memberList
  //     );
  //   });
  // }
  //
  // /**
  //  * 申请加入群组
  //  */
  // joinGroup(groupID: string, reqMsg: string): Promise<string> {
  //   const operationID = buildOperationID();
  //   return new Promise<string>((resolve, reject) => {
  //     OpenIMClient.groupManager.joinGroup(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`joinGroup failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: string) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       groupID,
  //       reqMsg
  //     );
  //   });
  // }
  //
  // /**
  //  * 获取用户信息
  //  */
  // getUsersInfo(userIDList: string[]): Promise<UserInfo[]> {
  //   const operationID = buildOperationID();
  //   return new Promise<UserInfo[]>((resolve, reject) => {
  //     OpenIMClient.userInfoManager.getUsersInfo(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getUsersInfo failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: UserInfo[]) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID,
  //       userIDList
  //     );
  //   });
  // }
  //
  // /**
  //  * 获取当前用户信息
  //  */
  // getSelfUserInfo(): Promise<UserInfo> {
  //   const operationID = buildOperationID();
  //   return new Promise<UserInfo>((resolve, reject) => {
  //     OpenIMClient.userInfoManager.getSelfUserInfo(
  //       {
  //         onError: (errCode: number, errMsg: string) => {
  //           reject(new Error(`getSelfUserInfo failed: ${errCode} - ${errMsg}`));
  //         },
  //         onSuccess: (data: UserInfo) => {
  //           resolve(data);
  //         }
  //       },
  //       operationID
  //     );
  //   });
  // }
  //
  // /**
  //  * 设置好友申请监听器
  //  */
  // setFriendListener(listener: FriendListener): void {
  //   OpenIMClient.friendshipManager.setFriendListener(listener);
  // }
  //
  // /**
  //  * 设置群组监听器
  //  */
  // setGroupListener(listener: GroupListener): void {
  //   OpenIMClient.groupManager.setGroupListener(listener);
  // }
  //
  // /**
  //  * 设置用户监听器
  //  */
  // setUserListener(listener: UserListener): void {
  //   OpenIMClient.userInfoManager.setUserListener(listener);
  // }
}

/**
 * 导出SDK包装单例
 */
export const IM = OpenIMAppWrapper.getInstance();
