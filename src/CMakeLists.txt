#Prerequirements
cmake_minimum_required(VERSION 3.0.2)
project(color-shootout)
find_package(SDL2 REQUIRED)

# Build
set(source "")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
aux_source_directory(${CMAKE_SOURCE_DIR} source)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(color-shootout ${source})
#target_link_libraries(color-shootout ${SDL2_LIBRARIES}) includes the -mwindows flag
target_link_libraries(color-shootout -lmingw32 -lSDL2main -lSDL2)
