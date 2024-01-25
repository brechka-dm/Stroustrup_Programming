cmake_minimum_required(VERSION 3.20)

project(User_names)
add_executable(user_names main.cpp)
target_compile_features(user_names PUBLIC cxx_std_20)