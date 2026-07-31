// import { IM } from "../../sdkwrapper/IMAppWrapper";
// import { UserInfo, FriendListener, GroupListener } from "imsdk";
// import Logger from "../../common/utils/Logger";
//
// @ObservedV2
// export default class MineViewModel {
//   @Trace userInfo: UserInfo | null = null;
//   @Trace isLoading: boolean = false;
//   @Trace errorMsg: string = "";
//
//   async load() {
//     this.isLoading = true;
//     this.errorMsg = "";
//
//     try {
//       this.userInfo = await IM.getSelfUserInfo();
//       Logger.info(`loaded user info: ${this.userInfo?.userID}`);
//     } catch (e) {
//       Logger.error(`load user info failed: ${e}`);
//       this.errorMsg = e instanceof Error ? e.message : "加载用户信息失败";
//     } finally {
//       this.isLoading = false;
//     }
//   }
//
//   /**
//    * 刷新用户信息
//    */
//   async refresh() {
//     await this.load();
//   }
//
//   /**
//    * 获取当前用户ID
//    */
//   getUserID(): string {
//     return this.userInfo?.userID || IM.getLoginUserID();
//   }
//
//   /**
//    * 获取用户昵称
//    */
//   getNickname(): string {
//     return this.userInfo?.nickname || this.getUserID();
//   }
//
//   /**
//    * 获取用户头像
//    */
//   getFaceUrl(): string {
//     return this.userInfo?.faceURL || "";
//   }
//
//   /**
//    * 设置用户信息
//    */
//   async setSelfUserInfo(nickname: string, faceUrl: string): Promise<boolean> {
//     try {
//       await IM.userInfoManager.setSelfInfo(
//         {
//           onError: (errCode:number, errMsg:string) => {
//             throw new Error(errMsg);
//           },
//           onSuccess: () => {}
//         },
//         "set_user_info_" + Date.now(),
//         nickname,
//         faceUrl
//       );
//       // 刷新用户信息
//       await this.refresh();
//       return true;
//     } catch (e) {
//       Logger.error(`set self user info failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 登出
//    */
//   async logout(): Promise<boolean> {
//     this.isLoading = true;
//
//     try {
//       await IM.logout();
//       Logger.info(`logout success`);
//       this.isLoading = false;
//       return true;
//     } catch (e) {
//       Logger.error(`logout failed: ${e}`);
//       this.isLoading = false;
//       return false;
//     }
//   }
//
//   /**
//    * 获取好友数量
//    */
//   async getFriendCount(): Promise<number> {
//     try {
//       const friends = await IM.getFriendList();
//       return friends.length;
//     } catch (e) {
//       Logger.error(`get friend count failed: ${e}`);
//       return 0;
//     }
//   }
//
//   /**
//    * 获取群组数量
//    */
//   async getGroupCount(): Promise<number> {
//     try {
//       const groups = await IM.getJoinedGroupList();
//       return groups.length;
//     } catch (e) {
//       Logger.error(`get group count failed: ${e}`);
//       return 0;
//     }
//   }
// }
