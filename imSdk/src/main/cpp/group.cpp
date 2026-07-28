//
// Created on 2026/7/27.
//

#include "libs/include/libopenimsdk.h"
#include "napi/native_api.h"
#include "hilog/log.h"
#include "utils.h"
#include "callback.h"
#include <string>
#include <chrono>

// ==================== Group Functions ====================

napi_value NAPI_createGroup(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupInfo = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_createGroup_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: CreateGroup(int baseCallbackID, char* operationID, char* groupInfo)
    CreateGroup(cbId, (char*)operationID.c_str(), (char*)groupInfo.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getJoinedGroupList(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getJoinedGroupList_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetJoinedGroupList(int baseCallbackID, char* operationID)
    GetJoinedGroupList(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getGroupsInfo(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupIDList = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getGroupsInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetGroupsInfo(int baseCallbackID, char* operationID, char* groupIDList)
    GetGroupsInfo(cbId, (char*)operationID.c_str(), (char*)groupIDList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_setGroupInfo(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupInfo = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setGroupInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SetGroupInfo(int baseCallbackID, char* operationID, char* groupInfo)
    SetGroupInfo(cbId, (char*)operationID.c_str(), (char*)groupInfo.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getJoinedGroupListPage(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    int offset = GetIntFromJS(env, args[2]);
    int count = GetIntFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getJoinedGroupListPage_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetJoinedGroupListPage(int baseCallbackID, char* operationID, int offset, int count)
    GetJoinedGroupListPage(cbId, (char*)operationID.c_str(), offset, count);
    return CreateJSUndefined(env);
}

napi_value NAPI_changeGroupMute(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    int isMute = GetIntFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_changeGroupMute_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: ChangeGroupMute(int baseCallbackID, char* operationID, char* groupID, int isMute)
    ChangeGroupMute(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), isMute);
    return CreateJSUndefined(env);
}

napi_value NAPI_changeGroupMemberMute(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string userID = GetStringFromJS(env, args[3]);
    long long mutedSeconds = GetInt64FromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_changeGroupMemberMute_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: ChangeGroupMemberMute(int baseCallbackID, char* operationID, char* groupID, char* userID, long long mutedSeconds)
    ChangeGroupMemberMute(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), (char*)userID.c_str(), mutedSeconds);
    return CreateJSUndefined(env);
}

napi_value NAPI_getGroupMemberList(napi_env env, napi_callback_info info) {
    size_t argc = 6;
    napi_value args[6];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    int filter = GetIntFromJS(env, args[3]);
    int offset = GetIntFromJS(env, args[4]);
    int count = GetIntFromJS(env, args[5]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getGroupMemberList_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetGroupMemberList(int baseCallbackID, char* operationID, char* groupID, int filter, int offset, int count)
    GetGroupMemberList(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), filter, offset, count);
    return CreateJSUndefined(env);
}

napi_value NAPI_getGroupMemberOwnerAndAdmin(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getGroupMemberOwnerAndAdmin_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetGroupMemberOwnerAndAdmin(int baseCallbackID, char* operationID, char* groupID)
    GetGroupMemberOwnerAndAdmin(cbId, (char*)operationID.c_str(), (char*)groupID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getUsersInGroup(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string userIDList = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getUsersInGroup_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetUsersInGroup(int baseCallbackID, char* operationID, char* groupID, char* userIDList)
    GetUsersInGroup(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), (char*)userIDList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_searchGroupMembers(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string searchParam = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_searchGroupMembers_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SearchGroupMembers(int baseCallbackID, char* operationID, char* searchParam)
    SearchGroupMembers(cbId, (char*)operationID.c_str(), (char*)searchParam.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_setGroupMemberInfo(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupMemberInfo = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setGroupMemberInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SetGroupMemberInfo(int baseCallbackID, char* operationID, char* groupMemberInfo)
    SetGroupMemberInfo(cbId, (char*)operationID.c_str(), (char*)groupMemberInfo.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_inviteUserToGroup(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string userIDList = GetStringFromJS(env, args[3]);
    std::string reason = GetStringFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_inviteUserToGroup_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: InviteUserToGroup(int baseCallbackID, char* operationID, char* groupID, char* userIDList, char* reason)
    InviteUserToGroup(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), (char*)userIDList.c_str(), (char*)reason.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_kickGroupMember(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string userIDList = GetStringFromJS(env, args[3]);
    std::string reason = GetStringFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_kickGroupMember_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: KickGroupMember(int baseCallbackID, char* operationID, char* groupID, char* userIDList, char* reason)
    KickGroupMember(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), (char*)userIDList.c_str(), (char*)reason.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getGroupApplicationUnhandledCount(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string req = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getGroupApplicationUnhandledCount_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetGroupApplicationUnhandledCount(int baseCallbackID, char* operationID, char* req)
    GetGroupApplicationUnhandledCount(cbId, (char*)operationID.c_str(), (char*)req.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_acceptGroupApplication(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string userID = GetStringFromJS(env, args[3]);
    std::string handleMsg = GetStringFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_acceptGroupApplication_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: AcceptGroupApplication(int baseCallbackID, char* operationID, char* groupID, char* userID, char* handleMsg)
    AcceptGroupApplication(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), (char*)userID.c_str(), (char*)handleMsg.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_refuseGroupApplication(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string userID = GetStringFromJS(env, args[3]);
    std::string handleMsg = GetStringFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_refuseGroupApplication_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: RefuseGroupApplication(int baseCallbackID, char* operationID, char* groupID, char* userID, char* handleMsg)
    RefuseGroupApplication(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), (char*)userID.c_str(), (char*)handleMsg.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_transferGroupOwner(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string newOwnerUserID = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_transferGroupOwner_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: TransferGroupOwner(int baseCallbackID, char* operationID, char* groupID, char* newOwnerUserID)
    TransferGroupOwner(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), (char*)newOwnerUserID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_quitGroup(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_quitGroup_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: QuitGroup(int baseCallbackID, char* operationID, char* groupID)
    QuitGroup(cbId, (char*)operationID.c_str(), (char*)groupID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_dismissGroup(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_dismissGroup_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: DismissGroup(int baseCallbackID, char* operationID, char* groupID)
    DismissGroup(cbId, (char*)operationID.c_str(), (char*)groupID.c_str());
    return CreateJSUndefined(env);
}

/**
 * @deprecated 此 API 已在 SDK 中废弃
 */
napi_value NAPI_getSendMessageOpt(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getSendMessageOpt_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    // int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetSendMessageOpt(int baseCallbackID, char* operationID, char* groupID)
    GetSendMessageOpt((char*)operationID.c_str(), (char*)groupID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getGroupApplicationListAsRecipient(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string req = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getGroupApplicationListAsRecipient_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetGroupApplicationListAsRecipient(int baseCallbackID, char* operationID, char* req)
    GetGroupApplicationListAsRecipient(cbId, (char*)operationID.c_str(), (char*)req.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getGroupApplicationListAsApplicant(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string req = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getGroupApplicationListAsApplicant_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetGroupApplicationListAsApplicant(int baseCallbackID, char* operationID, char* req)
    GetGroupApplicationListAsApplicant(cbId, (char*)operationID.c_str(), (char*)req.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_joinGroup(napi_env env, napi_callback_info info) {
    size_t argc = 6;
    napi_value args[6];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string reqMsg = GetStringFromJS(env, args[3]);
    int joinSource = GetIntFromJS(env, args[4]);
    std::string ex = GetStringFromJS(env, args[5]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_joinGroup_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: JoinGroup(int baseCallbackID, char* operationID, char* groupID, char* reqMsg, int joinSource, char* ex)
    JoinGroup(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), (char*)reqMsg.c_str(), joinSource, (char*)ex.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_searchGroups(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string searchParam = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_searchGroups_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SearchGroups(int baseCallbackID, char* operationID, char* searchParam)
    SearchGroups(cbId, (char*)operationID.c_str(), (char*)searchParam.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_isJoinGroup(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_isJoinGroup_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: IsJoinGroup(int baseCallbackID, char* operationID, char* groupID)
    IsJoinGroup(cbId, (char*)operationID.c_str(), (char*)groupID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getSpecifyGroupMembersInfo(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string userIDList = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getSpecifyGroupMembersInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetSpecifiedGroupMembersInfo(int baseCallbackID, char* operationID, char* groupID, char* userIDList)
    GetSpecifiedGroupMembersInfo(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), (char*)userIDList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getGroupMemberListByJoinTimeFilter(napi_env env, napi_callback_info info) {
    size_t argc = 8;
    napi_value args[8];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    long long offset = GetInt64FromJS(env, args[3]);
    long long count = GetInt64FromJS(env, args[4]);
    long long joinTimeBegin = GetInt64FromJS(env, args[5]);
    long long joinTimeEnd = GetInt64FromJS(env, args[6]);
    std::string filterUserIDList = GetStringFromJS(env, args[7]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getGroupMemberListByJoinTimeFilter_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetGroupMemberListByJoinTimeFilter(int baseCallbackID, char* operationID, char* groupID, long long offset, long long count, long long joinTimeBegin, long long joinTimeEnd, char* filterUserIDList)
    GetGroupMemberListByJoinTimeFilter(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), offset, count, joinTimeBegin, joinTimeEnd, (char*)filterUserIDList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getSpecifiedGroupsInfo(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string params = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getSpecifiedGroupsInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetGroupsInfo(int baseCallbackID, char* operationID, char* groupIDList)
    GetGroupsInfo(cbId, (char*)operationID.c_str(), (char*)params.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getSpecifiedGroupMembersInfo(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string groupID = GetStringFromJS(env, args[2]);
    std::string userIDList = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getSpecifiedGroupMembersInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetSpecifiedGroupMembersInfo(int baseCallbackID, char* operationID, char* groupID, char* userIDList)
    GetSpecifiedGroupMembersInfo(cbId, (char*)operationID.c_str(), (char*)groupID.c_str(), (char*)userIDList.c_str());
    return CreateJSUndefined(env);
}
