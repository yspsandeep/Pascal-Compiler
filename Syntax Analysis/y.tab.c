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
#line 1 "ERROR404.y"

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

extern FILE *yyin;

typedef struct sym_val {
        char name[100];
        char type[100];
        char value[100];
        bool initial;
} sym_val;

sym_val sym_table[500];

int sym_ptr = 0;

int findInSymTable(char* str) {
        for (int i = 0; i < 500; i++) {
                if (strcmp(sym_table[i].name, str) == 0) {
                        return i;
                }
        }
        return -1;
}

char str_arr[100][100];
int id_list_count = 0;

int findType(char* str) {
    bool hasDot = false;
    bool hasDigit = false;

    for (int i = 0; i < strlen(str); i++) {
        if (isdigit(str[i])) {
            hasDigit = true;
        } else if (str[i] == '.' && !hasDot) {
            hasDot = true;
        } else if (str[i] == '-') {
            continue;
        }
        // else {
        //     return -1;
        // }
    }

    if (hasDigit) {
        if (hasDot) {
            return 2;
        } else {
            return 1;
        }
    } else if (strlen(str) == 1) {
        return 3;
    } else {
        return -1;
    }
}

int isBool(char* str) {
    if (strlen(str) == 1) {
        if (str[0] == '0' || str[0] == '1')
            return 1;
    }
    return -1;
}


