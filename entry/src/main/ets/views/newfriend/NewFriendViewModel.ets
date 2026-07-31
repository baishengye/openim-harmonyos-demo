// import { IM } from "../../sdkwrapper/IMAppWrapper";
// import { FriendApplication } from "imsdk";
// import { FriendApplicationItem } from "../../common/types/UITypes";
// import Logger from "../../common/utils/Logger";
//
// @ObservedV2
// export default class NewFriendViewModel {
//   @Trace list: FriendApplicationItem[] = [];
//   @Trace isLoading: boolean = false;
//   @Trace errorMsg: string = "";
//
//   async load() {
//     this.isLoading = true;
//     this.errorMsg = "";
//     this.list = [];
//
//     try {
//       Logger.info(`load friend application`);
//
//       // 获取作为接收人的申请（别人发给我的）
//       const recipients = await IM.getFriendApplicationListAsRecipient(0, 20);
//
//       // 获取作为申请人的申请（我发给别人的）
//       const applicants = await IM.getFriendApplicationListAsApplicant(0, 20);
//
//       // 标记哪些是自己发起的申请
//       recipients.forEach(item => {
//         item.isMyRequest = false;
//       });
//
//       applicants.forEach(item => {
//         item.isMyRequest = true;
//       });
//
//       this.list = [...recipients, ...applicants].map((app:FriendApplication) =>
//         this.convertToFriendApplicationItem(app)
//       );
//
//       Logger.info(`loaded ${this.list.length} friend applications`);
//     } catch (e) {
//       Logger.error(`load friend application failed: ${e}`);
//       this.errorMsg = e instanceof Error ? e.message : "加载好友申请失败";
//     } finally {
//       this.isLoading = false;
//     }
//   }
//
//   private convertToFriendApplicationItem(app: FriendApplication): FriendApplicationItem {
//     const item = new FriendApplicationItem();
//     item.userID = app.fromUserID;
//     item.nickname = app.fromNickname || "";
//     item.faceUrl = app.fromFaceURL || "";
//     item.reqMsg = app.reqMsg || "";
//     item.handleStatus = app.handleResult || 0;
//     item.createTime = app.createTime || 0;
//     item.isMyRequest = false; // 默认值，具体值在load()中设置
//     return item;
//   }
//
//   /**
//    * 接受好友申请
//    */
//   async accept(userID: string): Promise<boolean> {
//     try {
//       await IM.acceptFriendApplication(userID);
//       Logger.info(`accept friend application: ${userID}`);
//
//       // 更新本地状态
//       const item = this.list.find(i => i.userID === userID);
//       if (item) {
//         item.handleStatus = 0; // 已接受
//       }
//
//       return true;
//     } catch (e) {
//       Logger.error(`accept friend application failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 拒绝好友申请
//    */
//   async refuse(userID: string): Promise<boolean> {
//     try {
//       await IM.refuseFriendApplication(userID);
//       Logger.info(`refuse friend application: ${userID}`);
//
//       // 更新本地状态
//       const item = this.list.find(i => i.userID === userID);
//       if (item) {
//         item.handleStatus = 1; // 已拒绝
//       }
//
//       return true;
//     } catch (e) {
//       Logger.error(`refuse friend application failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 添加好友
//    */
//   async addFriend(userID: string, reqMsg: string): Promise<boolean> {
//     try {
//       await IM.addFriend(userID, reqMsg);
//       Logger.info(`add friend: ${userID}`);
//       return true;
//     } catch (e) {
//       Logger.error(`add friend failed: ${e}`);
//       return false;
//     }
//   }
//
//   /**
//    * 获取待处理的申请数量
//    */
//   get pendingCount(): number {
//     return this.list.filter(item =>
//       item.handleStatus === -1 && !item.isMyRequest
//     ).length;
//   }
//
//   /**
//    * 获取我的申请数量
//    */
//   get myRequestCount(): number {
//     return this.list.filter(item => item.isMyRequest).length;
//   }
//
//   /**
//    * 格式化申请时间
//    */
//   formatTime(createTime: number): string {
//     if (createTime <= 0) {
//       return "";
//     }
//
//     const date = new Date(createTime);
//     const now = new Date();
//     const diff = now.getTime() - date.getTime();
//
//     // 1分钟内
//     if (diff < 60 * 1000) {
//       return "刚刚";
//     }
//
//     // 1小时内
//     if (diff < 60 * 60 * 1000) {
//       const minutes = Math.floor(diff / (60 * 1000));
//       return `${minutes}分钟前`;
//     }
//
//     // 1天内
//     if (diff < 24 * 60 * 60 * 1000) {
//       const hours = Math.floor(diff / (60 * 60 * 1000));
//       return `${hours}小时前`;
//     }
//
//     // 超过1天显示日期
//     const month = String(date.getMonth() + 1).padStart(2, '0');
//     const day = String(date.getDate()).padStart(2, '0');
//     return `${month}-${day}`;
//   }
//
//   /**
//    * 获取状态描述
//    */
//   getStatusText(handleStatus: number, isMyRequest: boolean): string {
//     if (isMyRequest) {
//       switch (handleStatus) {
//         case -1:
//           return "等待验证";
//         case 0:
//           return "已同意";
//         case 1:
//           return "已拒绝";
//         default:
//           return "未知";
//       }
//     } else {
//       switch (handleStatus) {
//         case -1:
//           return "待处理";
//         case 0:
//           return "已同意";
//         case 1:
//           return "已拒绝";
//         default:
//           return "未知";
//       }
//     }
//   }
// }
