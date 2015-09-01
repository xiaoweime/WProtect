If(NOT ALGORITHMS_DIR)
  Set(ALGORITHMS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
Endif()

set (
ALGORITHMS_SOURCES
random.cpp
)

if (STATIC_LIBRARY)
Set (
ALGORITHMS_LIBS
)
else()
Set (
ALGORITHMS_LIBS
)
endif()


Include_Directories(${ALGORITHMS_DIR})

if (LIBRARY_TYPE_SHARED)
add_library(Algorithms SHARED ${ALGORITHMS_SOURCES})
target_link_libraries (Algorithms ${ALGORITHMS_LIBS})
endif ()


if (LIBRARY_TYPE_STATIC)
add_library(Algorithms_Static STATIC ${ALGORITHMS_SOURCES})
target_link_libraries (Algorithms_Static ${ALGORITHMS_LIBS})
endif ()