#line 143 "y.tab.c"

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
    key_type = 258,                /* key_type  */
    id = 259,                      /* id  */
    num = 260,                     /* num  */
    num_real = 261,                /* num_real  */
    op_plus = 262,                 /* op_plus  */
    op_mult = 263,                 /* op_mult  */
    op_minus = 264,                /* op_minus  */
    op_div = 265,                  /* op_div  */
    op_mod = 266,                  /* op_mod  */
    colon = 267,                   /* colon  */
    open_s = 268,                  /* open_s  */
    close_s = 269,                 /* close_s  */
    open_b = 270,                  /* open_b  */
    close_b = 271,                 /* close_b  */
    lesser = 272,                  /* lesser  */
    greater = 273,                 /* greater  */
    not_equal = 274,               /* not_equal  */
    equal = 275,                   /* equal  */
    quotes = 276,                  /* quotes  */
    dot = 277,                     /* dot  */
    semicolon = 278,               /* semicolon  */
    space = 279,                   /* space  */
    newline = 280,                 /* newline  */
    quoted_string = 281,           /* quoted_string  */
    key_prog = 282,                /* key_prog  */
    key_downto = 283,              /* key_downto  */
    key_var = 284,                 /* key_var  */
    key_to = 285,                  /* key_to  */
    key_if = 286,                  /* key_if  */
    key_else = 287,                /* key_else  */
    key_for = 288,                 /* key_for  */
    key_while = 289,               /* key_while  */
    key_and = 290,                 /* key_and  */
    key_or = 291,                  /* key_or  */
    key_not = 292,                 /* key_not  */
    key_arr = 293,                 /* key_arr  */
    key_of = 294,                  /* key_of  */
    key_begin = 295,               /* key_begin  */
    key_end = 296,                 /* key_end  */
    key_read = 297,                /* key_read  */
    key_write = 298,               /* key_write  */
    key_do = 299,                  /* key_do  */
    key_then = 300,                /* key_then  */
    comma = 301                    /* comma  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define key_type 258
#define id 259
#define num 260
#define num_real 261
#define op_plus 262
#define op_mult 263
#define op_minus 264
#define op_div 265
#define op_mod 266
#define colon 267
#define open_s 268
#define close_s 269
#define open_b 270
#define close_b 271
#define lesser 272
#define greater 273
#define not_equal 274
#define equal 275
#define quotes 276
#define dot 277
#define semicolon 278
#define space 279
#define newline 280
#define quoted_string 281
#define key_prog 282
#define key_downto 283
#define key_var 284
#define key_to 285
#define key_if 286
#define key_else 287
#define key_for 288
#define key_while 289
#define key_and 290
#define key_or 291
#define key_not 292
#define key_arr 293
#define key_of 294
#define key_begin 295
#define key_end 296
#define key_read 297
#define key_write 298
#define key_do 299
#define key_then 300
#define comma 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 73 "ERROR404.y"

        char strval[100];

#line 289 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
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
  YYSYMBOL_key_type = 3,                   /* key_type  */
  YYSYMBOL_id = 4,                         /* id  */
  YYSYMBOL_num = 5,                        /* num  */
  YYSYMBOL_num_real = 6,                   /* num_real  */
  YYSYMBOL_op_plus = 7,                    /* op_plus  */
  YYSYMBOL_op_mult = 8,                    /* op_mult  */
  YYSYMBOL_op_minus = 9,                   /* op_minus  */
  YYSYMBOL_op_div = 10,                    /* op_div  */
  YYSYMBOL_op_mod = 11,                    /* op_mod  */
  YYSYMBOL_colon = 12,                     /* colon  */
  YYSYMBOL_open_s = 13,                    /* open_s  */
  YYSYMBOL_close_s = 14,                   /* close_s  */
  YYSYMBOL_open_b = 15,                    /* open_b  */
  YYSYMBOL_close_b = 16,                   /* close_b  */
  YYSYMBOL_lesser = 17,                    /* lesser  */
  YYSYMBOL_greater = 18,                   /* greater  */
  YYSYMBOL_not_equal = 19,                 /* not_equal  */
  YYSYMBOL_equal = 20,                     /* equal  */
  YYSYMBOL_quotes = 21,                    /* quotes  */
  YYSYMBOL_dot = 22,                       /* dot  */
  YYSYMBOL_semicolon = 23,                 /* semicolon  */
  YYSYMBOL_space = 24,                     /* space  */
  YYSYMBOL_newline = 25,                   /* newline  */
  YYSYMBOL_quoted_string = 26,             /* quoted_string  */
  YYSYMBOL_key_prog = 27,                  /* key_prog  */
  YYSYMBOL_key_downto = 28,                /* key_downto  */
  YYSYMBOL_key_var = 29,                   /* key_var  */
  YYSYMBOL_key_to = 30,                    /* key_to  */
  YYSYMBOL_key_if = 31,                    /* key_if  */
  YYSYMBOL_key_else = 32,                  /* key_else  */
  YYSYMBOL_key_for = 33,                   /* key_for  */
  YYSYMBOL_key_while = 34,                 /* key_while  */
  YYSYMBOL_key_and = 35,                   /* key_and  */
  YYSYMBOL_key_or = 36,                    /* key_or  */
  YYSYMBOL_key_not = 37,                   /* key_not  */
  YYSYMBOL_key_arr = 38,                   /* key_arr  */
  YYSYMBOL_key_of = 39,                    /* key_of  */
  YYSYMBOL_key_begin = 40,                 /* key_begin  */
  YYSYMBOL_key_end = 41,                   /* key_end  */
  YYSYMBOL_key_read = 42,                  /* key_read  */
  YYSYMBOL_key_write = 43,                 /* key_write  */
  YYSYMBOL_key_do = 44,                    /* key_do  */
  YYSYMBOL_key_then = 45,                  /* key_then  */
  YYSYMBOL_comma = 46,                     /* comma  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_valid_prog = 48,                /* valid_prog  */
  YYSYMBOL_newlines_p = 49,                /* newlines_p  */
  YYSYMBOL_spaces_p = 50,                  /* spaces_p  */
  YYSYMBOL_initial_block = 51,             /* initial_block  */
  YYSYMBOL_var_block = 52,                 /* var_block  */
  YYSYMBOL_dec_block = 53,                 /* dec_block  */
  YYSYMBOL_dec_statement = 54,             /* dec_statement  */
  YYSYMBOL_dec_type = 55,                  /* dec_type  */
  YYSYMBOL_id_list = 56,                   /* id_list  */
  YYSYMBOL_final_begin_end_block = 57,     /* final_begin_end_block  */
  YYSYMBOL_begin_end_block = 58,           /* begin_end_block  */
  YYSYMBOL_content = 59,                   /* content  */
  YYSYMBOL_write_statement = 60,           /* write_statement  */
  YYSYMBOL_read_statement = 61,            /* read_statement  */
  YYSYMBOL_array_id = 62,                  /* array_id  */
  YYSYMBOL_assign_statement = 63,          /* assign_statement  */
  YYSYMBOL_assign_statement_ws = 64,       /* assign_statement_ws  */
  YYSYMBOL_exp = 65,                       /* exp  */
  YYSYMBOL_name = 66,                      /* name  */
  YYSYMBOL_for_statement = 67,             /* for_statement  */
  YYSYMBOL_if_statement = 68,              /* if_statement  */
  YYSYMBOL_if_statement_ws = 69,           /* if_statement_ws  */
  YYSYMBOL_if_else_statement = 70,         /* if_else_statement  */
  YYSYMBOL_while_statement = 71            /* while_statement  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   380

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  227

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   301


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   100,   100,   108,   109,   111,   112,   114,   115,   117,
     118,   120,   121,   123,   138,   154,   155,   157,   158,   160,
     162,   162,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   181,   182,
     183,   184,   186,   187,   188,   189,   191,   192,   194,   195,
     197,   226,   256,   289,   321,   353,   385,   417,   432,   446,
     480,   512,   551,   586,   587,   588,   589,   591,   592,   593,
     608,   609,   611,   612,   612,   613,   614,   615,   615,   616,
     618,   619,   621,   622,   624,   625,   626,   627,   630,   631,
     632,   633
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
  "\"end of file\"", "error", "\"invalid token\"", "key_type", "id",
  "num", "num_real", "op_plus", "op_mult", "op_minus", "op_div", "op_mod",
  "colon", "open_s", "close_s", "open_b", "close_b", "lesser", "greater",
  "not_equal", "equal", "quotes", "dot", "semicolon", "space", "newline",
  "quoted_string", "key_prog", "key_downto", "key_var", "key_to", "key_if",
  "key_else", "key_for", "key_while", "key_and", "key_or", "key_not",
  "key_arr", "key_of", "key_begin", "key_end", "key_read", "key_write",
  "key_do", "key_then", "comma", "$accept", "valid_prog", "newlines_p",
  "spaces_p", "initial_block", "var_block", "dec_block", "dec_statement",
  "dec_type", "id_list", "final_begin_end_block", "begin_end_block",
  "content", "write_statement", "read_statement", "array_id",
  "assign_statement", "assign_statement_ws", "exp", "name",
  "for_statement", "if_statement", "if_statement_ws", "if_else_statement",
  "while_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-157)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      43,   -21,   -13,    34,    23,   -21,  -157,    69,  -157,    72,
      38,    45,    70,    96,   -21,   -21,   -21,    81,  -157,    90,
      83,    -1,  -157,  -157,  -157,    83,   110,  -157,   -21,  -157,
      93,    74,  -157,    71,     8,    83,    12,     4,    83,     4,
     101,   107,    83,   -21,   -21,   -21,   100,   -21,   -21,     2,
     -21,   -21,  -157,    83,   104,   117,  -157,   112,   118,   120,
    -157,  -157,     4,    59,  -157,   244,    83,   130,   249,   133,
       3,  -157,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,   110,     0,   114,     4,   121,    39,   330,    83,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,    47,  -157,    60,    47,    29,   124,   126,   134,  -157,
    -157,  -157,  -157,  -157,  -157,  -157,   119,  -157,  -157,  -157,
    -157,   136,   129,     0,   344,     4,   139,   142,  -157,  -157,
      84,    -5,    84,    -5,    -5,    63,    63,   344,   344,  -157,
     122,    83,   -21,     4,     4,    83,   -21,   135,   137,   138,
     141,    47,   154,  -157,   144,   344,  -157,  -157,    45,    83,
     287,   292,    45,    83,    83,    83,    83,    83,    83,   -21,
     149,  -157,  -157,    45,    47,    47,   146,    45,  -157,  -157,
    -157,  -157,    45,    83,   150,  -157,    83,   -21,    83,   -21,
      83,   151,   152,    45,   168,    45,    83,    45,    83,  -157,
      83,    83,   156,   163,   159,    45,   160,    45,  -157,  -157,
      83,   161,    83,   164,    83,   165,  -157,   145,  -157,    83,
    -157,    83,   167,  -157,  -157,   186,  -157
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     0,     0,     0,     3,     0,     1,     0,
       0,     0,     0,     0,    10,     0,     0,     0,     8,     0,
       0,     0,     2,    19,     7,     6,     0,     9,     0,    21,
      37,     0,     5,    18,     0,    12,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,     0,     0,     0,    11,     0,     0,    69,
      67,    68,     0,     0,    70,     0,    64,     0,     0,     0,
       0,    36,    22,    23,    24,    48,    25,    26,    80,     0,
      27,    28,     0,     0,     0,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,     0,     0,     0,     0,     0,     0,    29,
      30,    31,    49,    32,    33,    81,     0,    34,    35,    17,
      15,     0,     0,     0,    50,     0,     0,     0,    71,    66,
      52,    54,    53,    55,    56,    60,    59,    61,    62,    57,
      58,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    14,     0,    51,    47,    46,     0,     0,
       0,     0,     0,     0,    42,    43,    38,    39,     0,     0,
       0,    13,    82,     0,     0,     0,     0,     0,    44,    45,
      40,    41,     0,     0,     0,    83,     0,     0,     0,     0,
      88,     0,     0,     0,     0,     0,     0,     0,     0,    90,
      89,    84,     0,     0,     0,     0,     0,     0,    91,    86,
      85,     0,    73,     0,    72,     0,    87,     0,    77,    75,
      76,    74,     0,    79,    78,     0,    16
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -157,  -157,    61,   -20,  -157,  -157,   158,  -157,    73,   -35,
    -157,  -156,     6,  -157,  -157,   128,  -157,   131,   147,   132,
    -157,  -157,  -157,  -157,  -157
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,    63,     5,    11,    27,    28,   122,    34,
      16,    17,    31,    43,    44,    64,    45,    46,    65,    66,
      47,    48,    49,    50,    51
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      26,    30,   172,   120,     1,    32,   176,    33,    59,    60,
      61,     7,    95,    96,    55,    26,    58,   185,    67,    62,
      54,   191,    30,    25,    57,    78,   192,     1,    25,   107,
      99,   100,    25,    82,     8,   108,    25,   202,   121,   204,
      29,   206,    87,   126,   127,   147,   102,   119,    71,   213,
       9,   215,    30,    30,    30,   112,    30,    30,   115,   116,
      30,    30,     6,    59,    60,    61,    10,    14,     1,   129,
       2,    25,     1,    12,    62,    20,    21,    22,   109,   110,
     111,   142,   113,   114,   146,    15,   117,   118,   143,    35,
     144,    42,    91,    18,    93,    94,    13,    36,    99,   100,
      19,    95,    96,    23,    72,    73,    74,    25,    76,    77,
      79,    80,    81,    24,    33,    52,    69,    53,     1,    99,
     100,   158,    70,    75,    37,   162,    38,    39,    83,    84,
      86,   169,    85,    87,    36,    40,    41,   105,   123,   173,
     148,   125,   149,   177,   178,   179,   180,   181,   182,   152,
     150,   151,   153,   156,   187,   189,   157,    99,   164,   170,
     165,   166,   141,   193,   167,   145,   195,   171,   197,   190,
     199,   184,   194,   203,   200,   201,   205,   211,   207,   210,
     208,   209,   212,   214,   222,   217,    68,   219,   221,   226,
     216,   225,   218,    56,   220,    89,   154,   106,   103,   223,
       0,   224,     0,   159,     0,     0,     0,   163,     0,    88,
       0,     0,   168,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     183,     0,   124,     0,     0,   186,   188,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   196,     0,
     198,    90,    91,    92,    93,    94,    90,    91,    92,    93,
      94,    95,    96,    97,    98,     0,    95,    96,    97,    98,
       0,     0,   155,     0,     0,     0,     0,     0,     0,    99,
     100,     0,     0,     0,    99,   100,     0,     0,     0,   101,
     160,   161,     0,   104,    90,    91,    92,    93,    94,    90,
      91,    92,    93,    94,    95,    96,    97,    98,     0,    95,
      96,    97,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    99,   100,     0,     0,     0,    99,   100,     0,
       0,   174,     0,     0,     0,     0,   175,    90,    91,    92,
      93,    94,     0,     0,     0,     0,   128,    95,    96,    97,
      98,    90,    91,    92,    93,    94,     0,     0,     0,     0,
       0,    95,    96,    97,    98,    99,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    99,
     100
};

static const yytype_int16 yycheck[] =
{
      20,    21,   158,     3,    25,    25,   162,     4,     4,     5,
       6,    24,    17,    18,    34,    35,    36,   173,    38,    15,
      12,   177,    42,    24,    12,    23,   182,    25,    24,    26,
      35,    36,    24,    53,     0,    70,    24,   193,    38,   195,
      41,   197,    13,     4,     5,    16,    66,    82,    42,   205,
      27,   207,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,     1,     4,     5,     6,     5,    29,    25,    89,
      27,    24,    25,     4,    15,    14,    15,    16,    72,    73,
      74,   101,    76,    77,   104,    40,    80,    81,    28,    28,
      30,    30,     8,    23,    10,    11,    24,     4,    35,    36,
       4,    17,    18,    22,    43,    44,    45,    24,    47,    48,
      49,    50,    51,    23,     4,    41,    15,    46,    25,    35,
      36,   141,    15,    23,    31,   145,    33,    34,    24,    12,
      12,   151,    20,    13,     4,    42,    43,     4,    24,   159,
      16,    20,    16,   163,   164,   165,   166,   167,   168,    13,
      16,    32,    23,    14,   174,   175,    14,    35,    23,     5,
      23,    23,   101,   183,    23,   104,   186,    23,   188,    23,
     190,    22,    22,     5,    23,    23,   196,    14,   198,    23,
     200,   201,    23,    23,    39,    24,    39,    23,    23,     3,
     210,    24,   212,    35,   214,    63,   123,    69,    67,   219,
      -1,   221,    -1,   142,    -1,    -1,    -1,   146,    -1,    62,
      -1,    -1,   151,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     169,    -1,    85,    -1,    -1,   174,   175,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   187,    -1,
     189,     7,     8,     9,    10,    11,     7,     8,     9,    10,
      11,    17,    18,    19,    20,    -1,    17,    18,    19,    20,
      -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    45,
     143,   144,    -1,    44,     7,     8,     9,    10,    11,     7,
       8,     9,    10,    11,    17,    18,    19,    20,    -1,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    -1,    -1,    -1,    35,    36,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    44,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    16,    17,    18,    19,
      20,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,    27,    48,    49,    51,    49,    24,     0,    27,
      49,    52,     4,    24,    29,    40,    57,    58,    23,     4,
      49,    49,    49,    22,    23,    24,    50,    53,    54,    41,
      50,    59,    50,     4,    56,    49,     4,    31,    33,    34,
      42,    43,    49,    60,    61,    63,    64,    67,    68,    69,
      70,    71,    41,    46,    12,    50,    53,    12,    50,     4,
       5,     6,    15,    50,    62,    65,    66,    50,    65,    15,
      15,    59,    49,    49,    49,    23,    49,    49,    23,    49,
      49,    49,    50,    24,    12,    20,    12,    13,    65,    66,
       7,     8,     9,    10,    11,    17,    18,    19,    20,    35,
      36,    45,    50,    64,    44,     4,    62,    26,    56,    59,
      59,    59,    50,    59,    59,    50,    50,    59,    59,    56,
       3,    38,    55,    24,    65,    20,     4,     5,    16,    50,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    49,    50,    28,    30,    49,    50,    16,    16,    16,
      16,    32,    13,    23,    55,    65,    14,    14,    50,    49,
      65,    65,    50,    49,    23,    23,    23,    23,    49,    50,
       5,    23,    58,    50,    44,    44,    58,    50,    50,    50,
      50,    50,    50,    49,    22,    58,    49,    50,    49,    50,
      23,    58,    58,    50,    22,    50,    49,    50,    49,    50,
      23,    23,    58,     5,    58,    50,    58,    50,    50,    50,
      23,    14,    23,    58,    23,    58,    50,    24,    50,    23,
      50,    23,    39,    50,    50,    24,     3
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    54,    54,    55,    55,    56,    56,    57,
      58,    58,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      60,    60,    61,    61,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    66,    66,    66,
      66,    66,    67,    67,    67,    67,    67,    67,    67,    67,
      68,    68,    69,    69,    70,    70,    70,    70,    71,    71,
      71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     2,     1,     2,     1,     5,     4,     4,
       2,     3,     2,     7,     6,     1,    11,     4,     1,     2,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       4,     4,     4,     4,     4,     4,     3,     1,     5,     5,
       6,     6,     5,     5,     6,     6,     4,     4,     2,     3,
       4,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     2,     3,     1,     1,     1,
       1,     3,    10,    10,    11,    11,    11,    11,    12,    12,
       2,     3,     6,     7,     8,     9,     9,    10,     7,     8,
       8,     9
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
  case 2: /* valid_prog: initial_block var_block final_begin_end_block newlines_p  */
