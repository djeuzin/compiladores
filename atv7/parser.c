#include "parser.h"

pNode parse(){
        token = -1;
        get_next_token();
        pNode newTree = _exp();
        if(token != END){
                printf("ERRO\n");
                newTree = clear(newTree);
        }
        return newTree; 
}

pNode _exp(){
        if(token == END)
                return NULL;
        pNode newNode;
        pNode aux;
        pNode aux2 = NULL;
        newNode = ter();
        
        while(token == PLUS || token == MINUS){
                if(token == MINUS){
                        aux = malloc(sizeof(tNode));
                        aux->token = PLUS;
                        aux->left = newNode;
                        aux->right = NULL;
                        newNode = aux;

                        aux = malloc(sizeof(tNode));
                        aux->value = 0;
                        aux->token = NUM;
                        aux->left = NULL;
                        aux->right = NULL;

                        newNode->right = malloc(sizeof(tNode));
                        newNode->right->token = MINUS;
                        newNode->right->left = aux;

                        get_next_token();
                        newNode->right->right = ter();
                }
                else{
                        aux = malloc(sizeof(tNode));
                        aux->token = token;
                        aux->left = newNode;
                        newNode = aux;
                        get_next_token();
                        newNode->right = ter();
                }
        }

        return newNode;
}

pNode ter(){
        if(token == END)
                return NULL;
        pNode newNode;
        pNode aux;

        newNode = fat();
        while(token == TIMES || token == DASH || token == MOD){
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
        pNode aux;

        newNode = fat_();
        while(token == EXP){
                aux = malloc(sizeof(tNode));
                aux->token = token;
                aux->left = newNode;
                newNode = aux;
                get_next_token();
                newNode->right = fat();
        }

        return newNode;
}

pNode fat_(){
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
        if(tree->token == NUM){
                return tree->value;
        }
        
        int right;
        switch(tree->token){
                case PLUS:
                return compute(tree->left) + compute(tree->right);
                case EXP:
                return pow(compute(tree->left), compute(tree->right));
                case MOD:
                right = compute(tree->right);
                if(right == 0){
                        printf("ERRO divisão por 0\n");
                        return -1;
                }
                return compute(tree->left) % right;
                case DASH:
                right = compute(tree->right);
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