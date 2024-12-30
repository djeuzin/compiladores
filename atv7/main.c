#include "parser.h"
#include "lex.yy.c"
#include <stdio.h>

extern FILE* yyin;
int token;
int value;

int main(int argc, char ** argv){
        yyin = fopen(argv[1], "r");
        pNode tree;
        
        tree = parse();
        printf("Resultado: %d.\n", compute(tree));
        tree = clear(tree);

        fclose(yyin);
        return 0;
}