CMake_Minimum_Required(VERSION 2.6)
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")#就是这两行东东
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")#
project(WProtect)

#set (LIBRARY_TYPE_SHARED 0)  #是否生成共享链接库
#set (LIBRARY_TYPE_STATIC 1)  #是否生成静态链接库

set(WPROTECT_VERSION_MAJOR 1)
set(WPROTECT_VERSION_MINOR 2)

option(PROTECT_X64 "protect 64 binrary" OFF)
#option(DEBUG "the is debug" OFF)

option(DEBUG "the is debug" OFF)

option(X86 "the is X86" ON)
option(STATIC_LIBRARY "the is static library" ON)
option(LIBRARY_TYPE_STATIC "static lib" ON)
option(LIBRARY_TYPE_SHARED "share lib" ON)
option(QT_GUI "gui executable" OFF)


if (NOT PROTECT_X64)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    set (BUILD_HOST "x86_32")
endif()

#编译数据库文件
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(
"${PROJECT_SOURCE_DIR}/WProtectConfig.h.in"
"${PROJECT_BINARY_DIR}/WProtectConfig.h"
)
#configure_file(
#"${PROJECT_SOURCE_DIR}/bin/build_vm_handle.lua"
#"${PROJECT_BINARY_DIR}/bin/build_vm_handle.lua"
#)             

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})
include_directories(inc)
include_directories(inc/coff)
include_directories(inc/elf)

set (LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin/")
set (EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin/")

add_subdirectory(src)
