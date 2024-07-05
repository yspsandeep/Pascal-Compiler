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
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "tree_builder.c"                                                                   

extern FILE *yyin;

typedef struct sym_val {
        char name[100];
        int ind;
        int type;
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

void printSymTable() {
        for (int i = 0; i < sym_ptr; i++) {
                printf("%s %d %d %s\n", sym_table[i].name, sym_table[i].ind,sym_table[i].type, sym_table[i].value);
        }
}

void printSymTableTillInd(int ind) {
        printf("VARIABLE\tTYPE\tVALUE\t[INDEX]\n");
        for (int i = 0; i < ind; i++) {
                printf("%s\t\t%d\t%s\t%d\n", sym_table[i].name,sym_table[i].type, sym_table[i].value, sym_table[i].ind);
        }
}



char str_arr[100][100];
int id_list_count = 0;

const char* numToType(int value) {
    char* typeString = (char*)malloc(20 * sizeof(char));
    if (value == 1)
        sprintf(typeString, "integer");
    else if (value == 2)
        sprintf(typeString, "real");
    else if (value == 3)
        sprintf(typeString, "char");
    else if (value == 4)
        sprintf(typeString, "boolean");
    else
        sprintf(typeString, "unknown");

    return typeString;
}

struct Quadruple {
        char op[100];
        char arg1[100];
        char arg2[100];
        char result[100];
} quad[1000] ;
int quad_ptr = 0;

int findIfIdList(char* name) {
        char *temp = name;

        while (*temp != '\0') {
                if (*temp == ',') {
                        return 1;
                }
                temp++;
        }

        return 0;
}

char *deepCopy(char *s)
{
    int ptr = 0;
    while (s[ptr] != '\0')
        ptr++;

    char *res = (char *)malloc(ptr + 1);
    for (int i = 0; i < ptr; i++)
    {
        res[i] = s[i];
    }
    res[ptr] = '\0';
    return res;
}

char *getArrName(char *s)
{
    char *new_s = deepCopy(s);
    char *p = new_s;
    while (*p != '[')
    {
        p++;
    }
    *p = '\0';
    return new_s;
}

int getArrInd(char *s)
{
    char *new_s = deepCopy(s);
    int ptr = 0;

    while (s[ptr] != '\0' && s[ptr] != ']')
        ptr++;
    new_s[ptr] = '\0';

    char *p = new_s;
    while (*p != '\0' && *p != '[')
        p++;
    p++;

    int ind = findInSymTable(p);
    if (ind != -1) {
        return atoi(sym_table[ind].value);
    }

    return atoi(p);
}

int findIfArray(char *s)
{
    int flag = 0;
    char *p = s;
    while (*p != '\0')
    {
        if (*p == '[')
        {
            flag = 1;
        }
        if (flag == 1 && *p == ']' && *(p + 1) == '\0')
        {
            return 1;
        }
        p++;
    }
    return 0;
}

//post order traversal of the tree
void solveTree(struct Node* root) {
        if (root == NULL) {
                return;
        }
        else if(strcmp(root->name,  "content") == 0){
                if(root->children[0]) {
                        solveTree(root->children[0]);
                }
                if (root->children[1]) {
                        solveTree(root->children[1]);
                }
                root->line = quad_ptr;
        }
        else if(strcmp(root->name,  "assign_statement")==0){
                solveTree(root->children[1]);

                char temp[100];
                strcpy(quad[quad_ptr].op, "assign");
                sprintf(temp, "t%d",root->children[1]->line);
                strcpy(quad[quad_ptr].arg1, temp);
                if(strcmp(root->children[0]->name, "array_id") != 0) {
                        strcpy(quad[quad_ptr].result, root->children[0]->name);
                } else {
                        char temp[100];
                        sprintf(temp, "%s[%s]", root->children[0]->children[0]->name, root->children[0]->children[1]->name);
                        strcpy(quad[quad_ptr].result, temp);
                }
                
                root->line = quad_ptr;
                quad_ptr++;
        }

        else if(strcmp(root->name,  "exp")==0){

                if(root->children[2]) {
                        solveTree(root->children[0]);
                        solveTree(root->children[2]);
                        char temp[100];
                        sprintf(temp, "t%d",root->children[0]->line);
                        // quad[quad_ptr].op = root->children[1]->name;
                        if (strcmp(root->children[1]->name, "<>") == 0) {
                                // printf("NOTEQUALLLL\n");
                                strcpy(quad[quad_ptr].op, "x<>");
                        }
                        else {
                                strcpy(quad[quad_ptr].op, root->children[1]->name);
                        }
                        // quad[quad_ptr].arg1 = temp;
                        strcpy(quad[quad_ptr].arg1, temp);
                        sprintf(temp, "t%d",root->children[2]->line);

                        // quad[quad_ptr].arg2 = temp;
                        strcpy(quad[quad_ptr].arg2, temp);
                        sprintf(temp, "t%d",quad_ptr);
                        // quad[quad_ptr].result = temp;
                        strcpy(quad[quad_ptr].result, temp);
                        root->line = quad_ptr;
                        quad_ptr++;
                }
                else if(root->children[1]){
                        solveTree(root->children[1]);
                        char temp[100];
                        sprintf(temp, "t%d",root->children[1]->line);
                        // quad[quad_ptr].op = "not";
                        strcpy(quad[quad_ptr].op, "not");
                        // quad[quad_ptr].arg1 = temp;
                        strcpy(quad[quad_ptr].arg1, temp);


                        sprintf(temp, "t%d",quad_ptr);
                        // quad[quad_ptr].result = temp;
                        strcpy(quad[quad_ptr].result, temp);
                        root->line = quad_ptr;
                        quad_ptr++;
                }
                else if (strcmp(root->children[0]->name, "exp") == 0){
                        solveTree(root->children[0]);
                        root->line = quad_ptr - 1;
                }
                else{
                        // quad[quad_ptr].op = "assign";
                        strcpy(quad[quad_ptr].op, "assign");
                        char temp[100];
                        sprintf(temp, "t%d",quad_ptr);
                        // quad[quad_ptr].result = ;
                        strcpy(quad[quad_ptr].result, temp);


                        if(strcmp(root->children[0]->name, "array_id") != 0) {
                        strcpy(quad[quad_ptr].arg1, root->children[0]->name);
                        } else {
                        char temp[100];
                        sprintf(temp, "%s[%s]", root->children[0]->children[0]->name, root->children[0]->children[1]->name);
                        strcpy(quad[quad_ptr].arg1, temp);
                        }

                        

                        root->line = quad_ptr;
                        quad_ptr++;
                }
        }
        else if(strcmp(root->name,  "write") == 0){
                solveTree(root->children[0]);
                // quad[quad_ptr].op = "write"
                strcpy(quad[quad_ptr].op, "write");
                if(strcmp(root->children[0]->name, "array_id") == 0) {
                        char temp[100];
                        sprintf(temp, "%s[%s]", root->children[0]->children[0]->name, root->children[0]->children[1]->name);
                        strcpy(quad[quad_ptr].result, temp);
                        
                }else if(strcmp(root->children[0]->name, "id_list") == 0){
                        char temp[1000];
                        struct Node* temp2 = root->children[0];
                        int ptr =0;
                        while(temp2->children[1]){
                                strcpy(temp+ptr, temp2->children[0]->name);

                                ptr+=strlen(temp2->children[0]->name);
                                strcpy(temp+ptr, ",");
                                ptr++;
                                temp2 = temp2->children[1];

                                
                        }

                        strcpy(temp+ptr, temp2->children[0]->name);
                        strcpy(quad[quad_ptr].result, temp);



                } else {
                        strcpy(quad[quad_ptr].result, root->children[0]->name);
                }
                root->line = quad_ptr;
                quad_ptr++;
        }
        else if(strcmp(root->name,  "read")==0){
                solveTree(root->children[0]);
                // quad[quad_ptr].op = "write"
                strcpy(quad[quad_ptr].op, "read");
                // quad[quad_ptr].result = root->children[0]->name;
                if (strcmp(root->children[0]->name, "array_id") != 0) {
                        strcpy(quad[quad_ptr].result, root->children[0]->name);
                } else {
                        char temp[100];
                        sprintf(temp, "%s[%s]", root->children[0]->children[0]->name, root->children[0]->children[1]->name);
                        strcpy(quad[quad_ptr].result, temp);
                }
                root->line = quad_ptr;
                quad_ptr++;
        }
        else if(strcmp(root->name,  "if_statement")==0){
                char temp[100];

                solveTree(root->children[0]);


                sprintf(temp, "t%d",root->children[0]->line);
                strcpy(quad[quad_ptr].op, "jne");
                strcpy(quad[quad_ptr].arg1, temp);
                strcpy(quad[quad_ptr].arg2, "0");
                int lin = quad_ptr;

                quad_ptr++;
                solveTree(root->children[1]);
                sprintf(quad[lin].result, "%d",root->children[1]->line);
                root->line = lin;
                // quad_ptr++;
        }
        
        else if(strcmp(root->name,  "if_else_statement")==0){
                solveTree(root->children[0]->children[0]);
                char temp[100];

                sprintf(temp, "t%d",root->children[0]->children[0]->line);
                strcpy(quad[quad_ptr].op, "jne");
                strcpy(quad[quad_ptr].arg1, temp);
                strcpy(quad[quad_ptr].arg2, "0");
                int lin = quad_ptr;

                quad_ptr++;

                solveTree(root->children[0]->children[1]);

                int lin2 = quad_ptr;
                strcpy(quad[lin2].op, "j");
                quad_ptr++;

                solveTree(root->children[1]);

                sprintf(quad[lin2].result, "%d",root->children[1]->line);
                sprintf(quad[lin].result, "%d",lin2+1);
                root->line = quad_ptr;
                // quad_ptr++;


        }
        else if(strcmp(root->name,  "for_statement" ) == 0) {
                char id[100];
                solveTree(root->children[0]);
                


                sprintf(id, "%s", root->children[0]->children[0]->name);
                int lin2 = quad_ptr;
                solveTree(root->children[1]); //limit calc

                strcpy(quad[quad_ptr].op, "jg");
                strcpy(quad[quad_ptr].arg1, id);
                sprintf(quad[quad_ptr].arg2, "t%d",root->children[1]->line);
                int lin3 = quad_ptr;

                quad_ptr++;
                solveTree(root->children[2]); // run content    

                //increment id
                strcpy(quad[quad_ptr].op, "+");
                strcpy(quad[quad_ptr].arg1, id);
                strcpy(quad[quad_ptr].arg2, "1");
                strcpy(quad[quad_ptr].result, id);
                quad_ptr++;


                strcpy(quad[quad_ptr].op, "j");
                sprintf(quad[quad_ptr].result, "%d",lin2);

                quad_ptr++;
                sprintf(quad[lin3].result, "%d",quad_ptr);
        }
        else if(strcmp(root->name,  "while_statement")==0){
                char temp[100];
                int lin2 = quad_ptr;
                solveTree(root->children[0]);


                sprintf(temp, "t%d",root->children[0]->line);
                strcpy(quad[quad_ptr].op, "jne");
                strcpy(quad[quad_ptr].arg1, temp);
                strcpy(quad[quad_ptr].arg2, "0");
                int lin = quad_ptr;

                quad_ptr++;


                solveTree(root->children[1]);
                
                strcpy(quad[root->children[1]->line].op, "j");
                sprintf(quad[root->children[1]->line].result, "%d",lin2);



                sprintf(quad[lin].result, "%d",root->children[1]->line+1);
                root->line = lin;
                quad_ptr++;
        }
}

//print quadruples
void printQuadruples() {
        for (int i = 0; i < quad_ptr; i++) {
                printf("%d     %s \t%s \t%s \t%s\n", i,quad[i].op, quad[i].arg1, quad[i].arg2, quad[i].result);
        }
}


void freeTree(struct Node* root) {
        if (root == NULL) {
                return;
        }
        for (int i = 0; i < 15; i++) {
                freeTree(root->children[i]);
        }
        free(root);
}



struct Node* root;

int findinInterSymTable(char* name) {
        for (int i = 0; i < sym_ptr; i++) {
                if (strcmp(sym_table[i].name, name) == 0) {
                        return i;
                }
        }
        return -1;
}

int find_data_type(char* name1) {

        if (findIfArray(name1) == 1) {
                char *temp= getArrName(name1);
                int ind1 = getArrInd(name1);
                int ind2 = findExactArrayInd(temp, ind1);
                return sym_table[ind2].type;       
        }
        

        else
        {
                for (int i = 0; i < sym_ptr; i++) {
                        if (strcmp(sym_table[i].name, name1) == 0) {
                                return sym_table[i].type;
                        }
                }
                
                if (strlen(name1) ==1)
                {
                        if(!(name1[0]>='0' && name1
                        [0]<='9'))
                        {
                                return 3;
                        }
                }
                
                for(int i=0;name1[i]!='\0';i++)
                {
                        if(name1[i]=='.')
                        {
                                return 2;
                        }
                }

                return 1;
        }
        
}

int findExactArrayInd(char *str,int index) {
        for (int i = 0; i < sym_ptr; i++) {
                if (strcmp(sym_table[i].name, str) == 0 && sym_table[i].ind == index) {
                        return i;
                }
        }
        return -1;
}
 


#line 567 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 497 "ERROR404.y"

        char strval[100];
        struct Node* node;

#line 717 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
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
  YYSYMBOL_key_prog = 7,                   /* key_prog  */
  YYSYMBOL_equal = 8,                      /* equal  */
  YYSYMBOL_not_equal = 9,                  /* not_equal  */
  YYSYMBOL_op_plus = 10,                   /* op_plus  */
  YYSYMBOL_op_minus = 11,                  /* op_minus  */
  YYSYMBOL_op_mult = 12,                   /* op_mult  */
  YYSYMBOL_op_div = 13,                    /* op_div  */
  YYSYMBOL_op_mod = 14,                    /* op_mod  */
  YYSYMBOL_key_var = 15,                   /* key_var  */
  YYSYMBOL_key_arr = 16,                   /* key_arr  */
  YYSYMBOL_key_of = 17,                    /* key_of  */
  YYSYMBOL_key_begin = 18,                 /* key_begin  */
  YYSYMBOL_key_end = 19,                   /* key_end  */
  YYSYMBOL_key_read = 20,                  /* key_read  */
  YYSYMBOL_key_write = 21,                 /* key_write  */
  YYSYMBOL_quoted_string = 22,             /* quoted_string  */
  YYSYMBOL_quoted_char = 23,               /* quoted_char  */
  YYSYMBOL_colon = 24,                     /* colon  */
  YYSYMBOL_open_s = 25,                    /* open_s  */
  YYSYMBOL_close_s = 26,                   /* close_s  */
  YYSYMBOL_open_b = 27,                    /* open_b  */
  YYSYMBOL_close_b = 28,                   /* close_b  */
  YYSYMBOL_lesser = 29,                    /* lesser  */
  YYSYMBOL_greater = 30,                   /* greater  */
  YYSYMBOL_dot = 31,                       /* dot  */
  YYSYMBOL_semicolon = 32,                 /* semicolon  */
  YYSYMBOL_space = 33,                     /* space  */
  YYSYMBOL_newline = 34,                   /* newline  */
  YYSYMBOL_key_downto = 35,                /* key_downto  */
  YYSYMBOL_key_to = 36,                    /* key_to  */
  YYSYMBOL_key_if = 37,                    /* key_if  */
  YYSYMBOL_key_else = 38,                  /* key_else  */
  YYSYMBOL_key_for = 39,                   /* key_for  */
  YYSYMBOL_key_while = 40,                 /* key_while  */
  YYSYMBOL_key_and = 41,                   /* key_and  */
  YYSYMBOL_key_or = 42,                    /* key_or  */
  YYSYMBOL_key_do = 43,                    /* key_do  */
  YYSYMBOL_key_then = 44,                  /* key_then  */
  YYSYMBOL_comma = 45,                     /* comma  */
  YYSYMBOL_key_not = 46,                   /* key_not  */
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
#define YYLAST   421

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  249

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
       0,   560,   560,   569,   579,   580,   582,   583,   585,   589,
     595,   602,   608,   613,   619,   668,   716,   764,   814,   835,
     860,   867,   873,   877,   879,   883,   884,   885,   886,   887,
     888,   889,   890,   891,   892,   893,   894,   895,   896,   897,
     898,   900,   902,   907,   912,   917,   922,   926,   931,   944,
     955,   968,   979,   993,  1008,  1009,  1011,  1035,  1060,  1085,
    1108,  1137,  1165,  1193,  1221,  1238,  1265,  1293,  1321,  1348,
    1388,  1428,  1446,  1462,  1466,  1470,  1475,  1481,  1484,  1487,
    1503,  1506,  1507,  1509,  1514,  1519,  1524,  1529,  1534,  1539,
    1544,  1551,  1552,  1554,  1559,  1565,  1571,  1576,  1581,  1589,
    1596,  1601,  1607
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
  "num", "num_real", "key_prog", "equal", "not_equal", "op_plus",
  "op_minus", "op_mult", "op_div", "op_mod", "key_var", "key_arr",
  "key_of", "key_begin", "key_end", "key_read", "key_write",
  "quoted_string", "quoted_char", "colon", "open_s", "close_s", "open_b",
  "close_b", "lesser", "greater", "dot", "semicolon", "space", "newline",
  "key_downto", "key_to", "key_if", "key_else", "key_for", "key_while",
  "key_and", "key_or", "key_do", "key_then", "comma", "key_not", "$accept",
  "valid_prog", "newlines_p", "spaces_p", "initial_block", "var_block",
  "dec_block", "dec_statement", "dec_type", "id_list",
  "final_begin_end_block", "begin_end_block", "content", "write_statement",
  "read_statement", "array_id", "assign_statement", "assign_statement_ws",
  "exp", "name", "for_statement", "if_statement", "if_statement_ws",
  "if_else_statement", "while_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-178)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,   -14,   -21,    35,    33,   -21,    51,  -178,  -178,    25,
      55,    71,    41,    88,   -21,   -21,   -21,    73,  -178,    68,
      75,    -2,  -178,  -178,  -178,    75,   107,  -178,   -21,  -178,
     254,    94,  -178,    82,    60,    75,    50,   113,   114,     3,
      75,     3,    75,   -21,   -21,    62,   -21,   110,   -21,   -21,
      69,   -21,   -21,  -178,    75,    21,   119,  -178,   137,    93,
     122,   145,    -1,   126,  -178,  -178,  -178,     3,     3,   101,
    -178,   125,    75,   146,   287,  -178,    75,    75,   148,   129,
      75,    75,    75,    75,    75,    75,    75,    75,   107,  -178,
     132,    30,   131,    26,     3,   139,   147,   163,    44,   144,
     -13,   149,   150,   152,   356,  -178,     3,    75,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,    14,
    -178,    86,    14,  -178,  -178,     3,   166,  -178,  -178,  -178,
    -178,  -178,   154,  -178,  -178,  -178,   170,   151,  -178,    30,
     155,   379,  -178,  -178,     3,   158,   162,   164,   165,   168,
    -178,  -178,  -178,   379,   379,   198,   198,    49,    49,    49,
      90,    90,  -178,   135,    75,   -21,     3,     3,    75,   -21,
     379,     3,    14,   153,  -178,   175,  -178,   379,    75,    75,
      75,    75,    75,    71,    75,   310,   333,    71,    75,   379,
      75,   -21,   167,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
      71,    14,    14,   176,    71,    71,    75,   190,  -178,    75,
     -21,    75,   -21,    75,   177,   182,    71,   192,    71,    75,
      71,    75,  -178,    75,    75,   184,   169,   187,    71,   188,
      71,  -178,  -178,    75,   204,    75,   191,    75,   193,  -178,
     196,  -178,    75,  -178,    75,   223,  -178,  -178,  -178
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     5,     0,     0,     0,     0,     4,     1,     0,
       0,     0,     0,     0,    11,     0,     3,     0,     9,     0,
       0,     0,     2,    22,     8,     7,     0,    10,     0,    24,
      41,     0,     6,    21,     0,    13,     0,     0,     0,     0,
       0,     0,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,     0,     0,     0,    12,     0,     0,
       0,     0,     0,    79,    77,    78,    80,     0,     0,     0,
      81,     0,    74,     0,     0,    39,    25,    26,     0,     0,
      27,    54,    30,    28,    91,     0,    29,    31,     0,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,     0,     0,     0,     0,    72,     0,    75,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,    32,    33,     0,     0,    34,    55,    37,
      35,    92,     0,    36,    38,    20,     0,     0,    16,     0,
       0,    56,    53,    52,     0,     0,     0,     0,     0,     0,
      82,    71,    76,    70,    69,    60,    61,    62,    63,    64,
      68,    67,    65,    66,     0,     0,     0,     0,     0,     0,
      58,     0,     0,     0,    15,     0,    17,    57,    48,    49,
      42,    43,    46,     0,     0,     0,     0,     0,     0,    59,
       0,     0,     0,    14,    50,    51,    44,    45,    47,    93,
       0,     0,     0,     0,     0,     0,     0,     0,    94,     0,
       0,     0,     0,    99,     0,     0,     0,     0,     0,     0,
       0,     0,   101,   100,    95,     0,     0,     0,     0,     0,
       0,   102,    97,    96,     0,    84,     0,    83,     0,    98,
       0,    88,    86,    87,    85,     0,    90,    89,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,    66,   -20,  -178,  -178,   195,  -178,   -89,   -44,
    -178,  -177,    43,  -178,  -178,    15,  -178,   160,   138,   172,
    -178,  -178,  -178,  -178,  -178
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,    69,     5,    11,    27,    28,    92,    34,
      16,    17,    31,    43,    44,    70,    46,    47,    71,    72,
      48,    49,    50,    51,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      26,    30,   137,   100,   140,    32,   199,    63,    64,    65,
     203,     1,    59,     2,    56,    26,    60,    29,   102,     6,
      73,   101,    30,   208,    89,    79,    66,   214,   215,    89,
      67,    25,    54,    89,    88,     8,    25,    90,     2,   225,
       9,   227,    90,   229,   135,    45,    90,    25,     2,    68,
     175,   236,   120,   238,    91,    12,    30,    30,    13,   139,
      30,   128,    30,    30,   131,   132,    30,    30,     7,    59,
      14,    10,   145,    18,    58,    59,    99,   103,   115,   116,
      20,    21,    22,    25,    55,    75,    78,   152,    45,    15,
     117,   118,    19,    25,    35,    25,    42,    95,    96,   165,
      24,    84,   169,     2,    23,    63,    64,    65,    25,    76,
      77,    33,    80,    53,    82,    83,    85,    86,    87,   123,
     124,   166,   167,   127,    66,   129,   130,    54,    67,   133,
     134,   117,   118,   108,   109,   110,   111,   112,   113,   114,
      61,    62,    81,    93,   183,    94,    97,   106,   187,    98,
      36,    59,   191,   126,   115,   116,   125,   136,   194,   195,
     196,   197,   198,   138,   200,   142,   117,   118,   204,   119,
     205,   144,   146,   143,   171,   173,   117,   147,   148,    74,
     149,   210,   212,   174,   192,   164,   216,   176,   168,   218,
     178,   220,   172,   222,   179,   217,   180,   181,   207,   228,
     182,   230,   234,   231,   232,   104,   105,   193,   213,   223,
     112,   113,   114,   239,   224,   241,   233,   243,   226,   235,
     237,   240,   246,   242,   247,   244,   248,   115,   116,   245,
      57,   184,   141,   121,     0,   188,     0,     0,   190,   117,
     118,   107,     0,     0,   151,     0,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   206,    36,     0,
       0,     0,     0,   170,     0,     0,     0,   209,   211,     0,
       0,     0,     0,     0,    37,    38,   219,     0,   221,     0,
       0,     0,   177,     0,     0,     0,     0,     0,     2,     0,
       0,    39,     0,    40,    41,   108,   109,   110,   111,   112,
     113,   114,     0,     0,   185,   186,     0,     0,     0,   189,
       0,     0,     0,     0,     0,     0,   115,   116,   108,   109,
     110,   111,   112,   113,   114,     0,     0,     0,   117,   118,
     122,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   108,   109,   110,   111,   112,   113,   114,     0,     0,
       0,   117,   118,   201,     0,     0,     0,     0,     0,     0,
       0,     0,   115,   116,   108,   109,   110,   111,   112,   113,
     114,     0,     0,     0,   117,   118,   202,     0,     0,     0,
       0,     0,     0,     0,   150,   115,   116,   108,   109,   110,
     111,   112,   113,   114,     0,     0,     0,   117,   118,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118
};

