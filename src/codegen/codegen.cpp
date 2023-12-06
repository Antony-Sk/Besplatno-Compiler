//
// Created by anton on 13.11.23.
//

#include "llvm/ADT/APFloat.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/TargetParser/Host.h"
#include "llvm/MC/TargetRegistry.h"

#include "ast.h"
#include "codegen.h"

#include <utility>

llvm::Value *CodeGenerator::codegen(RealLit *b) {
    return llvm::ConstantFP::get(*theContext, llvm::APFloat((double) b->value));
}

llvm::Value *CodeGenerator::codegen(IntegerLit *b) {
    return llvm::ConstantInt::get(*theContext, llvm::APInt(64, b->value, true));
}

llvm::Value *CodeGenerator::codegen(BooleanLit *b) {
    return llvm::ConstantInt::get(*theContext, llvm::APInt(1, b->value, false));
}

llvm::Value *CodeGenerator::codegen(MethodCall *mc, const std::string &from) {
    llvm::FunctionType *ft = nullptr;
    llvm::Value *callee = nullptr;
    if (classes.contains(mc->name->toString())) { // Constructor
        callee = theModule->getFunction(mc->fullname);
        ft = theModule->getFunction(mc->fullname)->getFunctionType();
    } else {
        std::string type = mc->arguments->expsTypes.back();
        if (NOT_VIRTUAL_CLASSES.contains(type)) {
            callee = theModule->getFunction(mc->fullname);
            ft = theModule->getFunction(mc->fullname)->getFunctionType();
        } else {
            auto vtableType = llvm::ArrayType::get(llvm::Type::getInt64PtrTy(*theContext),
                                                   classes[type].methodsOffset.size());
            llvm::Value *vtable = getProp(from, "vtable" + type);
            vtable = builder->CreateLoad(vtableType->getPointerTo(), vtable);
            auto adderss = builder->CreateStructGEP(vtableType, vtable, classes[type].methodsOffset[mc->fullname]);
            callee = builder->CreateLoad(llvm::Type::getInt64PtrTy(*theContext), adderss, mc->fullname);
            ft = llvm::FunctionType::get(this->getLLVMType(mc->returnType), false);
        }
    }
    if (!callee) {
        error("Unknown function " + mc->fullname + " referenced");
    }
    std::vector<llvm::Value *> argsV;
    if (classes.contains(mc->name->toString())) {
        for (const auto &exp: mc->arguments->exps) {
            argsV.push_back(codegen(exp));
        }
    } else {
        for (int i = 0; i < (int) mc->arguments->exps.size() - 1; i++) {
            argsV.push_back(codegen(mc->arguments->exps[i]));
        }
        if (from.starts_with("__") || !isInConstructor)
            argsV.push_back(builder->CreateLoad(namedValuesTypes.at(from), namedValues.at(from)));
        else
            argsV.push_back(namedValues.at(from));
    }
    auto ret = builder->CreateCall(ft, callee, argsV, "calltmp");
    return ret;//builder->CreateLoad(ft->getReturnType(), ret);
}

llvm::Value *CodeGenerator::codegen(Expression *e) {
    struct Visitor {
        CodeGenerator *cg;

        llvm::Value *operator()(IntegerLit *v) { return cg->codegen(v); }

        llvm::Value *operator()(RealLit *v) { return cg->codegen(v); }

        llvm::Value *operator()(BooleanLit *v) { return cg->codegen(v); }

        llvm::Value *operator()(Keyword *) {
            return cg->namedValues["this"];
        }

        llvm::Value *operator()(MethodCall *v) {
            return cg->codegen(v, "this");
        }


        llvm::Value *operator()(const std::pair<std::string, Span> &p) {
            llvm::AllocaInst *v = cg->namedValues[p.first];
            if (v == nullptr) {
                llvm::Type *thisType = cg->namedValuesTypes.at("this");
                auto val = cg->getProp("this", p.first);
                if (val == nullptr)
                    error("Var " + p.first + " not found");
//                if (cg->isInConstructor)
//                    val = cg->builder->CreateLoad(llvm::Type::getInt64PtrTy(*cg->theContext), val, "this->" + p.first);
                while (!cg->classes.at(thisType->getStructName().str()).fields.contains(p.first)) {
                    thisType = cg->classes.at(
                            cg->classes.at(thisType->getStructName().str()).base->type->toString()).type;
                }
                return cg->builder->CreateLoad(cg->classes.at(thisType->getStructName().str()).fields.at(p.first).type,
                                               val, p.first);
            }
            return cg->builder->CreateLoad(v->getAllocatedType(), v, p.first.c_str());
        }

        llvm::Value *operator()(CompoundExpression *v) {
            std::string tmpName = "_tmp" + v->methodCall->fullname;
            if (cg->NOT_VIRTUAL_CLASSES.contains(v->expType))
                tmpName = "_" + tmpName;
            cg->namedValues[tmpName] = cg->createEntryBlockAlloca(cg->builder->GetInsertBlock()->getParent(), tmpName,
                                                                  cg->classes.at(v->expType).type);
            cg->builder->CreateStore(cg->codegen(v->expression), cg->namedValues[tmpName]);
            cg->namedValuesTypes[tmpName] = cg->classes.at(v->expType).type;
            auto ret = cg->codegen(v->methodCall, tmpName);
            return ret;
        }
    } visitor{this};
    return std::visit(visitor, *e);
}

