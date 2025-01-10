/**************************/
/*  Cross: C- Compiler    */
/*  parser.h              */
/*  Contém as definições  */
/*  das funções do parser.*/
/**************************/

#include "parser.h"

// Retira um elemento da pilha do parser e armazena seu valor na variável currentSymbol
void pop_stack(){
	currentSymbol = parserStack->symbol;
	stack_p aux = parserStack;
	parserStack = parserStack->next;
	free(aux);
}

// Adiciona um elemento à pilha do parser
void push_stack(int newSymbol, int isTerminal){
	stack_p aux = malloc(sizeof(struct stackNode));
	aux->symbol = newSymbol;
	aux->isTerminal = isTerminal;
	aux->next = parserStack;
	parserStack = aux;
}

// Libera a memória utilizada pela pilha
void clear_stack(){
	stack_p aux;

	while(parserStack){
		aux = parserStack;
		parserStack = parserStack->next;
		free(aux);
	}
}

// Inicializa a pilha do parser para a análise sintática
void init_stack(){
	parserStack = NULL;
	push_stack(ENDPARSE, 0);
	push_stack(PROG, 0);
}

// Verifica se o símbolo atual da pilha é igual ao token lido pelo lexer
void match(int currentSymbol, int token){
        if(currentSymbol != token){
                printf("Erro de casamento.\n \
                \"%s\", simbolo: %d em linha %d \
                 \n", mainLex.word, currentSymbol, mainLex.line);
                exit(1);
        }
}

// Exibe os elementos da pilha
void print_stack(){
        printf("token atual: %s\n", mainLex.word);
        stack_p aux = parserStack;
        while(aux != NULL){
                printf("%d-%d\n", aux->symbol, aux->isTerminal);
                aux = aux->next;
        }
}

// Função principal do parser
// Utiliza a tabela preditiva LL(1) para analisar a sintaxe do arquivo fonte
void parse(){
	// Indica qual o próximo passo na derivação deve ser tomado
	int nextStep;

	init_stack();
	get_next_lexem();

	while(parserStack->symbol != ENDPARSE){
		if(parserStack->isTerminal){
			// Se o símbolo no topo da pilha é um terminal, então 
			// comparamos ele com o que é lido pelo lexer
			pop_stack();
			match(currentSymbol, mainLex.token);
			get_next_lexem();
		}
		else{
			// O símbolo no topo da pilha é um não terminal
			// Verificamos qual passo de derivação deve ser tomado pela tabela
			// Chamamos handleStack() para manipular a pilha com a derivação correspondente
			pop_stack();
			nextStep = parsingTable[currentSymbol][mainLex.token];
			
			if(nextStep == 0){
                                printf("<%s> simbolo atual: %d na linha: %d coluna: %d\n", mainLex.word, currentSymbol, mainLex.line, mainLex.column);
				printf("Erro crítico.\n");
				return;
			}

			handle_stack(nextStep);
		}
	}

	if(ENDFILE == mainLex.token)
		printf("Programa parseado com sucesso.\n");
	else{
		printf("Erro ao parsear.\n");
        }

	clear_stack();
}

