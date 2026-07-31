// import { IM } from "../../sdkwrapper/IMAppWrapper";
// import { ConversationInfo, ConvListener } from "imsdk";
// import { ConversationItem, MessageItem } from "../../common/types/UITypes";
// import Logger from "../../common/utils/Logger";
//
// class ConvListenerImpl implements ConvListener{
//   private viewModel:ConversationViewModel;
//   constructor(viewModel:ConversationViewModel) {
//     this.viewModel = viewModel;
//   }
//   onSyncServerStart(reinstalled: boolean): void {
//     Logger.info(`onSyncServerStart, reinstalled: ${reinstalled}`);
//   }
//
//   onSyncServerFinish(reinstalled: boolean): void {
//     Logger.info(`onSyncServerFinish, reinstalled: ${reinstalled}`);
//     this.viewModel.isLoading = false;
//   }
//
//   onSyncServerProgress(progress: number): void {
//     Logger.info(`onSyncServerProgress: ${progress}`);
//   }
//
//   onSyncServerFailed(reinstalled: boolean): void {
//     Logger.info(`onSyncServerFailed, reinstalled: ${reinstalled}`);
//     this.viewModel.isLoading = false;
//     this.viewModel.errorMsg = "同步会话列表失败";
//   }
//
//   onConversationChanged(convList: ConversationInfo[]): void {
//     Logger.info(`onConversationChanged: ${convList.length}`);
//     convList.forEach(c => {
//       const index = this.viewModel.conversationList.findIndex(
//         item => item.conversationID === c.conversationID
//       );
//       const item = this.viewModel.convertToConversationItem(c);
//       if (index >= 0) {
//         this.viewModel.conversationList[index] = item;
//       } else {
//         this.viewModel.conversationList.push(item);
//       }
//     });
//   }
//
//   onNewConversation(convList: ConversationInfo[]): void {
//     Logger.info(`onNewConversation: ${convList.length}`);
//     convList.forEach(c => {
//       const item = this.viewModel.convertToConversationItem(c);
//       const exists = this.viewModel.conversationList.some(
//         existing => existing.conversationID === c.conversationID
//       );
//       if (!exists) {
//         this.viewModel.conversationList.push(item);
//       }
//     });
//   }
//
//   onTotalUnreadMessageCountChanged(totalUnreadCount: number): void {
//     Logger.info(`onTotalUnreadMessageCountChanged: ${totalUnreadCount}`);
//   }
//
//   onConversationUserInputStatusChanged(change: string): void {
//     // 收到用户输入状态变化
//   }
// }
//
// @ObservedV2
// export class ConversationViewModel {
//   @Trace conversationList: ConversationItem[] = [];
//   @Trace isLoading: boolean = false;
//   @Trace errorMsg: string = "";
//
//   async load() {
//     this.isLoading = true;
//
//     IM.setConversationListener(new ConvListenerImpl(this));
//
//     // 获取会话列表
//     try {
//       const convs = await IM.getAllConversationList();
//       this.conversationList = convs.map(c => this.convertToConversationItem(c));
//       this.isLoading = false;
//     } catch (e) {
//       Logger.error(`load conversation list failed: ${e}`);
//       this.errorMsg = e instanceof Error ? e.message : "加载会话列表失败";
//       this.isLoading = false;
//     }
//   }
//
//   private convertToConversationItem(conv: ConversationInfo): ConversationItem {
//     const item = new ConversationItem();
//     item.conversationID = conv.conversationID;
//     item.conversationType = conv.conversationType;
//     item.userID = conv.userID;
//     item.groupID = conv.groupID;
//     item.showName = conv.showName;
//     item.faceUrl = conv.faceUrl;
//     item.latestMsg = conv.latestMsg;
//     item.latestMsgSendTime = conv.latestMsgSendTime;
//     item.unreadCount = conv.unreadCount;
//     item.isPinned = conv.isPinned;
//     item.isMute = conv.recvMsgOpt === 1; // 根据recvMsgOpt判断是否免打扰
//     item.draftText = conv.draftText;
//     item.isTyping = false;
//     return item;
//   }
//
//   formatMillisecondsToTime(ms: number): string {
//     if (ms <= 0) {
//       return "";
//     }
//     const date = new Date(ms);
//     const now = new Date();
//     const diff = now.getTime() - date.getTime();
//
//     // 超过1天显示日期
//     if (diff > 24 * 60 * 60 * 1000) {
//       const month = String(date.getMonth() + 1).padStart(2, '0');
//       const day = String(date.getDate()).padStart(2, '0');
//       return `${month}-${day}`;
//     }
//
//     // 1天内显示时间
//     const hours = String(date.getHours()).padStart(2, '0');
//     const minutes = String(date.getMinutes()).padStart(2, '0');
//     return `${hours}:${minutes}`;
//   }
//
//   getTextMessageContent(msg: string): string {
//     if (!msg) {
//       return "";
//     }
//     try {
//       const m = JSON.parse(msg) as MessageItem;
//       return m.content ?? "";
//     } catch (e) {
//       return msg;
//     }
//   }
//
//   getMessageTime(msg: string): string {
//     if (!msg) {
//       return "";
//     }
//     try {
//       const m = JSON.parse(msg) as MessageItem;
//       return this.formatMillisecondsToTime(m.sendTime);
//     } catch (e) {
//       return "";
//     }
//   }
//
//   /**
//    * 刷新会话列表
//    */
//   async refresh() {
//     try {
//       const convs = await IM.getAllConversationList();
//       this.conversationList = convs.map(c => this.convertToConversationItem(c));
//     } catch (e) {
//       Logger.error(`refresh conversation list failed: ${e}`);
//     }
//   }
//
//   /**
//    * 删除会话
//    */
//   async deleteConversation(conversationID: string): Promise<boolean> {
//     try {
//       IM.conversationManager.deleteConversationAndDeleteAllMsg(
//         {
//           onError: (errCode:number, errMsg:string) => {
//             throw new Error(errMsg);
//           },
//           onSuccess: () => {}
//         },
//         "delete_conversation_" + Date.now(),
//         conversationID,
//       );
//       // 从列表中移除
//       const index = this.conversationList.findIndex(
//         item => item.conversationID === conversationID
//       );
//       if (index >= 0) {
//         this.conversationList.splice(index, 1);
//       }
//       return true;
//     } catch (e) {
//       Logger.error(`delete conversation failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 置顶/取消置顶会话
//    */
//   async pinConversation(conversationID: string, isPinned: boolean): Promise<boolean> {
//     try {
//       await IM.conversationManager.pinConversation(
//         {
//           onError: (errCode, errMsg) => {
//             throw new Error(errMsg);
//           },
//           onSuccess: () => {}
//         },
//         "pin_conversation_" + Date.now(),
//         conversationID,
//         isPinned
//       );
//       // 更新本地状态
//       const item = this.conversationList.find(
//         c => c.conversationID === conversationID
//       );
//       if (item) {
//         item.isPinned = isPinned;
//       }
//       return true;
//     } catch (e) {
//       Logger.error(`pin conversation failed: ${e}`);
//       return false;
//     }
//   }
// }
