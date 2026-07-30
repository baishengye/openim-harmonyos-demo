import { getSDK, FriendApplicationItem } from "imsdk";
import Logger from "../../common/utils/Logger";

@ObservedV2
export default class NewFriendViewModel {
  @Trace list: FriendApplicationItem[] = [];
  async load() {
    this.list = [];
    try {
      Logger.error(`load friend application`);
      const recipients = await getSDK().friendshipManager.getFriendApplicationListAsRecipient({
        handleResults: [],
        offset: 1,
        count: 10
      });
      const applicants = await getSDK().friendshipManager.getFriendApplicationListAsApplicant({
        offset: 1,
        count: 10
      });
      this.list.push(...recipients, ...applicants);
    }catch (e) {
      Logger.error(`load friend application, err: ${e}`);
    }
  }
}