llvm::Function *CodeGenerator::codegenFuncDecl(Method *m) {
    std::vector<llvm::Type *> args = extractArgsTypes(m->arguments);
    std::string methodName = m->fullName;
    llvm::FunctionType *FT = llvm::FunctionType::get(getLLVMType(m->returnType), args, false);

    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, methodName, theModule.get());
    unsigned Idx = 0;
    for (llvm::Function::arg_iterator AI = F->arg_begin(); Idx != m->arguments->args.size();
         ++AI, ++Idx) {
        AI->setName(m->arguments->args[Idx]->name);
    }
    return F;
}

llvm::Function *CodeGenerator::codegen(Method *m) {
    llvm::Function *F = theModule->getFunction(m->fullName);
    if (!F)
        F = codegenFuncDecl(m);
    namedValues.clear();
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(*theContext, "entry", F);
    builder->SetInsertPoint(BB);

    int i = 0;
    for (auto &Arg: F->args()) {
        llvm::AllocaInst *arg = createEntryBlockAlloca(F, Arg.getName().str(), Arg.getType());
        builder->CreateStore(&Arg, arg);
        namedValues[Arg.getName().str()] = arg;
        namedValuesTypes[Arg.getName().str()] = getLLVMType(m->arguments->args[i++]->type);
    }
    llvm::AllocaInst *obj;
    if (m->isConstructor) { // constructor
        isInConstructor = true;
        if (classes.at(m->name).base != nullptr) {
            llvm::Function *cst = theModule->getFunction(classes.at(m->name).base->type->toString() + "_");
            if (!cst) {
                warning("No default constructor in class " + classes.at(m->name).base->type->toString());
            } else {
                builder->CreateCall(cst);
            }
        }
        obj = namedValues["this"] = createEntryBlockAlloca(F, "this", getLLVMType(m->returnType));
        namedValuesTypes["this"] = obj->getAllocatedType();
//        namedValues["this"] = createEntryBlockAlloca(F, "this", getLLVMType(m->returnType)->getPointerTo());
//        builder->CreateStore(namedValues["_this"], namedValues["this"]);
//        namedValuesTypes["this"] = obj->getAllocatedType();

        for (const auto &[name, var]: classes[m->name].fields) {
            if (var.exp != nullptr)
                builder->CreateStore(codegen(var.exp), getProp("this", name));
        }
        // Filling vtable:
        auto adderss = getProp("this", "vtable" + m->name);
        builder->CreateStore(theModule->getNamedGlobal("vtable" + m->name), adderss);
    }
    if (llvm::Value *RetVal = codegen(m->body)) {
        verifyFunction(*F);
    }
    if (m->isConstructor) { // constructor
        isInConstructor = false;
        builder->CreateRet(builder->CreateLoad(getLLVMType(m->returnType), obj));
    }
    return F;
}

