%{
#include "funcs.h"
#define LEX
%}

NUMBER [0-9]

%%
"+" {return PLUS;}
"(" {return LPAR;}
")" {return RPAR;}
"-" {return MINUS;}
"*" {return TIMES;}
"/" {return DASH;}
{NUMBER}+ {value = atoi(yytext); return NUM;}
\n {;}
" " {;}
. {printf("Erro: caractere inválido.\n"); exit(1);}
<<EOF>> {return END;}
%%

int yywrap(){
        return 1;
}