cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "clang++")

project(Ex7)

add_executable(Ex7  Error.h
                    LogicGrammarRecognizer.cpp LogicGrammarRecognizer.h
                    main.cpp
                    Token.h
                    TokenStream.cpp TokenStream.h
                    TokenType.h
                    TokenTypeFromChar.cpp TokenTypeFromChar.h
)
target_compile_features(Ex7 PUBLIC cxx_std_20)