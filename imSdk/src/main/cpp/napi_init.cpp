#include "libs/include/libopenimsdk.h"
#include "napi/native_api.h"
#include "hilog/log.h"
#include <string>
#include <thread>
#include <chrono>
#include "callback.h"
#include "utils.h"

// External callback invocation from callback.cpp
extern void InvokeSuccessCallback(napi_env env, napi_ref callbackRef, const char* data);
extern void InvokeErrorCallback(napi_env env, napi_ref callbackRef, int errCode, const char* errMsg);

// External functions from listener.cpp (for listener registration)
extern "C" void RegisterConnListener(int onConnecting, int onConnectSuccess, int onConnectFailed, int onKickedOffline, int onUserTokenExpired, int onUserTokenInvalid);
extern "C" void RegisterMsgListener(int onRecvNewMsg, int onRecvReceipt, int onMsgRevoked, int onRecvOffline, int onMsgDeleted, int onRecvOnline);
extern "C" void RegisterConvListener(int onSyncStart, int onSyncFinish, int onSyncProgress, int onSyncFailed, int onConvChanged, int onNewConv, int onUnreadChanged, int onInputStatus);
extern "C" void RegisterGroupListener(int onJoinedGroupAdded, int onJoinedGroupDeleted, int onGroupMemberAdded, int onGroupMemberDeleted, int onGroupApplicationAdded, int onGroupApplicationDeleted, int onGroupInfoChanged, int onGroupDismissed, int onGroupMemberInfoChanged, int onGroupApplicationAccepted, int onGroupApplicationRejected);
extern "C" void RegisterFriendListener(int onFriendApplicationAdded, int onFriendApplicationDeleted, int onFriendApplicationAccepted, int onFriendApplicationRejected, int onFriendAdded, int onFriendDeleted, int onFriendInfoChanged, int onBlackAdded, int onBlackDeleted);
extern "C" void RegisterUserListener(int onSelfInfoUpdated, int onUserStatusChanged);
extern "C" void RegisterSignalingListener(int onReceiveNewInvitation, int onInviteeAccepted, int onInviteeAcceptedByOtherDevice, int onInviteeRejected, int onInviteeRejectedByOtherDevice, int onInvitationCancelled, int onInvitationTimeout, int onHangUp, int onRoomParticipantConnected, int onRoomParticipantDisconnected);
extern "C" void RegisterCustomBusinessListener(int onRecvCustomBusinessMessage);
extern "C" void RegisterMsgKvInfoListener(int onMessageKvInfoChanged);

// Connection listener callbacks
extern "C" void OnConnConnecting(int v);
extern "C" void OnConnSuccess(int v);
extern "C" void OnConnFailed(int errCode, char* errMsg);
extern "C" void OnConnKicked(int v);
extern "C" void OnConnTokenExpired(int v);
extern "C" void OnConnTokenInvalid(int v, char* errMsg);

// Message listener callbacks
extern "C" void OnRecvNewMsg(char* msg);
extern "C" void OnRecvReceipt(char* msg);
extern "C" void OnMsgRevoked(char* msg);
extern "C" void OnRecvOffline(char* msg);
extern "C" void OnMsgDeleted(char* msg);
extern "C" void OnRecvOnline(char* msg);

// Conversation listener callbacks
extern "C" void OnSyncStart(int reinstalled);
extern "C" void OnSyncFinish(int reinstalled);
extern "C" void OnSyncProgress(int progress);
extern "C" void OnSyncFailed(int reinstalled);
extern "C" void OnConvChanged(char* convList);
extern "C" void OnNewConv(char* convList);
extern "C" void OnUnreadChanged(int count);
extern "C" void OnInputStatus(char* change);

