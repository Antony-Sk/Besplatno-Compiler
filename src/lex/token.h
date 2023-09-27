//
// Created by anton on 26.09.23.
//

#ifndef BESPLATNO_COMPILER_TOKEN_H
#define BESPLATNO_COMPILER_TOKEN_H

#include <string>

enum TokenCode {
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
    tkSpace,
    tkNewline,
    // TODO { } \t \n space :  ( ) := , . EOF

    // other
    tkComment, // '//'
};

struct Token {
    struct Span {// Todo: have no idea how to get this
        long lineNum;
        int posBegin, posEnd;
    } span;

    unsigned int code;
};

struct Identifier : Token {
// Attributes specific for identifiers
    std::string identifier;
};

struct IntegerLit : Token {
// Attributes specific for integer constants
    long value;
};

struct RealLit : Token {
// Attributes specific for real constants
    long double value;
};

struct BooleanLit : Token {
// Attributes specific for real constants
    bool value;
};

struct Type : Token {
    std::string type;
};

struct Keyword : Token {
    std::string keyword;
};

struct ReservedWord : Token {
};

#endif //BESPLATNO_COMPILER_TOKEN_H
