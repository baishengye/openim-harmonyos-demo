#include "libs/include/libopenimsdk.h"
#include "napi/native_api.h"
#include "hilog/log.h"
#include "callback.h"
#include "utils.h"

// ==================== NAPI Functions ====================

napi_value NAPI_setConnListener(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (!args[0]) {
        DeleteConnListener();
        return nullptr;
    }

    napi_value listener = args[0];
    // 提取各个回调方法
    napi_value onConnecting, onConnectSuccess, onConnectFailed, onKickedOffline, onUserTokenExpired, onUserTokenInvalid;
    napi_get_named_property(env, listener, "onConnecting", &onConnecting);
    napi_get_named_property(env, listener, "onConnectSuccess", &onConnectSuccess);
    napi_get_named_property(env, listener, "onConnectFailed", &onConnectFailed);
    napi_get_named_property(env, listener, "onKickedOffline", &onKickedOffline);
    napi_get_named_property(env, listener, "onUserTokenExpired", &onUserTokenExpired);
    napi_get_named_property(env, listener, "onUserTokenInvalid", &onUserTokenInvalid);

    StoreConnListener(env, onConnecting, onConnectSuccess, onConnectFailed, onKickedOffline, onUserTokenExpired, onUserTokenInvalid);

    return nullptr;
}

napi_value NAPI_setAdvancedMsgListener(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (!args[0]) {
        DeleteMsgListener();
        return nullptr;
    }

    napi_value listener = args[0];
    // 提取各个回调方法
    napi_value onRecvNewMsg, onRecvReceipt, onMsgRevoked, onRecvOffline, onMsgDeleted, onRecvOnline;
    napi_get_named_property(env, listener, "onRecvNewMessage", &onRecvNewMsg);
    napi_get_named_property(env, listener, "onRecvC2CReadReceipt", &onRecvReceipt);
    napi_get_named_property(env, listener, "onNewRecvMessageRevoked", &onMsgRevoked);
    napi_get_named_property(env, listener, "onRecvOfflineNewMessage", &onRecvOffline);
    napi_get_named_property(env, listener, "onMsgDeleted", &onMsgDeleted);
    napi_get_named_property(env, listener, "onRecvOnlineOnlyMessage", &onRecvOnline);

    StoreMsgListener(env, onRecvNewMsg, onRecvReceipt, onMsgRevoked, onRecvOffline, onMsgDeleted, onRecvOnline);

    return nullptr;
}

napi_value NAPI_setBatchMsgListener(napi_env env, napi_callback_info info) {
    // BatchMsgListener 暂未在 callback.cpp 中实现，保持原有逻辑
    return nullptr;
}

napi_value NAPI_setConversationListener(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (!args[0]) {
        DeleteConvListener();
        return nullptr;
    }

    napi_value listener = args[0];
    // 提取各个回调方法
    napi_value onSyncStart, onSyncFinish, onSyncProgress, onSyncFailed, onConvChanged, onNewConv, onUnreadChanged, onInputStatus;
    napi_get_named_property(env, listener, "onSyncServerStart", &onSyncStart);
    napi_get_named_property(env, listener, "onSyncServerFinish", &onSyncFinish);
    napi_get_named_property(env, listener, "onSyncServerProgress", &onSyncProgress);
    napi_get_named_property(env, listener, "onSyncServerFailed", &onSyncFailed);
    napi_get_named_property(env, listener, "onConversationChanged", &onConvChanged);
    napi_get_named_property(env, listener, "onNewConversation", &onNewConv);
    napi_get_named_property(env, listener, "onTotalUnreadMessageCountChanged", &onUnreadChanged);
    napi_get_named_property(env, listener, "onConversationUserInputStatusChanged", &onInputStatus);

    StoreConvListener(env, onSyncStart, onSyncFinish, onSyncProgress, onSyncFailed, onConvChanged, onNewConv, onUnreadChanged, onInputStatus);

    return nullptr;
}

napi_value NAPI_setGroupListener(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (!args[0]) {
        DeleteGroupListener();
        return nullptr;
    }

    napi_value listener = args[0];
    // 提取各个回调方法
    napi_value onJoinedAdd, onJoinedDel, onMemberAdd, onMemberDel, onAppAdd, onAppDel, onInfoChanged, onDismissed, onMemberInfo, onAppAccept, onAppReject;
    napi_get_named_property(env, listener, "onJoinedGroupAdded", &onJoinedAdd);
    napi_get_named_property(env, listener, "onJoinedGroupDeleted", &onJoinedDel);
    napi_get_named_property(env, listener, "onGroupMemberAdded", &onMemberAdd);
    napi_get_named_property(env, listener, "onGroupMemberDeleted", &onMemberDel);
    napi_get_named_property(env, listener, "onGroupApplicationAdded", &onAppAdd);
    napi_get_named_property(env, listener, "onGroupApplicationDeleted", &onAppDel);
    napi_get_named_property(env, listener, "onGroupInfoChanged", &onInfoChanged);
    napi_get_named_property(env, listener, "onGroupDismissed", &onDismissed);
    napi_get_named_property(env, listener, "onGroupMemberInfoChanged", &onMemberInfo);
    napi_get_named_property(env, listener, "onGroupApplicationAccepted", &onAppAccept);
    napi_get_named_property(env, listener, "onGroupApplicationRejected", &onAppReject);

    StoreGroupListener(env, onJoinedAdd, onJoinedDel, onMemberAdd, onMemberDel, onAppAdd, onAppDel, onInfoChanged, onDismissed, onMemberInfo, onAppAccept, onAppReject);

    return nullptr;
}

