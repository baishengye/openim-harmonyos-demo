//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "utils.h"
#ifndef IMDEMO_MISC_H
#define IMDEMO_MISC_H

napi_value SubscribeUsersStatus(napi_env env, napi_callback_info info);
napi_value UnSubscribeUsersStatus(napi_env env, napi_callback_info info);
napi_value GetSubscribeUsersStatus(napi_env env, napi_callback_info info);
napi_value GetUserStatus(napi_env env, napi_callback_info info);
napi_value GetUsersInfo(napi_env env, napi_callback_info info);
napi_value SetSelfInfo(napi_env env, napi_callback_info info);
napi_value GetSelfUserInfo(napi_env env, napi_callback_info info);
napi_value UploadFile(napi_env env, napi_callback_info info);
napi_value UpdateFcmToken(napi_env env, napi_callback_info info);
napi_value SetAppBadge(napi_env env, napi_callback_info info);
napi_value UploadLogs(napi_env env, napi_callback_info info);
napi_value Logs(napi_env env, napi_callback_info info);

#endif //IMDEMO_MISC_H
