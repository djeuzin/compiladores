#include "lex.yy.c"
#include <stdio.h>

extern int yylex();
extern FILE* yyin;
int token;
int value;

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

int main(int argc, char ** argv){
        yyin = fopen(argv[1], "r");
        pNode tree;
        
        tree = parse();
        printf("Resultado: %d.\n", compute(tree));
        tree = clear(tree);

        fclose(yyin);
        return 0;
}

pNode parse(){
        get_next_token();
        return _exp();
}

pNode _exp(){
        if(token == END)
                return NULL;
        pNode newNode;
        pNode aux;
        newNode = ter();
        
        while(token == PLUS || token == MINUS){
                aux = malloc(sizeof(tNode));
                aux->token = token;
                aux->left = newNode;
                newNode = aux;
                get_next_token();
                newNode->right = ter();
        }

        return newNode;
}

pNode ter(){
        if(token == END)
                return NULL;
        pNode newNode;
        pNode aux;

        newNode = fat();
        while(token == TIMES || token == DASH){
                aux = malloc(sizeof(tNode));
                aux->token = token;
                aux->left = newNode;
                newNode = aux;
                get_next_token();
                newNode->right = fat();
        }

        return newNode;
}

pNode fat(){
        if(token == END)
                return NULL;
        pNode newNode;

        switch(token){
                case LPAR:
                get_next_token();
                newNode = _exp();
                if(token != RPAR)
                        exit(1);
                get_next_token();
                break;
                case NUM:
                newNode = malloc(sizeof(tNode));
                newNode->right = NULL;
                newNode->left = NULL;
                newNode->token = token;
                newNode->value = value;
                get_next_token();
                break;
                default:
                printf("ERRO\n");
                exit(1);
        }
        return newNode;
}

pNode clear(pNode tree){
        if(tree->left)
                tree->left = clear(tree->left);
        if(tree->right)
                tree->right = clear(tree->right);

        free(tree);
        return NULL;
}

void print_tree(pNode tree){
        if(tree->left)
                print_tree(tree->left);
        if(tree->right)
                print_tree(tree->right);

        printf("%d-", tree->token);
}

void get_next_token(){
        token = yylex();
}

int compute(pNode tree){
        if(tree->token == NUM)
                return tree->value;
        
        switch(tree->token){
                case PLUS:
                return compute(tree->left) + compute(tree->right);
                case DASH:
                int right = compute(tree->right);
                if(right == 0){
                        printf("ERRO divisão por 0\n");
                        return -1;
                }
                return compute(tree->left) / right;
                case TIMES:
                return compute(tree->left) * compute(tree->right);
                case MINUS:
                return compute(tree->left) - compute(tree->right);
        }
}