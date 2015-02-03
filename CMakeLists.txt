cmake_minimum_required(VERSION 2.8.4)
project(voronoy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(voronoy ${SOURCE_FILES})
target_link_libraries(voronoy SDL2)