/**
 * OpenIM SDK for HarmonyOS
 * 会话管理器 - 处理会话相关操作
 */

import im from 'libimsdk.so';
import { buildOperationID } from './Utils';
import { debug, info, error } from './Logger';
import { toString, toObject, toArray } from './JsonUtil';

/**
 * 会话信息
 */
export class ConversationInfo {
  conversationID: string = "";
  conversationType: number = 0;
  userID: string = "";
  groupID: string = "";
  showName: string = "";
  faceUrl: string = "";
  latestMsg: string = "";
  latestMsgSendTime: number = 0;
  unreadCount: number = 0;
  isPinned: boolean = false;
  isPrivate: boolean = false;
  burnDuration: number = 0;
  isNotInGroup: boolean = false;
  updateUnreadCountTime: number = 0;
  draftText: string = "";
  groupAtInfoList: GroupAtInfo[] = [];
  msgSeq: number = 0;
  isMsgFilter: boolean = false;
  isSupportTyping: boolean = false;
  recvMsgOpt: number = 0;
}

/**
 * 群组@信息
 */
export class GroupAtInfo {
  groupID: string = "";
  atType: number = 0;
  seq: number = 0;
}

/**
 * 会话管理器
 * 提供会话查询、管理等操作
 */
export class ConversationManager {
  /**
   * 获取所有会话列表
   * @returns 会话列表
   */
  getAllConversationList(): Promise<ConversationInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `getAllConversationList, operationID: ${operationID}`);

      im.getAllConversationList(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `getAllConversationList failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `getAllConversationList success`);
            resolve(toArray<ConversationInfo>(data));
          }
        },
        operationID
      );
    });
  }

  /**
   * 分页获取会话列表
   * @param offset 偏移量
   * @param count 数量
   * @returns 会话列表
   */
  getConversationListSplit(offset: number, count: number): Promise<ConversationInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `getConversationListSplit, offset: ${offset}, count: ${count}, operationID: ${operationID}`);

      im.getConversationListSplit(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `getConversationListSplit failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `getConversationListSplit success`);
            resolve(toArray<ConversationInfo>(data));
          }
        },
        operationID,
        offset,
        count
      );
    });
  }

  /**
   * 获取单个会话
   * @param sessionType 会话类型
   * @param sourceID 来源ID
   * @returns 会话信息
   */
  getOneConversation(sessionType: number, sourceID: string): Promise<ConversationInfo> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `getOneConversation, sessionType: ${sessionType}, sourceID: ${sourceID}, operationID: ${operationID}`);

      im.getOneConversation(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `getOneConversation failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `getOneConversation success`);
            resolve(toObject<ConversationInfo>(data) as ConversationInfo);
          }
        },
        operationID,
        sessionType,
        sourceID
      );
    });
  }

  /**
   * 获取多个会话
   * @param conversationIDList 会话ID列表
   * @returns 会话列表
   */
  getMultipleConversation(conversationIDList: string[]): Promise<ConversationInfo[]> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `getMultipleConversation, count: ${conversationIDList.length}, operationID: ${operationID}`);

      im.getMultipleConversation(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `getMultipleConversation failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `getMultipleConversation success`);
            resolve(toArray<ConversationInfo>(data));
          }
        },
        operationID,
        toString(conversationIDList)
      );
    });
  }

  /**
   * 获取会话ID
   * @param sourceID 来源ID
   * @param sessionType 会话类型
   * @returns 会话ID
   */
  getConversationIDBySessionType(sourceID: string, sessionType: number): string {
    const operationID = buildOperationID();
    debug('ConversationManager', `getConversationIDBySessionType, sourceID: ${sourceID}, sessionType: ${sessionType}, operationID: ${operationID}`);
    return im.getConversationIDBySessionType(operationID, sourceID, sessionType);
  }

  /**
   * 获取未读消息总数
   * @returns 未读消息总数
   */
  getTotalUnreadMsgCount(): Promise<number> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `getTotalUnreadMsgCount, operationID: ${operationID}`);

      im.getTotalUnreadMsgCount(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `getTotalUnreadMsgCount failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `getTotalUnreadMsgCount success: ${data}`);
            resolve(parseInt(data) || 0);
          }
        },
        operationID
      );
    });
  }

  /**
   * 标记会话消息已读
   * @param conversationID 会话ID
   * @returns 标记结果
   */
  markConversationMessageAsRead(conversationID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `markConversationMessageAsRead: ${conversationID}, operationID: ${operationID}`);

      im.markConversationMessageAsRead(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `markConversationMessageAsRead failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `markConversationMessageAsRead success`);
            resolve(data);
          }
        },
        operationID,
        conversationID
      );
    });
  }

  /**
   * 设置会话属性
   * @param conversationID 会话ID
   * @param params 属性参数JSON
   * @returns 设置结果
   */
  setConversation(conversationID: string, params: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `setConversation: ${conversationID}, operationID: ${operationID}`);

      im.setConversation(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `setConversation failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `setConversation success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        params
      );
    });
  }

  /**
   * 设置会话草稿
   * @param conversationID 会话ID
   * @param draftText 草稿文本
   * @returns 设置结果
   */
  setConversationDraft(conversationID: string, draftText: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `setConversationDraft: ${conversationID}, draftText: ${draftText}, operationID: ${operationID}`);

      im.setConversationDraft(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `setConversationDraft failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `setConversationDraft success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        draftText
      );
    });
  }

  /**
   * 置顶/取消置顶会话
   * @param conversationID 会话ID
   * @param isPinned 是否置顶
   * @returns 设置结果
   */
  pinConversation(conversationID: string, isPinned: boolean): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `pinConversation: ${conversationID}, isPinned: ${isPinned}, operationID: ${operationID}`);

      im.pinConversation(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `pinConversation failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `pinConversation success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        isPinned
      );
    });
  }

  /**
   * 设置会话消息接收选项
   * @param conversationID 会话ID
   * @param opt 接收选项 (0: 正常, 1: 不接受消息, 2: 不接受通知)
   * @returns 设置结果
   */
  setConversationRecvMessageOpt(conversationID: string, opt: number): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `setConversationRecvMessageOpt: ${conversationID}, opt: ${opt}, operationID: ${operationID}`);

      im.setConversationRecvMessageOpt(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `setConversationRecvMessageOpt failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `setConversationRecvMessageOpt success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        opt
      );
    });
  }

  /**
   * 设置会话私密聊天
   * @param conversationID 会话ID
   * @param isPrivate 是否私密
   * @returns 设置结果
   */
  setConversationPrivateChat(conversationID: string, isPrivate: boolean): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `setConversationPrivateChat: ${conversationID}, isPrivate: ${isPrivate}, operationID: ${operationID}`);

      im.setConversationPrivateChat(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `setConversationPrivateChat failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `setConversationPrivateChat success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        isPrivate
      );
    });
  }

  /**
   * 设置会话阅后即焚时长
   * @param conversationID 会话ID
   * @param burnDuration 阅后即焚时长（秒）
   * @returns 设置结果
   */
  setConversationBurnDuration(conversationID: string, burnDuration: number): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `setConversationBurnDuration: ${conversationID}, burnDuration: ${burnDuration}, operationID: ${operationID}`);

      im.setConversationBurnDuration(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `setConversationBurnDuration failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `setConversationBurnDuration success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        burnDuration
      );
    });
  }

  /**
   * 重置会话@提醒类型
   * @param conversationID 会话ID
   * @returns 重置结果
   */
  resetConversationGroupAtType(conversationID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `resetConversationGroupAtType: ${conversationID}, operationID: ${operationID}`);

      im.resetConversationGroupAtType(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `resetConversationGroupAtType failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `resetConversationGroupAtType success`);
            resolve(data);
          }
        },
        operationID,
        conversationID
      );
    });
  }

  /**
   * 隐藏会话
   * @param conversationID 会话ID
   * @returns 隐藏结果
   */
  hideConversation(conversationID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `hideConversation: ${conversationID}, operationID: ${operationID}`);

      im.hideConversation(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `hideConversation failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `hideConversation success`);
            resolve(data);
          }
        },
        operationID,
        conversationID
      );
    });
  }

  /**
   * 隐藏所有会话
   * @returns 隐藏结果
   */
  hideAllConversations(): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `hideAllConversations, operationID: ${operationID}`);

      im.hideAllConversations(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `hideAllConversations failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `hideAllConversations success`);
            resolve(data);
          }
        },
        operationID
      );
    });
  }

  /**
   * 清除会话并删除所有消息
   * @param conversationID 会话ID
   * @returns 清除结果
   */
  clearConversationAndDeleteAllMsg(conversationID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `clearConversationAndDeleteAllMsg: ${conversationID}, operationID: ${operationID}`);

      im.clearConversationAndDeleteAllMsg(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `clearConversationAndDeleteAllMsg failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `clearConversationAndDeleteAllMsg success`);
            resolve(data);
          }
        },
        operationID,
        conversationID
      );
    });
  }

  /**
   * 删除会话并删除所有消息
   * @param conversationID 会话ID
   * @returns 删除结果
   */
  deleteConversationAndDeleteAllMsg(conversationID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('ConversationManager', `deleteConversationAndDeleteAllMsg: ${conversationID}, operationID: ${operationID}`);

      im.deleteConversationAndDeleteAllMsg(
        {
          onError: (errCode: number, errMsg: string) => {
            error('ConversationManager', `deleteConversationAndDeleteAllMsg failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('ConversationManager', `deleteConversationAndDeleteAllMsg success`);
            resolve(data);
          }
        },
        operationID,
        conversationID
      );
    });
  }
}
