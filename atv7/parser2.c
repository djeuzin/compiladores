#include "parser2.h"

/*
        This algorithm needs two stacks: 
        1. one to follow the derivation steps
        2. another to store the nodes of the ast tree

        The algorithm works parsing the input with the predictive
        LL(1) table. In the derivation steps we include a special symbol
        to signal to our parse function that the tree must be constructed.
        When this symbol is reached in the parsing stack, we pop 3 elements 
        of the tree nodes stack and build a new node that is right after
        pushed onto the tree nodes stack.

        Example:
        Tree nodes stack (# denotes the end of the stack)
        In a stack with the following configuration, upon reading the 
        speacial symbol for tree construction the algorithm will pop
        these nodes and rearange them and push the resulting node back to the stack:

        (3) (+) (2) #

            (+) #          -> (+) node is the one pushed onto the stack
           /   \
         (2)   (3)
        

*/

/*
 (1) EXPP -> TERMO EXP_
 (2) EXP_ -> SOMA TERMO BUILD_TREE EXP_
 (3) EXP_ -> eps
 (4) SOMA -> + | -
 (5) TERMO -> FATOR TERMO_
 (6) TERMO_ -> MULTI FATOR BUILD_TREE TERMO_
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

void push(int symbol, int type){
        stack newPtr = malloc(sizeof(struct cell));
        newPtr->symbol = symbol;
        newPtr->type = type;
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
        push(END_PARSE, 0);
        push(EXPP, 0);
}

void print_stack(){
        stack aux = mainStack;
        while(aux != NULL){
                printf("%d-%d\n", aux->symbol, aux->type);
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
        init_ast_stack();
        parseTree = NULL;
        
        while(mainStack->symbol != END_PARSE){
                switch(mainStack->type){
                        case TERMINAL:
                        pop();
                        casa(topOfStack, token);
                        
                        if(token != LPAR && token != RPAR)
                                push_ast_stack(create_ast_node(token));

                        get_next_token();
                        break;
                        case NON_TERMINAL:
                        pop();
                        nextAction = table[topOfStack][token];
                        handle_stack(nextAction);
                        break;
                        case AST_BUILDER:
                        pop();
                        build_tree();
                        break;
                }
        }

        if(token != END)
                printf("Erro ao parsear.\n");
        else
                printf("Resultado: %d", calculate_result());

        clear_stack();
        clear_ast_stack();
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
                push(BUILD_TREE, AST_BUILDER);
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
                push(BUILD_TREE, AST_BUILDER);
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

ast create_ast_node(int token){
        ast newNode = malloc(sizeof(struct treeNode));
        newNode->token = token;
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
}

ast pop_ast_stack(){
        ast_stack stackAux = astStack;
        ast aux = astStack->top;
        astStack = astStack->next;
        free(stackAux);
        return aux;
}

void init_ast_stack(){
        astStack = NULL;
}

void push_ast_stack(ast newNode){
        ast_stack aux = malloc(sizeof(struct treeStack));
        aux->top = newNode;
        aux->next = astStack;
        astStack = aux;
}

void build_tree(){
        ast l, r, dad;
        r = pop_ast_stack();
        dad = pop_ast_stack();
        l = pop_ast_stack();

        dad->left = l;
        dad->right = r;

        push_ast_stack(dad);
}

ast clear_tree(ast tree){
        if(!tree)
                return NULL;
        
        tree->left = clear_tree(tree->left);
        tree->right = clear_tree(tree->right);

        free(tree);
        return NULL;
}

void clear_ast_stack(){
        ast_stack aux = astStack;
        while(astStack){
                astStack->top = clear_tree(astStack->top);
                astStack = astStack->next;
                free(aux);
                aux = astStack;
        }
}

int calculate_result(){
        return compute(astStack->top);
}

int compute(ast tree){
        if(tree->token == NUM){
                return tree->value;
        }
        
        int right;
        switch(tree->token){
                case PLUS:
                return compute(tree->left) + compute(tree->right);
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