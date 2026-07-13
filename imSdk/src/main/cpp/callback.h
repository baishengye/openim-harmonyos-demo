//
// Created on 2025/12/31.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "utils.h"
#ifndef IMDEMO_CALLBACK_H
#define IMDEMO_CALLBACK_H
struct TsfRegistration {
    napi_value promise = nullptr;
    bool should_proceed = false;
};
void ThrowError(napi_env env, int32_t errCode, const char* errorMsg);
napi_value ReturnVoid(napi_env env);
TsfRegistration CreateTSF(napi_env env, const std::string& opID, napi_value jsCB);

void RegisterSISSI(char *opID, int errCode, char* errMsg, char* data, int progress);
void OnCallJSSISSI(napi_env env,napi_value js_callback,void* /*context*/,void* data);

void RegisterSISS(char *opID, int errCode, char* errMsg, char* data);
void OnCallJSSISS(napi_env env,napi_value js_callback,void* /*context*/,void* data);
#endif //IMDEMO_CALLBACK_H
