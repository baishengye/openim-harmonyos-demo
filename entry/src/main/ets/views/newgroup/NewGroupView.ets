import { GroupApplication } from 'imsdk';
import { IM } from '../../sdkwrapper/IMAppWrapper';
import { TitleBar } from '../../component/TitleBar';

@ComponentV2
export struct NewGroupView {
  @Local applications: GroupApplication[] = [];
  @Local groupID: string = '';
  @Local reqMsg: string = '申请加入群组';
  @Local errorMsg: string = '';
  @Local tip: string = '';
  @Local isLoading: boolean = false;
  private errorText(error: Object): string { return error instanceof Error ? error.message : JSON.stringify(error); }
  private async load(): Promise<void> {
    this.isLoading = true;
    try { this.applications = await IM.getGroupApplicationListAsRecipient() || []; }
    catch (error) { this.errorMsg = this.errorText(error as Object); }
    finally { this.isLoading = false; }
  }
  private async join(): Promise<void> {
    if (this.groupID.trim().length === 0) return;
    this.isLoading = true; this.errorMsg = ''; this.tip = '';
    try { await IM.joinGroup(this.groupID.trim(), this.reqMsg); this.tip = '入群申请已发送'; this.groupID = ''; }
    catch (error) { this.errorMsg = this.errorText(error as Object); }
    finally { this.isLoading = false; }
  }
  private async handle(item: GroupApplication, accept: boolean): Promise<void> {
    this.isLoading = true;
    try {
      if (accept) await IM.acceptGroupApplication(item.groupID, item.userID);
      else await IM.refuseGroupApplication(item.groupID, item.userID);
      await this.load();
    } catch (error) { this.errorMsg = this.errorText(error as Object); this.isLoading = false; }
  }
  build() {
    NavDestination() {
      Column() {
        TitleBar({ title: '群组申请' })
        Column({ space: 8 }) {
          TextInput({ placeholder: '输入群组 ID', text: this.groupID }).onChange((value: string) => this.groupID = value)
          TextInput({ placeholder: '申请信息', text: this.reqMsg }).onChange((value: string) => this.reqMsg = value)
          Button('申请加入群组').width('100%').enabled(!this.isLoading && this.groupID.trim().length > 0).onClick(() => this.join())
        }.padding(12).backgroundColor(Color.White)
        if (this.tip.length > 0) Text(this.tip).fontColor('#067647').padding(8)
        if (this.errorMsg.length > 0) Text(this.errorMsg).fontColor('#B42318').padding(8)
        Row() { Text('收到的入群申请').fontSize(18).fontWeight(FontWeight.Bold).layoutWeight(1); Button('刷新').onClick(() => this.load()) }.padding(12).width('100%')
        List({ space: 1 }) {
          ForEach(this.applications, (item: GroupApplication) => {
            ListItem() {
              Row({ space: 10 }) {
                Image(item.userFaceURL || $r('app.media.Public_avatar')).width(42).height(42).borderRadius(21)
                Column({ space: 3 }) {
                  Text(item.nickname || item.userID).fontSize(16)
                  Text(`${item.groupName || item.groupID} · ${item.reqMsg}`).fontSize(12).fontColor('#64748B').maxLines(1)
                }.alignItems(HorizontalAlign.Start).layoutWeight(1)
                if (item.handleResult === 0) {
                  Button('拒绝').backgroundColor('#64748B').onClick(() => this.handle(item, false))
                  Button('同意').onClick(() => this.handle(item, true))
                } else {
                  Text(item.handleResult === 1 ? '已同意' : '已拒绝').fontColor('#64748B')
                }
              }.width('100%').padding(10).backgroundColor(Color.White)
            }
          }, (item: GroupApplication) => `${item.groupID}-${item.userID}-${item.reqTime}`)
        }.layoutWeight(1).width('100%')
      }.height('100%').backgroundColor('#F5F7FA')
    }.hideTitleBar(true).onReady(() => this.load())
  }
}
