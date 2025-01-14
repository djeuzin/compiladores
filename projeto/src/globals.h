/**************************/
/*  Cross: C- Compiler    */
/*  globals.h             */
/*  Contém as definições  */
/*  das variáveis globais */
/*  utilizadas.           */
/**************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

/* Flags opcionais */
// Exibe os lexemas classificados se for TRUE
int lexFlag = FALSE;

// Exibe a árvore sintática abstrata se for TRUE
int parserFlag = FALSE;

// Realiza apenas a análise léxica do arquivo fonte se for TRUE
int lexOnly = FALSE;

// Arquivo fonte que será analisado
FILE* sourceFile;

/* Variáveis usadas pelo analisador léxico */
// Buffer do analisador léxico
buffer_t mainBuffer;

// Estrutura que armazena cada lexema ao ser lido
lex_t mainLex;

/* Variáveis utilizadas pelo parser */
// Pilha de derivação doa analisador sintático
stack_p parserStack;

// Símbolo do topo da pilha, é atualizado ao ativar a rotina pop_stack()
int currentSymbol;

#endif