// Group listener callbacks
extern "C" void OnGroupJoinedAdd(char* groupInfo);
extern "C" void OnGroupJoinedDel(char* groupInfo);
extern "C" void OnGroupMemberAdd(char* memberInfo);
extern "C" void OnGroupMemberDel(char* memberInfo);
extern "C" void OnGroupAppAdd(char* application);
extern "C" void OnGroupAppDel(char* application);
extern "C" void OnGroupInfoChanged(char* groupInfo);
extern "C" void OnGroupDismissed(char* groupInfo);
extern "C" void OnGroupMemberInfo(char* memberInfo);
extern "C" void OnGroupAppAccept(char* application);
extern "C" void OnGroupAppReject(char* application);

// Friend listener callbacks
extern "C" void OnFriendAppAdd(char* application);
extern "C" void OnFriendAppDel(char* application);
extern "C" void OnFriendAppAccept(char* application);
extern "C" void OnFriendAppReject(char* application);
extern "C" void OnFriendAdd(char* friendInfo);
extern "C" void OnFriendDel(char* friendInfo);
extern "C" void OnFriendInfo(char* friendInfo);
extern "C" void OnBlackAdd(char* blackInfo);
extern "C" void OnBlackDel(char* blackInfo);

// User listener callbacks
extern "C" void OnSelfInfo(char* userInfo);
extern "C" void OnUserStatus(char* status);

// Signaling listener callbacks
extern "C" void OnSignalingReceiveNewInvitation(char* data);
extern "C" void OnSignalingInviteeAccepted(char* data);
extern "C" void OnSignalingInviteeAcceptedByOtherDevice(char* data);
extern "C" void OnSignalingInviteeRejected(char* data);
extern "C" void OnSignalingInviteeRejectedByOtherDevice(char* data);
extern "C" void OnSignalingInvitationCancelled(char* data);
extern "C" void OnSignalingInvitationTimeout(char* data);
extern "C" void OnSignalingHangUp(char* data);
extern "C" void OnSignalingRoomParticipantConnected(char* data);
extern "C" void OnSignalingRoomParticipantDisconnected(char* data);

// Custom business and message KV listener callbacks
extern "C" void OnCustomBusiness(char* msg);
extern "C" void OnMsgKvInfoChanged(char* msg);


static napi_value Add(napi_env env, napi_callback_info info)
{
    LogError("OpenIM", "Add");
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);

    LogError("OpenIM", "sum:%s",sum);
    return sum;

}

// External NAPI listener functions from listener.cpp
extern napi_value NAPI_setConnListener(napi_env env, napi_callback_info info);
extern napi_value NAPI_setAdvancedMsgListener(napi_env env, napi_callback_info info);
extern napi_value NAPI_setBatchMsgListener(napi_env env, napi_callback_info info);
extern napi_value NAPI_setConversationListener(napi_env env, napi_callback_info info);
extern napi_value NAPI_setGroupListener(napi_env env, napi_callback_info info);
extern napi_value NAPI_setFriendListener(napi_env env, napi_callback_info info);
extern napi_value NAPI_setUserListener(napi_env env, napi_callback_info info);
extern napi_value NAPI_setSignalingListener(napi_env env, napi_callback_info info);
extern napi_value NAPI_setCustomBusinessListener(napi_env env, napi_callback_info info);
extern napi_value NAPI_setMsgKvInfoListener(napi_env env, napi_callback_info info);


