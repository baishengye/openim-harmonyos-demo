//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "message.h"
#include "callback.h"
#include "utils.h"

/*
@napi-ts
创建文本消息.
@param operationID - 唯一操作标识
@param text - 文本内容
@returns string
@signature export function createTextMessage(operationID: string, text: string): string;
*/
napi_value CreateTextMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto text = GetJSString(env, args[1]);
    const char *msg = create_text_message(const_cast<char*>(operationID.c_str()), const_cast<char*>(text.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建高级文本消息.
@param operationID - 唯一操作标识
@param text - 唯一操作标识
@param messageEntityList - 消息实例列表
@returns string
@signature export function createAdvancedTextMessage(operationID: string, text: string, messageEntityList: string): string;
*/
napi_value CreateAdvancedTextMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto text = GetJSString(env, args[1]);
    auto messageEntityList = GetJSString(env, args[2]);
    const char *msg = create_advanced_text_message(const_cast<char*>(operationID.c_str()), const_cast<char*>(text.c_str()), const_cast<char*>(messageEntityList.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建At消息.
@param operationID - 唯一操作标识
@param text - 唯一操作标识
@param atUserList - 唯一操作标识
@param atUsersInfo - 唯一操作标识
@param message - 唯一操作标识
@returns string
@signature export function createTextAtMessage(operationID: string, text: string, atUserList: string, atUsersInfo: string, message: string): string;
*/
napi_value CreateTextAtMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 5;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto text = GetJSString(env, args[1]);
    auto atUserList = GetJSString(env, args[2]);
    auto atUsersInfo = GetJSString(env, args[3]);
    auto message = GetJSString(env, args[4]);
    const char *msg = create_text_at_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(text.c_str()), 
                                             const_cast<char*>(atUserList.c_str()),
                                             const_cast<char*>(atUsersInfo.c_str()),
                                             const_cast<char*>(message.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建位置消息.
@param operationID - 唯一操作标识
@param description - 描述
@param longitude - 经度
@param latitude - 维度
@returns string
@signature export function createLocationMessage(operationID: string, description: string, longitude: number, latitude: number): string;
*/
napi_value CreateLocationMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto description = GetJSString(env, args[1]);
    auto longitude = GetJSDouble(env, args[2]);
    auto latitude = GetJSDouble(env, args[3]);
    const char *msg = create_location_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(description.c_str()), 
                                             longitude, latitude);
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建自定义消息.
@param operationID - 唯一操作标识
@param data - 文本内容
@param extension - 扩展内容
@param description - 描述内容
@returns string
@signature export function createCustomMessage(operationID: string, data: string, extension: string, description: string): string;
*/
napi_value CreateCustomMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto data = GetJSString(env, args[1]);
    auto extension = GetJSString(env, args[2]);
    auto description = GetJSString(env, args[3]);
    const char *msg = create_custom_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(data.c_str()), 
                                             const_cast<char*>(extension.c_str()), const_cast<char*>(description.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建引用消息.
@param operationID - 唯一操作标识
@param data - 文本内容
@param message - 被引用的消息
@returns string
@signature export function createQuoteMessage(operationID: string, data: string, message: string): string;
*/
napi_value CreateQuoteMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto data = GetJSString(env, args[1]);
    auto message = GetJSString(env, args[2]);
    const char *msg = create_quote_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(data.c_str()), 
                                             const_cast<char*>(message.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建高级引用消息.
@param operationID - 唯一操作标识
@param data - 文本内容
@param message - 被引用的消息
@param messageEntityList - 消息实例列表
@returns string
@signature export function createAdvancedQuoteMessage(operationID: string, data: string, message: string, messageEntityList: string): string;
*/
napi_value CreateAdvancedQuoteMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto data = GetJSString(env, args[1]);
    auto message = GetJSString(env, args[2]);
    auto messageEntityList = GetJSString(env, args[2]);
    const char *msg = create_advanced_quote_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(data.c_str()), 
                                             const_cast<char*>(message.c_str()), 
                                             const_cast<char*>(messageEntityList.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建卡片消息.
@param operationID - 唯一操作标识
@param cardInfo - 卡片内容
@returns string
@signature export function createCardMessage(operationID: string, cardInfo: string): string;
*/
napi_value CreateCardMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto cardInfo = GetJSString(env, args[1]);
    const char *msg = create_card_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(cardInfo.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建本地路径视频消息.
@param operationID - 唯一操作标识
@param videoFullPath - 文件绝对路径
@param videoType - 视频类型
@param duration - 视频时长
@param snapshotFullPath - 预览图绝对路径
@returns string
@signature export function createVideoMessageFromFullPath(operationID: string, videoFullPath: string, videoType: string, duration: number, snapshotFullPath: string): string;
*/
napi_value CreateVideoMessageFromFullPath(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 5;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto videoFullPath = GetJSString(env, args[1]);
    auto videoType = GetJSString(env, args[2]);
    auto duration = GetJSInt64(env, args[3]);
    auto snapshotFullPath = GetJSString(env, args[4]);
    const char *msg = create_video_message_from_full_path(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(videoFullPath.c_str()),
                                             const_cast<char*>(videoType.c_str()),
                                             duration,
                                             const_cast<char*>(snapshotFullPath.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建本地路径图片消息.
@param operationID - 唯一操作标识
@param imageFullPath - 文件绝对路径
@returns string
@signature export function createImageMessageFromFullPath(operationID: string, imageFullPath: string): string;
*/
napi_value CreateImageMessageFromFullPath(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto imageFullPath = GetJSString(env, args[1]);
    const char *msg = create_image_message_from_full_path(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(imageFullPath.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建本地路径语音消息.
@param operationID - 唯一操作标识
@param soundPath - 文件绝对路径
@param duration - 音频时长
@returns string
@signature export function createSoundMessageFromFullPath(operationID: string, soundPath: string, duration: number): string;
*/
napi_value CreateSoundMessageFromFullPath(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto soundPath = GetJSString(env, args[1]);
    auto duration = GetJSInt64(env, args[2]);
    const char *msg = create_sound_message_from_full_path(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(soundPath.c_str()), duration);
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建本地路径文件消息.
@param operationID - 唯一操作标识
@param fileFullPath - 文件绝对路径
@param fileName - 文件名称
@returns string
@signature export function createSoundMessageFromFullPath(operationID: string, fileFullPath: string, fileName: string): string;
*/
napi_value CreateFileMessageFromFullPath(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto fileFullPath = GetJSString(env, args[1]);
    auto fileName = GetJSString(env, args[2]);
    const char *msg = create_file_message_from_full_path(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(fileFullPath.c_str()), 
                                             const_cast<char*>(fileName.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建图片文件消息.
@param operationID - 唯一操作标识
@param imagePath - 文件本地绝对路径
@returns string
@signature export function createImageMessage(operationID: string, imagePath: string): string;
*/
napi_value CreateImageMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto imagePath = GetJSString(env, args[1]);
    const char *msg = create_image_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(imagePath.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建URL地址图片消息.
@param operationID - 唯一操作标识
@param sourcePath - 源文件绝对路径
@param sourcePicture - 原图相关信息
@param bigPicture - 大图相关信息
@param snapshotPicture - 缩略图相关信息
@returns string
@signature export function createImageMessageByUrl(operationID: string, sourcePath: string, sourcePicture: string, bigPicture: string, snapshotPicture: string): string;
*/
napi_value CreateImageMessageByUrl(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 5;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto sourcePath = GetJSString(env, args[1]);
    auto sourcePicture = GetJSString(env, args[2]);
    auto bigPicture = GetJSString(env, args[3]);
    auto snapshotPicture = GetJSString(env, args[4]);
    const char *msg = create_image_message_by_url(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(sourcePath.c_str()),
                                             const_cast<char*>(sourcePicture.c_str()),
                                             const_cast<char*>(bigPicture.c_str()),
                                             const_cast<char*>(snapshotPicture.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建URL地址音频消息.
@param operationID - 唯一操作标识
@param sourcePath - 源文件URL
@returns string
@signature export function createSoundMessageByUrl(operationID: string, sourcePath: string): string;
*/
napi_value CreateSoundMessageByUrl(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto sourcePath = GetJSString(env, args[1]);
    const char *msg = create_sound_message_by_url(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(sourcePath.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建本地地址音频消息.
@param operationID - 唯一操作标识
@param sourcePath - 源文件绝对路径
@param duration - 时长
@returns string
@signature export function createSoundMessage(operationID: string, sourcePath: string, duration: number): string;
*/
napi_value CreateSoundMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto sourcePath = GetJSString(env, args[1]);
    auto duration = GetJSInt64(env, args[2]);
    const char *msg = create_sound_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(sourcePath.c_str()),
                                             duration);
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建URL地址视频消息.
@param operationID - 唯一操作标识
@param videoBaseInfo - 视频信息
@returns string
@signature export function createVideoMessageByUrl(operationID: string, videoBaseInfo: string): string;
*/
napi_value CreateVideoMessageByUrl(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto videoBaseInfo = GetJSString(env, args[1]);
    const char *msg = create_video_message_by_url(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(videoBaseInfo.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建视频消息.
@param operationID - 唯一操作标识
@param videoPath - 视频绝对信息
@param videoType - 视频类型
@param duration - 视频时长
@param snapshotPath - 视频缩略图
@returns string
@signature export function createVideoMessage(operationID: string, videoPath: string, videoType: string, duration: number, snapshotPath: string): string;
*/
napi_value CreateVideoMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 5;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto videoPath = GetJSString(env, args[1]);
    auto videoType = GetJSString(env, args[2]);
    auto duration = GetJSInt64(env, args[3]);
    auto snapshotPath = GetJSString(env, args[4]);
    const char *msg = create_video_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(videoPath.c_str()),
                                             const_cast<char*>(videoType.c_str()),
                                             duration,
                                             const_cast<char*>(snapshotPath.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建URL地址文件消息.
@param operationID - 唯一操作标识
@param fileBaseInfo - 文件信息
@returns string
@signature export function createFileMessageByUrl(operationID: string, fileBaseInfo: string): string;
*/
napi_value CreateFileMessageByUrl(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto fileBaseInfo = GetJSString(env, args[1]);
    const char *msg = create_file_message_by_url(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(fileBaseInfo.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建文件消息.
@param operationID - 唯一操作标识
@param filePath - 文件绝对路径
@param fileName - 文件名称
@returns string
@signature export function createFileMessage(operationID: string, filePath: string, fileName: string): string;
*/
napi_value CreateFileMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto filePath = GetJSString(env, args[1]);
    auto fileName = GetJSString(env, args[2]);
    const char *msg = create_file_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(filePath.c_str()),
                                             const_cast<char*>(fileName.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建合并消息.
@param operationID - 唯一操作标识
@param messageList - 消息列表
@param title - 标题
@param summaryList - 子标题列表
@returns string
@signature export function createMergerMessage(operationID: string, messageList: string, title: string, summaryList: string): string;
*/
napi_value CreateMergerMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto messageList = GetJSString(env, args[1]);
    auto title = GetJSString(env, args[2]);
    auto summaryList = GetJSString(env, args[3]);
    const char *msg = create_merger_message(const_cast<char*>(operationID.c_str()), 
                                             const_cast<char*>(messageList.c_str()),
                                              const_cast<char*>(title.c_str()),
                                             const_cast<char*>(summaryList.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建表情消息.
@param operationID - 唯一操作标识
@param index - 表情索引
@param data - 表情数据
@returns string
@signature export function createFaceMessage(operationID: string, index: number, data: string): string;
*/
napi_value CreateFaceMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto index = GetJSInt32(env, args[1]);
    auto data = GetJSString(env, args[2]);
    const char *msg = create_face_message(const_cast<char*>(operationID.c_str()), 
                                             index,
                                              const_cast<char*>(data.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
创建转发消息.
@param operationID - 唯一操作标识
@param data - 转发的消息
@returns string
@signature export function createForwardMessage(operationID: string, data: string): string;
*/
napi_value CreateForwardMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto data = GetJSString(env, args[1]);
    const char *msg = create_forward_message(const_cast<char*>(operationID.c_str()), 
                                              const_cast<char*>(data.c_str()));
    return SetJSString(env, std::string(msg));
}

/*
@napi-ts
发送消息.
@param operationID - 唯一操作标识
@param message -
@param recvID - 
@param groupID - 
@param offlinePush - 
@param isOnlineOnly - 
@param operationID - 
@param (progress: number) => {} -
@returns Promise<string>
@signature export function sendMessage(operationID: string, message: string, recvID: string, groupID: string, offlinePush: string, isOnlineOnly: boolean, onProgress: (progress: number) => void): Promise<string>;
*/
napi_value SendMessage(napi_env env, napi_callback_info info) {
    size_t argc = 7;
    napi_value args[7];
    napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    
    auto opID = GetJSString(env, args[0]);
    auto message = GetJSString(env, args[1]);
    auto recvID = GetJSString(env, args[2]);
    auto groupID = GetJSString(env, args[3]);
    auto offlinePush = GetJSString(env, args[4]);
    auto isOnlineOnly = GetJSInt32(env, args[5]);
    napi_value onProgress = args[6];
    auto result = CreateTSF(env, opID, onProgress);
    if (result.should_proceed) {
    send_message(RegisterSISSI, const_cast<char*>(opID.c_str()), const_cast<char*>(message.c_str()),const_cast<char*>(recvID.c_str()),
                 const_cast<char*>(groupID.c_str()),const_cast<char*>(offlinePush.c_str()), isOnlineOnly);
    }
    return result.promise;
}

/*
@napi-ts
发送消息.
@param operationID - 唯一操作标识
@param message -
@param recvID - 
@param groupID - 
@param offlinePush - 
@param isOnlineOnly - 
@param operationID - 
@param (progress: number) => {} -
@returns Promise<string>
@signature export function sendMessageNotOss(operationID: string, message: string, recvID: string, groupID: string, offlinePush: string, isOnlineOnly: boolean, onProgress: (progress: number) => void): Promise<string>;
*/
napi_value SendMessageNotOss(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 7;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto opID = GetJSString(env, args[0]);
    auto message = GetJSString(env, args[1]);
    auto recvID = GetJSString(env, args[2]);
    auto groupID = GetJSString(env, args[3]);
    auto offlinePush = GetJSString(env, args[4]);
    auto isOnlineOnly = GetJSInt32(env, args[5]);
    napi_value onProgress = args[6];
    auto result = CreateTSF(env, opID, onProgress);
    if (result.should_proceed) {
    send_message_not_oss(RegisterSISSI, const_cast<char*>(opID.c_str()), const_cast<char*>(message.c_str()),const_cast<char*>(recvID.c_str()),
                 const_cast<char*>(groupID.c_str()),const_cast<char*>(offlinePush.c_str()), isOnlineOnly);
    }
    return result.promise;
}

/*
@napi-ts
查询消息列表.
@param operationID - 唯一操作标识
@param findMessageOptions - 搜索参数
@returns Promise<string>
@signature export function findMessageList(operationID: string, findMessageOptions: string): Promise<string>;
*/
napi_value FindMessageList(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto findMessageOptions = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        find_message_list(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(findMessageOptions.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
查询高级消息列表.
@param operationID - 唯一操作标识
@param getMessageOptions - 搜索参数
@returns Promise<string>
@signature export function getAdvancedHistoryMessageList(operationID: string, getMessageOptions: string): Promise<string>;
*/
napi_value GetAdvancedHistoryMessageList(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto getMessageOptions = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_advanced_history_message_list(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(getMessageOptions.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
反序查询高级消息列表.
@param operationID - 唯一操作标识
@param getMessageOptions - 搜索参数
@returns Promise<string>
@signature export function getAdvancedHistoryMessageListReverse(operationID: string, getMessageOptions: string): Promise<string>;
*/
napi_value GetAdvancedHistoryMessageListReverse(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto getMessageOptions = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_advanced_history_message_list_reverse(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(getMessageOptions.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
撤回消息.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@param clientMsgID - 消息ID
@returns Promise<string>
@signature export function revokeMessage(operationID: string, conversationID: string, clientMsgID: string): Promise<string>;
*/
napi_value RevokeMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto clientMsgID = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        revoke_message(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(conversationID.c_str()), const_cast<char*>(clientMsgID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
输入状态更新.
@param operationID - 唯一操作标识
@param recvID - 接收者ID
@param msgTip - 提示消息
@returns Promise<string>
@signature export function typingStatusUpdate(operationID: string, recvID: string, msgTip: string): Promise<string>;
*/
napi_value TypingStatusUpdate(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto recvID = GetJSString(env, args[1]);
    auto msgTip = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        typing_status_update(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(recvID.c_str()), const_cast<char*>(msgTip.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
会话消息标记为已读.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@returns Promise<string>
@signature export function markConversationMessageAsRead(operationID: string, conversationID: string): Promise<string>;
*/
napi_value MarkConversationMessageAsRead(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        mark_conversation_message_as_read(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(conversationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
删除本地消息.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@param clientMsgID - 消息ID
@returns Promise<string>
@signature export function deleteMessageFromLocalStorage(operationID: string, conversationID: string, clientMsgID: string): Promise<string>;
*/
napi_value DeleteMessageFromLocalStorage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto clientMsgID = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        delete_message_from_local_storage(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(conversationID.c_str()),  const_cast<char*>(clientMsgID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
删除消息.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@param clientMsgID - 消息ID
@returns Promise<string>
@signature export function deleteMessage(operationID: string, conversationID: string, clientMsgID: string): Promise<string>;
*/
napi_value DeleteMessage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto clientMsgID = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        delete_message(RegisterSISS,const_cast<char*>(operationID.c_str()), 
                          const_cast<char*>(conversationID.c_str()),  const_cast<char*>(clientMsgID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
隐藏所有会话.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function hideAllConversations(operationID: string): Promise<string>;
*/
napi_value HideAllConversations(napi_env env, napi_callback_info info) {
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
        hide_all_conversations(RegisterSISS,const_cast<char*>(operationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
删除本地及服务器的所有消息.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function deleteAllMsgFromLocalAndSvr(operationID: string): Promise<string>;
*/
napi_value DeleteAllMsgFromLocalAndSvr(napi_env env, napi_callback_info info) {
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
        delete_all_msg_from_local_and_svr(RegisterSISS,const_cast<char*>(operationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
删除本地的所有消息.
@param operationID - 唯一操作标识
@returns Promise<string>
@signature export function deleteAllMsgFromLocal(operationID: string): Promise<string>;
*/
napi_value DeleteAllMsgFromLocal(napi_env env, napi_callback_info info) {
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
        delete_all_msg_from_local(RegisterSISS,const_cast<char*>(operationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
清除会话及删除会话的所有消息.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@returns Promise<string>
@signature export function clearConversationAndDeleteAllMsg(operationID: string, conversationID: string): Promise<string>;
*/
napi_value ClearConversationAndDeleteAllMsg(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        clear_conversation_and_delete_all_msg(RegisterSISS,const_cast<char*>(operationID.c_str()),const_cast<char*>(conversationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
删除会话及删除会话的所有消息.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@returns Promise<string>
@signature export function deleteConversationAndDeleteAllMsg(operationID: string, conversationID: string): Promise<string>;
*/
napi_value DeleteConversationAndDeleteAllMsg(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        delete_conversation_and_delete_all_msg(RegisterSISS,const_cast<char*>(operationID.c_str()),const_cast<char*>(conversationID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
插入单聊消息到本地.
@param operationID - 唯一操作标识
@param message - 
@param recvID - 
@param sendID - 
@returns Promise<string>
@signature export function insertSingleMessageToLocalStorage(operationID: string, message: string, recvID: string, sendID: string): Promise<string>;
*/
napi_value InsertSingleMessageToLocalStorage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto message = GetJSString(env, args[1]);
    auto recvID = GetJSString(env, args[2]);
    auto sendID = GetJSString(env, args[3]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        insert_single_message_to_local_storage(RegisterSISS,
                                               const_cast<char*>(operationID.c_str()),
                                               const_cast<char*>(message.c_str()),
                                               const_cast<char*>(recvID.c_str()),
                                               const_cast<char*>(sendID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
插入群聊消息到本地.
@param operationID - 唯一操作标识
@param message - 
@param groupID - 
@param sendID - 
@returns Promise<string>
@signature export function insertGroupMessageToLocalStorage(operationID: string, message: string, groupID: string, sendID: string): Promise<string>;
*/
napi_value InsertGroupMessageToLocalStorage(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto message = GetJSString(env, args[1]);
    auto groupID = GetJSString(env, args[2]);
    auto sendID = GetJSString(env, args[3]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        insert_group_message_to_local_storage(RegisterSISS,
                                               const_cast<char*>(operationID.c_str()),
                                               const_cast<char*>(message.c_str()),
                                               const_cast<char*>(groupID.c_str()),
                                               const_cast<char*>(sendID.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
搜索本地消息.
@param operationID - 唯一操作标识
@param searchParam - 搜索参数
@returns Promise<string>
@signature export function searchLocalMessages(operationID: string, searchParam: string): Promise<string>;
*/
napi_value SearchLocalMessages(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 2;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto searchParam = GetJSString(env, args[1]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        search_local_messages(RegisterSISS,
                              const_cast<char*>(operationID.c_str()),
                              const_cast<char*>(searchParam.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
设置消息本地ex字段.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@param clientMsgID - 消息ID
@param localEx - 扩展字段内容
@returns Promise<string>
@signature export function setMessageLocalEx(operationID: string, conversationID: string, clientMsgID: string, localEx: string): Promise<string>;
*/
napi_value SetMessageLocalEx(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 4;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto clientMsgID = GetJSString(env, args[2]);
    auto localEx = GetJSString(env, args[3]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        set_message_local_ex(RegisterSISS,
                             const_cast<char*>(operationID.c_str()),
                             const_cast<char*>(conversationID.c_str()),
                             const_cast<char*>(clientMsgID.c_str()),
                             const_cast<char*>(localEx.c_str()));
    }
    return result.promise;
}

/*
@napi-ts
改变输入状态.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@param inputStatus - 输入状态
@returns Promise<string>
@signature export function changeInputStates(operationID: string, conversationID: string, inputStatus: boolean): Promise<string>;
*/
napi_value ChangeInputStates(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto inputStatus = GetJSBoolean(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        change_input_states(RegisterSISS,
                             const_cast<char*>(operationID.c_str()),
                             const_cast<char*>(conversationID.c_str()),
                             inputStatus);
    }
    return result.promise;
}

/*
@napi-ts
获取输入状态.
@param operationID - 唯一操作标识
@param conversationID - 会话ID
@param userID - 用户ID
@returns Promise<string>
@signature export function getInputStates(operationID: string, conversationID: string, userID: string): Promise<string>;
*/
napi_value GetInputStates(napi_env env, napi_callback_info info) {
    constexpr size_t kArgc = 3;
    napi_value args[kArgc];
    size_t argc = kArgc;
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc < kArgc) {
        ThrowError(env, ARG_ERR, "missing arguments");
        return nullptr;
    }
    auto operationID = GetJSString(env, args[0]);
    auto conversationID = GetJSString(env, args[1]);
    auto userID = GetJSString(env, args[2]);
    auto result = CreateTSF(env, operationID, nullptr);
    if (result.should_proceed) {
        get_input_states(RegisterSISS,
                             const_cast<char*>(operationID.c_str()),
                             const_cast<char*>(conversationID.c_str()),
                             const_cast<char*>(userID.c_str()));
    }
    return result.promise;
}