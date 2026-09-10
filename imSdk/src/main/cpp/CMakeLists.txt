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

set_target_properties(imsdk PROPERTIES SKIP_BUILD_RPATH TRUE)
target_compile_features(imsdk PRIVATE cxx_std_17)
target_compile_options(imsdk PRIVATE -Wall -Wextra -Werror=array-bounds)
target_link_options(imsdk PRIVATE -Wl,--no-undefined)

target_link_libraries(imsdk
    PRIVATE
        libhilog_ndk.z.so
        libace_napi.z.so
        ${NATIVERENDER_ROOT_PATH}/../../../libs/${OHOS_ARCH}/libopenimsdk.so
        libc++_shared.so
)
