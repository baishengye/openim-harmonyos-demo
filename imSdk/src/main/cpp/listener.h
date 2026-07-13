//
// Created on 2025/12/28.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include "libs/include/libopenimsdk.h"
#include "utils.h"

#ifndef IMDEMO_ONLISTENER_H
#define IMDEMO_ONLISTENER_H

struct CBDataIS {
    int event; 
    std::string data;
};

struct CBDataSISS {
    std::string operationID;
    int errCode;
    std::string errMsg;
    std::string data;
};

/**********设置OhosSDK回调************/

napi_value setListener(napi_env env, napi_callback_info info);
void onListener(int event, char* data);

void releaseTSF();
#endif //IMDEMO_ONLISTENER_H
