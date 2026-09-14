import { ChatView } from '../chat/ChatView';
import { MyFriendView } from '../myfriend/MyFriendView';
import { MyGroupView } from '../mygroup/MyGroupView';
import { NewFriendView } from '../newfriend/NewFriendView';
import { NewGroupView } from '../newgroup/NewGroupView';

export class RouterName {
  static readonly Chat: string = 'chat';
  static readonly NewFriend: string = 'new-friend';
  static readonly NewGroup: string = 'new-group';
  static readonly MyFriend: string = 'my-friend';
  static readonly MyGroup: string = 'my-group';
}

@Builder
export function RouterMap(name: string) {
  if (name === RouterName.Chat) ChatView();
  else if (name === RouterName.NewFriend) NewFriendView();
  else if (name === RouterName.NewGroup) NewGroupView();
  else if (name === RouterName.MyFriend) MyFriendView();
  else if (name === RouterName.MyGroup) MyGroupView();
}
