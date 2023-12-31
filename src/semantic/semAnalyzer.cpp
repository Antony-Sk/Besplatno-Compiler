//
// Created by anton on 31.10.23.
//

#include <functional>
#include <utility>
#include <fstream>
#include "semAnalyzer.h"

SemAnalyzer::SemAnalyzer(const Program &p) { // Todo: generics work incorrectly now!!!
    std::string className;
    std::unordered_map<ClassDeclaration *, std::string> names;
    std::unordered_map<std::string, ClassDeclaration *> cds;
    std::unordered_set<std::string> classesNames;
    for (auto cd: p.classDecls->decls) {
        className = cd->type->toString();
        if (cd->type->generics != nullptr) { // generic class todo!!!
            templateClassesNames.insert({cd->type->base, className});
            className = cd->type->toString();
        }
        if (cds.contains(className)) {
            error("Redeclaration of class " + className, cd->type->span);
        }
        names[cd] = className;
        cds[className] = cd;
        classesNames.insert(className);
    }

//     1. find all usages of generics
//     2. instantiate generic classes with used types
//     3. continue type checking without generic classes

    std::unordered_map<std::string, int> cycleColor;
    std::function<void(ClassDeclaration *)> dfs = [&](ClassDeclaration *cd) {
        if (cycleColor[names[cd]] != 0)
            return;
        cycleColor[names[cd]] = 1;
        if (cd->extends != nullptr) {
            className = cd->extends->toString();
            if (cycleColor[className] == 1) {
                error("Cycling inheritance class " + className, cd->extends->span);
            }
            if (cd->extends->generics == nullptr) {
                if (!cds.contains(className))
                    error("No class '" + className + "'", cd->extends->span);
            } else {
                if (!templateClassesNames.contains(cd->extends->base)) {
                    error("No template class '" + cd->extends->base + "[]'", cd->extends->span);
                } else { // TODO

                }
            }
            if (!classes.contains(className)) {
                dfs(cds[className]);
            }
        }
        Class *base = nullptr;
        if (cd->extends)
            base = &classes.at(cd->extends->toString());
        classes.insert({names[cd], Class(*cd, base, names[cd])});
        classes.at(names[cd]).initMembers(classesNames);
        cycleColor[names[cd]] = 2;
    };
    for (auto &cd: p.classDecls->decls) {
        dfs(cd);
    }
}

void SemAnalyzer::error(const std::string &msg, const Span &span) {
    std::cerr << msg << " " << span.toString();
    exit(-1);
}

std::string SemAnalyzer::getTypeFromExp(const Class &context, const Expression &e) const {
    struct Visitor {
        const Class &context;
        const SemAnalyzer &sa;

        Visitor(const Class &context, const SemAnalyzer &sa) : context(context), sa(sa) {}

        std::string operator()(IntegerLit *v) { return "Integer"; }

        std::string operator()(RealLit *v) { return "Real"; }

        std::string operator()(BooleanLit *v) { return "Boolean"; }

        std::string operator()(const std::pair<std::string, Span> &p) { // Variable case
            const auto &[s, sp] = p;
            if (sa.symbols.contains(s)) // Local
                return sa.symbols.at(s);
            if (context.members.contains(s)) // Global
                return std::visit(*this, *context.members.at(s)->expression);
            error("Unknown symbol: " + s, sp);
        }

        std::string operator()(MethodCall *v) {
            if (!sa.classes.contains(v->name->toString()) && v->fullname.empty()) {
                auto *th = new Keyword();
                th->keyword = "this";
                v->arguments->exps.push_back(new Expression(th));
            }
            auto vars = sa.getVariantsTypeFromExps(context, *v->arguments);
            std::vector<std::string> possibleMethods;
            for (const auto &variant: vars) { // Checking on methods with args that are ancestors of actual args
                std::string name = v->name->toString() + "_" + variant;
                if (sa.classes.contains(v->name->toString())) { // Constructor
                    if (sa.classes.at(v->name->toString()).methods.contains(name))
                        possibleMethods.push_back(name);
                }
                if (context.methods.contains(name)) {
                    v->returnType = context.methods.at(name)->returnType;
                    possibleMethods.push_back(name);
                    break;
                }
            }
            v->fullname = v->name->toString() + "_" + sa.getTypeFromExps(context, *v->arguments);
            if (possibleMethods.empty()) {
                if (sa.classes.contains(v->name->toString())) { // Constructor
                    if (sa.classes.at(v->name->toString()).methods.contains(v->fullname)) {
                        v->returnType = sa.classes.at(v->name->toString()).methods.at(v->fullname)->returnType;
                        return v->name->toString();
                    }
                }
                error("No method '" + v->fullname + "' with such args types", v->span);
            }
            v->fullname = possibleMethods[0];
            if (sa.classes.contains(v->name->toString())) { // Constructor
                if (sa.classes.at(v->name->toString()).methods.contains(v->fullname)) {
                    v->returnType = sa.classes.at(v->name->toString()).methods.at(v->fullname)->returnType;

                    return v->name->toString();
                }
                error("No constructor with such parameters of class '" + v->name->toString() + "'", v->span);
            }
            if (sa.matchExpsAndArgs(v->arguments, context.methods.at(v->fullname)->arguments, context)) {
                return context.methods.at(v->fullname)->returnType->toString();
            }
            error("No such method or type : " + v->name->toString(), v->span);
        }

        std::string operator()(Keyword *v) { // "this"
            return context.name;
        }

        std::string operator()(CompoundExpression *v) {
            if (v->methodCall->fullname.empty())
                v->methodCall->arguments->exps.push_back(v->expression);
            std::string type = v->expType = std::visit(*this, *v->expression);
            auto vars = sa.getVariantsTypeFromExps(context, *v->methodCall->arguments);
            const auto &ms = sa.classes.at(type).methods;
            std::vector<std::string> possibleMethods;
            for (const auto &variant: vars) {
                std::string name = v->methodCall->name->toString() + "_" + variant;
                if (ms.contains(name)) {
                    possibleMethods.push_back(name);
                    v->methodCall->returnType = ms.at(name)->returnType;
                    break;
                }
            }
            v->methodCall->fullname =
                    v->methodCall->name->toString() + "_" + sa.getTypeFromExps(context, *v->methodCall->arguments);
            std::string methodName = v->methodCall->fullname;
            if (possibleMethods.empty()) {
                error("No method '" + methodName + "' with such args types", v->methodCall->span);
            }
            v->methodCall->fullname = methodName = possibleMethods[0];
            if (sa.matchExpsAndArgs(v->methodCall->arguments, ms.at(methodName)->arguments, context)) {
                return ms.at(methodName)->returnType->toString();
            }
            error("No method '" + methodName + "' in class '" + type + "'", v->methodCall->span);
        }
    } visitor(context, *this);
    return std::visit(visitor, e);
}

