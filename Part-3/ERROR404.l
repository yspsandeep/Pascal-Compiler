%{
#include "y.tab.h"
#include <string.h>

// ID_LIST TO BE HANDLED IN WRITE STATEMENT

%}

%%
\/\/(.*) {;}

[-] { return op_minus;}





[Pp][Rr][Oo][Gg][Rr][Aa][Mm] return key_prog;


[Ii][Nn][Tt][Ee][Gg][Ee][Rr] {strcpy(yylval.strval, "integer"); return key_type;}
[Rr][Ee][Aa][Ll] {strcpy(yylval.strval, "real"); return key_type;}
[Bb][Oo][Oo][Ll][Ee][Aa][Nn] {strcpy(yylval.strval, "boolean"); return key_type;}
[Cc][Hh][Aa][Rr] {strcpy(yylval.strval, "char"); return key_type;}


[Vv][Aa][Rr] return key_var;
[Tt][Oo] return key_to;
[Dd][Oo][Ww][Nn][Tt][Oo] return key_downto;
[Ii][Ff] return key_if;
[Ee][Ll][Ss][Ee] return key_else;
[Ww][Hh][Ii][Ll][Ee] return key_while;
[Ff][Oo][Rr] return key_for;
[Dd][Oo] return key_do;
[Aa][Rr][Rr][Aa][Yy] return key_arr;
[Oo][Ff] return key_of;
[Aa][Nn][Dd] return key_and;
[Oo][Rr] return key_or;
[Nn][Oo][Tt] return key_not;
[Bb][Ee][Gg][Ii][Nn] return key_begin;
[Ee][Nn][Dd] return key_end;
[Rr][Ee][Aa][Dd] return key_read;
[Ww][Rr][Ii][Tt][Ee] return key_write;
[Tt][Hh][Ee][Nn] return key_then;
[a-zA-Z][0-9a-zA-Z_]* {strcpy(yylval.strval, yytext); return id;}
[-]?[0-9]+ {strcpy(yylval.strval, yytext); return num;}
[-]?[0-9]+[.][0-9]+ {strcpy(yylval.strval, yytext); return num_real;}
\'([^\'\n])\' {strcpy(yylval.strval, yytext); return quoted_char;}
\"([^\"\n])*\" {strcpy(yylval.strval, yytext); return quoted_string;}
"." return dot;
"," return comma;
[+] return op_plus;
[*] return op_mult;
[/] return op_div;
[%] return op_mod;
"=" return equal;
"<>" return not_equal;
"<" return lesser;
">" return greater;
"(" return open_b;
")" return close_b;
"[" return open_s;
"]" return close_s;
":" return colon;
";" return semicolon;
" " return space;
[\t] return space;
\n return newline;
%%




