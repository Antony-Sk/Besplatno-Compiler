//
// Created by anton on 17.10.23.
//

#ifndef BESPLATNO_COMPILER_PARSER_H
#define BESPLATNO_COMPILER_PARSER_H

#include <fstream>
#include "ast.h"
#include "scanner.h"

int yyparse();

class Parser {
public:
    static Scanner scanner;
    static Program* program;

    Program* parse(const std::string &file) {
        std::ifstream fileStream(file);
        scanner.switch_streams(&fileStream);
        int t = yyparse();
        while (t) {
            t = yyparse();
        }
        return program;
    }
};

#endif // BESPLATNO_COMPILER_PARSER_H
