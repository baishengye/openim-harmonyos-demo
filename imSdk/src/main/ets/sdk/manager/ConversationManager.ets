/**
 * OpenIM SDK for HarmonyOS
 * 会话管理器 - 处理会话相关操作
 */

import im from 'libimsdk.so';
import { debug, error, info } from '../internal/log/Logger';
import { BaseCallback, ConvListener } from '../listeners/listener';
import { BaseCallbackWrapper, ConvListenerWrapper } from '../listeners/ListenerImpl';
import { ConversationInfo } from '../models/entity';
import { toArray, toObject, toString } from '../utils/JsonUtil';
import { buildOperationID } from '../utils/Utils';


/**
 * 会话管理器
 * 提供会话查询、管理等操作
 */
export class ConversationManager {
  /**
   * 设置会话监听器
   * @param listener 会话监听器
   */
  setConversationListener(listener: ConvListener): void {
    im.setConversationListener(new ConvListenerWrapper(listener));
  }

  /**
   * 获取所有会话列表
   * @param baseCallback 回调
   * @param operationID 操作ID
   */
  getAllConversationList(baseCallback: BaseCallback<ConversationInfo[]>, operationID: string): void {
    debug('ConversationManager', `getAllConversationList, operationID: ${operationID}`);

    im.getAllConversationList(
      new BaseCallbackWrapper(baseCallback),
      operationID
    );
  }

  /**
   * 分页获取会话列表
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param offset 偏移量
   * @param count 数量
   */
  getConversationListSplit(baseCallback: BaseCallback<ConversationInfo[]>, operationID: string, offset: number, count: number): void {
    debug('ConversationManager', `getConversationListSplit, offset: ${offset}, count: ${count}, operationID: ${operationID}`);

    im.getConversationListSplit(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      offset,
      count
    );
  }

  /**
   * 获取单个会话
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param sessionType 会话类型
   * @param sourceID 来源ID
   */
  getOneConversation(baseCallback: BaseCallback<ConversationInfo>, operationID: string, sessionType: number, sourceID: string): void {
    debug('ConversationManager', `getOneConversation, sessionType: ${sessionType}, sourceID: ${sourceID}, operationID: ${operationID}`);

    im.getOneConversation(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      sessionType,
      sourceID
    );
  }

  /**
   * 获取多个会话
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationIDList 会话ID列表
   */
  getMultipleConversation(baseCallback: BaseCallback<ConversationInfo[]>, operationID: string, conversationIDList: string[]): void {
    debug('ConversationManager', `getMultipleConversation, count: ${conversationIDList.length}, operationID: ${operationID}`);

    im.getMultipleConversation(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      toString(conversationIDList)
    );
  }

  /**
   * 获取会话ID
   * @param operationID 操作ID
   * @param sourceID 来源ID
   * @param sessionType 会话类型
   * @returns 会话ID
   */
  getConversationIDBySessionType(operationID: string, sourceID: string, sessionType: number): string {
    debug('ConversationManager', `getConversationIDBySessionType, sourceID: ${sourceID}, sessionType: ${sessionType}, operationID: ${operationID}`);
    return im.getConversationIDBySessionType(operationID, sourceID, sessionType);
  }

  /**
   * 获取未读消息总数
   * @param baseCallback 回调
   * @param operationID 操作ID
   */
  getTotalUnreadMsgCount(baseCallback: BaseCallback<number>, operationID: string): void {
    debug('ConversationManager', `getTotalUnreadMsgCount, operationID: ${operationID}`);

    im.getTotalUnreadMsgCount(
      new BaseCallbackWrapper(baseCallback),
      operationID
    );
  }

  /**
   * 标记会话消息已读
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   */
  markConversationMessageAsRead(baseCallback: BaseCallback<string>, operationID: string, conversationID: string): void {
    debug('ConversationManager', `markConversationMessageAsRead: ${conversationID}, operationID: ${operationID}`);

    im.markConversationMessageAsRead(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID
    );
  }

  /**
   * 设置会话属性
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   * @param params 属性参数JSON
   */
  setConversation(baseCallback: BaseCallback<string>, operationID: string, conversationID: string, params: string): void {
    debug('ConversationManager', `setConversation: ${conversationID}, operationID: ${operationID}`);

    im.setConversation(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID,
      params
    );
  }

