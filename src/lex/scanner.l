%{
#include "scanner.h"

int _lineNum = 0;
int _posInLine = 0;
%}
%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%%
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
    type->span.lineNum = _lineNum;
    type->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    type->span.posEnd = _posInLine;
    return type;
}

true|false {
    BooleanLit* token = new BooleanLit();
    token->code = tkBooleanLit;
    if (strcmp(yytext, "True"))
        token->value = true;
    else
        token->value = false;
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    return token;
}

[+-]?([0-9]{1,9}+)  {
    /* yytext is a string containing the matched text. */
    IntegerLit *token = new IntegerLit();
    token->code = tkIntegerLit;
    token->value = std::stol(yytext);
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    return token;
}

[+-]?([0-9]*[.])?[0-9]+ {
    RealLit* token = new RealLit();
    token->code = tkRealLit;
    token->value = std::stold(yytext);
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    return token;
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
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    return token;
}

[_a-zA-Z][_a-zA-Z0-9]{0,30} {
    Identifier* token = new Identifier();
    token->identifier = yytext;
    token->code = tkIdentifier;
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    return token;
}

^\/\/[^\n\r]+(?:[\n\r]|\*\))$ {
    /* ignore comments */
}

[\{\}\[\]\(\)]|:=|,|\.|:|[ |\t]+ { // Maybe forgot smt
    Delimiter* token = new Delimiter();
    token->code = tkDelimiter;
    token->del = yytext;
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    return token;
}

\n {
    Delimiter* token = new Delimiter();
    token->code = tkDelimiter;
    token->del = "\n";

    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;

    _lineNum++;
    _posInLine = 0;
    return token;
}

. {}

<<EOF>> {
    return nullptr;
}

%%