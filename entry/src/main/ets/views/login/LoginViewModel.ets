import { getSDK } from "imsdk";
import { Platform } from "imsdk/src/main/ets/sdk/enum";
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
  async login(): Promise<void> {
    const req: LoginRequest = {
      areaCode: "+86",
      phoneNumber: this.account,
      verifyCode: "",
      account: "",
      password: await Utils.MD5(this.password),
      platform:Platform.iOS,
      deviceId: "",
      ip: "",
      email: ""
    }

    try {
      Logger.info(`ChatClient login`);
      const resp = await ChatClient.getInstance().login(req)
      this.chatToken = resp.chatToken;
      this.imToken = resp.imToken;
      Logger.info(`userID: ${resp.userID}, imToken: ${this.imToken}`);
      AppRuntime.getInstance().setToken(resp.chatToken, resp.imToken)
      await getSDK().login({
        userID: resp.userID,
        token: resp.imToken,
        platformID: Platform.iOS,
        apiAddr: 'http://192.168.2.136:10002',
        wsAddr: 'ws://192.168.2.136:10001',
      })
      Logger.info(`login sucessful!`);
    }catch (e) {
      Logger.error(`login failed ${e}`);
    }
    return
  }
}