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
    Types* generics;

    Type(const std::string &base, Types *generics) : base(base), generics(generics) {}
    bool operator==(const Type &other) const;
    std::string toString();
};

struct Types {
    std::vector<Type*> types;
    Types() : types() {};
    explicit Types(Type* type) : types({type}) {};
    Types* add(Type* type) {
        types.push_back(type);
        return this;
    }
    bool operator==(const Types &other) const;

    std::string toString();
};

typedef std::variant<IntegerLit*, BooleanLit*, RealLit*, std::string, MethodCall*, CompoundExpression*, Keyword*> Expression;

struct Expressions {
    std::vector<Expression *> exps;

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
    Type* name;
    Expressions *arguments;

    MethodCall(Type* type, Expressions *arguments) : name(type), arguments(arguments) {}
};


typedef Expression Relation;

struct CompoundExpression {
    Expression *expression;
    MethodCall *methodCall;

    CompoundExpression(Expression *expression, MethodCall *methodCall) : expression(expression),
                                                                         methodCall(methodCall) {}
};

struct IfStatement;
struct WhileStatement;
struct ReturnStatement;
struct Assignment;
struct Variable;

typedef std::variant<Variable*, IfStatement*, WhileStatement*, ReturnStatement*, Assignment*, Expression*> Statement;

struct ReturnStatement {
    Expression *expression;

    explicit ReturnStatement(Expression *expression) : expression(expression) {}
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

    WhileStatement(Relation *relation, Statements *statement) : relation(relation), statement(statement) {}
};

struct IfStatement {
    Relation *relation;
    Statements *statements;
    Statements *elseStatements;

    IfStatement(Relation *relation, Statements *statement, Statements *elseStatement) : relation(relation),
                                                                                        statements(statement),
                                                                                        elseStatements(elseStatement) {}
};

struct Assignment {
    std::string identifier;
    Expression *expression;

    Assignment(std::string& identifier, Expression *expression) : identifier(identifier), expression(expression) {}
};

struct Argument {
    std::string name;

    Type* type;

    Argument(std::string& name, Type* type) : name(name), type(type) {}

    bool operator==(const Argument&arg) const {
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

    bool operator==(const Arguments& other) const {
        if (args.size() != other.args.size())
            return false;
        for (int i = 0; i < args.size(); i++) {
            if (*args[i] != *other.args[i])
                return false;
        }
        return true;
    }

    [[nodiscard]] std::string extractTypesAsString() const {
        std::string res;
        for (const auto arg: args) {
            res += arg->type->toString() + '&';
        }
        return res;
    }
};

struct Variable {
    std::string name;
    Expression *expression;

    Variable(std::string& name, Expression *expression) : expression(expression), name(name) {}
};

struct Method {
    std::string name;
    Arguments *arguments;
    Type* returnType;
    Statements *body;

    Method(std::string& name, Arguments *arguments, Type* returnType, Statements *body) : name(name), arguments(arguments), returnType(returnType), body(body) {}
};

struct Constructor {
    Arguments *arguments;
    Statements *body;

    Constructor(Arguments *arguments, Statements *body) : arguments(arguments), body(body) {}
};

typedef std::variant<Variable*, Method*, Constructor*> MemberDeclaration;

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
    Type* type;
    ClassBody *body;
    Type* extends;

    ClassDeclaration(Type *type, ClassBody *body, Type* extends) : type(type), body(body), extends(extends) { };
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
