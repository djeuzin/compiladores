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
        ELSE, IF, INT, RETURN, VOID, WHILE, OMTM
}token_t;

// Buffer que armazena o fluxo de caracteres lido do arquivo fonte
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
        unsigned int size;
        token_t token;
        char word[BUFFER_SIZE];
}lex_t;
typedef lex_t* lex_p;

#endif