// Realiza os passos de derivação da gramática
void handle_stack(int nextStep){
	switch(nextStep){
		case 1:
		push_stack(DECL_LIST, 0);
		break;
		case 2:
		push_stack(DECL_LIST_, 0);
		push_stack(DECLARATION, 0);
		break;
		case 3:
		push_stack(DECL_LIST_, 0);
		push_stack(DECLARATION, 0);
		break;
		case 4:
		break;
		case 5:
		push_stack(DECLARATION_, 0);
		push_stack(ID, 1);
		push_stack(TYPE_SPEC, 0);
		break;
		case 6:
		push_stack(VAR_DECL_, 0);
		break;
		case 7:
		push_stack(COMP_STMT, 0);
		push_stack(CL_PAR, 1);
		push_stack(PARAMS, 0);
		push_stack(OP_PAR, 1);
		break;
		case 8:
		push_stack(VAR_DECL_, 0);
		push_stack(ID, 1);
		push_stack(TYPE_SPEC, 0);
		break;
		case 9:
		push_stack(SCOL, 1);
		break;
		case 10:
		push_stack(SCOL, 1);
		push_stack(CL_BRA, 1);
		push_stack(NUM, 1);
		push_stack(OP_BRA, 1);
		break;
		case 11:
		push_stack(INT, 1);
		break;
		case 12:
		push_stack(VOID, 1);
		break;
		case 13:
		push_stack(PARAM_LIST_, 0);
		push_stack(PARAM_, 0);
		push_stack(ID, 1);
		push_stack(INT, 1);
		break;
		case 14:
		push_stack(VOID_PARAMS, 0);
		push_stack(VOID, 1);
		break;
		case 15:
		push_stack(PARAM_LIST_, 0);
		push_stack(PARAM_, 0);
		push_stack(ID, 1);
		break;
		case 16:
		break;
		case 17:
		push_stack(PARAM_LIST_, 0);
		push_stack(PARAM, 0);
		break;
		case 18:
		push_stack(PARAM_LIST_, 0);
		push_stack(PARAM, 0);
		push_stack(COMMA, 1);
		break;
		case 19:
		break;
		case 20:
		push_stack(PARAM_, 0);
		push_stack(ID, 1);
		push_stack(TYPE_SPEC, 0);
		break;
		case 21:
		push_stack(CL_BRA, 1);
		push_stack(OP_BRA, 1);
		break;
		case 22:
		break;
		case 23:
		push_stack(CL_CUR, 1);
		push_stack(STMT_LIST, 0);
		push_stack(LOCAL_DECL, 0);
		push_stack(OP_CUR, 1);
		break;
		case 24:
		push_stack(LOCAL_DECL_, 0);
		break;
		case 25:
		push_stack(LOCAL_DECL_, 0);
		push_stack(VAR_DECL, 0);
		break;
		case 26:
		break;
		case 27:
		push_stack(STMT_LIST_, 0);
		break;
		case 28:
		push_stack(STMT_LIST_, 0);
		push_stack(STATEMENT, 0);
		break;
		case 29:
		break;
		case 30:
		push_stack(EXP_STMT, 0);
		break;
		case 31:
		push_stack(COMP_STMT, 0);
		break;
		case 32:
		push_stack(SELECTION_STMT, 0);
		break;
		case 33:
		push_stack(ITERATION_STMT, 0);
		break;
		case 34:
		push_stack(RETURN_STMT, 0);
		break;
		case 35:
		push_stack(SCOL, 1);
		push_stack(EXPRESSION, 0);
		break;
		case 36:
		push_stack(SCOL, 1);
		break;
		case 37:
		push_stack(SELECTION_STMT_, 0);
		push_stack(STATEMENT, 0);
		push_stack(CL_PAR, 1);
		push_stack(EXPRESSION, 0);
		push_stack(OP_PAR, 1);
		push_stack(IF, 1);
		break;
		case 38:
		push_stack(STATEMENT, 0);
		push_stack(ELSE, 1);
		break;
		case 39:
		break;
		case 40:
		push_stack(STATEMENT, 0);
		push_stack(CL_PAR, 1);
		push_stack(EXPRESSION, 0);
		push_stack(OP_PAR, 1);
		push_stack(WHILE, 1);
		break;
		case 41:
		push_stack(RETURN_STMT_, 0);
		push_stack(RETURN, 1);
		break;
		case 42:
		push_stack(SCOL, 1);
		break;
		case 43:
		push_stack(SCOL, 1);
		push_stack(EXPRESSION, 0);
		break;
		case 44:
		push_stack(EXPRESSION_, 0);
		push_stack(ID, 1);
		break;
		case 45:
		push_stack(SIMPLE_EXP, 0);
		push_stack(ADD_EXP_, 0);
		push_stack(TERM_, 0);
		push_stack(CL_PAR, 1);
		push_stack(EXPRESSION, 0);
		push_stack(OP_PAR, 1);
		break;
		case 46:
		push_stack(SIMPLE_EXP, 0);
		push_stack(ADD_EXP_, 0);
		push_stack(TERM_, 0);
		push_stack(NUM, 1);
		break;
		case 47:
		push_stack(EXPRESSION__, 0);
		push_stack(VAR_, 0);
		break;
		case 48:
		push_stack(SIMPLE_EXP, 0);
		push_stack(ADD_EXP_, 0);
		push_stack(TERM_, 0);
		push_stack(CL_PAR, 1);
		push_stack(ARGS, 0);
		push_stack(OP_PAR, 1);
		break;
		case 49:
		push_stack(EXPRESSION, 0);
		push_stack(ATT, 1);
		break;
		case 50:
		push_stack(SIMPLE_EXP, 0);
		push_stack(ADD_EXP_, 0);
		push_stack(TERM_, 0);
		break;
		case 51:
		push_stack(VAR_, 0);
		push_stack(ID, 1);
		break;
		case 52:
		push_stack(CL_BRA, 1);
		push_stack(EXPRESSION, 0);
		push_stack(OP_BRA, 1);
		break;
		case 53:
		break;
		case 54:
		push_stack(ADD_EXP, 0);
		push_stack(RELOP, 0);
		break;
		case 55:
		break;
		case 56:
		push_stack(LEQUAL, 1);
		break;
		case 57:
		push_stack(LTHAN, 1);
		break;
		case 58:
		push_stack(GTHAN, 1);
		break;
		case 59:
		push_stack(GEQUAL, 1);
		break;
		case 60:
		push_stack(EQUAL, 1);
		break;
		case 61:
		push_stack(DIFF, 1);
		break;
		case 62:
		push_stack(ADD_EXP_, 0);
		push_stack(TERM, 0);
		break;
		case 63:
		push_stack(ADD_EXP_, 0);
		push_stack(TERM, 0);
		push_stack(ADDOP, 0);
		break;
		case 64:
		break;
		case 65:
		push_stack(PLUS, 1);
		break;
		case 66:
		push_stack(MINUS, 1);
		break;
		case 67:
		push_stack(TERM_, 0);
		push_stack(FACTOR, 0);
		break;
		case 68:
		push_stack(TERM_, 0);
		push_stack(FACTOR, 0);
		push_stack(MULOP, 0);
		break;
		case 69:
		break;
		case 70:
		push_stack(AST, 1);
		break;
		case 71:
		push_stack(DASH, 1);
		break;
		case 72:
		push_stack(CL_PAR, 1);
		push_stack(EXPRESSION, 0);
		push_stack(OP_PAR, 1);
		break;
		case 73:
		push_stack(FACTOR_, 0);
		push_stack(ID, 1);
		break;
		case 74:
		push_stack(NUM, 1);
		break;
		case 75:
		push_stack(VAR_, 0);
		break;
		case 76:
		push_stack(CL_PAR, 1);
		push_stack(ARGS, 0);
		push_stack(OP_PAR, 1);
		break;
		case 77:
		push_stack(ARG_LIST, 0);
		break;
		case 78:
		break;
		case 79:
		push_stack(ARG_LIST_, 0);
		push_stack(EXPRESSION, 0);
		break;
		case 80:
		push_stack(ARG_LIST_, 0);
		push_stack(EXPRESSION, 0);
		push_stack(COMMA, 1);
		break;
		case 81:
		break;
	}
}