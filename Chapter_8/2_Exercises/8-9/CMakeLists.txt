cmake_minimum_required(VERSION 3.20)

project(randint)
add_executable(randint  main.cpp
                        rand.cpp
                        rand.h)
target_compile_features(randint PUBLIC cxx_std_20)