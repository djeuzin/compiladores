/**************************/
/*  Cross: C- Compiler    */
/*  types.h               */
/*  Contém as definições  */
/*  dos tipos das         */
/*  variáveis utilizadas. */
/**************************/

#ifndef _TYPES_H_
#define _TYPES_H_

#define BUFFER_SIZE 256

// Para definir os tipos utiliza-se sufixo _t
// Para ponteiros de tipos utiliza-se o sufixo _p

// Definição dos tokens dos lexemas
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
        ELSE, IF, INT, RETURN, VOID, WHILE, 
        ENDFILE // Token de fim de arquivo
}token_t;

// Buffer que armazena o fluxo de caracteres lido do arquivo fonte
typedef struct{
        unsigned int index;
        unsigned int line;
        unsigned int column;
        unsigned int used;
        char* buffer;
}buffer_t;

// Armazena os lexemas obtidos
typedef struct{
        unsigned int line;
        unsigned int size;
        unsigned int column;
        token_t token;
        char word[BUFFER_SIZE];
}lex_t;

#endif