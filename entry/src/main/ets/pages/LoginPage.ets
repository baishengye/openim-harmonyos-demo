import Constants from '../api/Constants';
import LoginViewModel from '../views/login/LoginViewModel';
import { AppStorageV2, UIContext } from '@kit.ArkUI';
import Logger from '../common/utils/Logger';
import { AppRuntime } from '../appruntime/AppRuntime';
import { ApiError } from '../api/HttpClient';

@Extend(TextInput)
function inputStyle() {
  .placeholderColor($r('app.color.placeholder_color'))
  .height($r('app.float.login_input_height'))
  .fontSize($r('app.float.big_text_size'))
  .backgroundColor(Color.White)
  .width(Constants.FULL_PARENT)
  .padding({ left: Constants.INPUT_PADDING_LEFT })
  .margin({ top: $r('app.float.input_margin_top') })
}

@Extend(Line)
function lineStyle() {
  .width(Constants.FULL_PARENT)
  .height($r('app.float.line_height'))
  .backgroundColor($r('app.color.line_color'))
}

@Extend(Text)
function blueTextStyle() {
  .fontColor($r('app.color.login_blue_color'))
  .fontSize($r('app.float.small_text_size'))
  .fontWeight(FontWeight.Medium)
}

@Entry
@ComponentV2
struct LoginPage {
  @Provider('navPathStack') navPathStack: NavPathStack = new NavPathStack();
  @Local loginViewModel: LoginViewModel = AppStorageV2.connect<LoginViewModel>(LoginViewModel, () => new LoginViewModel())!;

  @Builder
  PagesMap(name: string) {
  }

  build() {
    Navigation(this.navPathStack) {
      Column() {
        Image($r('app.media.ic_logo'))
          .width($r('app.float.logo_image_size'))
          .height($r('app.float.logo_image_size'))
          .margin({
            top: $r('app.float.logo_margin_top'),
            bottom: $r('app.float.logo_margin_bottom')
          })
        Text($r('app.string.login_page'))
          .fontSize($r('app.float.title_text_size'))
          .fontWeight(FontWeight.Medium)
          .fontColor($r('app.color.title_text_color'))
        Text($r('app.string.login_more'))
          .fontSize($r('app.float.normal_text_size'))
          .fontColor($r('app.color.login_text_color'))
          .margin({
            bottom: $r('app.float.login_bottom'),
            top: $r('app.float.login_top')
          })

        Column() {
          TextInput({ placeholder: $r('app.string.account'),  text: "13682215018"})
            .maxLength(11)
            .type(InputType.USER_NAME)
            .inputStyle()
            .onChange((value: string) => {
              this.loginViewModel.setAccount(value);
            })

          Line().lineStyle()

          TextInput({ placeholder: $r('app.string.password'),  text: "Aa111111" })
            .maxLength(Constants.INPUT_PASSWORD_LENGTH)
            .type(InputType.Password)
            .inputStyle()
            .onChange((value: string) => {
              this.loginViewModel.setPassword(value);
            })
        }
        .backgroundColor(Color.White)
        .borderRadius($r('app.float.input_border_radius'))
        .padding({
          top: $r('app.float.input_padding_top'),
          bottom: $r('app.float.input_padding_top'),
          left: $r('app.float.input_padding_left'),
          right: $r('app.float.input_padding_left')
        })

        Row() {
          Text($r('app.string.message_login')).blueTextStyle()
          Text($r('app.string.forgot_password')).blueTextStyle()
        }
        .justifyContent(FlexAlign.SpaceBetween)
        .width(Constants.FULL_PARENT)
        .padding({
          top: $r('app.float.forgot_margin_top'),
          left: $r('app.float.forgot_margin_left'),
          right: $r('app.float.forgot_margin_right')
        })

        Button($r('app.string.login'), { type: ButtonType.Capsule })
          .width(Constants.BUTTON_WIDTH)
          .height($r('app.float.login_button_height'))
          .fontSize($r('app.float.normal_text_size'))
          .fontWeight(FontWeight.Medium)
          .backgroundColor(this.loginViewModel.isLogin ? $r('app.color.login_button_color') :
            $r('app.color.button_color_unavailable'))
          .margin({
            top: $r('app.float.button_top'),
            bottom: $r('app.float.button_bottom')
          })
          .enabled(this.loginViewModel.isLogin)
          .onClick(async () => {
            await this.loginViewModel.login();
            this.getUIContext().getRouter().replaceUrl({
              url: 'pages/HomePage'
            }).catch((error: BusinessError) => {
              Logger.error(`replaceUrl error ${error.code}`)
            });
          })
        Text($r('app.string.register_account'))
          .fontColor($r('app.color.login_blue_color'))
          .fontSize($r('app.float.normal_text_size'))
          .fontWeight(FontWeight.Medium)
          .onClick(() => {
            // this.pageInfos.pushPathByName('register', null);
          })

        Blank()
      }
      .backgroundColor($r('app.color.background'))
      .height(Constants.FULL_PARENT)
      .width(Constants.FULL_PARENT)
      .padding({
        left: $r('app.float.page_padding_hor'),
        right: $r('app.float.page_padding_hor'),
        bottom: $r('app.float.login_page_bottom')
      })
    }
    .navDestination(this.PagesMap)
    .hideTitleBar(true)
    .hideToolBar(false)
    .mode(NavigationMode.Stack)
    .backgroundColor($r('app.color.background'))
  }
}