import http from '@ohos.net.http';
import Logger from '../common/utils/Logger';
import { REQUEST_TIMEOUT, API_BASE_URL } from './Constants';

export class HttpClient {
  private readonly client: http.HttpRequest;

  constructor() {
    this.client = http.createHttp();
  }

  async get<T>(url: string): Promise<T> {
    const fullUrl: string = this.buildUrl(url);

    try {
      const response: http.HttpResponse = await this.client.request(fullUrl, {
        method: http.RequestMethod.GET,
        header: {
          'Content-Type': 'application/json',
        },
        connectTimeout: REQUEST_TIMEOUT,
        readTimeout: REQUEST_TIMEOUT,
      });
      const resp =  this.handleResponse<ApiResponse<T>>(response);
      if (resp.errCode != 0) {
        throw new ApiError(resp.errCode, resp.errMsg);
      } else {
        return resp.data
      }
    } catch (e) {
      const err: Error = e instanceof Error ? e : new Error(String(e));
      throw new ApiError(-1, `network request failed, ${err}`);
    }
  }

  async post<T>(url: string, data: Object): Promise<T> {
    const fullUrl: string = this.buildUrl(url);
    const body: string = JSON.stringify(data);
    Logger.info(`fullUrl: ${fullUrl}, body: ${body}`)
    try {
      const response: http.HttpResponse = await this.client.request(fullUrl, {
        method: http.RequestMethod.POST,
        header: {
          'Content-Type': 'application/json',
          'operationId': '1111',
        },
        extraData: body,
        connectTimeout: REQUEST_TIMEOUT,
        readTimeout: REQUEST_TIMEOUT,
      });
      const resp =  this.handleResponse<ApiResponse<T>>(response);
      if (resp.errCode != 0) {
        throw new ApiError(resp.errCode, resp.errMsg);
      } else {
        return resp.data
      }
    } catch (e) {
      if (e instanceof ApiError) throw e;
      else throw new ApiError(-1, `network request failed, ${String(e)}`);
    }
  }

  private buildUrl(path: string): string {
    if (path.startsWith('http')) {
      return path;
    }
    return API_BASE_URL + (path.startsWith('/') ? '' : '/') + path;
  }

  private handleResponse<T>(response: http.HttpResponse): T {
    const responseCode: number = response.responseCode;
    const result: string | object = response.result;


    if (responseCode >= 200 && responseCode < 300) {
      if (typeof result !== 'string') {
        throw new ApiError(-1, `response body is not string, response code: ${responseCode}`);
      }
      try {
        return JSON.parse(result) as T;
      } catch {
        throw new ApiError(-1, `response body is not valid json, response code: ${responseCode}`);
      }
    }
    throw new ApiError(-1, `error response code: ${responseCode}`);
  }

  destroy(): void {
    this.client.destroy();
  }
}

export interface ApiResponse<T> {
    errCode: number;
    errMsg: string;
    data: T;
}

export class ApiError extends Error {
  readonly errCode: number;
  readonly errMsg: string;

  constructor(errCode: number, errMsg: string) {
    super(errMsg);
    this.name = 'ApiError';
    this.errCode = errCode;
    this.errMsg = errMsg;
  }
}
