#ifndef _DELTA_TABLE_H_
#define _DELTA_TABLE_H_

// Na descrição daa tabelas os seguintes caracteres representam:
// l = [A-Za-z]
// d = [0-9]
// b = [\n ]
// . = Qualquer outro caractere não descrito

// Tabela de transição de estados do analisador léxico
static int delta_table[][20] = {
//       l, d, +, -, *, /, <, >, =, !, ;, ,, (, ), [, ], {, }, ., b 
        {1, 2, 3, 3, 3, 5, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},   // state 0
        {1, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},   // state 1
        {8, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},   // state 2
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 3
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},   // state 4
        {8, 8, 8, 8, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},   // state 5
        {6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},   // state 6
        {6, 6, 6, 6, 7, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},   // state 7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}    // state 8
};

// Tabela que indica quais estados do DFA do analisador léxico são de aceitação
static int accepting_table[] = {0, 0, 0, 1, 0, 0, 0, 0, 1};

// Tabela que indica, para cada transição do DFA, se o caractere é consumido (1) ou não (0)
static int used_table[][20] = {
//       l, d, +, -, *, /, <, >, =, !, ;, ,, (, ), [, ], {, }, b, .     
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},   // state 0
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 1
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 2
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 3
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 4
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 5
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},   // state 6
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},   // state 7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}    // state 8
};

#endif