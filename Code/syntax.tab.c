/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "./bison.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "errortype.h"
    #include "bison.h"
    #include "syntax.tab.h"

    #define YYERROR_VERBOSE 1 

    symbol_list* _var_symbol_table_start=NULL;
    symbol_list* _func_symbol_table_start=NULL;

    struct_typedef *_struct_typedef_table_start=NULL;

    void bison_error(const char*);
    
    node* node_con(char*, int);
    void add_child(node*,node*);
    void print_tree(node*, int);
    void free_all(node*);

    extern void translate(node *);

    char* empty="\"empty\"";
    char* cat;
    node* program_node;
    FILE* input_file;
    FILE* output_file;
    extern int yylineno;
    extern char* yytext;
    int yylex(void);
    void yyerror(const char *);  
    int error=1;

#line 103 "./syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    WS = 258,
    INT = 259,
    FLOAT = 260,
    ID = 261,
    SEMI = 262,
    COMMA = 263,
    ASSIGNOP = 264,
    LT = 265,
    LE = 266,
    EQ = 267,
    NE = 268,
    GT = 269,
    GE = 270,
    NOT = 271,
    DOT = 272,
    LP = 273,
    RP = 274,
    LB = 275,
    RB = 276,
    LC = 277,
    RC = 278,
    STAR = 279,
    DIV = 280,
    AND = 281,
    OR = 282,
    PLUS = 283,
    MINUS = 284,
    STRUCT = 285,
    RETURN = 286,
    IF = 287,
    ELSE = 288,
    WHILE = 289,
    TYPE = 290,
    RELOP = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 38 "./bison.y" /* yacc.c:355  */

    struct value val;
    node* _node;

#line 185 "./syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 202 "./syntax.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   296

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    70,    70,    82,    84,    89,    93,    95,   102,   107,
     113,   115,   119,   125,   128,   133,   137,   139,   148,   155,
     160,   164,   166,   171,   174,   179,   187,   189,   197,   204,
     206,   212,   216,   218,   223,   226,   234,   236,   241,   246,
     251,   255,   261,   269,   279,   289,   294,   298,   300,   306,
     308,   312,   319,   323,   331,   337,   343,   349,   356,   362,
     368,   374,   380,   386,   391,   396,   404,   411,   418,   425,
     430,   435,   440,   442,   448
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WS", "INT", "FLOAT", "ID", "SEMI",
  "COMMA", "ASSIGNOP", "LT", "LE", "EQ", "NE", "GT", "GE", "NOT", "DOT",
  "LP", "RP", "LB", "RB", "LC", "RC", "STAR", "DIV", "AND", "OR", "PLUS",
  "MINUS", "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "TYPE", "RELOP",
  "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
# endif

#define YYPACT_NINF -59

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-59)))

