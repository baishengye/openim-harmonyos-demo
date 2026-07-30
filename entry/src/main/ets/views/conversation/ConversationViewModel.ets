import { getSDK, ConversationItem, MessageItem, OnConvListener } from "imsdk";
import Constants from "../../api/Constants";
import Logger from "../../common/utils/Logger";

@ObservedV2
export class  ConversationViewModel {
  @Trace conversationList: ConversationItem[] = []

  async load() {
    // 设置会话监听器
    const convListener: OnConvListener = {
      onConversationChanged: (convList: string) => {
        try {
          const convs = JSON.parse(convList) as ConversationItem[];
          this.conversationList = [];
          this.conversationList.push(...convs);
        } catch (e) {
          Logger.error(`parse conversation list failed: ${e}`);
        }
      },
      onNewConversation: (convList: string) => {
        try {
          const convs = JSON.parse(convList) as ConversationItem[];
          this.conversationList.push(...convs);
        } catch (e) {
          Logger.error(`parse new conversation list failed: ${e}`);
        }
      }
    }
    getSDK().setConversationListener(convListener);

    // 获取会话列表
    getSDK().conversationManager.getAllConversationList().then((conv: ConversationItem[]) => {
      this.conversationList = [];
      this.conversationList.push(...conv);
    });
  }

  formatMillisecondsToTime(ms: number): string {
    const date = new Date(ms);

    const year = date.getFullYear();
    const month = String(date.getMonth() + 1).padStart(2, '0');
    const day = String(date.getDate()).padStart(2, '0');
    const hours = String(date.getHours()).padStart(2, '0');
    const minutes = String(date.getMinutes()).padStart(2, '0');
    const seconds = String(date.getSeconds()).padStart(2, '0');

    return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
  }

  getTextMessageContent(msg: string): string {
    const m = JSON.parse(msg) as MessageItem
    return m.textElem?.content??"";
  }

  getMessageTime(msg: string): string {
    const m = JSON.parse(msg) as MessageItem
    return this.formatMillisecondsToTime(m.sendTime);
  }
}