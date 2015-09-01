If(NOT ELFFILE_DIR)
  Set(ELFFILE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
Endif()

set (
ELFFILE_SOURCES
#elffile.cpp
ELFFile.cpp
)


Include_Directories(${ELFFILE_DIR})

if (LIBRARY_TYPE_SHARED)
  add_library(ELF SHARED ${ELFFILE_SOURCES})
endif ()


if (LIBRARY_TYPE_STATIC)
  add_library(ELF_Static STATIC ${ELFFILE_SOURCES})
endif ()

