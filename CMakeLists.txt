cmake_minimum_required(VERSION 3.5)

project(ChessOpenGL)

if(WIN32)
find_package(glfw3 REQUIRED PATHS "${CMAKE_SOURCE_DIR}/deps/GLFW/Windows/")
elseif(UNIX)
find_package(glfw3 REQUIRED PATHS "${CMAKE_SOURCE_DIR}/deps/GLFW/Linux/")
endif()

option(DEBUG "Debug mode" ON)

if(DEBUG)
find_package(imgui PATHS "C:/Deps/ImGui/") 
endif()

find_package(glad REQUIRED PATHS "${CMAKE_SOURCE_DIR}deps/GLAD/")

add_executable(run ${CMAKE_SOURCE_DIR}/main.cpp)

target_link_libraries(run glfw glad)

if(DEBUG)

    add_custom_command(OUTPUT Debug...
    COMMAND "./run.exe"
    DEPENDS run)

add_custom_target(Debug ALL
    DEPENDS Debug...)

endif()