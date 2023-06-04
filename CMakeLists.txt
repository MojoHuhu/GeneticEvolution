cmake_minimum_required(VERSION 3.14)
project(gen)

#With gcc, you need to compile and link with -fopenmp to enable OpenMP. Other compilers have different options; with intel it's -openmp, with pgi it's -mp, etc.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(${PROJECT_NAME} main.cpp )

                             