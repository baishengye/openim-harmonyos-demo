import Constants from '../api/Constants';
import Logger from '../common/utils/Logger';
import ContactsView from '../views/contacts/ContactsView';
import ConversationView from '../views/conversation/ConversationView';
import MineView from '../views/mine/MineView';
import { RouterMap } from '../views/router/RouterMap';

@Entry
@ComponentV2
struct HomePage {
  @Provider('navPathStack') navPathStack: NavPathStack = new NavPathStack();
  @Local index: number = Constants.CONVERSATION_TAB_INDEX;
  private tabsController: TabsController = new TabsController();

  @Builder
  baseTab(title: Resource, targetIndex: number, selectedImg: Resource, normalImg: Resource) {
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
      this.tabsController.changeIndex(this.index);
    })
  }

  @Builder
  tabTitles(title: Resource) {
    Text(title)
      .fontWeight(FontWeight.Medium)
      .fontSize($r('app.float.title_text_size'))
      .margin({ top: $r('app.float.main_titles_margin') })
      .padding({ left: $r('app.float.main_titles_padding') })
  }

  onPageShow(): void {
    Logger.info(`LoginPage onPageShow`);
  }

  build() {
    Navigation(this.navPathStack) {
      Tabs({
        barPosition: BarPosition.End,
        controller: this.tabsController
      }) {
        TabContent() {
          ConversationView()
        }
        .backgroundColor($r('app.color.main_background'))
        .tabBar(this.baseTab($r('app.string.message'), Constants.CONVERSATION_TAB_INDEX,
          $r('app.media.ic_home_tab1_sel'), $r('app.media.ic_home_tab1_nor')))

        TabContent() {
          ContactsView()
        }
        .backgroundColor($r('app.color.main_background'))
        .tabBar(this.baseTab($r('app.string.contacts_title'), Constants.CONTACTS_TAB_INDEX,
          $r('app.media.ic_home_tab2_sel'), $r('app.media.ic_home_tab2_nor')))

        TabContent() {
          MineView()
        }
        .backgroundColor($r('app.color.main_background'))
        .tabBar(this.baseTab($r('app.string.mine_title'), Constants.MINE_TAB_INDEX,
          $r('app.media.ic_home_tab4_sel'), $r('app.media.ic_home_tab4_nor')))
      }
      .width(Constants.FULL_PARENT)
      .backgroundColor(Color.White)
      .barHeight($r('app.float.main_bar_height'))
      .barMode(BarMode.Fixed)
      .onChange((index: number) => {
        this.index = index
      })
    }
    .navDestination(RouterMap)
    .hideTitleBar(true)
    .hideToolBar(false)
    .mode(NavigationMode.Stack)
    .backgroundColor($r('app.color.background'))
  }
}