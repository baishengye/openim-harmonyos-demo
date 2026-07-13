// Logger.ets

import hilog from '@ohos.hilog';

/**
 * 日志工具类，用于输出带标签的完整日志
 */
export class Logger {
  private static readonly DOMAIN: number = 0xFF00; // 日志域（建议 0x0000~0xFFFF）
  private static readonly TAG: string = 'imsdk';

  static print(text: string): void {
    hilog.info(Logger.DOMAIN, Logger.TAG, '** %{public}s', text);
  }

  static debug(text: string): void {
    hilog.debug(Logger.DOMAIN, Logger.TAG, '** %{public}s', text);
  }

  static error(text: string): void {
    hilog.error(Logger.DOMAIN, Logger.TAG, '** %{public}s', text);
  }

  static warn(text: string): void {
    hilog.warn(Logger.DOMAIN, Logger.TAG, '** %{public}s', text);
  }
}