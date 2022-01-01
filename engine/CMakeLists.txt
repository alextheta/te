cmake_minimum_required(VERSION 3.16)

project(te_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
add_definitions(-DUNICODE -D_UNICODE -DTE_IMPORT)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin/${CMAKE_BUILD_TYPE})

# Boost
set(BOOST_ROOT C:/boost/boost_1_78_0)
find_package(Boost 1.78.0 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# UUID_v4
include_directories(dependencies/uuid_v4)

# OpenGL
find_package(OpenGL REQUIRED)

# glm
include_directories(dependencies/glm)

# GL3W
include_directories(dependencies/GL3W/include)
file(GLOB_RECURSE LIB_GL3W dependencies/GL3W/src/*.c)
add_library(gl3w OBJECT ${LIB_GL3W})

# TE include
include_directories(include)

# TE render
file(GLOB_RECURSE SRC_CORE_RENDER source/Core/Render/*.cpp)
file(GLOB_RECURSE SRC_PLATFORM_RENDER source/Platform/Render/*.cpp)
add_library(render OBJECT ${SRC_CORE_RENDER} ${SRC_PLATFORM_RENDER})

# TE window
file(GLOB_RECURSE SRC_CORE_WINDOW source/Core/Window/*.cpp)
file(GLOB_RECURSE SRC_PLATFORM_WINDOW source/Platform/Window/*.cpp)
add_library(window OBJECT ${SRC_CORE_WINDOW} ${SRC_PLATFORM_WINDOW})

# TE event
file(GLOB_RECURSE SRC_CORE_EVENT source/Core/Event/*.cpp)
add_library(event OBJECT ${SRC_CORE_EVENT})

# TE engine
file(GLOB_RECURSE SRC_ENGINE source/Engine/*.cpp)
add_library(engine OBJECT ${SRC_ENGINE})

# TE core
file(GLOB SRC_CORE source/Core/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SRC_CORE})

# static lib
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL gl3w imgui window render event engine)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)