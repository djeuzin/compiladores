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

extern lex_t mainLex;
extern FILE* sourceFile;

void print_lexem();
void blue_text();
void default_color_text();

// Manipulação do arquivo fonte
void open_source_file(int, char*[]);
void close_source_file();

void display_help();

#endif