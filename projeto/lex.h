#ifndef _LEX_H_
#define _LEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "delta_table.h"

/* Definições úteis */

#define BSIZE 256       // Tamanho do buffer do lexer

/*
        Para as definições de tipo a convenção é utilizar sufixo _t para 
        tipos definidos e sufixo _p para ponteiros dos tipos a fim de não
        sobrecarregar o código com sintaxe de ponteiros.
*/

/* Definições dos tokens utilizados */
typedef enum{
        ID, NUM,
        PLUS,   // + 
        MINUS,  // - 
        AST,    // * 
        DASH,   // / 
        LTHAN,  // < 
        GTHAN,  // > 
        ATT,    // = 
        DIFF,   // != 
        SCOL,   // ; 
        COMMA,  // , 
        OP_PAR, // (
        CL_PAR, // ) 
        OP_BRA, // [
        CL_BRA, // ] 
        OP_CUR, // {
        CL_CUR, // } 
        ERR,
        LEQUAL, // <= 
        GEQUAL, // >= 
        EQUAL,  // == 
        ELSE, IF, INT, RETURN, VOID, WHILE
}token_t;

// Buffer que armazena o fluxo de caracteres lido no arquivo fonte
typedef struct{
        unsigned int size;
        unsigned int index;
        unsigned int line;
        unsigned int used;
        char* buffer;
}buffer_t;
typedef buffer_t* buffer_p;

// Armazena os lexemas obtidos
typedef struct{
        unsigned int line;
        unsigned int last;
        token_t token;
        char word[BSIZE];
}lex_t;
typedef lex_t* lex_p;

/* Tabelas utilizadas */
extern int delta_table[][20];
extern int accepting_table[9];
extern int used_table[][20];
extern int debugFlag;
extern FILE* sourceFile;
extern buffer_p mainBuffer;

/* Funções */
void allocate_buffer();
void deallocate_buffer();
void open_source_file(int, char*[]);
void print_lexem(lex_t);
void close_source_file();
char get_next_char();
lex_t get_next_lexem();
token_t assert_token(lex_t, int);
token_t check_keyword(char*, int);
int get_delta_index(char);

#define MAX_KEYWORD_LENGTH 6
#define MIN_KEYWORD_LENGTH 2
#endif