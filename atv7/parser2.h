#ifndef PARSER
#define PARSER

#include "funcs.h"
#include <math.h>

enum{
        EXPP,
        EXP_,
        SOMA,
        TERMO,
        TERMO_,
        MULTI,
        FATOR
};

extern int yylex();
extern int token;
extern int value;
extern int table[7][8];
extern int topOfStack;

struct node{
        int token;
        int value;
        struct node *left, *right;
};
typedef struct node tNode;
typedef tNode* pNode;

struct cell{
        int symbol;
        int isTerminal;
        struct cell *next;
};
typedef struct cell* stack;

extern stack mainStack;
extern pNode parseTree;

void push(int, int);
void pop();
void clear_stack();
void initialize_stack();
void print_stack();
void get_next_token();
void parse();
void casa(int, int);
void handle_stack(int);
void add_node();
pNode clear_tree(pNode);
int compute_tree();

#endif