import { getSDK, OpenIM, OpenIMClient, OnConnListener, LogLevel, Platform, InitConfig } from "imsdk";
import Logger from "../common/utils/Logger";

/**
 * SDK错误信息
 */
class SDKError extends Error {
  errCode: number;
  errMsg: string;

  constructor(errCode: number, errMsg: string) {
    super(errMsg);
    this.errCode = errCode;
    this.errMsg = errMsg;
    this.name = 'SDKError';
  }
}

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

    // 连接状态监听器
    const connListener: OnConnListener = {
      onConnecting: () => {
        Logger.info("OnConnecting")
      },
      onConnectSuccess: () => {
        Logger.info("OnConnectSuccess")
      },
      onConnectFailed: (errCode: number, errMsg: string) => {
        Logger.info(`OnConnectFailed, errCode: ${errCode}, errMsg: ${errMsg}`)
      },
      onKickedOffline: () => {
        Logger.info("OnKickedOffline")
      },
      onUserTokenExpired: () => {
        Logger.info("OnUserTokenExpired")
      },
      onUserTokenInvalid: (errMsg: string) => {
        Logger.info(`OnUserTokenInvalid, errMsg: ${errMsg}`)
      }
    }

    const config: InitConfig = {
      platformID: Platform.iOS,
      apiAddr: 'http://192.168.2.136:10002',
      wsAddr: 'ws://192.168.2.136:10001',
      dataDir: dataDir,
      logLevel: LogLevel.Verbose,
      isLogStandardOutput: false,
      logFilePath: dataDir,
    }

    getSDK().initSdk(connListener, config)
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
