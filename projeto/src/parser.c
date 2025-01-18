/**************************/
/*  Cross: C- Compiler    */
/*  parser.h              */
/*  Contém as definições  */
/*  das funções do parser.*/
/**************************/

#include "parser.h"

// Pilha de derivação da analisador sintático
parser_stack_p parserStack;
// Símbolo do topo da pilha
int currentSymbol;

/*
 * Argumento: vazio
 * Retorna: vazio
 * Retira o elemento do topo da pilha de
 * derivação e armazena o valor na variável
 * currentSymbol.
 */
void pop_stack(){
	currentSymbol = parserStack->symbol;
	parser_stack_p aux = parserStack;
	parserStack = parserStack->next;
	free(aux);
}

/*
 * Argumentos: int newSymbol, int kind
 * Retorna: vazio
 * Adiciona ao topo da pilha de derivação
 * o novo símbolo e o seu tipo.
 */
void push_stack(int newSymbol, int kind){
	parser_stack_p aux = malloc(sizeof(struct stackNode));
	aux->symbol = newSymbol;
	aux->kind = kind;
	aux->next = parserStack;
	parserStack = aux;
}

/*
 * Agumento: vazio
 * Retorna: vazio
 * Libera a memória utilizada pela pilha de derivação.
 */
void clear_stack(){
	parser_stack_p aux;

	while(parserStack){
		aux = parserStack;
		parserStack = parserStack->next;
		free(aux);
	}
}

/*
 * Argumento: vazio
 * Retorna: vazio
 * Inicializa a pilha de derivação com o símbolo
 * de fundo da pilha e o não terminal inicial.
 */
void init_stack(){
	parserStack = NULL;
	push_stack(ENDPARSE, 0);
	push_stack(PROG, 0);
}

/*
 * Argumentos: int currentSymbol, int token
 * Retorna: inteiro
 * Compara currentSymbol com token. Se forem diferentes
 * indica erro e retorna FALSE, caso contrário retorna TRUE
 * indicando que houve sucesso na comparação.
 */
int match(int currentSymbol, int token){
        if(currentSymbol != token){
                printf("ERRO SINTATICO: \"%s\" INVALIDO [linha: %d], COLUNA %d.\n", mainLex.word, mainLex.line, mainLex.column);
                return FALSE;
        }
	return TRUE;
}

/*
 * Argumento: vazio
 * Retorna: vazio
 * Exibe os elementos da pilha de derivação.
 */
void print_stack(){
        parser_stack_p aux = parserStack;
        while(aux != NULL){
                printf("%d-%d\n", aux->symbol, aux->kind);
                aux = aux->next;
        }
}

/*
 * Argumento: vazio
 * Retorna: vazio
 * Função principal do parser. Realiza derivações mais à esquerda utilizando a pilha de derivação
 * e constrói uma árvore de análise sintática abstrata representando
 * a estrutura do programa parseado utilizando a tabela preditiva LL(1)
 */
void parse(){
	allocate_buffer();
	int nextStep;

	init_stack();
	get_next_lexem();

	while(parserStack->symbol != ENDPARSE){
		switch(parserStack->kind){
			case TERMINAL:
			pop_stack();
			
			if(!match(currentSymbol, mainLex.token)){
				printf("Erro ao parsear\n");
				clear_stack();
				exit(1);
			}
			
			get_next_lexem();
			break;
			case NON_TERMINAL:
			pop_stack();
			nextStep = parsingTable[currentSymbol][mainLex.token];
			
			if(nextStep == 0){
                                printf("ERRO SINTATICO: \"%s\" INVALIDO [linha: %d], COLUNA %d.\n", mainLex.word, mainLex.line, mainLex.column);
				clear_stack();
				exit(1);
			}

			handle_stack(nextStep);
			break;
			case TREE_BUILDER:
			pop_stack();
			
			break;
		}
	}

	clear_stack();
	deallocate_buffer();
}

/*
 * Argumento: int nextStep
 * Retorna: vazio
 * Realiza o passo de derivação correspondente à nextStep.
 */
