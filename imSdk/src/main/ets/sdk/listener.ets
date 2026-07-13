import { setListener } from "libimsdk.so";
import { CbEvents } from "./enum";
import { emitter } from '@kit.BasicServicesKit';
import { CbEventData } from "./entity";
import { hilog } from "@kit.PerformanceAnalysisKit";
import { Logger } from "./Logger";

type EventCallback = (data: CbEventData) => void;


export class Listener {
  constructor() {
  }
  startListener() {
    Logger.print(`setListener nativeCallback`)
    setListener(this.nativeCallback);
  }
  private readonly prefix = 'imEvent';

  private eventId(id: number): string {
    return `${this.prefix}:${id}`;
  }
  private parseEventData(data: string): CbEventData {
    if (data === 'true') {
      return true;
    }
    if (data === 'false') {
      return false;
    }

    const num = Number(data);
    if (data.trim() !== '' && !isNaN(num)) {
      return num;
    }

    try {
      return JSON.parse(data) as CbEventData;
    } catch (e) {
      return undefined;
    }
  }
  // 重载1：无数据事件（void）
  on(id: CbEvents, callback: () => void): void;

  // 重载2：有数据事件
  on<T extends CbEventData>(id: CbEvents, callback: (data: T) => void): void;

  // 实现（统一处理）
  on(id: CbEvents, callback: ((data: CbEventData) => void) | (() => void)): void {
    const onCallback: Callback<emitter.GenericEventData<CbEventData>> =
      (eventData) => {
        if (callback.length === 0) {
          (callback as () => void)();
        } else {
          (callback as (data: CbEventData) => void)(eventData.data ?? ({} as CbEventData));
        }
      };

    emitter.off(this.eventId(id));
    emitter.on(this.eventId(id), onCallback);
  }

  private readonly nativeCallback = (event: number, data: string): void => {
    this.callback(event, data);
  };

  isCbEvent(value: number): boolean {
    return CbEvents[value] !== undefined;
  }
  callback(event: number, data: string): void {
   Logger.print(`emitter callback event: ${event}, data: ${data}`)
    if (!this.isCbEvent(event)) {
      Logger.warn(`unknown event code: ${event}}`)
      return;
    }

    const parsedData = this.parseEventData(data);

    emitter.emit(
      this.eventId(event),
      { data: parsedData }
    );
  }
}