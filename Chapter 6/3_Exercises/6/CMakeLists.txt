cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(Ex6)

add_executable(Ex6 main.cpp)
target_compile_features(Ex6 PUBLIC cxx_std_20)