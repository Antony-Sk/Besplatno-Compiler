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

var|method|is|end|this|class|extends|return|while|if|loop|then {
    Keyword* token = new Keyword();
    if (strcmp(yytext, "var") == 0) {
        token->code = tkVar;
    } else if (strcmp(yytext, "method") == 0) {
        token->code = tkMethod;
    } else if (strcmp(yytext, "is") == 0) {
        token->code = tkIs;
    } else if (strcmp(yytext, "end") == 0) {
        token->code = tkEnd;
    } else if (strcmp(yytext, "this") == 0) {
        token->code = tkThis;
    } else if (strcmp(yytext, "class") == 0) {
        token->code = tkClass;
    } else if (strcmp(yytext, "extends") == 0) {
        token->code = tkExtends;
    } else if (strcmp(yytext, "return") == 0) {
        token->code = tkReturn;
    } else if (strcmp(yytext, "while") == 0) {
        token->code = tkWhile;
    } else if (strcmp(yytext, "if") == 0) {
        token->code = tkIf;
    } else if (strcmp(yytext, "loop") == 0) {
        token->code = tkLoop;
    } else if (strcmp(yytext, "then") == 0) {
        token->code = tkThen;
    }
    token->keyword = yytext;
    _laptr->addToken(token);
    printf("Saw a keyword: %s\n", yytext);
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