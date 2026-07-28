# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(myNpmLib)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

# =============== 1. 声明导入库（必须先做！）===============
add_library(openimsdk SHARED IMPORTED)

# =============== 2. 设置 .so 路径 =========================
# 注意：DevEco Studio 传入的 OHOS_ARCH = arm64-v8a
set_target_properties(openimsdk
    PROPERTIES
    IMPORTED_LOCATION ${NATIVERENDER_ROOT_PATH}/libs/${OHOS_ARCH}/libopenimsdk.so
)

# =============== 3. 添加你的 native 模块 ================
include_directories(
    ${NATIVERENDER_ROOT_PATH}
    ${NATIVERENDER_ROOT_PATH}/include
    ${NATIVERENDER_ROOT_PATH}/libs/include
)

add_library(imsdk SHARED napi_init.cpp utils.cpp listener.cpp include/callback.cpp)

# =============== 4. 链接依赖 =============================
target_link_libraries(imsdk
    PUBLIC
        libhilog_ndk.z.so
        libace_napi.z.so
        openimsdk
)