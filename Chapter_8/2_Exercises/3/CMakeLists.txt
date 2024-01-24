cmake_minimum_required(VERSION 3.20)

project(Fibonacchi)

include_directories("${PROJECT_SOURCE_DIR}/../2")

add_executable(fibonacchi  
                        Fibonacci.cpp
                        Fibonacci.h
                        main.cpp
                        ${PROJECT_SOURCE_DIR}/../2/Print.cpp
                        ${PROJECT_SOURCE_DIR}/../2/Print.h)
target_compile_features(fibonacchi PUBLIC cxx_std_20)