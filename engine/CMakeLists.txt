cmake_minimum_required(VERSION 3.16)

project(te_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
add_definitions(-DUNICODE -D_UNICODE -DTE_IMPORT)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin/${CMAKE_BUILD_TYPE})

# Include
include_directories(include)

# OpenGL
find_package(OpenGL REQUIRED)

# glm
include_directories(dependencies/glm)

# GL3W
include_directories(dependencies/GL3W/include)
file(GLOB_RECURSE LIB_GL3W dependencies/GL3W/src/*.c)
add_library(gl3w OBJECT ${LIB_GL3W})

# TE render
file(GLOB_RECURSE SRC_ENGINE_RENDER source/Engine/Render/*.cpp)
file(GLOB_RECURSE SRC_PLATFORM_RENDER source/Platform/Render/*.cpp)
add_library(render OBJECT ${SRC_ENGINE_RENDER} ${SRC_PLATFORM_RENDER})

# TE window
file(GLOB_RECURSE SRC_ENGINE_WINDOW source/Engine/Window/*.cpp)
file(GLOB_RECURSE SRC_PLATFORM_WINDOW source/Platform/Window/*.cpp)
add_library(window OBJECT ${SRC_ENGINE_WINDOW} ${SRC_PLATFORM_WINDOW})

# TE event
file(GLOB_RECURSE SRC_ENGINE_EVENT source/Engine/Event/*.cpp)
add_library(event OBJECT ${SRC_ENGINE_EVENT})

# TE engine
file(GLOB SRC_ENGINE source/Engine/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SRC_ENGINE})

# static lib
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL gl3w imgui window render event)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)