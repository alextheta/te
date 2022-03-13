cmake_minimum_required(VERSION 3.16)

project(te_editor)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin/${CMAKE_BUILD_TYPE})

# Boost
set(BOOST_ROOT C:/boost/boost_1_78_0)
find_package(Boost 1.78.0 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# glm
include_directories(../engine/dependencies/glm)

# ImGui
include_directories(dependencies/imgui)
file(GLOB LIB_IMGUI dependencies/imgui/*.cpp dependencies/imgui/backends/imgui_impl_opengl3.cpp dependencies/imgui/backends/imgui_impl_win32.cpp)
add_library(imgui ${LIB_IMGUI})

# TE editor_api
include_directories(../editor_api/include)

# TE engine
include_directories(../engine/include)

# TE editor app
include_directories(include)
file(GLOB_RECURSE APP_EDITOR source/*.cpp)

# App
add_executable(${PROJECT_NAME} ${APP_EDITOR})
target_link_libraries(${PROJECT_NAME} PUBLIC te_engine imgui)