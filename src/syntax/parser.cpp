/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"

    #include "parser.h"
    #include "ast.h"
    #include <iostream>
    Program *program;

#line 78 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


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
    LBRACE = 272,                  /* LBRACE  */
    RBRACE = 273,                  /* RBRACE  */
    LPAREN = 274,                  /* LPAREN  */
    RPAREN = 275,                  /* RPAREN  */
    LBRACKET = 276,                /* LBRACKET  */
    RBRACKET = 277,                /* RBRACKET  */
    COMMA = 278,                   /* COMMA  */
    DOT = 279,                     /* DOT  */
    COLON = 280,                   /* COLON  */
    ASSIGNMENTOPERATOR = 281,      /* ASSIGNMENTOPERATOR  */
    BOOLLITERAL = 282,             /* BOOLLITERAL  */
    INTEGERLITERAL = 283,          /* INTEGERLITERAL  */
    REALLITERAL = 284,             /* REALLITERAL  */
    REAL = 285,                    /* REAL  */
    INTEGER = 286,                 /* INTEGER  */
    BOOLEAN = 287,                 /* BOOLEAN  */
    ARRAY = 288                    /* ARRAY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
#line 8 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
union value
{
#line 8 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"

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

#line 193 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"

};
#line 8 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
typedef union value YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_CLASS = 4,                      /* CLASS  */
  YYSYMBOL_IS = 5,                         /* IS  */
  YYSYMBOL_END = 6,                        /* END  */
  YYSYMBOL_METHOD = 7,                     /* METHOD  */
  YYSYMBOL_VAR = 8,                        /* VAR  */
  YYSYMBOL_THIS = 9,                       /* THIS  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_THEN = 11,                      /* THEN  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_LOOP = 15,                      /* LOOP  */
  YYSYMBOL_EXTENDS = 16,                   /* EXTENDS  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_LPAREN = 19,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 20,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 21,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 22,                  /* RBRACKET  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_DOT = 24,                       /* DOT  */
  YYSYMBOL_COLON = 25,                     /* COLON  */
  YYSYMBOL_ASSIGNMENTOPERATOR = 26,        /* ASSIGNMENTOPERATOR  */
  YYSYMBOL_BOOLLITERAL = 27,               /* BOOLLITERAL  */
  YYSYMBOL_INTEGERLITERAL = 28,            /* INTEGERLITERAL  */
  YYSYMBOL_REALLITERAL = 29,               /* REALLITERAL  */
  YYSYMBOL_REAL = 30,                      /* REAL  */
  YYSYMBOL_INTEGER = 31,                   /* INTEGER  */
  YYSYMBOL_BOOLEAN = 32,                   /* BOOLEAN  */
  YYSYMBOL_ARRAY = 33,                     /* ARRAY  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_Program = 35,                   /* Program  */
  YYSYMBOL_ClassDeclarations = 36,         /* ClassDeclarations  */
  YYSYMBOL_ClassDeclaration = 37,          /* ClassDeclaration  */
  YYSYMBOL_ClassBody = 38,                 /* ClassBody  */
  YYSYMBOL_MemberDeclarations = 39,        /* MemberDeclarations  */
  YYSYMBOL_MemberDeclaration = 40,         /* MemberDeclaration  */
  YYSYMBOL_Variable = 41,                  /* Variable  */
  YYSYMBOL_Constructor = 42,               /* Constructor  */
  YYSYMBOL_Method = 43,                    /* Method  */
  YYSYMBOL_ArgumentDeclarations = 44,      /* ArgumentDeclarations  */
  YYSYMBOL_ArgumentDeclaration = 45,       /* ArgumentDeclaration  */
  YYSYMBOL_Statements = 46,                /* Statements  */
  YYSYMBOL_Statement = 47,                 /* Statement  */
  YYSYMBOL_Assignment = 48,                /* Assignment  */
  YYSYMBOL_IfStatement = 49,               /* IfStatement  */
  YYSYMBOL_WhileStatement = 50,            /* WhileStatement  */
  YYSYMBOL_ReturnStatement = 51,           /* ReturnStatement  */
  YYSYMBOL_Expression = 52,                /* Expression  */
  YYSYMBOL_CompoundExpression = 53,        /* CompoundExpression  */
  YYSYMBOL_Relation = 54,                  /* Relation  */
  YYSYMBOL_ConstructorCall = 55,           /* ConstructorCall  */
  YYSYMBOL_MethodCall = 56,                /* MethodCall  */
  YYSYMBOL_Expressions = 57,               /* Expressions  */
  YYSYMBOL_Type = 58,                      /* Type  */
  YYSYMBOL_Types = 59                      /* Types  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   188

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  107

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   106,   106,   110,   111,   115,   116,   120,   121,   125,
     126,   130,   131,   132,   136,   140,   143,   147,   148,   149,
     153,   157,   158,   159,   163,   164,   165,   166,   167,   168,
     172,   176,   177,   181,   185,   186,   190,   191,   192,   193,
     194,   195,   196,   197,   201,   205,   209,   213,   217,   218,
     219,   223,   224,   225,   226,   227,   231,   232
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "CLASS",
  "IS", "END", "METHOD", "VAR", "THIS", "IF", "THEN", "ELSE", "RETURN",
  "WHILE", "LOOP", "EXTENDS", "LBRACE", "RBRACE", "LPAREN", "RPAREN",
  "LBRACKET", "RBRACKET", "COMMA", "DOT", "COLON", "ASSIGNMENTOPERATOR",
  "BOOLLITERAL", "INTEGERLITERAL", "REALLITERAL", "REAL", "INTEGER",
  "BOOLEAN", "ARRAY", "$accept", "Program", "ClassDeclarations",
  "ClassDeclaration", "ClassBody", "MemberDeclarations",
  "MemberDeclaration", "Variable", "Constructor", "Method",
  "ArgumentDeclarations", "ArgumentDeclaration", "Statements", "Statement",
  "Assignment", "IfStatement", "WhileStatement", "ReturnStatement",
  "Expression", "CompoundExpression", "Relation", "ConstructorCall",
  "MethodCall", "Expressions", "Type", "Types", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-78)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      13,    15,     9,   -78,    13,    28,   -78,   -78,   -78,    -2,
     -78,   -78,    15,    63,    15,   -78,     7,    31,    50,    36,
      53,    63,   -78,   -78,   -78,   -78,    68,   -78,    15,    55,
      57,    80,   -78,   -78,    63,   -78,    80,    12,    60,     5,
     -78,    83,    44,   -15,   -78,   -78,   -78,   -78,    70,   -78,
     -78,   -78,    79,    15,    94,    80,   -78,    77,    12,   100,
      12,   -78,   156,   -78,    15,    70,    45,    85,   -78,    46,
     -14,    12,    12,    12,   -78,    78,   -78,   -78,   -78,   -78,
     -78,    70,   106,   -78,    12,   -78,    12,    70,   101,    70,
      98,   -78,   -78,   156,    70,    70,   156,   156,    87,    48,
     117,   -78,   -78,   156,   -78,   126,   -78
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     3,    54,    53,    51,    52,     0,
       1,     4,     0,     7,     0,    56,     0,     0,     0,     0,
       0,     8,     9,    11,    13,    12,     0,    55,     0,     0,
       0,    17,     5,    10,     7,    57,    17,     0,     0,     0,
      18,     0,     0,    40,    39,    38,    36,    37,    14,    43,
      42,    41,     0,     0,     0,     0,     6,     0,    48,     0,
      48,    20,    21,    19,     0,    49,     0,     0,    44,     0,
      40,     0,    34,     0,    24,     0,    22,    25,    26,    27,
      28,    29,     0,    47,     0,    46,     0,    45,     0,    35,
       0,    15,    23,    21,    50,    30,    21,    21,     0,     0,
       0,    16,    31,    21,    33,     0,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,   -78,   118,   -78,    90,   -78,   107,   -11,   -78,   -78,
      97,    66,   -77,   -67,   -78,   -78,   -78,   -78,   -36,   -78,
      64,   -78,    82,    91,    -1,   -78
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,    20,    21,    22,    74,    24,    25,
      39,    40,    75,    76,    77,    78,    79,    80,    81,    49,
      88,    50,    51,    66,    52,    16
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       9,    48,    23,    13,    58,    58,    12,    12,    92,    10,
      23,    15,    86,    26,    14,    43,    98,     1,     5,    99,
     100,    44,    65,    23,    65,    54,   105,    35,    55,    27,
      28,    92,    92,    92,    29,    87,    89,    87,    92,    45,
      46,    47,     6,     7,     8,     6,     7,     8,    94,    12,
      95,    70,    61,    30,   102,    31,    18,    44,    71,    32,
     103,    72,    73,    82,    57,    83,    85,    55,    84,    84,
      17,    18,    19,    34,    36,    45,    46,    47,     6,     7,
       8,    70,    37,    38,    91,    53,    18,    44,    71,    56,
      70,    72,    73,   101,    59,    18,    44,    71,    60,    62,
      72,    73,    64,    67,    58,    45,    46,    47,     6,     7,
       8,    93,    96,    97,    45,    46,    47,     6,     7,     8,
      70,    63,    11,   104,    41,    18,    44,    71,    33,    70,
      72,    73,   106,    42,    18,    44,    71,    90,     0,    72,
      73,    68,     0,     0,    45,    46,    47,     6,     7,     8,
       0,    69,     0,    45,    46,    47,     6,     7,     8,    70,
       0,     0,     0,     0,    18,    44,    71,     0,     0,    72,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,    46,    47,     6,     7,     8
};

static const yytype_int8 yycheck[] =
{
       1,    37,    13,     5,    19,    19,    21,    21,    75,     0,
      21,    12,    26,    14,    16,     3,    93,     4,     3,    96,
      97,     9,    58,    34,    60,    20,   103,    28,    23,    22,
      23,    98,    99,   100,     3,    71,    72,    73,   105,    27,
      28,    29,    30,    31,    32,    30,    31,    32,    84,    21,
      86,     3,    53,     3,     6,    19,     8,     9,    10,     6,
      12,    13,    14,    64,    20,    20,    20,    23,    23,    23,
       7,     8,     9,     5,    19,    27,    28,    29,    30,    31,
      32,     3,    25,     3,     6,    25,     8,     9,    10,     6,
       3,    13,    14,     6,    24,     8,     9,    10,    19,     5,
      13,    14,    25,     3,    19,    27,    28,    29,    30,    31,
      32,     5,    11,    15,    27,    28,    29,    30,    31,    32,
       3,    55,     4,     6,    34,     8,     9,    10,    21,     3,
      13,    14,     6,    36,     8,     9,    10,    73,    -1,    13,
      14,    59,    -1,    -1,    27,    28,    29,    30,    31,    32,
      -1,    60,    -1,    27,    28,    29,    30,    31,    32,     3,
      -1,    -1,    -1,    -1,     8,     9,    10,    -1,    -1,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,    35,    36,    37,     3,    30,    31,    32,    58,
       0,    36,    21,     5,    16,    58,    59,     7,     8,     9,
      38,    39,    40,    41,    42,    43,    58,    22,    23,     3,
       3,    19,     6,    40,     5,    58,    19,    25,     3,    44,
      45,    38,    44,     3,     9,    27,    28,    29,    52,    53,
      55,    56,    58,    25,    20,    23,     6,    20,    19,    24,
      19,    58,     5,    45,    25,    52,    57,     3,    56,    57,
       3,    10,    13,    14,    41,    46,    47,    48,    49,    50,
      51,    52,    58,    20,    23,    20,    26,    52,    54,    52,
      54,     6,    47,     5,    52,    52,    11,    15,    46,    46,
      46,     6,     6,    12,     6,    46,     6
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    38,    38,    39,
      39,    40,    40,    40,    41,    42,    43,    44,    44,    44,
      45,    46,    46,    46,    47,    47,    47,    47,    47,    47,
      48,    49,    49,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    53,    54,    55,    56,    57,    57,
      57,    58,    58,    58,    58,    58,    59,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     5,     7,     0,     1,     1,
       2,     1,     1,     1,     4,     7,    10,     0,     1,     3,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       3,     5,     7,     5,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     4,     4,     0,     1,
       3,     1,     1,     1,     1,     4,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ClassDeclarations  */
