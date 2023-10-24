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
};

struct MethodCall {
    std::string name;
    Expressions *arguments;

    MethodCall(std::string& name, Expressions *arguments) : name(name), arguments(arguments) {}
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
struct VariableDefinition;
struct VariableDeclaration;

typedef std::variant<VariableDefinition*, VariableDeclaration*, IfStatement*, WhileStatement*, ReturnStatement*, Assignment*, Expression*> Statement;

struct ReturnStatement {
    Expression *expression;

    explicit ReturnStatement(Expression *expression) : expression(expression) {}
};

struct WhileStatement {
    Relation *relation;
    Statement *statement;

    WhileStatement(Relation *relation, Statement *statement) : relation(relation), statement(statement) {}
};

struct IfStatement {
    Relation *relation;
    Statement *statement;
    Statement *elseStatement;

    IfStatement(Relation *relation, Statement *statement, Statement *elseStatement) : relation(relation),
                                                                                      statement(statement),
                                                                                      elseStatement(elseStatement) {}
};

struct Assignment {
    std::string identifier;
    Expression *expression;

    Assignment(std::string& identifier, Expression *expression) : identifier(identifier), expression(expression) {}
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

struct Argument {
    std::string name;

    Type* type;

    Argument(std::string& name, Type* type) : name(name), type(type) {}
};

struct Arguments {
    std::vector<Argument *> args;

    Arguments *add(Argument *a) {
        args.push_back(a);
        return this;
    }

    Arguments() : args() {};

    explicit Arguments(Argument *arg) { args = {arg}; }
};

struct VariableDeclaration {
    std::string name;
    Expression *expression;

    VariableDeclaration(std::string& name, Expression *expression) : expression(expression), name(name) {}
};

struct VariableDefinition {
    std::string name;
    Type *type;

    VariableDefinition(std::string& name, Type *type) : type(type), name(name) {}
};

struct MethodDeclaration {
    std::string name;
    Arguments *arguments;
    Type* returnType;
    Statements *body;

    MethodDeclaration(std::string& name, Arguments *arguments, Type* returnType, Statements *body) : name(name), arguments(arguments), returnType(returnType), body(body) {}
};

struct ConstructorDeclaration {
    Arguments *arguments;
    Statements *body;

    ConstructorDeclaration(Arguments *arguments, Statements *body) : arguments(arguments), body(body) {}
};

typedef std::variant<VariableDefinition*, VariableDeclaration*, MethodDeclaration*, ConstructorDeclaration*> MemberDeclaration;

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
    std::string name;
    ClassBody *body;

    ClassDeclaration(std::string &name, ClassBody *body) : name(name), body(body) {
        std::cout << "new class " << name << '\n';
    };
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
