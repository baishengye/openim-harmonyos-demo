//
// Created on 2025/12/29.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include <string>
#include <unordered_map>
#include "hilog/log.h" 
#include "napi/native_api.h"
#include "libopenimsdk.h"
#include <mutex>
#ifndef IMDEMO_UTILS_H
#define IMDEMO_UTILS_H

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x3200  // 全局domain宏，标识业务领域
#define LOG_TAG "IMSDK"   // 全局tag宏，标识模块日志tag

#define NO_ERR 0
#define NO_PROGRESS 0
#define NO_ERR_MSG ""
#define ARG_ERR -1
#define NO_DATA std::string("")

std::string GetJSString(napi_env env, napi_value value);
int32_t GetJSInt32(napi_env env, napi_value value);
napi_value SetJSString(napi_env env, const std::string& str);
napi_value SetJSInt32(napi_env env, int32_t value);
int64_t GetJSInt64(napi_env env, napi_value value);
double GetJSDouble(napi_env env, napi_value value);
bool GetJSBoolean(napi_env env, napi_value value);
#endif //IMDEMO_UTILS_H
