/**
 * OpenIM SDK for HarmonyOS
 * JSON工具类 - 提供JSON序列化/反序列化功能
 */

/**
 * 将对象转换为JSON字符串
 * @param object 目标对象
 * @returns JSON字符串
 */
export function toString(object: Object): string {
  if (object == null) {
    return "";
  }
  return JSON.stringify(object);
}

/**
 * 将JSON字符串转换为对象
 * @param jsonString JSON字符串
 * @returns 解析后的对象
 */
export function toObject(jsonString: string): Object | null {
  if (jsonString == null || jsonString == "") {
    return null;
  }
  try {
    return JSON.parse(jsonString);
  } catch (e) {
    return null;
  }
}

/**
 * 将JSON字符串转换为数组
 * @param jsonString JSON字符串
 * @returns 解析后的数组
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

/**
 * 将对象转换为Map
 * @param jsonString JSON字符串
 * @returns Map对象
 */
export function toMap(jsonString: string): Map<string, Object> {
  const result = new Map<string, Object>();
  if (jsonString == null || jsonString == "") {
    return result;
  }
  try {
    const obj: Object = JSON.parse(jsonString);
    if (obj && typeof obj === 'object') {
      const keys: string[] = Object.keys(obj);
      for (let i = 0; i < keys.length; i++) {
        const key: string = keys[i];
        result.set(key, (obj as Record<string, Object>)[key]);
      }
    }
  } catch (e) {
    // 解析失败，返回空Map
  }
  return result;
}

/**
 * 判断字符串是否为有效的JSON
 * @param str 待检测字符串
 * @returns 是否有效
 */
export function isValidJson(str: string): boolean {
  if (str == null || str == "") {
    return false;
  }
  try {
    JSON.parse(str);
    return true;
  } catch (e) {
    return false;
  }
}
