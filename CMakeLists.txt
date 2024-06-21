cmake_minimum_required(VERSION 3.5)

project(ChessOpenGL)

if(WIN32)
find_package(glfw3 REQUIRED PATHS "{CMAKE_SOURCE_DIR}/deps/GLFW/Windows/")
elseif(UNIX)
find_package(glfw3 REQUIRED PATHS "{CMAKE_SOURCE_DIR}/Deps/GLFW/Linux/")
endif()

add_executable(ChessOpenGL ${CMAKE_SOURCE_DIR}/main.cpp)

target_link_libraries(ChessOpenGL glfw)
