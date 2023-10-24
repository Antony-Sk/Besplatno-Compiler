%{
    #include "parser.h"
    #include "ast.h"
    #include <iostream>
    Program *program;
%}

%union value {
  Program* prog;
  ClassDeclarations* cds;
  ClassDeclaration* cd;
  ClassBody* cb;
  MemberDeclarations* mds;
  MemberDeclaration* md;
  ConstructorDeclaration* cstrd;
  MethodDeclaration* metd;
  VariableDeclaration* vard;
  VariableDefinition* vardef;
  Arguments* argsd;
  Argument* argd;
  Statements* sttms;
  Assignment* assgn;
  IfStatement* ifst;
  ReturnStatement* rtst;
  WhileStatement* wlst;
  Statement* sttm;
  CompoundExpression* cexp;
  Expression* exp;
  MethodCall* metcall;
  ConstructorCall* cstcall;
  Expressions* exps;
  Keyword* keyword;
  Delimiter* delimiter;
  Identifier* identifier;
  BooleanLit* booleanLit;
  IntegerLit* integerLit;
  RealLit*    realLit;
  TypeToken* typetk;
  Type* type;
  Types* types;
}

%type <cds>         ClassDeclarations
%type <prog>        Program
%type <cd>          ClassDeclaration
%type <cb>          ClassBody
%type <mds>         MemberDeclarations
%type <md>          MemberDeclaration
%type <cstrd>       ConstructorDeclaration
%type <metd>        MethodDeclaration
%type <vard>        VariableDeclaration
%type <vardef>      VariableDefinition
%type <argsd>       ArgumentDeclarations
%type <argd>        ArgumentDeclaration
%type <sttms>       Statements
%type <assgn>       Assignment
%type <ifst>        IfStatement
%type <rtst>        ReturnStatement
%type <wlst>        WhileStatement
%type <sttm>        Statement
%type <cexp>        CompoundExpression
%type <exp>         Expression
%type <metcall>     MethodCall
%type <cstcall>     ConstructorCall
%type <exps>        Expressions
%type <exp>         Relation
%type <typetk>      TypeToken
%type <type>        Type
%type <types>       Types

%token <identifier>    IDENTIFIER
%token <keyword>       CLASS
%token <keyword>       IS
%token <keyword>       END
%token <keyword>       METHOD
%token <keyword>       VAR
%token <keyword>       THIS
%token <keyword>       IF
%token <keyword>       THEN
%token <keyword>       ELSE
%token <keyword>       RETURN
%token <keyword>       WHILE
%token <keyword>       LOOP
%token <keyword>       EXTENDS
%token <delimiter>     LBRACE   // {
%token <delimiter>     RBRACE   // }
%token <delimiter>     LPAREN   // (
%token <delimiter>     RPAREN   // )
%token <delimiter>     LBRACKET // [
%token <delimiter>     RBRACKET // ]
%token <delimiter>     COMMA    // ,
%token <delimiter>     DOT      // .
%token <delimiter>     COLON
%token <delimiter>     ASSIGNMENTOPERATOR
%token <booleanLit>    BOOLLITERAL
%token <integerLit>    INTEGERLITERAL
%token <realLit>       REALLITERAL
%token <typetk>        REAL
%token <typetk>        INTEGER
%token <typetk>        BOOLEAN
%token <typetk>        ARRAY

%start                 Program

%%

Program
    : ClassDeclarations {  $$ = program = new Program($1); }
    ;

ClassDeclarations
    : ClassDeclaration                   { $$ = new ClassDeclarations($1);  }
    | ClassDeclaration ClassDeclarations { $$ = $2->add($1); }
    ;

ClassDeclaration
    : CLASS Type IS ClassBody END              { $$ = new ClassDeclaration($2, $4, nullptr); }
    | CLASS Type EXTENDS Type IS ClassBody END { $$ = new ClassDeclaration($2, $6, $4); }
    ;

ClassBody
    :                    { $$ = new ClassBody(nullptr); }
    | MemberDeclarations { $$ = new ClassBody($1); }
    ;

MemberDeclarations
    : MemberDeclaration                    { $$ = new MemberDeclarations($1); }
    | MemberDeclarations MemberDeclaration { $$ = $1->add($2); }
    ;

MemberDeclaration
    : VariableDefinition     { auto t = new MemberDeclaration(); *t = $1; $$ = t; }
    | VariableDeclaration    { auto t = new MemberDeclaration(); *t = $1; $$ = t; }
    | MethodDeclaration      { auto t = new MemberDeclaration(); *t = $1; $$ = t; }
    | ConstructorDeclaration { auto t = new MemberDeclaration(); *t = $1; $$ = t; }
    ;

VariableDeclaration
    : VAR IDENTIFIER COLON Expression { $$ = new VariableDeclaration($2->identifier, $4); }
    ;

