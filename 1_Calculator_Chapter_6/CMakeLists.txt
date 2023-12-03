cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(CmakeTest)

add_executable(CmakeTest main.cpp)
target_compile_features(CmakeTest PUBLIC cxx_std_20)