#line 106 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                        {  (yyval.prog) = program = new Program((yyvsp[0].cds)); }
#line 1316 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 3: /* ClassDeclarations: ClassDeclaration  */
#line 110 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                         { (yyval.cds) = new ClassDeclarations((yyvsp[0].cd));  }
#line 1322 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 4: /* ClassDeclarations: ClassDeclaration ClassDeclarations  */
#line 111 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                         { (yyval.cds) = (yyvsp[0].cds)->add((yyvsp[-1].cd)); }
#line 1328 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 5: /* ClassDeclaration: CLASS Type IS ClassBody END  */
#line 115 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                               { (yyval.cd) = new ClassDeclaration((yyvsp[-3].type), (yyvsp[-1].cb), nullptr); }
#line 1334 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 6: /* ClassDeclaration: CLASS Type EXTENDS Type IS ClassBody END  */
#line 116 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                               { (yyval.cd) = new ClassDeclaration((yyvsp[-5].type), (yyvsp[-1].cb), (yyvsp[-3].type)); }
#line 1340 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 7: /* ClassBody: %empty  */
#line 120 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                         { (yyval.cb) = new ClassBody(nullptr); }
#line 1346 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 8: /* ClassBody: MemberDeclarations  */
#line 121 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                         { (yyval.cb) = new ClassBody((yyvsp[0].mds)); }
#line 1352 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 9: /* MemberDeclarations: MemberDeclaration  */
#line 125 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                           { (yyval.mds) = new MemberDeclarations((yyvsp[0].md)); }
#line 1358 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 10: /* MemberDeclarations: MemberDeclarations MemberDeclaration  */
#line 126 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                           { (yyval.mds) = (yyvsp[-1].mds)->add((yyvsp[0].md)); }
#line 1364 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 11: /* MemberDeclaration: Variable  */
#line 130 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                  { auto t = new MemberDeclaration(); *t = (yyvsp[0].vard); (yyval.md) = t; }
#line 1370 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 12: /* MemberDeclaration: Method  */
#line 131 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                  { auto t = new MemberDeclaration(); *t = (yyvsp[0].metd); (yyval.md) = t; }
#line 1376 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 13: /* MemberDeclaration: Constructor  */
#line 132 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                  { auto t = new MemberDeclaration(); *t = (yyvsp[0].cstrd); (yyval.md) = t; }
#line 1382 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 14: /* Variable: VAR IDENTIFIER COLON Expression  */
#line 136 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                      { (yyval.vard) = new Variable((yyvsp[-2].identifier)->identifier, (yyvsp[0].exp)); }
#line 1388 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 15: /* Constructor: THIS LPAREN ArgumentDeclarations RPAREN IS Statements END  */
#line 140 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                                                { (yyval.cstrd) = new Constructor((yyvsp[-4].argsd), (yyvsp[-1].sttms)); }
#line 1394 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 16: /* Method: METHOD IDENTIFIER LPAREN ArgumentDeclarations RPAREN COLON Type IS Statements END  */
#line 143 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                                                                        { (yyval.metd) = new Method((yyvsp[-8].identifier)->identifier, (yyvsp[-6].argsd), (yyvsp[-3].type), (yyvsp[-1].sttms)); }
#line 1400 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 17: /* ArgumentDeclarations: %empty  */
#line 147 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                                     { (yyval.argsd) = new Arguments(); }
#line 1406 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 18: /* ArgumentDeclarations: ArgumentDeclaration  */
#line 148 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                                     { (yyval.argsd) = new Arguments((yyvsp[0].argd)); }
#line 1412 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 19: /* ArgumentDeclarations: ArgumentDeclarations COMMA ArgumentDeclaration  */
#line 149 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                                     { (yyval.argsd) = (yyvsp[-2].argsd)->add((yyvsp[0].argd)); }
#line 1418 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 20: /* ArgumentDeclaration: IDENTIFIER COLON Type  */
#line 153 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                            { (yyval.argd) = new Argument((yyvsp[-2].identifier)->identifier, (yyvsp[0].type)); }
#line 1424 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 21: /* Statements: %empty  */
#line 157 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                           { (yyval.sttms) = new Statements(); }
#line 1430 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 22: /* Statements: Statement  */
#line 158 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                           { (yyval.sttms) = new Statements((yyvsp[0].sttm)); }
#line 1436 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 23: /* Statements: Statements Statement  */
#line 159 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                           { (yyval.sttms) = (yyvsp[-1].sttms)->add((yyvsp[0].sttm)); }
#line 1442 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 24: /* Statement: Variable  */
#line 163 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                          { auto t = new Statement(); *t = (yyvsp[0].vard); (yyval.sttm) = t; }
#line 1448 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 25: /* Statement: Assignment  */
#line 164 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                          { auto t = new Statement(); *t = (yyvsp[0].assgn); (yyval.sttm) = t; }
#line 1454 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 26: /* Statement: IfStatement  */
#line 165 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                          { auto t = new Statement(); *t = (yyvsp[0].ifst); (yyval.sttm) = t; }
#line 1460 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 27: /* Statement: WhileStatement  */
#line 166 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                          { auto t = new Statement(); *t = (yyvsp[0].wlst); (yyval.sttm) = t; }
#line 1466 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 28: /* Statement: ReturnStatement  */
#line 167 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                          { auto t = new Statement(); *t = (yyvsp[0].rtst); (yyval.sttm) = t; }
#line 1472 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 29: /* Statement: Expression  */
#line 168 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                          { auto t = new Statement(); *t = (yyvsp[0].exp); (yyval.sttm) = t; }
#line 1478 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 30: /* Assignment: IDENTIFIER ASSIGNMENTOPERATOR Expression  */
#line 172 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                               { (yyval.assgn) = new Assignment((yyvsp[-2].identifier)->identifier, (yyvsp[0].exp)); }
#line 1484 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 31: /* IfStatement: IF Relation THEN Statements END  */
#line 176 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                                      { (yyval.ifst) = new IfStatement((yyvsp[-3].exp), (yyvsp[-1].sttms), nullptr); }
#line 1490 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 32: /* IfStatement: IF Relation THEN Statements ELSE Statements END  */
#line 177 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                                      { (yyval.ifst) = new IfStatement((yyvsp[-5].exp), (yyvsp[-3].sttms), (yyvsp[-1].sttms)); }
#line 1496 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 33: /* WhileStatement: WHILE Relation LOOP Statements END  */
#line 181 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                         { (yyval.wlst) = new WhileStatement((yyvsp[-3].exp), (yyvsp[-1].sttms)); }
#line 1502 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 34: /* ReturnStatement: RETURN  */
#line 185 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                        { (yyval.rtst) = new ReturnStatement(nullptr); }
#line 1508 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 35: /* ReturnStatement: RETURN Expression  */
#line 186 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                        { (yyval.rtst) = new ReturnStatement((yyvsp[0].exp)); }
#line 1514 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 36: /* Expression: INTEGERLITERAL  */
#line 190 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                         { auto t = new Expression(); *t = (yyvsp[0].integerLit); (yyval.exp) = t; }
#line 1520 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 37: /* Expression: REALLITERAL  */
#line 191 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                         { auto t = new Expression(); *t = (yyvsp[0].realLit); (yyval.exp) = t; }
#line 1526 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 38: /* Expression: BOOLLITERAL  */
#line 192 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                         { auto t = new Expression(); *t = (yyvsp[0].booleanLit); (yyval.exp) = t; }
#line 1532 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 39: /* Expression: THIS  */
#line 193 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                         { auto t = new Expression(); *t = (yyvsp[0].keyword); (yyval.exp) = t; }
#line 1538 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 40: /* Expression: IDENTIFIER  */
#line 194 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                         { auto t = new Expression(); *t = (yyvsp[0].identifier)->identifier; (yyval.exp) = t; }
#line 1544 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 41: /* Expression: MethodCall  */
#line 195 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                         { auto t = new Expression(); *t = (yyvsp[0].metcall); (yyval.exp) = t; }
#line 1550 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 42: /* Expression: ConstructorCall  */
#line 196 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                         { auto t = new Expression(); *t = (yyvsp[0].cstcall); (yyval.exp) = t; }
#line 1556 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 43: /* Expression: CompoundExpression  */
#line 197 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                         { auto t = new Expression(); *t = (yyvsp[0].cexp); (yyval.exp) = t; }
#line 1562 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 44: /* CompoundExpression: Expression DOT MethodCall  */
#line 201 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                { (yyval.cexp) = new CompoundExpression((yyvsp[-2].exp), (yyvsp[0].metcall)); }
#line 1568 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 45: /* Relation: Expression  */
#line 205 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                 { (yyval.exp) = (yyvsp[0].exp); }
#line 1574 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 46: /* ConstructorCall: Type LPAREN Expressions RPAREN  */
#line 209 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                           { (yyval.cstcall) = new ConstructorCall((yyvsp[-3].type), (yyvsp[-1].exps)); }
#line 1580 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 47: /* MethodCall: IDENTIFIER LPAREN Expressions RPAREN  */
#line 213 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                           { (yyval.metcall) = new MethodCall((yyvsp[-3].identifier)->identifier, (yyvsp[-1].exps)); }
#line 1586 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 48: /* Expressions: %empty  */
#line 217 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                   { (yyval.exps) = nullptr; }
#line 1592 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 49: /* Expressions: Expression  */
#line 218 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                   { (yyval.exps) = new Expressions((yyvsp[0].exp)); }
#line 1598 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 50: /* Expressions: Expressions COMMA Expression  */
#line 219 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                   { (yyval.exps) = (yyvsp[-2].exps)->add((yyvsp[0].exp)); }
#line 1604 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 51: /* Type: INTEGER  */
#line 223 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                         { (yyval.type) = new Type((yyvsp[0].typetk), nullptr); }
#line 1610 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 52: /* Type: BOOLEAN  */
#line 224 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                         { (yyval.type) = new Type((yyvsp[0].typetk), nullptr); }
#line 1616 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 53: /* Type: REAL  */
#line 225 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                         { (yyval.type) = new Type((yyvsp[0].typetk), nullptr); }
#line 1622 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 54: /* Type: IDENTIFIER  */
#line 226 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                         { (yyval.type) = new Type((yyvsp[0].identifier)->identifier, nullptr); }
#line 1628 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 55: /* Type: IDENTIFIER LBRACKET Types RBRACKET  */
#line 227 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                                         { (yyval.type) = new Type((yyvsp[-3].identifier)->identifier, (yyvsp[-1].types)); }
#line 1634 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 56: /* Types: Type  */
#line 231 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                       { (yyval.types) = new Types((yyvsp[0].type)); }
#line 1640 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;

  case 57: /* Types: Types COMMA Type  */
#line 232 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"
                       { (yyval.types) = (yyvsp[-2].types)->add((yyvsp[0].type)); }
#line 1646 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"
    break;


#line 1650 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 234 "/home/anton/Documents/Besplatno-Compiler/src/syntax/parser.y"


#include "scanner.h"
#include "parser.tab.h"

Scanner scanner;

int yylex(void) {
    Token* t = scanner.get_next_token();
    if (t == nullptr)
        return 0;
    return t->code;
}

void yyerror(char *s) {
    fprintf (stderr, "Error: %s on line: %ld, pos: %ld:%ld\n", s, yylval.identifier->span.lineNum + 1, yylval.identifier->span.posBegin + 1, yylval.identifier->span.posEnd + 1);
    exit(-1);
}