void SemAnalyzer::checkTypes() {
    struct Visitor {
        SemAnalyzer &sa;
        const Class &context;
        bool inCycle = false;
        std::unordered_map<std::string, int> localVarUsage;
        std::string metRetType;

        Visitor(SemAnalyzer &sa, const Class &context) : sa(sa), context(context) {}

        void operator()(Variable *v) {
            if (sa.symbols.contains(v->name))
                error("Redeclaration of var " + v->name, v->span);
            if (sa.classes.contains(v->name) || context.methods.contains(v->name))
                error("Name of var cannot be name of class of method: " + v->name, v->span);
            sa.symbols[v->name] = sa.getTypeFromExp(context, *v->expression);
        }

        void operator()(IfStatement *s) {
            if (sa.getTypeFromExp(context, *s->relation) != "Boolean") {
                error("Expected Boolean found " + sa.getTypeFromExp(context, *s->relation), s->span);
            }
            for (Statement *stm: s->statements->stmts)
                std::visit(*this, *stm);
            if (s->elseStatements != nullptr)
                for (Statement *stm: s->elseStatements->stmts)
                    std::visit(*this, *stm);
        }

        void operator()(WhileStatement *s) {
            if (sa.getTypeFromExp(context, *s->relation) != "Boolean") {
                error("Expected Boolean found " + sa.getTypeFromExp(context, *s->relation), s->span);
            }
            inCycle = true;
            for (Statement *stm: s->statement->stmts)
                std::visit(*this, *stm);
            inCycle = false;
        }

        void operator()(ReturnStatement *s) {
            std::string t = sa.getTypeFromExp(context, *s->expression);
            if (t != metRetType)
                error("Return wrong type", s->span);
        }

        void operator()(Assignment *s) {
            if (!sa.symbols.contains(s->identifier) && !context.members.contains(s->identifier))
                error("No such variable " + s->identifier, s->span);
            sa.getTypeFromExp(context, *s->expression);
        }

        void operator()(Expression *e) {
            sa.getTypeFromExp(context, *e);
        }

        void operator()(Keyword *b) {
            if (!inCycle)
                error("Break is on in cycle", b->span);
        }
    };

    for (const auto &[className, c]: classes) {
        Visitor visitor(*this, c);
        for (const auto &[metName, met]: c.methods) {
            if (!classes.contains(met->returnType->toString()))
                error("Class '" + met->returnType->toString() + "' is undefined", met->returnType->span);
            symbols.clear();
            for (const auto &arg: met->arguments->args) {
                if (!classes.contains(arg->type->toString()))
                    error("Class '" + arg->type->toString() + "' is undefined", arg->span);
                if (symbols.contains(arg->name))
                    error("Args names are the same '" + arg->name + "' for method '" + className + "." + metName + "'",
                          arg->span);
                symbols.emplace(arg->name, arg->type->toString());
            }
            for (Statement *stm: met->body->stmts) {
                visitor.metRetType = met->returnType->toString();
                std::visit(visitor, *stm);
            }
        }
        symbols.clear();
        for (const auto &[varName, var]: c.members) {
            if (symbols.contains(varName))
                error("Redeclaration of var " + varName, var->span);
            if (classes.contains(varName))
                error("Name of var cannot be name of class: " + varName, var->span);
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
        this->members = this->base->members;
        for (const auto &[name, method]: this->base->methods) {
            if (classesNames.contains(name.substr(0, name.size() - 1))) // Constructors do not inherit
                continue;
            auto *newArgs = new Arguments();
            for (const auto &arg: method->arguments->args)
                newArgs->add(arg);
            newArgs->args.back() = new Argument(newArgs->args.back()->name, this->classDeclaration.type,
                                                newArgs->args.back()->span); // Change type of var "this"
            auto newMet = new Method(method->name, newArgs, method->returnType, method->body, method->span);
            std::string id = method->name + "_" + newMet->arguments->extractTypesAsString();
            newMet->fullName = id;
            this->methods[id] = newMet;
        }
    }
    struct Visitor {
        const std::unordered_set<std::string> &classesNames;
        std::unordered_map<std::string, Method *> &mds;
        std::unordered_map<std::string, Variable *> &vars;
        std::string className;
        ClassDeclaration &cd;
        std::unordered_set<std::string> notInheritedMethods;

        void operator()(Variable *vd) {
            if (vars.contains(vd->name) || mds.contains(vd->name) || classesNames.contains(vd->name))
                error("Redeclaration of var " + vd->name, vd->span);
//            if (className == vd->expression) // TODO: No declaration of type inside of itself (int cannot contain int)
            vars[vd->name] = vd;
        }

        void operator()(Method *vd) { // Quiz starts at 9:10
            std::string id = vd->name + "_" + vd->arguments->extractTypesAsString();
            if (vars.contains(id) || notInheritedMethods.contains(id) || classesNames.contains(id))
                error("Redeclaration of method " + id, vd->span);
            vd->fullName = id;
            mds[id] = vd;
            notInheritedMethods.insert(id);
        }

        void operator()(Constructor *vd) {
            error("Something wrong: no constructors in AST!!!", vd->span);
        }
    } visitor{classesNames, this->methods, this->members, name, this->classDeclaration};
    if (this->classDeclaration.body->members == nullptr)
        return;
    for (auto &md: this->classDeclaration.body->members->decls) {
        if (std::holds_alternative<Constructor *>(*md)) {
            Constructor *c = std::get<Constructor *>(*md);
            *md = new Method(name, c->arguments, this->classDeclaration.type, c->body, c->span, true);
            delete c;
        } else if (std::holds_alternative<Method *>(*md)) {
            std::get<Method *>(*md)->arguments->args.push_back(new Argument("this", classDeclaration.type, {}));
        }
    }
    for (auto &md: this->classDeclaration.body->members->decls) {
        std::visit(visitor, *md);
    }
}

SemAnalyzer::Class::Class(ClassDeclaration &classDeclaration, const Class *base, std::string name)
        : classDeclaration(classDeclaration), base(base), name(std::move(name)) {}

std::string SemAnalyzer::getTypeFromExps(const SemAnalyzer::Class &context, Expressions &e) const {
    std::string res;
    bool isFilled = !e.expsTypes.empty();
    for (const auto &exp: e.exps) {
        std::string type = getTypeFromExp(context, *exp);
        res += type + "_";
        if (!isFilled)
            e.expsTypes.push_back(type);
    }
    return res;
}

std::vector<std::string>
SemAnalyzer::getVariantsTypeFromExps(const SemAnalyzer::Class &context, const Expressions &e) const {
    std::vector<std::string> res;
    std::string inter;
    std::function<void(int)> dfs = [&](int i) {
        if (i == e.exps.size()) {
            res.push_back(inter);
            return;
        }
        std::string a = getTypeFromExp(context, *e.exps[i]);
        std::string pref = inter;
        for (;;) {
            inter = pref + a + "_";
            dfs(i + 1);
            if (classes.at(a).base)
                a = classes.at(a).base->name;
            else
                break;
        }
    };
    if (!e.exps.empty())
        dfs(0);
    return res;
}

void SemAnalyzer::instantiateGenerics(Program &p) {
    std::unordered_map<std::string, Type *> templates;
    // check inner vars types of not template classes and not self template vars of template classes
    // check vars types of not template classes and not self template vars of template classes
    // check args types of not template classes and not self template vars of template classes
    // check ret types of methods of not template classes and not self template vars of template classes
    // And only after check extends types
    // again check vars and methods types of self template vars of template classes
    for (auto &cd: p.classDecls->decls) {

    }

    for (auto &cd: p.classDecls->decls) {
        Type *t = cd->extends;
        if (cd->type->generics == nullptr) { // All "T" in "extends A[T]" should exist
            while (t != nullptr) {
                templates[t->toString()] = t;
                t = t->generics->types[0]; // Todo: Now it works only on one generic on class
            }
        } else {
            std::string templateTypeName = cd->type->generics->types[0]->toString(); // Todo: Now it works only on one generic on class
            std::function<bool(Type *)> dfs = [&templates, &templateTypeName, &dfs](Type *t) -> bool {
                if (t == nullptr)
                    return true;
                if (t->toString() == templateTypeName) {
                    return false;
                }
                if (dfs(t->generics->types[0])) {
                    templates[t->toString()] = t;
                    return true;
                }
                return false;
            };
        }
    }
}
