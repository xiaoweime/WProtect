# Reguire minimum version of CMake
#CMake_Minimum_Required(VERSION 2.6)

# AsmJit project - Need to use both C and C++
#Project(AsmJit C CXX)

# If ASMJIT_DIR is not specified, assume that we are building it from here
If(NOT ASMJIT_DIR)
  Set(ASMJIT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
EndIf()

# AsmJit C++ sources
Set(ASMJIT_SOURCES
  AssemblerX86X64.cpp
  CodeGenerator.cpp
  Compiler.cpp
  CompilerX86X64.cpp
  CpuInfo.cpp
  Defs.cpp
  DefsX86X64.cpp
  Logger.cpp
  MemoryManager.cpp
  MemoryMarker.cpp
  OperandX86X64.cpp
  Platform.cpp
  Util.cpp
  Assembl.cpp
  opcode_table.c
)

# AsmJit C++ headers
Set(ASMJIT_HEADERS
  ApiBegin.h
  ApiEnd.h
  AsmJit.h
  Assembler.h
  AssemblerX86X64.h
  Build.h
  CodeGenerator.h
  Compiler.h
  CompilerX86X64.h
  Config.h
  CpuInfo.h
  Defs.h
  DefsX86X64.h
  Logger.h
  MemoryManager.h
  MemoryMarker.h
  Operand.h
  OperandX86X64.h
  Platform.h
  Util.h
  Util_p.h
)

# Include AsmJit to be able to use #include <AsmJit/...>
Include_Directories(${ASMJIT_DIR})

# pthread library is needed for non-windows OSes.
If(NOT WIN32)
  Link_Libraries(pthread)
EndIf()

# Build-Type.
#If(${CMAKE_BUILD_TYPE})
#  If(${CMAKE_BUILD_TYPE} MATCHES "Debug")
#    Add_Definitions(-DASMJIT_DEBUG)
#  Else()
#    Add_Definitions(-DASMJIT_NO_DEBUG)
#  EndIf()
#EndIf()

# Build AsmJit shared library?
#If(ASMJIT_BUILD_LIBRARY)
#  Add_Library(AsmJit SHARED ${ASMJIT_SOURCES} ${ASMJIT_HEADERS})
#  Install(TARGETS AsmJit DESTINATION lib${LIB_SUFFIX})

  # Install header files.
#  ForEach(i ${ASMJIT_HEADERS})
#    Get_Filename_Component(path ${i} PATH)
#    Install(FILES ${i} DESTINATION "include/${path}")
#  EndForEach(i)
#EndIf()

if (LIBRARY_TYPE_SHARED)
add_library(AsmJit SHARED ${ASMJIT_SOURCES})
endif ()

if (LIBRARY_TYPE_STATIC)
add_library(AsmJit_Static STATIC ${ASMJIT_SOURCES})
#set_target_properties(AsmJit_Static PROPERTIES OUTPUT_NAME "AsmJit")
endif ()

