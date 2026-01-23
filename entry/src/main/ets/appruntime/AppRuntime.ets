import { getSDK, IMSdk } from "imsdk";
import { SDKError } from "imsdk/src/main/ets/sdk/entity";
import { CbEvents, LogLevel, Platform } from "imsdk/src/main/ets/sdk/enum";
import Logger from "../common/utils/Logger";

export class AppRuntime {
  private static instance: AppRuntime | undefined;
  chatToken: string = "";
  imToken: string = "";
  isRunning: boolean;

  private constructor() {
    this.isRunning = false;
  }

  static getInstance(): AppRuntime {
    if (AppRuntime.instance === undefined) {
      AppRuntime.instance = new AppRuntime();
    }
    return AppRuntime.instance;
  }

  start(dataDir: string): void {
    if (this.isRunning) {
      return;
    }
    this.chatToken = "test123";
    this.isRunning = true;
    IMSdk.getInstance().initSDK({
      platformID: Platform.iOS,
      apiAddr: 'http://192.168.2.136:10002',
      wsAddr: 'ws://192.168.2.136:10001',
      dataDir: dataDir,
      logLevel: LogLevel.Verbose,
      isLogStandardOutput: false,
      logFilePath: dataDir,
      isExternalExtensions: false
    })
    getSDK().on(CbEvents.OnConnecting, () => {
      Logger.info("OnConnecting")
    })
    getSDK().on(CbEvents.OnConnectSuccess, () => {
      Logger.info("OnConnectSuccess")
    })
    getSDK().on(CbEvents.OnConnectFailed, (data: SDKError) => {
      Logger.info(`OnConnectFailed, errCode: ${data.errCode}, errMsg: ${data.errMsg}`)
    })
    getSDK().on(CbEvents.OnUserTokenInvalid, (data: SDKError) => {
      Logger.info(`OnUserTokenInvalid, errCode: ${data.errCode}, errMsg: ${data.errMsg}`)
    })
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
}
