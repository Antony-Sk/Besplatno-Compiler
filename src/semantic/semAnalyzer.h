//
// Created by anton on 31.10.23.
//

#ifndef BESPLATNO_COMPILER_SEMANALYZER_H
#define BESPLATNO_COMPILER_SEMANALYZER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "ast.h"

class SemAnalyzer {
    struct Class {
        const std::string name;
        const Class *base;
        std::unordered_map<std::string, Constructor *> constructors;
        std::unordered_map<std::string, Method *> methods;
        std::unordered_map<std::string, Variable *> members;
        const ClassDeclaration &classDeclaration;

        Class(const ClassDeclaration &classDeclaration, const Class *base, std::string name);
        void initMembers(const std::unordered_set<std::string> &classesNames);
    };

public:
    explicit SemAnalyzer(const Program &p);
    static void error(const std::string &msg);
    void checkTypes();
private:
    std::unordered_map<std::string, Variable *> vars;
    std::unordered_map<std::string, Class> classes;
    std::unordered_map<std::string, std::string> symbols;
    std::string getTypeFromExp(const Class& context, const Expression& e) const;
    std::string getTypeFromExps(const Class& context, const Expressions& e) const;
    bool matchExpsAndArgs(Expressions* e, Arguments* a, const Class& context) const;
};


#endif //BESPLATNO_COMPILER_SEMANALYZER_H
