%{
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include "tree_builder.c"

extern FILE *yyin;

typedef struct sym_val {
        char name[100];
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

%}

%union {
        Node* node;
}

%token <strval> key_type
%token <strval> id
%token <strval> num
%token <strval> num_real


%type <strval> id_list
%type <strval> dec_type
%type <strval> dec_statement
%type <strval> exp
%type <strval> name
%type <strval> assign_statement_ws
%type <strval> assign_statement

%token op_plus op_mult op_minus op_div op_mod colon open_s close_s open_b close_b lesser greater not_equal equal quotes dot semicolon space newline quoted_string key_prog key_downto key_var key_to key_if key_else key_for key_while key_and key_or key_not key_arr key_of key_begin key_end key_read key_write key_do key_then comma

%right equal not_equal
%left op_plus op_minus
%left op_mult op_div op_mod
%left greater lesser
%left key_or
%left key_and
%%

valid_prog:initial_block var_block final_begin_end_block newlines_p{
        printf("valid input\n");

        // print all the values in the symbol table including initial
        for (int i = 0; i < sym_ptr; i++) {
                printf("%s %s %s\n", sym_table[i].name, sym_table[i].type, sym_table[i].value);
        }
};
newlines_p:newline newlines_p
          |newline;
          
spaces_p:space spaces_p
        |space;
        
initial_block:newlines_p key_prog space id semicolon
             |key_prog space id semicolon;
             
var_block:newlines_p key_var newlines_p dec_block
         |newlines_p key_var;
         
dec_block:dec_statement newlines_p dec_block
         |dec_statement newlines_p;
         
dec_statement: spaces_p id_list spaces_p colon space dec_type semicolon {
                        // printf("DEC: %d\n", sym_ptr);
                        // for (int i = 0; i < id_list_count; i++) {
                        //         sym_ptr--;
                        //         strcpy(sym_table[sym_ptr].type, $6);
                        // }
                        // sym_ptr += id_list_count;
                        // id_list_count = 0;
                        for (int i = 0; i < id_list_count; i++) {
                                strcpy(sym_table[sym_ptr].name, str_arr[i]);
                                strcpy(sym_table[sym_ptr].type, $6);
                                sym_ptr++;
                        }
                        id_list_count = 0;
                }
                | spaces_p id_list colon space dec_type semicolon {
                        // printf("DEC: %d\n", sym_ptr);
                        // for (int i = 0; i < id_list_count; i++) {
                        //         sym_ptr--;
                        //         strcpy(sym_table[sym_ptr].type, $5);
                        // }
                        // sym_ptr += id_list_count;
                        // id_list_count = 0;
                        for (int i = 0; i < id_list_count; i++) {
                                strcpy(sym_table[sym_ptr].name, str_arr[i]);
                                strcpy(sym_table[sym_ptr].type, $5);
                                sym_ptr++;
                        }
                        id_list_count = 0;
                };

dec_type: key_type {strcpy($$, $1);}
        | key_arr open_s num dot dot num close_s space key_of space key_type {strcpy($$, $11);};

id_list: id comma spaces_p id_list {strcpy(str_arr[id_list_count], $1); id_list_count++;} 
       | id {strcpy(str_arr[id_list_count], $1); id_list_count++;};
       
final_begin_end_block:begin_end_block dot;

begin_end_block:key_begin newlines_p content key_end|key_begin newlines_p key_end;

content:spaces_p write_statement newlines_p
       |spaces_p read_statement newlines_p
       |spaces_p assign_statement newlines_p
       |spaces_p for_statement newlines_p
       |spaces_p if_statement newlines_p
       |spaces_p if_else_statement newlines_p
       |spaces_p while_statement newlines_p
       |spaces_p write_statement newlines_p content
       |spaces_p read_statement newlines_p content
       |spaces_p assign_statement newlines_p content
       |spaces_p for_statement newlines_p content
       |spaces_p if_statement newlines_p content
       |spaces_p if_else_statement newlines_p content
       |spaces_p while_statement newlines_p content
       |spaces_p newlines_p content
       |spaces_p;

write_statement: key_write open_b quoted_string close_b semicolon
	       | key_write open_b id_list close_b semicolon
	       | key_write open_b quoted_string close_b semicolon spaces_p
	       | key_write open_b id_list close_b semicolon spaces_p;
	       
read_statement: key_read open_b id close_b semicolon
	      | key_read open_b array_id close_b semicolon
	      | key_read open_b id close_b semicolon spaces_p
	      | key_read open_b array_id close_b semicolon spaces_p;
	      
array_id:id open_s num close_s
	|id open_s id close_s;
	
assign_statement: assign_statement_ws semicolon
		|assign_statement_ws semicolon spaces_p;
		
assign_statement_ws:id colon equal exp {
        int ind = findInSymTable($1);
        if (ind != -1) {
                if (strcmp(sym_table[ind].type, "4") == 0){
                        if (isBool($4) == 1) {
                                sym_table[ind].initial = true;
                                strcpy(sym_table[ind].value, $4);
                        } else {
                                // printf("Variable: %s\n", $1);
                                // printf("Symbol Table Type: %s\n", sym_table[ind].type);
                                // printf("Type mismatch\n");
                                yyerror();
                        }
                }
                else if (atoi(sym_table[ind].type) == findType($4)) {
                        sym_table[ind].initial = true;
                        strcpy(sym_table[ind].value, $4);
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
                |id spaces_p colon equal exp {
        int ind = findInSymTable($1);
        if (ind != -1) {
                if (strcmp(sym_table[ind].type, "4") == 0) {
                        if (isBool($5) == 1) {
                                sym_table[ind].initial = true;
                                strcpy(sym_table[ind].value, $5);
                        } else {
                                // printf("Variable: %s\n", $1);
                                // printf("Symbol Table Type: %s\n", sym_table[ind].type);
                                // printf("Type mismatch\n");
                                yyerror();
                        }
                }
                else if (atoi(sym_table[ind].type) == findType($5)) {
                        sym_table[ind].initial = true;
                        strcpy(sym_table[ind].value, $5);
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
};
		   
exp:exp op_plus exp {
                        if(findType($1)==findType($3) && findType($1) == 1) 
                        {
                                int a=atoi($1)+atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==findType($3) && findType($1)==2) 
                        {
                                double a=atof($1)+atof($3);
                                sprintf($$, "%f", a);
                        }

                        else if(findType($1)==1 && findType($3)==2) 
                        {
                                double a=atoi($1)+atof($3);
                                sprintf($$, "%f", a);
                        }

                        else if(findType($1)==2 && findType($3)==1) 
                        {
                                double a=atof($1)+atoi($3);
                                sprintf($$, "%f", a);
                        }

                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

        }

        |exp op_minus exp {
                        if(findType($1)==findType($3) && findType($1)==1) 
                        {
                                int a=atoi($1) - atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==findType($3) && findType($1)==2) 
                        {
                                double a=atof($1) - atof($3);
                                sprintf($$, "%f", a);
                        }

                        else if(findType($1)==1 && findType($3)==2) 
                        {
                                double a=atoi($1) - atof($3);
                                sprintf($$, "%f", a);
                        }

                        else if(findType($1)==2 && findType($3)==1) 
                        {
                                double a=atof($1) - atoi($3);
                                sprintf($$, "%f", a);
                        }

                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
   |exp op_mult exp {
                        if(findType($1)==findType($3) && findType($1)==1) 
                        {
                                int a=atoi($1)+atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==findType($3) && findType($1)==2) 
                        {
                                double a=atof($1)+atof($3);
                                sprintf($$, "%f", a);
                        }

                        else if(findType($1)==1 && findType($3)==2) 
                        {
                                double a=atoi($1)+atof($3);
                                sprintf($$, "%f", a);
                        }

                        else if(findType($1)==2 && findType($3)==1) 
                        {
                                double a=atof($1)+atoi($3);
                                sprintf($$, "%f", a);
                        }

                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
   |exp op_div exp {
                        if(findType($1)==findType($3) && findType($1)==1) 
                        {
                                int a=atoi($1)+atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==findType($3) && findType($1)==2) 
                        {
                                double a=atof($1)+atof($3);
                                sprintf($$, "%f", a);
                        }

                        else if(findType($1)==1 && findType($3) == 2) 
                        {
                                double a=atoi($1)+atof($3);
                                sprintf($$, "%f", a);
                        }

                        else if(findType($1)==2 && findType($3)==1) 
                        {
                                double a=atof($1)+atoi($3);
                                sprintf($$, "%f", a);
                        }

                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
   |exp op_mod exp {
                        if(findType($1)==findType($3) && findType($1)==1) 
                        {
                                int a=atoi($1)+atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==findType($3) && findType($1)==2) 
                        {
                                double a=atof($1)+atof($3);
                                sprintf($$, "%f", a);
                        }

                        else if(findType($1)==1 && findType($3)==2) 
                        {
                                double a=atoi($1)+atof($3);
                                sprintf($$, "%f", a);
                        }

                        else if(findType($1)==2 && findType($3)==1) 
                        {
                                double a=atof($1)+atoi($3);
                                sprintf($$, "%f", a);
                        }

                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
   |exp key_and exp {
                        if(isBool($1)==isBool($3) && isBool($1)==1) 
                        {
                                int a=atoi($1)&&atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
   
   |exp key_or exp {
                        if(isBool($1)==isBool($3) && isBool($1)==1) 
                        {
                                int a=atoi($1)||atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
   |exp greater exp {
                        if(findType($1)==findType($3) && findType($1)==1) 
                        {
                                int a=atoi($1)>atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==findType($3) && findType($1)==2) 
                        {
                                int a=atof($1)>atof($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==1 && findType($3)==2) 
                        {
                                int a=atoi($1)>atof($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==2 && findType($3)==1) 
                        {
                                int a=atof($1)>atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }


   |exp lesser exp {
                        if(findType($1)==findType($3) && findType($1)==1) 
                        {
                                int a=atoi($1)<atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==findType($3) && findType($1)==2) 
                        {
                                int a=atof($1)<atof($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==1 && findType($3)==2) 
                        {
                                int a=atoi($1)<atof($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==2 && findType($3)==1) 
                        {
                                int a=atof($1)<atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
   |exp not_equal exp {
                        if(findType($1)==findType($3) && findType($1) == 1) 
                        {
                                int a=atoi($1)!=atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==findType($3) && findType($1)==2) 
                        {
                                int a=atof($1)!=atof($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==1 && findType($3)==2) 
                        {
                                int a=atoi($1)!=atof($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==2 && findType($3)==1) 
                        {
                                int a=atof($1)!=atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(isBool($1)==isBool($3) && isBool($1)==1) 
                        {
                                int a=(atoi($1)!=atoi($3));
                                sprintf($$, "%d", a);
                        }

                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                                 

                        }
   |exp equal exp {
                        if(findType($1)==findType($3) && findType($1)==1) 
                        {
                                int a=atoi($1)==atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==findType($3) && findType($1)==2) 
                        {
                                int a=atof($1)==atof($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==1 && findType($3)==2) 
                        {
                                int a=atoi($1)==atof($3);
                                sprintf($$, "%d", a);
                        }

                        else if(findType($1)==2 && findType($3)==1) 
                        {
                                int a=atof($1)==atoi($3);
                                sprintf($$, "%d", a);
                        }

                        else if(isBool($1)==isBool($3) && isBool($1)==1) 
                        {
                                int a=(atoi($1)==atoi($3));
                                sprintf($$, "%d", a);
                        }
                        else {
                                printf("Inside Expression Statement\n");
                                printf("Type mismatch\n");yyerror();
                        }
                        }
   |name spaces_p {strcpy($$, $1);}
   |name {strcpy($$, $1);}
   |spaces_p name {strcpy($$, $2);}
   |spaces_p name spaces_p {strcpy($$, $2);};

name:num {strcpy($$, $1);}
        |num_real {strcpy($$, $1);}
        |id {
                int ind = findInSymTable($1);
                if (ind != -1) {
                        if (sym_table[ind].initial) {
                                strcpy($$, sym_table[ind].value);
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
        |array_id
	|open_b exp close_b;
	
for_statement: key_for spaces_p assign_statement_ws  key_to  exp  key_do newlines_p spaces_p  begin_end_block semicolon
	      | key_for spaces_p assign_statement_ws  key_downto  exp key_do newlines_p spaces_p begin_end_block semicolon     |key_for spaces_p assign_statement_ws  key_to  exp  key_do spaces_p newlines_p spaces_p  begin_end_block semicolon
	      | key_for spaces_p assign_statement_ws  key_downto  exp key_do spaces_p newlines_p spaces_p begin_end_block semicolon
	      |key_for spaces_p assign_statement_ws  key_to  exp  key_do newlines_p spaces_p  begin_end_block semicolon spaces_p
	      | key_for spaces_p assign_statement_ws  key_downto  exp key_do newlines_p spaces_p begin_end_block semicolon spaces_p    |key_for spaces_p assign_statement_ws  key_to  exp  key_do spaces_p newlines_p spaces_p  begin_end_block semicolon spaces_p
	      | key_for spaces_p assign_statement_ws  key_downto  exp key_do spaces_p newlines_p spaces_p begin_end_block semicolon spaces_p;

if_statement:if_statement_ws semicolon
	    |if_statement_ws semicolon spaces_p;

if_statement_ws:key_if  exp  key_then newlines_p spaces_p begin_end_block
	       |key_if  exp  key_then spaces_p newlines_p spaces_p begin_end_block;

if_else_statement:if_statement_ws newlines_p spaces_p key_else newlines_p spaces_p begin_end_block semicolon
                 |if_statement_ws newlines_p spaces_p key_else spaces_p newlines_p spaces_p begin_end_block semicolon
                 |if_statement_ws newlines_p spaces_p key_else newlines_p spaces_p begin_end_block semicolon spaces_p
                 |if_statement_ws newlines_p spaces_p key_else spaces_p newlines_p spaces_p begin_end_block semicolon spaces_p;


while_statement:key_while  exp  key_do newlines_p spaces_p begin_end_block semicolon
	       |key_while  exp  key_do spaces_p newlines_p spaces_p begin_end_block semicolon
	       |key_while  exp  key_do newlines_p spaces_p begin_end_block semicolon spaces_p
	       |key_while  exp  key_do spaces_p newlines_p spaces_p begin_end_block semicolon spaces_p;
%%

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
