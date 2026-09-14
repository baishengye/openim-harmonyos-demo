import { C2CReadReceiptInfo, ConversationInfo, Message, MsgListener, RevokedInfo } from 'imsdk';
import { IM } from '../../sdkwrapper/IMAppWrapper';
import { TitleBar } from '../../component/TitleBar';

class ChatMsgListener implements MsgListener {
  private onMessage: (message: Message) => void;
  private onRevoked: (clientMsgID: string) => void;
  constructor(onMessage: (message: Message) => void, onRevoked: (clientMsgID: string) => void) {
    this.onMessage = onMessage;
    this.onRevoked = onRevoked;
  }
  onRecvNewMessage(message: Message): void { this.onMessage(message); }
  onRecvC2CReadReceipt(_list: C2CReadReceiptInfo[]): void {}
  onNewRecvMessageRevoked(message: RevokedInfo): void { this.onRevoked(message.clientMsgID); }
  onRecvOfflineNewMessage(messages: Message[]): void {
    if (messages) messages.forEach((message: Message) => this.onMessage(message));
  }
  onMsgDeleted(message: Message): void { this.onRevoked(message.clientMsgID); }
  onRecvOnlineOnlyMessage(_message: string): void {}
}

@ComponentV2
export struct ChatView {
  @Local conversation: ConversationInfo = new ConversationInfo();
  @Local messages: Message[] = [];
  @Local inputText: string = '';
  @Local isLoading: boolean = false;
  @Local errorMsg: string = '';
  private scroller: Scroller = new Scroller();

  private errorText(error: Object): string {
    return error instanceof Error ? error.message : JSON.stringify(error);
  }

  private async loadMessages(): Promise<void> {
    if (!this.conversation || !this.conversation.conversationID) return;
    this.isLoading = true;
    this.errorMsg = '';
    try {
      const result = await IM.getAdvancedHistoryMessageList(this.conversation.conversationID, '', 100);
      this.messages = result && result.messageList ? result.messageList : [];
      await IM.markConversationMessageAsRead(this.conversation.conversationID);
    } catch (error) {
      this.errorMsg = this.errorText(error as Object);
    } finally {
      this.isLoading = false;
    }
  }

  private belongsToCurrentConversation(message: Message): boolean {
    if (this.conversation.conversationType === 2) return message.groupID === this.conversation.groupID;
    return message.sendID === this.conversation.userID || message.recvID === this.conversation.userID;
  }

  private receiveMessage(message: Message): void {
    if (!message) return;
    if (!this.belongsToCurrentConversation(message)) return;
    if (this.messages.some((item: Message) => item.clientMsgID === message.clientMsgID)) return;
    this.messages = [...this.messages, message];
    this.scroller.scrollEdge(Edge.Bottom);
    IM.markConversationMessageAsRead(this.conversation.conversationID).catch(() => {});
  }

  private removeMessage(clientMsgID: string): void {
    this.messages = this.messages.filter((item: Message) => item.clientMsgID !== clientMsgID);
  }

  private messageText(message: Message): string {
    if (!message) return '[无效消息]';
    if (message.textElem && message.textElem.content) return message.textElem.content;
    if (message.pictureElem) return '[图片]';
    if (message.soundElem) return '[语音]';
    if (message.videoElem) return '[视频]';
    if (message.fileElem) return `[文件] ${message.fileElem.fileName || ''}`;
    if (message.customElem) return '[自定义消息]';
    return '[消息]';
  }

  private async sendText(): Promise<void> {
    const text = this.inputText.trim();
    if (text.length === 0 || this.isLoading) return;
    this.inputText = '';
    try {
      const message = IM.createTextMessage(text);
      const sent = await IM.sendMessage(message,
        this.conversation.conversationType === 1 ? this.conversation.userID : '',
        this.conversation.conversationType === 2 ? this.conversation.groupID : '');
      this.messages = [...this.messages, sent];
      this.scroller.scrollEdge(Edge.Bottom);
    } catch (error) {
      this.inputText = text;
      this.errorMsg = this.errorText(error as Object);
    }
  }

  build() {
    NavDestination() {
      Column() {
        Row() {
          TitleBar({ title: this.conversation.showName || '聊天' }).layoutWeight(1)
          Button('刷新').margin({ right: 8 }).onClick(() => this.loadMessages())
        }.width('100%')
        if (this.errorMsg.length > 0) {
          Text(this.errorMsg).width('100%').padding(8).fontColor('#B42318').backgroundColor('#FEF3F2')
        }
        if (this.isLoading) LoadingProgress().width(28).height(28)
        List({ space: 10, scroller: this.scroller }) {
          ForEach(this.messages, (item: Message) => {
            ListItem() {
              Row() {
                Text(this.messageText(item))
                  .fontSize(16)
                  .padding(10)
                  .borderRadius(10)
                  .backgroundColor(item.sendID === IM.getLoginUserID() ? '#CDE8FF' : '#FFFFFF')
              }
              .width('100%')
              .justifyContent(item.sendID === IM.getLoginUserID() ? FlexAlign.End : FlexAlign.Start)
            }
          }, (item: Message, index: number) => item && item.clientMsgID ? item.clientMsgID : `${index}`)
        }
        .layoutWeight(1)
        .width('100%')
        .padding(12)
        Row({ space: 8 }) {
          TextInput({ placeholder: '输入消息', text: this.inputText })
            .layoutWeight(1)
            .onChange((value: string) => this.inputText = value)
            .onSubmit(() => this.sendText())
          Button('发送').enabled(this.inputText.trim().length > 0).onClick(() => this.sendText())
        }
        .padding(10)
        .backgroundColor(Color.White)
      }
      .height('100%')
      .backgroundColor('#F5F7FA')
    }
    .hideTitleBar(true)
    .onReady((context: NavDestinationContext) => {
      const param = context.pathInfo.param as ConversationInfo;
      if (param) this.conversation = param;
      IM.setAdvancedMsgListener(new ChatMsgListener(
        (message: Message) => this.receiveMessage(message),
        (clientMsgID: string) => this.removeMessage(clientMsgID)));
      this.loadMessages();
    })
  }
}
