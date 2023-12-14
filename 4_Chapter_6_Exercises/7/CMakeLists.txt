cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(Ex7)

add_executable(Ex7 main.cpp)
target_compile_features(Ex7 PUBLIC cxx_std_20)