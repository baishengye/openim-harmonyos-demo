import { getSDK } from "imsdk";
import { ConversationItem, MessageItem } from "imsdk/src/main/ets/sdk/entity";
import { CbEvents } from "imsdk/src/main/ets/sdk/enum";
import Constants from "../../api/Constants";

@ObservedV2
export class  ConversationViewModel {
  @Trace conversationList: ConversationItem[] = []
  async load() {
    getSDK().on(CbEvents.OnConversationChanged, () => {
      getSDK().getAllConversationList().then((conv: ConversationItem[]) => {
        this.conversationList = []
        this.conversationList.push(...conv)
      })
    })
    getSDK().getAllConversationList().then((conv: ConversationItem[]) => {
      this.conversationList = []
      this.conversationList.push(...conv)
    })
  }
  formatMillisecondsToTime(ms: number): string {
    const date = new Date(ms);

    const year = date.getFullYear();
    const month = String(date.getMonth() + 1).padStart(2, '0'); // getMonth() 是 0-11
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