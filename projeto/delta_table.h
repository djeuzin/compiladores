/***************************/
/*  Cross: C- Compiler     */
/*  delta_table.h          */
/*  Contém a declaração    */
/*  da tabela do DFA       */
/*  utilizado pelo lexer e */
/*  de tabelas auxiliares  */
/***************************/

#ifndef _DELTA_TABLE_H_
#define _DELTA_TABLE_H_

// Tabela de transição de estados do analisador léxico
extern int deltaTable[][20];

// Tabela que indica quais estados do DFA do analisador léxico são de aceitação
extern int acceptingTable[];

// Tabela que indica, para cada transição do DFA, se o caractere é consumido (1) ou não (0)
extern int usedTable[][20];

#endif