#line 100 "ERROR404.y"
                                                                   {
        printf("valid input\n");

        // print all the values in the symbol table including initial
        for (int i = 0; i < sym_ptr; i++) {
                printf("%s %s %s\n", sym_table[i].name, sym_table[i].type, sym_table[i].value);
        }
}
#line 1522 "y.tab.c"
    break;

  case 13: /* dec_statement: spaces_p id_list spaces_p colon space dec_type semicolon  */
#line 123 "ERROR404.y"
                                                                        {
                        // printf("DEC: %d\n", sym_ptr);
                        // for (int i = 0; i < id_list_count; i++) {
                        //         sym_ptr--;
                        //         strcpy(sym_table[sym_ptr].type, $6);
                        // }
                        // sym_ptr += id_list_count;
                        // id_list_count = 0;
                        for (int i = 0; i < id_list_count; i++) {
                                strcpy(sym_table[sym_ptr].name, str_arr[i]);
                                strcpy(sym_table[sym_ptr].type, (yyvsp[-1].strval));
                                sym_ptr++;
                        }
                        id_list_count = 0;
                }
#line 1542 "y.tab.c"
    break;

  case 14: /* dec_statement: spaces_p id_list colon space dec_type semicolon  */
#line 138 "ERROR404.y"
                                                                  {
                        // printf("DEC: %d\n", sym_ptr);
                        // for (int i = 0; i < id_list_count; i++) {
                        //         sym_ptr--;
                        //         strcpy(sym_table[sym_ptr].type, $5);
                        // }
                        // sym_ptr += id_list_count;
                        // id_list_count = 0;
                        for (int i = 0; i < id_list_count; i++) {
                                strcpy(sym_table[sym_ptr].name, str_arr[i]);
                                strcpy(sym_table[sym_ptr].type, (yyvsp[-1].strval));
                                sym_ptr++;
                        }
                        id_list_count = 0;
                }
