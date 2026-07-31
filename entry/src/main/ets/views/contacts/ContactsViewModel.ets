// import { IM } from "../../sdkwrapper/IMAppWrapper";
// import { FriendInfo, GroupInfo } from "imsdk";
// import { FriendItem, GroupItem } from "../../common/types/UITypes";
// import Logger from "../../common/utils/Logger";
//
// @ObservedV2
// export default class ContactsViewModel {
//   @Trace friendList: FriendItem[] = [];
//   @Trace groupList: GroupItem[] = [];
//   @Trace isLoading: boolean = false;
//   @Trace errorMsg: string = "";
//
//   /**
//    * 加载通讯录数据（好友列表和群组列表）
//    */
//   async load() {
//     this.isLoading = true;
//     this.errorMsg = "";
//
//     try {
//       // 并行加载好友列表和群组列表
//       const [friends, groups] = await Promise.all([
//         IM.getFriendList(),
//         IM.getJoinedGroupList()
//       ]);
//
//       this.friendList = friends.map(f => this.convertToFriendItem(f));
//       this.groupList = groups.map(g => this.convertToGroupItem(g));
//
//       Logger.info(`loaded ${friends.length} friends and ${groups.length} groups`);
//     } catch (e) {
//       Logger.error(`load contacts failed: ${e}`);
//       this.errorMsg = e instanceof Error ? e.message : "加载通讯录失败";
//     } finally {
//       this.isLoading = false;
//     }
//   }
//
//   /**
//    * 刷新通讯录
//    */
//   async refresh() {
//     await this.load();
//   }
//
//   /**
//    * 获取好友列表
//    */
//   async getFriends(): Promise<FriendItem[]> {
//     try {
//       const friends = await IM.getFriendList();
//       this.friendList = friends.map(f => this.convertToFriendItem(f));
//       return this.friendList;
//     } catch (e) {
//       Logger.error(`get friend list failed: ${e}`);
//       return [];
//     }
//   }
//
//   /**
//    * 获取群组列表
//    */
//   async getGroups(): Promise<GroupItem[]> {
//     try {
//       const groups = await IM.getJoinedGroupList();
//       this.groupList = groups.map(g => this.convertToGroupItem(g));
//       return this.groupList;
//     } catch (e) {
//       Logger.error(`get group list failed: ${e}`);
//       return [];
//     }
//   }
//
//   private convertToFriendItem(friend: FriendInfo): FriendItem {
//     const item = new FriendItem();
//     item.userID = friend.userID;
//     item.nickname = friend.nickname || "";
//     item.faceUrl = friend.faceURL || "";
//     item.friendFlags = friend.friendFlags || 0;
//     return item;
//   }
//
//   private convertToGroupItem(group: GroupInfo): GroupItem {
//     const item = new GroupItem();
//     item.groupID = group.groupID;
//     item.groupName = group.groupName || "";
//     item.faceUrl = group.faceURL || "";
//     item.memberCount = group.memberCount || 0;
//     item.status = group.status || 0;
//     return item;
//   }
//
//   /**
//    * 搜索好友
//    */
//   searchFriends(keyword: string): FriendItem[] {
//     if (!keyword.trim()) {
//       return this.friendList;
//     }
//
//     const lowerKeyword = keyword.toLowerCase();
//     return this.friendList.filter(f =>
//       f.nickname.toLowerCase().includes(lowerKeyword) ||
//       f.userID.toLowerCase().includes(lowerKeyword)
//     );
//   }
//
//   /**
//    * 搜索群组
//    */
//   searchGroups(keyword: string): GroupItem[] {
//     if (!keyword.trim()) {
//       return this.groupList;
//     }
//
//     const lowerKeyword = keyword.toLowerCase();
//     return this.groupList.filter(g =>
//       g.groupName.toLowerCase().includes(lowerKeyword) ||
//       g.groupID.toLowerCase().includes(lowerKeyword)
//     );
//   }
//
//   /**
//    * 获取好友数量
//    */
//   get friendCount(): number {
//     return this.friendList.length;
//   }
//
//   /**
//    * 获取群组数量
//    */
//   get groupCount(): number {
//     return this.groupList.length;
//   }
// }