llvm::Value *CodeGenerator::codegen(Statements *statements) {
    if (statements == nullptr)
        return nullptr;
    struct Visitor {
        CodeGenerator &c;
        llvm::Value *ret = nullptr;

        llvm::Value *operator()(Variable *v) {
            llvm::AllocaInst *var = c.createEntryBlockAlloca(c.builder->GetInsertBlock()->getParent(), v->name,
                                                             c.getLLVMType(v->expression));
            c.builder->CreateStore(c.codegen(v->expression), var);
            c.namedValues[v->name] = var;
            return nullptr;
        }

        llvm::Value *operator()(IfStatement *s) {
            llvm::Value *CondV = c.codegen(s->relation);
            if (!CondV) {
                return nullptr;
            }
            // Convert condition to a bool by comparing non-equal to 0.
            CondV = c.builder->CreateICmpNE(CondV, llvm::ConstantInt::get(*c.theContext, llvm::APInt(1, 0)), "ifcond");
            llvm::Function *TheFunction = c.builder->GetInsertBlock()->getParent();

            // Create blocks for the then and else cases.  Insert the 'then' block at the
            // end of the function.
            llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(*c.theContext, "then", TheFunction);
            llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(*c.theContext, "else");
            llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(*c.theContext, "ifcont");

            c.builder->CreateCondBr(CondV, ThenBB, ElseBB);

            // Emit then value.
            c.builder->SetInsertPoint(ThenBB);

            llvm::Value *ThenV = c.codegen(s->statements);
//            if (!ThenV) { // todo
//                return nullptr;
//            }
            if (!ThenV)
                c.builder->CreateBr(MergeBB);
            // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
            ThenBB = c.builder->GetInsertBlock();
            // Emit else block.
            TheFunction->insert(TheFunction->end(), ElseBB);
            c.builder->SetInsertPoint(ElseBB);

            llvm::Value *ElseV = c.codegen(s->elseStatements);
//            if (!ElseV) { // todo
//                return nullptr;
//            }

            if (!ElseV)
                c.builder->CreateBr(MergeBB);
            // codegen of 'Else' can change the current block, update ElseBB for the PHI.
//            ElseBB = c.builder->GetInsertBlock();
            // Emit merge block.
            TheFunction->insert(TheFunction->end(), MergeBB);
            c.builder->SetInsertPoint(MergeBB);
            return nullptr;
        }

        llvm::Value *operator()(WhileStatement *s) {
            // Emit the start code first, without 'variable' in scope.
            llvm::Value *StartVal = c.codegen(s->relation);
            if (!StartVal)
                return nullptr;
            llvm::Function *TheFunction = c.builder->GetInsertBlock()->getParent();
            llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(*c.theContext, "loop", TheFunction);

            // Insert an explicit fall through from the current block to the LoopBB.
            c.builder->CreateBr(LoopBB);
            // Start insertion in LoopBB.
            c.builder->SetInsertPoint(LoopBB);

            c.codegen(s->statement);
            // Compute the end condition.
            llvm::Value *EndCond = c.codegen(s->relation);
            // Convert condition to a bool by comparing non-equal to 0.
            EndCond = c.builder->CreateICmpNE(EndCond, llvm::ConstantInt::get(*c.theContext, llvm::APInt(1, 0)),
                                              "loopcond");
            // Create the "after loop" block and insert it.
            llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(*c.theContext, "afterloop", TheFunction);
            // Insert the conditional branch into the end of LoopEndBB.
            c.builder->CreateCondBr(EndCond, LoopBB, AfterBB);
            c.builder->SetInsertPoint(AfterBB);
            return llvm::Constant::getNullValue(llvm::Type::getDoubleTy(*c.theContext));
        }

        llvm::Value *operator()(ReturnStatement *s) {
            return ret = c.builder->CreateRet(c.codegen(s->expression));
        }

        llvm::Value *operator()(Assignment *s) {
            llvm::AllocaInst *v = c.namedValues[s->identifier];
            if (v == nullptr) {
                llvm::Value *place = c.getProp("this", s->identifier);
                return c.builder->CreateStore(c.codegen(s->expression), place);
            }
            return c.builder->CreateStore(c.codegen(s->expression), v);
        }

        llvm::Value *operator()(Expression *e) {
            return c.codegen(e);
        }

        llvm::Value *operator()(Keyword *b) {}
    } visitor{*this};
    for (auto &st: statements->stmts) {
        std::visit(visitor, *st);
        if (visitor.ret) // Optimization: do not generate code after "return"
            break;
    }
    return visitor.ret;
}

