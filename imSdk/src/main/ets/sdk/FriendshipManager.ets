/**
 * OpenIM SDK for HarmonyOS
 * 好友管理器 - 处理好友相关操作
 */

import im from 'libimsdk.so';
import { buildOperationID } from './Utils';
import { debug, info, error } from './Logger';
import { toString, toObject, toArray } from './JsonUtil';

/**
 * 好友信息
 */
export class FriendInfo {
  ownerUserID: string = "";
  friendUserID: string = "";
  remark: string = "";
  createTime: number = 0;
  addSource: number = 0;
  operatorUserID: string = "";
  nickname: string = "";
  faceUrl: string = "";
  gender: number = 0;
  phoneNumber: string = "";
  birth: string = "";
  email: string = "";
  ex: string = "";
}

/**
 * 好友申请信息
 */
export class FriendApplication {
  fromUserID: string = "";
  fromNickname: string = "";
  fromFaceUrl: string = "";
  toUserID: string = "";
  toNickname: string = "";
  toFaceUrl: string = "";
  handleTime: number = 0;
  handleMsg: string = "";
  reqMsg: string = "";
  flag: number = 0;
  createTime: number = 0;
  type: number = 0;
}

/**
 * 黑名单信息
 */
export class BlackInfo {
  ownerUserID: string = "";
  blockUserID: string = "";
  nickname: string = "";
  faceUrl: string = "";
  gender: number = 0;
  createTime: number = 0;
}

/**
 * 好友管理器
 * 提供好友查询、添加、管理等操作
 */
