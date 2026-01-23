import { cryptoFramework } from '@kit.CryptoArchitectureKit';
import { buffer } from '@kit.ArkTS';

export class Utils {
  static uint8ArrayToHex(uint8Array: Uint8Array): string {
    return Array.from(uint8Array)
      .map(b => b.toString(16).padStart(2, '0'))
      .join('');
  }
  static async MD5(str: string): Promise<string> {
    let res = "";
    try {
      let md = cryptoFramework.createMd('MD5');
      await md.update({ data: new Uint8Array(buffer.from(str, 'utf-8').buffer) });
      let mdResult = await md.digest();
      return Utils.uint8ArrayToHex(mdResult.data);
    } catch (error) {
      return "";
    }
    return res;
  }
}