cmake_minimum_required(VERSION 3.24.0)
project(aoc_2022_06 VERSION 0.1.0)

# must be before add_executable() for compiler flags to be added.
set (CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} aoc_2022_06.cpp) 
