cmake_minimum_required(VERSION 3.5)

project(ChessOpenGL)

if(WIN32)
find_package(glfw3 REQUIRED PATHS "${CMAKE_SOURCE_DIR}/dependencies/GLFW/Windows/")
elseif(UNIX)
find_package(glfw3 REQUIRED PATHS "${CMAKE_SOURCE_DIR}/dependencies/GLFW/Linux/")
endif()

message(${CMAKE_SOURCE_DIR})
option(DEBUG "Debug mode" ON)

if(DEBUG)
find_package(imgui PATHS "C:/Deps/ImGui/") 
endif()

if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/dependencies/glm)
    find_package(glm PATHS ${CMAKE_SOURCE_DIR}/dependencies/glm)
else()
    message("\n==================================================================================================")
    message(SEND_ERROR "Did you forget to git clone --recurse-submodules https://github.com/hxajk/ChessOpenGL ?")
    message("==================================================================================================")
endif()

find_package(glad REQUIRED PATHS "${CMAKE_SOURCE_DIR}/dependencies/GLAD/")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

set(SOURCES 
${CMAKE_SOURCE_DIR}/main.cpp
${CMAKE_SOURCE_DIR}/Chess/gfx/vao.c
${CMAKE_SOURCE_DIR}/Chess/gfx/vbo.c
${CMAKE_SOURCE_DIR}/Chess/gfx/shader.c
)

add_executable(run ${SOURCES})

target_link_libraries(run glfw glad glm::glm)

if(DEBUG)

#[[     add_custom_command(OUTPUT Debug...
    COMMAND "./run.exe"
    DEPENDS run)

add_custom_target(Debug ALL
    DEPENDS Debug...) ]]

endif()