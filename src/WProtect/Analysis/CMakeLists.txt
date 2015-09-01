If(NOT ANALYSIS_DIR)
  Set(ANALYSIS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
Endif()

set (
ANALYSIS_SOURCES
Analysis.cpp
)

if (STATIC_LIBRARY)
Set (
ANALYSIS_LIBS
Libudis86_Static
)
else()
Set (
ANALYSIS_LIBS
Libudis86
)
endif()



Include_Directories(${ANALYSIS_DIR})


if (LIBRARY_TYPE_SHARED)
add_library(Analysis SHARED ${ANALYSIS_SOURCES})
target_link_libraries (Analysis ${ANALYSIS_LIBS})
endif ()


if (LIBRARY_TYPE_STATIC)
add_library(Analysis_Static STATIC ${ANALYSIS_SOURCES})
target_link_libraries (Analysis_Static ${ANALYSIS_LIBS})
endif ()

