project(MineSweeperlike)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(SDL2_PATH CACHE STRING "Search path for SDL2")
set(SDL2_IMAGE_PATH CACHE STRING "Search path for SDL2")
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
add_subdirectory(src)
