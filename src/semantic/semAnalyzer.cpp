//
// Created by anton on 31.10.23.
//

#include <functional>
#include <utility>
#include "semAnalyzer.h"

SemAnalyzer::SemAnalyzer(const Program &p) { // Todo: generics work incorrectly now!!!
    std::string className;
    std::unordered_map<ClassDeclaration *, std::string> names;
    std::unordered_map<std::string, ClassDeclaration *> cds;
    std::unordered_set<std::string> classesNames;
    for (auto cd: p.classDecls->decls) {
        className = cd->type->toString();
        if (cds.contains(className)) {
            error("Redeclaration of class " + className);
        }
        names[cd] = className;
        cds[className] = cd;
        classesNames.insert(className);
    }
    std::unordered_map<std::string, int> cycleColor;
    std::function<void(ClassDeclaration *)> dfs = [&](ClassDeclaration *cd) {
        if (cycleColor.contains(names[cd]))
            return;
        cycleColor[names[cd]] = 1;
        Class *base = nullptr;
        if (cd->extends != nullptr) {
            className = cd->extends->toString();
            if (cycleColor[className] == 1) {
                error("Cycling inheritance class " + className);
            }
            if (!classes.contains(className)) {
                dfs(cds[className]);
            }
            base = &classes.at(className);
        }
        classes.insert({names[cd], Class(*cd, base, names[cd])});
        classes.at(names[cd]).initMembers(classesNames);
        cycleColor[names[cd]] = 2;
    };
    for (auto &cd: p.classDecls->decls) {
        dfs(cd);
    }
}

void SemAnalyzer::error(const std::string &msg) {
    std::cout << msg;
    exit(-1);
}

std::string SemAnalyzer::getTypeFromExp(const Class& context, const Expression& e) const {
    struct Visitor {
        const Class& context;
        const SemAnalyzer &sa;
        Visitor(const Class &context, const SemAnalyzer &sa) : context(context), sa(sa) {}
        std::string operator()(IntegerLit *v) { return "Integer";}
        std::string operator()(RealLit *v) {return "Real";}
        std::string operator()(BooleanLit *v) {return "Boolean";}
        std::string operator()(const std::string &s) { // Variable case
            if (sa.symbols.contains(s)) // Local
                return sa.symbols.at(s);
            if (context.members.contains(s)) // Global
                return std::visit(*this, *context.members.at(s)->expression);
            error("Unknown symbol: " + s);
        }
        std::string operator()(MethodCall *v) {
            if (context.methods.contains(v->name->toString())) { // Plain function
                if (sa.matchExpsAndArgs(v->arguments, context.methods.at(v->name->toString())->arguments, context))
                    return context.methods.at(v->name->toString())->returnType->toString();
                error("Wrong parameters on call '" + v->name->toString() + "' with such args");
            }
            if (sa.classes.contains(v->name->toString())) { // Constructor
                std::string argsTypes;
                if (v->arguments != nullptr)
                    argsTypes = sa.getTypeFromExps(context, *v->arguments);
                if (sa.classes.at(v->name->toString()).constructors.contains(argsTypes))
                    return v->name->toString();
                error("No constructor with such parameters of class '" + v->name->toString() + "'");
            }
            error("No such method or constructor :" + v->name->toString());
        }
        std::string operator()(Keyword *v) { // "this"
            return context.name;
        }
        std::string operator()(CompoundExpression *v) {
            std::string type = std::visit(*this, *v->expression);
            std::string methodName = v->methodCall->name->toString();
            const auto& ms = sa.classes.at(type).methods;
            if (ms.contains(methodName)) {
                if (sa.matchExpsAndArgs(v->methodCall->arguments, ms.at(methodName)->arguments, context)) {
                    return ms.at(methodName)->returnType->toString();
                }
                error("No method '" + methodName + "' with such args types");
            }
            error("No method '" + methodName + "' in class '" + type);
        }
    } visitor(context, *this);
    return std::visit(visitor, e);
}