#define YYTABLE_NINF -73

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,   116,    54,   -59,     5,   -59,    15,   168,   -59,    -9,
       0,    46,   -59,   -59,   165,   -59,    92,    20,   -59,    64,
       3,    18,    16,     7,   -59,   147,    81,   -59,    43,   -59,
      51,   149,    65,    43,    48,   -59,   149,    70,    87,    98,
     -59,   -59,    85,    78,   -59,    60,   112,   126,   -59,   -59,
     106,   -59,    23,   -59,   132,   -59,   -59,   119,   189,   189,
     189,   189,   133,   145,   -59,   113,    78,   104,   189,   -59,
     149,   -59,   182,   -59,   260,   195,   128,   118,   189,   189,
     -59,   -59,   -59,   189,   160,   189,   189,   189,   189,   189,
     189,   189,   189,   247,   -59,   -59,   153,   148,   -59,   -59,
     208,   221,   247,   -59,   234,    34,    34,    34,    34,   128,
     128,   247,   189,   -59,    86,    86,   -59,   -59,   143,   -59,
      86,   -59
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,     0,    14,     0,     2,     0,     0,    15,    23,
      22,     0,    18,     1,    10,     4,    26,    24,     8,     0,
      11,     0,     0,     0,     7,     0,     0,    36,     0,     9,
      47,     0,     0,     0,    16,    28,     0,     0,    31,    26,
      24,    12,     0,     0,    26,    52,     0,    50,    17,    45,
      33,    27,     0,    25,    36,    70,    71,    69,     0,     0,
       0,     0,     0,     0,    40,     0,     0,     0,     0,    48,
       0,    30,     0,    72,    64,     0,    63,     0,     0,     0,
      35,    37,    39,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    53,    51,    66,    74,     0,    62,    41,
       0,     0,    54,    68,     0,    58,    59,    55,    56,    60,
      61,    57,     0,    65,     0,     0,    67,    73,    42,    44,
       0,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -59,   -59,   178,   -59,   167,    12,   -59,   -59,   -59,   -27,
     -59,   150,   -59,   164,   131,   -17,   163,   -59,   129,   -59,
     -58,    91
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    19,    31,     8,    11,    12,    20,
      21,    37,    38,    64,    65,    66,    32,    33,    46,    47,
      67,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      74,    75,    76,    77,    45,    13,    -5,     1,    34,    50,
      93,    25,     7,   -21,    96,    -5,    14,    30,     7,    27,
     100,   101,   -19,    26,    34,   102,    35,   104,   105,   106,
     107,   108,   109,   110,   111,    36,     2,     2,    23,   -46,
      28,     3,     3,    45,    30,     2,     2,   -46,   -46,   -46,
       3,     3,   -16,     2,    96,     9,   -34,   -16,     3,   -46,
      10,   -46,    90,    91,    36,   -46,   -46,   -32,    22,    68,
      92,    24,   -46,     2,   -46,   -46,   -20,   -46,     3,    54,
      26,   -49,    55,    56,    57,    42,   -49,    54,    48,    51,
      55,    56,    57,   -29,    58,    52,    59,   118,   119,   -13,
      28,   -38,    58,   121,    59,   -13,    53,    60,    28,    61,
      62,    82,    63,    83,   -29,    60,    -3,    61,    62,    69,
      63,    84,   -16,   -16,    85,    99,    26,    83,    86,    87,
      88,    89,    90,    91,    70,    84,    80,    72,    85,   -72,
      92,   -72,    86,    87,    88,    89,    90,    91,    39,   -72,
      44,    78,   -72,    40,    92,    40,   -72,   -72,   -72,   -72,
     -72,   112,    83,    79,    92,    -6,   103,   113,   -72,    16,
      84,   -16,   -16,    85,    17,    18,   120,    86,    87,    88,
      89,    90,    91,    73,    15,    29,    55,    56,    57,    92,
      73,    43,    41,    55,    56,    57,    49,    81,    58,    94,
      59,    95,    71,   117,    83,    58,     0,    59,     0,     0,
       0,    60,    84,     0,    98,    85,     0,    83,    60,    86,
      87,    88,    89,    90,    91,    84,     0,   114,    85,     0,
      83,    92,    86,    87,    88,    89,    90,    91,    84,     0,
     115,    85,     0,    83,    92,    86,    87,    88,    89,    90,
      91,    84,     0,     0,    85,   116,    83,    92,    86,    87,
      88,    89,    90,    91,    84,     0,     0,    85,     0,     0,
      92,    86,    87,    88,    89,    90,    91,    84,     0,     0,
      85,     0,     0,    92,    86,    87,    88,    89,    90,    91,
       0,     0,     0,     0,     0,     0,    92
};

