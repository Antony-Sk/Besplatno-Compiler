%{
#include "scanner.h"
#include "parser.tab.h"
int _lineNum = 0;
int _posInLine = 0;
%}
%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%%
true|false {
    BooleanLit* token = new BooleanLit();
    token->code = BOOLLITERAL;
    if (strcmp(yytext, "True"))
        token->value = true;
    else
        token->value = false;
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    token->setYylval(yylval);
    return token;
}

[+-]?([0-9]{1,9}+)  {
    /* yytext is a string containing the matched text. */
    IntegerLit *token = new IntegerLit();
    token->code = INTEGERLITERAL;
    token->value = std::stol(yytext);
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    token->setYylval(yylval);
    return token;
}

[+-]?([0-9]*[.])?[0-9]+ {
    RealLit* token = new RealLit();
    token->code = REALLITERAL;
    token->value = std::stold(yytext);
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    token->setYylval(yylval);
    return token;
}

var|method|is|end|this|class|extends|return|while|if|loop|then|else {
    Keyword* token = new Keyword();
    if (strcmp(yytext, "var") == 0) {
        token->code = VAR;
    } else if (strcmp(yytext, "method") == 0) {
        token->code = METHOD;
    } else if (strcmp(yytext, "is") == 0) {
        token->code = IS;
    } else if (strcmp(yytext, "end") == 0) {
        token->code = END;
    } else if (strcmp(yytext, "this") == 0) {
        token->code = THIS;
    } else if (strcmp(yytext, "class") == 0) {
        token->code = CLASS;
    } else if (strcmp(yytext, "extends") == 0) {
        token->code = EXTENDS;
    } else if (strcmp(yytext, "return") == 0) {
        token->code = RETURN;
    } else if (strcmp(yytext, "while") == 0) {
        token->code = WHILE;
    } else if (strcmp(yytext, "if") == 0) {
        token->code = IF;
    } else if (strcmp(yytext, "loop") == 0) {
        token->code = LOOP;
    } else if (strcmp(yytext, "then") == 0) {
        token->code = THEN;
    } else if (strcmp(yytext, "else") == 0) {
        token->code = ELSE;
    }
    token->keyword = yytext;
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    token->setYylval(yylval);
    return token;
}

[_a-zA-Z][_a-zA-Z0-9]{0,30} {
    Identifier* token = new Identifier();
    token->identifier = std::string(yytext);
    token->code = IDENTIFIER;
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    token->setYylval(yylval);
    return token;
}

\/\/[^\n\r]+?(?:\*\)|[\n\r]) {
    /* ignore comments */
}

\{|\}|\[|\]|\(|\)|:=|,|\.|: { // Maybe forgot smt
    Delimiter* token = new Delimiter();
    if (strcmp(yytext, "{") == 0) {
        token->code = LBRACE;
    } else if (strcmp(yytext, "}") == 0) {
        token->code = RBRACE;
    } else if (strcmp(yytext, "(") == 0) {
        token->code = LPAREN;
    } else if (strcmp(yytext, ")") == 0) {
        token->code = RPAREN;
    } else if (strcmp(yytext, "[") == 0) {
        token->code = LBRACKET;
    } else if (strcmp(yytext, "]") == 0) {
        token->code = RBRACKET;
    } else if (strcmp(yytext, ",") == 0) {
        token->code = COMMA;
    } else if (strcmp(yytext, ".") == 0) {
        token->code = DOT;
    } else if (strcmp(yytext, ":") == 0) {
        token->code = COLON;
    } else if (strcmp(yytext, ":=") == 0) {
        token->code = ASSIGNMENTOPERATOR;
    }
    token->del = yytext;
    token->span.lineNum = _lineNum;
    token->span.posBegin = _posInLine;
    _posInLine += strlen(yytext);
    token->span.posEnd = _posInLine;
    return token;
}

[ |\t]+ { _posInLine += strlen(yytext); }

\n { _lineNum++; _posInLine = 0; }

. {}

<<EOF>> {
    Delimiter* token = new Delimiter();
    token->code = YYEMPTY;
    return token;
}

%%