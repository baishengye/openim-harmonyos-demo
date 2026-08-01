//
// Created on 2026/7/27.
//

#include "include/libopenimsdk.h"
#include "napi/native_api.h"
#include "hilog/log.h"
#include "utils.h"
#include "callback.h"
#include <string>
#include <chrono>

// ==================== Friend Functions ====================

napi_value NAPI_getSpecifyFriendsInfo(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userIDList = GetStringFromJS(env, args[2]);
    int filterBlack = GetIntFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getSpecifyFriendsInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetSpecifyFriendsInfo(int baseCallbackID, char* operationID, char* userIDList, int filterBlack)
    GetSpecifyFriendsInfo(cbId, (char*)operationID.c_str(), (char*)userIDList.c_str(), filterBlack);
    return CreateJSUndefined(env);
}

napi_value NAPI_getFriendList(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    int filterBlack = GetIntFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getFriendList_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetFriendList(int baseCallbackID, char* operationID, int filterBlack)
    GetFriendList(cbId, (char*)operationID.c_str(), filterBlack);
    return CreateJSUndefined(env);
}

napi_value NAPI_getFriendListPage(napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value args[5];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    int offset = GetIntFromJS(env, args[2]);
    int count = GetIntFromJS(env, args[3]);
    int filterBlack = GetIntFromJS(env, args[4]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getFriendListPage_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetFriendListPage(int baseCallbackID, char* operationID, int offset, int count, int filterBlack)
    GetFriendListPage(cbId, (char*)operationID.c_str(), offset, count, filterBlack);
    return CreateJSUndefined(env);
}

napi_value NAPI_searchFriends(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string searchParam = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_searchFriends_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SearchFriends(int baseCallbackID, char* operationID, char* searchParam)
    SearchFriends(cbId, (char*)operationID.c_str(), (char*)searchParam.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_checkFriend(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userIDList = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_checkFriend_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: CheckFriend(int baseCallbackID, char* operationID, char* userIDList)
    CheckFriend(cbId, (char*)operationID.c_str(), (char*)userIDList.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_addFriend(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userIDReqMsg = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_addFriend_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: AddFriend(int baseCallbackID, char* operationID, char* userIDReqMsg)
    AddFriend(cbId, (char*)operationID.c_str(), (char*)userIDReqMsg.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_updateFriends(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string req = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_updateFriends_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: UpdateFriends(int baseCallbackID, char* operationID, char* req)
    UpdateFriends(cbId, (char*)operationID.c_str(), (char*)req.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_deleteFriend(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string friendUserID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_deleteFriend_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: DeleteFriend(int baseCallbackID, char* operationID, char* friendUserID)
    DeleteFriend(cbId, (char*)operationID.c_str(), (char*)friendUserID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getFriendApplicationListAsRecipient(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string req = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getFriendApplicationListAsRecipient_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetFriendApplicationListAsRecipient(int baseCallbackID, char* operationID, char* req)
    GetFriendApplicationListAsRecipient(cbId, (char*)operationID.c_str(), (char*)req.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getFriendApplicationListAsApplicant(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string req = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getFriendApplicationListAsApplicant_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetFriendApplicationListAsApplicant(int baseCallbackID, char* operationID, char* req)
    GetFriendApplicationListAsApplicant(cbId, (char*)operationID.c_str(), (char*)req.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_acceptFriendApplication(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userIDHandleMsg = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_acceptFriendApplication_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: AcceptFriendApplication(int baseCallbackID, char* operationID, char* userIDHandleMsg)
    AcceptFriendApplication(cbId, (char*)operationID.c_str(), (char*)userIDHandleMsg.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_refuseFriendApplication(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userIDHandleMsg = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_refuseFriendApplication_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: RefuseFriendApplication(int baseCallbackID, char* operationID, char* userIDHandleMsg)
    RefuseFriendApplication(cbId, (char*)operationID.c_str(), (char*)userIDHandleMsg.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_addBlack(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string blackUserID = GetStringFromJS(env, args[2]);
    std::string ex = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_addBlack_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: AddBlack(int baseCallbackID, char* operationID, char* blackUserID, char* ex)
    AddBlack(cbId, (char*)operationID.c_str(), (char*)blackUserID.c_str(), (char*)ex.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getBlackList(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getBlackList_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetBlackList(int baseCallbackID, char* operationID)
    GetBlackList(cbId, (char*)operationID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_removeBlack(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string removeUserID = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_removeBlack_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: RemoveBlack(int baseCallbackID, char* operationID, char* removeUserID)
    RemoveBlack(cbId, (char*)operationID.c_str(), (char*)removeUserID.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getFriendApplicationUnhandledCount(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string req = GetStringFromJS(env, args[2]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getFriendApplicationUnhandledCount_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetFriendApplicationUnhandledCount(int baseCallbackID, char* operationID, char* req)
    GetFriendApplicationUnhandledCount(cbId, (char*)operationID.c_str(), (char*)req.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_setFriendRemark(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string friendUserID = GetStringFromJS(env, args[2]);
    std::string remark = GetStringFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_setFriendRemark_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: SetFriendRemark(int baseCallbackID, char* operationID, char* friendUserID, char* remark)
    SetFriendRemark(cbId, (char*)operationID.c_str(), (char*)friendUserID.c_str(), (char*)remark.c_str());
    return CreateJSUndefined(env);
}

napi_value NAPI_getSpecifiedFriendsInfo(napi_env env, napi_callback_info info) {
    size_t argc = 4;
    napi_value args[4];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string userIDList = GetStringFromJS(env, args[2]);
    int filterBlack = GetIntFromJS(env, args[3]);
    std::string operationID = GetStringFromJS(env, args[1]);
    if (operationID.empty()) {
        operationID = "napi_getSpecifiedFriendsInfo_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    }
    int cbId = StoreBaseCallback(env, args[0]);
    // New signature: GetSpecifyFriendsInfo(int baseCallbackID, char* operationID, char* userIDList, int filterBlack)
    GetSpecifyFriendsInfo(cbId, (char*)operationID.c_str(), (char*)userIDList.c_str(), filterBlack);
    return CreateJSUndefined(env);
}
