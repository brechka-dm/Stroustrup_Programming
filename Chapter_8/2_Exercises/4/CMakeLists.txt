cmake_minimum_required(VERSION 3.20)

project(int_test)

include_directories("${PROJECT_SOURCE_DIR}/../3")

add_executable(int_test  
                        main.cpp
                        ${PROJECT_SOURCE_DIR}/../3/Fibonacci.cpp
                        ${PROJECT_SOURCE_DIR}/../3/Fibonacci.h)
target_compile_features(int_test PUBLIC cxx_std_20)