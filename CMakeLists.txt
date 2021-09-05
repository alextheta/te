cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME te)

project(${PROJECT_NAME})

find_package(OpenGL REQUIRED)

link_directories(dependencies/lib)
include_directories(dependencies/include)
file(GLOB_RECURSE SRC_DEPENDENCIES dependencies/src/*.c)
#file(GLOB_RECURSE SRC_DEPENDENCIES dependencies/src/*.cpp)

include_directories(include)

file(GLOB_RECURSE SRC_ENGINE source/Engine/*.cpp)
file(GLOB_RECURSE SRC_PLATFORM source/Platform/*.cpp)

add_library(dependencies ${SRC_DEPENDENCIES})
add_library(engine ${SRC_ENGINE})
add_library(platform ${SRC_PLATFORM})

add_definitions(-DUNICODE -D_UNICODE)

add_executable(${PROJECT_NAME} App.cpp)

target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} dependencies platform engine)