napi_value NAPI_setFriendListener(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (!args[0]) {
        DeleteFriendListener();
        return nullptr;
    }

    napi_value listener = args[0];
    // 提取各个回调方法
    napi_value onAppAdd, onAppDel, onAppAccept, onAppReject, onFriendAdd, onFriendDel, onFriendInfo, onBlackAdd, onBlackDel;
    napi_get_named_property(env, listener, "onFriendApplicationAdded", &onAppAdd);
    napi_get_named_property(env, listener, "onFriendApplicationDeleted", &onAppDel);
    napi_get_named_property(env, listener, "onFriendApplicationAccepted", &onAppAccept);
    napi_get_named_property(env, listener, "onFriendApplicationRejected", &onAppReject);
    napi_get_named_property(env, listener, "onFriendAdded", &onFriendAdd);
    napi_get_named_property(env, listener, "onFriendDeleted", &onFriendDel);
    napi_get_named_property(env, listener, "onFriendInfoChanged", &onFriendInfo);
    napi_get_named_property(env, listener, "onBlackAdded", &onBlackAdd);
    napi_get_named_property(env, listener, "onBlackDeleted", &onBlackDel);

    StoreFriendListener(env, onAppAdd, onAppDel, onAppAccept, onAppReject, onFriendAdd, onFriendDel, onFriendInfo, onBlackAdd, onBlackDel);

    return nullptr;
}

napi_value NAPI_setUserListener(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (!args[0]) {
        DeleteUserListener();
        return nullptr;
    }

    napi_value listener = args[0];
    // 提取各个回调方法
    napi_value onSelfInfo, onUserStatus;
    napi_get_named_property(env, listener, "onSelfInfoUpdated", &onSelfInfo);
    napi_get_named_property(env, listener, "onUserStatusChanged", &onUserStatus);

    StoreUserListener(env, onSelfInfo, onUserStatus);

    return nullptr;
}

napi_value NAPI_setSignalingListener(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (!args[0]) {
        DeleteSignalingListener();
        return nullptr;
    }

    napi_value listener = args[0];
    // 提取各个回调方法
    napi_value onReceiveNewInvitation, onInviteeAccepted, onInviteeAcceptedByOtherDevice, onInviteeRejected, onInviteeRejectedByOtherDevice, onInvitationCancelled, onInvitationTimeout, onHangUp, onRoomParticipantConnected, onRoomParticipantDisconnected;
    napi_get_named_property(env, listener, "onReceiveNewInvitation", &onReceiveNewInvitation);
    napi_get_named_property(env, listener, "onInviteeAccepted", &onInviteeAccepted);
    napi_get_named_property(env, listener, "onInviteeAcceptedByOtherDevice", &onInviteeAcceptedByOtherDevice);
    napi_get_named_property(env, listener, "onInviteeRejected", &onInviteeRejected);
    napi_get_named_property(env, listener, "onInviteeRejectedByOtherDevice", &onInviteeRejectedByOtherDevice);
    napi_get_named_property(env, listener, "onInvitationCancelled", &onInvitationCancelled);
    napi_get_named_property(env, listener, "onInvitationTimeout", &onInvitationTimeout);
    napi_get_named_property(env, listener, "onHangUp", &onHangUp);
    napi_get_named_property(env, listener, "onRoomParticipantConnected", &onRoomParticipantConnected);
    napi_get_named_property(env, listener, "onRoomParticipantDisconnected", &onRoomParticipantDisconnected);

    StoreSignalingListener(env, onReceiveNewInvitation, onInviteeAccepted, onInviteeAcceptedByOtherDevice, onInviteeRejected, onInviteeRejectedByOtherDevice, onInvitationCancelled, onInvitationTimeout, onHangUp, onRoomParticipantConnected, onRoomParticipantDisconnected);

    return nullptr;
}

napi_value NAPI_setCustomBusinessListener(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (!args[0]) {
        DeleteCustomBusinessListener();
        return nullptr;
    }

    napi_value listener = args[0];
    napi_value onRecvCustomBusinessMessage;
    napi_get_named_property(env, listener, "onRecvCustomBusinessMessage", &onRecvCustomBusinessMessage);

    StoreCustomBusinessListener(env, onRecvCustomBusinessMessage);

    return nullptr;
}

napi_value NAPI_setMsgKvInfoListener(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (!args[0]) {
        DeleteMsgKvInfoListener();
        return nullptr;
    }

    napi_value listener = args[0];
    napi_value onMessageKvInfoChanged;
    napi_get_named_property(env, listener, "onMessageKvInfoChanged", &onMessageKvInfoChanged);

    StoreMsgKvInfoListener(env, onMessageKvInfoChanged);

    return nullptr;
}
