cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(Ex5)

add_executable(Ex5 main.cpp)
target_compile_features(Ex5 PUBLIC cxx_std_20)