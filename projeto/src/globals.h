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

// Exibe a tabela de símbolos se for TRUE
int semanticFlag = FALSE;

// Arquivo fonte que será analisado
FILE* sourceFile;

// Raiz da árvore de análise sintática
ast_p syntaxTree;

#endif