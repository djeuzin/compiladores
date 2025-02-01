/******************************/
/*  Cross: C- Compiler        */
/*  senabtic.c                */
/*  Contém as definições      */
/*  das funções do analisador */
/*  semântico                 */
/******************************/

#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "parser.h"
#include "types.h"

extern ast_p syntaxTree;
extern int semanticFlag;
extern table_p symbol_table[SYMBOL_TABLE_SIZE];

extern void print_symbol_table();
extern ast_p ast_clear_tree(ast_p);

// Constrói a tabela de símbolos e analisa na segunda passada
void semantic_analysis(void);

// Inicializa a tabela de símbolos
void init_symbol_table(void);

// Libera a memória utilizada pela tabela de símbolos
void clear_symbol_table(void);

// Libera a memória de uma lista encadeada
table_p clear_list(table_p);

// Analiza a árvore sintática recursivamente
void recursive_analysis(ast_p, char*, int);

// Função hash para preencher a tabela de símbolos
int semantic_hash(char*);

// Preenche a tabela de símbolos
void fill_table(ast_p, char*);

// Cria uma entrada para ser adicionada à tabela de símbolos
table_p create_table_entry();

// Insere uma entrada em uma lista ligada
table_p insert_table_entry(table_p, table_p);

// Insere uma entrada na tabela no índice apropriado
void insert_symbol_table(table_p, int);

// Checa se a última função é main
void check_main_function(ast_p);

// Procura uma entrada na tabela associada a um nó
table_p search_table_entry(ast_p, int);

#endif