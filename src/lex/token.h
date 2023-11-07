//
// Created by anton on 26.09.23.
//

#ifndef BESPLATNO_COMPILER_TOKEN_H
#define BESPLATNO_COMPILER_TOKEN_H

#include <string>
#include <utility>

typedef union value YYSTYPE;

struct Span {
    long lineNum;
    int posBegin, posEnd;

    [[nodiscard]] std::string toString() const {
        return "line: " + std::to_string(lineNum + 1)
               + ", pos " + std::to_string(posBegin)
               + ":" + std::to_string(posEnd);
    }
};

struct Token {
    Span span;
    int code;

    virtual std::string toString() {
        return "Undefined token";
    }

    virtual void setYylval(YYSTYPE &yylval) = 0;
};

struct Identifier : Token {
    std::string identifier;

    std::string toString() override {
        return "Identifier token \'" + identifier + "\'";
    }

    void setYylval(YYSTYPE &) override;
};

struct IntegerLit : Token {
    long value;

    std::string toString() override {
        return "Integer literal token \'" + std::to_string(value) + "\'";
    }

    void setYylval(YYSTYPE &) override;
};

struct RealLit : Token {
    long double value;

    std::string toString() override {
        return "Real literal token \'" + std::to_string(value) + "\'";
    }

    void setYylval(YYSTYPE &) override;
};

struct BooleanLit : Token {
    bool value;

    std::string toString() override {
        return "Boolean literal token \'" + std::to_string(value) + "\'";
    }

    void setYylval(YYSTYPE &) override;
};

struct Keyword : Token {
    std::string keyword;

    std::string toString() override {
        return "Keyword token \'" + keyword + "\'";
    }

    void setYylval(YYSTYPE &) override;
};

struct Delimiter : Token {
    std::string del;

    std::string toString() override {
        return "Delimiter token \'" + del + "\'";
    }

    void setYylval(YYSTYPE &) override {};
};

#endif //BESPLATNO_COMPILER_TOKEN_H
