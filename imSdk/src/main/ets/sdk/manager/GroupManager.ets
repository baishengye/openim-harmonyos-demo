/**
 * OpenIM SDK for HarmonyOS
 * 群组管理器 - 处理群组相关操作
 */

import im from 'libimsdk.so';
import { debug, error, info } from '../internal/log/Logger';
import { GroupApplication, GroupInfo, GroupMemberInfo } from '../models/entity';
import { toArray, toObject, toString } from '../utils/JsonUtil';
import { buildOperationID } from '../utils/Utils';


/**
 * 群组管理器
 * 提供群组查询、创建、管理等操作
 */
export class GroupManager {
  /**
   * 创建群组
   * @param params 创建参数JSON
   * @returns 群组信息
   */
  createGroup(params: string): Promise<GroupInfo> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `createGroup, operationID: ${operationID}`);

      im.createGroup(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `createGroup failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `createGroup success`);
            resolve(toObject<GroupInfo>(data) as GroupInfo);
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 加入群组
   * @param groupID 群组ID
   * @param reqMsg 申请消息
   * @param joinSource 加入来源
   * @param ex 扩展信息
   * @returns 加入结果
   */
  joinGroup(groupID: string, reqMsg: string = "", joinSource: number = 2, ex: string = ""): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `joinGroup: ${groupID}, operationID: ${operationID}`);

      im.joinGroup(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `joinGroup failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `joinGroup success`);
            resolve(data);
          }
        },
        operationID,
        groupID,
        reqMsg,
        joinSource,
        ex
      );
    });
  }

  /**
   * 退出群组
   * @param groupID 群组ID
   * @returns 退出结果
   */
  quitGroup(groupID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `quitGroup: ${groupID}, operationID: ${operationID}`);

      im.quitGroup(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `quitGroup failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `quitGroup success`);
            resolve(data);
          }
        },
        operationID,
        groupID
      );
    });
  }

  /**
   * 解散群组
   * @param groupID 群组ID
   * @returns 解散结果
   */
  dismissGroup(groupID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `dismissGroup: ${groupID}, operationID: ${operationID}`);

      im.dismissGroup(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `dismissGroup failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `dismissGroup success`);
            resolve(data);
          }
        },
        operationID,
        groupID
      );
    });
  }

  /**
   * 获取已加入的群组列表
   * @returns 群组列表
   */
  getJoinedGroupList(): Promise<GroupInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getJoinedGroupList, operationID: ${operationID}`);

      im.getJoinedGroupList(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getJoinedGroupList failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getJoinedGroupList success`);
            resolve(toArray<GroupInfo>(data));
          }
        },
        operationID
      );
    });
  }

  /**
   * 分页获取已加入的群组列表
   * @param offset 偏移量
   * @param count 数量
   * @returns 群组列表
   */
  getJoinedGroupListPage(offset: number, count: number): Promise<GroupInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getJoinedGroupListPage, offset: ${offset}, count: ${count}, operationID: ${operationID}`);

      im.getJoinedGroupListPage(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getJoinedGroupListPage failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getJoinedGroupListPage success`);
            resolve(toArray<GroupInfo>(data));
          }
        },
        operationID,
        offset,
        count
      );
    });
  }

  /**
   * 获取指定群组信息
   * @param groupIDList 群组ID列表
   * @returns 群组信息列表
   */
  getSpecifiedGroupsInfo(groupIDList: string[]): Promise<GroupInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getSpecifiedGroupsInfo, count: ${groupIDList.length}, operationID: ${operationID}`);

      im.getSpecifiedGroupsInfo(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getSpecifiedGroupsInfo failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getSpecifiedGroupsInfo success`);
            resolve(toArray<GroupInfo>(data));
          }
        },
        operationID,
        toString(groupIDList)
      );
    });
  }

  /**
   * 获取群成员列表
   * @param groupID 群组ID
   * @param filter 过滤类型
   * @param offset 偏移量
   * @param count 数量
   * @returns 群成员列表
   */
  getGroupMemberList(groupID: string, filter: number, offset: number, count: number): Promise<GroupMemberInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getGroupMemberList: ${groupID}, operationID: ${operationID}`);

      im.getGroupMemberList(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getGroupMemberList failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getGroupMemberList success`);
            resolve(toArray<GroupMemberInfo>(data));
          }
        },
        operationID,
        groupID,
        filter,
        offset,
        count
      );
    });
  }

  /**
   * 获取群主和管理员
   * @param groupID 群组ID
   * @returns 群成员列表
   */
  getGroupMemberOwnerAndAdmin(groupID: string): Promise<GroupMemberInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getGroupMemberOwnerAndAdmin: ${groupID}, operationID: ${operationID}`);

      im.getGroupMemberOwnerAndAdmin(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getGroupMemberOwnerAndAdmin failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getGroupMemberOwnerAndAdmin success`);
            resolve(toArray<GroupMemberInfo>(data));
          }
        },
        operationID,
        groupID
      );
    });
  }

  /**
   * 获取指定群成员信息
   * @param groupID 群组ID
   * @param userIDList 用户ID列表
   * @returns 群成员列表
   */
  getSpecifiedGroupMembersInfo(groupID: string, userIDList: string[]): Promise<GroupMemberInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getSpecifiedGroupMembersInfo: ${groupID}, count: ${userIDList.length}, operationID: ${operationID}`);

      im.getSpecifiedGroupMembersInfo(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getSpecifiedGroupMembersInfo failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getSpecifiedGroupMembersInfo success`);
            resolve(toArray<GroupMemberInfo>(data));
          }
        },
        operationID,
        groupID,
        toString(userIDList)
      );
    });
  }

  /**
   * 获取群内指定用户
   * @param groupID 群组ID
   * @param userIDList 用户ID列表
   * @returns 群成员列表
   */
  getUsersInGroup(groupID: string, userIDList: string[]): Promise<GroupMemberInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getUsersInGroup: ${groupID}, count: ${userIDList.length}, operationID: ${operationID}`);

      im.getUsersInGroup(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getUsersInGroup failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getUsersInGroup success`);
            resolve(toArray<GroupMemberInfo>(data));
          }
        },
        operationID,
        groupID,
        toString(userIDList)
      );
    });
  }

  /**
   * 搜索群成员
   * @param params 搜索参数JSON
   * @returns 群成员列表
   */
  searchGroupMembers(params: string): Promise<GroupMemberInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `searchGroupMembers, operationID: ${operationID}`);

      im.searchGroupMembers(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `searchGroupMembers failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `searchGroupMembers success`);
            resolve(toArray<GroupMemberInfo>(data));
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 设置群组信息
   * @param params 群组信息JSON
   * @returns 设置结果
   */
  setGroupInfo(params: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `setGroupInfo, operationID: ${operationID}`);

      im.setGroupInfo(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `setGroupInfo failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `setGroupInfo success`);
            resolve(data);
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 更改群组禁言状态
   * @param groupID 群组ID
   * @param isMute 是否禁言
   * @returns 设置结果
   */
  changeGroupMute(groupID: string, isMute: boolean): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `changeGroupMute: ${groupID}, isMute: ${isMute}, operationID: ${operationID}`);

      im.changeGroupMute(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `changeGroupMute failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `changeGroupMute success`);
            resolve(data);
          }
        },
        operationID,
        groupID,
        isMute
      );
    });
  }

  /**
   * 更改群成员禁言状态
   * @param groupID 群组ID
   * @param userID 用户ID
   * @param mutedSeconds 禁言时长（秒）
   * @returns 设置结果
   */
  changeGroupMemberMute(groupID: string, userID: string, mutedSeconds: number): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `changeGroupMemberMute: ${groupID}, userID: ${userID}, mutedSeconds: ${mutedSeconds}, operationID: ${operationID}`);

      im.changeGroupMemberMute(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `changeGroupMemberMute failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `changeGroupMemberMute success`);
            resolve(data);
          }
        },
        operationID,
        groupID,
        userID,
        mutedSeconds
      );
    });
  }

  /**
   * 设置群成员信息
   * @param params 群成员信息JSON
   * @returns 设置结果
   */
  setGroupMemberInfo(params: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `setGroupMemberInfo, operationID: ${operationID}`);

      im.setGroupMemberInfo(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `setGroupMemberInfo failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `setGroupMemberInfo success`);
            resolve(data);
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 邀请用户入群
   * @param groupID 群组ID
   * @param userIDList 用户ID列表
   * @param reason 原因
   * @returns 邀请结果
   */
  inviteUserToGroup(groupID: string, userIDList: string[], reason: string = ""): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `inviteUserToGroup: ${groupID}, operationID: ${operationID}`);

      im.inviteUserToGroup(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `inviteUserToGroup failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `inviteUserToGroup success`);
            resolve(data);
          }
        },
        operationID,
        groupID,
        toString(userIDList),
        reason
      );
    });
  }

  /**
   * 踢出群成员
   * @param groupID 群组ID
   * @param userIDList 用户ID列表
   * @param reason 原因
   * @returns 踢出结果
   */
  kickGroupMember(groupID: string, userIDList: string[], reason: string = ""): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `kickGroupMember: ${groupID}, operationID: ${operationID}`);

      im.kickGroupMember(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `kickGroupMember failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `kickGroupMember success`);
            resolve(data);
          }
        },
        operationID,
        groupID,
        toString(userIDList),
        reason
      );
    });
  }

  /**
   * 转让群主
   * @param groupID 群组ID
   * @param newOwnerUserID 新群主用户ID
   * @returns 转让结果
   */
  transferGroupOwner(groupID: string, newOwnerUserID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `transferGroupOwner: ${groupID}, newOwner: ${newOwnerUserID}, operationID: ${operationID}`);

      im.transferGroupOwner(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `transferGroupOwner failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `transferGroupOwner success`);
            resolve(data);
          }
        },
        operationID,
        groupID,
        newOwnerUserID
      );
    });
  }

  /**
   * 获取作为申请人的群申请列表
   * @param params 查询参数JSON
   * @returns 群申请列表
   */
  getGroupApplicationListAsApplicant(params: string): Promise<GroupApplication[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getGroupApplicationListAsApplicant, operationID: ${operationID}`);

      im.getGroupApplicationListAsApplicant(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getGroupApplicationListAsApplicant failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getGroupApplicationListAsApplicant success`);
            resolve(toArray<GroupApplication>(data));
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 获取作为接收人的群申请列表
   * @param params 查询参数JSON
   * @returns 群申请列表
   */
  getGroupApplicationListAsRecipient(params: string): Promise<GroupApplication[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getGroupApplicationListAsRecipient, operationID: ${operationID}`);

      im.getGroupApplicationListAsRecipient(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getGroupApplicationListAsRecipient failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getGroupApplicationListAsRecipient success`);
            resolve(toArray<GroupApplication>(data));
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 获取未处理群申请数量
   * @returns 未处理数量
   */
  getGroupApplicationUnhandledCount(): Promise<number> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getGroupApplicationUnhandledCount, operationID: ${operationID}`);

      im.getGroupApplicationUnhandledCount(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getGroupApplicationUnhandledCount failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getGroupApplicationUnhandledCount success: ${data}`);
            resolve(parseInt(data) || 0);
          }
        },
        operationID,
        "{}"
      );
    });
  }

  /**
   * 接受群申请
   * @param groupID 群组ID
   * @param userID 用户ID
   * @param handleMsg 处理消息
   * @returns 接受结果
   */
  acceptGroupApplication(groupID: string, userID: string, handleMsg: string = ""): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `acceptGroupApplication: ${groupID}, userID: ${userID}, operationID: ${operationID}`);

      im.acceptGroupApplication(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `acceptGroupApplication failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `acceptGroupApplication success`);
            resolve(data);
          }
        },
        operationID,
        groupID,
        userID,
        handleMsg
      );
    });
  }

  /**
   * 拒绝群申请
   * @param groupID 群组ID
   * @param userID 用户ID
   * @param handleMsg 处理消息
   * @returns 拒绝结果
   */
  refuseGroupApplication(groupID: string, userID: string, handleMsg: string = ""): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `refuseGroupApplication: ${groupID}, userID: ${userID}, operationID: ${operationID}`);

      im.refuseGroupApplication(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `refuseGroupApplication failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `refuseGroupApplication success`);
            resolve(data);
          }
        },
        operationID,
        groupID,
        userID,
        handleMsg
      );
    });
  }

  /**
   * 搜索群组
   * @param params 搜索参数JSON
   * @returns 群组列表
   */
  searchGroups(params: string): Promise<GroupInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `searchGroups, operationID: ${operationID}`);

      im.searchGroups(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `searchGroups failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `searchGroups success`);
            resolve(toArray<GroupInfo>(data));
          }
        },
        operationID,
        params
      );
    });
  }

  /**
   * 按加入时间过滤获取群成员列表
   * @param groupID 群组ID
   * @param offset 偏移量
   * @param count 数量
   * @param joinTimeBegin 开始时间
   * @param joinTimeEnd 结束时间
   * @param filterUserIDList 过滤用户ID列表
   * @returns 群成员列表
   */
  getGroupMemberListByJoinTimeFilter(
    groupID: string,
    offset: number,
    count: number,
    joinTimeBegin: number,
    joinTimeEnd: number,
    filterUserIDList: string[]
  ): Promise<GroupMemberInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `getGroupMemberListByJoinTimeFilter: ${groupID}, operationID: ${operationID}`);

      im.getGroupMemberListByJoinTimeFilter(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `getGroupMemberListByJoinTimeFilter failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `getGroupMemberListByJoinTimeFilter success`);
            resolve(toArray<GroupMemberInfo>(data));
          }
        },
        operationID,
        groupID,
        offset,
        count,
        joinTimeBegin,
        joinTimeEnd,
        toString(filterUserIDList)
      );
    });
  }

  /**
   * 检查是否已加入群组
   * @param groupID 群组ID
   * @returns 是否已加入
   */
  isJoinGroup(groupID: string): Promise<boolean> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('GroupManager', `isJoinGroup: ${groupID}, operationID: ${operationID}`);

      im.isJoinGroup(
        {
          onError: (errCode: number, errMsg: string) => {
            error('GroupManager', `isJoinGroup failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('GroupManager', `isJoinGroup success: ${data}`);
            resolve(data === "true" || data === "1");
          }
        },
        operationID,
        groupID
      );
    });
  }
}
