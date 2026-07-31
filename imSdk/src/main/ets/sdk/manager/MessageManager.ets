/**
 * OpenIM SDK for HarmonyOS
 * 消息管理器 - 处理消息相关操作
 * 参考: open-im-sdk-android/OpenIM-SDK/src/main/java/io/openim/android/sdk/manager/MessageManager.java
 */

import im from 'libimsdk.so';
import { debug, error, info } from '../internal/log/Logger';
import { BaseCallback, CustomBusinessListener, MsgKvInfoListener, MsgListener, SendMsgCallBack } from '../listeners/listener';
import { BaseCallbackWrapper, CustomBusinessListenerWrapper, MsgKvInfoListenerWrapper, MsgListenerWrapper, SendMsgCallBackWrapper } from '../listeners/ListenerImpl';
import { GetAdvancedHistoryMessageParams, Message, SearchLocalMessagesParams } from '../models/entity';
import { toString } from '../utils/JsonUtil';
import { buildOperationID } from '../utils/Utils';

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
   * 设置高级消息监听器
   * @param listener 消息监听器
   */
  setAdvancedMsgListener(listener: MsgListener): void {
    debug('MessageManager', `setAdvancedMsgListener`);
    im.setAdvancedMsgListener(new MsgListenerWrapper(listener));
  }

  /**
   * 设置自定义业务消息监听器
   * @param listener 自定义业务监听器
   */
  setCustomBusinessListener(listener: CustomBusinessListener): void {
    debug('MessageManager', `setCustomBusinessListener`);
    im.setCustomBusinessListener(new CustomBusinessListenerWrapper((listener)));
  }

  /**
   * 设置消息KV信息监听器
   * @param listener KV信息监听器
   */
  setMessageKvInfoListener(listener: MsgKvInfoListener): void {
    debug('MessageManager', `setMessageKvInfoListener`);
    im.setMessageKvInfoListener(new MsgKvInfoListenerWrapper(listener));
  }

  /**
   * 发送消息
   * @param callback 回调
   * @param operationID 操作ID
   * @param message 消息体JSON
   * @param recvUid 接受者用户id
   * @param recvGid 群id
   * @param offlinePushInfo 离线推送内容
   * @param isOnlineOnly 是否仅在线发送
   */
  sendMessage(
    callback: SendMsgCallBack<Message>,
    operationID: string,
    message: string,
    recvUid: string,
    recvGid: string,
    offlinePushInfo: string,
    isOnlineOnly: boolean
  ): void {
    debug('MessageManager', `sendMessage, recvUid: ${recvUid}, recvGid: ${recvGid}, operationID: ${operationID}`);

    im.sendMessage(
      new SendMsgCallBackWrapper(callback),
      operationID,
      message,
      recvUid,
      recvGid,
      offlinePushInfo,
      isOnlineOnly
    );
  }

  /**
   * 删除消息（从本地）
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 会话id
   * @param clientMsgID 客户端消息id
   */
  deleteMessageFromLocalStorage(callback: BaseCallback<string>, operationID: string, conversationID: string, clientMsgID: string): void {
    debug('MessageManager', `deleteMessageFromLocalStorage: ${conversationID}, ${clientMsgID}, operationID: ${operationID}`);

    im.deleteMessageFromLocalStorage(
      new BaseCallbackWrapper(callback),
      operationID,
      conversationID,
      clientMsgID
    );
  }

  /**
   * 插入单聊消息到本地
   * @param callback 回调
   * @param operationID 操作ID
   * @param message 消息体JSON
   * @param receiver 接收者
   * @param sender 发送者
   */
  insertSingleMessageToLocalStorage(callback: BaseCallback<string>, operationID: string, message: string, receiver: string, sender: string): void {
    debug('MessageManager', `insertSingleMessageToLocalStorage, receiver: ${receiver}, sender: ${sender}, operationID: ${operationID}`);

    im.insertSingleMessageToLocalStorage(
      new BaseCallbackWrapper(callback),
      operationID,
      message,
      receiver,
      sender
    );
  }

  /**
   * 插入群聊消息到本地
   * @param callback 回调
   * @param operationID 操作ID
   * @param message 消息体JSON
   * @param groupID 群id
   * @param senderID 发送者id
   */
  insertGroupMessageToLocalStorage(callback: BaseCallback<string>, operationID: string, message: string, groupID: string, senderID: string): void {
    debug('MessageManager', `insertGroupMessageToLocalStorage, groupID: ${groupID}, senderID: ${senderID}, operationID: ${operationID}`);

    im.insertGroupMessageToLocalStorage(
      new BaseCallbackWrapper(callback),
      operationID,
      message,
      groupID,
      senderID
    );
  }

  /**
   * 标记消息已读
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 会话id
   * @param clientMsgIDs 消息ids
   */
  markMessagesAsReadByMsgID(callback: BaseCallback<string>, operationID: string, conversationID: string, clientMsgIDs: string): void {
    debug('MessageManager', `markMessagesAsReadByMsgID: ${conversationID}, operationID: ${operationID}`);

    im.markMessagesAsReadByMsgID(
      new BaseCallbackWrapper(callback),
      operationID,
      conversationID,
      clientMsgIDs
    );
  }

  /**
   * 标记会话已读
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 会话id
   */
  markConversationMessageAsRead(callback: BaseCallback<string>, operationID: string, conversationID: string): void {
    debug('MessageManager', `markConversationMessageAsRead: ${conversationID}, operationID: ${operationID}`);

    im.markConversationMessageAsRead(
      new BaseCallbackWrapper(callback),
      operationID,
      conversationID
    );
  }

  /**
   * 提示对方我正在输入
   * @param callback 回调
   * @param operationID 操作ID
   * @param userID 用户ID
   * @param msgTip 提示信息
   */
  typingStatusUpdate(callback: BaseCallback<string>, operationID: string, userID: string, msgTip: string): void {
    debug('MessageManager', `typingStatusUpdate: ${userID}, operationID: ${operationID}`);

    im.typingStatusUpdate(
      new BaseCallbackWrapper(callback),
      operationID,
      userID,
      msgTip
    );
  }

  /**
   * 创建文本消息
   * @param operationID 操作ID
   * @param text 内容
   * @returns 消息JSON字符串
   */
  createTextMessage(operationID: string, text: string): string {
    debug('MessageManager', `createTextMessage: ${text}, operationID: ${operationID}`);
    return im.createTextMessage(operationID, text);
  }

  /**
   * 创建@文本消息
   * @param operationID 操作ID
   * @param text 内容
   * @param atUserIDList 用户id列表
   * @param atUserInfoList 被@的用户id跟昵称映射
   * @param quoteMessage @消息带引用消息
   * @returns 消息JSON字符串
   */
  createTextAtMessage(operationID: string, text: string, atUserIDList: string, atUserInfoList: string, quoteMessage: string): string {
    debug('MessageManager', `createTextAtMessage: ${text}, operationID: ${operationID}`);
    return im.createTextAtMessage(operationID, text, atUserIDList, atUserInfoList, quoteMessage);
  }

  /**
   * 创建图片消息
   * @param operationID 操作ID
   * @param imagePath 相对路径
   * @returns 消息JSON字符串
   */
  createImageMessage(operationID: string, imagePath: string): string {
    debug('MessageManager', `createImageMessage: ${imagePath}, operationID: ${operationID}`);
    return im.createImageMessage(operationID, imagePath);
  }

  /**
   * 创建图片消息
   * @param operationID 操作ID
   * @param imagePath 绝对路径
   * @returns 消息JSON字符串
   */
  createImageMessageFromFullPath(operationID: string, imagePath: string): string {
    debug('MessageManager', `createImageMessageFromFullPath: ${imagePath}, operationID: ${operationID}`);
    return im.createImageMessageFromFullPath(operationID, imagePath);
  }

  /**
   * 创建声音消息
   * @param operationID 操作ID
   * @param soundPath 相对路径
   * @param duration 时长
   * @returns 消息JSON字符串
   */
  createSoundMessage(operationID: string, soundPath: string, duration: number): string {
    debug('MessageManager', `createSoundMessage: ${soundPath}, duration: ${duration}, operationID: ${operationID}`);
    return im.createSoundMessage(operationID, soundPath, duration);
  }

  /**
   * 创建声音消息
   * @param operationID 操作ID
   * @param soundPath 绝对路径
   * @param duration 时长
   * @returns 消息JSON字符串
   */
  createSoundMessageFromFullPath(operationID: string, soundPath: string, duration: number): string {
    debug('MessageManager', `createSoundMessageFromFullPath: ${soundPath}, duration: ${duration}, operationID: ${operationID}`);
    return im.createSoundMessageFromFullPath(operationID, soundPath, duration);
  }

  /**
   * 创建视频消息
   * @param operationID 操作ID
   * @param videoPath 视频相对路径
   * @param videoType mine type
   * @param duration 时长
   * @param snapshotPath 缩略图相对路径
   * @returns 消息JSON字符串
   */
  createVideoMessage(operationID: string, videoPath: string, videoType: string, duration: number, snapshotPath: string): string {
    debug('MessageManager', `createVideoMessage: ${videoPath}, operationID: ${operationID}`);
    return im.createVideoMessage(operationID, videoPath, videoType, duration, snapshotPath);
  }

  /**
   * 创建视频消息
   * @param operationID 操作ID
   * @param videoPath 绝对路径
   * @param videoType mine type
   * @param duration 时长
   * @param snapshotPath 缩略图绝对路径
   * @returns 消息JSON字符串
   */
  createVideoMessageFromFullPath(operationID: string, videoPath: string, videoType: string, duration: number, snapshotPath: string): string {
    debug('MessageManager', `createVideoMessageFromFullPath: ${videoPath}, operationID: ${operationID}`);
    return im.createVideoMessageFromFullPath(operationID, videoPath, videoType, duration, snapshotPath);
  }

  /**
   * 创建文件消息
   * @param operationID 操作ID
   * @param filePath 相对路径
   * @param fileName 文件名
   * @returns 消息JSON字符串
   */
  createFileMessage(operationID: string, filePath: string, fileName: string): string {
    debug('MessageManager', `createFileMessage: ${filePath}, fileName: ${fileName}, operationID: ${operationID}`);
    return im.createFileMessage(operationID, filePath, fileName);
  }

  /**
   * 创建文件消息
   * @param operationID 操作ID
   * @param filePath 绝对路径
   * @param fileName 文件名
   * @returns 消息JSON字符串
   */
  createFileMessageFromFullPath(operationID: string, filePath: string, fileName: string): string {
    debug('MessageManager', `createFileMessageFromFullPath: ${filePath}, fileName: ${fileName}, operationID: ${operationID}`);
    return im.createFileMessageFromFullPath(operationID, filePath, fileName);
  }

  /**
   * 创建合并消息
   * @param operationID 操作ID
   * @param messageList 消息列表JSON
   * @param title 标题
   * @param summaryList 摘要列表JSON
   * @returns 消息JSON字符串
   */
  createMergerMessage(operationID: string, messageList: string, title: string, summaryList: string): string {
    debug('MessageManager', `createMergerMessage: ${title}, operationID: ${operationID}`);
    return im.createMergerMessage(operationID, messageList, title, summaryList);
  }

  /**
   * 创建转发消息
   * @param operationID 操作ID
   * @param message 消息体JSON
   * @returns 消息JSON字符串
   */
  createForwardMessage(operationID: string, message: string): string {
    debug('MessageManager', `createForwardMessage, operationID: ${operationID}`);
    return im.createForwardMessage(operationID, message);
  }

  /**
   * 创建位置消息
   * @param operationID 操作ID
   * @param latitude 纬度
   * @param longitude 经度
   * @param description 描述消息
   * @returns 消息JSON字符串
   */
  createLocationMessage(operationID: string, latitude: number, longitude: number, description: string): string {
    debug('MessageManager', `createLocationMessage: ${latitude}, ${longitude}, ${description}, operationID: ${operationID}`);
    return im.createLocationMessage(operationID, description, longitude, latitude);
  }

  /**
   * 创建自定义消息
   * @param operationID 操作ID
   * @param data json String
   * @param extension json String
   * @param description 描述
   * @returns 消息JSON字符串
   */
  createCustomMessage(operationID: string, data: string, extension: string, description: string): string {
    debug('MessageManager', `createCustomMessage: ${description}, operationID: ${operationID}`);
    return im.createCustomMessage(operationID, data, extension, description);
  }

  /**
   * 创建引用消息
   * @param operationID 操作ID
   * @param text 内容
   * @param message 被引用的消息体JSON
   * @returns 消息JSON字符串
   */
  createQuoteMessage(operationID: string, text: string, message: string): string {
    debug('MessageManager', `createQuoteMessage: ${text}, operationID: ${operationID}`);
    return im.createQuoteMessage(operationID, text, message);
  }

  /**
   * 创建名片消息
   * @param operationID 操作ID
   * @param cardElem json String
   * @returns 消息JSON字符串
   */
  createCardMessage(operationID: string, cardElem: string): string {
    debug('MessageManager', `createCardMessage, operationID: ${operationID}`);
    return im.createCardMessage(operationID, cardElem);
  }

  /**
   * 创建自定义表情
   * @param operationID 操作ID
   * @param index 位置表情，表情的位置
   * @param data url表情，json String : {"url":"","width":0,"height":0}
   * @returns 消息JSON字符串
   */
  createFaceMessage(operationID: string, index: number, data: string): string {
    debug('MessageManager', `createFaceMessage: index ${index}, operationID: ${operationID}`);
    return im.createFaceMessage(operationID, index, data);
  }

  /**
   * 聊天设置里清除聊天记录
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 会话id
   */
  clearConversationAndDeleteAllMsg(callback: BaseCallback<string>, operationID: string, conversationID: string): void {
    debug('MessageManager', `clearConversationAndDeleteAllMsg: ${conversationID}, operationID: ${operationID}`);

    im.clearConversationAndDeleteAllMsg(
      new BaseCallbackWrapper(callback),
      operationID,
      conversationID
    );
  }

  /**
   * 搜索消息
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 根据会话查询，如果是全局搜索传null
   * @param keywordList 搜索关键词列表，目前仅支持一个关键词搜索
   * @param keywordListMatchType 关键词匹配模式，1代表与，2代表或，暂时未用
   * @param senderUserIDList 指定消息发送的uid列表 暂时未用
   * @param messageTypeList 消息类型列表
   * @param searchTimePosition 搜索的起始时间点。默认为0即代表从现在开始搜索。UTC 时间戳，单位：秒
   * @param searchTimePeriod 从起始时间点开始的过去时间范围，单位秒。默认为0即代表不限制时间范围，传24x60x60代表过去一天
   * @param pageIndex 当前页数
   * @param count 每页数量
   */
  searchLocalMessages(
    callback: BaseCallback<string>,
    operationID: string,
    conversationID: string,
    keywordList: string[],
    keywordListMatchType: number,
    senderUserIDList: string[],
    messageTypeList: number[],
    searchTimePosition: number,
    searchTimePeriod: number,
    pageIndex: number,
    count: number
  ): void {
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
      new BaseCallbackWrapper(callback),
      operationID,
      toString(searchParams)
    );
  }

  /**
   * 删除本地跟服务器消息
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 会话id
   * @param clientMsgID 消息id
   */
  deleteMessageFromLocalAndSvr(callback: BaseCallback<string>, operationID: string, conversationID: string, clientMsgID: string): void {
    debug('MessageManager', `deleteMessageFromLocalAndSvr: ${conversationID}, ${clientMsgID}, operationID: ${operationID}`);

    im.deleteMessage(
      new BaseCallbackWrapper(callback),
      operationID,
      conversationID,
      clientMsgID
    );
  }

  /**
   * 删除本地所有消息
   * @param callback 回调
   * @param operationID 操作ID
   */
  deleteAllMsgFromLocal(callback: BaseCallback<string>, operationID: string): void {
    debug('MessageManager', `deleteAllMsgFromLocal, operationID: ${operationID}`);

    im.deleteAllMsgFromLocal(
      new BaseCallbackWrapper(callback),
      operationID
    );
  }

  /**
   * 删除本地跟服务器所有消息
   * @param callback 回调
   * @param operationID 操作ID
   */
  deleteAllMsgFromLocalAndSvr(callback: BaseCallback<string>, operationID: string): void {
    debug('MessageManager', `deleteAllMsgFromLocalAndSvr, operationID: ${operationID}`);

    im.deleteAllMsgFromLocalAndSvr(
      new BaseCallbackWrapper(callback),
      operationID
    );
  }

  /**
   * 标记会话全部已读
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 会话id
   */
  markMessageAsReadByConID(callback: BaseCallback<string>, operationID: string, conversationID: string): void {
    debug('MessageManager', `markMessageAsReadByConID: ${conversationID}, operationID: ${operationID}`);

    im.markConversationMessageAsRead(
      new BaseCallbackWrapper(callback),
      operationID,
      conversationID
    );
  }

  /**
   * 撤回消息（新版本）
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   * @param clientMsgID msg client ID
   */
  revokeMessageV2(callback: BaseCallback<string>, operationID: string, conversationID: string, clientMsgID: string): void {
    debug('MessageManager', `revokeMessageV2: ${conversationID}, ${clientMsgID}, operationID: ${operationID}`);

    im.revokeMessage(
      new BaseCallbackWrapper(callback),
      operationID,
      conversationID,
      clientMsgID
    );
  }

  /**
   * 获取历史消息
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 会话id，如果不传userID跟groupID，则按会话id查询历史记录
   * @param startMsg 从startMsg开始拉取消息JSON
   * @param count 一次拉取count条
   * @param viewType 视图类型
   */
  getAdvancedHistoryMessageList(callback: BaseCallback<string>, operationID: string, conversationID: string, startMsg: string, count: number, viewType: number): void {
    debug('MessageManager', `getAdvancedHistoryMessageList, conversationID: ${conversationID}, operationID: ${operationID}`);

    const params: GetAdvancedHistoryMessageParams = {
      conversationID: conversationID,
      startClientMsgID: startMsg,
      count: count,
      viewType: viewType
    };

    im.getAdvancedHistoryMessageList(
      new BaseCallbackWrapper(callback),
      operationID,
      toString(params)
    );
  }

  /**
   * 获取历史消息 消息倒叙
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 会话id
   * @param startMsg 从startMsg开始拉取消息JSON
   * @param count 一次拉取count条
   * @param viewType 视图类型
   */
  getAdvancedHistoryMessageListReverse(callback: BaseCallback<string>, operationID: string, conversationID: string, startMsg: string, count: number, viewType: number): void {
    debug('MessageManager', `getAdvancedHistoryMessageListReverse, conversationID: ${conversationID}, operationID: ${operationID}`);

    const params: GetAdvancedHistoryMessageParams = {
      conversationID: conversationID,
      startClientMsgID: startMsg,
      count: count,
      viewType: viewType
    };

    im.getAdvancedHistoryMessageListReverse(
      new BaseCallbackWrapper(callback),
      operationID,
      toString(params)
    );
  }

  /**
   * 查询消息
   * @param callback 回调
   * @param operationID 操作ID
   * @param searchParams 搜索参数JSON
   */
  findMessageList(callback: BaseCallback<string>, operationID: string, searchParams: string): void {
    debug('MessageManager', `findMessageList, operationID: ${operationID}`);

    im.findMessageList(
      new BaseCallbackWrapper(callback),
      operationID,
      searchParams
    );
  }

  /**
   * 创建富文本消息
   * @param operationID 操作ID
   * @param text 消息内容
   * @param richList 富文本详细JSON
   * @returns 消息JSON字符串
   */
  createAdvancedTextMessage(operationID: string, text: string, richList: string): string {
    debug('MessageManager', `createAdvancedTextMessage: ${text}, operationID: ${operationID}`);
    return im.createAdvancedTextMessage(operationID, text, richList);
  }

  /**
   * 创建富文本引用消息
   * @param operationID 操作ID
   * @param text 内容
   * @param message 被引用的消息体JSON
   * @param richList 富文本详细JSON
   * @returns 消息JSON字符串
   */
  createAdvancedQuoteMessage(operationID: string, text: string, message: string, richList: string): string {
    debug('MessageManager', `createAdvancedQuoteMessage: ${text}, operationID: ${operationID}`);
    return im.createAdvancedQuoteMessage(operationID, text, message, richList);
  }

  /**
   * 发送消息（不上传OSS）
   * @param callback 回调
   * @param operationID 操作ID
   * @param message 消息体JSON
   * @param recvUid 接受者用户id
   * @param recvGid 群id
   * @param offlinePushInfo 离线推送内容
   * @param isOnlineOnly 是否仅在线发送
   */
  sendMessageNotOss(
    callback: SendMsgCallBack<Message>,
    operationID: string,
    message: string,
    recvUid: string,
    recvGid: string,
    offlinePushInfo: string,
    isOnlineOnly: boolean
  ): void {
    debug('MessageManager', `sendMessageNotOss, recvUid: ${recvUid}, recvGid: ${recvGid}, operationID: ${operationID}`);

    im.sendMessageNotOss(
      new SendMsgCallBackWrapper(callback),
      operationID,
      message,
      recvUid,
      recvGid,
      offlinePushInfo,
      isOnlineOnly
    );
  }

  /**
   * 创建图片消息
   * @param operationID 操作ID
   * @param sourcePath 源路径
   * @param sourcePicture 源图片信息JSON
   * @param bigPicture 大图信息JSON
   * @param snapshotPicture 缩略图信息JSON
   * @returns 消息JSON字符串
   */
  createImageMessageByURL(operationID: string, sourcePath: string, sourcePicture: string, bigPicture: string, snapshotPicture: string): string {
    debug('MessageManager', `createImageMessageByURL: ${sourcePath}, operationID: ${operationID}`);
    return im.createImageMessageByURL(operationID, sourcePath, sourcePicture, bigPicture, snapshotPicture);
  }

  /**
   * 创建声音消息
   * @param operationID 操作ID
   * @param soundElem 声音元素JSON
   * @returns 消息JSON字符串
   */
  createSoundMessageByURL(operationID: string, soundElem: string): string {
    debug('MessageManager', `createSoundMessageByURL, operationID: ${operationID}`);
    return im.createSoundMessageByURL(operationID, soundElem);
  }

  /**
   * 创建视频消息
   * @param operationID 操作ID
   * @param videoElem 视频元素JSON
   * @returns 消息JSON字符串
   */
  createVideoMessageByURL(operationID: string, videoElem: string): string {
    debug('MessageManager', `createVideoMessageByURL, operationID: ${operationID}`);
    return im.createVideoMessageByURL(operationID, videoElem);
  }

  /**
   * 创建文件消息
   * @param operationID 操作ID
   * @param fileElem 文件元素JSON
   * @returns 消息JSON字符串
   */
  createFileMessageByURL(operationID: string, fileElem: string): string {
    debug('MessageManager', `createFileMessageByURL, operationID: ${operationID}`);
    return im.createFileMessageByURL(operationID, fileElem);
  }

  /**
   * 修改消息本地 ex 字段
   * @param callback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   * @param clientMsgID 消息ID
   * @param localEx 本地扩展
   */
  setMessageLocalEx(callback: BaseCallback<string>, operationID: string, conversationID: string, clientMsgID: string, localEx: string): void {
    debug('MessageManager', `setMessageLocalEx: ${conversationID}, ${clientMsgID}, operationID: ${operationID}`);

    im.setMessageLocalEx(
      new BaseCallbackWrapper(callback),
      operationID,
      conversationID,
      clientMsgID,
      localEx
    );
  }
}
