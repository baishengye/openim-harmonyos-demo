import { TitleBar } from "../../component/TitleBar";

@ComponentV2
export struct NewGroupView {
  navPathStack: NavPathStack = new NavPathStack();
  build() {
    NavDestination() {
      TitleBar({title:"加群请求"});
      Text("加群请求");
    }
    .hideTitleBar(true)
    .onReady((context: NavDestinationContext) => {
      this.navPathStack = context.pathStack;
    })
  }
}