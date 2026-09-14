import { ConversationInfo, GroupInfo } from 'imsdk';
import { IM } from '../../sdkwrapper/IMAppWrapper';
import { TitleBar } from '../../component/TitleBar';
import { RouterName } from '../router/RouterMap';

@ComponentV2
export struct MyGroupView {
  @Local groups: GroupInfo[] = [];
  @Local errorMsg: string = '';
  @Local isLoading: boolean = false;
  private navPathStack: NavPathStack = new NavPathStack();

  private async load(): Promise<void> {
    this.isLoading = true;
    try { this.groups = await IM.getJoinedGroupList() || []; }
    catch (error) { this.errorMsg = error instanceof Error ? error.message : JSON.stringify(error); }
    finally { this.isLoading = false; }
  }
  private async openChat(item: GroupInfo): Promise<void> {
    try {
      const conversation: ConversationInfo = await IM.getOneConversation(2, item.groupID);
      this.navPathStack.pushPath({ name: RouterName.Chat, param: conversation });
    } catch (error) { this.errorMsg = error instanceof Error ? error.message : JSON.stringify(error); }
  }
  build() {
    NavDestination() {
      Column() {
        TitleBar({ title: '我的群组' })
        if (this.errorMsg.length > 0) Text(this.errorMsg).fontColor('#B42318').padding(8)
        if (this.isLoading) LoadingProgress().width(28).height(28)
        List({ space: 1 }) {
          ForEach(this.groups, (item: GroupInfo) => {
            ListItem() {
              Row({ space: 12 }) {
                Image(item.faceURL || $r('app.media.Public_avatar')).width(46).height(46).borderRadius(23)
                Column({ space: 4 }) {
                  Text(item.groupName || item.groupID).fontSize(16)
                  Text(`${item.memberCount} 位成员 · ${item.groupID}`).fontSize(12).fontColor('#94A3B8')
                }.alignItems(HorizontalAlign.Start)
              }.width('100%').padding(12).backgroundColor(Color.White)
            }.onClick(() => this.openChat(item))
          }, (item: GroupInfo) => item.groupID)
        }.layoutWeight(1).width('100%')
      }.height('100%').backgroundColor('#F5F7FA')
    }.hideTitleBar(true).onReady((context: NavDestinationContext) => { this.navPathStack = context.pathStack; this.load(); })
  }
}
