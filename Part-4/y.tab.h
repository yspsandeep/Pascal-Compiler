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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    key_prog = 262,                /* key_prog  */
    equal = 263,                   /* equal  */
    not_equal = 264,               /* not_equal  */
    op_plus = 265,                 /* op_plus  */
    op_minus = 266,                /* op_minus  */
    op_mult = 267,                 /* op_mult  */
    op_div = 268,                  /* op_div  */
    op_mod = 269,                  /* op_mod  */
    key_var = 270,                 /* key_var  */
    key_arr = 271,                 /* key_arr  */
    key_of = 272,                  /* key_of  */
    key_begin = 273,               /* key_begin  */
    key_end = 274,                 /* key_end  */
    key_read = 275,                /* key_read  */
    key_write = 276,               /* key_write  */
    quoted_string = 277,           /* quoted_string  */
    quoted_char = 278,             /* quoted_char  */
    colon = 279,                   /* colon  */
    open_s = 280,                  /* open_s  */
    close_s = 281,                 /* close_s  */
    open_b = 282,                  /* open_b  */
    close_b = 283,                 /* close_b  */
    lesser = 284,                  /* lesser  */
    greater = 285,                 /* greater  */
    dot = 286,                     /* dot  */
    semicolon = 287,               /* semicolon  */
    space = 288,                   /* space  */
    newline = 289,                 /* newline  */
    key_downto = 290,              /* key_downto  */
    key_to = 291,                  /* key_to  */
    key_if = 292,                  /* key_if  */
    key_else = 293,                /* key_else  */
    key_for = 294,                 /* key_for  */
    key_while = 295,               /* key_while  */
    key_and = 296,                 /* key_and  */
    key_or = 297,                  /* key_or  */
    key_do = 298,                  /* key_do  */
    key_then = 299,                /* key_then  */
    comma = 300,                   /* comma  */
    key_not = 301                  /* key_not  */
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
#define key_prog 262
#define equal 263
#define not_equal 264
#define op_plus 265
#define op_minus 266
#define op_mult 267
#define op_div 268
#define op_mod 269
#define key_var 270
#define key_arr 271
#define key_of 272
#define key_begin 273
#define key_end 274
#define key_read 275
#define key_write 276
#define quoted_string 277
#define quoted_char 278
#define colon 279
#define open_s 280
#define close_s 281
#define open_b 282
#define close_b 283
#define lesser 284
#define greater 285
#define dot 286
#define semicolon 287
#define space 288
#define newline 289
#define key_downto 290
#define key_to 291
#define key_if 292
#define key_else 293
#define key_for 294
#define key_while 295
#define key_and 296
#define key_or 297
#define key_do 298
#define key_then 299
#define comma 300
#define key_not 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 496 "ERROR404.y"

        char strval[100];
        struct Node* node;

#line 164 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
