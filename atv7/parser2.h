#ifndef PARSER
#define PARSER

#include "funcs.h"
#include <math.h>

#define TERMINAL 1
#define NON_TERMINAL 0
#define AST_BUILDER 2

enum{
        EXPP,
        EXP_,
        SOMA,
        TERMO,
        TERMO_,
        MULTI,
        FATOR,
        BUILD_TREE,
        END_PARSE
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
        int type;
        struct cell *next;
};
typedef struct cell* stack;

extern stack mainStack;
extern pNode parseTree;

struct treeNode{
        int token;
        int value;
        struct treeNode *left, *right;
};

typedef struct treeNode* ast;

struct treeStack{
        ast top;
        struct treeStack* next;
};

typedef struct treeStack* ast_stack;

extern ast_stack astStack;

void push(int, int);
void pop();
void clear_stack();
void initialize_stack();
void print_stack();
void get_next_token();
void parse();
void casa(int, int);
void handle_stack(int);

ast create_ast_node(int);
ast pop_ast_stack();
void push_ast_stack(ast);
void init_ast_stack();
void build_tree();
ast clear_tree(ast);
void clear_ast_stack();
int calculate_result();
int compute(ast);

#endif