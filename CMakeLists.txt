cmake_minimum_required(VERSION 3.12)
project(new_matrices)

set(CMAKE_CXX_STANDARD 14)

add_executable(new_matrices pvl_main.cpp matrix.cpp matrix.h)