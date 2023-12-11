cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(Ex4)

add_executable(Ex4 main.cpp)
target_compile_features(Ex4 PUBLIC cxx_std_20)