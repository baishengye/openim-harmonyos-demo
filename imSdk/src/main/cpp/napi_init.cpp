#include "libs/include/libopenimsdk.h"
#include "napi/native_api.h"
#include "hilog/log.h"  // ← 正确头文件
#include <string>
#include <thread>
#include <chrono>
#include "listener.h"
#include "message.h"
#include "login.h"
#include "message.h"
#include "conversation.h"
#include "group.h"
#include "friend.h"
#include "misc.h"

// ===== 模块初始化 =====
EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        { "setListener", nullptr, setListener, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "initSdk", nullptr, InitSdk, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "unInitSdk", nullptr, UnInitSdk, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "login", nullptr, Login, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "logout", nullptr, Logout, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setAppBackgroundStatus", nullptr, SetAppBackgroundStatus, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "networkStatusChanged", nullptr, NetworkStatusChanged, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getLoginStatus", nullptr, GetLoginStatus, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getLoginUser", nullptr, GetLoginUser, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createTextMessage", nullptr, CreateTextMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createAdvancedTextMessage", nullptr, CreateAdvancedTextMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createTextAtMessage", nullptr, CreateTextAtMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createLocationMessage", nullptr, CreateLocationMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createCustomMessage", nullptr, CreateCustomMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createQuoteMessage", nullptr, CreateQuoteMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createAdvancedQuoteMessage", nullptr, CreateAdvancedQuoteMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createCardMessage", nullptr, CreateCardMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createVideoMessageFromFullPath", nullptr, CreateVideoMessageFromFullPath, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createImageMessageFromFullPath", nullptr, CreateImageMessageFromFullPath, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createSoundMessageFromFullPath", nullptr, CreateSoundMessageFromFullPath, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createFileMessageFromFullPath", nullptr, CreateFileMessageFromFullPath, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createImageMessage", nullptr, CreateImageMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createImageMessageByUrl", nullptr, CreateImageMessageByUrl, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createSoundMessageByUrl", nullptr, CreateSoundMessageByUrl, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createSoundMessage", nullptr, CreateSoundMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createVideoMessageByUrl", nullptr, CreateVideoMessageByUrl, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createVideoMessage", nullptr, CreateVideoMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createFileMessageByUrl", nullptr, CreateFileMessageByUrl, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createFileMessage", nullptr, CreateFileMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createMergerMessage", nullptr, CreateMergerMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createFaceMessage", nullptr, CreateFaceMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createForwardMessage", nullptr, CreateForwardMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "sendMessage", nullptr, SendMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "sendMessageNotOss", nullptr, SendMessageNotOss, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "findMessageList", nullptr, FindMessageList, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getAdvancedHistoryMessageList", nullptr, GetAdvancedHistoryMessageList, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getAdvancedHistoryMessageListReverse", nullptr, GetAdvancedHistoryMessageListReverse, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "revokeMessage", nullptr, RevokeMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "typingStatusUpdate", nullptr, TypingStatusUpdate, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "markConversationMessageAsRead", nullptr, MarkConversationMessageAsRead, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "deleteMessageFromLocalStorage", nullptr, DeleteMessageFromLocalStorage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "deleteMessage", nullptr, DeleteMessage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "hideAllConversations", nullptr, HideAllConversations, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "deleteAllMsgFromLocalAndSvr", nullptr, DeleteAllMsgFromLocalAndSvr, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "deleteAllMsgFromLocal", nullptr, DeleteAllMsgFromLocal, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "clearConversationAndDeleteAllMsg", nullptr, ClearConversationAndDeleteAllMsg, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "deleteConversationAndDeleteAllMsg", nullptr, DeleteConversationAndDeleteAllMsg, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "insertSingleMessageToLocalStorage", nullptr, InsertSingleMessageToLocalStorage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "insertGroupMessageToLocalStorage", nullptr, InsertGroupMessageToLocalStorage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "searchLocalMessages", nullptr, SearchLocalMessages, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setMessageLocalEx", nullptr, SetMessageLocalEx, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "changeInputStates", nullptr, ChangeInputStates, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getInputStates", nullptr, GetInputStates, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getAllConversationList", nullptr, GetAllConversationList, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getConversationListSplit", nullptr, GetConversationListSplit, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getOneConversation", nullptr, GetOneConversation, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getMultipleConversation", nullptr, GetMultipleConversation, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setConversation", nullptr, SetConversation, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "hideConversation", nullptr, HideConversation, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setConversationDraft", nullptr, SetConversationDraft, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getTotalUnreadMsgCount", nullptr, GetTotalUnreadMsgCount, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getAtAllTag", nullptr, GetAtAllTag, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getConversationIdBySessionType", nullptr, GetConversationIdBySessionType, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getSpecifiedFriendsInfo", nullptr, GetSpecifiedFriendsInfo, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getFriendList", nullptr, GetFriendList, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getFriendListPage", nullptr, GetFriendListPage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "searchFriends", nullptr, SearchFriends, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "checkFriend", nullptr, CheckFriend, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "addFriend", nullptr, AddFriend, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "updateFriends", nullptr, UpdateFriends, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "deleteFriend", nullptr, DeleteFriend, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getFriendApplicationListAsRecipient", nullptr, GetFriendApplicationListAsRecipient, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getFriendApplicationListAsApplicant", nullptr, GetFriendApplicationListAsApplicant, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "acceptFriendApplication", nullptr, AcceptFriendApplication, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "refuseFriendApplication", nullptr, RefuseFriendApplication, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getFriendApplicationUnhandledCount", nullptr, GetFriendApplicationUnhandledCount, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "addBlack", nullptr, AddBlack, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getBlackList", nullptr, GetBlackList, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "removeBlack", nullptr, RemoveBlack, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createGroup", nullptr, CreateGroup, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "joinGroup", nullptr, JoinGroup, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "quitGroup", nullptr, QuitGroup, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "dismissGroup", nullptr, DismissGroup, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "changeGroupMute", nullptr, ChangeGroupMute, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "changeGroupMemberMute", nullptr, ChangeGroupMemberMute, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setGroupMemberInfo", nullptr, SetGroupMemberInfo, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getJoinedGroupList", nullptr, GetJoinedGroupList, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getJoinedGroupListPage", nullptr, GetJoinedGroupListPage, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getSpecifiedGroupsInfo", nullptr, GetSpecifiedGroupsInfo, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "searchGroups", nullptr, SearchGroups, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setGroupInfo", nullptr, SetGroupInfo, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getGroupMemberList", nullptr, GetGroupMemberList, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getGroupMemberOwnerAndAdmin", nullptr, GetGroupMemberOwnerAndAdmin, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getGroupMemberListByJoinTimeFilter", nullptr, GetGroupMemberListByJoinTimeFilter, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getSpecifiedGroupMembersInfo", nullptr, GetSpecifiedGroupMembersInfo, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "kickGroupMember", nullptr, KickGroupMember, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "transferGroupOwner", nullptr, TransferGroupOwner, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "inviteUserToGroup", nullptr, InviteUserToGroup, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getGroupApplicationListAsRecipient", nullptr, GetGroupApplicationListAsRecipient, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getGroupApplicationListAsApplicant", nullptr, GetGroupApplicationListAsApplicant, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "acceptGroupApplication", nullptr, AcceptGroupApplication, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "refuseGroupApplication", nullptr, RefuseGroupApplication, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getGroupApplicationUnhandledCount", nullptr, GetGroupApplicationUnhandledCount, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "searchGroupMembers", nullptr, SearchGroupMembers, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "isJoinGroup", nullptr, IsJoinGroup, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getUsersInGroup", nullptr, GetUsersInGroup, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getUsersInfo", nullptr, GetUsersInfo, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setSelfInfo", nullptr, SetSelfInfo, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getSelfUserInfo", nullptr, GetSelfUserInfo, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "uploadFile", nullptr, UploadFile, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "updateFcmToken", nullptr, UpdateFcmToken, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setAppBadge", nullptr, SetAppBadge, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "uploadLogs", nullptr, UploadLogs, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "logs", nullptr, Logs, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "subscribeUsersStatus", nullptr, SubscribeUsersStatus, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "unSubscribeUsersStatus", nullptr, UnSubscribeUsersStatus, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getSubscribeUsersStatus", nullptr, GetSubscribeUsersStatus, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getUserStatus", nullptr, GetUserStatus, nullptr, nullptr, nullptr, napi_default, nullptr },
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
    .nm_priv = nullptr,
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterImsdkModule(void) {
    napi_module_register(&imsdkModule);
}