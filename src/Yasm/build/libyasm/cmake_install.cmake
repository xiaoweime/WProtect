# Install script for directory: /home/lovewei/Project/yasm/new yasm/yasm/libyasm

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libyasm.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libyasm.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libyasm.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/lovewei/Project/yasm/new yasm/yasm/build/libyasm.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libyasm.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libyasm.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libyasm.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libyasm" TYPE FILE FILES
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/arch.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/assocdat.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/bitvect.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/bytecode.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/compat-queue.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/coretype.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/dbgfmt.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/errwarn.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/expr.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/file.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/floatnum.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/hamt.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/insn.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/intnum.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/inttree.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/linemap.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/listfmt.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/md5.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/module.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/objfmt.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/parser.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/phash.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/preproc.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/section.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/symrec.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/valparam.h"
    "/home/lovewei/Project/yasm/new yasm/yasm/libyasm/value.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

