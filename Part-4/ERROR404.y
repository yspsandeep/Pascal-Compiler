%{
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
        for (int i = 0; i < ind; i++) {
                printf("%s %d %d %s\n", sym_table[i].name, sym_table[i].ind,sym_table[i].type, sym_table[i].value);
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
 

%}
/* %parse-param {struct Node* root} */
%union {
        char strval[100];
        struct Node* node;
}

%token <strval> key_type
%token <strval> id
%token <strval> num
%token <strval> num_real
%token <strval> key_prog
%token <strval> equal
%token <strval> not_equal
%token <strval> op_plus
%token <strval> op_minus
%token <strval> op_mult
%token <strval> op_div
%token <strval> op_mod
%token <strval> key_var
%token <strval> key_arr
%token <strval> key_of
%token <strval> key_begin
%token <strval> key_end
%token <strval> key_read
%token <strval> key_write
%token <strval> quoted_string
%token <strval> quoted_char

%type <node> id_list
%type <node> dec_type
%type <node> dec_statement
%type <node> exp
%type <node> name
%type <node> assign_statement_ws
%type <node> assign_statement
%type <node> valid_prog
%type <node> initial_block
%type <node> var_block
%type <node> dec_block
%type <node> final_begin_end_block
%type <node> begin_end_block
%type <node> content
%type <node> write_statement
%type <node> read_statement
%type <node> array_id
%type <node> for_statement
%type <node> if_statement
%type <node> if_statement_ws
%type <node> if_else_statement
%type <node> while_statement



%token colon open_s close_s open_b close_b lesser greater  dot semicolon space newline  key_downto  key_to key_if key_else key_for key_while key_and key_or       key_do key_then comma

%right equal not_equal
%left op_plus op_minus
%left op_mult op_div op_mod
%left greater lesser
%left key_or
%left key_and
%left key_not
%%

valid_prog:initial_block var_block final_begin_end_block newlines_p{
        printf("Valid Input\n");
        fflush(stdout);
        $$ = makeNode("valid_prog", -1);
        $$ = connectChild($$, $2, 0);
        $$ = connectChild($$, $3, 1);
        
        root = $3;
        //printTree($$, 0);
}|initial_block var_block final_begin_end_block {
        printf("Valid Input\n");
        fflush(stdout);
        $$ = makeNode("valid_prog", -1);
        $$ = connectChild($$, $2, 0);
        $$ = connectChild($$, $3, 1);
        
        root = $3;
        //printTree($$, 0);
};
newlines_p:newline newlines_p
          |newline;
          
spaces_p:space spaces_p
        |space;
        
initial_block:newlines_p key_prog space id semicolon {
        $$ = makeNode("initial_block", -1);
        struct Node* temp = makeNode($4, -1);
        $$ = connectChild($$, temp, 0);}
             |key_prog space id semicolon{
        $$ = makeNode("initial_block", -1);
        struct Node* temp = makeNode($3, -1);
        $$ = connectChild($$, temp, 0);};
             
             
var_block:newlines_p key_var newlines_p dec_block{
                $$ = makeNode("var_block", -1);
                
                $$ = connectChild($$, $4, 0);
                
             }

         |newlines_p key_var{
                $$ = makeNode("var_block", -1);
                
               
             };
         
dec_block:dec_statement newlines_p dec_block{
                $$ = makeNode("dec_block", -1);
                $$ = connectChild($$, $1, 0);
                $$ = connectChild($$, $3, 1);
             }
         |dec_statement newlines_p{
                $$ = makeNode("dec_block", -1);
                $$ = connectChild($$, $1, 0);
             };

         
dec_statement: spaces_p id_list spaces_p colon space dec_type semicolon {
                        $$ = makeNode("dec_statement", -1);
                        $$ = connectChild($$, $2, 0);
                        
                        $$ = connectChild($$, $6, 1);

                        
                        if(strcmp($6->name,"array") ==0){
                                for (int i = 0; i < id_list_count; i++) {
                                        int start = atoi($6->children[0]->name);
                                        int end = atoi($6->children[1]->name);
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
                                                sym_table[sym_ptr].type = $6->type;
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
                                sym_table[sym_ptr].type = $6->type;
                                sym_table[sym_ptr].ind = -1;
                                sym_ptr++;
                        }}
                        id_list_count = 0;
                }
                | spaces_p id_list colon space dec_type semicolon {
                        $$ = makeNode("dec_statement", -1);
                        $$ = connectChild($$, $2, 0);
                        
                        $$ = connectChild($$, $5, 1);

                        if(strcmp($5->name,"array") ==0){
                                for (int i = 0; i < id_list_count; i++) {
                                        int start = atoi($5->children[0]->name);
                                        int end = atoi($5->children[1]->name);
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
                                                sym_table[sym_ptr].type = $5->type;
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
                                sym_table[sym_ptr].type = $5->type;
                                sym_table[sym_ptr].ind = -1;
                                sym_ptr++;
                        }}
                        id_list_count = 0;
                }
                | spaces_p id_list colon dec_type semicolon {
                        $$ = makeNode("dec_statement", -1);
                        $$ = connectChild($$, $2, 0);
                        
                        $$ = connectChild($$, $4, 1);

                        if(strcmp($4->name,"array") ==0){
                                for (int i = 0; i < id_list_count; i++) {
                                        int start = atoi($4->children[0]->name);
                                        int end = atoi($4->children[1]->name);
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
                                                sym_table[sym_ptr].type = $4->type;
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
                                sym_table[sym_ptr].type = $4->type;
                                sym_table[sym_ptr].ind = -1;
                                sym_ptr++;
                        }}
                        id_list_count = 0;
                }
                |spaces_p id_list spaces_p colon  dec_type semicolon {
                        $$ = makeNode("dec_statement", -1);
                        $$ = connectChild($$, $2, 0);
                        
                        $$ = connectChild($$, $5, 1);

                        
                        if(strcmp($5->name,"array") ==0){
                                for (int i = 0; i < id_list_count; i++) {
                                        int start = atoi($5->children[0]->name);
                                        int end = atoi($5->children[1]->name);
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
                                                sym_table[sym_ptr].type = $5->type;
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
                                sym_table[sym_ptr].type = $5->type;
                                sym_table[sym_ptr].ind = -1;
                                sym_ptr++;
                        }}
                        id_list_count = 0;
                };

dec_type: key_type {
        
        struct Node* temp = makeNode($1, -1);
        $$ = temp;

        
        if(strcmp($1,"integer")==0){
                
                $$->type = 1;
        }
        else if(strcmp($1,"real")==0){
                $$->type = 2;
        }
        else if(strcmp($1,"boolean")==0){
                $$->type = 4;
        }
        else if(strcmp($1,"char")==0){
                $$->type = 3;
        }
        }

        | key_arr open_s num dot dot num close_s space key_of space key_type {
        $$ = makeNode("array", -1);
        
        struct Node* temp2 = makeNode($3, -1);
        $$ = connectChild($$, temp2, 0);
        struct Node* temp3 = makeNode($6, -1);
        $$ = connectChild($$, temp3, 1);
        struct Node* temp4 = makeNode($11, -1);
        $$ = connectChild($$, temp4, 2);

        if(strcmp($11,"integer")==0){
                $$->type = 1;
        }
        else if(strcmp($11,"real")==0){
                $$->type = 2;
        }
        else if(strcmp($11,"boolean")==0){
                $$->type = 4;
        }
        else if(strcmp($11,"char")==0){
                $$->type = 3;
        }

        };

id_list: id comma spaces_p id_list {
        $$ = makeNode("id_list", -1);
        struct Node* temp = makeNode($1, -1);
        $$ = connectChild($$, temp, 0);
        $$ = connectChild($$, $4, 1);
        
        strcpy(str_arr[id_list_count], $1); id_list_count++;} 
       | id {
        $$ = makeNode("id_list", -1);
        struct Node* temp = makeNode($1, -1);
        $$ = connectChild($$, temp, 0);
        strcpy(str_arr[id_list_count], $1); id_list_count++;};
       
final_begin_end_block:begin_end_block dot{
        $$ = $1;
};

begin_end_block:key_begin newlines_p content key_end{
        $$ = $3;
}|key_begin newlines_p key_end{
        $$ = makeNode("begin_end_block", -1);
};

content:spaces_p write_statement newlines_p { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0);}
       |spaces_p read_statement newlines_p { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0);}
       |spaces_p assign_statement newlines_p { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0);}
       |spaces_p if_statement newlines_p { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0);}
       |spaces_p if_else_statement newlines_p{ $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0);}
       |spaces_p for_statement newlines_p { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0);}
       |spaces_p while_statement newlines_p { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0);}
       |spaces_p write_statement newlines_p content { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0); $$ = connectChild($$, $4, 1);}
       |spaces_p read_statement newlines_p content { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0); $$ = connectChild($$, $4, 1);}
       |spaces_p assign_statement newlines_p content{ $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0); $$ = connectChild($$, $4, 1);}
       |spaces_p if_statement newlines_p content{ $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0); $$ = connectChild($$, $4, 1);}
       |spaces_p if_else_statement newlines_p content { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0); $$ = connectChild($$, $4, 1);}
       |spaces_p for_statement newlines_p content { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0); $$ = connectChild($$, $4, 1);}
       |spaces_p while_statement newlines_p content { $$ = makeNode("content", -1); $$ = connectChild($$, $2, 0); $$ = connectChild($$, $4, 1);}
       |spaces_p newlines_p content {$$ = $3;}
       |spaces_p newlines_p  {$$ = makeNode("content", -1);}

       |spaces_p{$$ = makeNode("content", -1);};

