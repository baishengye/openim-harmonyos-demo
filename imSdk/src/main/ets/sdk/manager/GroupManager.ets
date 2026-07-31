/**
 * OpenIM SDK for HarmonyOS
 * 群组管理器 - 处理群组相关操作
 */

import im from 'libimsdk.so';
import { debug, error, info } from '../internal/log/Logger';
import { BaseCallback, GroupListener } from '../listeners/listener';
import { BaseCallbackWrapper, GroupListenerWrapper } from '../listeners/ListenerImpl';
import { GroupApplication, GroupInfo, GroupMemberInfo } from '../models/entity';
import { toArray, toObject, toString } from '../utils/JsonUtil';
import { buildOperationID } from '../utils/Utils';


/**
 * 群组管理器
 * 提供群组查询、创建、管理等操作
 */
export class GroupManager {
  /**
   * 设置群组监听器
   * @param listener 群组监听器
   */
  setGroupListener(listener: GroupListener): void {
    im.setGroupListener(new GroupListenerWrapper(listener));
  }

  /**
   * 创建群组
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 创建参数JSON
   */
  createGroup(callback: BaseCallback<GroupInfo>, operationID: string, params: string): void {
    debug('GroupManager', `createGroup, operationID: ${operationID}`);

    im.createGroup(
      new BaseCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 加入群组
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param reqMsg 申请消息
   * @param joinSource 加入来源
   * @param ex 扩展信息
   */
  joinGroup(callback: BaseCallback<string>, operationID: string, groupID: string, reqMsg: string = "", joinSource: number = 2, ex: string = ""): void {
    debug('GroupManager', `joinGroup: ${groupID}, operationID: ${operationID}`);

    im.joinGroup(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      reqMsg,
      joinSource,
      ex
    );
  }

  /**
   * 退出群组
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   */
  quitGroup(callback: BaseCallback<string>, operationID: string, groupID: string): void {
    debug('GroupManager', `quitGroup: ${groupID}, operationID: ${operationID}`);

    im.quitGroup(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID
    );
  }

  /**
   * 解散群组
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   */
  dismissGroup(callback: BaseCallback<string>, operationID: string, groupID: string): void {
    debug('GroupManager', `dismissGroup: ${groupID}, operationID: ${operationID}`);

    im.dismissGroup(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID
    );
  }

  /**
   * 获取已加入的群组列表
   * @param callback 回调
   * @param operationID 操作ID
   */
  getJoinedGroupList(callback: BaseCallback<GroupInfo[]>, operationID: string): void {
    debug('GroupManager', `getJoinedGroupList, operationID: ${operationID}`);

    im.getJoinedGroupList(
      new BaseCallbackWrapper(callback),
      operationID
    );
  }

  /**
   * 分页获取已加入的群组列表
   * @param callback 回调
   * @param operationID 操作ID
   * @param offset 偏移量
   * @param count 数量
   */
  getJoinedGroupListPage(callback: BaseCallback<GroupInfo[]>, operationID: string, offset: number, count: number): void {
    debug('GroupManager', `getJoinedGroupListPage, offset: ${offset}, count: ${count}, operationID: ${operationID}`);

    im.getJoinedGroupListPage(
      new BaseCallbackWrapper(callback),
      operationID,
      offset,
      count
    );
  }

  /**
   * 获取指定群组信息
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupIDList 群组ID列表
   */
  getSpecifiedGroupsInfo(callback: BaseCallback<GroupInfo[]>, operationID: string, groupIDList: string[]): void {
    debug('GroupManager', `getSpecifiedGroupsInfo, count: ${groupIDList.length}, operationID: ${operationID}`);

    im.getSpecifiedGroupsInfo(
      new BaseCallbackWrapper(callback),
      operationID,
      toString(groupIDList)
    );
  }

  /**
   * 获取群成员列表
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param filter 过滤类型
   * @param offset 偏移量
   * @param count 数量
   */
  getGroupMemberList(callback: BaseCallback<GroupMemberInfo[]>, operationID: string, groupID: string, filter: number, offset: number, count: number): void {
    debug('GroupManager', `getGroupMemberList: ${groupID}, operationID: ${operationID}`);

    im.getGroupMemberList(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      filter,
      offset,
      count
    );
  }

  /**
   * 获取群主和管理员
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   */
  getGroupMemberOwnerAndAdmin(callback: BaseCallback<GroupMemberInfo[]>, operationID: string, groupID: string): void {
    debug('GroupManager', `getGroupMemberOwnerAndAdmin: ${groupID}, operationID: ${operationID}`);

    im.getGroupMemberOwnerAndAdmin(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID
    );
  }

  /**
   * 获取指定群成员信息
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param userIDList 用户ID列表
   */
  getSpecifiedGroupMembersInfo(callback: BaseCallback<GroupMemberInfo[]>, operationID: string, groupID: string, userIDList: string[]): void {
    debug('GroupManager', `getSpecifiedGroupMembersInfo: ${groupID}, count: ${userIDList.length}, operationID: ${operationID}`);

    im.getSpecifiedGroupMembersInfo(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      toString(userIDList)
    );
  }

  /**
   * 获取群内指定用户
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param userIDList 用户ID列表
   */
  getUsersInGroup(callback: BaseCallback<GroupMemberInfo[]>, operationID: string, groupID: string, userIDList: string[]): void {
    debug('GroupManager', `getUsersInGroup: ${groupID}, count: ${userIDList.length}, operationID: ${operationID}`);

    im.getUsersInGroup(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      toString(userIDList)
    );
  }

  /**
   * 搜索群成员
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 搜索参数JSON
   */
  searchGroupMembers(callback: BaseCallback<GroupMemberInfo[]>, operationID: string, params: string): void {
    debug('GroupManager', `searchGroupMembers, operationID: ${operationID}`);

    im.searchGroupMembers(
      new BaseCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 设置群组信息
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 群组信息JSON
   */
  setGroupInfo(callback: BaseCallback<string>, operationID: string, params: string): void {
    debug('GroupManager', `setGroupInfo, operationID: ${operationID}`);

    im.setGroupInfo(
      new BaseCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 更改群组禁言状态
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param isMute 是否禁言
   */
  changeGroupMute(callback: BaseCallback<string>, operationID: string, groupID: string, isMute: boolean): void {
    debug('GroupManager', `changeGroupMute: ${groupID}, isMute: ${isMute}, operationID: ${operationID}`);

    im.changeGroupMute(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      isMute
    );
  }

  /**
   * 更改群成员禁言状态
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param userID 用户ID
   * @param mutedSeconds 禁言时长（秒）
   */
  changeGroupMemberMute(callback: BaseCallback<string>, operationID: string, groupID: string, userID: string, mutedSeconds: number): void {
    debug('GroupManager', `changeGroupMemberMute: ${groupID}, userID: ${userID}, mutedSeconds: ${mutedSeconds}, operationID: ${operationID}`);

    im.changeGroupMemberMute(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      userID,
      mutedSeconds
    );
  }

  /**
   * 设置群成员信息
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 群成员信息JSON
   */
  setGroupMemberInfo(callback: BaseCallback<string>, operationID: string, params: string): void {
    debug('GroupManager', `setGroupMemberInfo, operationID: ${operationID}`);

    im.setGroupMemberInfo(
      new BaseCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 邀请用户入群
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param userIDList 用户ID列表
   * @param reason 原因
   */
  inviteUserToGroup(callback: BaseCallback<string>, operationID: string, groupID: string, userIDList: string[], reason: string = ""): void {
    debug('GroupManager', `inviteUserToGroup: ${groupID}, operationID: ${operationID}`);

    im.inviteUserToGroup(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      toString(userIDList),
      reason
    );
  }

  /**
   * 踢出群成员
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param userIDList 用户ID列表
   * @param reason 原因
   */
  kickGroupMember(callback: BaseCallback<string>, operationID: string, groupID: string, userIDList: string[], reason: string = ""): void {
    debug('GroupManager', `kickGroupMember: ${groupID}, operationID: ${operationID}`);

    im.kickGroupMember(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      toString(userIDList),
      reason
    );
  }

  /**
   * 转让群主
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param newOwnerUserID 新群主用户ID
   */
  transferGroupOwner(callback: BaseCallback<string>, operationID: string, groupID: string, newOwnerUserID: string): void {
    debug('GroupManager', `transferGroupOwner: ${groupID}, newOwner: ${newOwnerUserID}, operationID: ${operationID}`);

    im.transferGroupOwner(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      newOwnerUserID
    );
  }

  /**
   * 获取作为申请人的群申请列表
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 查询参数JSON
   */
  getGroupApplicationListAsApplicant(callback: BaseCallback<GroupApplication[]>, operationID: string, params: string): void {
    debug('GroupManager', `getGroupApplicationListAsApplicant, operationID: ${operationID}`);

    im.getGroupApplicationListAsApplicant(
      new BaseCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 获取作为接收人的群申请列表
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 查询参数JSON
   */
  getGroupApplicationListAsRecipient(callback: BaseCallback<GroupApplication[]>, operationID: string, params: string): void {
    debug('GroupManager', `getGroupApplicationListAsRecipient, operationID: ${operationID}`);

    im.getGroupApplicationListAsRecipient(
      new BaseCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 获取未处理群申请数量
   * @param callback 回调
   * @param operationID 操作ID
   */
  getGroupApplicationUnhandledCount(callback: BaseCallback<number>, operationID: string): void {
    debug('GroupManager', `getGroupApplicationUnhandledCount, operationID: ${operationID}`);

    im.getGroupApplicationUnhandledCount(
      new BaseCallbackWrapper(callback),
      operationID,
      "{}"
    );
  }

  /**
   * 接受群申请
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param userID 用户ID
   * @param handleMsg 处理消息
   */
  acceptGroupApplication(callback: BaseCallback<string>, operationID: string, groupID: string, userID: string, handleMsg: string = ""): void {
    debug('GroupManager', `acceptGroupApplication: ${groupID}, userID: ${userID}, operationID: ${operationID}`);

    im.acceptGroupApplication(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      userID,
      handleMsg
    );
  }

  /**
   * 拒绝群申请
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param userID 用户ID
   * @param handleMsg 处理消息
   */
  refuseGroupApplication(callback: BaseCallback<string>, operationID: string, groupID: string, userID: string, handleMsg: string = ""): void {
    debug('GroupManager', `refuseGroupApplication: ${groupID}, userID: ${userID}, operationID: ${operationID}`);

    im.refuseGroupApplication(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      userID,
      handleMsg
    );
  }

  /**
   * 搜索群组
   * @param callback 回调
   * @param operationID 操作ID
   * @param params 搜索参数JSON
   */
  searchGroups(callback: BaseCallback<GroupInfo[]>, operationID: string, params: string): void {
    debug('GroupManager', `searchGroups, operationID: ${operationID}`);

    im.searchGroups(
      new BaseCallbackWrapper(callback),
      operationID,
      params
    );
  }

  /**
   * 按加入时间过滤获取群成员列表
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   * @param offset 偏移量
   * @param count 数量
   * @param joinTimeBegin 开始时间
   * @param joinTimeEnd 结束时间
   * @param filterUserIDList 过滤用户ID列表
   */
  getGroupMemberListByJoinTimeFilter(
    callback: BaseCallback<GroupMemberInfo[]>,
    operationID: string,
    groupID: string,
    offset: number,
    count: number,
    joinTimeBegin: number,
    joinTimeEnd: number,
    filterUserIDList: string[]
  ): void {
    debug('GroupManager', `getGroupMemberListByJoinTimeFilter: ${groupID}, operationID: ${operationID}`);

    im.getGroupMemberListByJoinTimeFilter(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID,
      offset,
      count,
      joinTimeBegin,
      joinTimeEnd,
      toString(filterUserIDList)
    );
  }

  /**
   * 检查是否已加入群组
   * @param callback 回调
   * @param operationID 操作ID
   * @param groupID 群组ID
   */
  isJoinGroup(callback: BaseCallback<boolean>, operationID: string, groupID: string): void {
    debug('GroupManager', `isJoinGroup: ${groupID}, operationID: ${operationID}`);

    im.isJoinGroup(
      new BaseCallbackWrapper(callback),
      operationID,
      groupID
    );
  }
}
