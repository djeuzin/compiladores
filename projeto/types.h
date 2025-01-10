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

/*-----Definições de tipos para o lexer-----*/
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
	ENDFILE // token retornado quando é atingido o fim do arquivo
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

/*-----Definições de tipos para o parser-----*/

// Definições dos não-terminais que serão utilizados na pilha
typedef enum{
	PROG,
	DECL_LIST,
	DECL_LIST_,
	DECLARATION,
	DECLARATION_,
	VAR_DECL,
	VAR_DECL_,
	TYPE_SPEC,
	PARAMS,
	VOID_PARAMS,
	PARAM_LIST,
	PARAM_LIST_,
	PARAM,
	PARAM_,
	COMP_STMT,
	LOCAL_DECL,
	LOCAL_DECL_,
	STMT_LIST,
	STMT_LIST_,
	STATEMENT,
	EXP_STMT,
	SELECTION_STMT,
	SELECTION_STMT_,
	ITERATION_STMT,
	RETURN_STMT,
	RETURN_STMT_,
	EXPRESSION,
	EXPRESSION_,
	EXPRESSION__,
	VAR,
	VAR_,
	SIMPLE_EXP,
	RELOP,
	ADD_EXP,
	ADD_EXP_,
	ADDOP,
	TERM,
	TERM_,
	MULOP,
	FACTOR,
	FACTOR_,
	ARGS,
	ARG_LIST,
	ARG_LIST_,
	ENDPARSE // Demarca o final da pilha do parser
} nonTerminal_t;

// Nó da pilha principal do parser
struct stackNode{
	int symbol;
	int isTerminal;
	struct stackNode* next;
};

typedef struct stackNode* stack_p;

#endif