import { ConversationItem, MessageItem } from "imsdk";
import Logger from "../../common/utils/Logger";
import { RouterName } from "../router/RouterMap";
import { ConversationViewModel } from "./ConversationViewModel";


@ComponentV2
export default struct ConversationView {
  @Local conversationViewModel:  ConversationViewModel = new ConversationViewModel()
  @Consumer('navPathStack') navPathStack: NavPathStack = new NavPathStack();

  private scroller: Scroller = new Scroller();
  @Local isFlag: boolean = false;
  aboutToAppear() {
    Logger.info("aboutToAppear")
    this.conversationViewModel.load()
  }

  build() {
    Stack({ alignContent: Alignment.BottomEnd }) {
      Column() {
        List({ space: 1, scroller: this.scroller }) {
          ForEach(this.conversationViewModel.conversationList, (item: ConversationItem, index: number) => {
            ListItem() {
              Row() {
                Image($r('app.media.Public_avatar'))
                  .width(48)
                  .height(48)

                Column() {
                  Row() {
                    Column() {
                      Text(item.showName)
                        .fontSize(16)
                        .fontWeight(FontWeight.Bold)
                        .margin({ bottom: 8 })
                        .textAlign(TextAlign.Start)
                      Text(this.conversationViewModel.getTextMessageContent(item.latestMsg))
                        .fontSize(16)
                        .maxLines(1)
                        .constraintSize({ maxWidth: '70%' })
                        .textOverflow({ overflow: TextOverflow.Ellipsis })
                    }
                    .height('100%')
                    .justifyContent(FlexAlign.Center)
                    .alignItems(HorizontalAlign.Start)

                    Text(this.conversationViewModel.getMessageTime(item.latestMsg))
                      .fontSize(12)
                      .margin({ bottom: 20 })
                      .fontColor(Color.Gray)
                  }
                  .width('80%')
                  .justifyContent(FlexAlign.SpaceBetween)

                  //Add underline.
                  Line().width('328vp').height(1).stroke(Color.Black).backgroundColor('#F5F5F5')
                }
              }
              .width('100%')
              .height(72)
              .padding({ left: 4, right: 4 })
              .backgroundColor('#FFFFFF')
              .justifyContent(FlexAlign.SpaceAround)
            }
            .onClick(() => {
              this.navPathStack.pushPath({ name: RouterName.Chat, param: item });
            })
            .transition({ type: TransitionType.Delete, opacity: 0 })
          })
        }
        .width('100%')
        .height('100%')
        .scrollBar(BarState.Off)
        .contentEndOffset(8)
        .sticky(StickyStyle.Header)
        // [Start onWillScroll]
        .onWillScroll(() => {
          if (this.scroller.currentOffset().yOffset > 100) {
            this.isFlag = true;
          } else {
            this.isFlag = false;
          }
        })
        // [End onWillScroll]
        .onItemMove(() => {
          return true;
        })
      }
      .width('100%')
      .height('100%')

      // [Start Back_to_top]
      if (this.isFlag) {
        Image($r('app.media.arrow_up_circle_fill'))
          .width(36)
          .height(36)
          .margin({ right: 10, bottom: 10 })
          .onClick(() => {
            this.scroller.scrollToIndex(0, true);
            this.isFlag = false;
          })
      }
      // [End Back_to_top]
    }
    .width('100%')
    .height('100%')
  }

}