write_statement: key_write open_b quoted_string close_b semicolon { 
        $$ = makeNode("write", -1); 
        struct Node* temp = makeNode($3, -1);
        $$ = connectChild($$, temp, 0);
        }
	       | key_write open_b id_list close_b semicolon{
                // printf("here without spaces\n");
        $$ = makeNode("write", -1);
        $$ = connectChild($$, $3, 0);
               }
	       | key_write open_b quoted_string close_b semicolon spaces_p{ 
        $$ = makeNode("write", -1); 
        struct Node* temp = makeNode($3, -1);
        $$ = connectChild($$, temp, 0);
        }
	       | key_write open_b id_list close_b semicolon spaces_p{
                printf("here with spaces\n");
        $$ = makeNode("write", -1);
        $$ = connectChild($$, $3, 0);
        }
                | key_write open_b array_id close_b semicolon {
                $$ = makeNode("write", -1);
                $$ = connectChild($$, $3, 0);
        }
                | key_write open_b array_id close_b semicolon spaces_p {
                $$ = makeNode("write", -1);
                $$ = connectChild($$, $3, 0);
        };
	       
read_statement: key_read open_b id close_b semicolon{
        $$ = makeNode("read", -1);
        struct Node* temp = makeNode($3, -1);
        $$ = connectChild($$, temp, 0);
        int ind = findInSymTable($3);
        if (ind != -1) {
                sym_table[ind].initial = true;
               }
        else {
                printf("Variable %s not declared\n",$3);
                // yyerror();
        }
}
	      | key_read open_b array_id close_b semicolon{
                $$ = makeNode("read", -1);
                $$ = connectChild($$, $3, 0);
                
                int ind = findInSymTable($3->children[0]->name);
                while(strcmp(sym_table[ind].name,$3->children[0]->name)==0){
                        sym_table[ind].initial = true;
                        ind++;
                }

              }
	      | key_read open_b id close_b semicolon spaces_p{
        $$ = makeNode("read", -1);
        struct Node* temp = makeNode($3, -1);
        $$ = connectChild($$, temp, 0);
        int ind = findInSymTable($3);
        if (ind != -1) {
                sym_table[ind].initial = true;
               }
        else {
                printf("Variable %s not declared\n",$3);
                // yyerror();
        }
               }
	      | key_read open_b array_id close_b semicolon spaces_p{
                $$ = makeNode("read", -1);
                $$ = connectChild($$, $3, 0);
                int ind = findInSymTable($3->children[0]->name);
                while(strcmp(sym_table[ind].name,$3->children[0]->name)==0){
                        sym_table[ind].initial = true;
                        ind++;
                }
                
              };
	      
