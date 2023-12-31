cmake_minimum_required(VERSION 3.20)

project(Calculator3)

add_executable(Calculator  
                        Calculator.cpp
                        Calculator.h
                        Error.h
                        Grammar.cpp
                        Grammar.h
                        main.cpp
                        Token.cpp
                        Token.h
                        TokenKinds.h
                        TokenStream.cpp
                        TokenStream.h)
target_compile_features(Calculator PUBLIC cxx_std_20)