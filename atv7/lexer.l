%{
#include "funcs.h"        
%}

NUMBER [0-9]

%%
"+" {return PLUS;}
"(" {return LPAR;}
")" {return RPAR;}
"-" {return MINUS;}
"*" {return TIMES;}
"/" {return DASH;}
{NUMBER}+ {return atoi(yytext);}
\n {;}
" " {;}
. {printf("Erro: caractere inválido.\n"); exit(1);}
%%

yyin = sourceFile;
int yylex();