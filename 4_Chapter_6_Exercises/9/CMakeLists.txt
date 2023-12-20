cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(Ex9)

add_executable(Ex9  main.cpp)
target_compile_features(Ex9 PUBLIC cxx_std_20)