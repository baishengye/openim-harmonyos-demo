# OpenIM HarmonyOS native bridge

This directory wraps `libopenimsdk.so` as the `libimsdk.so` N-API module.

## ABI rules

- Treat `include/libopenimsdk.h` as the only source of truth.
- Pass callback function addresses as `uintptr_t`; never use `int` on arm64.
- Wrap every synchronous `char*` result in `SdkString` so `FreeString` is
  always called.
- Go can invoke callbacks from non-ArkTS threads. All callbacks must go through
  the thread-safe dispatcher in `callback.cpp`.

## Build

```sh
/Applications/DevEco-Studio.app/Contents/tools/hvigor/bin/hvigorw \
  --mode module \
  -p product=default \
  -p module=imsdk@default \
  -p buildMode=debug \
  assembleHar
```

The output is `imSdk/build/default/outputs/default/imsdk.har`.

## Known ABI gaps

The patch15 native SDK does not expose compatible implementations for the
legacy Harmony-only `setConversationRecvMessageOpt`, callback-style
`getSendMessageOpt`, or `setSignalingListener` wrappers. They throw an explicit
ArkTS error instead of allocating callbacks that can never complete. `hideConversation` is backed
by the native SDK and is fully available.