// Conversation NAPI functions
extern napi_value NAPI_getAllConversationList(napi_env env, napi_callback_info info);
extern napi_value NAPI_getConversationListSplit(napi_env env, napi_callback_info info);
extern napi_value NAPI_getOneConversation(napi_env env, napi_callback_info info);
extern napi_value NAPI_getMultipleConversation(napi_env env, napi_callback_info info);
extern napi_value NAPI_getConversationIDBySessionType(napi_env env, napi_callback_info info);
extern napi_value NAPI_getTotalUnreadMsgCount(napi_env env, napi_callback_info info);
extern napi_value NAPI_markConversationMessageAsRead(napi_env env, napi_callback_info info);
extern napi_value NAPI_setConversation(napi_env env, napi_callback_info info);
extern napi_value NAPI_setConversationDraft(napi_env env, napi_callback_info info);
extern napi_value NAPI_pinConversation(napi_env env, napi_callback_info info);
extern napi_value NAPI_setConversationRecvMessageOpt(napi_env env, napi_callback_info info);
extern napi_value NAPI_setConversationPrivateChat(napi_env env, napi_callback_info info);
extern napi_value NAPI_setConversationBurnDuration(napi_env env, napi_callback_info info);
extern napi_value NAPI_resetConversationGroupAtType(napi_env env, napi_callback_info info);
extern napi_value NAPI_hideConversation(napi_env env, napi_callback_info info);
extern napi_value NAPI_hideAllConversations(napi_env env, napi_callback_info info);
extern napi_value NAPI_clearConversationAndDeleteAllMsg(napi_env env, napi_callback_info info);
extern napi_value NAPI_deleteConversationAndDeleteAllMsg(napi_env env, napi_callback_info info);


// Friend NAPI functions
extern napi_value NAPI_getSpecifyFriendsInfo(napi_env env, napi_callback_info info);
extern napi_value NAPI_getFriendList(napi_env env, napi_callback_info info);
extern napi_value NAPI_getFriendListPage(napi_env env, napi_callback_info info);
extern napi_value NAPI_searchFriends(napi_env env, napi_callback_info info);
extern napi_value NAPI_checkFriend(napi_env env, napi_callback_info info);
extern napi_value NAPI_addFriend(napi_env env, napi_callback_info info);
extern napi_value NAPI_updateFriends(napi_env env, napi_callback_info info);
extern napi_value NAPI_deleteFriend(napi_env env, napi_callback_info info);
extern napi_value NAPI_getFriendApplicationListAsRecipient(napi_env env, napi_callback_info info);
extern napi_value NAPI_getFriendApplicationListAsApplicant(napi_env env, napi_callback_info info);
extern napi_value NAPI_acceptFriendApplication(napi_env env, napi_callback_info info);
extern napi_value NAPI_refuseFriendApplication(napi_env env, napi_callback_info info);
extern napi_value NAPI_addBlack(napi_env env, napi_callback_info info);
extern napi_value NAPI_getBlackList(napi_env env, napi_callback_info info);
extern napi_value NAPI_removeBlack(napi_env env, napi_callback_info info);
extern napi_value NAPI_getFriendApplicationUnhandledCount(napi_env env, napi_callback_info info);
extern napi_value NAPI_setFriendRemark(napi_env env, napi_callback_info info);
extern napi_value NAPI_getSpecifiedFriendsInfo(napi_env env, napi_callback_info info);


