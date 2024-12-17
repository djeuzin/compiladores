/*
        CROSS: C- compiler
              ____
             /    \
      ______/      \______
     /                    \
    /______          ______\
    \     /          \     /
     \___/            \___/
        /              \
       /                \
      /                  \ 
     /____________________\
     \                    /
      \                  /
       \________________/

                                */



#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lex.h"

int debugFlag = 0;
FILE* sourceFile;
buffer_p mainBuffer;
lex_t mainLex;

#endif