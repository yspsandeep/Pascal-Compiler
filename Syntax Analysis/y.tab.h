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

#line 163 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
