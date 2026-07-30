import { getSDK, ConversationItem, FriendUserItem, SessionType } from "imsdk";
import Logger from "../../common/utils/Logger";

@ObservedV2
export default class MyFriendViewModel {
  @Trace friendList: FriendUserItem[] = [];
  async load() {
    getSDK().friendshipManager.getFriendListPage(0, 1000, true).then((res) => {
      this.friendList = res
      Logger.error(`getFriendListPage, res: ${JSON.stringify(res)}`)
    }).catch((e)=>{
      Logger.error(`getFriendListPage, err: ${e}`)
    })
  }

  async getConversation(userID: string): Promise<ConversationItem> {
   return getSDK().conversationManager.getOneConversation({
      sourceID: userID,
      sessionType: SessionType.Single,
    })
  }
}