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

char* reserved_words[] = {"else", "if", "int", "return", "void", "while"};

/* Definições dos tokens utilizados */
typedef enum{
        ERR, ELSE, IF, INT, RETURN, VOID, WHILE, ID, NUM,
        PLUS,   // + 
        MINUS,  // - 
        AST,    // * 
        DASH,   // / 
        LTHAN,  // < 
        LEQUAL, // <= 
        GTHAN,  // > 
        GEQUAL, // >= 
        EQUAL,  // == 
        DIFF,   // != 
        ATT,    // = 
        SCOL,   // ; 
        COMMA,  // , 
        OP_PAR, // (
        CL_PAR, // ) 
        OP_BRA, // [
        CL_BRA, // ] 
        OP_CUR, // {
        CL_CUR // } 
}token_t;

// Buffer que armazena o fluxo de caracteres lido no arquivo fonte
typedef struct{
        unsigned int size;
        unsigned int index;
        unsigned int line;
        unsigned int used;
        char buffer[BSIZE];
}buffer_t;
typedef buffer_t* buffer_p;

// Armazena os lexemas obtidos
typedef struct{
        unsigned int line;
        token_t token;
        char lexem[BSIZE];
}lex_t;
typedef lex_t* lex_p;

/* Tabelas utilizadas */
extern int delta_table[][20];
extern int accepting_table[10];
extern int consuming_table[][20];

/* Funções */
buffer_p allocate_buffer(int);
buffer_p deallocate_buffer(buffer_p);
char get_next_char(FILE*, buffer_p);
lex_t get_next_lexem(FILE*, buffer_p, int);
FILE* open_source_file(int, char*[], int*);
void print_lexem(lex_t);
token_t tokenfy_lex(char*, int);