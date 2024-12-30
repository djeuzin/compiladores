#ifndef PARSER
#define PARSER

#include "funcs.h"

extern int yylex();
extern int token;
extern int value;

struct node{
        int token;
        int value;
        struct node *left, *right;
};
typedef struct node tNode;
typedef tNode* pNode;

void get_next_token();
pNode parse();
pNode _exp();
pNode ter();
pNode fat();
pNode clear(pNode);
void print_tree(pNode);
int compute(pNode tree);

#endif