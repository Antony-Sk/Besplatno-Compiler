#include "parser.h"
#include "src/semantic/semAnalyzer.h"
#include "codegen.h"

int main() {
    Parser parser;
    auto program = parser.parse("test");
    auto std = parser.parse("Std.opl");
    Program wholeProgram(new ClassDeclarations());
    wholeProgram.classDecls->decls = std->classDecls->decls;
    for (auto cd: program->classDecls->decls)
        wholeProgram.classDecls->add(cd);
    SemAnalyzer sa(wholeProgram);
    sa.checkTypes();
    CodeGenerator cg;
    cg.addObjects(std);
    cg.generateCode(program);
}
