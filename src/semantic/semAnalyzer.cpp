//
// Created by anton on 31.10.23.
//

#include <functional>
#include "semAnalyzer.h"

void SemAnalyzer::initClasses(Program *p) {
    std::string className;
    struct Visitor { // TODO: now wrong type and no generics; just for test
        std::string &name;
        explicit Visitor(std::string &name) : name(name) {};
        void operator()(std::string &s) { name = s; }
        void operator()(TypeToken *tt) { name = tt->type; }
    } visitor(className);
    std::unordered_map<ClassDeclaration*, std::string > names;
    std::unordered_map<std::string, ClassDeclaration*> cds;
    for (auto cd: p->classDecls->decls) {
        std::visit(visitor, cd->type->base);
        if (cds.contains(className)) {
            error("Redeclaration of class " + className);
        }
        names[cd] = className;
        cds[className] = cd;
    }
    std::unordered_map<std::string, int> cycleColor;
    std::function<void(ClassDeclaration*)> dfs = [&] (ClassDeclaration* cd)  {
        if (cycleColor.contains(names[cd]))
            return;
        cycleColor[names[cd]] = 1;
        Class* base = nullptr;
        if (cd->extends != nullptr) {
            std::visit(visitor, cd->extends->base);
            if (cycleColor[className] == 1) {
                error("Cycling inheritance class " + className);
            }
            if (!classes.contains(className)) {
                dfs(cds[className]);
            }
            base = &classes.at(className);
        }
        classes.insert({names[cd], Class(cd, base)});
        classes.at(names[cd]).initMembers();
        cycleColor[names[cd]] = 2;
    };
    for (auto &cd: p->classDecls->decls) {
        dfs(cd);
    }
}

void SemAnalyzer::error(const std::string& msg) {
    std::cout << msg;
    exit(-1);
}

void SemAnalyzer::Class::initMembers() {
    if (this->base != nullptr) { // inheritance
        this->constructors = this->base->constructors;        
        this->members = this->base->members;        
        this->methods = this->base->methods;        
    }
    struct Visitor {
        std::unordered_map<std::string, Method*> &mds;
        std::vector<Constructor*> &css;
        std::unordered_map<std::string, Variable*> &vars;
        explicit Visitor(std::unordered_map<std::string, Method*> &mds,
                         std::vector<Constructor*> &css,
                         std::unordered_map<std::string, Variable*> &vars)
        : mds(mds), css(css), vars(vars) {}
        void operator()(Variable *vd) { vars[vd->name] = vd; }
        void operator()(Method *vd) { mds[vd->name] = vd; }
        void operator()(Constructor *vd) { css.push_back(vd); }
    } visitor(this->methods, this->constructors, this->members);
    if (this->classDeclaration->body->members == nullptr)
        return;
    for (auto &md: this->classDeclaration->body->members->decls) {
        std::visit(visitor, *md);
    }
}

SemAnalyzer::Class::Class(ClassDeclaration *classDeclaration, Class *base)
        : classDeclaration(classDeclaration), base(base) {}
