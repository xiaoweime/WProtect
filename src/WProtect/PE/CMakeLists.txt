include_directories("${PROJECT_SOURCE_DIR}/inc")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set (PE_SOURCES
PEExport.cpp
PEFile.cpp
PEImport.cpp
PESection.cpp
PEReloc.cpp
)


set (PE_HEADERS
PEExport.h
PEFile.h
PEImport.h
PESection.h
)

#set(WPROTECT_SOURCES ${WPROTECT_SOURCES} ${PE_SOURCES})

if (LIBRARY_TYPE_SHARED)
add_library(PE SHARED ${PE_SOURCES})
endif ()

if (LIBRARY_TYPE_STATIC)
add_library(PE_Static STATIC ${PE_SOURCES})
#set_target_properties(PE_Static PROPERTIES OUTPUT_NAME "PE")
endif ()
