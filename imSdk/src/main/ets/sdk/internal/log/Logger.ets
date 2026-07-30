/**
 * OpenIM SDK for HarmonyOS
 * 日志工具类 - 提供日志记录功能
 */



const TAG = "OpenIM";

/**
 * 打印调试日志
 * @param tag 标签
 * @param message 消息
 */
export function debug(tag: string, message: string): void {
  logMessage(LogLevel.DEBUG, tag, message);
}

/**
 * 打印信息日志
 * @param tag 标签
 * @param message 消息
 */
export function info(tag: string, message: string): void {
  logMessage(LogLevel.INFO, tag, message);
}

/**
 * 打印警告日志
 * @param tag 标签
 * @param message 消息
 */
export function warn(tag: string, message: string): void {
  logMessage(LogLevel.WARN, tag, message);
}

/**
 * 打印错误日志
 * @param tag 标签
 * @param message 消息
 */
export function error(tag: string, message: string): void {
  logMessage(LogLevel.ERROR, tag, message);
}

/**
 * 打印致命错误日志
 * @param tag 标签
 * @param message 消息
 */
export function fatal(tag: string, message: string): void {
  logMessage(LogLevel.FATAL, tag, message);
}

/**
 * 内部日志方法
 * @param level 日志级别
 * @param tag 标签
 * @param message 消息
 */
function logMessage(level: LogLevel, tag: string, message: string): void {
  const levelStr = LogLevel[level];
  const fullTag = `${TAG}/${tag}`;
  console.info(`[${levelStr}] ${fullTag}: ${message}`);
}
