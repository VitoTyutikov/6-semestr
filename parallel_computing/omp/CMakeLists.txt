cmake_minimum_required(VERSION 3.24)
project(omp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

#test
#add_executable(omp src/test.cpp)
#1
#add_executable(omp src/hello_world_with_8_threads.cpp)

#2
#add_executable(omp src/parallel_if.cpp)

#3
#add_executable(omp src/private_firstprivate.cpp)

#4
#add_executable(omp src/max_min_in_array.cpp)

#5
#add_executable(omp src/sections.cpp)

#6
#add_executable(omp src/reduction.cpp)

#7
#add_executable(omp src/schedule.cpp)

#8
#add_executable(omp src/time_schedule.cpp)

#9
add_executable(omp src/matrix_mult_vector.cpp)