void SemAnalyzer::checkTypes() {
    struct Visitor {
        SemAnalyzer& sa;
        const Class& context;
        Visitor(SemAnalyzer &sa, const Class &context) : sa(sa), context(context) {}
        void operator()(Variable* v) {
            if (sa.symbols.contains(v->name))
                error("Redeclaration of var " + v->name);
            if (sa.classes.contains(v->name) || context.methods.contains(v->name))
                error("Name of var cannot be name of class of method: " + v->name);
            sa.symbols[v->name] = sa.getTypeFromExp(context, *v->expression);
        }
        void operator()(IfStatement* s) {
            if (sa.getTypeFromExp(context, *s->relation) != "Boolean")
                error("Expected Boolean found " + sa.getTypeFromExp(context, *s->relation));
            for (Statement* stm: s->statements->stmts)
                std::visit(*this, *stm);
            if (s->elseStatements != nullptr)
                for (Statement* stm: s->elseStatements->stmts)
                    std::visit(*this, *stm);
        }
        void operator()(WhileStatement* s) {
            if (sa.getTypeFromExp(context, *s->relation) != "Boolean")
                error("Expected Boolean found " + sa.getTypeFromExp(context, *s->relation));

            for (Statement* stm: s->statement->stmts)
                std::visit(*this, *stm);
        }
        void operator()(ReturnStatement*s) {
            sa.getTypeFromExp(context, *s->expression);
        }
        void operator()(Assignment*s) {
            if (!sa.symbols.contains(s->identifier) && !sa.vars.contains(s->identifier))
                error("No such variable " + s->identifier);
        }
        void operator()(Expression*e) {
            sa.getTypeFromExp(context, *e);
        }
    };

    for (const auto& [className, c]: classes) {
        Visitor visitor(*this, c);
        for (const auto& [metName, met]: c.methods) {
            if (!classes.contains(met->returnType->toString()))
                error("Class '" + met->returnType->toString() + "' is undefined");
            symbols.clear();
            if (met->arguments != nullptr)
                for (const auto &arg: met->arguments->args) {
                    if (!classes.contains(arg->type->toString()))
                        error("Class '" + arg->type->toString() + "' is undefined");
                    if (symbols.contains(arg->name))
                        error("Args names are the same '" + arg->name + "' for method '" + metName + "'");
                    symbols.emplace(arg->name, arg->type->toString());
                }
            for (Statement* stm: met->body->stmts) {
                std::visit(visitor, *stm);
            }
        }
        for (const auto& [cnsName, cns]: c.constructors) {
            symbols.clear();
            if (cns->arguments != nullptr)
                for (const auto &arg: cns->arguments->args) {
                    if (!classes.contains(arg->type->toString()))
                        error("Class '" + arg->type->toString() + "' is undefined");
                    if (symbols.contains(arg->name))
                        error("Args names are the same '" + arg->name + "' for constructor of class '" + cnsName + "'");
                    symbols.emplace(arg->name, arg->type->toString());
                }
            for (Statement* stm: cns->body->stmts) {
                std::visit(visitor, *stm);
            }
        }
        for (const auto& [varName, var]: c.members) {
            if (symbols.contains(varName))
                error("Redeclaration of var " + varName);
            if (classes.contains(varName))
                error("Name of var cannot be name of class: " + varName);
            getTypeFromExp(c, *var->expression);
        }
    }
}

bool SemAnalyzer::matchExpsAndArgs(Expressions *e, Arguments *a, const SemAnalyzer::Class &context) const {
    if (e->exps.size() != a->args.size())
        return false;
    for (int i = 0; i < a->args.size(); ++i) {
        if (a->args[i]->type->toString() != getTypeFromExp(context, *e->exps[i])) {
            return false;
        }
    }
    return true;
}

void SemAnalyzer::Class::initMembers(const std::unordered_set<std::string> &classesNames) {
    if (this->base != nullptr) { // inheritance
        this->constructors = this->base->constructors;
        this->members = this->base->members;
        this->methods = this->base->methods;
    }
    struct Visitor {
        const std::unordered_set<std::string> &classesNames;
        std::unordered_map<std::string, Method *> &mds;
        std::unordered_map<std::string, Constructor *> &css;
        std::unordered_map<std::string, Variable *> &vars;
        std::string className;
        Visitor(std::unordered_map<std::string, Method *> &mds, std::unordered_map<std::string, Constructor *> &css,
                         std::unordered_map<std::string, Variable *> &vars,
                         const std::unordered_set<std::string> &classesNames, std::string className)
                : mds(mds), css(css), vars(vars), classesNames(classesNames), className(std::move(className)) {}
        void operator()(Variable *vd) {
            if (vars.contains(vd->name) || mds.contains(vd->name) || classesNames.contains(vd->name))
                error("Redeclaration of var " + vd->name);
//            if (className == vd->expression) // TODO: No declaration of type inside of itself (int cannot contain int)
            vars[vd->name] = vd;
        }
        void operator()(Method *vd) {
            if (vars.contains(vd->name) || mds.contains(vd->name) || classesNames.contains(vd->name))
                error("Redeclaration of method " + vd->name);
            mds[vd->name] = vd;
        }
        void operator()(Constructor *vd) {
            if (css.contains(vd->arguments->extractTypesAsString()))
                error("Constructor of '" + className + "' with args of types '" + vd->arguments->extractTypesAsString()+ "' already exists");
            css.emplace(vd->arguments->extractTypesAsString(), vd);
        }
    } visitor(this->methods, this->constructors, this->members, classesNames, name);
    if (this->classDeclaration.body->members == nullptr)
        return;
    for (auto &md: this->classDeclaration.body->members->decls) {
        std::visit(visitor, *md);
    }
}

SemAnalyzer::Class::Class(const ClassDeclaration &classDeclaration, const Class *base, std::string name)
        : classDeclaration(classDeclaration), base(base), name(std::move(name)) {}

std::string SemAnalyzer::getTypeFromExps(const SemAnalyzer::Class &context, const Expressions &e) const {
    std::string res;
    for (const auto& exp: e.exps) {
        res += getTypeFromExp(context, *exp) + "&";
    }
    return res;
}