static const yytype_int16 yycheck[] =
{
      20,    21,    91,     4,    93,    25,   183,     4,     5,     6,
     187,     7,    25,    34,    34,    35,    36,    19,    62,    33,
      40,    22,    42,   200,     3,    45,    23,   204,   205,     3,
      27,    33,    45,     3,    54,     0,    33,    16,    34,   216,
       7,   218,    16,   220,    88,    30,    16,    33,    34,    46,
     139,   228,    72,   230,    33,     4,    76,    77,    33,    33,
      80,    81,    82,    83,    84,    85,    86,    87,     2,    25,
      15,     5,    28,    32,    24,    25,    61,    62,    29,    30,
      14,    15,    16,    33,    24,    42,    24,   107,    73,    18,
      41,    42,     4,    33,    28,    33,    30,     4,     5,   119,
      32,    32,   122,    34,    31,     4,     5,     6,    33,    43,
      44,     4,    46,    19,    48,    49,    50,    51,    52,    76,
      77,    35,    36,    80,    23,    82,    83,    45,    27,    86,
      87,    41,    42,     8,     9,    10,    11,    12,    13,    14,
      27,    27,    32,    24,   164,     8,    24,    46,   168,     4,
       4,    25,   172,    24,    29,    30,     8,    25,   178,   179,
     180,   181,   182,    32,   184,    26,    41,    42,   188,    44,
     190,     8,    28,    26,     8,     5,    41,    28,    28,    41,
      28,   201,   202,    32,    31,   119,   206,    32,   122,   209,
      32,   211,    38,   213,    32,     5,    32,    32,    31,   219,
      32,   221,    33,   223,   224,    67,    68,    32,    32,    32,
      12,    13,    14,   233,    32,   235,    32,   237,    26,    32,
      32,    17,   242,    32,   244,    32,     3,    29,    30,    33,
      35,   165,    94,    73,    -1,   169,    -1,    -1,   172,    41,
      42,    69,    -1,    -1,   106,    -1,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   191,     4,    -1,
      -1,    -1,    -1,   125,    -1,    -1,    -1,   201,   202,    -1,
      -1,    -1,    -1,    -1,    20,    21,   210,    -1,   212,    -1,
      -1,    -1,   144,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    37,    -1,    39,    40,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,   166,   167,    -1,    -1,    -1,   171,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    30,     8,     9,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    34,    48,    49,    51,    33,    49,     0,     7,
      49,    52,     4,    33,    15,    18,    57,    58,    32,     4,
      49,    49,    49,    31,    32,    33,    50,    53,    54,    19,
      50,    59,    50,     4,    56,    49,     4,    20,    21,    37,
      39,    40,    49,    60,    61,    62,    63,    64,    67,    68,
      69,    70,    71,    19,    45,    24,    50,    53,    24,    25,
      50,    27,    27,     4,     5,     6,    23,    27,    46,    50,
      62,    65,    66,    50,    65,    59,    49,    49,    24,    50,
      49,    32,    49,    49,    32,    49,    49,    49,    50,     3,
      16,    33,    55,    24,     8,     4,     5,    24,     4,    62,
       4,    22,    56,    62,    65,    65,    46,    66,     8,     9,
      10,    11,    12,    13,    14,    29,    30,    41,    42,    44,
      50,    64,    43,    59,    59,     8,    24,    59,    50,    59,
      59,    50,    50,    59,    59,    56,    25,    55,    32,    33,
      55,    65,    26,    26,     8,    28,    28,    28,    28,    28,
      28,    65,    50,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    49,    50,    35,    36,    49,    50,
      65,     8,    38,     5,    32,    55,    32,    65,    32,    32,
      32,    32,    32,    50,    49,    65,    65,    50,    49,    65,
      49,    50,    31,    32,    50,    50,    50,    50,    50,    58,
      50,    43,    43,    58,    50,    50,    49,    31,    58,    49,
      50,    49,    50,    32,    58,    58,    50,     5,    50,    49,
      50,    49,    50,    32,    32,    58,    26,    58,    50,    58,
      50,    50,    50,    32,    33,    32,    58,    32,    58,    50,
      17,    50,    32,    50,    32,    33,    50,    50,     3
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    53,    53,    54,    54,    54,    54,    55,    55,
      56,    56,    57,    58,    58,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    60,    60,    60,    60,    60,    60,    61,    61,
      61,    61,    62,    62,    63,    63,    64,    64,    64,    64,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    66,    66,    66,
      66,    66,    66,    67,    67,    67,    67,    67,    67,    67,
      67,    68,    68,    69,    69,    70,    70,    70,    70,    71,
      71,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     2,     1,     2,     1,     5,     4,
       4,     2,     3,     2,     7,     6,     5,     6,     1,    11,
       4,     1,     2,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     4,     4,     4,     4,     4,     4,     3,
       2,     1,     5,     5,     6,     6,     5,     6,     5,     5,
       6,     6,     4,     4,     2,     3,     4,     5,     4,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     1,     2,     3,     1,     1,     1,
       1,     1,     3,    10,    10,    11,    11,    11,    11,    12,
      12,     2,     3,     6,     7,     8,     9,     9,    10,     7,
       8,     8,     9
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
#line 560 "ERROR404.y"
                                                                   {
        printf("Valid Input\n");
        fflush(stdout);
        (yyval.node) = makeNode("valid_prog", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 1);
        
        root = (yyvsp[-1].node);
        //printTree($$, 0);
}
#line 1969 "y.tab.c"
    break;

  case 3: /* valid_prog: initial_block var_block final_begin_end_block  */
#line 569 "ERROR404.y"
                                                {
        printf("Valid Input\n");
        fflush(stdout);
        (yyval.node) = makeNode("valid_prog", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);
        
        root = (yyvsp[0].node);
        //printTree($$, 0);
}
#line 1984 "y.tab.c"
    break;

  case 8: /* initial_block: newlines_p key_prog space id semicolon  */
#line 585 "ERROR404.y"
                                                     {
        (yyval.node) = makeNode("initial_block", -1);
        struct Node* temp = makeNode((yyvsp[-1].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);}
#line 1993 "y.tab.c"
    break;

  case 9: /* initial_block: key_prog space id semicolon  */
#line 589 "ERROR404.y"
                                         {
        (yyval.node) = makeNode("initial_block", -1);
        struct Node* temp = makeNode((yyvsp[-1].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);}
#line 2002 "y.tab.c"
    break;

  case 10: /* var_block: newlines_p key_var newlines_p dec_block  */
#line 595 "ERROR404.y"
                                                 {
                (yyval.node) = makeNode("var_block", -1);
                
                (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 0);
                
             }
#line 2013 "y.tab.c"
    break;

  case 11: /* var_block: newlines_p key_var  */
#line 602 "ERROR404.y"
                            {
                (yyval.node) = makeNode("var_block", -1);
                
               
             }
#line 2023 "y.tab.c"
    break;

  case 12: /* dec_block: dec_statement newlines_p dec_block  */
#line 608 "ERROR404.y"
                                            {
                (yyval.node) = makeNode("dec_block", -1);
                (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);
             }
#line 2033 "y.tab.c"
    break;

  case 13: /* dec_block: dec_statement newlines_p  */
#line 613 "ERROR404.y"
                                  {
                (yyval.node) = makeNode("dec_block", -1);
                (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);
             }
#line 2042 "y.tab.c"
    break;

  case 14: /* dec_statement: spaces_p id_list spaces_p colon space dec_type semicolon  */
#line 619 "ERROR404.y"
                                                                        {
                        (yyval.node) = makeNode("dec_statement", -1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-5].node), 0);
                        
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 1);

                        
                        if(strcmp((yyvsp[-1].node)->name,"array") ==0){
                                for (int i = 0; i < id_list_count; i++) {
                                        int start = atoi((yyvsp[-1].node)->children[0]->name);
                                        int end = atoi((yyvsp[-1].node)->children[1]->name);
                                        int ind = findInSymTable(str_arr[i]);
                                        if(ind !=-1){
                                                printf("Array %s Re-declared\n",str_arr[i]);
                                        }

                                        if (start > end) {
                                                printf("Array %s start index greater than end index\n",str_arr[i]);
                                                // yyerror();
                                        }
                                        for(int j = start; j <= end; j++) {
                                                char temp[20];
                                                sprintf(temp, "%s", str_arr[i]);
                                                strcpy(sym_table[sym_ptr].name, temp);
                                                sym_table[sym_ptr].type = (yyvsp[-1].node)->type;
                                                sym_table[sym_ptr].ind = j;
                                                
                                                sym_ptr++;

                                                // int ind = findInSymTable(str_arr[i]);
                                                // if(ind !=-1) printf("Variable %s Re-declared\n",str_arr[i]);
                                                // sprintf(sym_table[sym_ptr].name, "%s[%d]", str_arr[i], j);
                                                // sym_table[sym_ptr].type = $6->type;
                                                // sym_ptr++;
                                        }
                                        
                                }
                        }
                        else{
                        for (int i = 0; i < id_list_count; i++) {
                                int ind = findInSymTable(str_arr[i]);
                                if(ind !=-1) printf("Variable %s Re-declared\n",str_arr[i]);
                                strcpy(sym_table[sym_ptr].name, str_arr[i]);
                                sym_table[sym_ptr].type = (yyvsp[-1].node)->type;
                                sym_table[sym_ptr].ind = -1;
                                sym_ptr++;
                        }}
                        id_list_count = 0;
                }
