cmake_minimum_required(VERSION 3.24)
project(Besplatno_Compiler)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
#separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/lex/scanner.cpp
        COMMAND flex -o ${CMAKE_CURRENT_SOURCE_DIR}/src/lex/scanner.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/lex/scanner.l
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/lex/scanner.l
)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/syntax/parser.cpp
        COMMAND bison -o ${CMAKE_CURRENT_SOURCE_DIR}/src/syntax/parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/syntax/parser.y
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/syntax/parser.y
)

set(CMAKE_CXX_STANDARD 20)

add_executable(Besplatno_Compiler main.cpp
        src/lex/scanner.cpp
        src/syntax/parser.cpp
        src/lex/lex.cpp
        src/semantic/semAnalyzer.cpp
        src/syntax/ast.cpp
        src/codegen/standardLibrary.cpp
        src/codegen/codegen.cpp
)
include_directories(src/lex)
include_directories(src/syntax)
include_directories(src/semantic)
include_directories(src/codegen)

target_link_libraries(Besplatno_Compiler -lLLVM-16)