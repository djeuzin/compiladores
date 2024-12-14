%{
#include "funcs.c"

extern lexem mainLex;\
int curr_line = 1;
%}

DIGIT [0-9]
LETTER [A-Za-z]
%%
\n {curr_line++;}
if {strcpy(mainLex.word, yytext); mainLex.token = IF; mainLex.line = curr_line; print_lex(mainLex);}
then {strcpy(mainLex.word, yytext); mainLex.token = THEN; mainLex.line = curr_line; print_lex(mainLex);}
else {strcpy(mainLex.word, yytext); mainLex.token = ELSE; mainLex.line = curr_line; print_lex(mainLex);}
end {strcpy(mainLex.word, yytext); mainLex.token = END; mainLex.line = curr_line; print_lex(mainLex);}
repeat {strcpy(mainLex.word, yytext); mainLex.token = REPEAT; mainLex.line = curr_line; print_lex(mainLex);}
until {strcpy(mainLex.word, yytext); mainLex.token = UNTIL; mainLex.line = curr_line; print_lex(mainLex);}
read {strcpy(mainLex.word, yytext); mainLex.token = READ; mainLex.line = curr_line; print_lex(mainLex);}
write {strcpy(mainLex.word, yytext); mainLex.token = WRITE; mainLex.line = curr_line; print_lex(mainLex);}
"+" {strcpy(mainLex.word, yytext); mainLex.token = PLUS; mainLex.line = curr_line; print_lex(mainLex);}
"-" {strcpy(mainLex.word, yytext); mainLex.token = MINUS; mainLex.line = curr_line; print_lex(mainLex);}
"*" {strcpy(mainLex.word, yytext); mainLex.token = TIMES; mainLex.line = curr_line; print_lex(mainLex);}
"/" {strcpy(mainLex.word, yytext); mainLex.token = DASH; mainLex.line = curr_line; print_lex(mainLex);}
"=" {strcpy(mainLex.word, yytext); mainLex.token = EQ; mainLex.line = curr_line; print_lex(mainLex);}
"<" {strcpy(mainLex.word, yytext); mainLex.token = LTHAN; mainLex.line = curr_line; print_lex(mainLex);}
"(" {strcpy(mainLex.word, yytext); mainLex.token = LPAR; mainLex.line = curr_line; print_lex(mainLex);}
")" {strcpy(mainLex.word, yytext); mainLex.token = RPAR; mainLex.line = curr_line; print_lex(mainLex);}
";" {strcpy(mainLex.word, yytext); mainLex.token = SCOL; mainLex.line = curr_line; print_lex(mainLex);}
":=" {strcpy(mainLex.word, yytext); mainLex.token = ATT; mainLex.line = curr_line; print_lex(mainLex);}
{DIGIT}+ {strcpy(mainLex.word, yytext); mainLex.token = NUM; mainLex.line = curr_line; print_lex(mainLex);}
{LETTER}+ {strcpy(mainLex.word, yytext); mainLex.token = ID; mainLex.line = curr_line; print_lex(mainLex);}
[ \t] {;}
"{"[^"}"]*"}" {;}
. printf("Caractere inválido.\n");
%%

int yywrap(){}
int main(int argc, char** argv){
        yyin = fopen(argv[1], "r");
        yylex();

        return 0;
}