#line 2096 "y.tab.c"
    break;

  case 15: /* dec_statement: spaces_p id_list colon space dec_type semicolon  */
#line 668 "ERROR404.y"
                                                                  {
                        (yyval.node) = makeNode("dec_statement", -1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-4].node), 0);
                        
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 1);

                        if(strcmp((yyvsp[-1].node)->name,"array") ==0){
                                for (int i = 0; i < id_list_count; i++) {
                                        int start = atoi((yyvsp[-1].node)->children[0]->name);
                                        int end = atoi((yyvsp[-1].node)->children[1]->name);
                                        int ind = findInSymTable(str_arr[i]);
                                        if(ind !=-1){
                                                printf("Array %s Re-declared\n",str_arr[i]);
                                        }

                                        if (start > end) {
                                                printf("Array %s start index greater than end index\n",str_arr[i]);
                                                // yyerror();
                                        }
                                        for(int j = start; j <= end; j++) {
                                                char temp[20];
                                                sprintf(temp, "%s", str_arr[i]);
                                                strcpy(sym_table[sym_ptr].name, temp);
                                                sym_table[sym_ptr].type = (yyvsp[-1].node)->type;
                                                sym_table[sym_ptr].ind = j;
                                                
                                                sym_ptr++;

                                                // int ind = findInSymTable(str_arr[i]);
                                                // if(ind !=-1) printf("Variable %s Re-declared\n",str_arr[i]);
                                                // sprintf(sym_table[sym_ptr].name, "%s[%d]", str_arr[i], j);
                                                // sym_table[sym_ptr].type = $6->type;
                                                // sym_ptr++;
                                        }
                                        
                                }
                        }
                        else{
                        for (int i = 0; i < id_list_count; i++) {
                                int ind = findInSymTable(str_arr[i]);
                                if(ind !=-1) printf("Variable %s Re-declared\n",str_arr[i]);
                                strcpy(sym_table[sym_ptr].name, str_arr[i]);
                                sym_table[sym_ptr].type = (yyvsp[-1].node)->type;
                                sym_table[sym_ptr].ind = -1;
                                sym_ptr++;
                        }}
                        id_list_count = 0;
                }
