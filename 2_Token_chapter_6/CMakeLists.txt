cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(Grammar)

add_executable(Grammar main.cpp)
target_compile_features(Grammar PUBLIC cxx_std_20)