static const yytype_int8 yycheck[] =
{
      58,    59,    60,    61,    31,     0,     0,     1,     1,    36,
      68,     8,     0,    22,    72,     0,     1,     1,     6,     1,
      78,    79,    22,    20,     1,    83,    19,    85,    86,    87,
      88,    89,    90,    91,    92,    23,    30,    30,    18,    23,
      22,    35,    35,    70,     1,    30,    30,     4,     5,     6,
      35,    35,     1,    30,   112,     1,     8,     6,    35,    16,
       6,    18,    28,    29,    52,    22,    23,    19,    22,     9,
      36,     7,    29,    30,    31,    32,    22,    34,    35,     1,
      20,    30,     4,     5,     6,     4,    35,     1,    23,    19,
       4,     5,     6,     1,    16,     8,    18,   114,   115,     7,
      22,    23,    16,   120,    18,     7,    21,    29,    22,    31,
      32,     7,    34,     9,    22,    29,     0,    31,    32,     7,
      34,    17,     6,     7,    20,     7,    20,     9,    24,    25,
      26,    27,    28,    29,     8,    17,    23,    18,    20,     7,
      36,     9,    24,    25,    26,    27,    28,    29,     1,    17,
       1,    18,    20,     6,    36,     6,    24,    25,    26,    27,
      28,     8,     9,    18,    36,     0,     6,    19,    36,     1,
      17,     6,     7,    20,     6,     7,    33,    24,    25,    26,
      27,    28,    29,     1,     6,    21,     4,     5,     6,    36,
       1,    28,    25,     4,     5,     6,    33,    66,    16,    70,
      18,    19,    52,   112,     9,    16,    -1,    18,    -1,    -1,
      -1,    29,    17,    -1,    19,    20,    -1,     9,    29,    24,
      25,    26,    27,    28,    29,    17,    -1,    19,    20,    -1,
       9,    36,    24,    25,    26,    27,    28,    29,    17,    -1,
      19,    20,    -1,     9,    36,    24,    25,    26,    27,    28,
      29,    17,    -1,    -1,    20,    21,     9,    36,    24,    25,
      26,    27,    28,    29,    17,    -1,    -1,    20,    -1,    -1,
      36,    24,    25,    26,    27,    28,    29,    17,    -1,    -1,
      20,    -1,    -1,    36,    24,    25,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    30,    35,    38,    39,    40,    42,    43,     1,
       6,    44,    45,     0,     1,    39,     1,     6,     7,    41,
      46,    47,    22,    18,     7,     8,    20,     1,    22,    50,
       1,    42,    53,    54,     1,    19,    42,    48,    49,     1,
       6,    41,     4,    53,     1,    46,    55,    56,    23,    53,
      46,    19,     8,    21,     1,     4,     5,     6,    16,    18,
      29,    31,    32,    34,    50,    51,    52,    57,     9,     7,
       8,    48,    18,     1,    57,    57,    57,    57,    18,    18,
      23,    51,     7,     9,    17,    20,    24,    25,    26,    27,
      28,    29,    36,    57,    55,    19,    57,    58,    19,     7,
      57,    57,    57,     6,    57,    57,    57,    57,    57,    57,
      57,    57,     8,    19,    19,    19,    21,    58,    52,    52,
      33,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    38,    39,    39,    39,    40,    40,    40,
      40,    41,    41,    41,    42,    42,    42,    43,    43,    44,
      44,    44,    45,    45,    46,    46,    46,    47,    47,    47,
      48,    48,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    52,    52,    52,    52,    53,    53,    53,    54,    54,
      55,    55,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    58,    58
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     0,     1,     3,     2,     3,
       1,     1,     3,     1,     1,     1,     1,     5,     2,     1,
       0,     1,     1,     1,     1,     4,     1,     4,     3,     1,
       3,     1,     1,     2,     1,     4,     1,     2,     0,     2,
       1,     3,     5,     7,     5,     2,     0,     1,     3,     1,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     4,     3,     4,     3,     1,
       1,     1,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 70 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Program", 0);
        add_child((yyval._node),(yyvsp[0]._node));
        program_node=(yyval._node);
        if (error){
            init();
            print_tree((yyval._node),0);
            func((yyval._node));
            translate((yyval._node));
            free_all((yyval._node));
        }
    }
