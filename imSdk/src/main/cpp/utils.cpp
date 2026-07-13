//
// Created on 2025/12/29.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "utils.h"

std::string GetJSString(napi_env env, napi_value value) {
    if (value == nullptr) return "";

    size_t len;
    napi_get_value_string_utf8(env, value, nullptr, 0, &len);
    if (len == 0) return "";

    std::vector<char> buf(len + 1);
    napi_get_value_string_utf8(env, value, buf.data(), buf.size(), &len);
    return std::string(buf.data(), len);
}
napi_value SetJSString(napi_env env, const std::string& str) {
    napi_value result;
    napi_status status = napi_create_string_utf8(
        env,
        str.c_str(),
        str.size(),         
        &result
    );
    if (status != napi_ok) {
        return nullptr;
    }
    return result;
}
int32_t GetJSInt32(napi_env env, napi_value value) {
    if (value == nullptr) {
        return 0;
    }

    napi_valuetype type;
    if (napi_typeof(env, value, &type) != napi_ok || type != napi_number) {
        return 0;
    }

    int32_t int_val = 0;
    if (napi_get_value_int32(env, value, &int_val) != napi_ok) {
        return 0;
    }

    return int_val;
}

napi_value SetJSInt32(napi_env env, int32_t value) {
    napi_value result;
    napi_status status = napi_create_int32(env, value, &result);
    if (status != napi_ok) {
        return nullptr;
    }
    return result;
}

int64_t GetJSInt64(napi_env env, napi_value value) {
    if (value == nullptr) {
        return 0;
    }

    napi_valuetype type;
    if (napi_typeof(env, value, &type) != napi_ok || type != napi_number) {
        return 0;
    }

    int64_t int_val = 0;
    if (napi_get_value_int64(env, value, &int_val) != napi_ok) {
        // 超出 int64 范围时，N-API 会返回 napi_number_expected 或类似错误
        return 0;
    }

    return int_val;
}

double GetJSDouble(napi_env env, napi_value value) {
    if (value == nullptr) {
        return 0.0; // 或 NaN？见下方说明
    }

    napi_valuetype type;
    if (napi_typeof(env, value, &type) != napi_ok || type != napi_number) {
        return 0.0; // 类型不是 number
    }

    double double_val = 0.0;
    if (napi_get_value_double(env, value, &double_val) != napi_ok) {
        return 0.0; // 理论上不会失败，但保留健壮性
    }

    return double_val;
}

bool GetJSBoolean(napi_env env, napi_value value) {
    if (value == nullptr) {
        return false; // 默认值
    }

    napi_valuetype type;
    if (napi_typeof(env, value, &type) != napi_ok || type != napi_boolean) {
        return false; // 类型不匹配，返回 false
    }

    bool bool_val = false;
    if (napi_get_value_bool(env, value, &bool_val) != napi_ok) {
        return false; // 获取失败，返回 false
    }

    return bool_val;
}