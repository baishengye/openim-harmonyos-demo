//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "utils.h"
#ifndef IMDEMO_GROUP_H
#define IMDEMO_GROUP_H

napi_value CreateGroup(napi_env env, napi_callback_info info);
napi_value JoinGroup(napi_env env, napi_callback_info info);
napi_value QuitGroup(napi_env env, napi_callback_info info);
napi_value DismissGroup(napi_env env, napi_callback_info info);
napi_value ChangeGroupMute(napi_env env, napi_callback_info info);
napi_value ChangeGroupMemberMute(napi_env env, napi_callback_info info);
napi_value SetGroupMemberInfo(napi_env env, napi_callback_info info);
napi_value GetJoinedGroupList(napi_env env, napi_callback_info info);
napi_value GetJoinedGroupListPage(napi_env env, napi_callback_info info);
napi_value GetSpecifiedGroupsInfo(napi_env env, napi_callback_info info);
napi_value SearchGroups(napi_env env, napi_callback_info info);
napi_value SetGroupInfo(napi_env env, napi_callback_info info);
napi_value GetGroupMemberList(napi_env env, napi_callback_info info);
napi_value GetGroupMemberOwnerAndAdmin(napi_env env, napi_callback_info info);
napi_value GetGroupMemberListByJoinTimeFilter(napi_env env, napi_callback_info info);
napi_value GetSpecifiedGroupMembersInfo(napi_env env, napi_callback_info info);
napi_value KickGroupMember(napi_env env, napi_callback_info info);
napi_value TransferGroupOwner(napi_env env, napi_callback_info info);
napi_value InviteUserToGroup(napi_env env, napi_callback_info info);
napi_value GetGroupApplicationListAsRecipient(napi_env env, napi_callback_info info);
napi_value GetGroupApplicationListAsApplicant(napi_env env, napi_callback_info info);
napi_value AcceptGroupApplication(napi_env env, napi_callback_info info);
napi_value RefuseGroupApplication(napi_env env, napi_callback_info info);
napi_value GetGroupApplicationUnhandledCount(napi_env env, napi_callback_info info);
napi_value SearchGroupMembers(napi_env env, napi_callback_info info);
napi_value IsJoinGroup(napi_env env, napi_callback_info info);
napi_value GetUsersInGroup(napi_env env, napi_callback_info info);

#endif //IMDEMO_GROUP_H