#line 1410 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 82 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1416 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 84 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("ExtDefList", 1);
        add_child((yyval._node),(yyvsp[-1]._node));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1426 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("ExtDefList", 1);
            add_child((yyval._node),node_con(empty,-1));
        }
#line 1435 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 93 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1441 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 95 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("ExtDef", 2);
        add_child((yyval._node),(yyvsp[-2]._node));
        add_child((yyval._node),(yyvsp[-1]._node));
        add_child((yyval._node),node_con("SEMI", -1));
        child_node* start=(yyval._node)->children;
    }
#line 1453 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 102 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("ExtDef", 2);
        add_child((yyval._node),(yyvsp[-1]._node));
        add_child((yyval._node),node_con("SEMI", -1));
    }
#line 1463 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 107 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("ExtDef", 2);
        add_child((yyval._node),(yyvsp[-2]._node));
        add_child((yyval._node),(yyvsp[-1]._node));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1474 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 113 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1480 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 115 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("ExtDecList", 3);
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1489 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 119 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("ExtDecList", 3);
            add_child((yyval._node),(yyvsp[-2]._node));
            add_child((yyval._node),node_con("COMMA", -1));
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1500 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 125 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1506 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 128 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Specifier", 4);
        strcpy(cat,"TYPE: ");
        add_child((yyval._node),node_con(strcat(cat,(yyvsp[0].val).name),-1));
        }
#line 1516 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 133 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Specifier", 4);
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1525 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 137 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1531 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 139 "./bison.y" /* yacc.c:1646  */
    {
                    (yyval._node)=node_con("StructSpecifier", 5);
                    sprintf(cat,"%d^STRUCT",(yyvsp[-4].val).lineno);
                    add_child((yyval._node),node_con(cat,-1));
                    add_child((yyval._node),(yyvsp[-3]._node));
                    add_child((yyval._node),node_con("LC",-1));
                    add_child((yyval._node),(yyvsp[-1]._node));
                    add_child((yyval._node),node_con("RC",-1));
                }
#line 1545 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 148 "./bison.y" /* yacc.c:1646  */
    {
                    (yyval._node)=node_con("StructSpecifier", 5);
                    sprintf(cat,"%d^STRUCT",(yyvsp[-1].val).lineno);
                    add_child((yyval._node),node_con(cat,-1));
                    add_child((yyval._node),(yyvsp[0]._node));
                }
#line 1556 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 155 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("OptTag",19);
            strcpy(cat,"ID: ");
            add_child((yyval._node),node_con(strcat(cat,(yyvsp[0].val).name),-1));
        }
#line 1566 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 160 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("OptTag",19);
            add_child((yyval._node),node_con(empty,-1));
        }
#line 1575 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 164 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1581 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 166 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Tag",18);
            strcpy(cat,"ID: ");
            add_child((yyval._node),node_con(strcat(cat,(yyvsp[0].val).name),-1));
        }
#line 1591 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 171 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1597 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 174 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("VarDec", 6);
            strcpy(cat,"ID: ");
            add_child((yyval._node),node_con(strcat(cat,(yyvsp[0].val).name),-1));
        }
#line 1607 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 179 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("VarDec", 6);
            add_child((yyval._node),((yyvsp[-3]._node)));
            add_child((yyval._node),node_con("LB",-1));
            sprintf(cat,"INT: %d",(yyvsp[-1].val).ival);
            add_child((yyval._node),node_con(cat,-1));
            add_child((yyval._node),node_con("RB",-1));
        }
#line 1620 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 187 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1626 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 189 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("FunDec", 7);
            strcpy(cat,"ID: ");
            add_child((yyval._node),node_con(strcat(cat,(yyvsp[-3].val).name),-1));
            add_child((yyval._node),node_con("LP",-1));
            add_child((yyval._node),(yyvsp[-1]._node));
            add_child((yyval._node),node_con("RP",-1));
        }
