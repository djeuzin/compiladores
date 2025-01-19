/**************************/
/*  Cross: C- Compiler    */
/*  parser.h              */
/*  Contém as declarações */
/*  das funções do parser.*/
/**************************/

// TODO: AST construction and error handling

#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "parsing_table.h"

/* Variáveis externas utilizadas */

extern int parsingTable[][44];
extern lex_t mainLex;
extern parser_stack_p parserStack;
extern int currentSymbol;
extern ast_p dummyNode;
extern ast_stack_p treeNodeStack;
extern ast_p syntaxTree;
extern int parserFlag;

/* Funções externas utilizadas */

extern void allocate_buffer(void);
extern void deallocate_buffer(void);
extern void get_next_lexem(void);

// Retira o elemento do topo da pilha do parser
void pop_stack(void);

// Adiciona um elemento à pilha do parser
void push_stack(int, int);

// Libera a memória utilizada pela pilha do parser
void clear_stack(void);

// Inicializa a pilha do parser
void init_stack(void);

// Função principal do parser
void parse(void);

// Manipula a pilha de acordo com a tabela preditiva
void handle_stack(int);

// Verifica se o terminal no topo da pilha é igual ao terminal lido pelo lexer
int match(int, int);

// Exibe a pilha de derivação
void print_stack(void);

// Inicializa as variáveis para construir a árvore sintática
void init_tree_stack(void);

// Libera a memória utilizada por um nó e seus filhos
ast_p ast_clear_tree(ast_p);

// Libera a memória utilizada das estruturas auxiliares para construir a árvore sintática
void ast_clear_stack(void);

// Cria um novo nó para a árvore sintática
ast_p ast_create_node(void);

// Seta os dados do nó dummy a partir do token lido
void set_dummy_data(void);

// Adiciona um nó de árvore ao topo da pilha auxiliar
void ast_push_stack(ast_p);

// Retira o nó de árvore no topo da pilha auxiliar
ast_p ast_pop_stack(void);

// Constrói a árvore sintática
void build_tree(void);

// Checa se um nó possui filhos
int hasChildren(ast_p);

// Exibe a árvore sintática construída
void print_ast(ast_p, int);

void ast_print_stack(void);

#endif