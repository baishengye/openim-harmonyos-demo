import { IM } from "../../sdkwrapper/IMAppWrapper";
import { Platform } from "imsdk";
import { ChatClient, LoginRequest } from "../../api/ChatClient";
import { AppRuntime } from "../../appruntime/AppRuntime";
import Logger from "../../common/utils/Logger";
import { Utils } from "../../common/utils/Utils";

@ObservedV2
export default class LoginViewModel {
  @Trace public isLogin: boolean = false;
  @Trace private account: string = "";
  @Trace private password: string = "";
  @Trace chatToken: string = "";
  @Trace imToken: string = "";
  @Trace public isLoading: boolean = false;
  @Trace public errorMsg: string = "";

  setAccount(account: string) {
    this.account = account;
    this.isLoginAvailable()
  }

  setPassword(password: string) {
    this.password = password;
    this.isLoginAvailable()
  }

  isLoginAvailable() {
    this.isLogin = false;
    if (this.account.length > 0 && this.password.length > 0) {
      this.isLogin = true;
    }
  }

  async login(): Promise<boolean> {
    if (!this.isLogin) {
      return false;
    }

    this.isLoading = true;
    this.errorMsg = "";

    try {
      // 1. 调用后端API登录获取token
      const req: LoginRequest = {
        areaCode: "+86",
        phoneNumber: this.account,
        verifyCode: "",
        account: "",
        password: await Utils.MD5(this.password),
        platform: Platform.IOS,
        deviceId: "",
        ip: "",
        email: ""
      }

      Logger.info(`ChatClient login`);
      const resp = await ChatClient.getInstance().login(req)

      this.chatToken = resp.chatToken;
      this.imToken = resp.imToken;
      Logger.info(`userID: ${resp.userID}, imToken: ${this.imToken}`);

      // 保存token
      AppRuntime.getInstance().setToken(resp.chatToken, this.imToken);
      AppRuntime.getInstance().setUserID(resp.userID);

      // 2. 使用IM SDK登录
      await IM.login(resp.userID, this.imToken);
      Logger.info(`login successful!`);

      this.isLoading = false;
      return true;

    } catch (e) {
      Logger.error(`login failed: ${e}`);
      this.errorMsg = e instanceof Error ? e.message : "登录失败";
      this.isLoading = false;
      return false;
    }
  }
}
