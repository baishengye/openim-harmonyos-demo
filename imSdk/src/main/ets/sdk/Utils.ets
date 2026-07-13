
// Utils.ets
const CHARS = '0123456789abcdef';
export function  uuidV4(): string {
  let uuid = '';
  for (let i = 0; i < 36; i++) {
    if (i === 8 || i === 13 || i === 18 || i === 23) {
      uuid += '-';
    } else if (i === 14) {
      uuid += '4';
    } else if (i === 19) {
      // 使用 charAt 替代 CHARS[index]
      const index = (Math.random() * 4) | 8;
      uuid += '0123456789abcdef'.charAt(index);
    } else {
      const index = Math.floor(Math.random() * 16);
      uuid += '0123456789abcdef'.charAt(index);
    }
  }
  return uuid;
}