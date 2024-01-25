cmake_minimum_required(VERSION 3.20)

project(Reverse)
add_executable(reverse  
                        main.cpp
                        Reverse.cpp
                        Reverse.h)
target_compile_features(reverse PUBLIC cxx_std_20)