#line 1639 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 197 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("FunDec", 7);
            strcpy(cat,"ID: ");
            add_child((yyval._node),node_con(strcat(cat,(yyvsp[-2].val).name),-1));
            add_child((yyval._node),node_con("LP",-1));
            add_child((yyval._node),node_con("RP",-1));
        }
#line 1651 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 204 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1657 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 206 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("VarList", 8);
            add_child((yyval._node),(yyvsp[-2]._node));
            add_child((yyval._node),node_con("COMMA", -1));
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1668 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 212 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("VarList", 8);
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1677 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 216 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1683 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 218 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("ParamDec", 9);
            add_child((yyval._node),(yyvsp[-1]._node));
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1693 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 223 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1699 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 226 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("CompSt", 10);
            sprintf(cat,"%d^LC",(yyvsp[-3].val).lineno);
            add_child((yyval._node),node_con(cat,-1));
            add_child((yyval._node),(yyvsp[-2]._node));
            add_child((yyval._node),(yyvsp[-1]._node));
            add_child((yyval._node),node_con("RC",-1));
        }
#line 1712 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 234 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1718 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 236 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("StmtList", 12);
            add_child((yyval._node),(yyvsp[-1]._node));
            add_child((yyval._node),(yyvsp[0]._node));
            }
#line 1728 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 241 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("StmtList", 12);
            add_child((yyval._node),node_con(empty,-1));
        }
#line 1737 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 246 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Stmt", 13);
            add_child((yyval._node),(yyvsp[-1]._node));
            add_child((yyval._node),node_con("SEMI", -1));
        }
#line 1747 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 251 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Stmt", 13);
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1756 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 255 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Stmt", 13);
            add_child((yyval._node),node_con("RETURN",-1));
            add_child((yyval._node),(yyvsp[-1]._node));
            add_child((yyval._node),node_con("SEMI", -1));
        }
#line 1767 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 261 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Stmt", 13);
            add_child((yyval._node),node_con("IF",-1));
            add_child((yyval._node),node_con("LP",-1));
            add_child((yyval._node),(yyvsp[-2]._node));
            add_child((yyval._node),node_con("RP",-1));
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1780 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 269 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Stmt", 13);
            add_child((yyval._node),node_con("IF",-1));
            add_child((yyval._node),node_con("LP",-1));
            add_child((yyval._node),(yyvsp[-4]._node));
            add_child((yyval._node),node_con("RP",-1));
            add_child((yyval._node),(yyvsp[-2]._node));
            add_child((yyval._node),node_con("ELSE",-1));
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1795 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 279 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Stmt", 13);
            add_child((yyval._node),node_con("WHILE",-1));
            add_child((yyval._node),node_con("LP",-1));
            add_child((yyval._node),(yyvsp[-2]._node));
            add_child((yyval._node),node_con("RP",-1));
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1808 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 289 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("DefList", 11);
            add_child((yyval._node),(yyvsp[-1]._node));
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1818 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 294 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("DefList", 11);
            add_child((yyval._node),node_con(empty,-1));
        }
#line 1827 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 298 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1833 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 300 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Def", 14);
            add_child((yyval._node),(yyvsp[-2]._node));
            add_child((yyval._node),(yyvsp[-1]._node));
            add_child((yyval._node),node_con("SEMI", -1));
        }
#line 1844 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 306 "./bison.y" /* yacc.c:1646  */
    {;}
#line 1850 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 308 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("DecList",17);
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1859 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 312 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("DecList",17);
            add_child((yyval._node),(yyvsp[-2]._node));
            add_child((yyval._node),node_con("COMMA", -1));
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1870 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 319 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Dec", 20);
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1879 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 323 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Dec", 20);
            add_child((yyval._node),(yyvsp[-2]._node));
            add_child((yyval._node),node_con("ASSIGNOP", -1));
            add_child((yyval._node),(yyvsp[0]._node));
        }
