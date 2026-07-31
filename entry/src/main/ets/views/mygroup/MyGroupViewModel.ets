// import { IM } from "../../sdkwrapper/IMAppWrapper";
// import { GroupInfo, GroupListener } from "imsdk";
// import { GroupItem } from "../../common/types/UITypes";
// import Logger from "../../common/utils/Logger";
//
// @ObservedV2
// export default class MyGroupViewModel {
//   @Trace groupList: GroupItem[] = [];
//   @Trace isLoading: boolean = false;
//   @Trace errorMsg: string = "";
//
//   async load() {
//     this.isLoading = true;
//     this.errorMsg = "";
//
//     try {
//       const groups = await IM.getJoinedGroupList();
//       this.groupList = groups.map(g => this.convertToGroupItem(g));
//       Logger.info(`loaded ${groups.length} groups`);
//     } catch (e) {
//       Logger.error(`load group list failed: ${e}`);
//       this.errorMsg = e instanceof Error ? e.message : "加载群组列表失败";
//     } finally {
//       this.isLoading = false;
//     }
//   }
//
//   private convertToGroupItem(group: GroupInfo): GroupItem {
//     const item = new GroupItem();
//     item.groupID = group.groupID;
//     item.groupName = group.groupName || "";
//     item.faceUrl = group.faceURL || "";
//     item.memberCount = group.memberCount || 0;
//     item.status = group.status || 0;
//     item.isAdmin = false; // 需要从群成员信息中获取
//     return item;
//   }
//
//   /**
//    * 刷新群组列表
//    */
//   async refresh() {
//     this.isLoading = true;
//     try {
//       const groups = await IM.getJoinedGroupList();
//       this.groupList = groups.map(g => this.convertToGroupItem(g));
//     } catch (e) {
//       Logger.error(`refresh group list failed: ${e}`);
//     } finally {
//       this.isLoading = false;
//     }
//   }
//
//   /**
//    * 退出群组
//    */
//   async quitGroup(groupID: string): Promise<boolean> {
//     try {
//       await IM.groupManager.quitGroup(
//         {
//           onError: (errCode:number, errMsg:string)  => {
//             throw new Error(errMsg);
//           },
//           onSuccess: () => {}
//         },
//         "quit_group_" + Date.now(),
//         groupID
//       );
//
//       // 从列表中移除
//       const index = this.groupList.findIndex(g => g.groupID === groupID);
//       if (index >= 0) {
//         this.groupList.splice(index, 1);
//       }
//
//       Logger.info(`quit group success: ${groupID}`);
//       return true;
//     } catch (e) {
//       Logger.error(`quit group failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 解散群组（仅群主）
//    */
//   async dismissGroup(groupID: string): Promise<boolean> {
//     try {
//       await IM.groupManager.dismissGroup(
//         {
//           onError: (errCode:number, errMsg:string)  => {
//             throw new Error(errMsg);
//           },
//           onSuccess: () => {}
//         },
//         "dismiss_group_" + Date.now(),
//         groupID
//       );
//
//       // 从列表中移除
//       const index = this.groupList.findIndex(g => g.groupID === groupID);
//       if (index >= 0) {
//         this.groupList.splice(index, 1);
//       }
//
//       Logger.info(`dismiss group success: ${groupID}`);
//       return true;
//     } catch (e) {
//       Logger.error(`dismiss group failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 根据群组ID查找群组
//    */
//   findGroupByID(groupID: string): GroupItem | undefined {
//     return this.groupList.find(g => g.groupID === groupID);
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
// }
