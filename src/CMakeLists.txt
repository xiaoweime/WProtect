#设置lua版本
Set (Lua_Version "_5.2.2")


#set (STATIC_LIBRARY 1)
#设置库文件
if (STATIC_LIBRARY)
set (LIBS AsmJit_Static Libudis86_Static 
    PE_Static OutOfOrder_Static 
    "Lua${Lua_Version}_Static" Analysis_Static   
    VirtualMachine_Static
    ELF_Static) #LibYasm_Static YasmStd_Static) EquivalentReplacement_Static
else()
set (LIBS AsmJit Libudis86
    PE OutOfOrder "Lua${Lua_Version}"
    VirtualMachine Analysis
    ELF) #LibYasm YasmStd) EquivalentReplacement
endif ()

#设置可执行文件源代码
set (WPROTECT_SOURCES 
main.cpp
)

#包含头文件目录
include_directories(WProtect/Protect/Analysis)
include_directories(AsmJit)
include_directories(Libudis86)
include_directories(Disasm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(WProtect/PE)
include_directories(WProtect/ELF)
include_directories(WProtect/Protect/OutOfOrder)
include_directories(WProtect/Protect/EquivalentReplacement)
include_directories(Lua)
include_directories(WProtect/DataStruct)
include_directories(WProtect/Protect/Algorithms)
include_directories(WProtect/Protect/VirtualMachine)
include_directories(WProtect/Analysis)
#include_directories(WProtect/CryptoPP)
#add_subdirectory(Yasm)

#添加执行目录
add_subdirectory(Disasm)
add_subdirectory(AsmJit)
add_subdirectory(Libudis86)  
add_subdirectory(WProtect)
add_subdirectory(Lua)
#add_subdirectory(CryptoPP)
#add_subdirectory(Yasm)

if (QT_GUI)
add_subdirectory(Frontends)
endif ()

#set (RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")

#set (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/")

add_executable(WProtect ${WPROTECT_SOURCES})

target_link_libraries(WProtect ${LIBS})

message ("EXECUTABLE DIR: ${EXECUTABLE_OUTPUT_PATH}")

message ("RUNTIME DIR: ${RUNTIME_OUTPUT_DIRECTORY}")

Message ("src:" ${WPROTECT_SOURCES})

