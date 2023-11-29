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
#include "astPrinter.h"

//using namespace llvm;

llvm::Value *CodeGenerator::codegen(RealLit *b) {
    return llvm::ConstantFP::get(*theContext, llvm::APFloat((double) b->value));
}

llvm::Value *CodeGenerator::codegen(IntegerLit *b) {
    return llvm::ConstantInt::get(*theContext, llvm::APInt(64, b->value, true));
}

llvm::Value *CodeGenerator::codegen(BooleanLit *b) {
    return llvm::ConstantInt::get(*theContext, llvm::APInt(1, b->value, false)); // todo ???
}

llvm::Value *CodeGenerator::codegen(MethodCall *mc) {
    llvm::Function *callee = theModule->getFunction(mc->fullname);
    if (!callee) {
        error("Unknown function referenced");
    }
    if (callee->arg_size() != mc->arguments->exps.size()) {
        error("Incorrect number of arguments");
    }

    std::vector<llvm::Value *> argsV;
    for (const auto &exp: mc->arguments->exps) {
        argsV.push_back(codegen(exp));
    }
    return builder->CreateCall(callee, argsV, "calltmp");
}

llvm::Value *CodeGenerator::codegen(Expression *e) {
    struct Visitor {
        CodeGenerator *cg;

        llvm::Value *operator()(IntegerLit *v) { return cg->codegen(v); }

        llvm::Value *operator()(RealLit *v) { return cg->codegen(v); }

        llvm::Value *operator()(BooleanLit *v) { return cg->codegen(v); }

        llvm::Value *operator()(const std::pair<std::string, Span> &p) {
            llvm::AllocaInst *v = cg->namedValues[p.first];
            if (v == nullptr) {
//                auto this_ = cg->namedValues["this"];
//                llvm::Value* val = cg->builder->CreateLoad(this_->getAllocatedType(), this_);
                auto val = cg->getProp("this", p.first);
                return cg->builder->CreateLoad(cg->namedValuesTypes[p.first], val, p.first);

//                error("Var " + p.first + " not found");
            }
            return cg->builder->CreateLoad(v->getAllocatedType(), v, p.first.c_str());
        }

        llvm::Value *operator()(MethodCall *v) {
            return cg->codegen(v);
        }

        llvm::Value *operator()(Keyword *) {
            return cg->namedValues["this"];
        }

        llvm::Value *operator()(CompoundExpression *v) {
            // todo: add "this" var
//            auto oldVal = cg->namedValues["this"];
//            llvm::AllocaInst *var = cg->createEntryBlockAlloca(cg->builder->GetInsertBlock()->getParent(), "this",
//                                                         llvm::Type::getInt64Ty(*cg->theContext));
//            cg->builder->CreateStore(cg->codegen(v->expression), var);
//            cg->namedValues["this"] = var;
            auto ret = cg->codegen(v->methodCall);
//            if (oldVal != nullptr)
//                cg->builder->CreateStore(oldVal, var);
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
//    namedValues.clear();

int i = 0;
    for (auto &Arg: F->args()) {
        llvm::AllocaInst *arg = createEntryBlockAlloca(F, Arg.getName().str(), Arg.getType());
        builder->CreateStore(&Arg, arg);
        namedValues[Arg.getName().str()] = arg;
        namedValuesTypes[Arg.getName().str()] = getLLVMType(m->arguments->args[i++]->type);
    }
    llvm::AllocaInst* obj;
    if (classes.contains(m->name)) { // constructor
        obj = namedValues["this"] = createEntryBlockAlloca(F, "this", getLLVMType(m->returnType));
        namedValuesTypes["this"] = obj->getAllocatedType();
        for (const auto &[name, var]: classes[m->name].fields){
//            namedValues[name] = createEntryBlockAlloca(builder->GetInsertBlock()->getParent(), name, getLLVMType(var));
            builder->CreateStore(codegen(var), getProp("this", name));
        }
    }
    if (llvm::Value *RetVal = codegen(m->body)) {
        verifyFunction(*F);
    }
    if (classes.contains(m->name)) { // constructor
        builder->CreateRet(builder->CreateLoad(getLLVMType(m->returnType), obj));
    }
    return F;
}

llvm::Value *CodeGenerator::codegen(Statements *statements) {
    if (statements == nullptr)
        return nullptr;
    llvm::Value *ret = nullptr;
    struct Visitor {
        CodeGenerator &c;

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
            // Convert condition to a bool by comparing non-equal to 0.0.
            CondV = c.builder->CreateICmpNE(CondV, llvm::ConstantInt::get(*c.theContext, llvm::APInt(64, 0)), "ifcond");
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
            if (!ThenV) { // todo
                return nullptr;
            }
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

            c.builder->CreateBr(MergeBB);
            // codegen of 'Else' can change the current block, update ElseBB for the PHI.
            ElseBB = c.builder->GetInsertBlock();
            // Emit merge block.
            TheFunction->insert(TheFunction->end(), MergeBB);
            c.builder->SetInsertPoint(MergeBB);
//            PHINode *PN = c.builder->CreatePHI(ThenV->getType(), 2, "iftmp");
//
//            PN->addIncoming(ThenV, ThenBB);
//            if (ElseV != nullptr)
//                PN->addIncoming(ElseV, ElseBB);
            return nullptr;
        }

        llvm::Value *operator()(WhileStatement *s) {
            // Emit the start code first, without 'variable' in scope.
            llvm::Value *StartVal = c.codegen(s->relation);
            if (!StartVal)
                return nullptr;
            // Make the new basic block for the loop header, inserting after current
            // block.
            llvm::Function *TheFunction = c.builder->GetInsertBlock()->getParent();
//            llvm::BasicBlock *PreheaderBB = c.builder->GetInsertBlock();
            llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(*c.theContext, "loop", TheFunction);

            // Insert an explicit fall through from the current block to the LoopBB.
            c.builder->CreateBr(LoopBB);
            // Start insertion in LoopBB.
            c.builder->SetInsertPoint(LoopBB);

            c.codegen(s->statement);
            // Compute the end condition.
            llvm::Value *EndCond = c.codegen(s->relation);
            // Convert condition to a bool by comparing non-equal to 0.0.
            EndCond = c.builder->CreateICmpNE(EndCond, llvm::ConstantInt::get(*c.theContext, llvm::APInt(64, 0)), "loopcond");
            // Create the "after loop" block and insert it.
            llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(*c.theContext, "afterloop", TheFunction);

            // Insert the conditional branch into the end of LoopEndBB.
            c.builder->CreateCondBr(EndCond, LoopBB, AfterBB);
            c.builder->SetInsertPoint(AfterBB);
            return llvm::Constant::getNullValue(llvm::Type::getDoubleTy(*c.theContext));
        }

        llvm::Value *operator()(ReturnStatement *s) {
            return c.builder->CreateRet(c.codegen(s->expression));
        }

        llvm::Value *operator()(Assignment *s) {
            llvm::AllocaInst *v = c.namedValues[s->identifier];
            if (v == nullptr) {
//                llvm::AllocaInst* this_ = c.namedValues["this"];
//
//                llvm::Value* val = c.builder->CreateLoad(this_->getAllocatedType(), this_);
                //std::cerr << val->getType()->getStructName().str() << '\n';
                llvm::Value* place = c.getProp("this", s->identifier);
                return c.builder->CreateStore(c.codegen(s->expression), place);
//                error("Variable " + s->identifier + " not found");
            }
            return c.builder->CreateStore(c.codegen(s->expression), v);
        }

        llvm::Value *operator()(Expression *e) {
            return c.codegen(e);
        }

        llvm::Value *operator()(Keyword *b) {
        }
    } visitor{*this};
    for (auto &st: statements->stmts) {
        ret = std::visit(visitor, *st);
    }
//    if (ret == nullptr) {
//        error("No return statement");
//    }
    return ret;
}

llvm::Value *CodeGenerator::getProp(const std::string &instance, const std::string &field) const {
    auto alloc = (llvm::StructType*)namedValuesTypes.at(instance);
//    auto val = builder->CreateLoad(alloc, namedValues[instance], "p_this");
    bool b = alloc->isStructTy();
//    auto cls = alloc->getContainedType(0);
    std::string name = alloc->getStructName().data();
//    name = name.substr(0, name.size() - 2);
    auto fields = classes.at(name).fields;
    auto fieldIdx = std::distance(fields.begin(), fields.find(field));
    auto address = builder->CreateStructGEP(alloc, namedValues.at(instance), fieldIdx);
    return address;//builder->CreateLoad(alloc->getElementType(fieldIdx), address, field);
    return nullptr;
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
    std::vector<llvm::Type *> vars;
    std::map<std::string, Expression*> fields;
    if (cd->body->members == nullptr)
        return nullptr;
    for (auto &member: cd->body->members->decls)
        if (std::holds_alternative<Variable*>(*member)) {
            auto var = std::get<Variable *>(*member);
            auto type = getLLVMType(var->expression);
            vars.push_back(type);
            fields[var->name] = var->expression;
        }
    cls = llvm::StructType::create(*theContext, llvm::StringRef(cd->type->toString()));
    cls->setBody(llvm::ArrayRef<llvm::Type *>(vars));
    classes[cd->type->toString()] = {cls, fields};
    cls = nullptr;
    return nullptr;
}

llvm::Value *CodeGenerator::codegen(Program *p) {
    for (auto &cd: p->classDecls->decls) {
        codegenDecls(cd);
    }
    for (auto &cd: p->classDecls->decls) {
        if (cd->body->members != nullptr)
            for (const auto& m: cd->body->members->decls) {
                if (std::holds_alternative<Method*>(*m)) {
                    codegenFuncDecl(std::get<Method*>(*m));
                }
            }
    }
    for (auto &cd: p->classDecls->decls) {
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
    auto mainObj = createEntryBlockAlloca(F, "Main", classes["Main"].type);
    auto val = builder->CreateLoad(classes["Main"].type, mainObj);
    builder->CreateCall(main, llvm::ArrayRef<llvm::Value*>({val}));
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
llvm::AllocaInst *CodeGenerator::createEntryBlockAlloca(llvm::Function *TheFunction, const std::string &VarName, llvm::Type *type) {
    llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(type, nullptr, VarName);
}

void CodeGenerator::addObjects(Program *lib) {
    for (const auto &cd: lib->classDecls->decls) {
        codegenDecls(cd);
    }
    for (const auto &cd: lib->classDecls->decls) {
        if (cd->body->members == nullptr)
            continue;
        for (const auto &met: cd->body->members->decls) {
            if (std::holds_alternative<Method *>(*met)) {
                codegenFuncDecl(std::get<Method *>(*met));
            }
        }
    }
}

llvm::Type *CodeGenerator::getLLVMType(Type *type) {
    auto str = type->toString();
    if (str == "Integer")
        return llvm::Type::getInt64Ty(*theContext);
    else if (str == "Boolean")
        return llvm::Type::getInt1Ty(*theContext);
    else if (str == "Real")
        return llvm::Type::getBFloatTy(*theContext);
    return classes[str].type;
}

llvm::Type *CodeGenerator::getLLVMType(Expression *e) {
    struct Visitor {
        const CodeGenerator& c;
        llvm::Type *operator()(IntegerLit *v) { return llvm::Type::getInt64Ty(*c.theContext); }

        llvm::Type *operator()(RealLit *v) { return llvm::Type::getFloatTy(*c.theContext); }

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
            warning("Instantiating vars with method calls is not implemented yet: " + v->span.toString());
            return c.theModule->getFunction(v->fullname)->getReturnType();
        }

        llvm::Type *operator()(Keyword *v) { // "this"
            error("Instantiating vars with other vars is not implemented yet: " + v->span.toString());
        }

        llvm::Type *operator()(CompoundExpression *v) {
            error("Instantiating vars with method calls is not implemented yet: " + v->methodCall->span.toString());
        }
    } visitor{*this};
    return std::visit(visitor, *e);
}

void CodeGenerator::warning(const std::string &s) {
    std::cerr << s << '\n';
}

std::vector<llvm::Type *> CodeGenerator::extractArgsTypes(Arguments *args) {
    std::vector<llvm::Type*> types;
    for (const auto& arg: args->args) {
        llvm::Type* type = getLLVMType(arg->type);
//        type->print(llvm::outs());
        if (type->isStructTy()) {
            type = type->getPointerTo();
        }
        types.push_back(type);
    }
    return types;
}

