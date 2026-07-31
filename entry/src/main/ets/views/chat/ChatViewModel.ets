// import { IM } from "../../sdkwrapper/IMAppWrapper";
// import { Message, MsgListener, ConversationType } from "imsdk";
// import { ConversationItem, MessageItem } from "../../common/types/UITypes";
// import Logger from "../../common/utils/Logger";
// import { C2CReadReceiptInfo, RevokedInfo } from "imsdk/src/main/ets/sdk/models/entity";
//
// @ObservedV2
// export class ChatViewModel {
//   private conversationItem?: ConversationItem;
//   @Trace public messageList: MessageItem[] = [];
//   @Trace public userID: string = "";
//   @Trace public isLoading: boolean = false;
//   @Trace public errorMsg: string = "";
//
//   onInit(conversationItem: ConversationItem) {
//     this.conversationItem = conversationItem;
//     this.isLoading = true;
//
//     // 获取当前用户ID
//     IM.getSelfUserInfo()
//       .then((userInfo) => {
//         this.userID = userInfo.userID;
//         Logger.info(`myUserID: ${this.userID}`);
//
//         // 获取历史消息
//         return IM.getAdvancedHistoryMessageListReverse(
//           conversationItem.conversationID,
//           "",
//           100
//         );
//       })
//       .then((msgList) => {
//         this.messageList = msgList.map(m => this.convertToMessageItem(m));
//         Logger.info(`loaded ${msgList.length} messages`);
//       })
//       .catch((e:Error) => {
//         Logger.error(`load messages failed: ${e}`);
//         this.errorMsg = e instanceof Error ? e.message : "加载消息失败";
//       })
//       .finally(() => {
//         this.isLoading = false;
//       });
//
//     // 初始化消息监听器
//     this.initMsgListener();
//   }
//
//   private initMsgListener() {
//     IM.setAdvancedMsgListener({
//       onRecvNewMessage: (msg: Message) => {
//         Logger.info(`onRecvNewMessage: ${msg.clientMsgID}`);
//         // 只处理当前会话的消息
//         if (msg.clientMsgID &&
//           ((this.conversationItem?.conversationType === ConversationType.SINGLE_CHAT &&
//             msg.sendID === this.conversationItem?.userID) ||
//             (this.conversationItem?.conversationType === ConversationType.GROUP_CHAT &&
//               msg.groupID === this.conversationItem?.groupID))) {
//           this.messageList.push(this.convertToMessageItem(msg));
//         }
//       },
//       onRecvC2CReadReceipt: (msgReceiptList:C2CReadReceiptInfo[]) => {
//         // 已读回执
//         msgReceiptList.forEach(receipt => {
//           const msg = this.messageList.find(m => receipt.msgIDList.findIndex(m.clientMsgID));
//           if (msg) {
//             msg.isRead = true;
//           }
//         });
//       },
//       onNewRecvMessageRevoked: (messageRevoked:RevokedInfo) => {
//         // 消息撤回
//         const index = this.messageList.findIndex(
//           m => m.clientMsgID === messageRevoked.clientMsgID
//         );
//         if (index >= 0) {
//           this.messageList.splice(index, 1);
//         }
//       },
//       onRecvOfflineNewMessage: (messages: Message[]) => {
//         // 离线消息
//         messages.forEach(msg => {
//           this.messageList.push(this.convertToMessageItem(msg));
//         });
//       },
//       onMsgDeleted: (msg: Message) => {
//         // 消息删除
//         const index = this.messageList.findIndex(m => m.clientMsgID === msg.clientMsgID);
//         if (index >= 0) {
//           this.messageList.splice(index, 1);
//         }
//       },
//       onRecvOnlineOnlyMessage: (msg: string) => {
//         // 仅在线消息 - msg是JSON字符串
//         try {
//           const msgObj = JSON.parse(msg) as Message;
//           Logger.info(`onRecvOnlineOnlyMessage`);
//           this.messageList.push(this.convertToMessageItem(msgObj));
//         } catch (e) {
//           Logger.error(`parse online message failed: ${e}`);
//         }
//       }
//     });
//   }
//
//   private convertToMessageItem(msg: Message): MessageItem {
//     const item = new MessageItem();
//     item.clientMsgID = msg.clientMsgID;
//     item.sendID = msg.sendID;
//     item.senderNickname = msg.senderNickname;
//     item.senderFaceUrl = msg.senderFaceUrl;
//     item.conversationID = "";
//     item.sessionType = msg.sessionType;
//     item.groupID = msg.groupID;
//     item.contentType = msg.contentType;
//     item.sendTime = msg.sendTime;
//     item.status = msg.status;
//     item.isSelf = msg.sendID === this.userID;
//
//     // 提取消息内容
//     if (msg.textElem?.content) {
//       item.content = msg.textElem.content;
//     } else if (msg.customElem?.data) {
//       item.content = msg.customElem.data;
//     } else if (msg.pictureElem?.sourcePath) {
//       item.content = "[图片]";
//     } else if (msg.soundElem?.soundPath) {
//       item.content = "[语音]";
//     } else if (msg.videoElem?.videoPath) {
//       item.content = "[视频]";
//     } else if (msg.fileElem?.fileName) {
//       item.content = `[文件] ${msg.fileElem.fileName}`;
//     } else {
//       item.content = "";
//     }
//
//     item.showTimestamp = false;
//     return item;
//   }
//
//   async sendTextMessage(text: string): Promise<MessageItem | null> {
//     if (!text.trim() || !this.conversationItem) {
//       return null;
//     }
//
//     try {
//       // 创建消息
//       const msg = IM.createTextMessage(text);
//       const messageItem = this.convertToMessageItem(msg);
//
//       // 添加到列表显示（乐观更新）
//       this.messageList.push(messageItem);
//
//       // 发送消息
//       const recvUid = this.conversationItem.conversationType === ConversationType.SINGLE_CHAT
//         ? this.conversationItem.userID
//         : "";
//       const recvGid = this.conversationItem.conversationType === ConversationType.GROUP_CHAT
//         ? this.conversationItem.groupID
//         : "";
//
//       await IM.sendMessage(
//         JSON.stringify(msg),
//         recvUid,
//         recvGid,
//         "",
//         false
//       );
//
//       Logger.info(`sendTextMessage success: ${text}`);
//       return messageItem;
//
//     } catch (e) {
//       Logger.error(`sendTextMessage failed: ${e}`);
//       this.errorMsg = e instanceof Error ? e.message : "发送消息失败";
//       return null;
//     }
//   }
//
//   /**
//    * 标记消息已读
//    */
//   async markMessageAsRead(clientMsgID: string): Promise<void> {
//     if (!this.conversationItem) {
//       return;
//     }
//
//     try {
//       await IM.messageManager.markMessageAsRead(
//         {
//           onError: (errCode:number, errMsg:string) => {
//             Logger.error(`markMessageAsRead failed: ${errCode} - ${errMsg}`);
//           },
//           onSuccess: () => {}
//         },
//         "mark_read_" + Date.now(),
//         this.conversationItem.conversationID,
//         clientMsgID
//       );
//     } catch (e) {
//       Logger.error(`markMessageAsRead failed: ${e}`);
//     }
//   }
//
//   /**
//    * 撤回消息
//    */
//   async revokeMessage(clientMsgID: string): Promise<boolean> {
//     if (!this.conversationItem) {
//       return false;
//     }
//
//     try {
//       await IM.messageManager.revokeMessage(
//         {
//           onError: (errCode:number, errMsg:string) => {
//             throw new Error(errMsg);
//           },
//           onSuccess: () => {}
//         },
//         "revoke_msg_" + Date.now(),
//         this.conversationItem.conversationID,
//         clientMsgID
//       );
//       // 从列表中移除
//       const index = this.messageList.findIndex(m => m.clientMsgID === clientMsgID);
//       if (index >= 0) {
//         this.messageList.splice(index, 1);
//       }
//       return true;
//     } catch (e) {
//       Logger.error(`revokeMessage failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 删除消息（本地）
//    */
//   async deleteMessageFromLocal(clientMsgID: string): Promise<boolean> {
//     if (!this.conversationItem) {
//       return false;
//     }
//
//     try {
//       await IM.messageManager.deleteMessageFromLocalStorage(
//         {
//           onError: (errCode:number, errMsg:string) => {
//             throw new Error(errMsg);
//           },
//           onSuccess: () => {}
//         },
//         "delete_msg_" + Date.now(),
//         this.conversationItem.conversationID,
//         clientMsgID
//       );
//       // 从列表中移除
//       const index = this.messageList.findIndex(m => m.clientMsgID === clientMsgID);
//       if (index >= 0) {
//         this.messageList.splice(index, 1);
//       }
//       return true;
//     } catch (e) {
//       Logger.error(`deleteMessageFromLocal failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 加载更多历史消息
//    */
//   async loadMoreMessages(): Promise<boolean> {
//     if (!this.conversationItem || this.isLoading) {
//       return false;
//     }
//
//     this.isLoading = true;
//
//     try {
//       // 获取最后一条消息的seq作为分页起点
//       const lastMsg = this.messageList.length > 0
//         ? this.messageList[this.messageList.length - 1]
//         : null;
//
//       const messages = await IM.getAdvancedHistoryMessageListReverse(
//         this.conversationItem.conversationID,
//         lastMsg?.clientMsgID || "",
//         20
//       );
//
//       // 将新消息添加到列表末尾
//       const newMessages = messages.map(m => this.convertToMessageItem(m));
//       this.messageList.push(...newMessages);
//
//       this.isLoading = false;
//       return newMessages.length > 0;
//
//     } catch (e) {
//       Logger.error(`loadMoreMessages failed: ${e}`);
//       this.isLoading = false;
//       return false;
//     }
//   }
// }
