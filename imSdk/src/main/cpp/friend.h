//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "utils.h"
#ifndef IMDEMO_FRIENDSHIP_H
#define IMDEMO_FRIENDSHIP_H

napi_value GetSpecifiedFriendsInfo(napi_env env, napi_callback_info info);
napi_value GetFriendList(napi_env env, napi_callback_info info);
napi_value GetFriendListPage(napi_env env, napi_callback_info info);
napi_value SearchFriends(napi_env env, napi_callback_info info);
napi_value CheckFriend(napi_env env, napi_callback_info info);
napi_value AddFriend(napi_env env, napi_callback_info info);
napi_value UpdateFriends(napi_env env, napi_callback_info info);
napi_value DeleteFriend(napi_env env, napi_callback_info info);
napi_value GetFriendApplicationListAsRecipient(napi_env env, napi_callback_info info);
napi_value GetFriendApplicationListAsApplicant(napi_env env, napi_callback_info info);
napi_value AcceptFriendApplication(napi_env env, napi_callback_info info);
napi_value RefuseFriendApplication(napi_env env, napi_callback_info info);
napi_value GetFriendApplicationUnhandledCount(napi_env env, napi_callback_info info);
napi_value AddBlack(napi_env env, napi_callback_info info);
napi_value GetBlackList(napi_env env, napi_callback_info info);
napi_value RemoveBlack(napi_env env, napi_callback_info info);

#endif //IMDEMO_FRIENDSHIP_H
