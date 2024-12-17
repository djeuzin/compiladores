#ifndef PARSER
#define PARSER
#include "funcs.h"
#include "lex.yy.c"

struct tree_node{
        int token;
        unsigned int value;
        struct tree_node *left, *right;
};

typedef struct tree_node node_t;
typedef node_t* node_p;

node_p parse_tree;
int tok;
extern FILE* sourceFile;

void open_file(char **);
void parse_expression();
void create_tree();
void avanca();
void casa(int);
node_p clear_tree(node_p);
int compute_tree(node_p);
void exp();
void termo();
void fator();
#endif