#ifndef UTILS_H
#define UTILS_H

#include "libs/include/libopenimsdk.h"
#include "napi/native_api.h"
#include <string>

// Get values from JavaScript
std::string GetStringFromJS(napi_env env, napi_value value);
int GetIntFromJS(napi_env env, napi_value value);
long long GetInt64FromJS(napi_env env, napi_value value);
bool GetBoolFromJS(napi_env env, napi_value value);
double GetDoubleFromJS(napi_env env, napi_value value);

// Create JavaScript values
napi_value CreateJSString(napi_env env, const std::string& str);
napi_value CreateJSInt(napi_env env, int val);
napi_value CreateJSInt64(napi_env env, long long val);
napi_value CreateJSDouble(napi_env env, double val);
napi_value CreateJSBool(napi_env env, bool val);
napi_value CreateJSUndefined(napi_env env);
napi_value CreateJSNull(napi_env env);
napi_value CreateJSError(napi_env env, int errCode, const char* errMsg);

// Utility functions
void SafeStringCopy(char* dest, const char* src, size_t destSize);
std::string GenerateOperationID();
void LogInfo(const char* tag, const char* fmt, ...);
void LogError(const char* tag, const char* fmt, ...);

#endif // UTILS_H
