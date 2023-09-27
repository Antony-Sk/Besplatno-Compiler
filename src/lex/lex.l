/*** Definition section ***/

%{
/* C code to be copied verbatim */
#include "lex.l.h"

LexicalAnalyzer *_laptr;

%}
%option noyywrap

%%
    /*** Rules section ***/

    /* [0-9]+ matches a string of one or more digits */
[0-9]{1,9}+  {
    /* yytext is a string containing the matched text. */
    IntegerLit *token = new IntegerLit();
    token->code = tkIntegerLit;
    token->value = std::stol(yytext); // TODO Big numbers
    _laptr->addToken(token);
    printf("Saw an integer: %s\n", yytext);
}

Integer|Boolean|Real|Array {
    Type *type = new Type();
    type->type = yytext;
//    switch yytext {
//        case "Integer":
//            type->code = tkInteger;
//            break;
//        case "Boolean":
//            type->code = tkBoolean;
//            break;
//        case "Real":
//            type->code = tkReal;
//            break;
//        case "Array":
//            type->code = tkArray;
//            break;
//    }
    if (strcmp(yytext, "Integer"))
        type->code = tkInteger;
    else if (strcmp(yytext, "Boolean"))
        type->code = tkBoolean;
    else if (strcmp(yytext, "Real"))
        type->code = tkReal;
    else if (strcmp(yytext, "Array"))
        type->code = tkArray;

    _laptr->addToken(type);
    printf("Saw an identifier: %s\n", yytext);
}

True|False {
    BooleanLit* token = new BooleanLit();
    token->code = tkBooleanLit;
    if (strcmp(yytext, "True"))
        token->value = true;
    else
        token->value = false;
     _laptr->addToken(token);
    printf("Saw an boolean: %s\n", yytext);
}

[+-]?([0-9]*[.])?[0-9]+ {
    RealLit* token = new RealLit();
    token->code = tkRealLit;
    token->value = std::stold(yytext);
    _laptr->addToken(token);
    printf("Saw an real: %s\n", yytext);
}

.|\n    {   /* Ignore all other characters. */   }

%%
/*** C Code section ***/

void lexAnalyzerProcess(LexicalAnalyzer* la)
{
    _laptr = la;
    /* Call the lexer, then quit. */
    yylex();
}