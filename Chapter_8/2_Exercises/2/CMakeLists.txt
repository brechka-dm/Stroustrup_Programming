cmake_minimum_required(VERSION 3.20)

project(print)

add_executable(print_test  
                        main.cpp
                        Print.cpp
                        Print.h)
target_compile_features(print_test PUBLIC cxx_std_20)