#line 1890 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 331 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),(yyvsp[-2]._node));
        add_child((yyval._node),node_con("ASSIGNOP", -2));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1901 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 337 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),(yyvsp[-2]._node));
        add_child((yyval._node),node_con("AND",-3));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1912 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 343 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),(yyvsp[-2]._node));
        add_child((yyval._node),node_con("OR",-3));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1923 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 349 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),(yyvsp[-2]._node));
        strcpy(cat,"RELOP: ");
        add_child((yyval._node),node_con(strcat(cat,(yyvsp[-1].val).name),-3));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1935 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 356 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),(yyvsp[-2]._node));
        add_child((yyval._node),node_con("STAR", -4));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1946 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 362 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),(yyvsp[-2]._node));
        add_child((yyval._node),node_con("DIV", -4));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1957 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 368 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),(yyvsp[-2]._node));
        add_child((yyval._node),node_con("PLUS", -4));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1968 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 374 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),(yyvsp[-2]._node));
        add_child((yyval._node),node_con("MINUS", -4));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 1979 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 380 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),node_con("LP",-1));
        add_child((yyval._node),(yyvsp[-1]._node));
        add_child((yyval._node),node_con("RP",-1));
    }
#line 1990 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 386 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),node_con("MINUS", -1));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 2000 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 391 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),node_con("NOT", -3));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 2010 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 396 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        strcpy(cat,"ID: ");
        add_child((yyval._node),node_con(strcat(cat,(yyvsp[-3].val).name),-1));
        add_child((yyval._node),node_con("LP",-1));
        add_child((yyval._node),(yyvsp[-1]._node));
        add_child((yyval._node),node_con("RP",-1));
    }
#line 2023 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 404 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        strcpy(cat,"ID: ");
        add_child((yyval._node),node_con(strcat(cat,(yyvsp[-2].val).name),-1));
        add_child((yyval._node),node_con("LP",-1));
        add_child((yyval._node),node_con("RP",-1));
    }
#line 2035 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 411 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Exp", 15);
        add_child((yyval._node),(yyvsp[-3]._node));
        add_child((yyval._node),node_con("LB",-1));
        add_child((yyval._node),(yyvsp[-1]._node));
        add_child((yyval._node),node_con("RB",-1));
    }
#line 2047 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 418 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Exp", 15);
            add_child((yyval._node),(yyvsp[-2]._node));
            add_child((yyval._node),node_con("DOT",-5));
            strcpy(cat,"ID: ");
            add_child((yyval._node),node_con(strcat(cat,(yyvsp[0].val).name),-1));
    }
#line 2059 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 425 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Exp", 15);
            strcpy(cat,"ID: ");
            add_child((yyval._node),node_con(strcat(cat,(yyvsp[0].val).name),-1));
    }
#line 2069 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 430 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Exp", 15);
            sprintf(cat,"INT: %d",yylval.val.ival);
            add_child((yyval._node),node_con(cat,-6));
        }
#line 2079 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 435 "./bison.y" /* yacc.c:1646  */
    {
            (yyval._node)=node_con("Exp", 15);
            sprintf(cat,"FLOAT: %f",(yyvsp[0].val).fval);
            add_child((yyval._node),node_con(cat,-7));
        }
#line 2089 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 440 "./bison.y" /* yacc.c:1646  */
    {;}
#line 2095 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 442 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Args",16);
        add_child((yyval._node),(yyvsp[-2]._node));
        add_child((yyval._node),node_con("COMMA", -1));
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 2106 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 448 "./bison.y" /* yacc.c:1646  */
    {
        (yyval._node)=node_con("Args",16);
        add_child((yyval._node),(yyvsp[0]._node));
    }
#line 2115 "./syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2119 "./syntax.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 454 "./bison.y" /* yacc.c:1906  */


//void print_tree()