// Group NAPI functions
extern napi_value NAPI_createGroup(napi_env env, napi_callback_info info);
extern napi_value NAPI_getJoinedGroupList(napi_env env, napi_callback_info info);
extern napi_value NAPI_getGroupsInfo(napi_env env, napi_callback_info info);
extern napi_value NAPI_setGroupInfo(napi_env env, napi_callback_info info);
extern napi_value NAPI_getJoinedGroupListPage(napi_env env, napi_callback_info info);
extern napi_value NAPI_changeGroupMute(napi_env env, napi_callback_info info);
extern napi_value NAPI_changeGroupMemberMute(napi_env env, napi_callback_info info);
extern napi_value NAPI_getGroupMemberList(napi_env env, napi_callback_info info);
extern napi_value NAPI_getGroupMemberOwnerAndAdmin(napi_env env, napi_callback_info info);
extern napi_value NAPI_getUsersInGroup(napi_env env, napi_callback_info info);
extern napi_value NAPI_searchGroupMembers(napi_env env, napi_callback_info info);
extern napi_value NAPI_setGroupMemberInfo(napi_env env, napi_callback_info info);
extern napi_value NAPI_inviteUserToGroup(napi_env env, napi_callback_info info);
extern napi_value NAPI_kickGroupMember(napi_env env, napi_callback_info info);
extern napi_value NAPI_getGroupApplicationUnhandledCount(napi_env env, napi_callback_info info);
extern napi_value NAPI_acceptGroupApplication(napi_env env, napi_callback_info info);
extern napi_value NAPI_refuseGroupApplication(napi_env env, napi_callback_info info);
extern napi_value NAPI_transferGroupOwner(napi_env env, napi_callback_info info);
extern napi_value NAPI_quitGroup(napi_env env, napi_callback_info info);
extern napi_value NAPI_dismissGroup(napi_env env, napi_callback_info info);
extern napi_value NAPI_getSendMessageOpt(napi_env env, napi_callback_info info);
extern napi_value NAPI_getGroupApplicationListAsRecipient(napi_env env, napi_callback_info info);
extern napi_value NAPI_getGroupApplicationListAsApplicant(napi_env env, napi_callback_info info);
extern napi_value NAPI_joinGroup(napi_env env, napi_callback_info info);
extern napi_value NAPI_searchGroups(napi_env env, napi_callback_info info);
extern napi_value NAPI_isJoinGroup(napi_env env, napi_callback_info info);
extern napi_value NAPI_getSpecifyGroupMembersInfo(napi_env env, napi_callback_info info);
extern napi_value NAPI_getGroupMemberListByJoinTimeFilter(napi_env env, napi_callback_info info);
extern napi_value NAPI_getSpecifiedGroupsInfo(napi_env env, napi_callback_info info);


// init
extern napi_value NAPI_initSdk(napi_env env, napi_callback_info info);
extern napi_value NAPI_login(napi_env env, napi_callback_info info);
extern napi_value NAPI_logout(napi_env env, napi_callback_info info);
extern napi_value NAPI_getLoginStatus(napi_env env, napi_callback_info info);
extern napi_value NAPI_getLoginUserID(napi_env env, napi_callback_info info);


// Message NAPI functions
extern napi_value NAPI_createTextMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createImageMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createImageMessageFromFullPath(napi_env env, napi_callback_info info);
extern napi_value NAPI_createImageMessageByURL(napi_env env, napi_callback_info info);
extern napi_value NAPI_createSoundMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createSoundMessageFromFullPath(napi_env env, napi_callback_info info);
extern napi_value NAPI_createSoundMessageByURL(napi_env env, napi_callback_info info) ;
extern napi_value NAPI_createFileMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createFileMessageByURL(napi_env env, napi_callback_info info);
extern napi_value NAPI_createFileMessageFromFullPath(napi_env env, napi_callback_info info);
extern napi_value NAPI_createVideoMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createVideoMessageByURL(napi_env env, napi_callback_info info);
extern napi_value NAPI_createVideoMessageFromFullPath(napi_env env, napi_callback_info info);
extern napi_value NAPI_createLocationMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createCustomMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createQuoteMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createFaceMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createMergerMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createForwardMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createCardMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createTextAtMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createAdvancedQuoteMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_createAdvancedTextMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_sendMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_sendMessageNotOss(napi_env env, napi_callback_info info);
extern napi_value NAPI_typingStatusUpdate(napi_env env, napi_callback_info info);
extern napi_value NAPI_markMessageAsRead(napi_env env, napi_callback_info info);
extern napi_value NAPI_markAllMessageAsRead(napi_env env, napi_callback_info info);
extern napi_value NAPI_revokeMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_deleteMessageFromLocal(napi_env env, napi_callback_info info);
extern napi_value NAPI_deleteMessage(napi_env env, napi_callback_info info);
extern napi_value NAPI_deleteAllMessageFromLocal(napi_env env, napi_callback_info info);
extern napi_value NAPI_deleteAllMsgFromLocalAndSvr(napi_env env, napi_callback_info info);
extern napi_value NAPI_insertSingleMessageToLocal(napi_env env, napi_callback_info info);
extern napi_value NAPI_findMessageList(napi_env env, napi_callback_info info);
extern napi_value NAPI_getHistoryMessageList(napi_env env, napi_callback_info info);
extern napi_value NAPI_getAdvancedHistoryMessageList(napi_env env, napi_callback_info info);
extern napi_value NAPI_getAdvancedHistoryMessageListReverse(napi_env env, napi_callback_info info);
extern napi_value NAPI_searchLocalMessages(napi_env env, napi_callback_info info);
extern napi_value NAPI_searchConversation(napi_env env, napi_callback_info info);
extern napi_value NAPI_setMessageLocalEx(napi_env env, napi_callback_info info);
extern napi_value NAPI_deleteMessageFromLocalStorage(napi_env env, napi_callback_info info);
extern napi_value NAPI_deleteAllMsgFromLocal(napi_env env, napi_callback_info info);
extern napi_value NAPI_insertSingleMessageToLocalStorage(napi_env env, napi_callback_info info);
extern napi_value NAPI_insertGroupMessageToLocalStorage(napi_env env, napi_callback_info info);
extern napi_value NAPI_getSpecifiedGroupMembersInfo(napi_env env, napi_callback_info info);
extern napi_value NAPI_markMessagesAsReadByMsgID(napi_env env, napi_callback_info info);


