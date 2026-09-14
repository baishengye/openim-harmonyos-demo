import { FriendApplication } from 'imsdk';
import { IM } from '../../sdkwrapper/IMAppWrapper';
import { TitleBar } from '../../component/TitleBar';

@ComponentV2
export struct NewFriendView {
  @Local applications: FriendApplication[] = [];
  @Local userID: string = '';
  @Local reqMsg: string = '你好，我想加你为好友';
  @Local errorMsg: string = '';
  @Local tip: string = '';
  @Local isLoading: boolean = false;

  private errorText(error: Object): string { return error instanceof Error ? error.message : JSON.stringify(error); }
  private async load(): Promise<void> {
    this.isLoading = true;
    try { this.applications = await IM.getFriendApplicationListAsRecipient() || []; }
    catch (error) { this.errorMsg = this.errorText(error as Object); }
    finally { this.isLoading = false; }
  }
  private async add(): Promise<void> {
    if (this.userID.trim().length === 0) return;
    this.isLoading = true; this.errorMsg = ''; this.tip = '';
    try { await IM.addFriend(this.userID.trim(), this.reqMsg); this.tip = '好友申请已发送'; this.userID = ''; }
    catch (error) { this.errorMsg = this.errorText(error as Object); }
    finally { this.isLoading = false; }
  }
  private async handle(item: FriendApplication, accept: boolean): Promise<void> {
    this.isLoading = true;
    try {
      if (accept) await IM.acceptFriendApplication(item.fromUserID);
      else await IM.refuseFriendApplication(item.fromUserID);
      await this.load();
    } catch (error) { this.errorMsg = this.errorText(error as Object); this.isLoading = false; }
  }
  build() {
    NavDestination() {
      Column() {
        TitleBar({ title: '好友申请' })
        Column({ space: 8 }) {
          TextInput({ placeholder: '输入用户 ID', text: this.userID }).onChange((value: string) => this.userID = value)
          TextInput({ placeholder: '验证信息', text: this.reqMsg }).onChange((value: string) => this.reqMsg = value)
          Button('发送好友申请').width('100%').enabled(!this.isLoading && this.userID.trim().length > 0).onClick(() => this.add())
        }.padding(12).backgroundColor(Color.White)
        if (this.tip.length > 0) Text(this.tip).fontColor('#067647').padding(8)
        if (this.errorMsg.length > 0) Text(this.errorMsg).fontColor('#B42318').padding(8)
        Row() { Text('收到的申请').fontSize(18).fontWeight(FontWeight.Bold).layoutWeight(1); Button('刷新').onClick(() => this.load()) }.padding(12).width('100%')
        List({ space: 1 }) {
          ForEach(this.applications, (item: FriendApplication) => {
            ListItem() {
              Row({ space: 10 }) {
                Image(item.fromFaceURL || $r('app.media.Public_avatar')).width(42).height(42).borderRadius(21)
                Column({ space: 3 }) {
                  Text(item.fromNickname || item.fromUserID).fontSize(16)
                  Text(item.reqMsg || item.fromUserID).fontSize(12).fontColor('#64748B').maxLines(1)
                }.alignItems(HorizontalAlign.Start).layoutWeight(1)
                if (item.handleResult === 0) {
                  Button('拒绝').backgroundColor('#64748B').onClick(() => this.handle(item, false))
                  Button('同意').onClick(() => this.handle(item, true))
                } else {
                  Text(item.handleResult === 1 ? '已同意' : '已拒绝').fontColor('#64748B')
                }
              }.width('100%').padding(10).backgroundColor(Color.White)
            }
          }, (item: FriendApplication) => `${item.fromUserID}-${item.createTime}`)
        }.layoutWeight(1).width('100%')
      }.height('100%').backgroundColor('#F5F7FA')
    }.hideTitleBar(true).onReady(() => this.load())
  }
}
