import Constants from '../api/Constants';
import Logger from '../common/utils/Logger';
import { AppRuntime } from '../appruntime/AppRuntime';
import { IM } from '../sdkwrapper/IMAppWrapper';
import { ConversationInfo, FriendInfo, GroupInfo, UserInfo } from 'imsdk';

@Entry
@ComponentV2
struct HomePage {
  @Local index: number = Constants.CONVERSATION_TAB_INDEX;
  @Local conversations: ConversationInfo[] = [];
  @Local friends: FriendInfo[] = [];
  @Local groups: GroupInfo[] = [];
  @Local selfInfo: UserInfo | null = null;
  @Local isLoading: boolean = false;
  @Local errorMsg: string = '';
  private tabsController: TabsController = new TabsController();

  aboutToAppear(): void {
    this.loadSdkData();
  }

  private errorText(error: Object): string {
    if (error instanceof Error) {
      return error.message;
    }
    return JSON.stringify(error);
  }

  private async loadSdkData(): Promise<void> {
    if (this.isLoading) {
      return;
    }
    this.isLoading = true;
    this.errorMsg = '';
    try {
      await AppRuntime.getInstance().waitUntilReady();
      this.conversations = await IM.getAllConversationList();
      this.friends = await IM.getFriendList();
      this.groups = await IM.getJoinedGroupList();
      this.selfInfo = await IM.getSelfUserInfo();
      Logger.info(`SDK data loaded: conversations=${this.conversations.length}, friends=${this.friends.length}, groups=${this.groups.length}`);
    } catch (error) {
      this.errorMsg = this.errorText(error as Object);
      Logger.error(`load SDK data failed: ${this.errorMsg}`);
    } finally {
      this.isLoading = false;
    }
  }

  private async logout(): Promise<void> {
    if (this.isLoading) {
      return;
    }
    this.isLoading = true;
    this.errorMsg = '';
    try {
      await IM.logout();
      this.getUIContext().getRouter().replaceUrl({ url: 'pages/LoginPage' }).catch(() => {
        Logger.error('replace LoginPage failed');
      });
    } catch (error) {
      this.errorMsg = this.errorText(error as Object);
      Logger.error(`logout failed: ${this.errorMsg}`);
    } finally {
      this.isLoading = false;
    }
  }

  @Builder
  private baseTab(title: Resource, targetIndex: number, selectedImg: Resource, normalImg: Resource) {
    Column() {
      Image(this.index === targetIndex ? selectedImg : normalImg)
        .width($r('app.float.main_base_size'))
        .height($r('app.float.main_base_size'))
      Text(title)
        .margin({ top: $r('app.float.main_base_top') })
        .fontSize($r('app.float.main_tab_fontSize'))
        .fontColor(this.index === targetIndex ? $r('app.color.main_selected') : $r('app.color.main_normal'))
    }
    .margin({ top: $r('app.float.main_base_margin') })
    .height($r('app.float.main_bar_height'))
    .width(Constants.FULL_PARENT)
    .onClick(() => {
      this.index = targetIndex;
      this.tabsController.changeIndex(targetIndex);
    })
  }

  @Builder
  private pageHeader(title: string, summary: string) {
    Row() {
      Column({ space: 4 }) {
        Text(title)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
        Text(summary)
          .fontSize(13)
          .fontColor('#64748B')
      }
      .alignItems(HorizontalAlign.Start)
      .layoutWeight(1)
      Button('刷新')
        .type(ButtonType.Normal)
        .height(34)
        .enabled(!this.isLoading)
        .onClick(() => this.loadSdkData())
    }
    .width('100%')
    .padding({ left: 16, right: 16, top: 18, bottom: 12 })
  }

