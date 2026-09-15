/**
 * OpenIM SDK for HarmonyOS
 * 好友管理器 - 处理好友相关操作
 */

import im from 'libimsdk.so';
import { debug, error, info } from '../internal/log/Logger';
import { BaseCallback, CompletionCallback, FriendListener } from '../listeners/listener';
import { BaseCallbackWrapper, CompletionCallbackWrapper, decodeArray, decodeNumber, FriendListenerWrapper } from '../listeners/ListenerImpl';
import { BlackInfo, FriendApplication, FriendshipInfo, FriendInfo } from '../models/entity';
import { toArray, toString } from '../utils/JsonUtil';
import { buildOperationID } from '../utils/Utils';


/**
 * 好友管理器
 * 提供好友查询、添加、管理等操作
 */
export class FriendshipManager {
  /**
   * 设置好友监听器
   * @param listener 好友监听器
   */
  setFriendListener(listener: FriendListener): void {
    im.setFriendListener(new FriendListenerWrapper(listener));
  }

  /**
   * 获取好友列表
   * @param callback 回调
   * @param operationID 操作ID
   * @param filterBlack 是否过滤黑名单
   */
  getFriendList(callback: BaseCallback<FriendInfo[]>, operationID: string, filterBlack: boolean = false): void {
    debug('FriendshipManager', `getFriendList, filterBlack: ${filterBlack}, operationID: ${operationID}`);

    im.getFriendList(
      new BaseCallbackWrapper(callback, decodeArray<FriendInfo>),
      operationID,
      filterBlack
    );
  }

  /**
   * 分页获取好友列表
   * @param callback 回调
   * @param operationID 操作ID
   * @param offset 偏移量
   * @param count 数量
   * @param filterBlack 是否过滤黑名单
   */
  getFriendListPage(callback: BaseCallback<FriendInfo[]>, operationID: string, offset: number, count: number, filterBlack: boolean = false): void {
    debug('FriendshipManager', `getFriendListPage, offset: ${offset}, count: ${count}, operationID: ${operationID}`);

    im.getFriendListPage(
      new BaseCallbackWrapper(callback, decodeArray<FriendInfo>),
      operationID,
      offset,
      count,
      filterBlack
    );
  }

  /**
   * 获取指定好友信息
   * @param callback 回调
   * @param operationID 操作ID
   * @param userIDList 用户ID列表
   * @param ex 是否获取扩展信息
   */
  getSpecifiedFriendsInfo(callback: BaseCallback<FriendInfo[]>, operationID: string, userIDList: string[], ex: boolean = false): void {
    debug('FriendshipManager', `getSpecifiedFriendsInfo, operationID: ${operationID}`);

    im.getSpecifiedFriendsInfo(
      new BaseCallbackWrapper(callback, decodeArray<FriendInfo>),
      operationID,
      toString(userIDList),
      ex
    );
  }

  /**
   * 搜索好友
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 搜索参数JSON
   */
  searchFriends(callback: BaseCallback<FriendInfo[]>, operationID: string, params: string): void {
    debug('FriendshipManager', `searchFriends, operationID: ${operationID}`);

    im.searchFriends(
      new BaseCallbackWrapper(callback, decodeArray<FriendInfo>),
      operationID,
      params
    );
  }

