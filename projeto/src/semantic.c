/******************************/
/*  Cross: C- Compiler        */
/*  senabtic.c                */
/*  Contém as implementações  */
/*  das funções do analisador */
/*  semântico                 */
/******************************/

#include "semantic.h"
#include "types.h"
#include <stdio.h>

// Tabela de símbolos
table_p symbol_table[SYMBOL_TABLE_SIZE];

/* 
 * Argumento: vazio
 * Retorna: vazio
 * Realiza duas passadas pela árvore sintáitca.
 * Na primeira constói a tabela de símbolos.
 * Na segunda confere se está correta.
 */
void semantic_analysis(void){
        ast_p nodePtr = syntaxTree;

        // Escopo inicial para variáveis
        char* currentScope = "global";

        init_symbol_table();

        // Percorre a árvore analisando cada nó
        recursive_analysis(nodePtr, currentScope, INITIAL_DEPTH);

        if(semanticFlag)
                print_symbol_table();
        
        clear_symbol_table();

        syntaxTree = ast_clear_tree(syntaxTree);
}

/* 
 * Argumento: vazio
 * Retorna: vazio
 * Preenche cada posição da tabela com ponteiros NULL
 */
void init_symbol_table(){
        for(int i=0; i<SYMBOL_TABLE_SIZE; i++)
                symbol_table[i] = NULL;
}

/*
 * Argumento: vazio
 * Retorna: vazio
 * Libera a memória utilizada pela tabela de símbolos
 */
void clear_symbol_table(){
        for(int i=0; i<SYMBOL_TABLE_SIZE; i++)
                symbol_table[i] = clear_list(symbol_table[i]);
}

/* 
 * Argumento: elemento da tabela de símbolos
 * Retorna: elemento nulo da tablea de símbolos
 * Libera a memória de toda lista encadeada encabeçada
 * pelo elemento recebido como argumento
 */
table_p clear_list(table_p unit){
        table_p aux;

        while(unit){
                aux = unit;
                unit = unit->next;
                free(aux);
        }

        return NULL;
}

/*
 * Argumento: nó da árvore sintática, escopo atual e profundiade atual
 * Retorna: vazio
 * Recursivamente, analisa a árvore sintática
 * preenchendo a tabela de símbolos no processo
 */
void recursive_analysis(ast_p node, char* scope, int depth){
        if(node == NULL)
                return;

        char* dadScope;
        dadScope = scope;

        if(node->type == AST_FUN_DECL)
                dadScope = node->id;

        fill_table(node, scope);

        for(int i=0; i<AST_MAX_CHILDREN; i++)
                recursive_analysis(node->children[i], dadScope, depth+1);
        
        if(node->sibling)
                recursive_analysis(node->sibling, scope, depth);
        else if(depth == INITIAL_DEPTH)
                check_main_function(node);
}

/*
 * Argumento: string
 * Retorna: índice na tabela de símbolos
 * Calcula o hash dado um identificador
 */
int semantic_hash(char* word){
        long int temp = 0, n = strlen(word);
        
        for(int i=0; i<n; i++){
                temp+= pow(ALPHA, n) * word[i];
                n--;
        }

        return temp % SYMBOL_TABLE_SIZE;
}

/*
 * Agumentos: nó e escopo
 * Retorna: vazio
 * Preenche a tabela de símbolos dado um nó
 * e o escopo dele no programa
 */
void fill_table(ast_p node, char* scope){
        switch(node->type){
                case AST_ARRAY_PARAM: 
                case AST_ARRAY_DECL: 
                case AST_VAR_PARAM: 
	        case AST_VAR_DECL: {
                        if(node->typeSpecifier != INT)
                                printf("ERRO SEMANTICO: variavel sendo declarada como tipo void. LINHA: %d\n", node->line);
                        break;
                } 
                case AST_ARRAY:
	        case AST_FUN_DECL:
                case AST_VAR: 
	        case AST_FUN:
                case AST_ASSIGNMENT:
                default:
                break;
        }
}

/*
 * Argumento: vazio
 * Retorna: nó da tabela de símbolos
 * Aloca memória para uma entrada
 * na tabela de símbolos
 */
table_p create_table_entry(){
        table_p newEntry = malloc(sizeof(struct symbolTable));
        newEntry->dataType = NULL;
        newEntry->id = NULL;
        newEntry->next = NULL;
        newEntry->scope = NULL;
        newEntry->type = NULL;
        newEntry->line = -1;
        newEntry->declaration = FALSE;

        return newEntry;
}

/*
 * Argumento: cabeça da lista e entrada da tabela
 * Retorna: ponteiro para o primeiro elemento da lista
 * Insere a entrada na lista ligada.
 */
table_p insert_table_entry(table_p listHead, table_p entry){
        if(!listHead){
                listHead = entry;
                return listHead;
        }

        table_p aux = listHead;

        while(aux->next){
                aux = aux->next;
        }
        
        aux->next = entry;
        return listHead;
}

/*
 * Argumento: entrada da tabela e índice
 * Retorna: vazio
 * Insere a entrada no índice apropriado
 * da tabela de símbolos
 */
void insert_symbol_table(table_p entry, int index){
        symbol_table[index] = insert_table_entry(symbol_table[index], entry);
}

/*
 * Argumento: nó raiz
 * Retorna: vazio
 * Checa se a última declaração do programa
 * é da função void main(void).
 */
void check_main_function(ast_p root){
        if(strcmp(root->id, "main") || root->type != AST_FUN_DECL){
                printf("ERRO SEMANTICO: ultima declaracao dever ser da funcao main. Ultima declaracao foi \"%s\". LINHA: %d.\n", root->id, root->line);
                return;
        }

        if(root->children[PARAM_CHILD]->type != AST_VOID){
                printf("ERRO SEMANTICO: funcao main deve ser definida com parametro void. LINHA: %d\n", root->line);
                return;
        }

        if(root->typeSpecifier != VOID){
                printf("ERRO SEMANTICO: funcao main deve ser definida como void. LINHA: %d\n", root->line);
                return;
        }

        root = root->children[STMT_CHILD];
        while(root->sibling)
                root = root->sibling;

        if(root->type == AST_RETURN)
                printf("ERRO SEMANTICO: funcao main nao utiliza controle de fluxo return. LINHA: %d\n", root->line);
}