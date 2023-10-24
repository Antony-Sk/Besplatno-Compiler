#include "parser.h"
#include "ast.h"
#include "astPrinter.h"
extern Program *program;

int main() {
    int t = yyparse();
    while (t) {
        t = yyparse();
    }
    Program* p = program;
    print(p,0);
}