VariableDefinition
    : VAR IDENTIFIER COLON Type { $$ = new VariableDefinition($2->identifier, $4); }
    ;

ConstructorDeclaration
    : THIS LPAREN ArgumentDeclarations RPAREN IS Statements END { $$ = new ConstructorDeclaration($3, $6); }

MethodDeclaration
    : METHOD IDENTIFIER LPAREN ArgumentDeclarations RPAREN COLON Type IS Statements END { $$ = new MethodDeclaration($2->identifier, $4, $7, $9); }
    ;

ArgumentDeclarations
    :                                                { $$ = new Arguments(); }
    | ArgumentDeclaration                            { $$ = new Arguments($1); }
    | ArgumentDeclarations COMMA ArgumentDeclaration { $$ = $1->add($3); }
    ;

ArgumentDeclaration
    : IDENTIFIER COLON Type { $$ = new Argument($1->identifier, $3); }
    ;

Statements
    :                      { $$ = new Statements(); }
    | Statement            { $$ = new Statements($1); }
    | Statements Statement { $$ = $1->add($2); }
    ;

Statement
    : VariableDefinition  { auto t = new Statement(); *t = $1; $$ = t; }
    | VariableDeclaration { auto t = new Statement(); *t = $1; $$ = t; }
    | Assignment          { auto t = new Statement(); *t = $1; $$ = t; }
    | IfStatement         { auto t = new Statement(); *t = $1; $$ = t; }
    | WhileStatement      { auto t = new Statement(); *t = $1; $$ = t; }
    | ReturnStatement     { auto t = new Statement(); *t = $1; $$ = t; }
    | Expression          { auto t = new Statement(); *t = $1; $$ = t; }
    ;

Assignment
    : IDENTIFIER ASSIGNMENTOPERATOR Expression { $$ = new Assignment($1->identifier, $3); }
    ;

IfStatement
    : IF Relation THEN Statements END                 { $$ = new IfStatement($2, $4, nullptr); }
    | IF Relation THEN Statements ELSE Statements END { $$ = new IfStatement($2, $4, $6); }
    ;

WhileStatement
    : WHILE Relation LOOP Statements END { $$ = new WhileStatement($2, $4); }
    ;

ReturnStatement
    : RETURN            { $$ = new ReturnStatement(nullptr); }
    | RETURN Expression { $$ = new ReturnStatement($2); }
    ;

Expression
    : INTEGERLITERAL     { auto t = new Expression(); *t = $1; $$ = t; }
    | REALLITERAL        { auto t = new Expression(); *t = $1; $$ = t; }
    | BOOLLITERAL        { auto t = new Expression(); *t = $1; $$ = t; }
    | THIS               { auto t = new Expression(); *t = $1; $$ = t; }
    | IDENTIFIER         { auto t = new Expression(); *t = $1->identifier; $$ = t; }
    | MethodCall         { auto t = new Expression(); *t = $1; $$ = t; }
    | ConstructorCall    { auto t = new Expression(); *t = $1; $$ = t; }
    | CompoundExpression { auto t = new Expression(); *t = $1; $$ = t; }
    ;

CompoundExpression
    : Expression DOT MethodCall { $$ = new CompoundExpression($1, $3); }
    ;

Relation
    : Expression { $$ = $1; }
    ;

ConstructorCall
    : Type LPAREN Expressions RPAREN       { $$ = new ConstructorCall($1, $3); }
    ;

MethodCall
    : IDENTIFIER LPAREN Expressions RPAREN { $$ = new MethodCall($1->identifier, $3); }
    ;

Expressions
    :
    | Expression                   { $$ = new Expressions($1); }
    | Expressions COMMA Expression { $$ = $1->add($3); }
    ;

Type
    : INTEGER                            { $$ = new Type($1, nullptr); }
    | BOOLEAN                            { $$ = new Type($1, nullptr); }
    | REAL                               { $$ = new Type($1, nullptr); }
    | IDENTIFIER                         { $$ = new Type($1->identifier, nullptr); }
    | IDENTIFIER LBRACKET Types RBRACKET { $$ = new Type($1->identifier, $3); }
    ;

Types
    : Type             { $$ = new Types($1); }
    | Types COMMA Type { $$ = $1->add($3); }
    ;
%%

#include "scanner.h"
#include "parser.tab.h"

Scanner scanner;

int yylex(void) {
    Token* t = scanner.get_next_token();
    if (t == nullptr)
        return 0;
    //std::cout << "token: " << t->toString() << '\n';
    return t->code;
}

void yyerror(char *s) {
    fprintf (stderr, "Error: %s on line: %ld, pos: %ld:%ld\n", s, yylval.identifier->span.lineNum + 1, yylval.identifier->span.posBegin + 1, yylval.identifier->span.posEnd + 1);
    exit(-1);
}
