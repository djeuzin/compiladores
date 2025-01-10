#include "parser2.h"

/*
 (1) EXPP -> TERMO EXP_
 (2) EXP_ -> SOMA TERMO EXP_
 (3) EXP_ -> eps
 (4) SOMA -> + | -
 (5) TERMO -> FATOR TERMO_
 (6) TERMO_ -> MULTI FATOR TERMO_
 (7) TERMO_ -> eps
 (8) MULTI -> * | /
 (9) FATOR -> ( EXPP )
(10) FATOR -> NUM
*/
int table[7][8] = {
//       (,          ),      NUM,        +,         -,        *,         /,       $    
        {1,          0,        1,        0,         0,         0,        0,       0},  // <exp>
        {0,          3,        0,        2,         2,         0,        0,       3},  // <exp'>
        {0,          0,        0,        4,         4,         0,        0,       0},  // <soma>
        {5,          0,        5,        0,         0,         0,        0,       0},  // <termo>
        {0,          7,        0,        7,         7,         6,        6,       7},  // <termo'>
        {0,          0,        0,        0,         0,         8,        8,       0},  // <multi>
        {9,          0,       10,        0,         0,         0,        0,       0}   // <fator>
};

void push(int symbol, int isTerminal){
        stack newPtr = malloc(sizeof(struct cell));
        newPtr->symbol = symbol;
        newPtr->isTerminal = isTerminal;
        newPtr->next = mainStack;
        mainStack = newPtr;
}

void pop(){
        stack aux = mainStack;
        topOfStack = mainStack->symbol;
        mainStack = mainStack->next;
        free(aux);
}

void clear_stack(){
        stack auxPtr;
        while(mainStack != NULL){
                auxPtr = mainStack;
                mainStack = auxPtr->next;
                free(auxPtr);
        }
}

void initialize_stack(){
        clear_stack();
        push(END, 0);
        push(EXPP, 0);
}

void print_stack(){
        stack aux = mainStack;
        while(aux != NULL){
                printf("%d-%d\n", aux->symbol, aux->isTerminal);
                aux = aux->next;
        }
        printf("--------------\n");
}

void get_next_token(){
        token = yylex();
}

void casa(int tok, int token){
        if(tok != token)
                printf("Erro no casamento.\n");
}

void parse(){
        int nextAction;
        get_next_token();
        initialize_stack();
        parseTree = NULL;

        while(mainStack->symbol != END){
                if(mainStack->isTerminal){
                        pop();
                        casa(topOfStack, token);
                        add_node();
                        get_next_token();
                }
                else{
                        pop();
                        nextAction = table[topOfStack][token];
                        handle_stack(nextAction);
                }
        }

        if(mainStack->symbol != token)
                printf("Erro ao parsear.\n");
}

void handle_stack(int next){
        switch(next){
                case 0:
                printf("Erro 0\n");
                clear_stack();
                exit(1);
                break;
                case 1:
                push(EXP_, 0);
                push(TERMO, 0);
                break;
                case 2:
                push(EXP_, 0);
                push(TERMO, 0);
                push(SOMA, 0);
                break;
                case 3:
                break;
                case 4:
                push(token, 1);
                break;
                case 5:
                push(TERMO_, 0);
                push(FATOR, 0);
                break;
                case 6:
                push(TERMO_, 0);
                push(FATOR, 0);
                push(MULTI, 0);
                break;
                case 7:
                break;
                case 8:
                push(token, 1);
                break;
                case 9:
                push(RPAR, 1);
                push(EXPP, 0);
                push(LPAR, 1);
                break;
                case 10:
                push(NUM, 1);
                break;
        }
}

pNode clear_tree(pNode tree){
        if(!tree)
                return NULL;
        
        tree->left = clear_tree(tree->left);
        tree->right = clear_tree(tree->right);
        free(tree);
        return NULL;
}

void add_node(){

}