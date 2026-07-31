// import { IM } from "../../sdkwrapper/IMAppWrapper";
// import { FriendInfo, ConversationType } from "imsdk";
// import { FriendUserItem, ConversationItem } from "../../common/types/UITypes";
// import Logger from "../../common/utils/Logger";
//
// @ObservedV2
// export default class MyFriendViewModel {
//   @Trace friendList: FriendUserItem[] = [];
//   @Trace isLoading: boolean = false;
//   @Trace errorMsg: string = "";
//
//   async load() {
//     this.isLoading = true;
//     this.errorMsg = "";
//
//     try {
//       const friendList = await IM.getFriendList();
//       this.friendList = friendList.map(f => this.convertToFriendUserItem(f));
//       Logger.info(`loaded ${friendList.length} friends`);
//     } catch (e) {
//       Logger.error(`load friend list failed: ${e}`);
//       this.errorMsg = e instanceof Error ? e.message : "加载好友列表失败";
//     } finally {
//       this.isLoading = false;
//     }
//   }
//
//   private convertToFriendUserItem(friend: FriendInfo): FriendUserItem {
//     const item = new FriendUserItem();
//     item.userID = friend.userID;
//     item.nickname = friend.nickname || "";
//     item.faceUrl = friend.faceURL || "";
//     item.remark = friend.remark || "";
//     item.showName = friend.remark || friend.nickname || friend.userID;
//     return item;
//   }
//
//   async getConversation(userID: string): Promise<ConversationItem | null> {
//     try {
//       const conv = await IM.getOneConversation(ConversationType.SINGLE_CHAT, userID);
//       const item = new ConversationItem();
//       item.conversationID = conv.conversationID;
//       item.conversationType = conv.conversationType;
//       item.userID = conv.userID;
//       item.groupID = conv.groupID;
//       item.showName = conv.showName;
//       item.faceUrl = conv.faceUrl;
//       item.latestMsg = conv.latestMsg;
//       item.latestMsgSendTime = conv.latestMsgSendTime;
//       item.unreadCount = conv.unreadCount;
//       return item;
//     } catch (e) {
//       Logger.error(`getConversation failed: ${e}`);
//       return null;
//     }
//   }
//
//   async searchFriends(keyword: string): Promise<FriendUserItem[]> {
//     if (!keyword.trim()) {
//       return this.friendList;
//     }
//
//     const lowerKeyword = keyword.toLowerCase();
//     return this.friendList.filter(f =>
//       f.nickname.toLowerCase().includes(lowerKeyword) ||
//       f.remark.toLowerCase().includes(lowerKeyword) ||
//       f.userID.toLowerCase().includes(lowerKeyword)
//     );
//   }
//
//   async deleteFriend(userID: string): Promise<boolean> {
//     try {
//       await IM.friendshipManager.deleteFriend(
//         {
//           onError: (errCode:number, errMsg:string) => {
//             throw new Error(errMsg);
//           },
//           onSuccess: () => {}
//         },
//         "delete_friend_" + Date.now(),
//         userID
//       );
//       // 从列表中移除
//       const index = this.friendList.findIndex(f => f.userID === userID);
//       if (index >= 0) {
//         this.friendList.splice(index, 1);
//       }
//       return true;
//     } catch (e) {
//       Logger.error(`deleteFriend failed: ${e}`);
//       return false;
//     }
//   }
//
//   async setFriendRemark(userID: string, remark: string): Promise<boolean> {
//     try {
//       await IM.friendshipManager.setFriendRemark(
//         {
//           onError: (errCode:number, errMsg:string)  => {
//             throw new Error(errMsg);
//           },
//           onSuccess: () => {}
//         },
//         "set_remark_" + Date.now(),
//         userID,
//         remark
//       );
//       // 更新本地状态
//       const friend = this.friendList.find(f => f.userID === userID);
//       if (friend) {
//         friend.remark = remark;
//         friend.showName = remark || friend.nickname;
//       }
//       return true;
//     } catch (e) {
//       Logger.error(`setFriendRemark failed: ${e}`);
//       return false;
//     }
//   }
// }
