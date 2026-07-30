/**
 * OpenIM SDK for HarmonyOS
 * 消息管理器 - 处理消息相关操作
 * 参考: open-im-sdk-android/OpenIM-SDK/src/main/java/io/openim/android/sdk/manager/MessageManager.java
 */

import im from 'libimsdk.so';
import { buildOperationID } from './Utils';
import { debug, info, error } from './Logger';
import { toString, toArray } from './JsonUtil';
import { SearchLocalMessagesParams, GetAdvancedHistoryMessageParams } from './entity';
import { MsgListener, CustomBusinessListener, MsgKvInfoListener } from './listener';
import List from '@ohos.util.List';

/**
 * 发送消息进度回调
 */
export interface SendMsgProgressCallback {
  /** 成功回调 */
  onProgress(progress: number): void;
}

/**
 * 消息管理器
 * 提供消息创建、发送、查询等操作
 */
export class MessageManager {
  /**
   * 发送消息
   * @param message 消息体JSON
   * @param recvUid 接受者用户id
   * @param recvGid 群id
   * @param offlinePushInfo 离线推送内容
   * @param isOnlineOnly 是否仅在线发送
   * @param onProgress 发送进度回调
   * @returns 发送结果JSON字符串
   */
  sendMessage(
    message: string,
    recvUid: string,
    recvGid: string,
    offlinePushInfo: string,
    isOnlineOnly: boolean,
    onProgress?: SendMsgProgressCallback
  ): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `sendMessage, recvUid: ${recvUid}, recvGid: ${recvGid}, operationID: ${operationID}`);

      im.sendMessage(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `sendMessage failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `sendMessage success`);
            resolve(data);
          },
          onProgress: (progress:number)=>{
            onProgress?.onProgress(progress)
          }
        },
        operationID,
        message,
        recvUid,
        recvGid,
        offlinePushInfo,
        isOnlineOnly
      );
    });
  }

  /**
   * 删除消息（从本地）
   * @param conversationID 会话id
   * @param clientMsgID 客户端消息id
   * @returns 删除结果
   */
  deleteMessageFromLocalStorage(conversationID: string, clientMsgID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `deleteMessageFromLocalStorage: ${conversationID}, ${clientMsgID}, operationID: ${operationID}`);

      im.deleteMessageFromLocalStorage(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `deleteMessageFromLocalStorage failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `deleteMessageFromLocalStorage success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        clientMsgID
      );
    });
  }

  /**
   * 插入单聊消息到本地
   * @param message 消息体JSON
   * @param receiver 接收者
   * @param sender 发送者
   * @returns 插入结果
   */
  insertSingleMessageToLocalStorage(message: string, receiver: string, sender: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `insertSingleMessageToLocalStorage, receiver: ${receiver}, sender: ${sender}, operationID: ${operationID}`);

      im.insertSingleMessageToLocalStorage(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `insertSingleMessageToLocalStorage failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `insertSingleMessageToLocalStorage success`);
            resolve(data);
          }
        },
        operationID,
        message,
        receiver,
        sender
      );
    });
  }

  /**
   * 插入群聊消息到本地
   * @param message 消息体JSON
   * @param groupID 群id
   * @param senderID 发送者id
   * @returns 插入结果
   */
  insertGroupMessageToLocalStorage(message: string, groupID: string, senderID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `insertGroupMessageToLocalStorage, groupID: ${groupID}, senderID: ${senderID}, operationID: ${operationID}`);

      im.insertGroupMessageToLocalStorage(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `insertGroupMessageToLocalStorage failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `insertGroupMessageToLocalStorage success`);
            resolve(data);
          }
        },
        operationID,
        message,
        groupID,
        senderID
      );
    });
  }

  /**
   * 标记消息已读
   * @param conversationID 会话id
   * @param clientMsgIDs 消息ids
   * @returns 标记结果
   */
  markMessagesAsReadByMsgID(conversationID: string, clientMsgIDs: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `markMessagesAsReadByMsgID: ${conversationID}, operationID: ${operationID}`);

      im.markMessagesAsReadByMsgID(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `markMessagesAsReadByMsgID failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `markMessagesAsReadByMsgID success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        clientMsgIDs
      );
    });
  }

  /**
   * 标记会话已读
   * @param conversationID 会话id
   * @returns 标记结果
   */
  markConversationMessageAsRead(conversationID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `markConversationMessageAsRead: ${conversationID}, operationID: ${operationID}`);

      im.markConversationMessageAsRead(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `markConversationMessageAsRead failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `markConversationMessageAsRead success`);
            resolve(data);
          }
        },
        operationID,
        conversationID
      );
    });
  }

  /**
   * 提示对方我正在输入
   * @param userID 用户ID
   * @param msgTip 提示信息
   * @returns 操作结果
   */
  typingStatusUpdate(userID: string, msgTip: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `typingStatusUpdate: ${userID}, operationID: ${operationID}`);

      im.typingStatusUpdate(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `typingStatusUpdate failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `typingStatusUpdate success`);
            resolve(data);
          }
        },
        operationID,
        userID,
        msgTip
      );
    });
  }

  /**
   * 创建文本消息
   * @param text 内容
   * @returns 消息JSON字符串
   */
  createTextMessage(text: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createTextMessage: ${text}, operationID: ${operationID}`);
    return im.createTextMessage(operationID, text);
  }

  /**
   * 创建@文本消息
   * @param text 内容
   * @param atUserIDList 用户id列表
   * @param atUserInfoList 被@的用户id跟昵称映射
   * @param quoteMessage @消息带引用消息
   * @returns 消息JSON字符串
   */
  createTextAtMessage(text: string, atUserIDList: string, atUserInfoList: string, quoteMessage: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createTextAtMessage: ${text}, operationID: ${operationID}`);
    return im.createTextAtMessage(operationID, text, atUserIDList, atUserInfoList, quoteMessage);
  }

  /**
   * 创建图片消息
   * @param imagePath 相对路径
   * @returns 消息JSON字符串
   */
  createImageMessage(imagePath: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createImageMessage: ${imagePath}, operationID: ${operationID}`);
    return im.createImageMessage(operationID, imagePath);
  }

  /**
   * 创建图片消息
   * @param imagePath 绝对路径
   * @returns 消息JSON字符串
   */
  createImageMessageFromFullPath(imagePath: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createImageMessageFromFullPath: ${imagePath}, operationID: ${operationID}`);
    return im.createImageMessageFromFullPath(operationID, imagePath);
  }

  /**
   * 创建声音消息
   * @param soundPath 相对路径
   * @param duration 时长
   * @returns 消息JSON字符串
   */
  createSoundMessage(soundPath: string, duration: number): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createSoundMessage: ${soundPath}, duration: ${duration}, operationID: ${operationID}`);
    return im.createSoundMessage(operationID, soundPath, duration);
  }

  /**
   * 创建声音消息
   * @param soundPath 绝对路径
   * @param duration 时长
   * @returns 消息JSON字符串
   */
  createSoundMessageFromFullPath(soundPath: string, duration: number): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createSoundMessageFromFullPath: ${soundPath}, duration: ${duration}, operationID: ${operationID}`);
    return im.createSoundMessageFromFullPath(operationID, soundPath, duration);
  }

  /**
   * 创建视频消息
   * @param videoPath 视频相对路径
   * @param videoType mine type
   * @param duration 时长
   * @param snapshotPath 缩略图相对路径
   * @returns 消息JSON字符串
   */
  createVideoMessage(videoPath: string, videoType: string, duration: number, snapshotPath: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createVideoMessage: ${videoPath}, operationID: ${operationID}`);
    return im.createVideoMessage(operationID, videoPath, videoType, duration, snapshotPath);
  }

  /**
   * 创建视频消息
   * @param videoPath 绝对路径
   * @param videoType mine type
   * @param duration 时长
   * @param snapshotPath 缩略图绝对路径
   * @returns 消息JSON字符串
   */
  createVideoMessageFromFullPath(videoPath: string, videoType: string, duration: number, snapshotPath: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createVideoMessageFromFullPath: ${videoPath}, operationID: ${operationID}`);
    return im.createVideoMessageFromFullPath(operationID, videoPath, videoType, duration, snapshotPath);
  }

  /**
   * 创建文件消息
   * @param filePath 相对路径
   * @param fileName 文件名
   * @returns 消息JSON字符串
   */
  createFileMessage(filePath: string, fileName: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createFileMessage: ${filePath}, fileName: ${fileName}, operationID: ${operationID}`);
    return im.createFileMessage(operationID, filePath, fileName);
  }

  /**
   * 创建文件消息
   * @param filePath 绝对路径
   * @param fileName 文件名
   * @returns 消息JSON字符串
   */
  createFileMessageFromFullPath(filePath: string, fileName: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createFileMessageFromFullPath: ${filePath}, fileName: ${fileName}, operationID: ${operationID}`);
    return im.createFileMessageFromFullPath(operationID, filePath, fileName);
  }

  /**
   * 创建合并消息
   * @param messageList 消息列表JSON
   * @param title 标题
   * @param summaryList 摘要列表JSON
   * @returns 消息JSON字符串
   */
  createMergerMessage(messageList: string, title: string, summaryList: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createMergerMessage: ${title}, operationID: ${operationID}`);
    return im.createMergerMessage(operationID, messageList, title, summaryList);
  }

  /**
   * 创建转发消息
   * @param message 消息体JSON
   * @returns 消息JSON字符串
   */
  createForwardMessage(message: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createForwardMessage, operationID: ${operationID}`);
    return im.createForwardMessage(operationID, message);
  }

  /**
   * 创建位置消息
   * @param latitude 纬度
   * @param longitude 经度
   * @param description 描述消息
   * @returns 消息JSON字符串
   */
  createLocationMessage(latitude: number, longitude: number, description: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createLocationMessage: ${latitude}, ${longitude}, ${description}, operationID: ${operationID}`);
    return im.createLocationMessage(operationID, description, longitude, latitude);
  }

  /**
   * 创建自定义消息
   * @param data json String
   * @param extension json String
   * @param description 描述
   * @returns 消息JSON字符串
   */
  createCustomMessage(data: string, extension: string, description: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createCustomMessage: ${description}, operationID: ${operationID}`);
    return im.createCustomMessage(operationID, data, extension, description);
  }

  /**
   * 创建引用消息
   * @param text 内容
   * @param message 被引用的消息体JSON
   * @returns 消息JSON字符串
   */
  createQuoteMessage(text: string, message: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createQuoteMessage: ${text}, operationID: ${operationID}`);
    return im.createQuoteMessage(operationID, text, message);
  }

  /**
   * 创建名片消息
   * @param cardElem json String
   * @returns 消息JSON字符串
   */
  createCardMessage(cardElem: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createCardMessage, operationID: ${operationID}`);
    return im.createCardMessage(operationID, cardElem);
  }

  /**
   * 创建自定义表情
   * @param index 位置表情，表情的位置
   * @param data url表情，json String : {"url":"","width":0,"height":0}
   * @returns 消息JSON字符串
   */
  createFaceMessage(index: number, data: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createFaceMessage: index ${index}, operationID: ${operationID}`);
    return im.createFaceMessage(operationID, index, data);
  }

  /**
   * 聊天设置里清除聊天记录
   * @param conversationID 会话id
   * @returns 清除结果
   */
  clearConversationAndDeleteAllMsg(conversationID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `clearConversationAndDeleteAllMsg: ${conversationID}, operationID: ${operationID}`);

      im.clearConversationAndDeleteAllMsg(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `clearConversationAndDeleteAllMsg failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `clearConversationAndDeleteAllMsg success`);
            resolve(data);
          }
        },
        operationID,
        conversationID
      );
    });
  }

  /**
   * 搜索消息
   * @param conversationID 根据会话查询，如果是全局搜索传null
   * @param keywordList 搜索关键词列表，目前仅支持一个关键词搜索
   * @param keywordListMatchType 关键词匹配模式，1代表与，2代表或，暂时未用
   * @param senderUserIDList 指定消息发送的uid列表 暂时未用
   * @param messageTypeList 消息类型列表
   * @param searchTimePosition 搜索的起始时间点。默认为0即代表从现在开始搜索。UTC 时间戳，单位：秒
   * @param searchTimePeriod 从起始时间点开始的过去时间范围，单位秒。默认为0即代表不限制时间范围，传24x60x60代表过去一天
   * @param pageIndex 当前页数
   * @param count 每页数量
   * @returns 搜索结果JSON字符串
   */
  searchLocalMessages(
    conversationID: string,
    keywordList: string[],
    keywordListMatchType: number,
    senderUserIDList: string[],
    messageTypeList: number[],
    searchTimePosition: number,
    searchTimePeriod: number,
    pageIndex: number,
    count: number
  ): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `searchLocalMessages, conversationID: ${conversationID}, operationID: ${operationID}`);

      const searchParams: SearchLocalMessagesParams = {
        conversationID: conversationID,
        keywordList: keywordList,
        keywordListMatchType: keywordListMatchType,
        senderUserIDList: senderUserIDList,
        messageTypeList: messageTypeList,
        searchTimePosition: searchTimePosition,
        searchTimePeriod: searchTimePeriod,
        pageIndex: pageIndex,
        count: count
      };

      im.searchLocalMessages(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `searchLocalMessages failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `searchLocalMessages success`);
            resolve(data);
          }
        },
        operationID,
        toString(searchParams)
      );
    });
  }

  /**
   * 删除本地跟服务器消息
   * @param conversationID 会话id
   * @param clientMsgID 消息id
   * @returns 删除结果
   */
  deleteMessageFromLocalAndSvr(conversationID: string, clientMsgID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `deleteMessageFromLocalAndSvr: ${conversationID}, ${clientMsgID}, operationID: ${operationID}`);

      im.deleteMessage(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `deleteMessageFromLocalAndSvr failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `deleteMessageFromLocalAndSvr success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        clientMsgID
      );
    });
  }

  /**
   * 删除本地所有消息
   * @returns 删除结果
   */
  deleteAllMsgFromLocal(): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `deleteAllMsgFromLocal, operationID: ${operationID}`);

      im.deleteAllMsgFromLocal(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `deleteAllMsgFromLocal failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `deleteAllMsgFromLocal success`);
            resolve(data);
          }
        },
        operationID
      );
    });
  }

  /**
   * 删除本地跟服务器所有消息
   * @returns 删除结果
   */
  deleteAllMsgFromLocalAndSvr(): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `deleteAllMsgFromLocalAndSvr, operationID: ${operationID}`);

      im.deleteAllMsgFromLocalAndSvr(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `deleteAllMsgFromLocalAndSvr failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `deleteAllMsgFromLocalAndSvr success`);
            resolve(data);
          }
        },
        operationID
      );
    });
  }

  /**
   * 标记会话全部已读
   * @param conversationID 会话id
   * @returns 标记结果
   */
  markMessageAsReadByConID(conversationID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `markMessageAsReadByConID: ${conversationID}, operationID: ${operationID}`);

      im.markConversationMessageAsRead(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `markMessageAsReadByConID failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `markMessageAsReadByConID success`);
            resolve(data);
          }
        },
        operationID,
        conversationID
      );
    });
  }

  /**
   * 撤回消息（新版本）
   * @param conversationID 会话ID
   * @param clientMsgID msg client ID
   * @returns 撤回结果
   */
  revokeMessageV2(conversationID: string, clientMsgID: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `revokeMessageV2: ${conversationID}, ${clientMsgID}, operationID: ${operationID}`);

      im.revokeMessage(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `revokeMessageV2 failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `revokeMessageV2 success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        clientMsgID
      );
    });
  }

  /**
   * 获取历史消息
   * @param conversationID 会话id，如果不传userID跟groupID，则按会话id查询历史记录
   * @param startMsg 从startMsg开始拉取消息JSON
   * @param count 一次拉取count条
   * @param viewType 视图类型
   * @returns 历史消息JSON字符串
   */
  getAdvancedHistoryMessageList(conversationID: string, startMsg: string, count: number, viewType: number): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `getAdvancedHistoryMessageList, conversationID: ${conversationID}, operationID: ${operationID}`);

      const params: GetAdvancedHistoryMessageParams = {
        conversationID: conversationID,
        startClientMsgID: startMsg,
        count: count,
        viewType: viewType
      };

      im.getAdvancedHistoryMessageList(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `getAdvancedHistoryMessageList failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `getAdvancedHistoryMessageList success`);
            resolve(data);
          }
        },
        operationID,
        toString(params)
      );
    });
  }

  /**
   * 获取历史消息 消息倒叙
   * @param conversationID 会话id
   * @param startMsg 从startMsg开始拉取消息JSON
   * @param count 一次拉取count条
   * @param viewType 视图类型
   * @returns 历史消息JSON字符串
   */
  getAdvancedHistoryMessageListReverse(conversationID: string, startMsg: string, count: number, viewType: number): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `getAdvancedHistoryMessageListReverse, conversationID: ${conversationID}, operationID: ${operationID}`);

      const params: GetAdvancedHistoryMessageParams = {
        conversationID: conversationID,
        startClientMsgID: startMsg,
        count: count,
        viewType: viewType
      };

      im.getAdvancedHistoryMessageListReverse(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `getAdvancedHistoryMessageListReverse failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `getAdvancedHistoryMessageListReverse success`);
            resolve(data);
          }
        },
        operationID,
        toString(params)
      );
    });
  }

  /**
   * 查询消息
   * @param searchParams 搜索参数JSON
   * @returns 消息列表JSON字符串
   */
  findMessageList(searchParams: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `findMessageList, operationID: ${operationID}`);

      im.findMessageList(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `findMessageList failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `findMessageList success`);
            resolve(data);
          }
        },
        operationID,
        searchParams
      );
    });
  }

  /**
   * 创建富文本消息
   * @param text 消息内容
   * @param richList 富文本详细JSON
   * @returns 消息JSON字符串
   */
  createAdvancedTextMessage(text: string, richList: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createAdvancedTextMessage: ${text}, operationID: ${operationID}`);
    return im.createAdvancedTextMessage(operationID, text, richList);
  }

  /**
   * 创建富文本引用消息
   * @param text 内容
   * @param message 被引用的消息体JSON
   * @param richList 富文本详细JSON
   * @returns 消息JSON字符串
   */
  createAdvancedQuoteMessage(text: string, message: string, richList: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createAdvancedQuoteMessage: ${text}, operationID: ${operationID}`);
    return im.createAdvancedQuoteMessage(operationID, text, message, richList);
  }

  /**
   * 发送消息（不上传OSS）
   * @param message 消息体JSON
   * @param recvUid 接受者用户id
   * @param recvGid 群id
   * @param offlinePushInfo 离线推送内容
   * @param isOnlineOnly 是否仅在线发送
   * @param onProgress 发送进度回调
   * @returns 发送结果JSON字符串
   */
  sendMessageNotOss(
    message: string,
    recvUid: string,
    recvGid: string,
    offlinePushInfo: string,
    isOnlineOnly: boolean,
    onProgress: SendMsgProgressCallback
  ): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `sendMessageNotOss, recvUid: ${recvUid}, recvGid: ${recvGid}, operationID: ${operationID}`);

      im.sendMessageNotOss(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `sendMessageNotOss failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `sendMessageNotOss success`);
            resolve(data);
          },
          onProgress: (progress:number) => {
            onProgress.onProgress(progress)
          }
        },
        operationID,
        message,
        recvUid,
        recvGid,
        offlinePushInfo,
        isOnlineOnly
      );
    });
  }

  /**
   * 创建图片消息
   * @param sourcePath 源路径
   * @param sourcePicture 源图片信息JSON
   * @param bigPicture 大图信息JSON
   * @param snapshotPicture 缩略图信息JSON
   * @returns 消息JSON字符串
   */
  createImageMessageByURL(sourcePath: string, sourcePicture: string, bigPicture: string, snapshotPicture: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createImageMessageByURL: ${sourcePath}, operationID: ${operationID}`);
    return im.createImageMessageByURL(operationID, sourcePath, sourcePicture, bigPicture, snapshotPicture);
  }

  /**
   * 创建声音消息
   * @param soundElem 声音元素JSON
   * @returns 消息JSON字符串
   */
  createSoundMessageByURL(soundElem: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createSoundMessageByURL, operationID: ${operationID}`);
    return im.createSoundMessageByURL(operationID, soundElem);
  }

  /**
   * 创建视频消息
   * @param videoElem 视频元素JSON
   * @returns 消息JSON字符串
   */
  createVideoMessageByURL(videoElem: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createVideoMessageByURL, operationID: ${operationID}`);
    return im.createVideoMessageByURL(operationID, videoElem);
  }

  /**
   * 创建文件消息
   * @param fileElem 文件元素JSON
   * @returns 消息JSON字符串
   */
  createFileMessageByURL(fileElem: string): string {
    const operationID = buildOperationID();
    debug('MessageManager', `createFileMessageByURL, operationID: ${operationID}`);
    return im.createFileMessageByURL(operationID, fileElem);
  }

  /**
   * 修改消息本地 ex 字段
   * @param conversationID 会话ID
   * @param clientMsgID 消息ID
   * @param localEx 本地扩展
   * @returns 设置结果
   */
  setMessageLocalEx(conversationID: string, clientMsgID: string, localEx: string): Promise<string> {
    return new Promise((resolve, reject) => {
      const operationID = buildOperationID();
      debug('MessageManager', `setMessageLocalEx: ${conversationID}, ${clientMsgID}, operationID: ${operationID}`);

      im.setMessageLocalEx(
        {
          onError: (errCode: number, errMsg: string) => {
            error('MessageManager', `setMessageLocalEx failed: ${errCode} - ${errMsg}`);
            reject({ errCode, errMsg });
          },
          onSuccess: (data: string) => {
            info('MessageManager', `setMessageLocalEx success`);
            resolve(data);
          }
        },
        operationID,
        conversationID,
        clientMsgID,
        localEx
      );
    });
  }

  /**
   * 设置高级消息监听器
   * @param listener 消息监听器
   */
  setAdvancedMsgListener(listener: MsgListener): void {
    debug('MessageManager', `setAdvancedMsgListener`);
    im.setAdvancedMsgListener(listener);
  }

  /**
   * 设置自定义业务消息监听器
   * @param listener 自定义业务监听器
   */
  setCustomBusinessListener(listener: CustomBusinessListener): void {
    debug('MessageManager', `setCustomBusinessListener`);
    im.setCustomBusinessListener(listener);
  }

  /**
   * 设置消息KV信息监听器
   * @param listener KV信息监听器
   */
  setMessageKvInfoListener(listener: MsgKvInfoListener): void {
    debug('MessageManager', `setMessageKvInfoListener`);
    im.setMessageKvInfoListener(listener);
  }
}
