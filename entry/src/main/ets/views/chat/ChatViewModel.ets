import { getSDK } from "imsdk";
import {
  AdvancedGetMessageResult,
  ConversationItem, MessageItem, SDKError, SelfUserInfo } from "imsdk/src/main/ets/sdk/entity";
import { CbEvents } from "imsdk/src/main/ets/sdk/enum";
import Logger from "../../common/utils/Logger";

@ObservedV2
export class  ChatViewModel {
  private conversationItem?: ConversationItem;
  @Trace public messageList: MessageItem[] = [];
  public userID: string = "";
  public onInit(conversationItem: ConversationItem) {
    this.conversationItem = conversationItem
    getSDK().getSelfUserInfo().then((userInfo: SelfUserInfo)=> {
      this.userID = userInfo.userID
      getSDK().getAdvancedHistoryMessageListReverse({
        lastMinSeq: 0,
        count: 100,
        startClientMsgID: "",
        conversationID: this.conversationItem!.conversationID,
      }).then((msg: AdvancedGetMessageResult) => {
        this.messageList.push(...msg.messageList)
      })
      Logger.info(`new conversation ID: ${conversationItem.conversationID}, userID: ${conversationItem.userID}, myUserID: ${this.userID}`);
      this.initCB()
    })
  }

  private initCB() {
    Logger.info(`new OnRecvNewMessage init`);
    getSDK().on(CbEvents.OnRecvNewMessage, (data: MessageItem) => {
      Logger.info(`new OnRecvNewMessage`);
      this.messageList.push(data)
    })
    getSDK().on(CbEvents.OnRecvNewMessages, (data: MessageItem[]) => {
      Logger.info(`new OnRecvNewMessages: ${data.length}`);
      this.messageList.push(...data)
    })
  }

  async sendTextMessage(text: string): Promise<MessageItem> {
    Logger.info(`sendTextMessage: ${text}`)
    const msg = await getSDK().createTextMessage(text);
    const ok = getSDK().sendMessage({
      recvID: this.conversationItem!.userID,
      groupID: "",
      message: msg
    })
    this.messageList.push(msg)
    return ok;
  }
}