export class FriendshipManager {
  /**
   * 获取好友列表
   * @param filterBlack 是否过滤黑名单
   * @returns 好友列表
   */
  getFriendList(filterBlack: boolean = false): Promise<FriendInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `getFriendList, filterBlack: ${filterBlack}, operationID: ${operationID}`);

      im.getFriendList(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `getFriendList failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `getFriendList success`);
            resolve(toArray<FriendInfo>(data));
          }
        },
        operationID,
        filterBlack
      );
    });
  }

  /**
   * 分页获取好友列表
   * @param offset 偏移量
   * @param count 数量
   * @param filterBlack 是否过滤黑名单
   * @returns 好友列表
   */
  getFriendListPage(offset: number, count: number, filterBlack: boolean = false): Promise<FriendInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `getFriendListPage, offset: ${offset}, count: ${count}, operationID: ${operationID}`);

      im.getFriendListPage(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `getFriendListPage failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `getFriendListPage success`);
            resolve(toArray<FriendInfo>(data));
          }
        },
        operationID,
        offset,
        count,
        filterBlack
      );
    });
  }

  /**
   * 获取指定好友信息
   * @param userIDList 用户ID列表
   * @param ex 是否获取扩展信息
   * @returns 好友信息列表
   */
  getSpecifiedFriendsInfo(userIDList: string[], ex: boolean = false): Promise<FriendInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `getSpecifiedFriendsInfo, operationID: ${operationID}`);

      im.getSpecifiedFriendsInfo(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `getSpecifiedFriendsInfo failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `getSpecifiedFriendsInfo success`);
            resolve(toArray<FriendInfo>(data));
          }
        },
        operationID,
        toString(userIDList),
        ex
      );
    });
  }

  /**
   * 搜索好友
   * @param params 搜索参数JSON
   * @returns 好友列表
   */
  searchFriends(params: string): Promise<FriendInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `searchFriends, operationID: ${operationID}`);

      im.searchFriends(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `searchFriends failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `searchFriends success`);
            resolve(toArray<FriendInfo>(data));
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 添加好友
   * @param params 添加参数JSON
   * @returns 添加结果
   */
  addFriend(params: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `addFriend, operationID: ${operationID}`);

      im.addFriend(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `addFriend failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `addFriend success`);
            resolve(data);
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 检查好友关系
   * @param userIDList 用户ID列表
   * @returns 好友关系结果
   */
  checkFriend(userIDList: string[]): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `checkFriend, operationID: ${operationID}`);

      im.checkFriend(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `checkFriend failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `checkFriend success`);
            resolve(data);
          }
        },
        operationID,
        toString(userIDList)
      );
    });
  }

  /**
   * 更新好友信息
   * @param params 更新参数JSON
   * @returns 更新结果
   */
  updateFriends(params: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `updateFriends, operationID: ${operationID}`);

      im.updateFriends(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `updateFriends failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `updateFriends success`);
            resolve(data);
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 获取未处理好友申请数量
   * @returns 未处理数量
   */
  getFriendApplicationUnhandledCount(): Promise<number> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `getFriendApplicationUnhandledCount, operationID: ${operationID}`);

      im.getFriendApplicationUnhandledCount(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `getFriendApplicationUnhandledCount failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `getFriendApplicationUnhandledCount success: ${data}`);
            resolve(parseInt(data) || 0);
          }
        },
        operationID,
        "{}"
      );
    });
  }

  /**
   * 删除好友
   * @param friendUserID 好友用户ID
   * @returns 删除结果
   */
  deleteFriend(friendUserID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `deleteFriend: ${friendUserID}, operationID: ${operationID}`);

      im.deleteFriend(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `deleteFriend failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `deleteFriend success`);
            resolve(data);
          }
        },
        operationID,
        friendUserID
      );
    });
  }

  /**
   * 设置好友备注
   * @param toUserID 用户ID
   * @param remark 备注
   * @returns 设置结果
   */
  setFriendRemark(toUserID: string, remark: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `setFriendRemark: ${toUserID}, remark: ${remark}, operationID: ${operationID}`);

      im.setFriendRemark(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `setFriendRemark failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `setFriendRemark success`);
            resolve(data);
          }
        },
        operationID,
        toUserID,
        remark
      );
    });
  }

  /**
   * 获取作为申请人的好友申请列表
   * @param params 查询参数JSON
   * @returns 好友申请列表
   */
  getFriendApplicationListAsApplicant(params: string): Promise<FriendApplication[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `getFriendApplicationListAsApplicant, operationID: ${operationID}`);

      im.getFriendApplicationListAsApplicant(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `getFriendApplicationListAsApplicant failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `getFriendApplicationListAsApplicant success`);
            resolve(toArray<FriendApplication>(data));
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 获取作为接收人的好友申请列表
   * @param params 查询参数JSON
   * @returns 好友申请列表
   */
  getFriendApplicationListAsRecipient(params: string): Promise<FriendApplication[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `getFriendApplicationListAsRecipient, operationID: ${operationID}`);

      im.getFriendApplicationListAsRecipient(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `getFriendApplicationListAsRecipient failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `getFriendApplicationListAsRecipient success`);
            resolve(toArray<FriendApplication>(data));
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 接受好友申请
   * @param params 接受参数JSON
   * @returns 接受结果
   */
  acceptFriendApplication(params: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `acceptFriendApplication, operationID: ${operationID}`);

      im.acceptFriendApplication(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `acceptFriendApplication failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `acceptFriendApplication success`);
            resolve(data);
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 拒绝好友申请
   * @param params 拒绝参数JSON
   * @returns 拒绝结果
   */
  refuseFriendApplication(params: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `refuseFriendApplication, operationID: ${operationID}`);

      im.refuseFriendApplication(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `refuseFriendApplication failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `refuseFriendApplication success`);
            resolve(data);
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 添加黑名单
   * @param toUserID 用户ID
   * @param ex 扩展信息
   * @returns 添加结果
   */
  addBlack(toUserID: string, ex: string = ""): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `addBlack: ${toUserID}, operationID: ${operationID}`);

      im.addBlack(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `addBlack failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `addBlack success`);
            resolve(data);
          }
        },
        operationID,
        toUserID,
        ex
      );
    });
  }

  /**
   * 获取黑名单
   * @returns 黑名单列表
   */
  getBlackList(): Promise<BlackInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `getBlackList, operationID: ${operationID}`);

      im.getBlackList(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `getBlackList failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `getBlackList success`);
            resolve(toArray<BlackInfo>(data));
          }
        },
        operationID
      );
    });
  }

  /**
   * 移除黑名单
   * @param userID 用户ID
   * @returns 移除结果
   */
  removeBlack(userID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('FriendshipManager', `removeBlack: ${userID}, operationID: ${operationID}`);

      im.removeBlack(
        {
          onError: (errCode: number, errMsg: string) => {
            error('FriendshipManager', `removeBlack failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('FriendshipManager', `removeBlack success`);
            resolve(data);
          }
        },
        operationID,
        userID
      );
    });
  }
}
