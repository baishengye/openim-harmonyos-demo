import { BackButton } from "./BackButton"

@ComponentV2
export struct TitleBar {
  @Consumer('navPathStack') navPathStack: NavPathStack = new NavPathStack();
  @Param title: string = "";
  @Event onBack?: () => void = undefined; //正确用法
  build() {
    Stack() {
      Text(this.title)
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
      Row() {
        BackButton()
          .width(24)
          .height(24)
          .onClick(()=>{
            if (this.onBack != undefined) {
                this.onBack();
            } else {
              this.navPathStack.pop();
            }
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)
    }
    .width('100%')
    .height(56)
    .alignContent(Alignment.Center)
    .padding({left: 10, right: 10})
  }
}