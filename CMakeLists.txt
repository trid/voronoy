cmake_minimum_required(VERSION 2.8.4)
project(voronoy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES *.cpp)

add_executable(voronoy ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(voronoy SDL2main.lib)
    target_link_libraries(voronoy SDL2.lib)
else()
    target_link_libraries(voronoy SDL2)
endif(WIN32)