llvm::Value *CodeGenerator::getProp(const std::string &instance, const std::string &field) const {
    auto alloc = (llvm::StructType *) namedValuesTypes.at(instance);
    auto val = (llvm::Value *) namedValues.at(instance);
    if (!isInConstructor)
        val = builder->CreateLoad(alloc->getPointerTo(), val);
    while (!classes.at(alloc->getStructName().data()).fields.contains(field)) {
        alloc = (llvm::StructType *) (classes.at(
                classes.at(alloc->getStructName().data()).base->type->toString()).type);
    }
    auto fieldIdx = classes.at(alloc->getStructName().data()).fields.at(field);
    auto address = builder->CreateStructGEP(alloc, val, fieldIdx.idx, instance + "." + field);
    return address;
}

llvm::Value *
CodeGenerator::getProp(llvm::Value *instance, const std::string &field) const {
    auto fieldIdx = classes.at(instance->getType()->getStructName().str()).fields.at(field);
    auto address = builder->CreateStructGEP(instance->getType(), instance, fieldIdx.idx,
                                            instance->getType()->getStructName().str() + "." + field);
    return address;
}

llvm::Value *CodeGenerator::codegen(ClassDeclaration *cd) {
    struct Visitor {
        CodeGenerator &c;

        llvm::Value *operator()(Variable *vd) {
            return nullptr;
        }

        llvm::Value *operator()(Method *vd) {
            return c.codegen(vd);
        }

        llvm::Value *operator()(Constructor *) {
            error("Something wrong: no constructors in AST!!!");
        }
    } visitor(*this);
    if (cd->body->members == nullptr)
        return nullptr;
    for (auto &member: cd->body->members->decls) {
        std::visit(visitor, *member);
    }
    return nullptr;
}

llvm::Value *CodeGenerator::codegenDecls(ClassDeclaration *cd) {
    if (classes.contains(cd->type->toString()))
        return nullptr;
    std::vector<llvm::Type *> vars;
    std::map<std::string, Class::Field> fields;
    size_t methodsNum = 0;
    if (cd->extends != nullptr) { // Inheritance
        codegenDecls(typeToCd[cd->extends->toString()]);
        vars.push_back(classes[cd->extends->toString()].type);
    }
    if (cd->body->members != nullptr) {
        for (auto &member: cd->body->members->decls) {
            if (std::holds_alternative<Variable *>(*member)) {
                auto var = std::get<Variable *>(*member);
                auto type = getLLVMType(var->expression);
                vars.push_back(type);
                fields[var->name] = {vars.size() - 1, var->expression, type};
            } else if (std::holds_alternative<Method *>(*member)) {
                methodsNum++;
            }
        }
    }
    auto vtableType = llvm::ArrayType::get(llvm::Type::getInt64PtrTy(*theContext), methodsNum);
    vars.push_back(vtableType->getPointerTo());
    fields["vtable" + cd->type->toString()] = {vars.size() - 1, nullptr, getLLVMType(cd->type)};

    std::cout << cd->type->toString() << " fields\n";
    for (auto [n, f]: fields) {
        std::cout << n << " " << f.idx << "\n";
    }

    if (NOT_VIRTUAL_CLASSES.contains(cd->type->toString())) {
        classes[cd->type->toString()] = {getLLVMType(cd->type), nullptr, fields};
        return nullptr;
    }
    auto cls = llvm::StructType::create(*theContext, llvm::StringRef(cd->type->toString()));
    cls->setBody(llvm::ArrayRef<llvm::Type *>(vars));
    ClassDeclaration *base = nullptr;
    if (cd->extends != nullptr)
        base = typeToCd[cd->extends->toString()];
    classes[cd->type->toString()] = {cls, base, fields};
    return nullptr;
}

