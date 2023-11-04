//
// Created by anton on 23.10.23.
//

#ifndef BESPLATNO_COMPILER_ASTPRINTER_H
#define BESPLATNO_COMPILER_ASTPRINTER_H

#include "ast.h"

void print(Types*);
void print(Type* t) {
    std::cout << t->toString();
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
    print(is->statements, offset + 1);
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

void print(Variable *vd, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Var decl : " << vd->name << "\n";
    print(vd->expression, offset + 1);
}

void print(Statement *s, int offset) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Statement\n";
    if (std::holds_alternative<Variable *>(*s)) {
        print(std::get<Variable *>(*s), offset + 1);
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
    std::cout << "Method '" << mc->name->toString() << "' call with ";
    if (mc->arguments == nullptr) {
        std::cout << "no args\n";
        return;
    }
    std::cout << "args:\n";
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

void print(Constructor *cd, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Constructor" << "\n";
    print(cd->arguments, offset + 1);
    print(cd->body, offset + 1);
}

void print(Method *md, int offset = 0) {
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
    if (std::holds_alternative<Method *>(*md)) {
        print(std::get<Method *>(*md), offset + 1);
    }
    if (std::holds_alternative<Constructor *>(*md)) {
        print(std::get<Constructor *>(*md), offset + 1);
    }
    if (std::holds_alternative<Variable *>(*md)) {
        print(std::get<Variable *>(*md), offset + 1);
    }
}

void print(ClassDeclaration *cd, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Class : " << cd->type->toString();
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
