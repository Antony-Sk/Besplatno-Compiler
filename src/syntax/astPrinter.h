//
// Created by anton on 23.10.23.
//

#ifndef BESPLATNO_COMPILER_ASTPRINTER_H
#define BESPLATNO_COMPILER_ASTPRINTER_H

#include "ast.h"

void print(Types*);
void print(Type* t) {
    if (std::holds_alternative<std::string>(t->base)) {
        std::cout << std::get<std::string>(t->base);
    }
    if (std::holds_alternative<TypeToken*>(t->base)) {
        std::cout << std::get<TypeToken*>(t->base)->type;
    }
    if (t->generics == nullptr)
        return;
    print(t->generics);
}
void print(Types* t) {
    std::cout << "[";
    for (int i = 0; i < t->types.size() - 1; i++) {
        print(t->types[i]);
        std::cout << ", ";
    }
    if (!t->types.empty())
        print(t->types.back());
    std::cout << "]";
}
void print(Expression *e, int offset = 0);

void print(Statement *s, int offset = 0);

void print(Statements *sts, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Statements" << "\n";
    for (auto s: sts->stmts) {
        print(s, offset + 1);
    }
}
void print(IfStatement *is, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "IF" << "\n";
    print(is->relation, offset + 1);
    print(is->statement, offset + 1);
}

void print(WhileStatement *ws, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "WHILE" << "\n";
    print(ws->relation, offset + 1);
    print(ws->statement, offset + 1);
}

void print(ReturnStatement *rs, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "RETURN" << "\n";
    print(rs->expression, offset + 1);
}

void print(VariableDefinition *vd, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Var def : " << vd->name << " with type : ";
    print(vd->type);
    std::cout << "\n";
}

void print(VariableDeclaration *vd, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Var decl : " << vd->name << "\n";
    print(vd->expression, offset + 1);
}

void print(Statement *s, int offset) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Statement\n";
    if (std::holds_alternative<VariableDefinition *>(*s)) {
        print(std::get<VariableDefinition *>(*s), offset + 1);
    }
    if (std::holds_alternative<VariableDeclaration *>(*s)) {
        print(std::get<VariableDeclaration *>(*s), offset + 1);
    }
    if (std::holds_alternative<IfStatement *>(*s)) {
        print(std::get<IfStatement *>(*s), offset + 1);
    }
    if (std::holds_alternative<WhileStatement *>(*s)) {
        print(std::get<WhileStatement *>(*s), offset + 1);
    }
    if (std::holds_alternative<ReturnStatement *>(*s)) {
        print(std::get<ReturnStatement *>(*s), offset + 1);
    }
    if (std::holds_alternative<Expression *>(*s)) {
        print(std::get<Expression *>(*s), offset + 1);
    }
}

void print(Argument *arg, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Arg '" << arg->name << "' of type ";
    print(arg->type);
    std::cout << "\n";
}

void print(Arguments *args, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Args" << "\n";
    for (auto arg: args->args) {
        print(arg, offset + 1);
    }
}

void print(Expressions *es, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Expressions" << "\n";
    for (auto e: es->exps) {
        print(e, offset + 1);
    }
}

void print(MethodCall *mc, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Method '" << mc->name << "' call with args:\n";
    print(mc->arguments, offset + 1);
}
void print(ConstructorCall *mc, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Constructor of type '";
    print(mc->type);
    std::cout << "' call with args:\n";
    print(mc->arguments, offset + 1);
}

void print(CompoundExpression *ce, int offset = 0);

void print(Expression *e, int offset) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Expression with value : ";
    if (std::holds_alternative<IntegerLit *>(*e)) {
        std::cout << std::get<IntegerLit *>(*e)->value << "\n";
    }
    if (std::holds_alternative<RealLit *>(*e)) {
        std::cout << std::get<RealLit *>(*e)->value << "\n";
    }
    if (std::holds_alternative<BooleanLit *>(*e)) {
        std::cout << std::get<BooleanLit *>(*e)->value << "\n";
    }
    if (std::holds_alternative<std::string>(*e)) {
        std::cout << std::get<std::string>(*e) << "\n";
    }
    if (std::holds_alternative<MethodCall *>(*e)) {
        std::cout << "\n";
        print(std::get<MethodCall *>(*e), offset + 1);
    }
    if (std::holds_alternative<ConstructorCall *>(*e)) {
        std::cout << "\n";
        print(std::get<ConstructorCall *>(*e), offset + 1);
    }
    if (std::holds_alternative<CompoundExpression *>(*e)) {
        std::cout << "\n";
        print(std::get<CompoundExpression *>(*e), offset + 1);
    }
    if (std::holds_alternative<Keyword *>(*e)) {
        std::cout << std::get<Keyword *>(*e)->keyword << "\n";
    }
}

void print(CompoundExpression *ce, int offset) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Compound expression" << "\n";
    print(ce->expression, offset + 1);
    print(ce->methodCall, offset + 1);
}

void print(ConstructorDeclaration *cd, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Constructor" << "\n";
    print(cd->arguments, offset + 1);
    print(cd->body, offset + 1);
}

void print(MethodDeclaration *md, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Method : " << md->name << " with return type : ";
    print(md->returnType);
    std::cout << "\n";
    print(md->arguments, offset + 1);
    print(md->body, offset + 1);
}

void print(MemberDeclaration *md, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Member decl" << "\n";
    if (std::holds_alternative<MethodDeclaration *>(*md)) {
        print(std::get<MethodDeclaration *>(*md), offset + 1);
    }
    if (std::holds_alternative<ConstructorDeclaration *>(*md)) {
        print(std::get<ConstructorDeclaration *>(*md), offset + 1);
    }
    if (std::holds_alternative<VariableDefinition *>(*md)) {
        print(std::get<VariableDefinition *>(*md), offset + 1);
    }
    if (std::holds_alternative<VariableDeclaration *>(*md)) {
        print(std::get<VariableDeclaration *>(*md), offset + 1);
    }
}

void print(ClassDeclaration *cd, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Class : " << std::get<std::string>(cd->type->base);
    if (cd->type->generics != nullptr)
        print(cd->type->generics);
    if (cd->extends != nullptr) {
        std::cout << " extends: ";
        print(cd->extends);
    }
    std::cout << "\n";
    if (cd->body->members != nullptr)
        for (auto m: cd->body->members->decls) {
            print(m, offset + 1);
        }
}

void print(Program *program, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Program" << "\n";
    for (auto cd: program->classDecls->decls) {
        print(cd, offset + 1);
    }
}


#endif //BESPLATNO_COMPILER_ASTPRINTER_H
