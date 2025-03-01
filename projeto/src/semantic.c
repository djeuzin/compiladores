/******************************/
/*  Cross: C- Compiler        */
/*  senabtic.c                */
/*  Contém as implementações  */
/*  das funções do analisador */
/*  semântico                 */
/******************************/

#include "semantic.h"
#include "parser.h"
#include "types.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

// Tabela de símbolos
table_p symbol_table[SYMBOL_TABLE_SIZE];

/* 
 * Argumento: vazio
 * Retorna: vazio
 * Realiza uma passada pela árvore sintáitca
 * e monta a tabela de símbolos.
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
 * Preenche cada posição da tabela com ponteiros NULL.
 * Também adiciona as funções input() e output()
 * na tabela de símbolos.
 */
void init_symbol_table(){
        for(int i=0; i<SYMBOL_TABLE_SIZE; i++)
                symbol_table[i] = NULL;

        table_p inputFunction = create_table_entry();

        inputFunction->dataType = "function";
        inputFunction->objectType = AST_FUN;
        inputFunction->type = "int";
        inputFunction->typeSpecifier = INT;
        inputFunction->id = "input";
        inputFunction->scope = "global";
        inputFunction->paramsIndex = 0;

        insert_symbol_table(inputFunction, semantic_hash("input"));

        table_p outputFunction = create_table_entry();

        outputFunction->dataType = "function";
        outputFunction->objectType = AST_FUN;
        outputFunction->type = "void";
        outputFunction->typeSpecifier = VOID;
        outputFunction->id = "output";
        outputFunction->scope = "global";
        outputFunction->paramsIndex = 1;
        outputFunction->params[0] = AST_VAR_PARAM;

        insert_symbol_table(outputFunction, semantic_hash("output"));
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

        if(node->visited == FALSE)
                fill_table(node, scope);

        for(int i=0; i<AST_MAX_CHILDREN; i++)
                recursive_analysis(node->children[i], dadScope, depth+1);

        if(node->type == AST_FUN_DECL)
                check_return_validity(node);
        
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
                case AST_ARRAY_DECL: 
                case AST_ARRAY_PARAM:
                case AST_VAR_PARAM: 
                case AST_VAR_DECL: {
                        check_variable_unity(node, scope);

                        break;
                } 
                case AST_ARRAY:
                case AST_VAR: {
                        if(node->visited == FALSE)
                                check_variable_consistency(node, scope);

                        break;
                }
                case AST_ASSIGNMENT: {
                        if(node->visited == FALSE){
                                table_p auxEntry = search_table_entry(node, scope);
                                check_variable_consistency(node, scope);
                                
                                if(node->children[INDEX_CHILD] == NULL && auxEntry->objectType == AST_ARRAY)
                                        printf("ERRO SEMANTICO: variavel \"%s\" do tipo arrary deve ser indexado em uma atribuicao. LINHA: %d.\n", node->id, node->line);

                                check_assignment(node->children[EXP_CHILD], scope);
                        }

                        break;
                }
                case AST_FUN_DECL: {
                        check_function_declaration(node, scope);

                        break;
                }
	        case AST_FUN: {
                        if(node->visited == FALSE)
                                check_function_call(node, scope);
                        
                        break;
                }
                case AST_RETURN: {
                        check_return(node, scope);

                        if(node->sibling != NULL)
                                printf("ERRO SEMANTICO: declaracoes alem de uma declaracao return. LINHA: %d.\n", node->line);

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
        newEntry->paramsIndex = 0;
        newEntry->linesIndex = 0;
        newEntry->hasReturn = FALSE;
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
}

/*
 * Argumento: nó da árvore e escopo
 * Retorna: entrada da tabela de símbolos
 * Busca a entrada correspondente ao nó utilizado como argumento
 * e retorna a entrada se for encontrada. Busca primeiro pela funcao
 * em seguida pela variavel no escopo e por fim pela variavel global.
 * Para buscar apenas funções passe NULL como escopo.
 */
table_p search_table_entry(ast_p node, char* scope){
        table_p aux;
        int hashIndex;
        char hashKey[ID_LENGTH];

        // Procura primeiro pela função com mesmo id
        hashIndex = semantic_hash(node->id);
        aux = symbol_table[hashIndex];

        while(aux){
                if(!strcmp(node->id, aux->id))
                        return aux;
                aux = aux->next;
        }

        if(scope == NULL)
                return NULL;

        // Procura depois pela variavel no escopo
        strcpy(hashKey, scope);
        strcat(hashKey, node->id);
        hashIndex = semantic_hash(hashKey);
        aux = symbol_table[hashIndex];

        while(aux){
                if(!strcmp(node->id, aux->id))
                        return aux;
                aux = aux->next;
        }

        // Por fim procura pela variável global
        strcpy(hashKey, "global");
        strcat(hashKey, node->id);
        hashIndex = semantic_hash(hashKey);
        aux = symbol_table[hashIndex];

        while(aux){
                if(!strcmp(node->id, aux->id))
                        return aux;
                aux = aux->next;
        }

        return NULL;
}

/*
 * Argumento: nó raiz da expressão e escopo do nó
 * Retorna: vazio
 * Checa se os valores da expressão
 * são válidos na atribuição de valores.
 */
void check_assignment(ast_p expRoot, char* scope){
        if(expRoot == NULL)
                return;

        expRoot->visited = TRUE;

        switch(expRoot->type){
                case AST_ARRAY:{
                        check_variable_consistency(expRoot, scope);

                        if(expRoot->children[INDEX_CHILD] == NULL)
                                printf("ERRO SEMANTICO: variavel \"%s\" do tipo arrary deve ser indexado em uma atribuicao. LINHA: %d.\n", expRoot->id, expRoot->line);
                        
                        break;
                }
                case AST_VAR: {
                        check_variable_consistency(expRoot, scope);
                        break;
                }
                case AST_FUN: {
                        check_function_call(expRoot, scope);
                        break;
                }
                case AST_ASSIGNMENT: {
                        table_p auxEntry = search_table_entry(expRoot, scope);
                        check_variable_consistency(expRoot, scope);

                        if(expRoot->children[INDEX_CHILD] == NULL && auxEntry->objectType == AST_ARRAY)
                                printf("ERRO SEMANTICO: variavel \"%s\" do tipo arrary deve ser indexado em uma atribuicao. LINHA: %d.\n", expRoot->id, expRoot->line);

                        check_assignment(expRoot->children[EXP_CHILD], scope);

                        return;
                }
                default:
                        break;
        }

        check_assignment(expRoot->children[LEFT_CHILD], scope);
        check_assignment(expRoot->children[RIGHT_CHILD], scope);
}

/* 
 * Argumentos: nó da árvore e escopo do nó
 * Retorna: vazio
 * Checa a consitência da variável, se foi declarada antes
 * do uso ou se o identificador é o mesmo que de uma função
 */ 
void check_variable_consistency(ast_p node, char* scope){
        table_p auxEntry;

        auxEntry = search_table_entry(node, scope);
        node->visited = TRUE;

        if(auxEntry == NULL){
                printf("ERRO SEMANTICO: variavel \"%s\" nao delcarada antes do uso. LINHA: %d.\n", node->id, node->line);
                return;
        }

        if(auxEntry->objectType == AST_FUN){
                printf("ERRO SEMANTICO: identificardor utilizado na declaracao de funcao %s. LINHA: %d.\n", node->id, node->line);
                return;
        }

        auxEntry->lines[auxEntry->linesIndex] = node->line;
        (auxEntry->linesIndex)++;
}

/* 
 * Argumentos: nó da árvore e escopo do nó
 * Retorna: vazio
 * Confere a unicidade na declaração de variáveis
 */
void check_variable_unity(ast_p node, char* scope){
        table_p auxEntry;
        char hashKey[ID_LENGTH];
        int hashIndex;

        node->visited = TRUE;

        if(node->typeSpecifier != INT)
                printf("ERRO SEMANTICO: variavel \"%s\" sendo declarada como tipo void. LINHA: %d\n", node->id, node->line);

        strcpy(hashKey, scope);
        strcat(hashKey, node->id);
        hashIndex = semantic_hash(hashKey);
        auxEntry = symbol_table[hashIndex];

        while(auxEntry){
                if(!strcmp(node->id, auxEntry->id))
                        break;
                auxEntry = auxEntry->next;
        }

        if(auxEntry == NULL){
                char hashKey[ID_LENGTH];
                strcpy(hashKey, scope);
                strcat(hashKey, node->id);
                int entryHash = semantic_hash(hashKey);
                table_p newEntry = create_table_entry();

                if(node->type == AST_ARRAY_DECL || node->type == AST_ARRAY_PARAM){
                        newEntry->dataType = "array";
                        newEntry->objectType = AST_ARRAY;
                }
                else{
                        newEntry->dataType = "variable";
                        newEntry->objectType = AST_VAR;
                }
                newEntry->type = "int";
                newEntry->typeSpecifier = INT;
                newEntry->id = node->id;
                newEntry->scope = scope;
                newEntry->lines[newEntry->linesIndex] = node->line;
                (newEntry->linesIndex)++;

                insert_symbol_table(newEntry, entryHash);

                return;
        }

        if(auxEntry->objectType == AST_FUN){
                printf("ERRO SEMANTICO: identificardor utilizado na declaracao de funcao %s. LINHA: %d.\n", node->id, node->line);
                return;
        }
                        

        if(!strcmp(auxEntry->scope, scope)){
                printf("ERRO SEMANTICO: variavel \"%s\" ja declarada nesse escopo. LINHA: %d.\n", node->id, node->line);
                return;
         }

}

/*
 * Argumentos: nó da árvore e escopo do nó
 * Retorna: vazio
 * Checa a consistência de declarações de funções
 * e também organiza a lista de parâmetros para 
 * checagem em futurar chamadas da função
 */
void check_function_declaration(ast_p node, char* scope){
        ast_p auxCrawlingNode = node->children[PARAM_CHILD];
        table_p auxEntry = search_table_entry(node, NULL);

        node->visited = TRUE;

        if(auxEntry != NULL){
                printf("ERRO SEMANTICO: identificardor \"%s\" ja declarado. LINHA: %d.\n", node->id, node->line);
                return;
        }

        table_p newEntry = create_table_entry();
        newEntry->dataType = "function";
        newEntry->objectType = AST_FUN;
        if(node->typeSpecifier == INT){
                newEntry->type = "int";
                newEntry->typeSpecifier = INT;
        }
        else{
                newEntry->type = "void";
                newEntry->typeSpecifier = VOID;
        }
        newEntry->id = node->id;
        newEntry->scope = scope;
        newEntry->lines[newEntry->linesIndex] = node->line;
        (newEntry->linesIndex)++;

        while(auxCrawlingNode){
                if(auxCrawlingNode->type == AST_VOID)
                        break;
                newEntry->params[newEntry->paramsIndex] = auxCrawlingNode->type;
                (newEntry->paramsIndex)++;
                auxCrawlingNode = auxCrawlingNode->sibling;
        }

        insert_symbol_table(newEntry, semantic_hash(node->id));
}

/*
 * Argumentos: nó da árvore e escopo do nó
 * Retorna: vazio
 * Checa se a função chamada existe e se existir
 * checa se os parâmetros passados na chamada
 * são consistentes.
 */
void check_function_call(ast_p node, char* scope){
        table_p auxEntry = search_table_entry(node, NULL);
        ast_p auxCrawlingNode;

        node->visited = TRUE;

        if(auxEntry == NULL){
                printf("ERRO SEMANTICO: funcao \"%s\" nao delcarada antes do uso. LINHA: %d.\n", node->id, node->line);
                return;
        }

        auxCrawlingNode = node->children[PARAM_CHILD];

        for(int i=0; i < auxEntry->paramsIndex; i++){
                if(auxCrawlingNode->type == AST_CONST || 
                   auxCrawlingNode->type == AST_OPERAND)
                        if(auxEntry->params[i] != AST_VAR_PARAM)
                                break;

                if(auxCrawlingNode->type == AST_FUN){
                        table_p otherEntry = search_table_entry(auxCrawlingNode, NULL);
                        if(otherEntry == NULL ||
                           otherEntry->typeSpecifier != INT ||
                           auxEntry->params[i] != AST_VAR_PARAM)
                                break;
                }

                if(auxCrawlingNode->type == AST_ARRAY){
                        // Se tem referência, temos um inteiro
                        if(auxCrawlingNode->children[INDEX_CHILD]){
                                if(auxEntry->params[i] != AST_VAR_PARAM)
                                        break;
                        }
                        else{
                                if(auxEntry->params[i] != AST_ARRAY_PARAM)
                                        break;
                        }
                }

                if(auxCrawlingNode->type == AST_VAR){
                        table_p otherEntry = search_table_entry(auxCrawlingNode, scope);
                                if(otherEntry == NULL)
                                break;

                        if(otherEntry->objectType == AST_ARRAY &&
                           auxEntry->params[i] != AST_ARRAY_PARAM)
                                break;

                        if(otherEntry->objectType == AST_VAR &&
                           auxEntry->params[i] != AST_VAR_PARAM)
                                break;
                }

                auxCrawlingNode = auxCrawlingNode->sibling;
        }

        if(auxCrawlingNode != NULL){
                printf("ERRO SEMANTICO: parametros passados para funcao \"%s\" invalidos. LINHA: %d.\n", node->id, node->line);
                return;
        }

        auxEntry->lines[auxEntry->linesIndex] = node->line;
        (auxEntry->linesIndex)++;
}

/* 
 * Argumentos: nó da árvore e escopo do nó
 * Retorna: vazio
 * Checa se o return condiz com a declaração de 
 * tipo da função.
 */
void check_return(ast_p node, char* scope){
        table_p auxEntry;
        int hashIndex;

        hashIndex = semantic_hash(scope);
        auxEntry = symbol_table[hashIndex];

        while(auxEntry){
                if(!strcmp(scope, auxEntry->id))
                        break;
                auxEntry = auxEntry->next;
        }

        auxEntry->hasReturn = TRUE;

        if(node->children[EXP_CHILD] == NULL && auxEntry->typeSpecifier == INT)
                printf("ERRO SEMANTICO: funcao \"%s\" de retorno int nao retorna nenhum valor. LINHA: %d.\n", auxEntry->id, node->line);

        if(node->children[EXP_CHILD] != NULL && auxEntry->typeSpecifier == VOID)
                printf("ERRO SEMANTICO: funcao \"%s\" de retorno void retornando valor. LINHA: %d.\n", auxEntry->id, node->line);
}

/*
 * Argumentos: nó de declaração de função
 * Retorna: vazio
 * Checa se os returns são consistentes.
 */
void check_return_validity(ast_p node){
        table_p auxEntry = search_table_entry(node, NULL);

        if(auxEntry->typeSpecifier == VOID)
                return;

        if(auxEntry->hasReturn == FALSE){
                printf("ERRO SEMANTICO: funcao \"%s\" do tipo int sem retorno de valores. LINHA: %d.\n", node->id, node->line);
                return;
        }
}       