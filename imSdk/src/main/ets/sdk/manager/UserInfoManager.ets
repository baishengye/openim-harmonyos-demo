/**
 * OpenIM SDK for HarmonyOS
 * 用户信息管理器 - 处理用户相关操作
 */

import im from 'libimsdk.so';
import { debug, error, info } from '../internal/log/Logger';
import { BaseCallback, UserListener } from '../listeners/listener';
import { BaseCallbackWrapper, UserListenerWrapper } from '../listeners/ListenerImpl';
import { SubscribeUsersStatus, UserInfo, UserStatus } from '../models/entity';
import { toArray, toString } from '../utils/JsonUtil';
import { buildOperationID } from '../utils/Utils';


/**
 * 用户信息管理器
 * 提供用户信息查询、设置、状态订阅等操作
 */
export class UserInfoManager {
  /**
   * 设置用户监听器
   * @param listener 用户监听器
   */
  setUserListener(listener: UserListener): void {
    im.setUserListener(new UserListenerWrapper(listener));
  }

  /**
   * 获取指定用户信息
   * @param callback 回调
   * @param operationID 操作ID
   * @param userIDList 用户ID列表
   */
  getUsersInfo(callback: BaseCallback<UserInfo[]>, operationID: string, userIDList: string[]): void {
    debug('UserInfoManager', `getUsersInfo, operationID: ${operationID}`);

    im.getUsersInfo(
      new BaseCallbackWrapper(callback),
      operationID,
      toString(userIDList)
    );
  }

  /**
   * 获取当前用户信息
   * @param callback 回调
   * @param operationID 操作ID
   */
  getSelfUserInfo(callback: BaseCallback<UserInfo>, operationID: string): void {
    debug('UserInfoManager', `getSelfUserInfo, operationID: ${operationID}`);

    im.getSelfUserInfo(
      new BaseCallbackWrapper(callback),
      operationID
    );
  }

  /**
   * 设置当前用户信息
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 用户信息JSON
   */
  setSelfInfo(callback: BaseCallback<string>, operationID: string, params: string): void {
    debug('UserInfoManager', `setSelfInfo, operationID: ${operationID}`);

    im.setSelfInfo(
      new BaseCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 设置当前用户昵称
   * @param callback 回调
   * @param operationID 操作ID
   * @param nickname 昵称
   */
  setSelfNickname(callback: BaseCallback<string>, operationID: string, nickname: string): void {
    debug('UserInfoManager', `setSelfNickname: ${nickname}, operationID: ${operationID}`);

    im.setSelfInfo(
      new BaseCallbackWrapper(callback),
      operationID,
      JSON.stringify({ nickname: nickname })
    );
  }

  /**
   * 设置当前用户头像
   * @param callback 回调
   * @param operationID 操作ID
   * @param faceUrl 头像URL
   */
  setSelfFaceURL(callback: BaseCallback<string>, operationID: string, faceUrl: string): void {
    debug('UserInfoManager', `setSelfFaceURL: ${faceUrl}, operationID: ${operationID}`);

    im.setSelfInfo(
      new BaseCallbackWrapper(callback),
      operationID,
      JSON.stringify({ faceUrl: faceUrl })
    );
  }

  /**
   * 获取用户状态
   * @param callback 回调
   * @param operationID 操作ID
   * @param userIDList 用户ID列表
   */
  getUserStatus(callback: BaseCallback<UserStatus[]>, operationID: string, userIDList: string[]): void {
    debug('UserInfoManager', `getUserStatus, operationID: ${operationID}`);

    im.getUserStatus(
      new BaseCallbackWrapper(callback),
      operationID,
      toString(userIDList)
    );
  }

  /**
   * 订阅用户状态
   * @param callback 回调
   * @param operationID 操作ID
   * @param userIDList 用户ID列表
   */
  subscribeUsersStatus(callback: BaseCallback<SubscribeUsersStatus[]>, operationID: string, userIDList: string[]): void {
    debug('UserInfoManager', `subscribeUsersStatus, operationID: ${operationID}`);

    im.subscribeUsersStatus(
      new BaseCallbackWrapper(callback),
      operationID,
      toString(userIDList)
    );
  }

  /**
   * 取消订阅用户状态
   * @param callback 回调
   * @param operationID 操作ID
   * @param userIDList 用户ID列表
   */
  unsubscribeUsersStatus(callback: BaseCallback<string>, operationID: string, userIDList: string[]): void {
    debug('UserInfoManager', `unsubscribeUsersStatus, operationID: ${operationID}`);

    im.unsubscribeUsersStatus(
      new BaseCallbackWrapper(callback),
      operationID,
      toString(userIDList)
    );
  }
}
