import { ConversationItem, FriendUserItem } from "imsdk/src/main/ets/sdk/entity";
import { GroupAtType, MessageReceiveOptType, SessionType } from "imsdk/src/main/ets/sdk/enum";
import { TitleBar } from "../../component/TitleBar";
import { RouterName } from "../router/RouterMap";
import MyFriendViewModel from "./MyFriendViewModel";

@ComponentV2
export struct MyFriendView {
  @Local myFriendViewModel: MyFriendViewModel = new MyFriendViewModel()
  private scroller: Scroller = new Scroller();

  navPathStack: NavPathStack = new NavPathStack();
  aboutToAppear(): void {
    this.myFriendViewModel.load()
  }
  build() {
    NavDestination() {
      TitleBar({title:"我的好友"});
      Column() {
        List({ space: 1, scroller: this.scroller }) {
          ForEach(this.myFriendViewModel.friendList, (item: FriendUserItem, index: number) => {
            ListItem() {
              Row({space: 10}) {
                Image(item.faceURL != ""?item.faceURL:$r('app.media.Public_avatar'))
                  .width(48)
                  .height(48)

                Text(item.nickname)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
                  .margin({ bottom: 8 })
                  .textAlign(TextAlign.Start)
              }
              .width('100%')
              .height(72)
              .padding({ left: 10, right: 10 })
              .alignItems(VerticalAlign.Center)
              .onClick(async  ()=>{
                const conversationItem = await this.myFriendViewModel.getConversation(item.userID)
                this.navPathStack.pushPath({ name:  RouterName.Chat, param: conversationItem});
              })
            }
          });
        }.width("100%").height("100%")
      }
    }
    .hideTitleBar(true)
    .onReady((context: NavDestinationContext) => {
      this.navPathStack = context.pathStack;
    })
  }
}