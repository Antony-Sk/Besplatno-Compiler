//
// Created by anton on 17.10.23.
//

#ifndef BESPLATNO_COMPILER_PARSER_H
#define BESPLATNO_COMPILER_PARSER_H

int yylex();

void yyerror(char *);

int yyparse();

#endif // BESPLATNO_COMPILER_PARSER_H
