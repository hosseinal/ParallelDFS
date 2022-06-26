cmake_minimum_required(VERSION 3.21)
project(parallel_recursive)

set(CMAKE_CXX_STANDARD 14)

add_executable(parallel_recursive main.cpp)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
