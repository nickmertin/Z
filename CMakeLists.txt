cmake_minimum_required(VERSION 3.3)
project(Z)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(zasm assembler.cpp util.cpp instruction_set.cpp)
add_executable(zjit jit_rt.cpp util.cpp instruction_set.cpp)
add_executable(zvm vm_rt.cpp instruction_set.cpp)