cmake_minimum_required(VERSION 3.20)

project(library)

include_directories("${PROJECT_SOURCE_DIR}/../../1_Tasks")

set(
    Date_sources
    ${PROJECT_SOURCE_DIR}/../../1_Tasks/Chrono.cpp
    ${PROJECT_SOURCE_DIR}/../../1_Tasks/Chrono.h
    ${PROJECT_SOURCE_DIR}/../../1_Tasks/DateV1.cpp
    ${PROJECT_SOURCE_DIR}/../../1_Tasks/DateV1.h
    ${PROJECT_SOURCE_DIR}/../../1_Tasks/DateV2.cpp
    ${PROJECT_SOURCE_DIR}/../../1_Tasks/DateV2.h
    ${PROJECT_SOURCE_DIR}/../../1_Tasks/Utils.h
)
source_group("..\\..\\1_Tasks" FILES ${Date_sources})

add_executable(library  Book.cpp
                        Book.h
                        main.cpp
                        Patron.cpp
                        Patron.h
                        ${Date_sources})
target_compile_features(library PUBLIC cxx_std_20)