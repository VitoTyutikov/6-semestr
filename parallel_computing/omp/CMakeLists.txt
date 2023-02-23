cmake_minimum_required(VERSION 3.24)
project(omp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

#test
#add_executable(omp src/test.cpp)
#1
#add_executable(omp src/hello_world_with_8_threads.cpp)
#2
add_executable(omp src/parallel_if.cpp)