#line 2149 "y.tab.c"
    break;

  case 16: /* dec_statement: spaces_p id_list colon dec_type semicolon  */
#line 716 "ERROR404.y"
                                                            {
                        (yyval.node) = makeNode("dec_statement", -1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-3].node), 0);
                        
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 1);

                        if(strcmp((yyvsp[-1].node)->name,"array") ==0){
                                for (int i = 0; i < id_list_count; i++) {
                                        int start = atoi((yyvsp[-1].node)->children[0]->name);
                                        int end = atoi((yyvsp[-1].node)->children[1]->name);
                                        int ind = findInSymTable(str_arr[i]);
                                        if(ind !=-1){
                                                printf("Array %s Re-declared\n",str_arr[i]);
                                        }

                                        if (start > end) {
                                                printf("Array %s start index greater than end index\n",str_arr[i]);
                                                // yyerror();
                                        }
                                        for(int j = start; j <= end; j++) {
                                                char temp[20];
                                                sprintf(temp, "%s", str_arr[i]);
                                                strcpy(sym_table[sym_ptr].name, temp);
                                                sym_table[sym_ptr].type = (yyvsp[-1].node)->type;
                                                sym_table[sym_ptr].ind = j;
                                                
                                                sym_ptr++;

                                                // int ind = findInSymTable(str_arr[i]);
                                                // if(ind !=-1) printf("Variable %s Re-declared\n",str_arr[i]);
                                                // sprintf(sym_table[sym_ptr].name, "%s[%d]", str_arr[i], j);
                                                // sym_table[sym_ptr].type = $6->type;
                                                // sym_ptr++;
                                        }
                                        // printf("%d\n",$5->type);
                                }
                        }
                        else{
                        for (int i = 0; i < id_list_count; i++) {
                                int ind = findInSymTable(str_arr[i]);
                                if(ind !=-1) printf("Variable %s Re-declared\n",str_arr[i]);
                                strcpy(sym_table[sym_ptr].name, str_arr[i]);
                                sym_table[sym_ptr].type = (yyvsp[-1].node)->type;
                                sym_table[sym_ptr].ind = -1;
                                sym_ptr++;
                        }}
                        id_list_count = 0;
                }
#line 2202 "y.tab.c"
    break;

  case 17: /* dec_statement: spaces_p id_list spaces_p colon dec_type semicolon  */
#line 764 "ERROR404.y"
                                                                     {
                        (yyval.node) = makeNode("dec_statement", -1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-4].node), 0);
                        
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 1);

                        
                        if(strcmp((yyvsp[-1].node)->name,"array") ==0){
                                for (int i = 0; i < id_list_count; i++) {
                                        int start = atoi((yyvsp[-1].node)->children[0]->name);
                                        int end = atoi((yyvsp[-1].node)->children[1]->name);
                                        int ind = findInSymTable(str_arr[i]);
                                        if(ind !=-1){
                                                printf("Array %s Re-declared\n",str_arr[i]);
                                        }

                                        if (start > end) {
                                                printf("Array %s start index greater than end index\n",str_arr[i]);
                                                // yyerror();
                                        }
                                        for(int j = start; j <= end; j++) {
                                                char temp[20];
                                                sprintf(temp, "%s", str_arr[i]);
                                                strcpy(sym_table[sym_ptr].name, temp);
                                                sym_table[sym_ptr].type = (yyvsp[-1].node)->type;
                                                sym_table[sym_ptr].ind = j;
                                                
                                                sym_ptr++;

                                                // int ind = findInSymTable(str_arr[i]);
                                                // if(ind !=-1) printf("Variable %s Re-declared\n",str_arr[i]);
                                                // sprintf(sym_table[sym_ptr].name, "%s[%d]", str_arr[i], j);
                                                // sym_table[sym_ptr].type = $6->type;
                                                // sym_ptr++;
                                        }
                                        // printf("%d\n",$5->type);
                                }
                        }
                        else{
                        for (int i = 0; i < id_list_count; i++) {
                                int ind = findInSymTable(str_arr[i]);
                                if(ind !=-1) printf("Variable %s Re-declared\n",str_arr[i]);
                                strcpy(sym_table[sym_ptr].name, str_arr[i]);
                                sym_table[sym_ptr].type = (yyvsp[-1].node)->type;
                                sym_table[sym_ptr].ind = -1;
                                sym_ptr++;
                        }}
                        id_list_count = 0;
                }
#line 2256 "y.tab.c"
    break;

  case 18: /* dec_type: key_type  */
#line 814 "ERROR404.y"
                   {
        
        struct Node* temp = makeNode((yyvsp[0].strval), -1);
        (yyval.node) = temp;

        
        if(strcmp((yyvsp[0].strval),"integer")==0){
                
                (yyval.node)->type = 1;
        }
        else if(strcmp((yyvsp[0].strval),"real")==0){
                (yyval.node)->type = 2;
        }
        else if(strcmp((yyvsp[0].strval),"boolean")==0){
                (yyval.node)->type = 4;
        }
        else if(strcmp((yyvsp[0].strval),"char")==0){
                (yyval.node)->type = 3;
        }
        }
#line 2281 "y.tab.c"
    break;

  case 19: /* dec_type: key_arr open_s num dot dot num close_s space key_of space key_type  */
#line 835 "ERROR404.y"
                                                                             {
        (yyval.node) = makeNode("array", -1);
        
        struct Node* temp2 = makeNode((yyvsp[-8].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp2, 0);
        struct Node* temp3 = makeNode((yyvsp[-5].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp3, 1);
        struct Node* temp4 = makeNode((yyvsp[0].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp4, 2);

        if(strcmp((yyvsp[0].strval),"integer")==0){
                (yyval.node)->type = 1;
        }
        else if(strcmp((yyvsp[0].strval),"real")==0){
                (yyval.node)->type = 2;
        }
        else if(strcmp((yyvsp[0].strval),"boolean")==0){
                (yyval.node)->type = 4;
        }
        else if(strcmp((yyvsp[0].strval),"char")==0){
                (yyval.node)->type = 3;
        }

        }
#line 2310 "y.tab.c"
    break;

  case 20: /* id_list: id comma spaces_p id_list  */
#line 860 "ERROR404.y"
                                   {
        (yyval.node) = makeNode("id_list", -1);
        struct Node* temp = makeNode((yyvsp[-3].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);
        
        strcpy(str_arr[id_list_count], (yyvsp[-3].strval)); id_list_count++;}
#line 2322 "y.tab.c"
    break;

  case 21: /* id_list: id  */
#line 867 "ERROR404.y"
            {
        (yyval.node) = makeNode("id_list", -1);
        struct Node* temp = makeNode((yyvsp[0].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);
        strcpy(str_arr[id_list_count], (yyvsp[0].strval)); id_list_count++;}
#line 2332 "y.tab.c"
    break;

  case 22: /* final_begin_end_block: begin_end_block dot  */
#line 873 "ERROR404.y"
                                         {
        (yyval.node) = (yyvsp[-1].node);
}
#line 2340 "y.tab.c"
    break;

  case 23: /* begin_end_block: key_begin newlines_p content key_end  */
#line 877 "ERROR404.y"
                                                    {
        (yyval.node) = (yyvsp[-1].node);
}
#line 2348 "y.tab.c"
    break;

  case 24: /* begin_end_block: key_begin newlines_p key_end  */
#line 879 "ERROR404.y"
                              {
        (yyval.node) = makeNode("begin_end_block", -1);
}
#line 2356 "y.tab.c"
    break;

  case 25: /* content: spaces_p write_statement newlines_p  */
#line 883 "ERROR404.y"
                                            { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);}
#line 2362 "y.tab.c"
    break;

  case 26: /* content: spaces_p read_statement newlines_p  */
#line 884 "ERROR404.y"
                                           { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);}
#line 2368 "y.tab.c"
    break;

  case 27: /* content: spaces_p assign_statement newlines_p  */
#line 885 "ERROR404.y"
                                             { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);}
#line 2374 "y.tab.c"
    break;

  case 28: /* content: spaces_p if_statement newlines_p  */
#line 886 "ERROR404.y"
                                         { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);}
#line 2380 "y.tab.c"
    break;

  case 29: /* content: spaces_p if_else_statement newlines_p  */
#line 887 "ERROR404.y"
                                             { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);}