array_id:id open_s num close_s { $$=makeNode("array_id",-1); struct Node* temp = makeNode($1,-1); $$ = connectChild($$,temp,0); struct Node* temp2 = makeNode($3,-1); $$ = connectChild($$,temp2,1);
                int ind = findInSymTable($1);
                if (ind != -1) {
                        if (sym_table[ind].initial) {
                                $$->type = sym_table[ind].type;
                        } else {
                                printf("Variable %s not initialized\n",$1);
                                // yyerror();
                        }
                }
                else {
                        printf("Variable %s not declared\n",$1);
                }
}
	|id open_s id close_s{ $$=makeNode("array_id",-1); struct Node* temp = makeNode($1,-1); $$ = connectChild($$,temp,0); struct Node* temp2 = makeNode($3,-1); $$ = connectChild($$,temp2,1);
                int ind = findInSymTable($1);
                if (ind != -1) {
                        if (sym_table[ind].initial) {
                                $$->type = sym_table[ind].type;
                        } else {
                                // printf("Variable %s not initialized\n",$1);
                                printf("Variable %s not initialized\n",$1);
                                // yyerror();
                        }
                }
                else {
                        printf("Variable %s not declared\n",$1);
                }};
	
assign_statement: assign_statement_ws semicolon {$$ = $1;}
		|assign_statement_ws semicolon spaces_p{$$ = $1;};
		
