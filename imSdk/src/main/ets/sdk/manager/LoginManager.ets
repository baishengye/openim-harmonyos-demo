/**
 * OpenIM SDK for HarmonyOS
 * 登录管理器 - 处理登录相关操作
 */

import im from 'libimsdk.so';
import { debug, error, info } from '../internal/log/Logger';
import { BaseCallback, ConnListener } from '../listeners/listener';
import { BaseCallbackWrapper, ConnListenerWrapper } from '../listeners/ListenerImpl';
import { InitConfig } from '../models/entity';
import { buildOperationID } from '../utils/Utils';
import { toString } from '../utils/JsonUtil';
import { LoginStatus } from '../enums/enum';

/**
 * 登录管理器
 */
export class LoginManager {
  private TAG = "LoginManager"

  /**
   * 初始化SDK
   * @param listener 连接监听器
   * @param operationID 操作ID
   * @param config 初始化配置
   * @returns 初始化结果，0表示成功
   */
  initSdk(listener: ConnListener, operationID: string, config: InitConfig): number {
    debug(this.TAG, `initSdk with operationID: ${operationID}, config: ${toString(config)}`);

    const wrappedListener = new ConnListenerWrapper(listener);
    debug(this.TAG, `Created ConnListenerWrapper, calling im.initSdk...`);

    const result = im.initSdk(
      wrappedListener,
      operationID,
      toString(config)
    );

    info(this.TAG, `SDK initialized with result: ${result}`);
    return result;
  }

  /**
   * 登录
   * @param callback 回调
   * @param operationID 操作ID
   * @param userID 用户ID
   * @param token 登录令牌
   */
  login(callback: BaseCallback<string>, operationID: string, userID: string, token: string): void {
    debug('OpenIM', `login with userID: ${userID}, operationID: ${operationID}`);

    im.login(
      new BaseCallbackWrapper(callback),
      operationID,
      userID,
      token
    );
  }

  /**
   * 登出
   * @param callback 回调
   * @param operationID 操作ID
   */
  logout(callback: BaseCallback<string>, operationID: string): void {
    debug('OpenIM', `logout with operationID: ${operationID}`);

    im.logout(
      new BaseCallbackWrapper(callback),
      operationID
    );
  }

  /**
   * 获取登录状态
   * @param operationID 操作ID
   * @returns 登录状态
   */
  getLoginStatus(operationID: string): LoginStatus {
    return im.getLoginStatus(operationID) as LoginStatus;
  }

  /**
   * 获取当前登录用户ID
   * @returns 用户ID
   */
  getLoginUserID(): string {

    im.add(1,2)
    // return im.getLoginUserID();
    return "";
  }

  /**
   * 反初始化SDK
   * @param operationID 操作ID
   */
  unInitSDK(operationID: string): void {
    debug('OpenIM', `unInitSDK with operationID: ${operationID}`);
    im.unInitSDK(operationID);
    info('OpenIM', 'SDK uninitialized');
  }

  /**
   * 获取SDK版本
   * @returns SDK版本号
   */
  getSdkVersion(): string {
    return im.getSdkVersion();
  }
}