#line 2386 "y.tab.c"
    break;

  case 30: /* content: spaces_p for_statement newlines_p  */
#line 888 "ERROR404.y"
                                          { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);}
#line 2392 "y.tab.c"
    break;

  case 31: /* content: spaces_p while_statement newlines_p  */
#line 889 "ERROR404.y"
                                            { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);}
#line 2398 "y.tab.c"
    break;

  case 32: /* content: spaces_p write_statement newlines_p content  */
#line 890 "ERROR404.y"
                                                    { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0); (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);}
#line 2404 "y.tab.c"
    break;

  case 33: /* content: spaces_p read_statement newlines_p content  */
#line 891 "ERROR404.y"
                                                   { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0); (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);}
#line 2410 "y.tab.c"
    break;

  case 34: /* content: spaces_p assign_statement newlines_p content  */
#line 892 "ERROR404.y"
                                                    { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0); (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);}
#line 2416 "y.tab.c"
    break;

  case 35: /* content: spaces_p if_statement newlines_p content  */
#line 893 "ERROR404.y"
                                                { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0); (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);}
#line 2422 "y.tab.c"
    break;

  case 36: /* content: spaces_p if_else_statement newlines_p content  */
#line 894 "ERROR404.y"
                                                      { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0); (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);}
#line 2428 "y.tab.c"
    break;

  case 37: /* content: spaces_p for_statement newlines_p content  */
#line 895 "ERROR404.y"
                                                  { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0); (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);}
#line 2434 "y.tab.c"
    break;

  case 38: /* content: spaces_p while_statement newlines_p content  */
#line 896 "ERROR404.y"
                                                    { (yyval.node) = makeNode("content", -1); (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0); (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);}
#line 2440 "y.tab.c"
    break;

  case 39: /* content: spaces_p newlines_p content  */
#line 897 "ERROR404.y"
                                    {(yyval.node) = (yyvsp[0].node);}
#line 2446 "y.tab.c"
    break;

  case 40: /* content: spaces_p newlines_p  */
#line 898 "ERROR404.y"
                             {(yyval.node) = makeNode("content", -1);}
#line 2452 "y.tab.c"
    break;

  case 41: /* content: spaces_p  */
#line 900 "ERROR404.y"
                {(yyval.node) = makeNode("content", -1);}
#line 2458 "y.tab.c"
    break;

  case 42: /* write_statement: key_write open_b quoted_string close_b semicolon  */
#line 902 "ERROR404.y"
                                                                  { 
        (yyval.node) = makeNode("write", -1); 
        struct Node* temp = makeNode((yyvsp[-2].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);
        }
#line 2468 "y.tab.c"
    break;

  case 43: /* write_statement: key_write open_b id_list close_b semicolon  */
#line 907 "ERROR404.y"
                                                           {
                // printf("here without spaces\n");
        (yyval.node) = makeNode("write", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
               }
#line 2478 "y.tab.c"
    break;

  case 44: /* write_statement: key_write open_b quoted_string close_b semicolon spaces_p  */
#line 912 "ERROR404.y"
                                                                          { 
        (yyval.node) = makeNode("write", -1); 
        struct Node* temp = makeNode((yyvsp[-3].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);
        }
#line 2488 "y.tab.c"
    break;

  case 45: /* write_statement: key_write open_b id_list close_b semicolon spaces_p  */
#line 917 "ERROR404.y"
                                                                    {
                printf("here with spaces\n");
        (yyval.node) = makeNode("write", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-3].node), 0);
        }
#line 2498 "y.tab.c"
    break;

  case 46: /* write_statement: key_write open_b array_id close_b semicolon  */
#line 922 "ERROR404.y"
                                                              {
                (yyval.node) = makeNode("write", -1);
                (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
        }
#line 2507 "y.tab.c"
    break;

  case 47: /* write_statement: key_write open_b array_id close_b semicolon spaces_p  */
#line 926 "ERROR404.y"
                                                                       {
                (yyval.node) = makeNode("write", -1);
                (yyval.node) = connectChild((yyval.node), (yyvsp[-3].node), 0);
        }
#line 2516 "y.tab.c"
    break;

  case 48: /* read_statement: key_read open_b id close_b semicolon  */
#line 931 "ERROR404.y"
                                                    {
        (yyval.node) = makeNode("read", -1);
        struct Node* temp = makeNode((yyvsp[-2].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);
        int ind = findInSymTable((yyvsp[-2].strval));
        if (ind != -1) {
                sym_table[ind].initial = true;
               }
        else {
                printf("Variable %s not declared\n",(yyvsp[-2].strval));
                // yyerror();
        }
}
#line 2534 "y.tab.c"
    break;

  case 49: /* read_statement: key_read open_b array_id close_b semicolon  */
#line 944 "ERROR404.y"
                                                          {
                (yyval.node) = makeNode("read", -1);
                (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                
                int ind = findInSymTable((yyvsp[-2].node)->children[0]->name);
                while(strcmp(sym_table[ind].name,(yyvsp[-2].node)->children[0]->name)==0){
                        sym_table[ind].initial = true;
                        ind++;
                }

              }
#line 2550 "y.tab.c"
    break;

  case 50: /* read_statement: key_read open_b id close_b semicolon spaces_p  */
#line 955 "ERROR404.y"
                                                             {
        (yyval.node) = makeNode("read", -1);
        struct Node* temp = makeNode((yyvsp[-3].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);
        int ind = findInSymTable((yyvsp[-3].strval));
        if (ind != -1) {
                sym_table[ind].initial = true;
               }
        else {
                printf("Variable %s not declared\n",(yyvsp[-3].strval));
                // yyerror();
        }
               }
#line 2568 "y.tab.c"
    break;

  case 51: /* read_statement: key_read open_b array_id close_b semicolon spaces_p  */
#line 968 "ERROR404.y"
                                                                   {
                (yyval.node) = makeNode("read", -1);
                (yyval.node) = connectChild((yyval.node), (yyvsp[-3].node), 0);
                int ind = findInSymTable((yyvsp[-3].node)->children[0]->name);
                while(strcmp(sym_table[ind].name,(yyvsp[-3].node)->children[0]->name)==0){
                        sym_table[ind].initial = true;
                        ind++;
                }
                
              }
#line 2583 "y.tab.c"
    break;

  case 52: /* array_id: id open_s num close_s  */
#line 979 "ERROR404.y"
                               { (yyval.node)=makeNode("array_id",-1); struct Node* temp = makeNode((yyvsp[-3].strval),-1); (yyval.node) = connectChild((yyval.node),temp,0); struct Node* temp2 = makeNode((yyvsp[-1].strval),-1); (yyval.node) = connectChild((yyval.node),temp2,1);
                int ind = findInSymTable((yyvsp[-3].strval));
                if (ind != -1) {
                        if (sym_table[ind].initial) {
                                (yyval.node)->type = sym_table[ind].type;
                        } else {
                                printf("Variable %s not initialized\n",(yyvsp[-3].strval));
                                // yyerror();
                        }
                }
                else {
                        printf("Variable %s not declared\n",(yyvsp[-3].strval));
                }
}
#line 2602 "y.tab.c"
    break;

  case 53: /* array_id: id open_s id close_s  */
#line 993 "ERROR404.y"
                             { (yyval.node)=makeNode("array_id",-1); struct Node* temp = makeNode((yyvsp[-3].strval),-1); (yyval.node) = connectChild((yyval.node),temp,0); struct Node* temp2 = makeNode((yyvsp[-1].strval),-1); (yyval.node) = connectChild((yyval.node),temp2,1);
                int ind = findInSymTable((yyvsp[-3].strval));
                if (ind != -1) {
                        if (sym_table[ind].initial) {
                                (yyval.node)->type = sym_table[ind].type;
                        } else {
                                // printf("Variable %s not initialized\n",$1);
                                printf("Variable %s not initialized\n",(yyvsp[-3].strval));
                                // yyerror();
                        }
                }
                else {
                        printf("Variable %s not declared\n",(yyvsp[-3].strval));
                }}
#line 2621 "y.tab.c"
    break;

  case 54: /* assign_statement: assign_statement_ws semicolon  */
#line 1008 "ERROR404.y"
                                                {(yyval.node) = (yyvsp[-1].node);}
#line 2627 "y.tab.c"
    break;

  case 55: /* assign_statement: assign_statement_ws semicolon spaces_p  */
#line 1009 "ERROR404.y"
                                                       {(yyval.node) = (yyvsp[-2].node);}
#line 2633 "y.tab.c"
    break;

  case 56: /* assign_statement_ws: id colon equal exp  */
#line 1011 "ERROR404.y"
                                       {
        (yyval.node) = makeNode("assign_statement", -1);
        struct Node* temp = makeNode((yyvsp[-3].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);
        int ind = findInSymTable((yyvsp[-3].strval));
        if (ind != -1) {
        
                if (sym_table[ind].type == (yyvsp[0].node)->type 
                || (sym_table[ind].type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "1") == 0 ))
                || (sym_table[ind].type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "0") == 0 ))
                ||(sym_table[ind].type == 2 && (yyvsp[0].node)->type == 1) ) {
                        sym_table[ind].initial = true;
                        
                } else {
                        printf("Type mismatch %s assigned to %s\n",numToType(sym_table[ind].type),numToType((yyvsp[0].node)->type));
                       
                        //yyerror();
                }
        } else {
                printf("Variable %s not declared\n",(yyvsp[-3].strval));
                // yyerror();
        }
}
#line 2662 "y.tab.c"
    break;

  case 57: /* assign_statement_ws: id spaces_p colon equal exp  */
#line 1035 "ERROR404.y"
                                             {
                        
        (yyval.node) = makeNode("assign_statement", -1);
        struct Node* temp = makeNode((yyvsp[-4].strval), -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);
        int ind = findInSymTable((yyvsp[-4].strval));
        if (ind != -1) {
                if (sym_table[ind].type == (yyvsp[0].node)->type 
                || (sym_table[ind].type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "1") == 0 ))|| (sym_table[ind].type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "0") == 0 ))
                ||(sym_table[ind].type == 2 && (yyvsp[0].node)->type == 1) )
                {
                        // bool val = true;
                        // printf("%d\n",sym_table[ind].initial);
                        sym_table[ind].initial = true;
                } else {
                        printf("Type mismatch %s assigned to %s\n",numToType(sym_table[ind].type),numToType((yyvsp[0].node)->type));

                        //yyerror();
                }
        } else {
                printf("Variable %s not declared\n",(yyvsp[-4].strval));
                // yyerror();
        }
}
#line 2692 "y.tab.c"
    break;

  case 58: /* assign_statement_ws: array_id colon equal exp  */
