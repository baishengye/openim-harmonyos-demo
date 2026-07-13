//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "utils.h"
#ifndef IMDEMO_LOGIN_H
#define IMDEMO_LOGIN_H

napi_value InitSdk(napi_env env, napi_callback_info info);
napi_value UnInitSdk(napi_env env, napi_callback_info info);
napi_value Login(napi_env env, napi_callback_info info);
napi_value Logout(napi_env env, napi_callback_info info);
napi_value SetAppBackgroundStatus(napi_env env, napi_callback_info info);
napi_value NetworkStatusChanged(napi_env env, napi_callback_info info);
napi_value GetLoginStatus(napi_env env, napi_callback_info info);
napi_value GetLoginUser(napi_env env, napi_callback_info info);

#endif //IMDEMO_LOGIN_H
