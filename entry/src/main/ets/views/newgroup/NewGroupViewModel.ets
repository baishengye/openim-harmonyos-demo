// import { IM } from "../../sdkwrapper/IMAppWrapper";
// import { GroupInfo, GroupMemberInfo,BaseCallback } from "imsdk";
// import { GroupItem, GroupMemberItem } from "../../common/types/UITypes";
// import Logger from "../../common/utils/Logger";
//
// @ObservedV2
// export default class NewGroupViewModel {
//   @Trace searchResultList: GroupItem[] = [];
//   @Trace memberList: GroupMemberItem[] = [];
//   @Trace selectedMembers: string[] = [];
//   @Trace isLoading: boolean = false;
//   @Trace errorMsg: string = "";
//   @Trace groupName: string = "";
//
//   /**
//    * 创建群组
//    */
//   async createGroup(name: string, memberList: string[]): Promise<GroupInfo | null> {
//     if (!name.trim() || memberList.length === 0) {
//       this.errorMsg = "群组名称和成员不能为空";
//       return null;
//     }
//
//     this.isLoading = true;
//     this.errorMsg = "";
//
//     try {
//       const group = await IM.createGroup(name, memberList);
//       Logger.info(`create group success: ${group.groupID}`);
//       this.isLoading = false;
//       return group;
//     } catch (e) {
//       Logger.error(`create group failed: ${e}`);
//       this.errorMsg = e instanceof Error ? e.message : "创建群组失败";
//       this.isLoading = false;
//       return null;
//     }
//   }
//
//   /**
//    * 申请加入群组
//    */
//   async joinGroup(groupID: string, reqMsg: string = ""): Promise<boolean> {
//     this.isLoading = true;
//     this.errorMsg = "";
//
//     try {
//       await IM.joinGroup(groupID, reqMsg);
//       Logger.info(`join group success: ${groupID}`);
//       this.isLoading = false;
//       return true;
//     } catch (e) {
//       Logger.error(`join group failed: ${e}`);
//       this.errorMsg = e instanceof Error ? e.message : "加入群组失败";
//       this.isLoading = false;
//       return false;
//     }
//   }
//
//   /**
//    * 获取群成员列表
//    */
//   async getGroupMembers(groupID: string): Promise<GroupMemberItem[]> {
//     try {
//       const members = await IM.getGroupMemberList(groupID);
//       this.memberList = members.map(m => this.convertToGroupMemberItem(m));
//       return this.memberList;
//     } catch (e) {
//       Logger.error(`get group members failed: ${e}`);
//       return [];
//     }
//   }
//
//   private convertToGroupMemberItem(member: GroupMemberInfo): GroupMemberItem {
//     const item = new GroupMemberItem();
//     item.userID = member.userID;
//     item.nickname = member.nickname || "";
//     item.groupNickname = member.nickname || "";
//     item.faceUrl = member.faceURL || "";
//     item.roleLevel = member.roleLevel || 20;
//     item.isOwner = item.roleLevel === 100;
//     item.isAdmin = item.roleLevel === 60;
//     item.joinTime = member.joinTime || 0;
//     return item;
//   }
//
//   /**
//    * 添加选中的成员
//    */
//   addSelectedMember(userID: string) {
//     if (!this.selectedMembers.includes(userID)) {
//       this.selectedMembers.push(userID);
//     }
//   }
//
//   /**
//    * 移除选中的成员
//    */
//   removeSelectedMember(userID: string) {
//     const index = this.selectedMembers.indexOf(userID);
//     if (index >= 0) {
//       this.selectedMembers.splice(index, 1);
//     }
//   }
//
//   /**
//    * 清空选中的成员
//    */
//   clearSelectedMembers() {
//     this.selectedMembers = [];
//   }
//
//   /**
//    * 获取选中的成员数量
//    */
//   get selectedMemberCount(): number {
//     return this.selectedMembers.length;
//   }
//
//   /**
//    * 设置群组名称
//    */
//   setGroupName(name: string) {
//     this.groupName = name;
//   }
//
//   /**
//    * 邀请好友加入群组
//    */
//   async inviteUserToGroup(groupID: string, userIDList: string[]): Promise<boolean> {
//     try {
//       IM.groupManager.inviteUserToGroup(
//         {
//           onError: (errCode:number, errMsg:string) => {
//             throw new Error(errMsg);
//           },
//           onSuccess: () => {}
//         },
//         "invite_user_" + Date.now(),
//         groupID,
//         userIDList,
//         ""
//       );
//       Logger.info(`invite user to group success`);
//       return true;
//     } catch (e) {
//       Logger.error(`invite user to group failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 踢出群成员（仅管理员/群主）
//    */
//   async kickGroupMember(groupID: string, userID: string): Promise<boolean> {
//     try {
//       new Promise<string>(()=>{
//         IM.groupManager.kickGroupMember(
//           {
//             onError: (errCode:number, errMsg:string) => {
//
//             },
//             onSuccess: (data:string) => {}
//           },
//           "kick_member_" + Date.now(),
//           groupID,
//           userID,
//           ""
//         );
//       })
//       Logger.info(`kick group member success: ${userID}`);
//
//       // 从本地列表中移除
//       const index = this.memberList.findIndex(m => m.userID === userID);
//       if (index >= 0) {
//         this.memberList.splice(index, 1);
//       }
//
//       return true;
//     } catch (e) {
//       Logger.error(`kick group member failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 搜索群组
//    */
//   async searchGroups(keyword: string): Promise<GroupItem[]> {
//     if (!keyword.trim()) {
//       this.searchResultList = [];
//       return [];
//     }
//
//     try {
//       const groups = await IM.groupManager.searchGroups(
//         {
//           onError: (errCode, errMsg) => {
//             throw new Error(errMsg);
//           },
//           onSuccess: (data) => {
//             // 转换结果
//             this.searchResultList = data.map((g: GroupInfo) => this.convertToGroupItem(g));
//           }
//         },
//         "search_group_" + Date.now(),
//         JSON.stringify({ keywordList: [keyword] })
//       );
//       return this.searchResultList;
//     } catch (e) {
//       Logger.error(`search groups failed: ${e}`);
//       return [];
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
//     return item;
//   }
// }
