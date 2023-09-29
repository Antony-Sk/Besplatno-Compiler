//
// Created by anton on 26.09.23.
//

#ifndef BESPLATNO_COMPILER_LEXICALANALYZER_H
#define BESPLATNO_COMPILER_LEXICALANALYZER_H

#include <vector>
#include <iostream>
#include "token.h"

class LexicalAnalyzer {
public:
    Token getNext(); // Todo: implement

    void addToken(Token *token) {
        _tokens.push_back(token);
    }

    ~LexicalAnalyzer() {
        for (const Token *it: _tokens)
            delete it;
    }

private:
    std::vector<Token *> _tokens;
};

#endif //BESPLATNO_COMPILER_LEXICALANALYZER_H
