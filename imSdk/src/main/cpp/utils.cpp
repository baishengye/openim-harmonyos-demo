#include "utils.h"
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <cstring>


// Get string from napi_value
std::string GetStringFromJS(napi_env env, napi_value value) {
    if (!value) return "";

    napi_valuetype type = napi_undefined;
    if (napi_typeof(env, value, &type) != napi_ok || type != napi_string) return "";

    size_t len = 0;
    if (napi_get_value_string_utf8(env, value, nullptr, 0, &len) != napi_ok) return "";
    if (len == 0) return "";

    std::string result(len + 1, '\0');
    if (napi_get_value_string_utf8(env, value, &result[0], result.size(), &len) != napi_ok) return "";
    result.resize(len);
    return result;
}

// Get int from napi_value
int GetIntFromJS(napi_env env, napi_value value) {
    int32_t result = 0;
    if (!value) return result;

    napi_valuetype type = napi_undefined;
    if (napi_typeof(env, value, &type) != napi_ok) return result;
    if (type == napi_boolean) {
        bool booleanValue = false;
        if (napi_get_value_bool(env, value, &booleanValue) == napi_ok) {
            return booleanValue ? 1 : 0;
        }
        return result;
    }
    napi_get_value_int32(env, value, &result);
    return result;
}

// Get int64 from napi_value
long long GetInt64FromJS(napi_env env, napi_value value) {
    int64_t result = 0;
    if (value && napi_get_value_int64(env, value, &result) == napi_ok) return result;
    double fallback = 0;
    if (value) napi_get_value_double(env, value, &fallback);
    return static_cast<long long>(fallback);
}

// Get bool from napi_value
bool GetBoolFromJS(napi_env env, napi_value value) {
    bool result = false;
    if (!value) return result;

    napi_valuetype type = napi_undefined;
    if (napi_typeof(env, value, &type) != napi_ok) return result;
    if (type == napi_boolean) {
        napi_get_value_bool(env, value, &result);
        return result;
    }
    if (type == napi_number) {
        int32_t numericValue = 0;
        if (napi_get_value_int32(env, value, &numericValue) == napi_ok) {
            return numericValue != 0;
        }
    }
    return result;
}

// Get double from napi_value
double GetDoubleFromJS(napi_env env, napi_value value) {
    double result = 0;
    if (value) napi_get_value_double(env, value, &result);
    return result;
}

bool GetArgs(napi_env env, napi_callback_info info, size_t expected, napi_value* args) {
    size_t argc = expected;
    if (!args || napi_get_cb_info(env, info, &argc, args, nullptr, nullptr) != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to read native arguments");
        return false;
    }
    if (argc < expected) {
        napi_throw_type_error(env, nullptr, "Not enough arguments");
        return false;
    }
    return true;
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

std::string OperationIDOrGenerated(const std::string& operationID) {
    return operationID.empty() ? GenerateOperationID() : operationID;
}

char* MutableCString(const std::string& value) {
    return const_cast<char*>(value.c_str());
}

SdkString::~SdkString() {
    if (value_) FreeString(value_);
}

// Log helper
void LogInfo(const char* tag, const char* fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    OH_LOG_Print(LOG_APP, LOG_INFO, 0, tag, "%{public}s", buf);
}

void LogError(const char* tag, const char* fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    OH_LOG_Print(LOG_APP, LOG_ERROR, 0, tag, "%{public}s", buf);
}

void LogDebug(const char *tag, const char *fmt, ...){
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    OH_LOG_Print(LOG_APP, LOG_DEBUG, 0, tag, "%{public}s", buf);
}
