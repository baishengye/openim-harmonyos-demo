import router from '@ohos.router';
import Logger from '../../common/utils/Logger';
import LoginViewModel from './LoginViewModel';

@Entry
@ComponentV2
struct LoginView {
  @Local viewModel: LoginViewModel = new LoginViewModel();

  build() {
    Column() {
      // 标题
      Text('OpenIM 登录')
        .fontSize(28)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 80, bottom: 60 })

      // 账号输入框
      TextInput({
          placeholder: '请输入账号',
          text: "1368225018"
        })
        .width('80%')
        .height(50)
        .margin({ bottom: 20 })
        .onChange((value: string) => {
          this.viewModel.setAccount(value);
        })

      // 密码输入框
      TextInput({
          placeholder: '请输入密码',
          text: "Aa111111"
        })
        .width('80%')
        .height(50)
        .type(InputType.Password)
        .margin({ bottom: 40 })
        .onChange((value: string) => {
          this.viewModel.setPassword(value);
        })

      // 错误信息
      if (this.viewModel.errorMsg) {
        Text(this.viewModel.errorMsg)
          .fontColor('#FF4444')
          .fontSize(14)
          .margin({ bottom: 20 })
      }

      // 登录按钮
      Button('登录')
        .width('80%')
        .height(50)
        .fontSize(18)
        .enabled(!this.viewModel.isLoading && this.viewModel.isLogin)
        .onClick(async () => {
          const success = await this.viewModel.login();
          if (success) {
            // 登录成功，跳转到首页
            Logger.error(`登陆成功`);
          }
        })

      // 加载状态
      if (this.viewModel.isLoading) {
        LoadingProgress()
          .width(40)
          .height(40)
          .margin({ top: 20 })
      }
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F5F5F5')
  }
}
