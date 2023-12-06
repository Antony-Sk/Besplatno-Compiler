//
// Created by anton on 18.10.23.
//

#ifndef BESPLATNO_COMPILER_AST_H
#define BESPLATNO_COMPILER_AST_H

#include <utility>
#include <vector>
#include <iostream>
#include <variant>
#include "token.h"

struct CompoundExpression;
struct MethodCall;
struct Types;

struct Type {
    std::string base;
    Types *generics;
    const Span span;

    Type(std::string base, Types *generics, const Span &span) : base(std::move(base)), generics(generics), span(span) {}

    bool operator==(const Type &other) const;

    std::string toString();
};

struct Types {
    std::vector<Type *> types;

    Types() : types() {};

    explicit Types(Type *type) : types({type}) {};

    Types *add(Type *type) {
        types.push_back(type);
        return this;
    }

    bool operator==(const Types &other) const;

    std::string toString();
};

typedef std::variant<IntegerLit *, BooleanLit *, RealLit *, std::pair<std::string, Span>, MethodCall *, CompoundExpression *, Keyword *> Expression;

struct Expressions {
    std::vector<Expression *> exps;
    std::vector<std::string> expsTypes;

    Expressions *add(Expression *exp) {
        exps.push_back(exp);
        return this;
    }

    explicit Expressions(Expression *exp) {
        exps = {exp};
    }

    Expressions() = default;
};

struct MethodCall {
    Type *name;
    Expressions *arguments;
    const Span span;
    std::string fullname;
    Type *returnType = nullptr;

    MethodCall(Type *type, Expressions *arguments, const Span &span) : name(type), arguments(arguments), span(span) {}
};


typedef Expression Relation;

struct CompoundExpression {
    Expression *expression;
    MethodCall *methodCall;
    std::string expType;

    CompoundExpression(Expression *expression, MethodCall *methodCall) : expression(expression),
                                                                         methodCall(methodCall) {}
};

struct IfStatement;
struct WhileStatement;
struct ReturnStatement;
struct Assignment;
struct Variable;

typedef std::variant<Variable *, IfStatement *, WhileStatement *, ReturnStatement *, Assignment *, Expression *, Keyword *> Statement;

struct ReturnStatement {
    Expression *expression;
    const Span span;

    explicit ReturnStatement(Expression *expression, const Span &span) : expression(expression), span(span) {}
};

struct Statements {
    std::vector<Statement *> stmts;

    Statements *add(Statement *st) {
        stmts.push_back(st);
        return this;
    }

    Statements() = default;

    explicit Statements(Statement *stmt) { stmts = {stmt}; }
};

struct WhileStatement {
    Relation *relation;
    Statements *statement;
    const Span span;

    WhileStatement(Relation *relation, Statements *statement, const Span &span)
            : relation(relation), statement(statement), span(span) {}
};

struct IfStatement {
    Relation *relation;
    Statements *statements;
    Statements *elseStatements;
    const Span span;

    IfStatement(Relation *relation, Statements *statement, Statements *elseStatement, const Span &span)
            : relation(relation),
              statements(statement),
              elseStatements(elseStatement), span(span) {}
};

struct Assignment {
    std::string identifier;
    Expression *expression;
    const Span span;

    Assignment(std::string identifier, Expression *expression, const Span span)
            : identifier(std::move(identifier)), expression(expression), span(span) {}
};

struct Argument {
    std::string name;

    Type *type;
    const Span span;

    Argument(std::string name, Type *type, const Span &span) : name(std::move(name)), type(type), span(span) {}

    bool operator==(const Argument &arg) const {
        return (name == arg.name) && (*type == *arg.type);
    }
};

struct Arguments {
    std::vector<Argument *> args;

    Arguments *add(Argument *a) {
        args.push_back(a);
        return this;
    }

    Arguments() : args() {};

    explicit Arguments(Argument *arg) { args = {arg}; }

    bool operator==(const Arguments &other) const {
        if (args.size() != other.args.size())
            return false;
        for (int i = 0; i < args.size(); i++) {
            if (*args[i] == *other.args[i])
                return false;
        }
        return true;
    }

    [[nodiscard]] std::string extractTypesAsString() const {
        std::string res;
        for (const auto arg: args) {
            res += arg->type->toString() + '_';
        }
        return res;
    }
};

struct Variable {
    std::string name;
    Expression *expression;
    Span span;

    Variable(std::string &name, Expression *expression, Span span) : expression(expression), name(name),
                                                                     span(span) {}
};

struct Method {
    std::string name;
    Arguments *arguments;
    Type *returnType;
    Statements *body;
    const Span span;
    std::string fullName;
    bool isConstructor;

    Method(std::string name, Arguments *arguments, Type *returnType, Statements *body, const Span &span,
           bool isConstructor = false) : name(
            std::move(name)), arguments(arguments), returnType(returnType), body(body), span(span),
                                         isConstructor(isConstructor) {}
};

struct Constructor {
    Arguments *arguments;
    Statements *body;
    const Span span;

    Constructor(Arguments *arguments, Statements *body, const Span &span)
            : arguments(arguments), body(body), span(span) {}
};

typedef std::variant<Variable *, Method *, Constructor *> MemberDeclaration;

struct MemberDeclarations {
    std::vector<MemberDeclaration *> decls;

    MemberDeclarations *add(MemberDeclaration *cd) {
        decls.push_back(cd);
        return this;
    }

    explicit MemberDeclarations(MemberDeclaration *decl) { decls = {decl}; }
};

struct ClassBody {
    MemberDeclarations *members;

    explicit ClassBody(MemberDeclarations *m) : members(m) {};
};

struct ClassDeclaration {
    Type *type;
    ClassBody *body;
    Type *extends;

    ClassDeclaration(Type *type, ClassBody *body, Type *extends)
            : type(type), body(body), extends(extends) {};
};

struct ClassDeclarations {
    std::vector<ClassDeclaration *> decls;

    ClassDeclarations *add(ClassDeclaration *cd) {
        decls.push_back(cd);
        return this;
    }

    explicit ClassDeclarations(ClassDeclaration *cd) { decls = {cd}; }

    ClassDeclarations() = default;
};

struct Program {
    ClassDeclarations *classDecls;

    explicit Program(ClassDeclarations *cds) : classDecls(cds) {}

    Program() = default;
};

#endif //BESPLATNO_COMPILER_AST_H
