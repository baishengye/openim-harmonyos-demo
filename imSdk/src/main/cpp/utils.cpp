#include "libs/include/libopenimsdk.h"
#include "napi/native_api.h"
#include "hilog/log.h"
#include <string>
#include <cstring>
#include <cstdarg>
#include <chrono>

// Get string from napi_value
std::string GetStringFromJS(napi_env env, napi_value value) {
    if (!value) return "";

    napi_valuetype type;
    napi_typeof(env, value, &type);
    if (type != napi_string) return "";

    size_t len;
    napi_get_value_string_utf8(env, value, nullptr, 0, &len);
    if (len == 0) return "";

    std::string result(len, '\0');
    napi_get_value_string_utf8(env, value, &result[0], len + 1, &len);
    return result;
}

// Get int from napi_value
int GetIntFromJS(napi_env env, napi_value value) {
    int32_t result = 0;
    napi_get_value_int32(env, value, &result);
    return result;
}

// Get int64 from napi_value
long long GetInt64FromJS(napi_env env, napi_value value) {
    double result = 0;
    napi_get_value_double(env, value, &result);
    return (long long)result;
}

// Get bool from napi_value
bool GetBoolFromJS(napi_env env, napi_value value) {
    bool result = false;
    napi_get_value_bool(env, value, &result);
    return result;
}

// Get double from napi_value
double GetDoubleFromJS(napi_env env, napi_value value) {
    double result = 0;
    napi_get_value_double(env, value, &result);
    return result;
}

// Create string napi_value
napi_value CreateJSString(napi_env env, const std::string& str) {
    napi_value result;
    napi_create_string_utf8(env, str.c_str(), str.length(), &result);
    return result;
}

// Create int napi_value
napi_value CreateJSInt(napi_env env, int val) {
    napi_value result;
    napi_create_int32(env, val, &result);
    return result;
}

// Create int64 napi_value
napi_value CreateJSInt64(napi_env env, long long val) {
    napi_value result;
    napi_create_int64(env, val, &result);
    return result;
}

// Create double napi_value
napi_value CreateJSDouble(napi_env env, double val) {
    napi_value result;
    napi_create_double(env, val, &result);
    return result;
}

// Create bool napi_value
napi_value CreateJSBool(napi_env env, bool val) {
    napi_value result;
    napi_get_boolean(env, val, &result);
    return result;
}

// Create undefined napi_value
napi_value CreateJSUndefined(napi_env env) {
    napi_value result;
    napi_get_undefined(env, &result);
    return result;
}

// Create null napi_value
napi_value CreateJSNull(napi_env env) {
    napi_value result;
    napi_get_null(env, &result);
    return result;
}

// Create error napi_value
napi_value CreateJSError(napi_env env, int errCode, const char* errMsg) {
    napi_value err;
    napi_create_error(env, nullptr, nullptr, &err);
    napi_value code;
    napi_create_int32(env, errCode, &code);
    napi_set_named_property(env, err, "code", code);
    napi_value msg;
    napi_create_string_utf8(env, errMsg ? errMsg : "", NAPI_AUTO_LENGTH, &msg);
    napi_set_named_property(env, err, "message", msg);
    return err;
}

// Safe string copy
void SafeStringCopy(char* dest, const char* src, size_t destSize) {
    if (!dest || !src || destSize == 0) return;
    strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';
}

// Generate operation ID
std::string GenerateOperationID() {
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();
    return "napi_" + std::to_string(timestamp);
}

// Log helper
void LogInfo(const char* tag, const char* fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    OH_LOG_INFO(LOG_APP, "[%s] %{public}s", tag, buf);
}

void LogError(const char* tag, const char* fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    OH_LOG_ERROR(LOG_APP, "[%s] %{public}s", tag, buf);
}
