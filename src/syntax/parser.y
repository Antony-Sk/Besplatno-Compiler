%{
    #include "parser.h"
    #include "ast.h"
    #include <iostream>

    int yylex();
    void yyerror(char *);
    Scanner Parser::scanner;
    Program* Parser::program = nullptr;
%}

%union value {
  Program* prog;
  ClassDeclarations* cds;
  ClassDeclaration* cd;
  ClassBody* cb;
  MemberDeclarations* mds;
  MemberDeclaration* md;
  Constructor* cstrd;
  Method* metd;
  Variable* vard;
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
  Expressions* exps;
  Keyword* keyword;
  Delimiter* delimiter;
  Identifier* identifier;
  BooleanLit* booleanLit;
  IntegerLit* integerLit;
  RealLit*    realLit;
  Type* type;
  Types* types;
}

%type <cds>         ClassDeclarations
%type <prog>        Program
%type <cd>          ClassDeclaration
%type <cb>          ClassBody
%type <mds>         MemberDeclarations
%type <md>          MemberDeclaration
%type <cstrd>       Constructor
%type <metd>        Method
%type <vard>        Variable
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
%type <exps>        Expressions
%type <exp>         Relation
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
%token <keyword>       BREAK
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

%start                 Program

%%

Program
    : ClassDeclarations {  $$ = Parser::program = new Program($1); }
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
    : Variable    { auto t = new MemberDeclaration(); *t = $1; $$ = t; }
    | Method      { auto t = new MemberDeclaration(); *t = $1; $$ = t; }
    | Constructor { auto t = new MemberDeclaration(); *t = $1; $$ = t; }
    ;

Variable
    : VAR IDENTIFIER COLON Expression { $$ = new Variable($2->identifier, $4, $2->span); }
    ;

Constructor
    : THIS LPAREN ArgumentDeclarations RPAREN IS Statements END { $$ = new Constructor($3, $6, $1->span); }

Method
    : METHOD IDENTIFIER LPAREN ArgumentDeclarations RPAREN COLON Type IS Statements END { $$ = new Method($2->identifier, $4, $7, $9, $2->span); }
    ;

ArgumentDeclarations
    :                                                { $$ = new Arguments(); }
    | ArgumentDeclaration                            { $$ = new Arguments($1); }
    | ArgumentDeclarations COMMA ArgumentDeclaration { $$ = $1->add($3); }
    ;

ArgumentDeclaration
    : IDENTIFIER COLON Type { $$ = new Argument($1->identifier, $3, $1->span); }
    ;

Statements
    :                      { $$ = new Statements(); }
    | Statement            { $$ = new Statements($1); }
    | Statements Statement { $$ = $1->add($2); }
    ;

Statement
    : Variable            { auto t = new Statement(); *t = $1; $$ = t; }
    | Assignment          { auto t = new Statement(); *t = $1; $$ = t; }
    | IfStatement         { auto t = new Statement(); *t = $1; $$ = t; }
    | WhileStatement      { auto t = new Statement(); *t = $1; $$ = t; }
    | ReturnStatement     { auto t = new Statement(); *t = $1; $$ = t; }
    | Expression          { auto t = new Statement(); *t = $1; $$ = t; }
    | BREAK               { auto t = new Statement(); *t = $1; $$ = t; }
    ;

Assignment
    : IDENTIFIER ASSIGNMENTOPERATOR Expression { $$ = new Assignment($1->identifier, $3, $1->span); }
    ;

IfStatement
    : IF Relation THEN Statements END                 { $$ = new IfStatement($2, $4, nullptr, $1->span); }
    | IF Relation THEN Statements ELSE Statements END { $$ = new IfStatement($2, $4, $6, $1->span); }
    ;

WhileStatement
    : WHILE Relation LOOP Statements END { $$ = new WhileStatement($2, $4, $1->span); }
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
    | IDENTIFIER         { auto t = new Expression(); *t = std::make_pair<std::string, Span>(std::move($1->identifier), std::move($1->span)); $$ = t; } // variable
    | MethodCall         { auto t = new Expression(); *t = $1; $$ = t; }
    | CompoundExpression { auto t = new Expression(); *t = $1; $$ = t; }
    ;

CompoundExpression
    : Expression DOT MethodCall { $$ = new CompoundExpression($1, $3); }
    ;

Relation
    : Expression { $$ = $1; }
    ;

MethodCall
    : Type LPAREN Expressions RPAREN { $$ = new MethodCall($1, $3, $1->span); }
    ;

Expressions
    :                              { $$ = new Expressions(); } // empty
    | Expression                   { $$ = new Expressions($1); }
    | Expressions COMMA Expression { $$ = $1->add($3); }
    ;

Type
    : IDENTIFIER                         { $$ = new Type($1->identifier, nullptr, $1->span); }
    | IDENTIFIER LBRACKET Types RBRACKET { $$ = new Type($1->identifier, $3, $1->span); }
    ;

Types
    : Type             { $$ = new Types($1); }
    | Types COMMA Type { $$ = $1->add($3); }
    ;
%%

#include "parser.tab.h"

int yylex(void) {
    Token* t = Parser::scanner.get_next_token();
    if (t == nullptr)
        return 0;
    return t->code;
}

void yyerror(char *s) {
    fprintf (stderr, "Error: %s on line: %ld, pos: %ld:%ld\n", s, yylval.identifier->span.lineNum + 1, yylval.identifier->span.posBegin + 1, yylval.identifier->span.posEnd + 1);
    exit(-1);
}
