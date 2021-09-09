cmake_minimum_required(VERSION 3.16)
project(te_editor)

set(CMAKE_CXX_STANDARD 20)

include_directories(../engine/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin/${CMAKE_BUILD_TYPE})
find_library(te_engine .)

add_executable(${PROJECT_NAME} App.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC te_engine)