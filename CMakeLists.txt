cmake_minimum_required(VERSION 3.16)

project(HighwayRush VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(HighwayRush
    src/main.cpp
    src/Game.cpp
    src/Renderer.cpp
    src/Road.cpp
    src/Player.cpp
    src/TrafficCar.cpp
)

target_include_directories(HighwayRush PRIVATE include)
target_link_libraries(HighwayRush PRIVATE glfw OpenGL::GL)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(HighwayRush PRIVATE -Wall -Wextra -Wpedantic)
endif()

