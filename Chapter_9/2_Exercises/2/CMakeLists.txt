cmake_minimum_required(VERSION 3.20)

project(name_pairs)
add_executable(name_pairs main.cpp
                    NamePairs.cpp
                    NamePairs.h)
target_compile_features(name_pairs PUBLIC cxx_std_20)