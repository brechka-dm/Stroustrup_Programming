cmake_minimum_required(VERSION 3.20)

project(Reverse)
include_directories("${PROJECT_SOURCE_DIR}/../2")
add_executable(reverse  
                        main.cpp
                        Reverse.cpp
                        Reverse.h
                        ${PROJECT_SOURCE_DIR}/../2/Print.cpp
                        ${PROJECT_SOURCE_DIR}/../2/Print.h)
target_compile_features(reverse PUBLIC cxx_std_20)