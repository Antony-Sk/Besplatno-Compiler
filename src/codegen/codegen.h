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

    llvm::Value *codegen(MethodCall *mc);

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

    std::vector<llvm::Type*> extractArgsTypes(Arguments* args);

    llvm::Value *getProp(const std::string &instance, const std::string &field) const ;
private:
    struct Class {
        llvm::StructType* type;
        std::map<std::string, Expression *> fields;
    };
    llvm::StructType *cls; // Currently compiling class
    std::unordered_map<std::string, Class> classes;
};

#endif //BESPLATNO_COMPILER_CODEGEN_H
