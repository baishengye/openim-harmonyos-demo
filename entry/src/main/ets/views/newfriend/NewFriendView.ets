// import { TitleBar } from "../../component/TitleBar";
// import NewFriendViewModel from "./NewFriendViewModel";
//
// @ComponentV2
// export struct NewFriendView {
//   @Local newFriendViewModel: NewFriendViewModel = new NewFriendViewModel()
//   navPathStack: NavPathStack = new NavPathStack();
//
//   aboutToAppear(): void {
//     this.newFriendViewModel.load()
//   }
//
//   build() {
//     NavDestination() {
//       TitleBar({title:"好友请求"});
//       Text("好友请求");
//     }
//     .hideTitleBar(true)
//     .onReady((context: NavDestinationContext) => {
//       this.navPathStack = context.pathStack;
//     })
//   }
// }