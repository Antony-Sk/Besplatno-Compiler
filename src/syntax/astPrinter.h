//
// Created by anton on 23.10.23.
//

#ifndef BESPLATNO_COMPILER_ASTPRINTER_H
#define BESPLATNO_COMPILER_ASTPRINTER_H

#include "ast.h"

void print(Types *);

void print(Type *t) {
    std::cout << t->toString();
}

void print(Types *t) {
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

void print(Assignment *vd, int offset = 0) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Var assignment : " << vd->identifier << " with exp:\n";
    print(vd->expression, offset + 1);
}

void print(Statement *s, int offset) {
    for (int i = 0; i < offset; i++)
        std::cout << "-";
    std::cout << "Statement\n";
    struct Visitor {
        int offset;

        void operator()(Variable *v) { print(v, offset + 1); }

        void operator()(IfStatement *v) { print(v, offset + 1); }

        void operator()(ReturnStatement *v) { print(v, offset + 1); }

        void operator()(WhileStatement *v) { print(v, offset + 1); }

        void operator()(Expression *v) { print(v, offset + 1); }

        void operator()(Assignment *v) { print(v, offset + 1); }

        void operator()(Keyword *v) {
            for (int i = 0; i <= offset; i++)
                std::cout << "-";
            std::cout << "Break\n";
        }
    } visitor{offset};
    std::visit(visitor, *s);
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
    struct Visitor {
        int offset;

        void operator()(IntegerLit *v) { std::cout << v->value << "\n"; }

        void operator()(RealLit *v) { std::cout << v->value << "\n"; }

        void operator()(BooleanLit *v) { std::cout << v->value << "\n"; }

        void operator()(const std::pair<std::string, Span> &p) { std::cout << p.first << '\n'; }

        void operator()(MethodCall *v) {
            std::cout << "\n";
            print(v, offset + 1);
        }

        void operator()(Keyword *v) { std::cout << v->keyword << "\n"; }

        void operator()(CompoundExpression *v) {
            std::cout << "\n";
            print(v, offset + 1);
        }
    } visitor{offset};
    std::visit(visitor, *e);
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
    std::visit([offset](auto t) { print(t, offset + 1); }, *md);
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
