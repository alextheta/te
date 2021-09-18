cmake_minimum_required(VERSION 3.16)
project(te_editor)

set(CMAKE_CXX_STANDARD 20)

# ImGui
include_directories(dependencies/imgui)
file(GLOB LIB_IMGUI dependencies/imgui/*.cpp dependencies/imgui/backends/imgui_impl_opengl3.cpp dependencies/imgui/backends/imgui_impl_win32.cpp)
add_library(imgui STATIC ${LIB_IMGUI})

# TE engine
include_directories(../engine/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin/${CMAKE_BUILD_TYPE})
find_library(te_engine .)

# TE editor
include_directories(include)
file(GLOB_RECURSE APP_EDITOR source/*.cpp)

# App
add_executable(${PROJECT_NAME} ${APP_EDITOR})
target_link_libraries(${PROJECT_NAME} PUBLIC te_engine imgui)