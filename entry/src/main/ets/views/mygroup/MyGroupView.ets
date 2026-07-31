// import { TitleBar } from "../../component/TitleBar";
//
// @ComponentV2
// export struct MyGroupView {
//   navPathStack: NavPathStack = new NavPathStack();
//   build() {
//     NavDestination() {
//       TitleBar({title:"我的群组"});
//       Text("我的群组");
//     }
//     .hideTitleBar(true)
//     .onReady((context: NavDestinationContext) => {
//       this.navPathStack = context.pathStack;
//     })
//   }
// }