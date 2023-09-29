#include "lexicalAnalyzer.h"
#include "scanner.h"

int main() {
    LexicalAnalyzer la;
    Scanner scanner;
    Token *t = scanner.get_next_token();
    while (t != nullptr) {
        std::cout << GetStrOfToken(t) << " Line: " << t->span.lineNum << " Pos: " << t->span.posBegin << " " << t->span.posEnd << "\n";
        t = scanner.get_next_token();
    }
}
