//
// Created by anton on 26.09.23.
//

#ifndef BESPLATNO_COMPILER_TOKEN_H
#define BESPLATNO_COMPILER_TOKEN_H

#include <string>

enum TokenCode {
    tkIdentifier,
    // types
    tkInteger,
    tkBoolean,
    tkReal,
    tkArray,
    // literals
    tkIntegerLit,
    tkBooleanLit,
    tkRealLit,
    // keywords
    tkVar,
    tkMethod,
    tkIs,
    tkEnd,
    tkThis,
    tkClass,
    tkExtends,
    tkReturn,
    tkWhile,
    tkIf,
    tkLoop,
    tkThen,
    // delimiters
    tkDelimiter,
};

struct Token {
    struct Span {// Todo: have no idea how to get this
        long lineNum;
        int posBegin, posEnd;
    } span;
    unsigned int code;
};

struct Identifier : Token {
    std::string identifier;
};

struct IntegerLit : Token {
    long value;
};

struct RealLit : Token {
    long double value;
};

struct BooleanLit : Token {
    bool value;
};

struct Type : Token {
    std::string type;
};

struct Keyword : Token {
    std::string keyword;
};

struct Delimiter : Token {
    std::string del;
};

static std::string GetStrOfToken(Token *t) {
    switch (t->code) {
        case tkIntegerLit:
            return "Integer Literal: " + std::to_string(reinterpret_cast<IntegerLit*>(t)->value);
        case tkBooleanLit:
            return "Boolean Literal: " + std::to_string(reinterpret_cast<BooleanLit*>(t)->value);
        case tkRealLit:
            return "Real Literal: " + std::to_string(reinterpret_cast<RealLit*>(t)->value);
        case tkIdentifier:
            return "Identifier: " + reinterpret_cast<Identifier*>(t)->identifier;
        case tkInteger:
            return "Integer";
        case tkBoolean:
            return "Boolean";
        case tkReal:
            return "Real";
        case tkArray:
            return "Array";
        case tkVar:
            return "Variable Declaration";
        case tkMethod:
            return "Method Declaration";
        case tkIs:
            return "Assignment";
        case tkEnd:
            return "End";
        case tkThis:
            return "This";
        case tkClass:
            return "Class";
        case tkExtends:
            return "Extends";
        case tkReturn:
            return "Return";
        case tkWhile:
            return "While";
        case tkIf:
            return "If";
        case tkLoop:
            return "Loop";
        case tkThen:
            return "Then";
        case tkDelimiter:
            return "Delimiter: '" + reinterpret_cast<Delimiter*>(t)->del + "'";
        default:
            return "Unknown";
    }
}

#endif //BESPLATNO_COMPILER_TOKEN_H
