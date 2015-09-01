If(NOT EQUIVALENT_DIR)
  Set(EQUIVALENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
EndIf()

set (
EQUIVALENT_SOURCES
LuaEquivalentReplacement.cpp
EquivalentReplacement.cpp
)

if (STATIC_LIBRARY)
Set (
EQUIVALENT_LIBS
Libudis86_Static
AsmJit_Static
Disasm_Static
"Lua${Lua_Version}_Static"
DataStructure_Static
)
else()
Set (
EQUIVALENT_LIBS
Libudis86
AsmJit
Disasm
"Lua${Lua_Version}"
DataStructure
)
endif()


Include_Directories(${EQUIVALENT_DIR})

if (LIBRARY_TYPE_SHARED)
add_library(EquivalentReplacement SHARED ${EQUIVALENT_SOURCES})
target_link_libraries (EquivalentReplacement ${EQUIVALENT_LIBS})
endif ()

if (LIBRARY_TYPE_STATIC)
add_library(EquivalentReplacement_Static STATIC ${EQUIVALENT_SOURCES})
target_link_libraries (EquivalentReplacement_Static ${EQUIVALENT_LIBS})
#set_target_properties(EquivalentReplacement_Static PROPERTIES OUTPUT_NAME "EquivalentReplacement")
endif ()