// Misc NAPI functions
extern napi_value NAPI_uploadFile(napi_env env, napi_callback_info info);
extern napi_value NAPI_updateFcmToken(napi_env env, napi_callback_info info);
extern napi_value NAPI_setAppBadge(napi_env env, napi_callback_info info);
extern napi_value NAPI_uploadLogs(napi_env env, napi_callback_info info);
extern napi_value NAPI_logs(napi_env env, napi_callback_info info);
extern napi_value NAPI_getSdkVersion(napi_env env, napi_callback_info info);
extern napi_value NAPI_unInitSDK(napi_env env, napi_callback_info info);
extern napi_value NAPI_getAtAllTag(napi_env env, napi_callback_info info);
extern napi_value NAPI_changeInputStates(napi_env env, napi_callback_info info);
extern napi_value NAPI_getInputStates(napi_env env, napi_callback_info info);


// User NAPI functions
extern napi_value NAPI_getUsersInfo(napi_env env, napi_callback_info info);
extern napi_value NAPI_getSelfUserInfo(napi_env env, napi_callback_info info);
extern napi_value NAPI_setSelfInfo(napi_env env, napi_callback_info info);
extern napi_value NAPI_getUserStatus(napi_env env, napi_callback_info info);
extern napi_value NAPI_subscribeUsersStatus(napi_env env, napi_callback_info info);
extern napi_value NAPI_unsubscribeUsersStatus(napi_env env, napi_callback_info info);
extern napi_value NAPI_getSubscribeUsersStatus(napi_env env, napi_callback_info info);
extern napi_value NAPI_setAppBackgroundStatus(napi_env env, napi_callback_info info);
extern napi_value NAPI_networkStatusChanged(napi_env env, napi_callback_info info);

