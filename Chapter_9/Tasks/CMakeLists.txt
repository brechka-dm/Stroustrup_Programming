cmake_minimum_required(VERSION 3.20)

project(date)
add_executable(date Chrono.cpp
                    Chrono.h
                    DateV1.cpp
                    DateV1.h
                    DateV2.cpp
                    DateV2.h
                    main.cpp)
target_compile_features(date PUBLIC cxx_std_20)