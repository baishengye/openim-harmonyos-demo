import { IMSdk } from "imsdk";
import { FriendApplicationItem, SDKError } from "imsdk/src/main/ets/sdk/entity";
import Logger from "../../common/utils/Logger";

@ObservedV2
export default class NewFriendViewModel {
  @Trace list: FriendApplicationItem[] = [];
  async load() {
    this.list = [];
    try {
      Logger.error(`load friend application`);
      const recipients = await IMSdk.getInstance().getFriendApplicationListAsRecipient({
        handleResults: [],
        offset: 1,
        count: 10
      });
      const applicants = await IMSdk.getInstance().getFriendApplicationListAsApplicant({
        offset: 1,
        count: 10
      });
      this.list.push(...recipients, ...applicants);
    }catch (e) {
      const err = e as SDKError;
      Logger.error(`load friend application, ${err.errCode}, ${err.errMsg}`);
    }
  }
}