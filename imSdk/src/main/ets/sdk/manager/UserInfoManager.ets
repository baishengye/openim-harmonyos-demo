/**
 * OpenIM SDK for HarmonyOS
 * 用户信息管理器 - 处理用户相关操作
 */

import im from 'libimsdk.so';
import { debug, error, info } from '../internal/log/Logger';
import { BaseCallback, CompletionCallback, UserListener } from '../listeners/listener';
import { BaseCallbackWrapper, CompletionCallbackWrapper, decodeArray, decodeObject, UserListenerWrapper } from '../listeners/ListenerImpl';
import { SubscribeUsersStatus, UserCommand, UserInfo, UsersOnlineStatus } from '../models/entity';
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

  addUserCommand(callback: CompletionCallback, operationID: string, commandType: number,
    uuid: string, value: string): void {
    im.addUserCommand(new CompletionCallbackWrapper(callback), operationID, commandType, uuid, value);
  }

  deleteUserCommand(callback: CompletionCallback, operationID: string, commandType: number, uuid: string): void {
    im.deleteUserCommand(new CompletionCallbackWrapper(callback), operationID, commandType, uuid);
  }

  getAllUserCommands(callback: BaseCallback<UserCommand[]>, operationID: string, commandType: number): void {
    im.getAllUserCommands(new BaseCallbackWrapper(callback, decodeArray<UserCommand>), operationID, commandType);
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
      new BaseCallbackWrapper(callback, decodeArray<UserInfo>),
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
      new BaseCallbackWrapper(callback, decodeObject<UserInfo>),
      operationID
    );
  }

  /**
   * 设置当前用户信息
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 用户信息JSON
   */
  setSelfInfo(callback: CompletionCallback, operationID: string, params: string): void {
    debug('UserInfoManager', `setSelfInfo, operationID: ${operationID}`);

    im.setSelfInfo(
      new CompletionCallbackWrapper(callback),
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
  setSelfNickname(callback: CompletionCallback, operationID: string, nickname: string): void {
    debug('UserInfoManager', `setSelfNickname: ${nickname}, operationID: ${operationID}`);

    im.setSelfInfo(
      new CompletionCallbackWrapper(callback),
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
  setSelfFaceURL(callback: CompletionCallback, operationID: string, faceUrl: string): void {
    debug('UserInfoManager', `setSelfFaceURL: ${faceUrl}, operationID: ${operationID}`);

    im.setSelfInfo(
      new CompletionCallbackWrapper(callback),
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
  getUserStatus(callback: BaseCallback<UsersOnlineStatus[]>, operationID: string, userIDList: string[]): void {
    debug('UserInfoManager', `getUserStatus, operationID: ${operationID}`);

    im.getUserStatus(
      new BaseCallbackWrapper(callback, decodeArray<UsersOnlineStatus>),
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
      new BaseCallbackWrapper(callback, decodeArray<SubscribeUsersStatus>),
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
  unsubscribeUsersStatus(callback: CompletionCallback, operationID: string, userIDList: string[]): void {
    debug('UserInfoManager', `unsubscribeUsersStatus, operationID: ${operationID}`);

    im.unsubscribeUsersStatus(
      new CompletionCallbackWrapper(callback),
      operationID,
      toString(userIDList)
    );
  }

  /** 获取已经订阅用户的在线状态。 */
  getSubscribeUsersStatus(callback: BaseCallback<UsersOnlineStatus[]>, operationID: string): void {
    debug('UserInfoManager', `getSubscribeUsersStatus, operationID: ${operationID}`);
    im.getSubscribeUsersStatus(new BaseCallbackWrapper(callback, decodeArray<UsersOnlineStatus>), operationID);
  }

  /** 通知 SDK 当前应用前后台状态。 */
  setAppBackgroundStatus(callback: CompletionCallback, operationID: string, isBackground: boolean): void {
    debug('UserInfoManager', `setAppBackgroundStatus: ${isBackground}, operationID: ${operationID}`);
    im.setAppBackgroundStatus(new CompletionCallbackWrapper(callback), operationID, isBackground);
  }

  /** 通知 SDK 网络状态发生变化并触发重连检查。 */
  networkStatusChanged(callback: CompletionCallback, operationID: string): void {
    debug('UserInfoManager', `networkStatusChanged, operationID: ${operationID}`);
    im.networkStatusChanged(new CompletionCallbackWrapper(callback), operationID);
  }
}