assign_statement_ws:id colon equal exp {
        $$ = makeNode("assign_statement", -1);
        struct Node* temp = makeNode($1, -1);
        $$ = connectChild($$, temp, 0);
        $$ = connectChild($$, $4, 1);
        int ind = findInSymTable($1);
        if (ind != -1) {
        
                if (sym_table[ind].type == $4->type 
                || (sym_table[ind].type == 4 && $4->type == 1 && (strcmp($4->children[0]->name, "1") == 0 ))
                || (sym_table[ind].type == 4 && $4->type == 1 && (strcmp($4->children[0]->name, "0") == 0 ))
                ||(sym_table[ind].type == 2 && $4->type == 1) ) {
                        sym_table[ind].initial = true;
                        
                } else {
                        printf("Type mismatch %s assigned to %s\n",numToType(sym_table[ind].type),numToType($4->type));
                       
                        //yyerror();
                }
        } else {
                printf("Variable %s not declared\n",$1);
                // yyerror();
        }
}
                |id spaces_p colon equal exp {
                        
        $$ = makeNode("assign_statement", -1);
        struct Node* temp = makeNode($1, -1);
        $$ = connectChild($$, temp, 0);
        $$ = connectChild($$, $5, 1);
        int ind = findInSymTable($1);
        if (ind != -1) {
                if (sym_table[ind].type == $5->type 
                || (sym_table[ind].type == 4 && $5->type == 1 && (strcmp($5->children[0]->name, "1") == 0 ))|| (sym_table[ind].type == 4 && $5->type == 1 && (strcmp($5->children[0]->name, "0") == 0 ))
                ||(sym_table[ind].type == 2 && $5->type == 1) )
                {
                        // bool val = true;
                        // printf("%d\n",sym_table[ind].initial);
                        sym_table[ind].initial = true;
                } else {
                        printf("Type mismatch %s assigned to %s\n",numToType(sym_table[ind].type),numToType($5->type));

                        //yyerror();
                }
        } else {
                printf("Variable %s not declared\n",$1);
                // yyerror();
        }
};
|array_id colon equal exp {
        $$ = makeNode("assign_statement", -1);
        $$ = connectChild($$, $1, 0);
        $$ = connectChild($$, $4, 1);
        int ind = findInSymTable($1->children[0]->name);
        if (ind != -1) {
                if (sym_table[ind].type == $4->type 
                || (sym_table[ind].type == 4 && $4->type == 1 && (strcmp($4->children[0]->name, "1") == 0 ))|| (sym_table[ind].type == 4 && $4->type == 1 && (strcmp($4->children[0]->name, "0") == 0 ))
                ||(sym_table[ind].type == 2 && $4->type == 1) ){
                        // bool val = true;
                        // printf("%d\n",sym_table[ind].initial);
                        ind=findExactArrayInd($1->children[0]->name,atoi($1->children[1]->name));
                        sym_table[ind].initial = true;
                } else {
                        printf("Type mismatch %s assigned to %s\n",numToType(sym_table[ind].type),numToType($4->type));

                        //yyerror();
                }
        }

        else {
                printf("Variable %s not declared\n",$1->children[0]->name);
                // yyerror();
        }
}
        |array_id spaces_p colon equal exp {
        $$ = makeNode("assign_statement", -1);
        $$ = connectChild($$, $1, 0);
        $$ = connectChild($$, $5, 1);
        int ind = findInSymTable($1->children[0]->name);
        if (ind != -1) {
                if (sym_table[ind].type == $5->type|| (sym_table[ind].type == 4 && $5->type == 1 && (strcmp($5->children[0]->name, "1") == 0 )) || (sym_table[ind].type == 4 && $5->type == 1 && (strcmp($5->children[0]->name, "0") == 0 ))||($1->type == 2 && $5->type == 1))
                {
                        // bool val = true;
                        // printf("%d\n",sym_table[ind].initial);
                        ind=findExactArrayInd($1->children[0]->name,atoi($1->children[1]->name));
                        sym_table[ind].initial = true;
                } else {
                        printf("Type mismatch %s assigned to %s\n",numToType(sym_table[ind].type),numToType($5->type));

                        //yyerror();
                }
        } else {
                printf("Variable %s not declared\n",$1->children[0]->name);
                // yyerror();
        }
};
		   
