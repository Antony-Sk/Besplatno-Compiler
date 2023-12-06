//
// Created by anton on 18.11.23.
//

#ifndef BESPLATNO_COMPILER_CODEGEN_H
#define BESPLATNO_COMPILER_CODEGEN_H

#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <map>
#include <unordered_set>

class CodeGenerator {
public:
    CodeGenerator();

    void generateCode(Program *p);

    void generateIRCodeToFile(const std::string &filename);

    void addObjects(Program *lib);

private:
    std::unique_ptr<llvm::LLVMContext> theContext;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<llvm::Module> theModule;
    std::map<std::string, llvm::AllocaInst *> namedValues;
    std::map<std::string, llvm::Type *> namedValuesTypes;


    llvm::Value *codegen(RealLit *b);

    llvm::Value *codegen(IntegerLit *b);

    llvm::Value *codegen(BooleanLit *b);

    llvm::Value *codegen(MethodCall *mc, const std::string &from);

    llvm::Value *codegen(Expression *e);

    llvm::Function *codegenFuncDecl(Method *m);

    llvm::Function *codegen(Method *m);

    llvm::Value *codegen(Statements *statements);

    llvm::Value *codegen(ClassDeclaration *cd);

    llvm::Value *codegenDecls(ClassDeclaration *cd);

    llvm::Value *codegen(Program *p);

    llvm::Value *generateMain();

    static void error(const std::string &s);

    static void warning(const std::string &s);

    llvm::AllocaInst *createEntryBlockAlloca(llvm::Function *TheFunction, const std::string &VarName, llvm::Type *type);

    llvm::Type *getLLVMType(Expression *e);

    llvm::Type *getLLVMType(Type *e);

    std::vector<llvm::Type *> extractArgsTypes(Arguments *args);

    llvm::Value *getProp(const std::string &instance, const std::string &field) const;

    llvm::Value *getProp(llvm::Value *instance, const std::string &field) const;

    void generateVTables(ClassDeclaration *cd);

private:
    struct Class {
        struct Field {
            size_t idx;
            Expression *exp;
            llvm::Type *type;
        };
        llvm::Type *type;
        ClassDeclaration *base;
        std::map<std::string, Field> fields;
        std::unordered_map<std::string, size_t> methodsOffset;
        std::vector<llvm::Constant *> vtable;
    };
    std::unordered_map<std::string, ClassDeclaration *> typeToCd;
    std::unordered_map<std::string, Class> classes;
    llvm::Value *lastFunRet = nullptr;
    bool isInConstructor = false;
    const std::unordered_set<std::string> NOT_VIRTUAL_CLASSES{"Integer", "Real", "Boolean"};
};

#endif //BESPLATNO_COMPILER_CODEGEN_H
