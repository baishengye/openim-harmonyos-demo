import { BaseCallback, SendMsgCallBack } from "./listener";

// 桥接类同样支持泛型 T
export class PromiseBaseCallback<T> implements BaseCallback<T> {
  private resolve: (value: T) => void;
  private reject: (reason: Error) => void;

  constructor(resolve: (value: T) => void, reject: (reason: Error) => void) {
    this.resolve = resolve;
    this.reject = reject;
  }

  onSuccess(result: T): void {
    this.resolve(result);
  }

  onError(code: number, message: string): void {
    this.reject(new Error(`Code: ${code}, Message: ${message}`));
  }
}

export class PromiseSendMsgCallback<T> implements SendMsgCallBack<T>{
  private resolve: (value: T) => void;
  private reject: (reason: Error) => void;
  private callOnProgress: (progress:number) => void;

  constructor(resolve: (value: T) => void, reject: (reason: Error) => void,callOnProgress:(progress:number) => void) {
    this.resolve = resolve;
    this.reject = reject;
    this.callOnProgress = callOnProgress;
  }

  onError(errCode: number, errMsg: string): void {
    this.reject(new Error(`Code: ${errCode}, Message: ${errMsg}`));
  }

  onSuccess(data: T): void {
    this.resolve(data);
  }

  onProgress(progress: number): void {
    this.callOnProgress(progress)
  }
}