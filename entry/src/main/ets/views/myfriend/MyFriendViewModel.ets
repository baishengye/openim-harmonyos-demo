import { getSDK } from "imsdk";
import { ConversationItem, FriendUserItem, SDKError } from "imsdk/src/main/ets/sdk/entity";
import { SessionType } from "imsdk/src/main/ets/sdk/enum";
import Logger from "../../common/utils/Logger";

@ObservedV2
export default class MyFriendViewModel {
  @Trace friendList: FriendUserItem[] = [];
  async load() {
    getSDK().getFriendListPage(0, 1000, true).then((res) => {
      this.friendList = res
      Logger.error(`getFriendListPage, res: ${JSON.stringify(res)}`)
    }).catch((e: SDKError)=>{
      Logger.error(`getFriendListPage, errCode: ${e.errCode}, errMsg: ${e.errMsg}`)
    })
  }

  async getConversation(userID: string): Promise<ConversationItem> {
   return getSDK().getOneConversation({
      sourceID: userID,
      sessionType: SessionType.Single,
    })
  }
}