  /**
   * 添加好友
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 添加参数JSON
   */
  addFriend(callback: CompletionCallback, operationID: string, params: string): void {
    debug('FriendshipManager', `addFriend, operationID: ${operationID}`);

    im.addFriend(
      new CompletionCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 检查好友关系
   * @param callback 回调
   * @param operationID 操作ID
   * @param userIDList 用户ID列表
   */
  checkFriend(callback: BaseCallback<FriendshipInfo[]>, operationID: string, userIDList: string[]): void {
    debug('FriendshipManager', `checkFriend, operationID: ${operationID}`);

    im.checkFriend(
      new BaseCallbackWrapper(callback, decodeArray<FriendshipInfo>),
      operationID,
      toString(userIDList)
    );
  }

  /**
   * 更新好友信息
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 更新参数JSON
   */
  updateFriends(callback: CompletionCallback, operationID: string, params: string): void {
    debug('FriendshipManager', `updateFriends, operationID: ${operationID}`);

    im.updateFriends(
      new CompletionCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 获取未处理好友申请数量
   * @param callback 回调
   * @param operationID 操作ID
   */
  getFriendApplicationUnhandledCount(callback: BaseCallback<number>, operationID: string): void {
    debug('FriendshipManager', `getFriendApplicationUnhandledCount, operationID: ${operationID}`);

    im.getFriendApplicationUnhandledCount(
      new BaseCallbackWrapper(callback, decodeNumber),
      operationID,
      "{}"
    );
  }

  /**
   * 删除好友
   * @param callback 回调
   * @param operationID 操作ID
   * @param friendUserID 好友用户ID
   */
  deleteFriend(callback: CompletionCallback, operationID: string, friendUserID: string): void {
    debug('FriendshipManager', `deleteFriend: ${friendUserID}, operationID: ${operationID}`);

    im.deleteFriend(
      new CompletionCallbackWrapper(callback),
      operationID,
      friendUserID
    );
  }

  /**
   * 设置好友备注
   * @param callback 回调
   * @param operationID 操作ID
   * @param toUserID 用户ID
   * @param remark 备注
   */
  setFriendRemark(callback: CompletionCallback, operationID: string, toUserID: string, remark: string): void {
    debug('FriendshipManager', `setFriendRemark: ${toUserID}, remark: ${remark}, operationID: ${operationID}`);

    im.setFriendRemark(
      new CompletionCallbackWrapper(callback),
      operationID,
      toUserID,
      remark
    );
  }

  /**
   * 获取作为申请人的好友申请列表
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 查询参数JSON
   */
  getFriendApplicationListAsApplicant(callback: BaseCallback<FriendApplication[]>, operationID: string, params: string): void {
    debug('FriendshipManager', `getFriendApplicationListAsApplicant, operationID: ${operationID}`);

    im.getFriendApplicationListAsApplicant(
      new BaseCallbackWrapper(callback, decodeArray<FriendApplication>),
      operationID,
      params
    );
  }

  /**
   * 获取作为接收人的好友申请列表
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 查询参数JSON
   */
  getFriendApplicationListAsRecipient(callback: BaseCallback<FriendApplication[]>, operationID: string, params: string): void {
    debug('FriendshipManager', `getFriendApplicationListAsRecipient, operationID: ${operationID}`);

    im.getFriendApplicationListAsRecipient(
      new BaseCallbackWrapper(callback, decodeArray<FriendApplication>),
      operationID,
      params
    );
  }

  /**
   * 接受好友申请
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 接受参数JSON
   */
  acceptFriendApplication(callback: CompletionCallback, operationID: string, params: string): void {
    debug('FriendshipManager', `acceptFriendApplication, operationID: ${operationID}`);

    im.acceptFriendApplication(
      new CompletionCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 拒绝好友申请
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 拒绝参数JSON
   */
  refuseFriendApplication(callback: CompletionCallback, operationID: string, params: string): void {
    debug('FriendshipManager', `refuseFriendApplication, operationID: ${operationID}`);

    im.refuseFriendApplication(
      new CompletionCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 添加黑名单
   * @param callback 回调
   * @param operationID 操作ID
   * @param toUserID 用户ID
   * @param ex 扩展信息
   */
  addBlack(callback: CompletionCallback, operationID: string, toUserID: string, ex: string = ""): void {
    debug('FriendshipManager', `addBlack: ${toUserID}, operationID: ${operationID}`);

    im.addBlack(
      new CompletionCallbackWrapper(callback),
      operationID,
      toUserID,
      ex
    );
  }

  /**
   * 获取黑名单
   * @param callback 回调
   * @param operationID 操作ID
   */
  getBlackList(callback: BaseCallback<BlackInfo[]>, operationID: string): void {
    debug('FriendshipManager', `getBlackList, operationID: ${operationID}`);

    im.getBlackList(
      new BaseCallbackWrapper(callback, decodeArray<BlackInfo>),
      operationID
    );
  }

  /**
   * 移除黑名单
   * @param callback 回调
   * @param operationID 操作ID
   * @param userID 用户ID
   */
  removeBlack(callback: CompletionCallback, operationID: string, userID: string): void {
    debug('FriendshipManager', `removeBlack: ${userID}, operationID: ${operationID}`);

    im.removeBlack(
      new CompletionCallbackWrapper(callback),
      operationID,
      userID
    );
  }
}