#line 1060 "ERROR404.y"
                          {
        (yyval.node) = makeNode("assign_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-3].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);
        int ind = findInSymTable((yyvsp[-3].node)->children[0]->name);
        if (ind != -1) {
                if (sym_table[ind].type == (yyvsp[0].node)->type 
                || (sym_table[ind].type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "1") == 0 ))|| (sym_table[ind].type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "0") == 0 ))
                ||(sym_table[ind].type == 2 && (yyvsp[0].node)->type == 1) ){
                        // bool val = true;
                        // printf("%d\n",sym_table[ind].initial);
                        ind=findExactArrayInd((yyvsp[-3].node)->children[0]->name,atoi((yyvsp[-3].node)->children[1]->name));
                        sym_table[ind].initial = true;
                } else {
                        printf("Type mismatch %s assigned to %s\n",numToType(sym_table[ind].type),numToType((yyvsp[0].node)->type));

                        //yyerror();
                }
        }

        else {
                printf("Variable %s not declared\n",(yyvsp[-3].node)->children[0]->name);
                // yyerror();
        }
}
#line 2722 "y.tab.c"
    break;

  case 59: /* assign_statement_ws: array_id spaces_p colon equal exp  */
#line 1085 "ERROR404.y"
                                           {
        (yyval.node) = makeNode("assign_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-4].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);
        int ind = findInSymTable((yyvsp[-4].node)->children[0]->name);
        if (ind != -1) {
                if (sym_table[ind].type == (yyvsp[0].node)->type|| (sym_table[ind].type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "1") == 0 )) || (sym_table[ind].type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "0") == 0 ))||((yyvsp[-4].node)->type == 2 && (yyvsp[0].node)->type == 1))
                {
                        // bool val = true;
                        // printf("%d\n",sym_table[ind].initial);
                        ind=findExactArrayInd((yyvsp[-4].node)->children[0]->name,atoi((yyvsp[-4].node)->children[1]->name));
                        sym_table[ind].initial = true;
                } else {
                        printf("Type mismatch %s assigned to %s\n",numToType(sym_table[ind].type),numToType((yyvsp[0].node)->type));

                        //yyerror();
                }
        } else {
                printf("Variable %s not declared\n",(yyvsp[-4].node)->children[0]->name);
                // yyerror();
        }
}
#line 2749 "y.tab.c"
    break;

  case 60: /* exp: exp op_plus exp  */
#line 1108 "ERROR404.y"
                    {
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode("+", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 1) 
                        {
                                (yyval.node)->type = 1;
                        }
                        else if((yyvsp[-2].node)->type==(yyvsp[0].node)->type && (yyvsp[-2].node)->type == 2) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else if((yyvsp[-2].node)->type==1 && (yyvsp[0].node)->type==2) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else if((yyvsp[-2].node)->type==2 && (yyvsp[0].node)->type==1) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else {
                                printf("Type mismatch %s added to %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));
// yyerror();
                        }
        }
#line 2782 "y.tab.c"
    break;

  case 61: /* exp: exp op_minus exp  */
#line 1137 "ERROR404.y"
                          {
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode("-", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 1) 
                        {
                                (yyval.node)->type = 1;
                        }
                        else if((yyvsp[-2].node)->type==(yyvsp[0].node)->type && (yyvsp[-2].node)->type == 2) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else if((yyvsp[-2].node)->type==1 && (yyvsp[0].node)->type==2) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else if((yyvsp[-2].node)->type==2 && (yyvsp[0].node)->type==1) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else {
                                printf("Type mismatch %s subtracted by %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));

                        }
        }
#line 2815 "y.tab.c"
    break;

  case 62: /* exp: exp op_mult exp  */
#line 1165 "ERROR404.y"
                    {
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode("*", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 1) 
                        {
                                (yyval.node)->type = 1;
                        }
                        else if((yyvsp[-2].node)->type==(yyvsp[0].node)->type && (yyvsp[-2].node)->type == 2) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else if((yyvsp[-2].node)->type==1 && (yyvsp[0].node)->type==2) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else if((yyvsp[-2].node)->type==2 && (yyvsp[0].node)->type==1) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else {
                                printf("Type mismatch %s multipled by %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));
// yyerror();
                        }
        }
#line 2848 "y.tab.c"
    break;

  case 63: /* exp: exp op_div exp  */
#line 1193 "ERROR404.y"
                   {
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode("/", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 1) 
                        {
                                (yyval.node)->type = 1;
                        }
                        else if((yyvsp[-2].node)->type==(yyvsp[0].node)->type && (yyvsp[-2].node)->type == 2) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else if((yyvsp[-2].node)->type==1 && (yyvsp[0].node)->type==2) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else if((yyvsp[-2].node)->type==2 && (yyvsp[0].node)->type==1) 
                        {
                                (yyval.node)->type = 2;
                        }
                        else {
                                 printf("Type mismatch %s divided by %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));

                        }
        }
#line 2881 "y.tab.c"
    break;

  case 64: /* exp: exp op_mod exp  */
#line 1221 "ERROR404.y"
                   {
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode("%", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 1) 
                        {
                                (yyval.node)->type = 1;
                        }
                        
                        else {
                                printf("Type mismatch %s modulo by %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));

                        }
        }
#line 2903 "y.tab.c"
    break;

  case 65: /* exp: exp key_and exp  */
#line 1238 "ERROR404.y"
                    {
                        
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode("and", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 4) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type == 1 && (yyvsp[0].node)->type == 4 && (strcmp((yyvsp[-2].node)->children[0]->name, "1" == 0) || strcmp((yyvsp[-2].node)->children[0]->name, "1") == 0)) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "1" == 0) || strcmp((yyvsp[0].node)->children[0]->name, "1") == 0)) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else {
                                 printf("Both operands should be boolean but they were %s and %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));

                        }

                        }
#line 2934 "y.tab.c"
    break;

  case 66: /* exp: exp key_or exp  */
#line 1265 "ERROR404.y"
                   {
                        
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode("or", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 4) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type == 1 && (yyvsp[0].node)->type == 4 && (strcmp((yyvsp[-2].node)->children[0]->name, "1" == 0) || strcmp((yyvsp[-2].node)->children[0]->name, "1") == 0)) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "1" == 0) || strcmp((yyvsp[0].node)->children[0]->name, "1") == 0)) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else {
                                 printf("Both operands should be boolean but they were %s and %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));

                        }
        
                                 

                        }
#line 2967 "y.tab.c"
    break;

  case 67: /* exp: exp greater exp  */
#line 1293 "ERROR404.y"
                    {
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode(">", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 1) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==(yyvsp[0].node)->type && (yyvsp[-2].node)->type == 2) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==1 && (yyvsp[0].node)->type==2) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==2 && (yyvsp[0].node)->type==1) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else {
                                printf("Type mismatch %s greater than %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));
                        }
        }
#line 2999 "y.tab.c"
    break;

  case 68: /* exp: exp lesser exp  */
#line 1321 "ERROR404.y"
                   {
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode("<", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 1) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==(yyvsp[0].node)->type && (yyvsp[-2].node)->type == 2) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==1 && (yyvsp[0].node)->type==2) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==2 && (yyvsp[0].node)->type==1) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else {
                                 printf("Type mismatch %s less than %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));
                        }
        }
#line 3031 "y.tab.c"
    break;

  case 69: /* exp: exp not_equal exp  */
#line 1348 "ERROR404.y"
                      {
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode("<>", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 1) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==(yyvsp[0].node)->type && (yyvsp[-2].node)->type == 2) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==1 && (yyvsp[0].node)->type==2) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==2 && (yyvsp[0].node)->type==1) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==4 && (yyvsp[0].node)->type==4) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type == 1 && (yyvsp[0].node)->type == 4 && (strcmp((yyvsp[-2].node)->children[0]->name, "1" == 0) || strcmp((yyvsp[-2].node)->children[0]->name, "1") == 0)) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "1" == 0) || strcmp((yyvsp[0].node)->children[0]->name, "1") == 0)) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else {
                               printf("Type mismatch %s not equal to %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));

                        }
        }
#line 3076 "y.tab.c"
    break;

  case 70: /* exp: exp equal exp  */
#line 1388 "ERROR404.y"
                   {
                        (yyval.node) = makeNode("exp", (yyvsp[-2].node)->type);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 0);
                        struct Node* temp = makeNode("=", -1);
                        (yyval.node) = connectChild((yyval.node), temp, 1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 2);

                        if((yyvsp[-2].node)->type==(yyvsp[0].node)->type &&  (yyvsp[-2].node)->type == 1) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==(yyvsp[0].node)->type && (yyvsp[-2].node)->type == 2) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==1 && (yyvsp[0].node)->type==2) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==2 && (yyvsp[0].node)->type==1) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type==4 && (yyvsp[0].node)->type==4) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type == 1 && (yyvsp[0].node)->type == 4 && (strcmp((yyvsp[-2].node)->children[0]->name, "1" == 0) || strcmp((yyvsp[-2].node)->children[0]->name, "1") == 0)) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if((yyvsp[-2].node)->type == 4 && (yyvsp[0].node)->type == 1 && (strcmp((yyvsp[0].node)->children[0]->name, "1" == 0) || strcmp((yyvsp[0].node)->children[0]->name, "1") == 0)) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else {
                                 printf("Type mismatch %s equal %s\n",numToType((yyvsp[-2].node)->type),numToType((yyvsp[0].node)->type));

                        }
        }
#line 3121 "y.tab.c"
    break;

  case 71: /* exp: spaces_p key_not exp  */