void handle_stack(int nextStep){
	switch(nextStep){
		case 1:
		push_stack(DECL_LIST, NON_TERMINAL);
		break;
		case 2:
		push_stack(DECL_LIST_, NON_TERMINAL);
		push_stack(DECLARATION, NON_TERMINAL);
		break;
		case 3:
		push_stack(DECL_LIST_, NON_TERMINAL);
		push_stack(DECLARATION, NON_TERMINAL);
		break;
		case 4:
		break;
		case 5:
		push_stack(DECLARATION_, NON_TERMINAL);
		push_stack(ID, TERMINAL);
		push_stack(TYPE_SPEC, NON_TERMINAL);
		break;
		case 6:
		push_stack(VAR_DECL_, NON_TERMINAL);
		break;
		case 7:
		push_stack(COMP_STMT, NON_TERMINAL);
		push_stack(CL_PAR, TERMINAL);
		push_stack(PARAMS, NON_TERMINAL);
		push_stack(OP_PAR, TERMINAL);
		break;
		case 8:
		push_stack(VAR_DECL_, NON_TERMINAL);
		push_stack(ID, TERMINAL);
		push_stack(TYPE_SPEC, NON_TERMINAL);
		break;
		case 9:
		push_stack(SCOL, TERMINAL);
		break;
		case 10:
		push_stack(SCOL, TERMINAL);
		push_stack(CL_BRA, TERMINAL);
		push_stack(NUM, TERMINAL);
		push_stack(OP_BRA, TERMINAL);
		break;
		case 11:
		push_stack(INT, TERMINAL);
		break;
		case 12:
		push_stack(VOID, TERMINAL);
		break;
		case 13:
		push_stack(PARAM_LIST_, NON_TERMINAL);
		push_stack(PARAM_, NON_TERMINAL);
		push_stack(ID, TERMINAL);
		push_stack(INT, TERMINAL);
		break;
		case 14:
		push_stack(VOID_PARAMS, NON_TERMINAL);
		push_stack(VOID, TERMINAL);
		break;
		case 15:
		push_stack(PARAM_LIST_, NON_TERMINAL);
		push_stack(PARAM_, NON_TERMINAL);
		push_stack(ID, TERMINAL);
		break;
		case 16:
		break;
		case 17:
		push_stack(PARAM_LIST_, NON_TERMINAL);
		push_stack(PARAM, NON_TERMINAL);
		break;
		case 18:
		push_stack(PARAM_LIST_, NON_TERMINAL);
		push_stack(PARAM, NON_TERMINAL);
		push_stack(COMMA, TERMINAL);
		break;
		case 19:
		break;
		case 20:
		push_stack(PARAM_, NON_TERMINAL);
		push_stack(ID, TERMINAL);
		push_stack(TYPE_SPEC, NON_TERMINAL);
		break;
		case 21:
		push_stack(CL_BRA, TERMINAL);
		push_stack(OP_BRA, TERMINAL);
		break;
		case 22:
		break;
		case 23:
		push_stack(CL_CUR, TERMINAL);
		push_stack(STMT_LIST, NON_TERMINAL);
		push_stack(LOCAL_DECL, NON_TERMINAL);
		push_stack(OP_CUR, TERMINAL);
		break;
		case 24:
		push_stack(LOCAL_DECL_, NON_TERMINAL);
		break;
		case 25:
		push_stack(LOCAL_DECL_, NON_TERMINAL);
		push_stack(VAR_DECL, NON_TERMINAL);
		break;
		case 26:
		break;
		case 27:
		push_stack(STMT_LIST_, NON_TERMINAL);
		break;
		case 28:
		push_stack(STMT_LIST_, NON_TERMINAL);
		push_stack(STATEMENT, NON_TERMINAL);
		break;
		case 29:
		break;
		case 30:
		push_stack(EXP_STMT, NON_TERMINAL);
		break;
		case 31:
		push_stack(COMP_STMT, NON_TERMINAL);
		break;
		case 32:
		push_stack(SELECTION_STMT, NON_TERMINAL);
		break;
		case 33:
		push_stack(ITERATION_STMT, NON_TERMINAL);
		break;
		case 34:
		push_stack(RETURN_STMT, NON_TERMINAL);
		break;
		case 35:
		push_stack(SCOL, TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		break;
		case 36:
		push_stack(SCOL, TERMINAL);
		break;
		case 37:
		push_stack(SELECTION_STMT_, NON_TERMINAL);
		push_stack(STATEMENT, NON_TERMINAL);
		push_stack(CL_PAR, TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		push_stack(OP_PAR, TERMINAL);
		push_stack(IF, TERMINAL);
		break;
		case 38:
		push_stack(STATEMENT, NON_TERMINAL);
		push_stack(ELSE, TERMINAL);
		break;
		case 39:
		break;
		case 40:
		push_stack(STATEMENT, NON_TERMINAL);
		push_stack(CL_PAR, TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		push_stack(OP_PAR, TERMINAL);
		push_stack(WHILE, TERMINAL);
		break;
		case 41:
		push_stack(RETURN_STMT_, NON_TERMINAL);
		push_stack(RETURN, TERMINAL);
		break;
		case 42:
		push_stack(SCOL, TERMINAL);
		break;
		case 43:
		push_stack(SCOL, TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		break;
		case 44:
		push_stack(EXPRESSION_, NON_TERMINAL);
		push_stack(ID, TERMINAL);
		break;
		case 45:
		push_stack(SIMPLE_EXP, NON_TERMINAL);
		push_stack(ADD_EXP_, NON_TERMINAL);
		push_stack(TERM_, NON_TERMINAL);
		push_stack(CL_PAR, TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		push_stack(OP_PAR, TERMINAL);
		break;
		case 46:
		push_stack(SIMPLE_EXP, NON_TERMINAL);
		push_stack(ADD_EXP_, NON_TERMINAL);
		push_stack(TERM_, NON_TERMINAL);
		push_stack(NUM, TERMINAL);
		break;
		case 47:
		push_stack(EXPRESSION__, NON_TERMINAL);
		push_stack(VAR_, NON_TERMINAL);
		break;
		case 48:
		push_stack(SIMPLE_EXP, NON_TERMINAL);
		push_stack(ADD_EXP_, NON_TERMINAL);
		push_stack(TERM_, NON_TERMINAL);
		push_stack(CL_PAR, TERMINAL);
		push_stack(ARGS, NON_TERMINAL);
		push_stack(OP_PAR, TERMINAL);
		break;
		case 49:
		push_stack(EXPRESSION, NON_TERMINAL);
		push_stack(ATT, TERMINAL);
		break;
		case 50:
		push_stack(SIMPLE_EXP, NON_TERMINAL);
		push_stack(ADD_EXP_, NON_TERMINAL);
		push_stack(TERM_, NON_TERMINAL);
		break;
		case 51:
		push_stack(VAR_, NON_TERMINAL);
		push_stack(ID, TERMINAL);
		break;
		case 52:
		push_stack(CL_BRA, TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		push_stack(OP_BRA, TERMINAL);
		break;
		case 53:
		break;
		case 54:
		push_stack(ADD_EXP, NON_TERMINAL);
		push_stack(RELOP, NON_TERMINAL);
		break;
		case 55:
		break;
		case 56:
		push_stack(LEQUAL, TERMINAL);
		break;
		case 57:
		push_stack(LTHAN, TERMINAL);
		break;
		case 58:
		push_stack(GTHAN, TERMINAL);
		break;
		case 59:
		push_stack(GEQUAL, TERMINAL);
		break;
		case 60:
		push_stack(EQUAL, TERMINAL);
		break;
		case 61:
		push_stack(DIFF, TERMINAL);
		break;
		case 62:
		push_stack(ADD_EXP_, NON_TERMINAL);
		push_stack(TERM, NON_TERMINAL);
		break;
		case 63:
		push_stack(ADD_EXP_, NON_TERMINAL);
		push_stack(TERM, NON_TERMINAL);
		push_stack(ADDOP, NON_TERMINAL);
		break;
		case 64:
		break;
		case 65:
		push_stack(PLUS, TERMINAL);
		break;
		case 66:
		push_stack(MINUS, TERMINAL);
		break;
		case 67:
		push_stack(TERM_, NON_TERMINAL);
		push_stack(FACTOR, NON_TERMINAL);
		break;
		case 68:
		push_stack(TERM_, NON_TERMINAL);
		push_stack(FACTOR, NON_TERMINAL);
		push_stack(MULOP, NON_TERMINAL);
		break;
		case 69:
		break;
		case 70:
		push_stack(AST, TERMINAL);
		break;
		case 71:
		push_stack(DASH, TERMINAL);
		break;
		case 72:
		push_stack(CL_PAR, TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		push_stack(OP_PAR, TERMINAL);
		break;
		case 73:
		push_stack(FACTOR_, NON_TERMINAL);
		push_stack(ID, TERMINAL);
		break;
		case 74:
		push_stack(NUM, TERMINAL);
		break;
		case 75:
		push_stack(VAR_, NON_TERMINAL);
		break;
		case 76:
		push_stack(CL_PAR, TERMINAL);
		push_stack(ARGS, NON_TERMINAL);
		push_stack(OP_PAR, TERMINAL);
		break;
		case 77:
		push_stack(ARG_LIST, NON_TERMINAL);
		break;
		case 78:
		break;
		case 79:
		push_stack(ARG_LIST_, NON_TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		break;
		case 80:
		push_stack(ARG_LIST_, NON_TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		push_stack(COMMA, TERMINAL);
		break;
		case 81:
		break;
	}
}