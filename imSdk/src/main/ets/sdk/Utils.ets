/**
 * OpenIM SDK for HarmonyOS
 * 工具类 - 提供通用工具方法
 */

/**
 * 生成唯一的操作ID
 */
export function buildOperationID(): string {
  return Date.now().toString();
}

/**
 * 将 JSON 字符串解析为数组
 * @param jsonString JSON 字符串
 * @returns 解析后的对象数组
 */
export function toArray(jsonString: string): Object[] {
  if (jsonString == null || jsonString == "") {
    return [];
  }
  try {
    const parsed: Object = JSON.parse(jsonString);
    if (Array.isArray(parsed)) {
      return parsed as Object[];
    }
    return [];
  } catch (e) {
    return [];
  }
}
