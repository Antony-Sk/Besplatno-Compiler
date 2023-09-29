#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL Token* Scanner::get_next_token()

class Scanner : public yyFlexLexer {
public:
    Token *get_next_token();
};

#endif