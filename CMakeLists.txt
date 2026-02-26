cmake_minimum_required(VERSION 3.20)
project(hw1_aid LANGUAGES CXX)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

add_executable(hw1_aid
    src/main.cpp
    src/core/Application.cpp
    src/core/Logger.cpp
    src/core/States.cpp
    src/game/InputController.cpp
    src/render/RaylibRenderAdapter.cpp
)

target_include_directories(hw1_aid PRIVATE src)
target_link_libraries(hw1_aid PRIVATE raylib)

if(MSVC)
    target_compile_options(hw1_aid PRIVATE /W4 /utf-8)
else()
    target_compile_options(hw1_aid PRIVATE -Wall -Wextra -Wpedantic)
endif()
