import Logger from "../common/utils/Logger";
import { ApiError, HttpClient } from "./HttpClient";

export interface LoginRequest {
  areaCode: string;      // 区号，如 "+86"
  phoneNumber: string;   // 手机号（用于验证码登录）
  verifyCode: string;    // 短信/语音验证码
  account: string;       // 用户名/账号（用于账号密码登录）
  password: string;      // 密码（用于账号密码登录）
  platform: number;      // 平台类型
  deviceId: string;      // 设备唯一标识
  ip: string;            // 客户端 IP（可选，部分后端用于风控）
  email: string;         // 邮箱（用于邮箱登录）
}

export interface LoginResponse {
  imToken: string;
  chatToken: string;
  userID: string;
}

export class ChatClient {
  private static instance: ChatClient | undefined;
  private readonly httpClient: HttpClient;

  private constructor() {
    this.httpClient = new HttpClient();
  }

  static getInstance(): ChatClient {
    if (ChatClient.instance === undefined) {
      ChatClient.instance = new ChatClient();
    }
    return ChatClient.instance;
  }

  getHttpClient(): HttpClient {
    return this.httpClient;
  }

  destroy(): void {
    this.httpClient.destroy();
    ChatClient.instance = undefined;
  }

  async login(request: LoginRequest): Promise<LoginResponse> {
    try {
      return await this.httpClient.post<LoginResponse>('/account/login', request);
    } catch (error) {
      let err: ApiError = error ;
      Logger.info(`login err: ${err.errCode}, ${err.errMsg}`);
      throw error as ApiError;
    }
  }
}
