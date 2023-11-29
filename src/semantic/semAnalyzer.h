//
// Created by anton on 31.10.23.
//

#ifndef BESPLATNO_COMPILER_SEMANALYZER_H
#define BESPLATNO_COMPILER_SEMANALYZER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include "ast.h"

class SemAnalyzer {
public:
    explicit SemAnalyzer(const Program &p);
    void checkTypes();

private:
    struct Class {
        const std::string name;
        const Class *base;
        std::unordered_map<std::string, Method *> methods; // "name&type1&type2&...typeN&" -> Method*
        std::unordered_map<std::string, Variable *> members;
        ClassDeclaration &classDeclaration;

        Class(ClassDeclaration &classDeclaration, const Class *base, std::string name);

        void initMembers(const std::unordered_set<std::string> &classesNames);
    };

    std::unordered_map<std::string, Class> classes;
    std::unordered_map<std::string, Class> stdClasses;
    std::unordered_map<std::string, std::string> templateClassesNames;
    std::unordered_map<std::string, std::string> symbols;

private:
    static void error(const std::string &msg, const Span & = Span());

    std::string getTypeFromExp(const Class &context, const Expression &e) const;

    std::string getTypeFromExps(const Class &context, const Expressions &e) const;

    bool matchExpsAndArgs(Expressions *e, Arguments *a, const Class &context) const;

    void instantiateGenerics(Program &p);
};


#endif //BESPLATNO_COMPILER_SEMANALYZER_H
