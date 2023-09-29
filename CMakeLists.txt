cmake_minimum_required(VERSION 3.24)
project(Besplatno_Compiler)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/lex/scanner.cpp
        COMMAND flex -o ${CMAKE_CURRENT_SOURCE_DIR}/src/lex/scanner.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/lex/scanner.l
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/lex/scanner.l
)

set(CMAKE_CXX_STANDARD 20)

add_executable(Besplatno_Compiler main.cpp
        src/lex/token.h
        src/lex/lexicalAnalyzer.h
        src/lex/scanner.cpp
)
include_directories(src/lex)
