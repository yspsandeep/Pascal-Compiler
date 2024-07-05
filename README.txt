ERROR404

Members :
Kamalesh Ram R 2021A7PS0286H
Raguram Venkatesan 2021A7PS0150H
Bhaarath K 2021A7PS1816H
Suman Sekhar Sahoo 2021A7PS2605H
Sandeep YSP 2021A7PS3113H

FOR COMPILATION:
    lex ERROR404.l
    yacc -d ERROR404.y
    gcc lex.yy.c y.tab.c -ll
    ./a.out input.txt

IGNORE THE WARNINGS SHOWN WHEN EXECUTING "gcc lex.yy.c y.tab.c -ll"