exp:exp op_plus exp {
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode("+", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 1) 
                        {
                                $$->type = 1;
                        }
                        else if($1->type==$3->type && $1->type == 2) 
                        {
                                $$->type = 2;
                        }
                        else if($1->type==1 && $3->type==2) 
                        {
                                $$->type = 2;
                        }
                        else if($1->type==2 && $3->type==1) 
                        {
                                $$->type = 2;
                        }
                        else {
                                printf("Type mismatch %s added to %s\n",numToType($1->type),numToType($3->type));
// yyerror();
                        }
        }

        |exp op_minus exp {
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode("-", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 1) 
                        {
                                $$->type = 1;
                        }
                        else if($1->type==$3->type && $1->type == 2) 
                        {
                                $$->type = 2;
                        }
                        else if($1->type==1 && $3->type==2) 
                        {
                                $$->type = 2;
                        }
                        else if($1->type==2 && $3->type==1) 
                        {
                                $$->type = 2;
                        }
                        else {
                                printf("Type mismatch %s subtracted by %s\n",numToType($1->type),numToType($3->type));

                        }
        }
   |exp op_mult exp {
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode("*", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 1) 
                        {
                                $$->type = 1;
                        }
                        else if($1->type==$3->type && $1->type == 2) 
                        {
                                $$->type = 2;
                        }
                        else if($1->type==1 && $3->type==2) 
                        {
                                $$->type = 2;
                        }
                        else if($1->type==2 && $3->type==1) 
                        {
                                $$->type = 2;
                        }
                        else {
                                printf("Type mismatch %s multipled by %s\n",numToType($1->type),numToType($3->type));
// yyerror();
                        }
        }
   |exp op_div exp {
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode("/", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 1) 
                        {
                                $$->type = 1;
                        }
                        else if($1->type==$3->type && $1->type == 2) 
                        {
                                $$->type = 2;
                        }
                        else if($1->type==1 && $3->type==2) 
                        {
                                $$->type = 2;
                        }
                        else if($1->type==2 && $3->type==1) 
                        {
                                $$->type = 2;
                        }
                        else {
                                 printf("Type mismatch %s divided by %s\n",numToType($1->type),numToType($3->type));

                        }
        }
   |exp op_mod exp {
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode("%", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 1) 
                        {
                                $$->type = 1;
                        }
                        
                        else {
                                printf("Type mismatch %s modulo by %s\n",numToType($1->type),numToType($3->type));

                        }
        }
   |exp key_and exp {
                        
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode("and", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 4) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type == 1 && $3->type == 4 && (strcmp($1->children[0]->name, "1" == 0) || strcmp($1->children[0]->name, "1") == 0)) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type == 4 && $3->type == 1 && (strcmp($3->children[0]->name, "1" == 0) || strcmp($3->children[0]->name, "1") == 0)) 
                        {
                                $$->type = 4;
                        }
                        else {
                                 printf("Both operands should be boolean but they were %s and %s\n",numToType($1->type),numToType($3->type));

                        }

                        }
   
   |exp key_or exp {
                        
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode("or", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 4) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type == 1 && $3->type == 4 && (strcmp($1->children[0]->name, "1" == 0) || strcmp($1->children[0]->name, "1") == 0)) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type == 4 && $3->type == 1 && (strcmp($3->children[0]->name, "1" == 0) || strcmp($3->children[0]->name, "1") == 0)) 
                        {
                                $$->type = 4;
                        }
                        else {
                                 printf("Both operands should be boolean but they were %s and %s\n",numToType($1->type),numToType($3->type));

                        }
        
                                 

                        }
   |exp greater exp {
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode(">", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 1) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==$3->type && $1->type == 2) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==1 && $3->type==2) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==2 && $3->type==1) 
                        {
                                $$->type = 4;
                        }
                        else {
                                printf("Type mismatch %s greater than %s\n",numToType($1->type),numToType($3->type));
                        }
        }

   |exp lesser exp {
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode("<", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 1) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==$3->type && $1->type == 2) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==1 && $3->type==2) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==2 && $3->type==1) 
                        {
                                $$->type = 4;
                        }
                        else {
                                 printf("Type mismatch %s less than %s\n",numToType($1->type),numToType($3->type));
                        }
        }
   |exp not_equal exp {
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode("<>", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 1) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==$3->type && $1->type == 2) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==1 && $3->type==2) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==2 && $3->type==1) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==4 && $3->type==4) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type == 1 && $3->type == 4 && (strcmp($1->children[0]->name, "1" == 0) || strcmp($1->children[0]->name, "1") == 0)) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type == 4 && $3->type == 1 && (strcmp($3->children[0]->name, "1" == 0) || strcmp($3->children[0]->name, "1") == 0)) 
                        {
                                $$->type = 4;
                        }
                        else {
                               printf("Type mismatch %s not equal to %s\n",numToType($1->type),numToType($3->type));

                        }
        }
   |exp equal exp  {
                        $$ = makeNode("exp", $1->type);
                        $$ = connectChild($$, $1, 0);
                        struct Node* temp = makeNode("=", -1);
                        $$ = connectChild($$, temp, 1);
                        $$ = connectChild($$, $3, 2);

                        if($1->type==$3->type &&  $1->type == 1) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==$3->type && $1->type == 2) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==1 && $3->type==2) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==2 && $3->type==1) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type==4 && $3->type==4) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type == 1 && $3->type == 4 && (strcmp($1->children[0]->name, "1" == 0) || strcmp($1->children[0]->name, "1") == 0)) 
                        {
                                $$->type = 4;
                        }
                        else if($1->type == 4 && $3->type == 1 && (strcmp($3->children[0]->name, "1" == 0) || strcmp($3->children[0]->name, "1") == 0)) 
                        {
                                $$->type = 4;
                        }
                        else {
                                 printf("Type mismatch %s equal %s\n",numToType($1->type),numToType($3->type));

                        }
        }
   |spaces_p key_not exp{
        $$ = makeNode("exp", 0);
        struct Node* temp = makeNode("!", -1);
        $$ = connectChild($$, temp, 0);
        $$ = connectChild($$, $3, 1);

                        if($3->type == 4) 
                        {
                                $$->type = 4;
                        }
                        else if ($3->type == 1 && strcmp($3->children[0]->name,"1") == 0) {
                                $$->type = 4;
                        }
                        else {
                                 printf("operand should be boolean but they were \n",numToType($3->type));

                        }
   }
   |key_not exp{
        $$ = makeNode("!", 0);
        $$ = connectChild($$, $2, 0);

                        if($2->type == 4) 
                        {
                                $$->type = 4;
                        }
                        else if ($2->type == 1 && strcmp($2->children[0]->name,"1") == 0) {
                                $$->type = 4;
                        }
                        else {
                                 printf("operand should be boolean but they were \n",numToType($2->type));

                        }
   }
   |name spaces_p {
                $$ = makeNode("exp", $1->type);
                $$ = connectChild($$, $1, 0);
        }
   |name {
                $$ = makeNode("exp", $1->type);
                $$ = connectChild($$, $1, 0);
        }
   |spaces_p name {
                //printf("Variable  not initialized\n");
                $$ = makeNode("exp", $2->type);
                $$ = connectChild($$, $2, 0);
        }
   |spaces_p name spaces_p {
        
                $$ = makeNode("exp", $2->type);
                $$ = connectChild($$, $2, 0);
        };

