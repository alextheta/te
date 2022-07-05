cmake_minimum_required(VERSION 3.16)

project(te_app)

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

# TE engine
include_directories(../engine/include)

# TE app
include_directories(include)
file(GLOB_RECURSE TE_APP source/*.cpp)

# App
add_executable(${PROJECT_NAME} ${TE_APP})
target_link_libraries(${PROJECT_NAME} PUBLIC te_engine)