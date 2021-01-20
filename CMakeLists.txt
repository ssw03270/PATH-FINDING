cmake_minimum_required(VERSION 3.16)
project(PATH_FINDING)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_executable(PATH_FINDING Sources/main.cpp Sources/map.cpp Includes/map.hpp Sources/point.cpp Includes/point.hpp)