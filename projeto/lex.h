/**************************/
/*  Cross: C- Compiler    */
/*  lex.h                 */
/*  Contém as definições  */
/*  das funções do lexer. */
/**************************/

#ifndef _LEX_H_
#define _LEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "delta_table.h"
#include "types.h"
#include "utils.h"

#define MAX_KEYWORD_LENGTH 6
#define MIN_KEYWORD_LENGTH 2

/* Tabelas utilizadas */
extern int deltaTable[][20];
extern int acceptingTable[9];
extern int usedTable[][20];
extern int debugFlag;
extern FILE* sourceFile;
extern buffer_p mainBuffer;
extern lex_t mainLex;

// Alocação de memória para o buffer
void allocate_buffer();
void deallocate_buffer();

// Manipulação do arquivo fonte
void open_source_file(int, char*[]);
void close_source_file();

// Retorna o próximo caractere do buffer
char get_next_char();

// Retorna o próximo lexema classificado
void get_next_lexem();

// Confere se o token atribuido ao lexema está correto
token_t assert_token();

// Checa se a palavra do lexema é palavra-chave
token_t check_keyword();

// Embrula o lexema para ser utilizado pelo parser
void wrap_lexem();

// Retorna o índice do caractere na tabela de transição
int get_delta_index(char);

#endif