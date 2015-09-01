If(NOT DISASM_DIR)
  Set(LIBUDIS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
EndIf()


Set(DISASM_SOURCES
asmserv.cpp
assembl.cpp
disasm.cpp
)

include_directories(LIBUDIS_DIR)
#include_directories(include)

if (LIBRARY_TYPE_SHARED)
add_library(Disasm SHARED ${DISASM_SOURCES})
endif ()

if (LIBRARY_TYPE_STATIC)
add_library(Disasm_Static STATIC ${DISASM_SOURCES})
#set_target_properties(Disasm_Static PROPERTIES OUTPUT_NAME "Disasm")
endif ()
