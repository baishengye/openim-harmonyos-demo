# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(openim-harmonyos-demo)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(imsdk SHARED
    callback.cpp
    conversation.cpp
    friend.cpp
    group.cpp
    listener.cpp
    login.cpp
    message.cpp
    misc.cpp
    napi_init.cpp
    user.cpp
    utils.cpp)

# 链接依赖（暂时注释掉libopenimsdk.so，先确保libimsdk.so能正常加载）
target_link_libraries(imsdk
    PUBLIC
        libhilog_ndk.z.so
        libace_napi.z.so
        ${NATIVERENDER_ROOT_PATH}/../../../libs/${OHOS_ARCH}/libopenimsdk.so
        libc++_shared.so
)
