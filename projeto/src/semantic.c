/******************************/
/*  Cross: C- Compiler        */
/*  senabtic.c                */
/*  Contém as implementações  */
/*  das funções do analisador */
/*  semântico                 */
/******************************/

#include "semantic.h"

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
        char* currentScope = "global";

        init_symbol_table();

        recursive_analysis(nodePtr, currentScope);

        if(semanticFlag)
                print_symbol_table();
        
        clear_symbol_table();
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
 * Argumento: nó da árvore sintática e escopo atual
 * Retorna: vazio
 * Recursivamente, analisa a árvore sintática
 * preenchendo a tabela de símbolos no processo
 */
void recursive_analysis(ast_p node, char* scope){
        if(node == NULL)
                return;

        char* dadScope;
        dadScope = scope;

        if(node->type == AST_FUN_DECL)
                dadScope = node->id;

        fill_table(node, scope);

        for(int i=0; i<AST_MAX_CHILDREN; i++)
                recursive_analysis(node->children[i], dadScope);
        
        recursive_analysis(node->sibling, scope);
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
	        case AST_VAR_DECL: 
	        case AST_FUN_DECL: {
                        table_p entry = create_table_entry();
                        entry->declaration = TRUE;
                        entry->id = node->id;
                        entry->line = node->line;
                        entry->scope = scope;
                        if(node->typeSpecifier == INT)
                                entry->type = "int";
                        else
                                entry->type = "void";
                        entry->dataType = "array";
                        char* keyHash = NULL;
                        strcpy(keyHash, scope);
                        strcat(keyHash, entry->id);
                        insert_symbol_table(entry, semantic_hash(keyHash));
                        break;
                }
                case AST_ARRAY: 
                case AST_VAR: 
	        case AST_FUN:
                case AST_ASSIGNMENT: {
                        table_p entry = create_table_entry();
                        entry->declaration = FALSE;
                        entry->id = node->id;
                        entry->line = node->line;
                        entry->scope = scope;
                        if(node->typeSpecifier == INT)
                                entry->type = "int";
                        else
                                entry->type = "void";
                        entry->dataType = "array";
                        char* keyHash = NULL;
                        strcpy(keyHash, scope);
                        strcat(keyHash, entry->id);
                        insert_symbol_table(entry, semantic_hash(keyHash));
                        break;
                }
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
                if (!strcmp(aux->id, entry->id)){
                        if(aux->declaration){
                                if (entry->declaration){
                                        printf("Erro semantic\n");
                                }
                        }
                }
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