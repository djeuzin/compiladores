#include "parser.h"

void casa(int marca){
        if(marca == tok)
                return;
        printf("Erro de análise sintática.\n");
        exit(1);
}

void avanca(){
        tok = yylex();
}

void open_file(char **argv){
        sourceFile = fopen(argv[1], "r");
}

node_p clear_tree(node_p tree){
        if(tree->left)
                tree->left = clear_tree(tree->left);
        if(tree->right)
                tree->right = clear_tree(tree->right);
        free(tree);
        return NULL;
}

void parse_expression(){
        create_tree();
}

void create_tree(){
        parse_tree = NULL;
        avanca();
        exp();
}

int compute_tree(node_p tree){
        if(tree->token == NUM)
                return tree->value;
        
        switch (tree->token){
        case PLUS:
        return compute_tree(tree->left) + compute_tree(tree->right);
        case MINUS:
        return compute_tree(tree->left) - compute_tree(tree->right);
        case TIMES:
        return compute_tree(tree->left) * compute_tree(tree->right);
        case DASH:
        return compute_tree(tree->left) / compute_tree(tree->right);
        }
}

void exp(){
        termo();
        while(tok == PLUS || tok == MINUS){
                insert_node(tok);
                avanca();
                termo();
        }
}
void termo(){
        fator();
        while(tok == TIMES || tok == DASH){
                insert_node(tok);
                avanca();
                fator();
        }
}

void fator(){
        switch(tok){
                case LPAR:
                avanca();
                exp();
                casa(RPAR);
                break;
                case NUM:
                insert_node(tok);
                avanca();
                break;
                default:
                printf("Erro de análise sintática.\n");
                exit(1);
        }
}