// @State isPressed: boolean = false;
//
// Image($r('app.media.back_icon'))
//   .opacity(this.isPressed ? 0.6 : 1) // 按下透明度变化
//   .onTouch((event) => {
//     if (event.type === TouchType.Down) {
//       this.isPressed = true;
//     } else if (event.type === TouchType.Up) {
//       this.isPressed = false;
//     }
//   })

@ComponentV2
export struct BackButton {
  @Local isPressed: boolean = false;
  build() {
    Image($r('app.media.ic_back_black'))
      .opacity(this.isPressed ? 0.6 : 1) // 按下透明度变化
      .onTouch((event) => {
        if (event.type === TouchType.Down) {
          this.isPressed = true;
        } else if (event.type === TouchType.Up) {
          this.isPressed = false;
        }
      })
  }
}