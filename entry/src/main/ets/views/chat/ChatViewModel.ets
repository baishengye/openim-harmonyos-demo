import { getSDK, Message, OnMsgListener, ViewType } from "imsdk";
import { ConversationItem, MessageItem } from "../../common/types/UITypes";
import Logger from "../../common/utils/Logger";

@ObservedV2
export class ChatViewModel {
  private conversationItem?: ConversationItem;
  @Trace public messageList: MessageItem[] = [];
  public userID: string = "";
  public onInit(conversationItem: ConversationItem) {
    this.conversationItem = conversationItem
    getSDK().userInfoManager.getSelfUserInfo().then((userInfo: Message) => {
      this.userID = userInfo.userID
      getSDK().messageManager.getAdvancedHistoryMessageListReverse(this.conversationItem!.conversationID, "", 100, ViewType.History).then((msgStr: string) => {
        try {
          const result = JSON.parse(msgStr);
          const msgList: Message[] = JSON.parse(result.data);
          this.messageList.push(...msgList.map(m => this.convertToMessageItem(m)))
        } catch (e) {
          Logger.error(`parse message failed: ${e}`);
        }
      })
      Logger.info(`new conversation ID: ${conversationItem.conversationID}, userID: ${conversationItem.userID}, myUserID: ${this.userID}`);
      this.initCB()
    })
  }

  private convertToMessageItem(msg: Message): MessageItem {
    const item = new MessageItem();
    item.clientMsgID = msg.clientMsgID;
    item.sendID = msg.sendID;
    item.senderNickname = msg.senderNickname;
    item.senderFaceUrl = msg.senderFaceUrl;
    item.conversationID = "";
    item.sessionType = msg.sessionType;
    item.groupID = msg.groupID;
    item.contentType = msg.contentType;
    item.sendTime = msg.sendTime;
    item.status = msg.status;
    item.isSelf = msg.sendID === this.userID;
    item.content = msg.textElem?.content ?? msg.customElem?.data ?? "";
    item.showTimestamp = false;
    return item;
  }

  private initCB() {
    Logger.info(`new OnRecvNewMessage init`);
    const msgListener: OnMsgListener = {
      onRecvNewMessage: (msg: string) => {
        Logger.info(`OnRecvNewMessage`);
        try {
          const msgItem = JSON.parse(msg) as MessageItem;
          this.messageList.push(msgItem)
        } catch (e) {
          Logger.error(`parse message failed: ${e}`);
        }
      },
      onRecvOnlineOnlyMessage: (msg: string) => {
        try {
          const msgs = JSON.parse(msg) as MessageItem[];
          Logger.info(`OnRecvOnlineOnlyMessage: ${msgs.length}`);
          this.messageList.push(...msgs)
        } catch (e) {
          Logger.error(`parse messages failed: ${e}`);
        }
      }
    }
    getSDK().setAdvancedMsgListener(msgListener)
  }

  async sendTextMessage(text: string): Promise<MessageItem> {
    Logger.info(`sendTextMessage: ${text}`)
    const msgStr = getSDK().messageManager.createTextMessage(text);
    const msg = JSON.parse(msgStr) as MessageItem;
    getSDK().messageManager.sendMessage(
      this.conversationItem!.userID,
      "",
      msgStr
    )
    this.messageList.push(msg)
    return msg;
  }
}