name:   num {      
                $$ = makeNode($1, 1);
        }
        |num_real {
                $$ = makeNode($1, 2);
        }
        |id {
                $$ = makeNode($1, 0);

                int ind = findInSymTable($1);
                if (ind != -1) {
                        if (sym_table[ind].initial) {
                                $$ = makeNode($1, sym_table[ind].type);
                        } else {
                                printf("Variable %s not initialized\n",$1);
                                // yyerror();
                        }
                }
                else {
                        printf("Variable %s not declared\n",$1);
                }
        }
        |quoted_char {
                $$ = makeNode($1, 3);
        }
        |array_id {$$ = $1;}
	|open_b exp close_b {$$ = $2;};
	
for_statement: key_for spaces_p assign_statement_ws  key_to  exp  key_do newlines_p spaces_p  begin_end_block semicolon {
        $$ = makeNode("for_statement", -1);
        $$ = connectChild($$, $3, 0);
        $$ = connectChild($$, $5, 1);
        $$ = connectChild($$, $9, 2);
}    | key_for spaces_p assign_statement_ws  key_downto  exp key_do newlines_p spaces_p begin_end_block semicolon {
        $$ = makeNode("for_statement", -1);
        $$ = connectChild($$, $3, 0);
        $$ = connectChild($$, $5, 1);
        $$ = connectChild($$, $9, 2);
}    |key_for spaces_p assign_statement_ws  key_to  exp  key_do spaces_p newlines_p spaces_p  begin_end_block semicolon{
        $$ = makeNode("for_statement", -1);
        $$ = connectChild($$, $3, 0);
        $$ = connectChild($$, $5, 1);
        $$ = connectChild($$, $10, 2);
}    | key_for spaces_p assign_statement_ws  key_downto  exp key_do spaces_p newlines_p spaces_p begin_end_block semicolon{
        $$ = makeNode("for_statement", -1);
        $$ = connectChild($$, $3, 0);
        $$ = connectChild($$, $5, 1);
        $$ = connectChild($$, $10, 2);
}    |key_for spaces_p assign_statement_ws  key_to  exp  key_do newlines_p spaces_p  begin_end_block semicolon spaces_p{
        $$ = makeNode("for_statement", -1);
        $$ = connectChild($$, $3, 0);
        $$ = connectChild($$, $5, 1);
        $$ = connectChild($$, $9, 2);
}    | key_for spaces_p assign_statement_ws  key_downto  exp key_do newlines_p spaces_p begin_end_block semicolon spaces_p {
        $$ = makeNode("for_statement", -1);
        $$ = connectChild($$, $3, 0);
        $$ = connectChild($$, $5, 1);
        $$ = connectChild($$, $9, 2);
}    |key_for spaces_p assign_statement_ws  key_to  exp  key_do spaces_p newlines_p spaces_p  begin_end_block semicolon spaces_p{
        $$ = makeNode("for_statement", -1);
        $$ = connectChild($$, $3, 0);
        $$ = connectChild($$, $5, 1);
        $$ = connectChild($$, $10, 2);
}    | key_for spaces_p assign_statement_ws  key_downto  exp key_do spaces_p newlines_p spaces_p begin_end_block semicolon spaces_p{
        $$ = makeNode("for_statement", -1);
        $$ = connectChild($$, $3, 0);
        $$ = connectChild($$, $5, 1);
        $$ = connectChild($$, $10, 2);
};

