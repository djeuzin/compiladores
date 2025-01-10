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
#include "types.h"
#include "parsing_table.h"

/* Tabela preditiva */
extern int parsingTable[][44];

/* Variáveis externas utilizadas */
extern lex_t mainLex;
extern stack_p parserStack;
extern int currentSymbol;

/* Função externa utilizada */
extern void get_next_lexem();

// Retira o elemento do topo da pilha do parser
void pop_stack();

// Adiciona um elemento à pilha do parser
void push_stack(int, int);

// Libera a memória utilizada pela pilha do parser
void clear_stack();

// Inicializa a pilha do parser
void init_stack();

// Função principal do parser
void parse();

// Manipula a pilha de acordo com a tabela preditiva
void handle_stack(int);

// Verifica se o terminal no topo da pilha é igual ao terminal lido pelo lexer
void match(int, int);

// Exibe a pilha
void print_stack();

#endif