#line 1562 "y.tab.c"
    break;

  case 15: /* dec_type: key_type  */
#line 154 "ERROR404.y"
                   {strcpy((yyval.strval), (yyvsp[0].strval));}
#line 1568 "y.tab.c"
    break;

  case 16: /* dec_type: key_arr open_s num dot dot num close_s space key_of space key_type  */
#line 155 "ERROR404.y"
                                                                             {strcpy((yyval.strval), (yyvsp[0].strval));}
#line 1574 "y.tab.c"
    break;

  case 17: /* id_list: id comma spaces_p id_list  */
#line 157 "ERROR404.y"
                                   {strcpy(str_arr[id_list_count], (yyvsp[-3].strval)); id_list_count++;}
#line 1580 "y.tab.c"
    break;

  case 18: /* id_list: id  */
#line 158 "ERROR404.y"
            {strcpy(str_arr[id_list_count], (yyvsp[0].strval)); id_list_count++;}
#line 1586 "y.tab.c"
    break;

  case 50: /* assign_statement_ws: id colon equal exp  */
#line 197 "ERROR404.y"
                                       {
        int ind = findInSymTable((yyvsp[-3].strval));
        if (ind != -1) {
                if (strcmp(sym_table[ind].type, "4") == 0){
                        if (isBool((yyvsp[0].strval)) == 1) {
                                sym_table[ind].initial = true;
                                strcpy(sym_table[ind].value, (yyvsp[0].strval));
                        } else {
                                // printf("Variable: %s\n", $1);
                                // printf("Symbol Table Type: %s\n", sym_table[ind].type);
                                // printf("Type mismatch\n");
                                yyerror();
                        }
                }
                else if (atoi(sym_table[ind].type) == findType((yyvsp[0].strval))) {
                        sym_table[ind].initial = true;
                        strcpy(sym_table[ind].value, (yyvsp[0].strval));
                } else {
                        // printf("Variable: %s\n", $1);
                        // printf("Symbol Table Type: %s\n", sym_table[ind].type);
                        // printf("Expression Type: %d\n", findType($4));
                        // printf("Type mismatch\n");
                        yyerror();
                }
        } else {
                printf("Variable not declared\n");
                yyerror();
        }
}
#line 1620 "y.tab.c"
    break;

  case 51: /* assign_statement_ws: id spaces_p colon equal exp  */
