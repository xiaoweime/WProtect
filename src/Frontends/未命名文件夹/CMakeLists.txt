#PROJECT(example)
#CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTMAIN TRUE)
INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})


if(MINGW)
set(CMAKE_RC_COMPILER_INIT windres)
ENABLE_LANGUAGE(RC)
SET(CMAKE_RC_COMPILE_OBJECT
"<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif(MINGW)

SET(example_SRCS main.cpp mainwindow.cpp ) # widget.cpp res/main.rc

SET (example_UIS mainwindow.ui)
QT4_WRAP_UI (example_UIS     ${example_UIS})

SET(example_MOC_SRCS mainwindow.h) # widget.h
QT4_WRAP_CPP(example_MOCS ${example_MOC_SRCS})

QT4_ADD_RESOURCES(example_RCC_SRCS ) #main.qrc
SET(example_SRCS ${example_SRCS} ${example_MOCS} ${example_RCC_SRCS} ${example_UIS})

ADD_EXECUTABLE(example WIN32 main.cpp mainwindow.cpp ${example_SRCS})
TARGET_LINK_LIBRARIES(example ${QT_LIBRARIES} ${LIBS})
