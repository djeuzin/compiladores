#include "lex.yy.c"
#include "parser2.h"
#include <stdio.h>

extern FILE* yyin;
int token;
int value;
int topOfStack;
stack mainStack = NULL;
pNode parseTree;

int main(int argc, char ** argv){
        yyin = fopen(argv[1], "r");
        
        parse();

        fclose(yyin);
        clear_stack();
        parseTree = clear_tree(parseTree);
        return 0;
}