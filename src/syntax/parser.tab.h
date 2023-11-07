/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    CLASS = 259,                   /* CLASS  */
    IS = 260,                      /* IS  */
    END = 261,                     /* END  */
    METHOD = 262,                  /* METHOD  */
    VAR = 263,                     /* VAR  */
    THIS = 264,                    /* THIS  */
    IF = 265,                      /* IF  */
    THEN = 266,                    /* THEN  */
    ELSE = 267,                    /* ELSE  */
    RETURN = 268,                  /* RETURN  */
    WHILE = 269,                   /* WHILE  */
    LOOP = 270,                    /* LOOP  */
    EXTENDS = 271,                 /* EXTENDS  */
    BREAK = 272,                   /* BREAK  */
    LBRACE = 273,                  /* LBRACE  */
    RBRACE = 274,                  /* RBRACE  */
    LPAREN = 275,                  /* LPAREN  */
    RPAREN = 276,                  /* RPAREN  */
    LBRACKET = 277,                /* LBRACKET  */
    RBRACKET = 278,                /* RBRACKET  */
    COMMA = 279,                   /* COMMA  */
    DOT = 280,                     /* DOT  */
    COLON = 281,                   /* COLON  */
    ASSIGNMENTOPERATOR = 282,      /* ASSIGNMENTOPERATOR  */
    BOOLLITERAL = 283,             /* BOOLLITERAL  */
    INTEGERLITERAL = 284,          /* INTEGERLITERAL  */
    REALLITERAL = 285              /* REALLITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
#line 8 "parser.y"
#include "ast.h"
union value
{
#line 8 "parser.y"

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

#line 127 "parser.tab.h"

};
#line 8 "parser.y"
typedef union value YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
