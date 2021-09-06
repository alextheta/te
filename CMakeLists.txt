cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME te)

project(${PROJECT_NAME})
add_definitions(-DUNICODE -D_UNICODE)

# OpenGL
find_package(OpenGL REQUIRED)

# GL3W
include_directories(dependencies/GL3W/include)
file(GLOB_RECURSE LIB_GL3W dependencies/GL3W/src/*.c)
add_library(gl3w ${LIB_GL3W})

# Engine
include_directories(include)

file(GLOB_RECURSE SRC_ENGINE_RESOURCE source/Engine/Resource/*.cpp)
file(GLOB_RECURSE SRC_ENGINE_RENDER source/Engine/Render/*.cpp)
file(GLOB_RECURSE SRC_ENGINE_WINDOW source/Engine/Window/*.cpp)

file(GLOB_RECURSE SRC_PLATFORM_RESOURCE source/Platform/Resource/*.cpp)
file(GLOB_RECURSE SRC_PLATFORM_RENDER source/Platform/Render/*.cpp)
file(GLOB_RECURSE SRC_PLATFORM_WINDOW source/Platform/Window/*.cpp)

file(GLOB SRC_ENGINE source/Engine/*.cpp)

add_library(resource ${SRC_ENGINE_RESOURCE} ${SRC_PLATFORM_RESOURCE})
add_library(render ${SRC_ENGINE_RENDER} ${SRC_PLATFORM_RENDER})
add_library(window ${SRC_ENGINE_WINDOW} ${SRC_PLATFORM_WINDOW})
add_library(engine ${SRC_ENGINE})

# Exec
add_executable(${PROJECT_NAME} App.cpp)

target_link_libraries(${PROJECT_NAME} OpenGL::GL gl3w)
target_link_libraries(${PROJECT_NAME} resource window render engine)