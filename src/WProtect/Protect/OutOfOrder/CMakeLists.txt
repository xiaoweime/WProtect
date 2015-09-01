If(NOT OUTOFORDER_DIR)
  Set(OUTOFORDER_DIR ${CMAKE_CURRENT_SOURCE_DIR})
EndIf()

Set(
OUTOFORDER_SOURCES
OutOfOrder.cpp
)

Set(
OUTOFORDER_HEADERS
OutOfOrder.h
)

if (STATIC_LIBRARY)
Set (
OUTOFORDER_LIBS
Libudis86_Static
AsmJit_Static
Disasm_Static
)
else()
Set (
OUTOFORDER_LIBS
Libudis86
AsmJit
Disasm
)
endif()

Include_Directories(${OUTOFORDER_DIR})


if (LIBRARY_TYPE_SHARED)
add_library(OutOfOrder SHARED ${OUTOFORDER_SOURCES})
target_link_libraries (OutOfOrder ${OUTOFORDER_LIBS})
endif ()

if (LIBRARY_TYPE_STATIC)
add_library(OutOfOrder_Static STATIC ${OUTOFORDER_SOURCES})
target_link_libraries (OutOfOrder_Static ${OUTOFORDER_LIBS})
#set_target_properties(OutOfOrder_Static PROPERTIES OUTPUT_NAME "OutOfOrder")
endif ()
