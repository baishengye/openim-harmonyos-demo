import { MessageItem } from "imsdk/src/main/ets/sdk/entity";
import { BackButton } from "../../component/BackButton";
import { ChatViewModel } from "./ChatViewModel";

@ComponentV2
export struct ChatView {
  private scroller: Scroller = new Scroller();
  private chatViewModel: ChatViewModel = new ChatViewModel();
  @Local isRefreshing: boolean = false;
  @Local inputMessage: string = '';

  navPathStack: NavPathStack = new NavPathStack();
  context = this.getUIContext().getHostContext();

  build() {
    NavDestination() {
      Column() {
        this.headView()
        Column() {
          // [Start Refresh]
          Refresh({ refreshing: $$this.isRefreshing }) {
            // [Start initialIndex_scrollEdge]
            List({ space: 10, scroller: this.scroller, initialIndex: this.chatViewModel.messageList.length - 1 }) {
              ForEach(this.chatViewModel.messageList, (item: MessageItem, index: number) => {
                ListItem() {
                  if (item.sendID !== this.chatViewModel.userID) {
                    Row() {
                      Image(item.senderFaceUrl === ""? $r('app.media.Public_avatar') : item.senderFaceUrl)
                        .width(36)
                        .height(36)
                        .margin({ right: 8 })

                      Text(item.textElem?.content)
                        .fontSize(16)
                        .constraintSize({ maxWidth: '70%' })
                        .backgroundColor('#F1F3F5')
                        .borderRadius(12)
                        .padding({
                          top: 8,
                          bottom: 8,
                          left: 12,
                          right: 12
                        })
                    }
                    .width('100%')
                    .constraintSize({ minHeight: 48 })
                    .justifyContent(FlexAlign.Start)
                  } else {
                    Row() {
                      Text(item.textElem?.content)
                        .fontSize(16)
                        .backgroundColor('#F1F3F5')
                        .borderRadius(12)
                        .padding({
                          top: 8,
                          bottom: 8,
                          left: 12,
                          right: 12
                        })
                      Image($r('app.media.Public_avatar'))
                        .width(36)
                        .height(36)
                        .margin({ left: 8 })
                    }
                    .width('100%')
                    .height(48)
                    .justifyContent(FlexAlign.End)
                  }
                }
              })
            }
            .onAppear(() => {
              // Initialize display to the bottom.
              this.scroller.scrollEdge(Edge.Bottom);
            })
            // [End initialIndex_scrollEdge]
            .scrollBar(BarState.Off)
            .contentEndOffset(8)
            .width('100%')
            .height('100%')
          }
          .width('100%')
          .height('100%')
          .refreshOffset(64)
          .pullToRefresh(true)
          .onRefreshing(() => {
            setTimeout(() => {
              //this.getLastTenElements(this.itemMessage);
              this.isRefreshing = false;
            }, 1500)
          })

          // [End Refresh]
        }
        .width('100%')
        .height('calc(100% - 100vp)')
        .padding({
          left: 16,
          right: 16
        })
        .justifyContent(FlexAlign.Start)
        .expandSafeArea([SafeAreaType.KEYBOARD])

        Column() {
          Row() {
            Row({ space: 12 }) {
              Image($r('app.media.mic_filled'))
                .width(28)
                .height(28)

              Image($r('app.media.emoji'))
                .width(28)
                .height(28)
            }

            // [Start TextInput]
            TextInput({ placeholder: 'input your word...', text: this.inputMessage })
              .height(40)
              .width(200)
              .margin({
                left: 12,
                right: 12
              })
              .onBlur(() => {
                this.scroller.scrollEdge(Edge.Bottom);
              })
              .onChange((value) => {
                this.inputMessage = value;
              })
            // [End TextInput]

            Row() {
              Row({ space: 12 }) {
                Image($r('app.media.plus_circle'))
                  .width(28)
                  .height(28)
                // [Start SendMessage]
                Image(this.inputMessage === '' ? $r('app.media.send_off') : $r('app.media.send_on'))
                  .width(28)
                  .height(28)
                  .onClick(() => {
                    if (this.inputMessage.trim() === '') {
                      return;
                    }
                    this.chatViewModel.sendTextMessage(this.inputMessage).finally(()=>{
                      this.scroller.scrollEdge(Edge.Bottom);
                    });
                    this.inputMessage = '';
                  })
                // [End SendMessage]
              }
            }
          }
          .justifyContent(FlexAlign.SpaceBetween)
        }
        .padding({
          top: 8,
          bottom: 8
        })
        .backgroundColor('#F1F3F5')
        .width('100%')
        .height(80)
      }.width('100%').height('100%').justifyContent(FlexAlign.SpaceBetween)
    }.hideTitleBar(true)
    .onReady((context: NavDestinationContext) => {
      this.chatViewModel.onInit(JSON.parse(JSON.stringify(context.pathInfo.param)))
      this.navPathStack = context.pathStack;
    })
  }

  @Builder
  headView() {
    Stack() {
      Text("聊天")
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
      Row() {
        BackButton()
          .width(24)
          .height(24)
          .onClick(()=>{
            this.navPathStack.pop()
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween) // 关键布局
    }
    .width('100%')
    .height(56)
    .alignContent(Alignment.Center)
    .padding({left: 10, right: 10})
  }
}