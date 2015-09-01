If(NOT LIBUDIS_DIR)
  Set(LIBUDIS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
EndIf()


Set(UDIS86_SOURCES
decode.c
itab.c
syn.c
syn-att.c
syn-intel.c
udis86.c)

Set(UDIS86_HEADERS
decode.h
extern.h
input.h
itab.h
syn.h
types.h
udis86.h)


Include_Directories(${LIBUDIS_DIR})

if (LIBRARY_TYPE_SHARED)
add_library(Libudis86 SHARED ${UDIS86_SOURCES})
endif ()

if (LIBRARY_TYPE_STATIC)
add_library(Libudis86_Static STATIC ${UDIS86_SOURCES})
#set_target_properties(Libudis86_Static PROPERTIES OUTPUT_NAME "Libudis86")
endif ()
