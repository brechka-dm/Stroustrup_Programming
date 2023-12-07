cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(Calculator)

add_executable(Calculator main.cpp)
target_compile_features(Calculator PUBLIC cxx_std_20)