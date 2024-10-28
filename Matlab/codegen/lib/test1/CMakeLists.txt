cmake_minimum_required(VERSION 3.30.2)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_BUILD_TYPE Debug)  # Define o modo de depuração
set(CMAKE_C_FLAGS_DEBUG "-g -O0")  # Flags para GCC no modo Debug

project(IC_2024 C)

add_executable(test1 test1.c)
target_link_libraries(test1 tmwtypes.h)