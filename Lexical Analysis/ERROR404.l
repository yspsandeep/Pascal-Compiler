%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int line_num=1;

void print_line(char * s,char * token_type){
	printf("%d\t\t%s\t\t<%s>\n",line_num,s,token_type);
}

%}

%%
\/\/(.*) {;}
[Pp][Rr][Oo][Gg][Rr][Aa][Mm] { print_line(yytext,"key_prog");}
[Ii][Nn][Tt][Ee][Gg][Ee][Rr] {print_line(yytext,"key_type");}
[Rr][Ee][Aa][Ll] {print_line(yytext,"key_type");}
[Bb][Oo][Oo][Ll][Ee][Aa][Nn] {print_line(yytext,"key_type");}
[Cc][Hh][Aa][Rr] {print_line(yytext,"key_type");}
[Vv][Aa][Rr] {print_line(yytext,"key_var");}
[Tt][Oo] {print_line(yytext,"key_to");}
[Dd][Oo][Ww][Nn][Tt][Oo] {print_line(yytext,"key_downto");}
[Ii][Ff] {print_line(yytext,"key_if");}
[Ee][Ll][Ss][Ee] {print_line(yytext,"key_else");}
[Ww][Hh][Ii][Ll][Ee] {print_line(yytext,"key_while");}
[Ff][Oo][Rr] {print_line(yytext,"key_for");}
[Dd][Oo] {print_line(yytext,"key_do");}
[Aa][Rr][Rr][Aa][Yy] {print_line(yytext,"key_arr");}
[Oo][Ff] {print_line(yytext,"key_of");}
[Aa][Nn][Dd] {print_line(yytext,"key_and");}
[Oo][Rr] {print_line(yytext,"key_or");}
[Nn][Oo][Tt] {print_line(yytext,"key_not");}
[Bb][Ee][Gg][Ii][Nn] {print_line(yytext,"key_begin");}
[Ee][Nn][Dd] {print_line(yytext,"key_end");}
[Rr][Ee][Aa][Dd] {print_line(yytext,"key_read");}
[Ww][Rr][Ii][Tt][Ee] {print_line(yytext,"key_write");}
[Tt][Hh][Ee][Nn] {print_line(yytext,"key_then");}
[a-zA-Z][0-9a-zA-Z_]* {print_line(yytext,"id");}
[-]?[0-9]+ {print_line(yytext,"num");}
[-]?[0-9]+[.][0-9]+ {print_line(yytext,"num_real");}
\"([^\"\n])*\" {print_line(yytext,"quoted_string");}
"." {print_line(yytext,"dot");}
"," {print_line(yytext,"comma");}
[+] {print_line(yytext,"op_plus");}
[*] {print_line(yytext,"op_mult");}
[-] {print_line(yytext,"op_minus");}
[/] {print_line(yytext,"op_div");}
[%] {print_line(yytext,"op_mod");}
"=" {print_line(yytext,"equal");}
"<>" {print_line(yytext,"not_equal");}
"<" {print_line(yytext,"lesser");}
">" {print_line(yytext,"greater");}
"(" {print_line(yytext,"open_b");}
")" {print_line(yytext,"close_b");}
"[" {print_line(yytext,"open_s");}
"]" {print_line(yytext,"close_s");}
":" {print_line(yytext,"colon");}
["] {print_line(yytext,"quotes");}
";" {print_line(yytext,"semicolon");}
" " {print_line(yytext,"space");}
\n {print_line("","newline");line_num++;}
%%

main()
{
	printf("line number\tlexeme\t\ttoken type\n");
	yyin = fopen("input.txt", "r");
	yylex();
	
}


