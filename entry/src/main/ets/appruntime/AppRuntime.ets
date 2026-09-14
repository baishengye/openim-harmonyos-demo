import { IM, OpenIMAppWrapper } from "../sdkwrapper/IMAppWrapper";
import {
  InitConfig,
  Platform,
  LogLevel,
  ConnListener
} from "imsdk";
import Logger from "../common/utils/Logger";
import { API_ADDR, WS_ADDR } from "../api/Constants";

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
  private initTask: Promise<number> | null = null;
  private initResult: number = -1;
  private initError: string = "SDK 尚未初始化";

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
  start(dataDir: string): Promise<number> {
    if (this.initTask !== null) {
      return this.initTask;
    }

    this.isRunning = true;

    const config: InitConfig = {
      platformID: Platform.IOS,
      apiAddr: API_ADDR,
      wsAddr: WS_ADDR,
      dataDir: dataDir,
      logLevel: LogLevel.Error,
      isLogStandardOutput: false,
      logFilePath: dataDir,
    }

    this.initTask = IM.init(config, new ConnListenerImpl())
      .then((result: number) => {
        this.initResult = result;
        if (result !== 0) {
          this.isRunning = false;
          this.initError = `initSdk 返回 ${result}`;
          throw new Error(this.initError);
        }
        this.initError = "";
        const version = IM.getSdkVersion();
        Logger.info(`AppRuntime started, SDK version: ${version}`);
        return result;
      })
      .catch((error: Error) => {
        this.isRunning = false;
        this.initError = error.message;
        Logger.error(`AppRuntime start failed: ${error.message}`);
        throw error;
      });
    return this.initTask;
  }

  async waitUntilReady(): Promise<void> {
    if (this.initTask === null) {
      throw new Error(this.initError);
    }
    await this.initTask;
    if (this.initResult !== 0) {
      throw new Error(this.initError);
    }
  }

  getInitResult(): number {
    return this.initResult;
  }

  getInitError(): string {
    return this.initError;
  }

  stop(): void {
    if (!this.isRunning) {
      return;
    }
    IM.unInitSDK();
    this.isRunning = false;
    this.initTask = null;
    this.initResult = -1;
    this.initError = "SDK 已释放";
    Logger.info('AppRuntime stopped');
  }

  isActive(): boolean {
    return this.isRunning;
  }

  onBackground(): void {
    Logger.info('AppRuntime onBackground');
    if (this.initResult === 0) {
      IM.setAppBackgroundStatus(true).catch((error: Error): void => {
        Logger.error(`set background failed: ${error.message}`);
      });
    }
  }

  onForeground(): void {
    Logger.info('AppRuntime onForeground');
    if (this.initResult === 0) {
      IM.setAppBackgroundStatus(false).catch((error: Error): void => {
        Logger.error(`set foreground failed: ${error.message}`);
      });
      IM.networkStatusChanged().catch((error: Error): void => {
        Logger.error(`network status changed failed: ${error.message}`);
      });
    }
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
