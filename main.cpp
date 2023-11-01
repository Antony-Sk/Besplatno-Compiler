#include "parser.h"
#include "ast.h"
#include "src/semantic/semAnalyzer.h"
#include "astPrinter.h"

extern Program *program;

int main() {
    int t = yyparse();
    while (t) {
        t = yyparse();
    }
    SemAnalyzer sa;
    sa.initClasses(program);
    print(program);
}
