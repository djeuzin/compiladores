/***************************/
/*  Cross: C- Compiler     */
/*  utils.h                */
/*  Contém as definições   */
/*  de funções utilitárias */
/***************************/

#ifndef _UTILS_H_
#define _UTILS_H_

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

extern int lexFlag;
extern int parserFlag;
extern int lexOnly;
extern int semanticFlag;

extern lex_t mainLex;
extern FILE* sourceFile;

// Funções auxiliares para exibição
void print_b(char*);
void print_r(char*);
void red_text();
void default_color_text();

// Manipulação do arquivo fonte
void open_source_file(int, char*[]);
void close_source_file();

// Exibe as opções do programa
void display_help();

// Exibe o lexema classificado
void print_lexem();

// Checa se um nó possui filhos
int hasChildren(ast_p);

// Exibe a árvore sintática construída
void print_ast(ast_p, int);

// Exibe a tabela de símbolos
void print_symbol_table();

#endif