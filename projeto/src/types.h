/**************************/
/*  Cross: C- Compiler    */
/*  types.h               */
/*  Contém as definições  */
/*  dos tipos das         */
/*  variáveis utilizadas. */
/**************************/

#ifndef _TYPES_H_
#define _TYPES_H_

// Tamanho do buffer do analisador léxico
#define BUFFER_SIZE 256

// Definições auxiliares para interagir com flags
#define TRUE 1
#define FALSE 0

// Número máximo de filhos de um nó da árvore sintática abstrata
#define AST_MAX_CHILDREN 3

// Tamanho máximo dos identificadores
#define ID_LENGTH 100

// Número máximo de referências a um identificador
#define NUMBER_OF_REFERENCES 256

// Índices dos fihos do nó da árvore sintática abstrata
#define PARAM_CHILD 0
#define EXP_CHILD 0
#define STMT_CHILD 1
#define INDEX_CHILD 1
#define LEFT_CHILD 0
#define RIGHT_CHILD 1
#define ELSE_CHILD 2

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

// Armazena os lexemas classificados
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
} non_terminal_t;

// Definições dos tipos de nós da pilha de derivação
typedef enum{
	NON_TERMINAL,
	TERMINAL,
	TREE_BUILDER
} parser_stack_kind_t;

// Definições dos tipos de nó da árvore sintática
typedef enum{
	AST_IF,
	AST_WHILE,
	AST_RETURN,
	AST_ARRAY,
	AST_ARRAY_PARAM,
	AST_ARRAY_DECL,
	AST_VAR,
	AST_VAR_PARAM,
	AST_VAR_DECL,
	AST_FUN,
	AST_FUN_DECL,
	AST_CONST,
	AST_OPERAND,
	AST_ASSIGNMENT,
	AST_VOID,
	AST_SIBLING_STOPPER
} ast_node_type_t;

// Indicam ao parser qual ação tomar para construir a árvore sintática abstrata
typedef enum{
	ADD_EXP_CHILD,
	ADD_STMT_CHILD,
	BUILD_EXP,
	ADD_PARAM_CHILD,
	ADD_SIBLING,
	ADD_ELSE_CHILD,
	SET_VAR,
	SET_ARRAY,
	SET_VAR_PARAM,
	SET_ARRAY_PARAM,
	SET_VAR_DECL,
	SET_ARRAY_DECL,
	SET_FUN_DECL,
	SET_FUN_CALL,
	SET_VOID_PARAM,
	ADD_SIBLING_STOPPER,
	ADD_ARRAY_INDEX
} ast_action_t;

// Nó da pilha principal de derivação
struct stackNode{
	int symbol;
	parser_stack_kind_t kind;
	struct stackNode* next;
};
typedef struct stackNode* parser_stack_p;

// Nó da árvore sintática abstrata
struct astNode{
	char* name;
	ast_node_type_t type;
	token_t token;
	int typeSpecifier;
	int value;
	char id[ID_LENGTH];
	int arraySize;
	int line;
	int column;
	int visited;
	struct astNode* sibling;
	struct astNode* children[AST_MAX_CHILDREN];
};
typedef struct astNode ast_t;
typedef ast_t* ast_p;

// Pilha auxiliar para construir a árvore sintática abstrata
struct astStack{
	ast_p top;
	struct astStack* next;
};
typedef struct astStack ast_stack_t;
typedef ast_stack_t* ast_stack_p;

/* Definições para análise semântica */
#define SYMBOL_TABLE_SIZE 211
#define ALPHA 2
#define INITIAL_DEPTH 1

// Definição do nó da tabela de símbolos
struct symbolTable{
	// Variáveis para exibição
        char* id;
        char* scope;
        char* type;
        char* dataType;
        // Variáveis para implementar a lógica da tabela
        int params[NUMBER_OF_REFERENCES];
        int paramsIndex;
        int lines[NUMBER_OF_REFERENCES];
        int linesIndex;
        int typeSpecifier;
        int objectType;
        struct symbolTable* next;
};
typedef struct symbolTable* table_p;

#endif