void CodeGenerator::generateVTables(ClassDeclaration *cd) {
    if (NOT_VIRTUAL_CLASSES.contains(cd->type->toString()))
        return;
    auto vtableName = "vtable" + cd->type->toString();
    if (theModule->getNamedGlobal(vtableName))
        return;
    auto &cls = classes.at(cd->type->toString());
    std::vector<llvm::Constant *> &methods = cls.vtable;
    if (cd->extends != nullptr) { // First, add methods of base
        generateVTables(typeToCd[cd->extends->toString()]);
        const auto &baseCls = classes.at(cls.base->type->toString());
        methods.resize(baseCls.methodsOffset.size());
        for (const auto &[name, offset]: baseCls.methodsOffset) {
            std::string metName = // Change last argument ("this" variable) type
                    name.substr(0, name.size() - cd->extends->toString().size() - 1) +
                    cd->type->toString() + "_";
            cls.methodsOffset[metName] = offset;
            methods[offset] = baseCls.vtable[offset];
        }
    }
    if (cd->body->members != nullptr) { // Then methods of derived
        for (const auto &member: cd->body->members->decls) {
            if (std::holds_alternative<Method *>(*member)) {
                auto met = std::get<Method *>(*member);
                if (met->isConstructor)
                    continue;
                std::string metName = met->fullName;
                if (!cls.methodsOffset.contains(metName)) {
                    methods.push_back(theModule->getFunction(metName));
                    cls.methodsOffset[metName] = methods.size() - 1;
                } else { // If base contains this method then change pointer in vtable
                    methods[cls.methodsOffset[metName]] = theModule->getFunction(metName);
                }
            }
        }
    }
    auto ptrType = llvm::Type::getInt64PtrTy(*theContext);
    auto vtableType = llvm::ArrayType::get(ptrType, methods.size());
    theModule->getOrInsertGlobal(vtableName, vtableType);
    auto vtable = theModule->getNamedGlobal(vtableName);
    vtable->setInitializer(llvm::ConstantArray::get(vtableType, methods));
}

llvm::Value *CodeGenerator::codegen(Program *p) {
    for (const auto &cd: p->classDecls->decls) { // Just initializing this map for convenient getting classDecls
        typeToCd[cd->type->toString()] = cd;
    }
    for (auto &cd: p->classDecls->decls) { // Generating llvm types
        codegenDecls(cd);
    }
    for (auto &cd: p->classDecls->decls) { // Generating functions headers
        if (cd->body->members != nullptr) {
            for (const auto &m: cd->body->members->decls) {
                if (std::holds_alternative<Method *>(*m)) {
                    codegenFuncDecl(std::get<Method *>(*m));
                }
            }
        }
    }
    for (auto &cd: p->classDecls->decls) { // Generating virtual tables
        generateVTables(cd);
    }
    for (auto &cd: p->classDecls->decls) { // Generating function bodies
        codegen(cd);
    }
    generateMain();
    return nullptr;
}

llvm::Value *CodeGenerator::generateMain() {
    auto main = theModule->getFunction("Main_");
    if (main == nullptr) {
        error("No entry point");
    }
    llvm::FunctionType *FT;
    FT = llvm::FunctionType::get(llvm::Type::getInt32Ty(*theContext), false);
    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "main", theModule.get());
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(*theContext, "entry", F);
    builder->SetInsertPoint(BB);
//    auto mainObj = createEntryBlockAlloca(F, "Main", classes["Main"].type);
//    auto val = builder->CreateLoad(classes["Main"].type, mainObj);
    builder->CreateCall(main, llvm::ArrayRef<llvm::Value *>({/*val*/}));
    builder->CreateRet(llvm::ConstantInt::get(*theContext, llvm::APInt(32, 0)));
    return nullptr;
}

void CodeGenerator::error(const std::string &s) {
    std::cerr << s;// << " " << span.toString();
    exit(-1);
}

CodeGenerator::CodeGenerator() {
    // Open a new context and module.
    theContext = std::make_unique<llvm::LLVMContext>();
    theModule = std::make_unique<llvm::Module>("OplLLVM", *theContext);

    // Create a new builder for the module.
    builder = std::make_unique<llvm::IRBuilder<>>(*theContext);
}

void CodeGenerator::generateCode(Program *p) {
    codegen(p);
    generateIRCodeToFile("a.ll");
    /*auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();
    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target) {
        errs() << Error;
        return;
    }
    auto CPU = "generic";
    auto Features = "";
    TargetOptions opt;
    auto RM = std::optional<Reloc::Model>();
    auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
    theModule->setDataLayout(TargetMachine->createDataLayout());
    theModule->setTargetTriple(TargetTriple);
    auto Filename = "output.o";
    std::error_code EC;
    raw_fd_ostream dest(Filename, EC, sys::fs::OF_None);

    if (EC) {
        errs() << "Could not open file: " << EC.message();
        return;
    }
    legacy::PassManager pass;
    auto FileType = CodeGenFileType::CGFT_ObjectFile;

    if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        errs() << "TargetMachine can't emit a file of this type";
        return;
    }

    pass.run(*theModule);
    dest.flush();*/
}

