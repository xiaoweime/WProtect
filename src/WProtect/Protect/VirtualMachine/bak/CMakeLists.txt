If(NOT VIRTUALMACHINE_DIR)
  Set(VIRTUALMACHINE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
EndIf()

Set(
VIRTUALMACHINE_SOURCES
VMHandle.cpp
VirtualMachine.cpp
VirtualMachineManage.cpp
PCode.cpp
SeniorVMHandle.cpp
)

Set(
VIRTUALMACHINE_HEADERS
VMHandle.h
)

if (STATIC_LIBRARY)
Set (
VIRTUALMACHINE_LIBS
AsmJit_Static
)
else()
Set (
VIRTUALMACHINE_LIBS
AsmJit
)
endif()

Include_Directories(${VIRTUALMACHINE_DIR})

if (LIBRARY_TYPE_SHARED)
add_library(VirtualMachine SHARED ${VIRTUALMACHINE_SOURCES})
target_link_libraries (VirtualMachine ${VIRTUALMACHINE_LIBS})
endif ()

if (LIBRARY_TYPE_STATIC)
add_library(VirtualMachine_Static STATIC ${VIRTUALMACHINE_SOURCES})
target_link_libraries (VirtualMachine_Static ${VIRTUALMACHINE_LIBS})
#set_target_properties(OutOfOrder_Static PROPERTIES OUTPUT_NAME "OutOfOrder")
endif ()
