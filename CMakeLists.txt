cmake_minimum_required(VERSION 3.26)
project(Besplatno_Compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Besplatno_Compiler main.cpp
        src/lex/token.h
        src/lex/lexicalAnalyzer.h
        src/lex/lex.l.cpp
)
include_directories(src/lex)
