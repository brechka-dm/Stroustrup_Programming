cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(Ex10)

add_executable(Ex10  main.cpp)
target_compile_features(Ex10 PUBLIC cxx_std_20)