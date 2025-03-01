/***************************/
/*  Cross: C- Compiler     */
/*  delta_table.c          */
/*  Contém as definições   */
/*  da tabela do DFA       */
/*  utilizado pelo lexer e */
/*  de tabelas auxiliares  */
/***************************/

#include "delta_table.h"

// Na descrição das tabelas os seguintes caracteres representam:
// l = [A-Za-z]
// d = [0-9]
// b = [\n ]
// . = Qualquer outro caractere não descrito

// Tabela de transição de estados do analisador léxico
int deltaTable[][20] = {
//       l, d, +, -, *, /, <, >, =, !, ;, ,, (, ), [, ], {, }, ., b 
        {1, 3, 8, 8, 8, 5, 4, 4, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0},   // state 0
        {1, 2, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},   // state 1
        {2, 2, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},   // state 2
        {2, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},   // state 3
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},   // state 4
        {8, 8, 8, 8, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},   // state 5
        {6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},   // state 6
        {6, 6, 6, 6, 7, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}    // state 7
};

// Tabela que indica quais estados do DFA do analisador léxico são de aceitação
int acceptingTable[] = {0, 0, 0, 0, 0, 0, 0, 0, 1};

// Tabela que indica, para cada transição do DFA, se o caractere é consumido (1) ou não (0)
int usedTable[][20] = {
//       l, d, +, -, *, /, <, >, =, !, ;, ,, (, ), [, ], {, }, ., b     
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},   // state 0
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 1
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 2
        {2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 3
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 4
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // state 5
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},   // state 6
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}    // state 7
};

// Retorna se o estado é um que deve ser ignorado pelo lexer
int is_ignored_state(int state){
        return (state == 6 || state == 7 || state == 0);
}