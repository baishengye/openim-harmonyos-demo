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

The current native SDK header does not expose compatible implementations for
`setConversationRecvMessageOpt`, single-conversation `hideConversation`, or
the callback-style `getSendMessageOpt`. These wrappers throw an explicit
ArkTS error instead of silently allocating callbacks that can never complete.