#line 1428 "ERROR404.y"
                        {
        (yyval.node) = makeNode("exp", 0);
        struct Node* temp = makeNode("!", -1);
        (yyval.node) = connectChild((yyval.node), temp, 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);

                        if((yyvsp[0].node)->type == 4) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if ((yyvsp[0].node)->type == 1 && strcmp((yyvsp[0].node)->children[0]->name,"1") == 0) {
                                (yyval.node)->type = 4;
                        }
                        else {
                                 printf("operand should be boolean but they were \n",numToType((yyvsp[0].node)->type));

                        }
   }
#line 3144 "y.tab.c"
    break;

  case 72: /* exp: key_not exp  */
#line 1446 "ERROR404.y"
               {
        (yyval.node) = makeNode("!", 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 0);

                        if((yyvsp[0].node)->type == 4) 
                        {
                                (yyval.node)->type = 4;
                        }
                        else if ((yyvsp[0].node)->type == 1 && strcmp((yyvsp[0].node)->children[0]->name,"1") == 0) {
                                (yyval.node)->type = 4;
                        }
                        else {
                                 printf("operand should be boolean but they were \n",numToType((yyvsp[0].node)->type));

                        }
   }
#line 3165 "y.tab.c"
    break;

  case 73: /* exp: name spaces_p  */
#line 1462 "ERROR404.y"
                  {
                (yyval.node) = makeNode("exp", (yyvsp[-1].node)->type);
                (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);
        }
#line 3174 "y.tab.c"
    break;

  case 74: /* exp: name  */
#line 1466 "ERROR404.y"
         {
                (yyval.node) = makeNode("exp", (yyvsp[0].node)->type);
                (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 0);
        }
#line 3183 "y.tab.c"
    break;

  case 75: /* exp: spaces_p name  */
#line 1470 "ERROR404.y"
                  {
                //printf("Variable  not initialized\n");
                (yyval.node) = makeNode("exp", (yyvsp[0].node)->type);
                (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 0);
        }
#line 3193 "y.tab.c"
    break;

  case 76: /* exp: spaces_p name spaces_p  */
#line 1475 "ERROR404.y"
                           {
        
                (yyval.node) = makeNode("exp", (yyvsp[-1].node)->type);
                (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 0);
        }
#line 3203 "y.tab.c"
    break;

  case 77: /* name: num  */
#line 1481 "ERROR404.y"
            {      
                (yyval.node) = makeNode((yyvsp[0].strval), 1);
        }
#line 3211 "y.tab.c"
    break;

  case 78: /* name: num_real  */
#line 1484 "ERROR404.y"
                  {
                (yyval.node) = makeNode((yyvsp[0].strval), 2);
        }
#line 3219 "y.tab.c"
    break;

  case 79: /* name: id  */
#line 1487 "ERROR404.y"
            {
                (yyval.node) = makeNode((yyvsp[0].strval), 0);

                int ind = findInSymTable((yyvsp[0].strval));
                if (ind != -1) {
                        if (sym_table[ind].initial) {
                                (yyval.node) = makeNode((yyvsp[0].strval), sym_table[ind].type);
                        } else {
                                printf("Variable %s not initialized\n",(yyvsp[0].strval));
                                // yyerror();
                        }
                }
                else {
                        printf("Variable %s not declared\n",(yyvsp[0].strval));
                }
        }
#line 3240 "y.tab.c"
    break;

  case 80: /* name: quoted_char  */
#line 1503 "ERROR404.y"
                     {
                (yyval.node) = makeNode((yyvsp[0].strval), 3);
        }
#line 3248 "y.tab.c"
    break;

  case 81: /* name: array_id  */
#line 1506 "ERROR404.y"
                  {(yyval.node) = (yyvsp[0].node);}
#line 3254 "y.tab.c"
    break;

  case 82: /* name: open_b exp close_b  */
#line 1507 "ERROR404.y"
                            {(yyval.node) = (yyvsp[-1].node);}
#line 3260 "y.tab.c"
    break;

  case 83: /* for_statement: key_for spaces_p assign_statement_ws key_to exp key_do newlines_p spaces_p begin_end_block semicolon  */
#line 1509 "ERROR404.y"
                                                                                                                        {
        (yyval.node) = makeNode("for_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-7].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-5].node), 1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 2);
}
#line 3271 "y.tab.c"
    break;

  case 84: /* for_statement: key_for spaces_p assign_statement_ws key_downto exp key_do newlines_p spaces_p begin_end_block semicolon  */
#line 1514 "ERROR404.y"
                                                                                                                  {
        (yyval.node) = makeNode("for_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-7].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-5].node), 1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 2);
}
#line 3282 "y.tab.c"
    break;

  case 85: /* for_statement: key_for spaces_p assign_statement_ws key_to exp key_do spaces_p newlines_p spaces_p begin_end_block semicolon  */
#line 1519 "ERROR404.y"
                                                                                                                       {
        (yyval.node) = makeNode("for_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-8].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-6].node), 1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 2);
}
#line 3293 "y.tab.c"
    break;

  case 86: /* for_statement: key_for spaces_p assign_statement_ws key_downto exp key_do spaces_p newlines_p spaces_p begin_end_block semicolon  */
#line 1524 "ERROR404.y"
                                                                                                                          {
        (yyval.node) = makeNode("for_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-8].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-6].node), 1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 2);
}
#line 3304 "y.tab.c"
    break;

  case 87: /* for_statement: key_for spaces_p assign_statement_ws key_to exp key_do newlines_p spaces_p begin_end_block semicolon spaces_p  */
#line 1529 "ERROR404.y"
                                                                                                                       {
        (yyval.node) = makeNode("for_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-8].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-6].node), 1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 2);
}
#line 3315 "y.tab.c"
    break;

  case 88: /* for_statement: key_for spaces_p assign_statement_ws key_downto exp key_do newlines_p spaces_p begin_end_block semicolon spaces_p  */
#line 1534 "ERROR404.y"
                                                                                                                           {
        (yyval.node) = makeNode("for_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-8].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-6].node), 1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 2);
}
#line 3326 "y.tab.c"
    break;

  case 89: /* for_statement: key_for spaces_p assign_statement_ws key_to exp key_do spaces_p newlines_p spaces_p begin_end_block semicolon spaces_p  */
#line 1539 "ERROR404.y"
                                                                                                                                {
        (yyval.node) = makeNode("for_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-9].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-7].node), 1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 2);
}
#line 3337 "y.tab.c"
    break;

  case 90: /* for_statement: key_for spaces_p assign_statement_ws key_downto exp key_do spaces_p newlines_p spaces_p begin_end_block semicolon spaces_p  */
#line 1544 "ERROR404.y"
                                                                                                                                   {
        (yyval.node) = makeNode("for_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-9].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-7].node), 1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 2);
}
#line 3348 "y.tab.c"
    break;

  case 91: /* if_statement: if_statement_ws semicolon  */
#line 1551 "ERROR404.y"
                                       {(yyval.node) = (yyvsp[-1].node);}
#line 3354 "y.tab.c"
    break;

  case 92: /* if_statement: if_statement_ws semicolon spaces_p  */
#line 1552 "ERROR404.y"
                                               {(yyval.node) = (yyvsp[-2].node);}
#line 3360 "y.tab.c"
    break;

  case 93: /* if_statement_ws: key_if exp key_then newlines_p spaces_p begin_end_block  */
#line 1554 "ERROR404.y"
                                                                         {
        (yyval.node) = makeNode("if_statement", -1); 
        (yyval.node) = connectChild((yyval.node), (yyvsp[-4].node), 0); 
        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);
        }
#line 3370 "y.tab.c"
    break;

  case 94: /* if_statement_ws: key_if exp key_then spaces_p newlines_p spaces_p begin_end_block  */
#line 1559 "ERROR404.y"
                                                                                  {
        (yyval.node) = makeNode("if_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-5].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[0].node), 1);
               }
#line 3380 "y.tab.c"
    break;

  case 95: /* if_else_statement: if_statement_ws newlines_p spaces_p key_else newlines_p spaces_p begin_end_block semicolon  */
#line 1565 "ERROR404.y"
                                                                                                            {
        (yyval.node) = makeNode("if_else_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-7].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 1);
        }
#line 3390 "y.tab.c"
    break;

  case 96: /* if_else_statement: if_statement_ws newlines_p spaces_p key_else spaces_p newlines_p spaces_p begin_end_block semicolon  */
#line 1571 "ERROR404.y"
                                                                                                                     {
                        (yyval.node) = makeNode("if_else_statement", -1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-8].node), 0);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 1);
                 }
#line 3400 "y.tab.c"
    break;

  case 97: /* if_else_statement: if_statement_ws newlines_p spaces_p key_else newlines_p spaces_p begin_end_block semicolon spaces_p  */
#line 1576 "ERROR404.y"
                                                                                                                     {
                        (yyval.node) = makeNode("if_else_statement", -1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-8].node), 0);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 1);
                 }
#line 3410 "y.tab.c"
    break;

  case 98: /* if_else_statement: if_statement_ws newlines_p spaces_p key_else spaces_p newlines_p spaces_p begin_end_block semicolon spaces_p  */
#line 1581 "ERROR404.y"
                                                                                                                              {
                        (yyval.node) = makeNode("if_else_statement", -1);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-9].node), 0);
                        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 1);
                 
                 }
#line 3421 "y.tab.c"
    break;

  case 99: /* while_statement: key_while exp key_do newlines_p spaces_p begin_end_block semicolon  */
#line 1589 "ERROR404.y"
                                                                                    {
        (yyval.node) = makeNode("while_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-5].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 1);
        }
#line 3431 "y.tab.c"
    break;

  case 100: /* while_statement: key_while exp key_do spaces_p newlines_p spaces_p begin_end_block semicolon  */
#line 1596 "ERROR404.y"
                                                                                             {
        (yyval.node) = makeNode("while_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-6].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-1].node), 1);
               }
#line 3441 "y.tab.c"
    break;

  case 101: /* while_statement: key_while exp key_do newlines_p spaces_p begin_end_block semicolon spaces_p  */
#line 1601 "ERROR404.y"
                                                                                             {
        (yyval.node) = makeNode("while_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-6].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 1);

               }
#line 3452 "y.tab.c"
    break;

  case 102: /* while_statement: key_while exp key_do spaces_p newlines_p spaces_p begin_end_block semicolon spaces_p  */
#line 1607 "ERROR404.y"
                                                                                                      {
        (yyval.node) = makeNode("while_statement", -1);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-7].node), 0);
        (yyval.node) = connectChild((yyval.node), (yyvsp[-2].node), 1);

               }
#line 3463 "y.tab.c"
    break;


#line 3467 "y.tab.c"

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

#line 1613 "ERROR404.y"


