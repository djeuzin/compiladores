#ifndef FUNCS
#define FUNCS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum{
    IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,
    PLUS, MINUS, TIMES, DASH, EQ, LTHAN, LPAR, RPAR,
    SCOL, ATT, ID, NUM
};

typedef struct{
    char word[256];
    int line;
    int token;
}lexem;

lexem mainLex;

void print_lex(lexem);
char* get_token(lexem);
#endif