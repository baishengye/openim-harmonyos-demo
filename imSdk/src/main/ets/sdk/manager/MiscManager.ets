/**
 * OpenIM SDK for HarmonyOS
 * 杂项管理器 - 处理FCM、角标、日志、上传等杂项操作
 */

import im from 'libimsdk.so';
import { debug, info } from '../internal/log/Logger';
import { BaseCallback, UploadFileCallback, UploadLogProgress } from '../listeners/listener';
import { BaseCallbackWrapper, UploadFileCallbackWrapper, UploadLogProgressWrapper } from '../listeners/ListenerImpl';
import { buildOperationID } from '../utils/Utils';

/**
 * 杂项管理器
 * 提供FCM Token、App角标、日志上传、文件上传等操作
 */
export class MiscManager {
  /**
   * 更新FCM Token
   * @param callback 回调
   * @param fcmToken FCM Token
   * @param expireTime 过期时间（秒）
   */
  updateFcmToken(callback: BaseCallback<string>, fcmToken: string, expireTime: number): void {
    const operationID = buildOperationID();
    debug('MiscManager', `updateFcmToken, operationID: ${operationID}`);

    im.updateFcmToken(
      new BaseCallbackWrapper(callback),
      operationID,
      fcmToken,
      expireTime
    );
  }

  /**
   * 设置App角标
   * @param callback 回调
   * @param appUnreadCount 未读消息数
   */
  setAppBadge(callback: BaseCallback<string>, appUnreadCount: number): void {
    const operationID = buildOperationID();
    debug('MiscManager', `setAppBadge: ${appUnreadCount}, operationID: ${operationID}`);

    im.setAppBadge(
      new BaseCallbackWrapper(callback),
      operationID,
      appUnreadCount
    );
  }

  /**
   * 上传日志
   * @param callback 回调
   * @param line 日志行数
   * @param ex 扩展信息
   * @param progressCallback 上传进度回调
   */
  uploadLogs(callback: BaseCallback<string>, line: number, ex: string, progressCallback: UploadLogProgress): void {
    const operationID = buildOperationID();
    debug('MiscManager', `uploadLogs, line: ${line}, operationID: ${operationID}`);

    im.uploadLogs(
      new BaseCallbackWrapper(callback),
      operationID,
      line,
      ex,
      new UploadLogProgressWrapper(progressCallback)
    );
  }

  /**
   * 上传文件
   * @param callback 回调
   * @param reqData 请求数据JSON
   * @param uploadFileCallback 上传文件回调
   */
  uploadFile(callback: BaseCallback<string>, reqData: string, uploadFileCallback: UploadFileCallback): void {
    const operationID = buildOperationID();
    debug('MiscManager', `uploadFile, operationID: ${operationID}`);

    im.uploadFile(
      new BaseCallbackWrapper(callback),
      operationID,
      reqData,
      new UploadFileCallbackWrapper(uploadFileCallback)
    );
  }

  /**
   * 写入日志
   * @param callback 回调
   * @param logLevel 日志级别
   * @param file 文件名
   * @param line 行号
   * @param msgs 消息
   * @param err 错误信息
   */
  logs(callback: BaseCallback<string>, operationID: string, logLevel: number, file: string, line: number, msgs: string, err: string, keyAndValue: string): void {
    debug('MiscManager', `logs, logLevel: ${logLevel}, file: ${file}, operationID: ${operationID}`);

    im.logs(
      new BaseCallbackWrapper(callback),
      operationID,
      logLevel,
      file,
      line,
      msgs,
      err,
      keyAndValue
    );
  }

  /**
   * 获取SDK版本
   * @returns SDK版本号
   */
  getSdkVersion(): string {
    debug('MiscManager', 'getSdkVersion');
    return im.getSdkVersion();
  }

  /**
   * 反初始化SDK
   */
  unInitSDK(): void {
    const operationID = buildOperationID();
    debug('MiscManager', `unInitSDK, operationID: ${operationID}`);
    im.unInitSDK(operationID);
  }

  /**
   * 获取@所有人标签
   * @returns @所有人标签
   */
  getAtAllTag(): string {
    const operationID = buildOperationID();
    debug('MiscManager', `getAtAllTag, operationID: ${operationID}`);
    return im.getAtAllTag(operationID);
  }

  /**
   * 更改输入状态
   * @param callback 回调
   * @param conversationID 会话ID
   * @param focus 是否获取焦点
   */
  changeInputStates(callback: BaseCallback<string>, conversationID: string, focus: boolean): void {
    const operationID = buildOperationID();
    debug('MiscManager', `changeInputStates: ${conversationID}, focus: ${focus}, operationID: ${operationID}`);

    im.changeInputStates(
      new BaseCallbackWrapper(callback),
      operationID,
      conversationID,
      focus
    );
  }

  /**
   * 获取输入状态
   * @param callback 回调
   * @param conversationID 会话ID
   * @param userID 用户ID
   */
  getInputStates(callback: BaseCallback<number>, conversationID: string, userID: string): void {
    const operationID = buildOperationID();
    debug('MiscManager', `getInputStates: ${conversationID}, userID: ${userID}, operationID: ${operationID}`);

    im.getInputStates(
      new BaseCallbackWrapper(callback),
      operationID,
      conversationID,
      userID
    );
  }
}