// ==================== Module Init ====================

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
         { "add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr },
        // Login
        {"initSdk", nullptr, NAPI_initSdk, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"login", nullptr, NAPI_login, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"logout", nullptr, NAPI_logout, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getLoginStatus", nullptr, NAPI_getLoginStatus, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getLoginUserID", nullptr, NAPI_getLoginUserID, nullptr, nullptr, nullptr, napi_default, nullptr},
        // User
        {"getUsersInfo", nullptr, NAPI_getUsersInfo, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getSelfUserInfo", nullptr, NAPI_getSelfUserInfo, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setSelfInfo", nullptr, NAPI_setSelfInfo, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getUserStatus", nullptr, NAPI_getUserStatus, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"subscribeUsersStatus", nullptr, NAPI_subscribeUsersStatus, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"unsubscribeUsersStatus", nullptr, NAPI_unsubscribeUsersStatus, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"getSubscribeUsersStatus", nullptr, NAPI_getSubscribeUsersStatus, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"setAppBackgroundStatus", nullptr, NAPI_setAppBackgroundStatus, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"networkStatusChanged", nullptr, NAPI_networkStatusChanged, nullptr, nullptr, nullptr, napi_default, nullptr},
        // Conversation
        {"getAllConversationList", nullptr, NAPI_getAllConversationList, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"getConversationListSplit", nullptr, NAPI_getConversationListSplit, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"getOneConversation", nullptr, NAPI_getOneConversation, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getMultipleConversation", nullptr, NAPI_getMultipleConversation, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"getConversationIDBySessionType", nullptr, NAPI_getConversationIDBySessionType, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"getTotalUnreadMsgCount", nullptr, NAPI_getTotalUnreadMsgCount, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"markConversationMessageAsRead", nullptr, NAPI_markConversationMessageAsRead, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"setConversation", nullptr, NAPI_setConversation, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setConversationDraft", nullptr, NAPI_setConversationDraft, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"pinConversation", nullptr, NAPI_pinConversation, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setConversationRecvMessageOpt", nullptr, NAPI_setConversationRecvMessageOpt, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"setConversationPrivateChat", nullptr, NAPI_setConversationPrivateChat, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"setConversationBurnDuration", nullptr, NAPI_setConversationBurnDuration, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"resetConversationGroupAtType", nullptr, NAPI_resetConversationGroupAtType, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"hideConversation", nullptr, NAPI_hideConversation, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"hideAllConversations", nullptr, NAPI_hideAllConversations, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"clearConversationAndDeleteAllMsg", nullptr, NAPI_clearConversationAndDeleteAllMsg, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"deleteConversationAndDeleteAllMsg", nullptr, NAPI_deleteConversationAndDeleteAllMsg, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        // Message
        {"createTextMessage", nullptr, NAPI_createTextMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createImageMessage", nullptr, NAPI_createImageMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createImageMessageFromFullPath", nullptr, NAPI_createImageMessageFromFullPath, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"createSoundMessage", nullptr, NAPI_createSoundMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createSoundMessageFromFullPath", nullptr, NAPI_createSoundMessageFromFullPath, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"createFileMessageByURL", nullptr, NAPI_createFileMessageByURL, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"createFileMessage", nullptr, NAPI_createFileMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createFileMessageFromFullPath", nullptr, NAPI_createFileMessageFromFullPath, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"createVideoMessage", nullptr, NAPI_createVideoMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createVideoMessageFromFullPath", nullptr, NAPI_createVideoMessageFromFullPath, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"createImageMessageByURL", nullptr, NAPI_createImageMessageByURL, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"createLocationMessage", nullptr, NAPI_createLocationMessage, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"createCustomMessage", nullptr, NAPI_createCustomMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createQuoteMessage", nullptr, NAPI_createQuoteMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createFaceMessage", nullptr, NAPI_createFaceMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createMergerMessage", nullptr, NAPI_createMergerMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createForwardMessage", nullptr, NAPI_createForwardMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createCardMessage", nullptr, NAPI_createCardMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createTextAtMessage", nullptr, NAPI_createTextAtMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createAdvancedQuoteMessage", nullptr, NAPI_createAdvancedQuoteMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createAdvancedTextMessage", nullptr, NAPI_createAdvancedTextMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createSoundMessageByURL", nullptr, NAPI_createSoundMessageByURL, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"createVideoMessageByURL", nullptr, NAPI_createVideoMessageByURL, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"sendMessage", nullptr, NAPI_sendMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"sendMessageNotOss", nullptr, NAPI_sendMessageNotOss, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"typingStatusUpdate", nullptr, NAPI_typingStatusUpdate, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"markMessageAsRead", nullptr, NAPI_markMessageAsRead, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"markAllMessageAsRead", nullptr, NAPI_markAllMessageAsRead, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"revokeMessage", nullptr, NAPI_revokeMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"deleteMessageFromLocal", nullptr, NAPI_deleteMessageFromLocal, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"deleteMessage", nullptr, NAPI_deleteMessage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"deleteAllMessageFromLocal", nullptr, NAPI_deleteAllMessageFromLocal, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"deleteAllMsgFromLocalAndSvr", nullptr, NAPI_deleteAllMsgFromLocalAndSvr, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"insertSingleMessageToLocal", nullptr, NAPI_insertSingleMessageToLocal, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"findMessageList", nullptr, NAPI_findMessageList, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getHistoryMessageList", nullptr, NAPI_getHistoryMessageList, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"getAdvancedHistoryMessageList", nullptr, NAPI_getAdvancedHistoryMessageList, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"getAdvancedHistoryMessageListReverse", nullptr, NAPI_getAdvancedHistoryMessageListReverse, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"searchLocalMessages", nullptr, NAPI_searchLocalMessages, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"searchConversation", nullptr, NAPI_searchConversation, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setMessageLocalEx", nullptr, NAPI_setMessageLocalEx, nullptr, nullptr, nullptr, napi_default, nullptr},
         {"deleteMessageFromLocalStorage", nullptr, NAPI_deleteMessageFromLocalStorage, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"deleteAllMsgFromLocal", nullptr, NAPI_deleteAllMsgFromLocal, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"insertSingleMessageToLocalStorage", nullptr, NAPI_insertSingleMessageToLocalStorage, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"insertGroupMessageToLocalStorage", nullptr, NAPI_insertGroupMessageToLocalStorage, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"markMessagesAsReadByMsgID", nullptr, NAPI_markMessagesAsReadByMsgID, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        // Friend
        {"getSpecifyFriendsInfo", nullptr, NAPI_getSpecifyFriendsInfo, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"getFriendList", nullptr, NAPI_getFriendList, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getFriendListPage", nullptr, NAPI_getFriendListPage, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"searchFriends", nullptr, NAPI_searchFriends, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"checkFriend", nullptr, NAPI_checkFriend, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"addFriend", nullptr, NAPI_addFriend, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"updateFriends", nullptr, NAPI_updateFriends, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"deleteFriend", nullptr, NAPI_deleteFriend, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getFriendApplicationListAsRecipient", nullptr, NAPI_getFriendApplicationListAsRecipient, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"getFriendApplicationListAsApplicant", nullptr, NAPI_getFriendApplicationListAsApplicant, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"acceptFriendApplication", nullptr, NAPI_acceptFriendApplication, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"refuseFriendApplication", nullptr, NAPI_refuseFriendApplication, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"addBlack", nullptr, NAPI_addBlack, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getBlackList", nullptr, NAPI_getBlackList, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"removeBlack", nullptr, NAPI_removeBlack, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getFriendApplicationUnhandledCount", nullptr, NAPI_getFriendApplicationUnhandledCount, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"setFriendRemark", nullptr, NAPI_setFriendRemark, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getSpecifiedFriendsInfo", nullptr, NAPI_getSpecifiedFriendsInfo, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        // Group
        {"createGroup", nullptr, NAPI_createGroup, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getJoinedGroupList", nullptr, NAPI_getJoinedGroupList, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getGroupsInfo", nullptr, NAPI_getGroupsInfo, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setGroupInfo", nullptr, NAPI_setGroupInfo, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getJoinedGroupListPage", nullptr, NAPI_getJoinedGroupListPage, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"changeGroupMute", nullptr, NAPI_changeGroupMute, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"changeGroupMemberMute", nullptr, NAPI_changeGroupMemberMute, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"getGroupMemberList", nullptr, NAPI_getGroupMemberList, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getGroupMemberOwnerAndAdmin", nullptr, NAPI_getGroupMemberOwnerAndAdmin, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"getUsersInGroup", nullptr, NAPI_getUsersInGroup, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"searchGroupMembers", nullptr, NAPI_searchGroupMembers, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setGroupMemberInfo", nullptr, NAPI_setGroupMemberInfo, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"inviteUserToGroup", nullptr, NAPI_inviteUserToGroup, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"kickGroupMember", nullptr, NAPI_kickGroupMember, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getGroupApplicationUnhandledCount", nullptr, NAPI_getGroupApplicationUnhandledCount, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"acceptGroupApplication", nullptr, NAPI_acceptGroupApplication, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"refuseGroupApplication", nullptr, NAPI_refuseGroupApplication, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"transferGroupOwner", nullptr, NAPI_transferGroupOwner, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"quitGroup", nullptr, NAPI_quitGroup, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"dismissGroup", nullptr, NAPI_dismissGroup, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getSendMessageOpt", nullptr, NAPI_getSendMessageOpt, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getGroupApplicationListAsRecipient", nullptr, NAPI_getGroupApplicationListAsRecipient, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"getGroupApplicationListAsApplicant", nullptr, NAPI_getGroupApplicationListAsApplicant, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"joinGroup", nullptr, NAPI_joinGroup, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"searchGroups", nullptr, NAPI_searchGroups, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"isJoinGroup", nullptr, NAPI_isJoinGroup, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getSpecifyGroupMembersInfo", nullptr, NAPI_getSpecifyGroupMembersInfo, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        {"getGroupMemberListByJoinTimeFilter", nullptr, NAPI_getGroupMemberListByJoinTimeFilter, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"getSpecifiedGroupsInfo", nullptr, NAPI_getSpecifiedGroupsInfo, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"getSpecifiedGroupMembersInfo", nullptr, NAPI_getSpecifiedGroupMembersInfo, nullptr, nullptr, nullptr,
         napi_default, nullptr},
        // Misc
        {"uploadFile", nullptr, NAPI_uploadFile, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"updateFcmToken", nullptr, NAPI_updateFcmToken, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setAppBadge", nullptr, NAPI_setAppBadge, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"uploadLogs", nullptr, NAPI_uploadLogs, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"logs", nullptr, NAPI_logs, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getSdkVersion", nullptr, NAPI_getSdkVersion, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"unInitSDK", nullptr, NAPI_unInitSDK, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getAtAllTag", nullptr, NAPI_getAtAllTag, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"changeInputStates", nullptr, NAPI_changeInputStates, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getInputStates", nullptr, NAPI_getInputStates, nullptr, nullptr, nullptr, napi_default, nullptr},
        // Listener
        {"setConnListener", nullptr, NAPI_setConnListener, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setAdvancedMsgListener", nullptr, NAPI_setAdvancedMsgListener, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"setBatchMsgListener", nullptr, NAPI_setBatchMsgListener, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setConversationListener", nullptr, NAPI_setConversationListener, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"setGroupListener", nullptr, NAPI_setGroupListener, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setFriendListener", nullptr, NAPI_setFriendListener, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setUserListener", nullptr, NAPI_setUserListener, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setSignalingListener", nullptr, NAPI_setSignalingListener, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setCustomBusinessListener", nullptr, NAPI_setCustomBusinessListener, nullptr, nullptr, nullptr, napi_default,
         nullptr},
        {"setMessageKvInfoListener", nullptr, NAPI_setMsgKvInfoListener, nullptr, nullptr, nullptr, napi_default, nullptr},
    };

    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    OH_LOG_INFO(LOG_APP, "IMSDK module initialized");
    return exports;
}
EXTERN_C_END

// ===== 模块注册 =====
static napi_module imsdkModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "imsdk",
    .nm_priv = ((void*)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterImsdkModule(void) {
    napi_module_register(&imsdkModule);
}
