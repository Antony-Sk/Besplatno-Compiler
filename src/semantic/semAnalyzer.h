//
// Created by anton on 31.10.23.
//

#ifndef BESPLATNO_COMPILER_SEMANALYZER_H
#define BESPLATNO_COMPILER_SEMANALYZER_H


#include <string>
#include <unordered_map>
#include "ast.h"

class SemAnalyzer {
    struct Class {
        Class* base;
        std::vector<Constructor *> constructors;
        std::unordered_map<std::string, Method *> methods;
        std::unordered_map<std::string, Variable *> members;
        ClassDeclaration *classDeclaration;
        Class(ClassDeclaration *classDeclaration, Class* base);
        void initMembers();
    };
public:
    void initClasses(Program *p);
    void error(const std::string& msg);
private:
    std::unordered_map<std::string, Variable *> vars;
    std::unordered_map<std::string, Class> classes;
};


#endif //BESPLATNO_COMPILER_SEMANALYZER_H