  /**
   * 设置会话草稿
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   * @param draftText 草稿文本
   */
  setConversationDraft(baseCallback: BaseCallback<string>, operationID: string, conversationID: string, draftText: string): void {
    debug('ConversationManager', `setConversationDraft: ${conversationID}, draftText: ${draftText}, operationID: ${operationID}`);

    im.setConversationDraft(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID,
      draftText
    );
  }

  /**
   * 置顶/取消置顶会话
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   * @param isPinned 是否置顶
   */
  pinConversation(baseCallback: BaseCallback<string>, operationID: string, conversationID: string, isPinned: boolean): void {
    debug('ConversationManager', `pinConversation: ${conversationID}, isPinned: ${isPinned}, operationID: ${operationID}`);

    im.pinConversation(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID,
      isPinned
    );
  }

  /**
   * 设置会话消息接收选项
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   * @param opt 接收选项 (0: 正常, 1: 不接受消息, 2: 不接受通知)
   */
  setConversationRecvMessageOpt(baseCallback: BaseCallback<string>, operationID: string, conversationID: string, opt: number): void {
    debug('ConversationManager', `setConversationRecvMessageOpt: ${conversationID}, opt: ${opt}, operationID: ${operationID}`);

    im.setConversationRecvMessageOpt(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID,
      opt
    );
  }

  /**
   * 设置会话私密聊天
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   * @param isPrivate 是否私密
   */
  setConversationPrivateChat(baseCallback: BaseCallback<string>, operationID: string, conversationID: string, isPrivate: boolean): void {
    debug('ConversationManager', `setConversationPrivateChat: ${conversationID}, isPrivate: ${isPrivate}, operationID: ${operationID}`);

    im.setConversationPrivateChat(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID,
      isPrivate
    );
  }

  /**
   * 设置会话阅后即焚时长
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   * @param burnDuration 阅后即焚时长（秒）
   */
  setConversationBurnDuration(baseCallback: BaseCallback<string>, operationID: string, conversationID: string, burnDuration: number): void {
    debug('ConversationManager', `setConversationBurnDuration: ${conversationID}, burnDuration: ${burnDuration}, operationID: ${operationID}`);

    im.setConversationBurnDuration(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID,
      burnDuration
    );
  }

  /**
   * 重置会话@提醒类型
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   */
  resetConversationGroupAtType(baseCallback: BaseCallback<string>, operationID: string, conversationID: string): void {
    debug('ConversationManager', `resetConversationGroupAtType: ${conversationID}, operationID: ${operationID}`);

    im.resetConversationGroupAtType(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID
    );
  }

  /**
   * 隐藏会话
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   */
  hideConversation(baseCallback: BaseCallback<string>, operationID: string, conversationID: string): void {
    debug('ConversationManager', `hideConversation: ${conversationID}, operationID: ${operationID}`);

    im.hideConversation(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID
    );
  }

  /**
   * 隐藏所有会话
   * @param baseCallback 回调
   * @param operationID 操作ID
   */
  hideAllConversations(baseCallback: BaseCallback<string>, operationID: string): void {
    debug('ConversationManager', `hideAllConversations, operationID: ${operationID}`);

    im.hideAllConversations(
      new BaseCallbackWrapper(baseCallback),
      operationID
    );
  }

  /**
   * 清除会话并删除所有消息
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   */
  clearConversationAndDeleteAllMsg(baseCallback: BaseCallback<string>, operationID: string, conversationID: string): void {
    debug('ConversationManager', `clearConversationAndDeleteAllMsg: ${conversationID}, operationID: ${operationID}`);

    im.clearConversationAndDeleteAllMsg(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID
    );
  }

  /**
   * 删除会话并删除所有消息
   * @param baseCallback 回调
   * @param operationID 操作ID
   * @param conversationID 会话ID
   */
  deleteConversationAndDeleteAllMsg(baseCallback: BaseCallback<string>, operationID: string, conversationID: string): void {
    debug('ConversationManager', `deleteConversationAndDeleteAllMsg: ${conversationID}, operationID: ${operationID}`);

    im.deleteConversationAndDeleteAllMsg(
      new BaseCallbackWrapper(baseCallback),
      operationID,
      conversationID
    );
  }
}
