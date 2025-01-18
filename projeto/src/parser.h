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

// Exibe a pilha
void print_stack(void);

#endif