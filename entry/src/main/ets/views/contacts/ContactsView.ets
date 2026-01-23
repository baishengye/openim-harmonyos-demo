import Logger from "../../common/utils/Logger"
import { RouterName } from "../router/RouterMap";

@ComponentV2
export default struct ContactsView {
  @Consumer('navPathStack') navPathStack: NavPathStack = new NavPathStack();

  build() {
    Column({space: 0.5}){
      this.ItemView($r('app.media.ic_new_friend'), "新好友", true, () => {
        this.navPathStack.pushPath({ name: RouterName.NewFriend});
      })
      this.ItemView($r('app.media.ic_new_group'), "新群组", true, () => {
        this.navPathStack.pushPath({ name: RouterName.NewGroup});
      })
      this.ItemView($r('app.media.ic_my_friend'), "我的好友", true, () => {
        this.navPathStack.pushPath({ name: RouterName.MyFriend});
      })
      this.ItemView($r('app.media.ic_my_group'), "我的群组", true, () => {
        this.navPathStack.pushPath({ name: RouterName.MyGroup});
      })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Start) // 关键修改：顶部对齐
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  ItemView(assetsName: Resource, label: string, showRightArrow: boolean, onTap: () => void) {
    Row() {
      Image(assetsName)
        .width($r('app.float.other_image_size'))
        .height($r('app.float.other_image_size'))
        .margin({ right: 12 })

      Text(label)
        .fontSize(16)
        .flexGrow(1)

      if (showRightArrow) {
        Image($r('app.media.ic_right_arrow'))
          .width(20)
          .height(20)
      }
    }
    .width('100%')
    .padding(12)
    .backgroundColor($r('app.color.component_background'))
    .alignItems(VerticalAlign.Center)
    .onClick(() => onTap?.()) // 安全调用回调
  }
}