int main(int argc, char* argv[]) {
        char* filename = argv[1];
        printf("\n");

        yyin = fopen(filename, "r");

        int ptr = 0;
        while (ptr++ < 500) {
                sym_table[ptr].initial = false;
        }

        for (int i = 0; i < 500; i++)
                strcpy(sym_table[i].value, "-1");

        yyparse();
        FILE* file = fopen("syntaxtree.txt", "w");
        writeTreeToFile(root, file);

        solveTree(root);
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("OUTPUT OF THE PROGRAM\n");
        printf("---------------------------------------------------------------------------------------------------\n");

        int eo_sym_table = sym_ptr;
        int count =0;
        for(int i=0; i<quad_ptr; i++)
        {       
        
        fflush(stdout);

        char temp1[100];
        strcpy(temp1, quad[i].arg1);
        if (strcmp(temp1, "") != 0) {
                if(findIfArray(temp1))
                {
                        char*temp = getArrName(temp1);
                        int temp_ind=getArrInd(temp1);
                        int ind = findExactArrayInd(temp, temp_ind);
                        strcpy(temp1,sym_table[ind].value);
                }
                else {
                        int ind1 = findInSymTable(temp1);
                        /* printf("Index is %d    %s\n", ind1, quad[i].arg1); */
                        if (ind1 != -1){
                                /* printf("%s index %d\n", quad[i].arg1, ind1); */
                                strcpy(temp1,sym_table[ind1].value);
                                /* printf("%s index %d\n", quad[i].arg1, ind1); */
                        }
                }
        }
        

        //..............................................................
        char temp2[100];
        strcpy(temp2, quad[i].arg2);
        if (strcmp(temp2, "") != 0) {
                if(findIfArray(temp2))
                {
                        char*temp=getArrName(temp2);
                        int temp_ind=getArrInd(temp2);
                        int ind = findExactArrayInd(temp, temp_ind);
                        strcpy(temp2, sym_table[ind].value);
                }

                int ind2 = findInSymTable(temp2);
                if (ind2 != -1)
                        strcpy(temp2,sym_table[ind2].value);
        }
        else

        /* printf("Arg2: %s\n", temp2); */
        fflush(stdout);
        //..............................................................

        if(strcmp(quad[i].op,"j")==0)
        {
                /* printf("Inside Jump\n"); */
                fflush(stdout);
                i = atoi(quad[i].result) - 1;
        }

        else if(strcmp(quad[i].op,"jg")==0)
        {
                /* printf("Inside Jump Greater\n"); */
                /* printf("%s\n", quad[i].arg1); */
                fflush(stdout);
                if(atoi(temp1)>atoi(temp2))
                {
                        i = atoi(quad[i].result)-1;
                }

        }

        else if (strcmp(quad[i].op,"jne")==0)
        {
                /* printf(" inside jne %s",temp1); */
                if(
                        atoi(temp1) == 0)
                {
                     i=atoi(quad[i].result)-1;   
                }
        }

        else if (strcmp(quad[i].op,"assign")==0)
        {
                if(findIfArray(quad[i].result))
                {
                        char*temp=getArrName(quad[i].result);
                        int temp_ind=getArrInd(quad[i].result);
                        int ind=findExactArrayInd(temp,temp_ind);
                        strcpy(sym_table[ind].value, temp1);
                }
                else
                {
                        int ind=findInSymTable(quad[i].result);
                        if(ind == -1)
                        {
                                strcpy(sym_table[sym_ptr].name, quad[i].result);
                                strcpy(sym_table[sym_ptr].value, temp1);
                                sym_ptr++;
                        }
                        else
                                strcpy(sym_table[ind].value, temp1);
                }

        }

        else if(strcmp(quad[i].op,"read")==0)
        {
                /* printf("Inside Read\n"); */
                fflush(stdout);
                int ind;
                char temp[100];
                if (findIfArray(quad[i].result)) {
                        ind = findInSymTable(getArrName(quad[i].result));
                        if (ind == -1)
                                printf("Variable not declared\n");
                        ind=findExactArrayInd(getArrName(quad[i].result),getArrInd(quad[i].result));
                        
                        scanf("%s",temp);
                        if (sym_table[ind].type != find_data_type(temp)) {
                                printf("Type mismatch\n");
                                // yyerror();
                        }
                } else {
                        /* printf("Not Array\n"); */
                        ind = findInSymTable(quad[i].result);
                        if (ind == -1)
                                printf("Variable not declared\n");
                        
                        scanf("%s",temp);
                        if (sym_table[ind].type != find_data_type(temp)) {
                                printf("Type mismatch\n");
                                // yyerror();
                        }
                        strcpy(sym_table[ind].value,temp);
                }
                strcpy(sym_table[ind].value,temp); //number should also be in string format
        }

        else if(strcmp(quad[i].op,"write")==0)
        {
                if (quad[i].result[0] == '"')
                        printf("%s\n", quad[i].result);
                else if (findIfArray(quad[i].result)) {
                        char*temp = getArrName(quad[i].result);
                        int temp_ind=getArrInd(quad[i].result);
                        int ind = findExactArrayInd(temp, temp_ind);
                        printf("%s\n", sym_table[ind].value);
                }
                else if (findIfIdList(quad[i].result)) {
                        char* token = strtok(quad[i].result, ",");
                        while (token != NULL) {
                                int ind = findInSymTable(token);
                                if (ind != -1) {
                                        printf("%s\n", sym_table[ind].value);
                                }
                                else {
                                        printf("Variable %s not declared\n", token);
                                }
                                token = strtok(NULL, ",");
                        }
                }
                else {
                        int ind = findInSymTable(quad[i].result);
                        if (ind != -1) {
                                printf("%s\n", sym_table[ind].value);
                        }
                        else {
                                printf("Variable %s not declared\n",quad[i].result);
                        }
                }
        }

        else
        {
                int t1, t2;
                char temp = quad[i].op[0]; 
                switch(temp)
                {
                        case '+':
                                
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);
                                
                                //int ind=findinSymTable(quad[i].result);
                                if(t1==1 && t2==1)
                                {       
                                        int a = atoi(temp1) + atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=1;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==2 && t2==2)
                                {
                                        float a=atof(temp1)+atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==1 && t2==2)
                                {
                                        float a=atoi(temp1)+atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==2 && t2==1)
                                {
                                        float a=atof(temp1)+atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }

                        sym_ptr++;
                        break;

                        case '-':
                                
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);
                                if(t1==1 && t2==1)
                                {
                                        int a=atoi(temp1)-atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=1;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==2 && t2==2)
                                {
                                        float a=atof(temp1)-atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==1 && t2==2)
                                {
                                        float a=atof(temp1)-atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==2 && t2==1)
                                {
                                        float a=atof(temp1)-atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                sym_ptr++;
                                break;
                        case '*':
                                
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);
                                if(t1==1 && t2==1)
                                {
                                        int a=atoi(temp1)*atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=1;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==2 && t2==2)
                                {
                                        float a=atof(temp1)*atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==1 && t2==2)
                                {
                                        float a=atof(temp1)*atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                        }
                                }
                                else if(t1==2 && t2==1)
                                {
                                        float a=atof(temp1)*atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                        }
                                }
                                sym_ptr++;
                                break;
                        case '/':
                                
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);
                                
                                if(t1==1 && t2==1)
                                {
                                        int a=atoi(temp1)/atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=1;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                        }
                                }
                                else if(t1==2 && t2==2)
                                {
                                        float a=atof(temp1)/atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                        }
                                }
                                else if(t1==1 && t2==2)
                                {
                                        float a=atof(temp1)/atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                        }
                                }
                                else if(t1==2 && t2==1)
                                {
                                        float a=atof(temp1)/atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                sym_ptr++;
                                break;

                        case '%':
                                
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);
                                
                                if(t1==1 && t2==1)
                                {
                                        int a=atoi(temp1)%atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=1;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else
                                {
                                        printf("Type mismatch\n");
                                }
                                sym_ptr++;
                                break;

                        case '>':
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);

                                if(t1==1 && t2==1)
                                {
                                        int a=atoi(temp1)>atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=4;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==2 && t2==2)
                                {
                                        int a=atof(temp1)>atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else
                                {
                                        printf("Type mismatch\n");
                                }
                                sym_ptr++;
                                break;
                        case '<':
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);

                                if(t1==1 && t2==1)
                                {
                                        int a=atoi(temp1)<atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=4;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==2 && t2==2)
                                {
                                        int a=atof(temp1)<atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else
                                {
                                        printf("Type mismatch\n");
                                }
                                sym_ptr++;
                                break;

                        case '=':
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);
                                 
                                if(t1==1 && t2==1)
                                {
                                        int a=atoi(temp1)==atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=4;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==2 && t2==2)
                                {
                                        int a=atof(temp1)==atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else
                                {
                                        printf("Type mismatch\n");
                                }
                                sym_ptr++;
                                break;

                        case 'x':
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);
                                if(t1==1 && t2==1)
                                {
                                        int a=atoi(temp1)!=atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=4;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else if(t1==2 && t2==2)
                                {
                                        int a=atof(temp1)!=atof(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%f",a);
                                                sym_table[sym_ptr].type=2;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%f", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else
                                {
                                        printf("Type mismatch\n");
                                }
                                sym_ptr++;
                                break;

                        case 'a':
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);

                                if(t1==4 && t2==4)
                                {
                                        int a=atoi(temp1) && atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=4;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else
                                {
                                        printf("Type mismatch\n");
                                }
                                sym_ptr++;
                                break;
                        
                        case 'o':
                                t1=find_data_type(temp1);
                                t2=find_data_type(temp2);

                                if(t1==4 && t2==4)
                                {
                                        int a=atoi(temp1) || atoi(temp2);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=4;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else
                                {
                                        printf("Type mismatch\n");
                                }
                                sym_ptr++;
                                break;
                        
                        case '!':
                                t1=find_data_type(temp1);

                                if(t1==4)
                                {
                                        int a=!atoi(temp1);
                                        if (findInSymTable(quad[i].result) == -1) {
                                                strcpy(sym_table[sym_ptr].name,quad[i].result);
                                                sprintf(sym_table[sym_ptr].value,"%d",a);
                                                sym_table[sym_ptr].type=4;
                                        }
                                        else {
                                                char tempa[50];
                                                sprintf(tempa, "%d", a);
                                                strcpy(sym_table[findInSymTable(quad[i].result)].value, tempa);
                                                /* printf("Value of %s is %s\n", quad[i].result, sym_table[findInSymTable(quad[i].result)].value); */
                                        }
                                }
                                else
                                {
                                        printf("Type mismatch\n");
                                }
                                sym_ptr++;
                                break; 
                             
                }
        }
}

        printf("---------------------------------------------------------------------------------------------------\n");
        printf("SYMBOL TABLE\n");
        printf("---------------------------------------------------------------------------------------------------\n");
        printSymTableTillInd(eo_sym_table);

        fclose(file);
        fclose(yyin);
        
        freeTree(root);
        return 0;
}

void yyerror()
{
        printf("syntax error\n"); 
        exit(0);
}
