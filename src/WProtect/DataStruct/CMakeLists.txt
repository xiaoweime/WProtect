If(NOT LIST_DIR)
  Set(DATASTRUCTURE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
EndIf()

set (
DATASTRUCTURE_SOURCES
CodeList.cpp
AddrTable.cpp
)


Include_Directories(${DATASTRUCTURE_DIR})

if (LIBRARY_TYPE_SHARED)
add_library(DataStructure SHARED ${DATASTRUCTURE_SOURCES})
target_link_libraries (DataStructure ${DATASTRUCTURE_LIBS})
endif ()

if (LIBRARY_TYPE_STATIC)
add_library(DataStructure_Static STATIC ${DATASTRUCTURE_SOURCES})
target_link_libraries (DataStructure_Static ${EQUIVALENT_LIBS})
#set_target_properties(DataStructure_Static PROPERTIES OUTPUT_NAME "DataStructure")
endif ()