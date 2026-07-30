/**
 * OpenIM SDK for HarmonyOS
 * 用户信息管理器 - 处理用户相关操作
 */

import im from 'libimsdk.so';
import { debug, error, info } from '../internal/log/Logger';
import { SubscribeUsersStatus, UserInfo, UserStatus } from '../models/entity';
import { toArray, toString } from '../utils/JsonUtil';
import { buildOperationID } from '../utils/Utils';


/**
 * 用户信息管理器
 * 提供用户信息查询、设置、状态订阅等操作
 */
export class UserInfoManager {
  /**
   * 获取指定用户信息
   * @param userIDList 用户ID列表
   * @param ex 是否获取扩展信息
   * @returns 用户信息列表
   */
  getUsersInfo(userIDList: string[], ex: boolean = false): Promise<UserInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('UserInfoManager', `getUsersInfo, operationID: ${operationID}`);

      im.getUsersInfo(
        {
          onError: (errCode: number, errMsg: string) => {
            error('UserInfoManager', `getUsersInfo failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('UserInfoManager', `getUsersInfo success`);
            resolve(toArray<UserInfo>(data));
          }
        },
        operationID,
        toString(userIDList)
      );
    });
  }

  /**
   * 获取当前用户信息
   * @returns 当前用户信息
   */
  getSelfUserInfo(): Promise<UserInfo> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('UserInfoManager', `getSelfUserInfo, operationID: ${operationID}`);

      im.getSelfUserInfo(
        {
          onError: (errCode: number, errMsg: string) => {
            error('UserInfoManager', `getSelfUserInfo failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('UserInfoManager', `getSelfUserInfo success`);
            const userInfo = toArray<UserInfo>(data);
            resolve(userInfo.length > 0 ? userInfo[0] : new UserInfo());
          }
        },
        operationID
      );
    });
  }

  /**
   * 设置当前用户信息
   * @param params 用户信息JSON字符串
   * @returns 设置结果
   */
  setSelfInfo(params: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('UserInfoManager', `setSelfInfo, operationID: ${operationID}`);

      im.setSelfInfo(
        {
          onError: (errCode: number, errMsg: string) => {
            error('UserInfoManager', `setSelfInfo failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('UserInfoManager', `setSelfInfo success`);
            resolve(data);
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 设置当前用户昵称
   * @param nickname 昵称
   * @returns 设置结果
   */
  setSelfNickname(nickname: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('UserInfoManager', `setSelfNickname: ${nickname}, operationID: ${operationID}`);

      im.setSelfInfo(
        {
          onError: (errCode: number, errMsg: string) => {
            error('UserInfoManager', `setSelfNickname failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('UserInfoManager', `setSelfNickname success`);
            resolve(data);
          }
        },
        operationID,
        JSON.stringify({ nickname: nickname })
      );
    });
  }

  /**
   * 设置当前用户头像
   * @param faceUrl 头像URL
   * @returns 设置结果
   */
  setSelfFaceURL(faceUrl: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('UserInfoManager', `setSelfFaceURL: ${faceUrl}, operationID: ${operationID}`);

      im.setSelfInfo(
        {
          onError: (errCode: number, errMsg: string) => {
            error('UserInfoManager', `setSelfFaceURL failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('UserInfoManager', `setSelfFaceURL success`);
            resolve(data);
          }
        },
        operationID,
        JSON.stringify({ faceUrl: faceUrl })
      );
    });
  }

  /**
   * 获取用户状态
   * @param userIDList 用户ID列表
   * @returns 用户状态列表
   */
  getUserStatus(userIDList: string[]): Promise<UserStatus[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('UserInfoManager', `getUserStatus, operationID: ${operationID}`);

      im.getUserStatus(
        {
          onError: (errCode: number, errMsg: string) => {
            error('UserInfoManager', `getUserStatus failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('UserInfoManager', `getUserStatus success`);
            resolve(toArray<UserStatus>(data));
          }
        },
        operationID,
        toString(userIDList)
      );
    });
  }

  /**
   * 订阅用户状态
   * @param userIDList 用户ID列表
   * @returns 订阅状态列表
   */
  subscribeUsersStatus(userIDList: string[]): Promise<SubscribeUsersStatus[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('UserInfoManager', `subscribeUsersStatus, operationID: ${operationID}`);

      im.subscribeUsersStatus(
        {
          onError: (errCode: number, errMsg: string) => {
            error('UserInfoManager', `subscribeUsersStatus failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('UserInfoManager', `subscribeUsersStatus success`);
            resolve(toArray<SubscribeUsersStatus>(data));
          }
        },
        operationID,
        toString(userIDList)
      );
    });
  }

  /**
   * 取消订阅用户状态
   * @param userIDList 用户ID列表
   * @returns 取消结果
   */
  unsubscribeUsersStatus(userIDList: string[]): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('UserInfoManager', `unsubscribeUsersStatus, operationID: ${operationID}`);

      im.unsubscribeUsersStatus(
        {
          onError: (errCode: number, errMsg: string) => {
            error('UserInfoManager', `unsubscribeUsersStatus failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('UserInfoManager', `unsubscribeUsersStatus success`);
            resolve(data);
          }
        },
        operationID,
        toString(userIDList)
      );
    });
  }
}
