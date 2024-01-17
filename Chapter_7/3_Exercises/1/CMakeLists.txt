cmake_minimum_required(VERSION 3.20)

project(Calculator3)

add_executable(Calculator  
                        Calculator.cpp
                        Calculator.h
                        Error.h
                        main.cpp
                        Token.h
                        TokenKind.cpp
                        TokenKind.h
                        TokenStream.cpp
                        TokenStream.h
                        Variable.cpp
                        Variable.h)
target_compile_features(Calculator PUBLIC cxx_std_20)