  @Builder
  private conversationsView() {
    Column() {
      this.pageHeader('消息', `共 ${this.conversations.length} 个会话`)
      if (this.conversations.length === 0 && !this.isLoading) {
        Text('暂无会话')
          .fontColor('#94A3B8')
          .margin({ top: 48 })
      } else {
        List({ space: 1 }) {
          ForEach(this.conversations, (item: ConversationInfo) => {
            ListItem() {
              Row({ space: 12 }) {
                Image(item.faceUrl.length > 0 ? item.faceUrl : $r('app.media.Public_avatar'))
                  .width(48)
                  .height(48)
                  .borderRadius(24)
                Column({ space: 6 }) {
                  Row() {
                    Text(item.showName || item.userID || item.groupID)
                      .fontSize(16)
                      .fontWeight(FontWeight.Medium)
                      .maxLines(1)
                      .layoutWeight(1)
                    if (item.unreadCount > 0) {
                      Text(`${item.unreadCount}`)
                        .fontSize(11)
                        .fontColor(Color.White)
                        .backgroundColor('#E84026')
                        .borderRadius(10)
                        .padding({ left: 6, right: 6, top: 2, bottom: 2 })
                    }
                  }
                  .width('100%')
                  Text(item.latestMsg || '暂无消息')
                    .fontSize(13)
                    .fontColor('#64748B')
                    .maxLines(1)
                    .textOverflow({ overflow: TextOverflow.Ellipsis })
                    .width('100%')
                }
                .alignItems(HorizontalAlign.Start)
                .layoutWeight(1)
              }
              .width('100%')
              .padding(14)
              .backgroundColor(Color.White)
            }
          }, (item: ConversationInfo) => item.conversationID)
        }
        .width('100%')
        .layoutWeight(1)
      }
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F8FAFC')
  }

  @Builder
  private contactsView() {
    Column() {
      this.pageHeader('通讯录', `${this.friends.length} 位好友，${this.groups.length} 个群组`)
      List({ space: 1 }) {
        ListItemGroup({ header: this.sectionHeader(`好友 (${this.friends.length})`) }) {
          ForEach(this.friends, (item: FriendInfo) => {
            ListItem() {
              this.contactRow(item.faceURL, item.remark || item.nickname || item.userID, item.userID)
            }
          }, (item: FriendInfo) => item.userID)
        }
        ListItemGroup({ header: this.sectionHeader(`群组 (${this.groups.length})`) }) {
          ForEach(this.groups, (item: GroupInfo) => {
            ListItem() {
              this.contactRow(item.faceURL, item.groupName || item.groupID, `${item.memberCount} 位成员`)
            }
          }, (item: GroupInfo) => item.groupID)
        }
      }
      .width('100%')
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F8FAFC')
  }

  @Builder
  private sectionHeader(title: string) {
    Text(title)
      .fontSize(13)
      .fontColor('#64748B')
      .width('100%')
      .padding({ left: 16, top: 10, bottom: 8 })
      .backgroundColor('#F1F5F9')
  }

  @Builder
  private contactRow(faceURL: string, title: string, subtitle: string) {
    Row({ space: 12 }) {
      Image(faceURL.length > 0 ? faceURL : $r('app.media.Public_avatar'))
        .width(42)
        .height(42)
        .borderRadius(21)
      Column({ space: 4 }) {
        Text(title).fontSize(16).maxLines(1)
        Text(subtitle).fontSize(12).fontColor('#94A3B8').maxLines(1)
      }
      .alignItems(HorizontalAlign.Start)
    }
    .width('100%')
    .padding({ left: 16, right: 16, top: 10, bottom: 10 })
    .backgroundColor(Color.White)
  }

  @Builder
  private mineView() {
    Column({ space: 18 }) {
      this.pageHeader('我的', `SDK ${IM.getSdkVersion()}`)
      Image(this.selfInfo?.faceURL || $r('app.media.Public_avatar'))
        .width(82)
        .height(82)
        .borderRadius(41)
      Text(this.selfInfo?.nickname || 'OpenIM 用户')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
      Text(`userID：${this.selfInfo?.userID || IM.getLoginUserID()}`)
        .fontSize(14)
        .fontColor('#64748B')
      Text(`登录状态：${IM.getLoginStatus()}`)
        .fontSize(14)
        .fontColor('#64748B')
      Button('退出登录')
        .width('80%')
        .enabled(!this.isLoading)
        .backgroundColor('#E84026')
        .onClick(() => this.logout())
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F8FAFC')
  }

  build() {
    Column() {
      if (this.errorMsg.length > 0) {
        Text(this.errorMsg)
          .width('100%')
          .padding(10)
          .fontSize(13)
          .fontColor('#B42318')
          .backgroundColor('#FEF3F2')
      }
      if (this.isLoading) {
        Progress({ value: 50, total: 100, type: ProgressType.Linear })
          .width('100%')
          .height(2)
          .color('#2563EB')
      }
      Tabs({ barPosition: BarPosition.End, controller: this.tabsController }) {
        TabContent() {
          this.conversationsView()
        }
        .tabBar(this.baseTab($r('app.string.message'), Constants.CONVERSATION_TAB_INDEX,
          $r('app.media.ic_home_tab1_sel'), $r('app.media.ic_home_tab1_nor')))

        TabContent() {
          this.contactsView()
        }
        .tabBar(this.baseTab($r('app.string.contacts_title'), Constants.CONTACTS_TAB_INDEX,
          $r('app.media.ic_home_tab2_sel'), $r('app.media.ic_home_tab2_nor')))

        TabContent() {
          this.mineView()
        }
        .tabBar(this.baseTab($r('app.string.mine_title'), Constants.MINE_TAB_INDEX,
          $r('app.media.ic_home_tab4_sel'), $r('app.media.ic_home_tab4_nor')))
      }
      .layoutWeight(1)
      .barHeight($r('app.float.main_bar_height'))
      .barMode(BarMode.Fixed)
      .onChange((targetIndex: number) => {
        this.index = targetIndex;
      })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F8FAFC')
  }
}
