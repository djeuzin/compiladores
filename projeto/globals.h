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

int debugFlag = 0;
FILE* sourceFile;
buffer_p mainBuffer;
lex_t mainLex;

#endif