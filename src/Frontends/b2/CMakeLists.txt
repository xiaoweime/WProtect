cmake_minimum_required(VERSION 2.8.11)

project(WProtectGui)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Gui)                             
find_package(Qt5Core)

# Tell CMake to create the helloworld executable
add_executable(WProtectGui WIN32 main.cc )

# Use the Widgets module from Qt 5.
target_link_libraries(WProtectGui Qt5::Widgets Qt5::Gui)
