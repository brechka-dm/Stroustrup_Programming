cmake_minimum_required(VERSION 3.20)

project(ch8_task1-2)

add_executable(task1-2  
                        my.cpp
                        my.h
                        use.cpp)
target_compile_features(task1-2 PUBLIC cxx_std_20)