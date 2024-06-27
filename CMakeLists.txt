cmake_minimum_required(VERSION 3.5)

project(ChessOpenGL)

if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/dependencies/cglm OR IS_DIRECTORY ${CMAKE_SOURCE_DIR}/dependencies/glfw)

else()
    message("\n==================================================================================================")
    message(SEND_ERROR "Did you forget to git clone --recurse-submodules https://github.com/hxajk/ChessOpenGL ?")
    message("==================================================================================================")
endif()

if(WIN32)
    find_package(glfw3 REQUIRED PATHS "${CMAKE_SOURCE_DIR}/dependencies/glfw/Windows/")
elseif(UNIX)
    find_package(glfw3 REQUIRED PATHS "${CMAKE_SOURCE_DIR}/dependencies/glfw/Linux/")
endif()

find_package(cglm PATHS "${CMAKE_SOURCE_DIR}/dependencies/cglm")

find_package(glad REQUIRED PATHS "${CMAKE_SOURCE_DIR}/dependencies/GLAD/")

message(${CMAKE_SOURCE_DIR})
option(DEBUG "Debug mode" OFF)

if(DEBUG)
    find_package(imgui PATHS "C:/Deps/ImGui/")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/ 
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb_image
)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/main.cpp

    # gfx folder
    ${CMAKE_SOURCE_DIR}/Chess/gfx/vao.c
    ${CMAKE_SOURCE_DIR}/Chess/gfx/vbo.c
    ${CMAKE_SOURCE_DIR}/Chess/gfx/shader.c
    ${CMAKE_SOURCE_DIR}/Chess/gfx/texture.c
    ${CMAKE_SOURCE_DIR}/Chess/gfx/window.c

    # core folder
    ${CMAKE_SOURCE_DIR}/Chess/core/board.c
)

add_executable(run ${SOURCES})

target_link_libraries(run glfw glad cglm::cglm)

if(DEBUG)
    #[[     add_custom_command(OUTPUT Debug...
    COMMAND "./run.exe"
    DEPENDS run)

add_custom_target(Debug ALL
    DEPENDS Debug...) ]]
endif()