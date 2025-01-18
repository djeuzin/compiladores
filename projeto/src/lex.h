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
#define NUM_KEYWORDS 6

/* Variáveis usadas pelo analisador léxico */
// Buffer do analisador léxico
extern buffer_t mainBuffer;

// Estrutura que armazena cada lexema ao ser lido
extern lex_t mainLex;

/* Tabelas utilizadas na análise léxica */
extern int deltaTable[][20];
extern int acceptingTable[9];
extern int usedTable[][20];

/* Variáveis externas utilizadas */
extern int lexFlag;
extern FILE* sourceFile;
extern buffer_t mainBuffer;
extern lex_t mainLex;

/* Hashs das palavras-chave */
extern char keywords[NUM_KEYWORDS][30];
extern unsigned int keywordsHash[NUM_KEYWORDS];
extern token_t keywordsTokens[NUM_KEYWORDS];

// Alocação de memória para o buffer
void allocate_buffer(void);
void deallocate_buffer(void);

// Retorna o próximo caractere do buffer
char get_next_char(void);

// Retorna o próximo lexema classificado
void get_next_lexem(void);

// Confere se o token atribuido ao lexema está correto
token_t assert_token(void);

// Checa se a palavra do lexema é palavra-chave
token_t check_keyword(void);

// Embrula o lexema para ser utilizado pelo parser
void wrap_lexem(void);

// Retorna o índice do caractere na tabela de transição
int get_delta_index(char);

// Gera um hash para uma palavra
int hash_function(char *);

// Inicializa os hashs das palavras chave
void generate_keywords_hash(void);

#endif