if_statement:if_statement_ws semicolon {$$ = $1;}
	    |if_statement_ws semicolon spaces_p{$$ = $1;};

if_statement_ws:key_if  exp  key_then newlines_p spaces_p begin_end_block{
        $$ = makeNode("if_statement", -1); 
        $$ = connectChild($$, $2, 0); 
        $$ = connectChild($$, $6, 1);
        }
	       |key_if  exp  key_then spaces_p newlines_p spaces_p begin_end_block{
        $$ = makeNode("if_statement", -1);
        $$ = connectChild($$, $2, 0);
        $$ = connectChild($$, $7, 1);
               };

if_else_statement:if_statement_ws newlines_p spaces_p key_else newlines_p spaces_p begin_end_block semicolon{
        $$ = makeNode("if_else_statement", -1);
        $$ = connectChild($$, $1, 0);
        $$ = connectChild($$, $7, 1);
        }
                 
                 |if_statement_ws newlines_p spaces_p key_else spaces_p newlines_p spaces_p begin_end_block semicolon{
                        $$ = makeNode("if_else_statement", -1);
                        $$ = connectChild($$, $1, 0);
                        $$ = connectChild($$, $8, 1);
                 }
                 |if_statement_ws newlines_p spaces_p key_else newlines_p spaces_p begin_end_block semicolon spaces_p{
                        $$ = makeNode("if_else_statement", -1);
                        $$ = connectChild($$, $1, 0);
                        $$ = connectChild($$, $7, 1);
                 }
                 |if_statement_ws newlines_p spaces_p key_else spaces_p newlines_p spaces_p begin_end_block semicolon spaces_p{
                        $$ = makeNode("if_else_statement", -1);
                        $$ = connectChild($$, $1, 0);
                        $$ = connectChild($$, $8, 1);
                 
                 };


while_statement:key_while  exp  key_do newlines_p spaces_p begin_end_block semicolon{
        $$ = makeNode("while_statement", -1);
        $$ = connectChild($$, $2, 0);
        $$ = connectChild($$, $6, 1);
        }
               

	       |key_while  exp  key_do spaces_p newlines_p spaces_p begin_end_block semicolon{
        $$ = makeNode("while_statement", -1);
        $$ = connectChild($$, $2, 0);
        $$ = connectChild($$, $7, 1);
               }
	       |key_while  exp  key_do newlines_p spaces_p begin_end_block semicolon spaces_p{
        $$ = makeNode("while_statement", -1);
        $$ = connectChild($$, $2, 0);
        $$ = connectChild($$, $6, 1);

               }
	       |key_while  exp  key_do spaces_p newlines_p spaces_p begin_end_block semicolon spaces_p{
        $$ = makeNode("while_statement", -1);
        $$ = connectChild($$, $2, 0);
        $$ = connectChild($$, $7, 1);

               };
%%

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
        printf("THREE ADDRESS CODE\n");
        printf("---------------------------------------------------------------------------------------------------\n");
        printQuadruples(quad);

        fclose(file);
        fclose(yyin);
        
        freeTree(root);
        exit(0);

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
