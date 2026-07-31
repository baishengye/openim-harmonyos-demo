import { IM, OpenIMAppWrapper } from "../sdkwrapper/IMAppWrapper";
import {
  InitConfig,
  Platform,
  LogLevel,
  ConnListener
} from "imsdk";
import Logger from "../common/utils/Logger";

class ConnListenerImpl implements ConnListener{
  onConnecting(): void {
    Logger.info("OnConnecting")
  }

  onConnectSuccess(): void {
    Logger.info("OnConnectSuccess")
  }

  onConnectFailed(errCode: number, errMsg: string): void {
    Logger.info(`OnConnectFailed, errCode: ${errCode}, errMsg: ${errMsg}`)
  }

  onKickedOffline(): void {
    Logger.info("OnKickedOffline")
  }

  onUserTokenExpired(): void {
    Logger.info("OnUserTokenExpired");
  }

  onUserTokenInvalid(errMsg: string): void {
    Logger.info(`OnUserTokenInvalid, errMsg: ${errMsg}`)
  }

}

export class AppRuntime {
  private static instance: AppRuntime | undefined;
  chatToken: string = "";
  imToken: string = "";
  isRunning: boolean;
  currentUserID: string = "";

  private constructor() {
    this.isRunning = false;
  }

  static getInstance(): AppRuntime {
    if (AppRuntime.instance === undefined) {
      AppRuntime.instance = new AppRuntime();
    }
    return AppRuntime.instance;
  }

  /**
   * 启动SDK
   */
  start(dataDir: string): void {
    if (this.isRunning) {
      return;
    }

    this.isRunning = true;

    const config: InitConfig = {
      platformID: Platform.IOS,
      apiAddr: 'http://172.16.25.203:10002',
      wsAddr: 'ws://172.16.25.203:10001',
      dataDir: dataDir,
      logLevel: LogLevel.Error,
      isLogStandardOutput: false,
      logFilePath: dataDir,
    }

    // 初始化SDK
    IM.init(config, new ConnListenerImpl());
    IM.getLoginUserID()
    Logger.info('AppRuntime started')
  }

  stop(): void {
    if (!this.isRunning) {
      return;
    }
    this.isRunning = false;
    Logger.info('AppRuntime stopped');
  }

  isActive(): boolean {
    return this.isRunning;
  }

  onBackground(): void {
    Logger.info('AppRuntime onBackground');
  }

  onForeground(): void {
    Logger.info('AppRuntime onForeground');
  }

  setToken(chatToken: string, imToken: string): void {
    this.chatToken = chatToken;
    this.imToken = imToken;
  }

  getChatToken(): string {
    return this.chatToken;
  }

  getImToken(): string {
    return this.imToken;
  }

  setUserID(userID: string): void {
    this.currentUserID = userID;
  }

  getUserID(): string {
    return this.currentUserID || IM.getLoginUserID();
  }
}