#line 226 "ERROR404.y"
                                             {
        int ind = findInSymTable((yyvsp[-4].strval));
        if (ind != -1) {
                if (strcmp(sym_table[ind].type, "4") == 0) {
                        if (isBool((yyvsp[0].strval)) == 1) {
                                sym_table[ind].initial = true;
                                strcpy(sym_table[ind].value, (yyvsp[0].strval));
                        } else {
                                // printf("Variable: %s\n", $1);
                                // printf("Symbol Table Type: %s\n", sym_table[ind].type);
                                // printf("Type mismatch\n");
                                yyerror();
                        }
                }
                else if (atoi(sym_table[ind].type) == findType((yyvsp[0].strval))) {
                        sym_table[ind].initial = true;
                        strcpy(sym_table[ind].value, (yyvsp[0].strval));
                } else {
                        // printf("Variable: %s\n", $1);
                        // printf("Symbol Table Type: %s\n", sym_table[ind].type);
                        // printf("Expression Type: %d\n", findType($5));
                        // printf("Type mismatch\n");
                        yyerror();
                }
        } else {
                printf("Variable not declared\n");
                yyerror();
        }
}
#line 1654 "y.tab.c"
    break;

  case 52: /* exp: exp op_plus exp  */
#line 256 "ERROR404.y"
                    {
                        if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval)) == 1) 
                        {
                                int a=atoi((yyvsp[-2].strval))+atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==2) 
                        {
                                double a=atof((yyvsp[-2].strval))+atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else if(findType((yyvsp[-2].strval))==1 && findType((yyvsp[0].strval))==2) 
                        {
                                double a=atoi((yyvsp[-2].strval))+atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else if(findType((yyvsp[-2].strval))==2 && findType((yyvsp[0].strval))==1) 
                        {
                                double a=atof((yyvsp[-2].strval))+atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else {
                                printf("TESTING");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

        }
#line 1691 "y.tab.c"
    break;

  case 53: /* exp: exp op_minus exp  */
#line 289 "ERROR404.y"
                          {
                        if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==1) 
                        {
                                int a=atoi((yyvsp[-2].strval)) - atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==2) 
                        {
                                double a=atof((yyvsp[-2].strval)) - atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else if(findType((yyvsp[-2].strval))==1 && findType((yyvsp[0].strval))==2) 
                        {
                                double a=atoi((yyvsp[-2].strval)) - atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else if(findType((yyvsp[-2].strval))==2 && findType((yyvsp[0].strval))==1) 
                        {
                                double a=atof((yyvsp[-2].strval)) - atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else {
                                printf("TESTING");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
#line 1728 "y.tab.c"
    break;

  case 54: /* exp: exp op_mult exp  */
#line 321 "ERROR404.y"
                    {
                        if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==1) 
                        {
                                int a=atoi((yyvsp[-2].strval))+atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==2) 
                        {
                                double a=atof((yyvsp[-2].strval))+atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else if(findType((yyvsp[-2].strval))==1 && findType((yyvsp[0].strval))==2) 
                        {
                                double a=atoi((yyvsp[-2].strval))+atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else if(findType((yyvsp[-2].strval))==2 && findType((yyvsp[0].strval))==1) 
                        {
                                double a=atof((yyvsp[-2].strval))+atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else {
                                printf("TESTING");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
#line 1765 "y.tab.c"
    break;

  case 55: /* exp: exp op_div exp  */
#line 353 "ERROR404.y"
                   {
                        if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==1) 
                        {
                                int a=atoi((yyvsp[-2].strval))+atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==2) 
                        {
                                double a=atof((yyvsp[-2].strval))+atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else if(findType((yyvsp[-2].strval))==1 && findType((yyvsp[0].strval)) == 2) 
                        {
                                double a=atoi((yyvsp[-2].strval))+atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else if(findType((yyvsp[-2].strval))==2 && findType((yyvsp[0].strval))==1) 
                        {
                                double a=atof((yyvsp[-2].strval))+atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else {
                                printf("TESTING");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
#line 1802 "y.tab.c"
    break;

  case 56: /* exp: exp op_mod exp  */
#line 385 "ERROR404.y"
                   {
                        if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==1) 
                        {
                                int a=atoi((yyvsp[-2].strval))+atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==2) 
                        {
                                double a=atof((yyvsp[-2].strval))+atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else if(findType((yyvsp[-2].strval))==1 && findType((yyvsp[0].strval))==2) 
                        {
                                double a=atoi((yyvsp[-2].strval))+atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else if(findType((yyvsp[-2].strval))==2 && findType((yyvsp[0].strval))==1) 
                        {
                                double a=atof((yyvsp[-2].strval))+atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%f", a);
                        }

                        else {
                                printf("TESTING");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
#line 1839 "y.tab.c"
    break;

  case 57: /* exp: exp key_and exp  */
#line 417 "ERROR404.y"
                    {
                        if(isBool((yyvsp[-2].strval))==isBool((yyvsp[0].strval)) && isBool((yyvsp[-2].strval))==1) 
                        {
                                int a=atoi((yyvsp[-2].strval))&&atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else {
                                printf("TESTING");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
#line 1858 "y.tab.c"
    break;

  case 58: /* exp: exp key_or exp  */
#line 432 "ERROR404.y"
                   {
                        if(isBool((yyvsp[-2].strval))==isBool((yyvsp[0].strval)) && isBool((yyvsp[-2].strval))==1) 
                        {
                                int a=atoi((yyvsp[-2].strval))||atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else {
                                printf("TESTING");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
#line 1877 "y.tab.c"
    break;

  case 59: /* exp: exp greater exp  */
#line 446 "ERROR404.y"
                    {
                        if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==1) 
                        {
                                int a=atoi((yyvsp[-2].strval))>atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==2) 
                        {
                                int a=atof((yyvsp[-2].strval))>atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==1 && findType((yyvsp[0].strval))==2) 
                        {
                                int a=atoi((yyvsp[-2].strval))>atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==2 && findType((yyvsp[0].strval))==1) 
                        {
                                int a=atof((yyvsp[-2].strval))>atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else {
                                printf("TESTING");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
#line 1914 "y.tab.c"
    break;

  case 60: /* exp: exp lesser exp  */
#line 480 "ERROR404.y"
                   {
                        if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==1) 
                        {
                                int a=atoi((yyvsp[-2].strval))<atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==2) 
                        {
                                int a=atof((yyvsp[-2].strval))<atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==1 && findType((yyvsp[0].strval))==2) 
                        {
                                int a=atoi((yyvsp[-2].strval))<atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==2 && findType((yyvsp[0].strval))==1) 
                        {
                                int a=atof((yyvsp[-2].strval))<atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else {
                                printf("TESTING");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
#line 1951 "y.tab.c"
    break;

  case 61: /* exp: exp not_equal exp  */
#line 512 "ERROR404.y"
                      {
                        if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval)) == 1) 
                        {
                                int a=atoi((yyvsp[-2].strval))!=atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==2) 
                        {
                                int a=atof((yyvsp[-2].strval))!=atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==1 && findType((yyvsp[0].strval))==2) 
                        {
                                int a=atoi((yyvsp[-2].strval))!=atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==2 && findType((yyvsp[0].strval))==1) 
                        {
                                int a=atof((yyvsp[-2].strval))!=atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(isBool((yyvsp[-2].strval))==isBool((yyvsp[0].strval)) && isBool((yyvsp[-2].strval))==1) 
                        {
                                int a=(atoi((yyvsp[-2].strval))!=atoi((yyvsp[0].strval)));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else {
                                printf("%d %d\n", findType((yyvsp[-2].strval)), findType((yyvsp[-2].strval)) == 1);
                                printf("TESTING IN NOT EQUAL\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
#line 1995 "y.tab.c"
    break;

  case 62: /* exp: exp equal exp  */
#line 551 "ERROR404.y"
                  {
                        if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==1) 
                        {
                                int a=atoi((yyvsp[-2].strval))==atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==findType((yyvsp[0].strval)) && findType((yyvsp[-2].strval))==2) 
                        {
                                int a=atof((yyvsp[-2].strval))==atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==1 && findType((yyvsp[0].strval))==2) 
                        {
                                int a=atoi((yyvsp[-2].strval))==atof((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        else if(findType((yyvsp[-2].strval))==2 && findType((yyvsp[0].strval))==1) 
                        {
                                int a=atof((yyvsp[-2].strval))==atoi((yyvsp[0].strval));
                                sprintf((yyval.strval), "%d", a);
                        }

                        if(isBool((yyvsp[-2].strval))==isBool((yyvsp[0].strval)) && isBool((yyvsp[-2].strval))==1) 
                        {
                                int a=(atoi((yyvsp[-2].strval))==atoi((yyvsp[0].strval)));
                                sprintf((yyval.strval), "%d", a);
                        }
                        else {
                                printf("TESTING");
                                printf("Type mismatch\n");yyerror();
                        }
                        }
#line 2035 "y.tab.c"
    break;

  case 63: /* exp: name spaces_p  */
#line 586 "ERROR404.y"
                  {strcpy((yyval.strval), (yyvsp[-1].strval));}
#line 2041 "y.tab.c"
    break;

  case 64: /* exp: name  */
#line 587 "ERROR404.y"
         {strcpy((yyval.strval), (yyvsp[0].strval));}
#line 2047 "y.tab.c"
    break;

  case 65: /* exp: spaces_p name  */
#line 588 "ERROR404.y"
                  {strcpy((yyval.strval), (yyvsp[0].strval));}
#line 2053 "y.tab.c"
    break;

  case 66: /* exp: spaces_p name spaces_p  */
#line 589 "ERROR404.y"
                           {strcpy((yyval.strval), (yyvsp[-1].strval));}
#line 2059 "y.tab.c"
    break;

  case 67: /* name: num  */
#line 591 "ERROR404.y"
         {strcpy((yyval.strval), (yyvsp[0].strval));}
#line 2065 "y.tab.c"
    break;

  case 68: /* name: num_real  */
#line 592 "ERROR404.y"
                  {strcpy((yyval.strval), (yyvsp[0].strval));}
#line 2071 "y.tab.c"
    break;

  case 69: /* name: id  */
#line 593 "ERROR404.y"
            {
                int ind = findInSymTable((yyvsp[0].strval));
                if (ind != -1) {
                        if (sym_table[ind].initial) {
                                strcpy((yyval.strval), sym_table[ind].value);
                        } else {
                                printf("Variable not initialized\n");
                                yyerror();
                        }
                }
                else {
                        printf("Variable not declared\n");
                        yyerror();
                }
        }
#line 2091 "y.tab.c"
    break;


#line 2095 "y.tab.c"

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

#line 634 "ERROR404.y"


void main(){
int ptr = 0;
while (ptr++ < 500) {
        sym_table[ptr].initial = false;
}

for (int i = 0; i < 500; i++)
        strcpy(sym_table[i].value, "-1");

yyin = fopen("input.txt", "r");
yyparse();
exit(0);
}

void yyerror()
{
        printf("syntax error\n"); 
        exit(0);
}
