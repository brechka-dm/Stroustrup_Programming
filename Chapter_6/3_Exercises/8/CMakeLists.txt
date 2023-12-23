cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(Ex8)

add_executable(Ex8  main.cpp)
target_compile_features(Ex8 PUBLIC cxx_std_20)