void CodeGenerator::generateIRCodeToFile(const std::string &filename) {
    std::error_code errorCode;
    llvm::raw_fd_ostream outLL(filename, errorCode);
    theModule->print(outLL, nullptr);
//    theModule->print(llvm::outs(), nullptr);
}

/// createEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.  This is used for mutable variables etc.
llvm::AllocaInst *
CodeGenerator::createEntryBlockAlloca(llvm::Function *TheFunction, const std::string &VarName, llvm::Type *type) {
    llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(type, nullptr, VarName);
}

void CodeGenerator::addObjects(Program *lib) {
    for (const auto &cd: lib->classDecls->decls) { // Just initializing this map for convenient getting classDecls
        typeToCd[cd->type->toString()] = cd;
    }
    for (const auto &cd: lib->classDecls->decls) { // Generating llvm types
        codegenDecls(cd);
    }
    for (const auto &cd: lib->classDecls->decls) { // Generating functions headers
        if (cd->body->members != nullptr) {
            for (const auto &met: cd->body->members->decls) {
                if (std::holds_alternative<Method *>(*met)) {
                    codegenFuncDecl(std::get<Method *>(*met));
                }
            }
        }
    }
    for (auto &cd: lib->classDecls->decls) { // Generating virtual tables
        generateVTables(cd);
    }
}

llvm::Type *CodeGenerator::getLLVMType(Type *type) {
    auto str = type->toString();
    if (str == "Integer")
        return llvm::Type::getInt64Ty(*theContext);
    else if (str == "Boolean")
        return llvm::Type::getInt1Ty(*theContext);
    else if (str == "Real")
        return llvm::Type::getDoubleTy(*theContext);
    return classes[str].type;
}

llvm::Type *CodeGenerator::getLLVMType(Expression *e) {
    struct Visitor {
        CodeGenerator &c;

        llvm::Type *operator()(IntegerLit *v) { return llvm::Type::getInt64Ty(*c.theContext); }

        llvm::Type *operator()(RealLit *v) { return llvm::Type::getDoubleTy(*c.theContext); }

        llvm::Type *operator()(BooleanLit *v) { return llvm::Type::getInt1Ty(*c.theContext); }

        llvm::Type *operator()(const std::pair<std::string, Span> &p) { // Variable case
            warning("Instantiating vars with other vars is not implemented yet: " + p.second.toString());
            const llvm::AllocaInst *v = c.namedValues.at(p.first);
//            if (v == nullptr) {
//                c.classes.at()
//            }
//            if (v == nullptr) {
//                llvm::Value* place = c.getProp("this", p.first);
//                return c.builder->CreateStore(c.codegen(), place);
//                error("Variable " + s->identifier + " not found");
//            }
            return v->getAllocatedType();
        }

        llvm::Type *operator()(MethodCall *v) {
//            warning("Instantiating vars with method calls is not implemented yet: " + v->span.toString());
            return c.getLLVMType(v->returnType);
//            return c.theModule->getFunction(v->fullname)->getReturnType();
        }

        llvm::Type *operator()(Keyword *v) { // "this"
            error("Instantiating vars with other vars is not implemented yet: " + v->span.toString());
        }

        llvm::Type *operator()(CompoundExpression *v) {
//            warning("Instantiating vars with method calls is not implemented yet: " + v->methodCall->span.toString());
            return c.getLLVMType(v->methodCall->returnType);
//            return c.theModule->getFunction(v->methodCall->fullname)->getReturnType();
        }
    } visitor{*this};
    return std::visit(visitor, *e);
}

void CodeGenerator::warning(const std::string &s) {
    std::cerr << s << '\n';
}

std::vector<llvm::Type *> CodeGenerator::extractArgsTypes(Arguments *args) {
    std::vector<llvm::Type *> types;
    for (const auto &arg: args->args) {
        llvm::Type *type = getLLVMType(arg->type);
//        type->print(llvm::outs());
        if (type->isStructTy()) {
            type = type->getPointerTo();
        }
        types.push_back(type);
    }
    return types;
}

