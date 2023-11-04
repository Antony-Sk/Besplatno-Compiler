//
// Created by anton on 22.10.23.
//

#include "scanner.h"
#include "parser.tab.h"

std::string Scanner::getStrval() {
    return this->yytext;
}

void Identifier::setYylval(YYSTYPE &yylval) {
    yylval.identifier = this;
}

void IntegerLit::setYylval(YYSTYPE &yylval) {
    yylval.integerLit = this;
}

void RealLit::setYylval(YYSTYPE &yylval) {
    yylval.realLit = this;
}

void BooleanLit::setYylval(YYSTYPE &yylval) {
    yylval.booleanLit = this;
}

void Keyword::setYylval(YYSTYPE &yylval) {
    yylval.keyword = this;
}






