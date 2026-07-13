//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "group.h"
#include "callback.h"

/*
@napi-ts
创建群.
@param operationID - 唯一操作标识
@param cGroupReqInfo - 群信息 
@returns Promise<string>
@signature export function createGroup(operationID: string, cGroupReqInfo: string): Promise<string>;
*/
napi_value CreateGroup(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupReqInfo = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        create_group(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cGroupReqInfo.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
加入群.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param cReqMsg - 加入请求
@param cJoinSource - 加入来源
@param ex - 其他信息
@returns Promise<string>
@signature export function joinGroup(operationID: string, cGroupID: string, cReqMsg: string, cJoinSource: number, ex: string): Promise<string>;
*/
napi_value JoinGroup(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 5;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cReqMsg = GetJSString(env, args[2]);
    auto cJoinSource = GetJSInt32(env, args[3]);
    auto ex = GetJSString(env, args[4]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        join_group(RegisterSISS, const_cast<char*>(operationID.c_str()), 
                   const_cast<char*>(cGroupID.c_str()),
                   const_cast<char*>(cReqMsg.c_str()),
                   cJoinSource, 
                   const_cast<char*>(ex.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
退出群.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@returns Promise<string>
@signature export function quitGroup(operationID: string, cGroupID: string): Promise<string>;
*/
napi_value QuitGroup(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        quit_group(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cGroupID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
解散群.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@returns Promise<string>
@signature export function dismissGroup(operationID: string, cGroupID: string): Promise<string>;
*/
napi_value DismissGroup(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        dismiss_group(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cGroupID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
群禁言设置.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param cIsMute - 禁言标识
@returns Promise<string>
@signature export function changeGroupMute(operationID: string, cGroupID: string, cIsMute: boolean): Promise<string>;
*/
napi_value ChangeGroupMute(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cIsMute = GetJSBoolean(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        change_group_mute(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cGroupID.c_str()), cIsMute);
    }
    return result.promise;
}

/*
@napi-ts
群成员禁言设置.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param cUserID - 成员用户ID
@param cMutedSeconds - 禁言时长
@returns Promise<string>
@signature export function changeGroupMemberMute(operationID: string, cGroupID: string, cUserID: string, cMutedSeconds: number): Promise<string>;
*/
napi_value ChangeGroupMemberMute(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cUserID = GetJSString(env, args[2]);
    auto cMutedSeconds = GetJSInt32(env, args[3]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        change_group_member_mute(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cGroupID.c_str()), const_cast<char*>(cUserID.c_str()), cMutedSeconds);
    }
    return result.promise;
}

/*
@napi-ts
设置群成员信息.
@param operationID - 唯一操作标识
@param cGroupMemberInfo - 群成员信息
@returns Promise<string>
@signature export function setGroupMemberInfo(operationID: string, cGroupMemberInfo: string): Promise<string>;
*/
napi_value SetGroupMemberInfo(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupMemberInfo = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        set_group_member_info(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cGroupMemberInfo.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取已加入群列表.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function getJoinedGroupList(operationID: string): Promise<string>;
*/
napi_value GetJoinedGroupList(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 1;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_joined_group_list(RegisterSISS, const_cast<char*>(operationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取已加入群列表.
@param operationID - 唯一操作标识
@param offset - 页码
@param count - 每页大小
@returns Promise<string>
@signature export function getJoinedGroupListPage(operationID: string, offset: number, count: number): Promise<string>;
*/
napi_value GetJoinedGroupListPage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto offset = GetJSInt32(env, args[1]);
    auto count = GetJSInt32(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_joined_group_list_page(RegisterSISS, const_cast<char*>(operationID.c_str()), offset, count);
    }
    return result.promise;
}

/*
@napi-ts
获取指定群信息.
@param operationID - 唯一操作标识
@param cGroupIDList - 群ID列表
@returns Promise<string>
@signature export function getSpecifiedGroupsInfo(operationID: string, cGroupIDList: string): Promise<string>;
*/
napi_value GetSpecifiedGroupsInfo(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupIDList = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_specified_groups_info(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cGroupIDList.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取指定群信息.
@param operationID - 唯一操作标识
@param cSearchParam - 群ID列表
@returns Promise<string>
@signature export function searchGroups(operationID: string, cSearchParam: string): Promise<string>;
*/
napi_value SearchGroups(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cSearchParam = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        search_groups(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cSearchParam.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
设置群信息.
@param operationID - 唯一操作标识
@param cGroupInfo - 群信息
@returns Promise<string>
@signature export function setGroupInfo(operationID: string, cGroupInfo: string): Promise<string>;
*/
napi_value SetGroupInfo(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupInfo = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        set_group_info(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cGroupInfo.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取群成员列表.
@param operationID - 唯一操作标识
@param cGroupInfo - 群信息
@param cFilter - 过滤条件
@param cOffset - 页码
@param cCount - 每页大小
@returns Promise<string>
@signature export function getGroupMemberList(operationID: string, cGroupInfo: string, cFilter: number, cOffset: number, cCount: number): Promise<string>;
*/
napi_value GetGroupMemberList(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 5;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cFilter = GetJSInt32(env, args[2]);
    auto cOffset = GetJSInt32(env, args[3]);
    auto cCount = GetJSInt32(env, args[4]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_group_member_list(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cGroupID.c_str()), cFilter, cOffset, cCount);
    }
    return result.promise;
}

/*
@napi-ts
获取群主和群管理员.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@returns Promise<string>
@signature export function getGroupMemberOwnerAndAdmin(operationID: string, cGroupID: string): Promise<string>;
*/
napi_value GetGroupMemberOwnerAndAdmin(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_group_member_owner_and_admin(RegisterSISS, const_cast<char*>(operationID.c_str()), const_cast<char*>(cGroupID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取群主和群管理员.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param cOffset - 页码
@param cCount - 每页大小
@param cJoinTimeBegin - 加入起始时间
@param cJoinTimeEnd - 加入结束时间
@param cFilterUserIDList - 过滤用户列表
@returns Promise<string>
@signature export function getGroupMemberListByJoinTimeFilter(operationID: string, cGroupID: string, cOffset: number, cCount: number, cJoinTimeBegin: number,  cJoinTimeEnd: number,  cFilterUserIDList: string): Promise<string>;
*/
napi_value GetGroupMemberListByJoinTimeFilter(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 7;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cOffset = GetJSInt32(env, args[2]);
    auto cCount = GetJSInt32(env, args[3]);
    auto cJoinTimeBegin = GetJSInt64(env, args[4]);
    auto cJoinTimeEnd = GetJSInt64(env, args[5]);
    auto cFilterUserIDList = GetJSString(env, args[6]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_group_member_list_by_join_time_filter(RegisterSISS, 
                                                  const_cast<char*>(operationID.c_str()), 
                                                  const_cast<char*>(cGroupID.c_str()),
                                                  cOffset,cCount,
                                                  cJoinTimeBegin,cJoinTimeEnd,
                                                  const_cast<char*>(cFilterUserIDList.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取指定群成员信息.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param cUserIDList - 成员ID列表
@returns Promise<string>
@signature export function getSpecifiedGroupMembersInfo(operationID: string, cGroupID: string, cUserIDList: string): Promise<string>;
*/
napi_value GetSpecifiedGroupMembersInfo(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cUserIDList = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_specified_group_members_info(RegisterSISS, 
                                                  const_cast<char*>(operationID.c_str()), 
                                                  const_cast<char*>(cGroupID.c_str()),
                                                  const_cast<char*>(cUserIDList.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
移除群成员.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param cReason - 原因
@param cUserIDList - 成员ID列表
@returns Promise<string>
@signature export function kickGroupMember(operationID: string, cGroupID: string, cReason: string, cUserIDList: string): Promise<string>;
*/
napi_value KickGroupMember(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cReason = GetJSString(env, args[2]);
    auto cUserIDList = GetJSString(env, args[3]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        kick_group_member(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(cGroupID.c_str()),
                          const_cast<char*>(cReason.c_str()),
                          const_cast<char*>(cUserIDList.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
转让群主.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param cNewOwnerUserID - 新群主ID
@returns Promise<string>
@signature export function transferGroupOwner(operationID: string, cGroupID: string, cNewOwnerUserID: string): Promise<string>;
*/
napi_value TransferGroupOwner(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cNewOwnerUserID = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        transfer_group_owner(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(cGroupID.c_str()),
                          const_cast<char*>(cNewOwnerUserID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
转让群主.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param cReason - 原因
@param cUserIDList - 用户ID列表
@returns Promise<string>
@signature export function inviteUserToGroup(operationID: string, cGroupID: string, cReason: string, cUserIDList: string): Promise<string>;
*/
napi_value InviteUserToGroup(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cReason = GetJSString(env, args[2]);
    auto cUserIDList = GetJSString(env, args[3]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        invite_user_to_group(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(cGroupID.c_str()),
                          const_cast<char*>(cReason.c_str()),
                          const_cast<char*>(cUserIDList.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取加入群申请，（接收者）.
@param operationID - 唯一操作标识
@param req - 请求参数
@returns Promise<string>
@signature export function getGroupApplicationListAsRecipient(operationID: string, req: string): Promise<string>;
*/
napi_value GetGroupApplicationListAsRecipient(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto req = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_group_application_list_as_recipient(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(req.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取加入群申请，（申请者）.
@param operationID - 唯一操作标识
@param req - 请求参数
@returns Promise<string>
@signature export function getGroupApplicationListAsApplicant(operationID: string, req: string): Promise<string>;
*/
napi_value GetGroupApplicationListAsApplicant(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto req = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_group_application_list_as_applicant(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(req.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
接收加入群申请.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param cFromUserID - 申请者ID
@param cHandleMsg - 处理信息
@returns Promise<string>
@signature export function acceptGroupApplication(operationID: string, cGroupID: string, cFromUserID: string, cHandleMsg: string): Promise<string>;
*/
napi_value AcceptGroupApplication(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cFromUserID = GetJSString(env, args[2]);
    auto cHandleMsg = GetJSString(env, args[3]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        accept_group_application(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(cGroupID.c_str()),
                          const_cast<char*>(cFromUserID.c_str()),
                          const_cast<char*>(cHandleMsg.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
拒绝加入群申请.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param cFromUserID - 申请者ID
@param cHandleMsg - 处理信息
@returns Promise<string>
@signature export function refuseGroupApplication(operationID: string, cGroupID: string, cFromUserID: string, cHandleMsg: string): Promise<string>;
*/
napi_value RefuseGroupApplication(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto cFromUserID = GetJSString(env, args[2]);
    auto cHandleMsg = GetJSString(env, args[3]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        refuse_group_application(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(cGroupID.c_str()),
                          const_cast<char*>(cFromUserID.c_str()),
                          const_cast<char*>(cHandleMsg.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取群加入申请数量.
@param operationID - 唯一操作标识
@param req - 请求参数
@returns Promise<string>
@signature export function getGroupApplicationUnhandledCount(operationID: string, req: string): Promise<string>;
*/
napi_value GetGroupApplicationUnhandledCount(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto req = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_group_application_unhandled_count(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(req.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
搜索群成员.
@param operationID - 唯一操作标识
@param cSearchParam - 搜索参数
@returns Promise<string>
@signature export function searchGroupMembers(operationID: string, cSearchParam: string): Promise<string>;
*/
napi_value SearchGroupMembers(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cSearchParam = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        search_group_members(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(cSearchParam.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
是否已加入群.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@returns Promise<string>
@signature export function isJoinGroup(operationID: string, cGroupID: string): Promise<string>;
*/
napi_value IsJoinGroup(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        is_join_group(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(cGroupID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
获取群指定成员.
@param operationID - 唯一操作标识
@param cGroupID - 群ID
@param userIDList - 成员ID列表 
@returns Promise<string>
@signature export function getUsersInGroup(operationID: string, cGroupID: string, userIDList: string): Promise<string>;
*/
napi_value GetUsersInGroup(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cGroupID = GetJSString(env, args[1]);
    auto userIDList = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_users_in_group(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(cGroupID.c_str()), const_cast<char*>(userIDList.c_str()));
    }
    return result.promise;
}