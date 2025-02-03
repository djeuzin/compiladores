/**************************/
/*  Cross: C- Compiler    */
/*  parser.h              */
/*  Contém as definições  */
/*  das funções do parser.*/
/**************************/

#include "parser.h"
#include "parsing_table.h"
#include "types.h"
#include "utils.h"
#include <stdio.h>

// Pilha de derivação da analisador sintático
parser_stack_p parserStack;
// Símbolo do topo da pilha
int currentSymbol;
// Nó da árvore que receberá os dados lidos pelo lexer
ast_p dummyNode;
// Pilha auxiliar para construir a árvore sintática
ast_stack_p treeNodeStack;

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
 * indica erro e retorna FALSE, caso contrário retorna TRUE.
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
 * Função utilizada durante desenvolvimento.
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
	// Inidica o próximo passo de derivação a ser tomado
	int nextStep;
	int errorFlag = FALSE;

	allocate_buffer();
	init_stack();
	init_tree_stack();
	get_next_lexem();

	while(parserStack->symbol != ENDPARSE){
		switch(parserStack->kind){
			case TERMINAL: {
				/*
				 * Símbolo no topo da pilha de análise seintática é um terminal.
				 * Se esse símbolo for diferente do que é lido na entrada indicamos
				 * o erro. Em caso de sucesso criamos um nó receptáculo e o preenchemos
				 * de acordo com o token lido. Por fim lemos o próximo token da entrada.
				 */
				pop_stack();
				
				if(!match(currentSymbol, mainLex.token)){
					if(errorFlag == FALSE){
						errorFlag = TRUE;
						ast_clear_stack();
						if(dummyNode)
							free(dummyNode);
						dummyNode = NULL;
					}
					get_next_lexem();
					break;
				}

				if(errorFlag == FALSE){
					if(dummyNode == NULL)
						dummyNode = ast_create_node();

					set_dummy_data();
				}
				
				get_next_lexem();
				break;
			}
			case NON_TERMINAL: {
				/*
				 * O símbolo no topo da pilha é um não-terminal.
				 * Pela tabela de análise sintática LL(1) obtemos o próximo
				 * passo de derivação. Caso a tabela aponte para o valor 0
				 * indicamos o erro. Caso contrário, manipulamos a pilha
				 * de análise de acordo com o passo de derivação.
				 */
				pop_stack();
				nextStep = parsingTable[currentSymbol][mainLex.token];
				
				if(nextStep < 1){
					printf("%dERRO SINTATICO: \"%s\" INVALIDO [linha: %d], COLUNA %d.\n", nextStep, mainLex.word, mainLex.line, mainLex.column);

					if(errorFlag == FALSE){
						errorFlag = TRUE;
						ast_clear_stack();
						if(dummyNode)
							free(dummyNode);
						dummyNode = NULL;
					}

					while(nextStep == -1){
						if(parserStack->kind == TERMINAL || parserStack->kind == TREE_BUILDER)
							pop_stack();
						else{
							pop_stack();
							nextStep = parsingTable[currentSymbol][mainLex.token];
						}
					}

					while(parserStack->kind != NON_TERMINAL)
						pop_stack();
					pop_stack();

					if(nextStep == 0){
						push_stack(currentSymbol, NON_TERMINAL);
						
						while(parsingTable[currentSymbol][mainLex.token] == 0)
							get_next_lexem();
						break;
					}
				}

				handle_stack(nextStep);
				break;
			}
			case TREE_BUILDER:{
				/*
				 * O símbolo no topo da pilha é uma marca auxiliar para
				 * construção de árvore. Se houve um erro durante a análise
				 * a árvore não pode ser construída. Caso contrário, utilizando
				 * o nó receptáculo e uma pilha auxiliar, construímos a árvore
				 * sintática.
				 */
				pop_stack();

				if(errorFlag == FALSE)
					build_tree();

				break;
			}
		}
	}

	if(errorFlag == FALSE){	
		if(mainLex.token != ENDFILE)
			printf("ERRO SINTATICO: ainda ha simbolos para serem lidos na entrada.\n");
		
		syntaxTree = ast_pop_stack();

		if(parserFlag)
			print_ast(syntaxTree, 1);

		ast_clear_stack();

		if(dummyNode)
			free(dummyNode);
		dummyNode = NULL;
	}
	else{
		ast_clear_stack();
		clear_stack();
		deallocate_buffer();
		close_source_file();
		exit(1);
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
		push_stack(ADD_SIBLING, TREE_BUILDER);
		push_stack(DECL_LIST_, NON_TERMINAL);
		push_stack(DECLARATION, NON_TERMINAL);
		push_stack(ADD_SIBLING_STOPPER, TREE_BUILDER);
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
		push_stack(ADD_STMT_CHILD, TREE_BUILDER);
		push_stack(COMP_STMT, NON_TERMINAL);
		push_stack(ADD_PARAM_CHILD, TREE_BUILDER);
		push_stack(ADD_SIBLING, TREE_BUILDER);
		push_stack(CL_PAR, TERMINAL);
		push_stack(PARAMS, NON_TERMINAL);
		push_stack(ADD_SIBLING_STOPPER, TREE_BUILDER);
		push_stack(SET_FUN_DECL, TREE_BUILDER);
		push_stack(OP_PAR, TERMINAL);
		break;
		case 8:
		push_stack(VAR_DECL_, NON_TERMINAL);
		push_stack(ID, TERMINAL);
		push_stack(TYPE_SPEC, NON_TERMINAL);
		break;
		case 9:
		push_stack(SET_VAR_DECL, TREE_BUILDER);
		push_stack(SCOL, TERMINAL);
		break;
		case 10:
		push_stack(SCOL, TERMINAL);
		push_stack(CL_BRA, TERMINAL);
		push_stack(SET_ARRAY_DECL, TREE_BUILDER);
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
		push_stack(SET_VOID_PARAM, TREE_BUILDER);
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
		push_stack(SET_ARRAY_PARAM, TREE_BUILDER);
		push_stack(CL_BRA, TERMINAL);
		push_stack(OP_BRA, TERMINAL);
		break;
		case 22:
		push_stack(SET_VAR_PARAM, TREE_BUILDER);
		break;
		case 23:
		push_stack(ADD_SIBLING, TREE_BUILDER);
		push_stack(CL_CUR, TERMINAL);
		push_stack(STMT_LIST, NON_TERMINAL);
		push_stack(LOCAL_DECL, NON_TERMINAL);
		push_stack(ADD_SIBLING_STOPPER, TREE_BUILDER);
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
		push_stack(ADD_STMT_CHILD, TREE_BUILDER);
		push_stack(STATEMENT, NON_TERMINAL);
		push_stack(ADD_EXP_CHILD, TREE_BUILDER);
		push_stack(CL_PAR, TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		push_stack(OP_PAR, TERMINAL);
		push_stack(IF, TERMINAL);
		break;
		case 38:
		push_stack(ADD_ELSE_CHILD, TREE_BUILDER);
		push_stack(STATEMENT, NON_TERMINAL);
		push_stack(ELSE, TERMINAL);
		break;
		case 39:
		break;
		case 40:
		push_stack(ADD_STMT_CHILD, TREE_BUILDER);
		push_stack(STATEMENT, NON_TERMINAL);
		push_stack(ADD_EXP_CHILD, TREE_BUILDER);
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
		push_stack(ADD_EXP_CHILD, TREE_BUILDER);
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
		push_stack(ADD_PARAM_CHILD, TREE_BUILDER);
		push_stack(ADD_SIBLING, TREE_BUILDER);
		push_stack(CL_PAR, TERMINAL);
		push_stack(ARGS, NON_TERMINAL);
		push_stack(ADD_SIBLING_STOPPER, TREE_BUILDER);
		push_stack(SET_FUN_CALL, TREE_BUILDER);
		push_stack(OP_PAR, TERMINAL);
		break;
		case 49:
		push_stack(ADD_EXP_CHILD, TREE_BUILDER);
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
		push_stack(ADD_ARRAY_INDEX, TREE_BUILDER);
		push_stack(CL_BRA, TERMINAL);
		push_stack(EXPRESSION, NON_TERMINAL);
		push_stack(SET_ARRAY, TREE_BUILDER);
		push_stack(OP_BRA, TERMINAL);
		break;
		case 53:
		push_stack(SET_VAR, TREE_BUILDER);
		break;
		case 54:
		push_stack(BUILD_EXP, TREE_BUILDER);
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
		push_stack(BUILD_EXP, TREE_BUILDER);
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
		push_stack(BUILD_EXP, TREE_BUILDER);
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
		push_stack(ADD_PARAM_CHILD, TREE_BUILDER);
		push_stack(ADD_SIBLING, TREE_BUILDER);
		push_stack(CL_PAR, TERMINAL);
		push_stack(ARGS, NON_TERMINAL);
		push_stack(ADD_SIBLING_STOPPER, TREE_BUILDER);
		push_stack(SET_FUN_CALL, TREE_BUILDER);
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

/*------Construção da árvore sintática------*/

/*
 * Argumento: vazio
 * Retorna: vazio
 * Inicializa as variáveis auxilires de construção
 * da árvore sintática.
 */
void init_tree_stack(){
	treeNodeStack = NULL;
	dummyNode = NULL;
	syntaxTree = NULL;
}

/*
 * Argumento: nó da árvore
 * Retorna: nó nulo da árvore
 * Libera a memória de todos os elementos da árvore
 * da qual tree é raiz.
 */
ast_p ast_clear_tree(ast_p tree){
	if(tree == NULL)
		return NULL;
	
	tree->sibling = ast_clear_tree(tree->sibling);
	for(int i=0; i<AST_MAX_CHILDREN; i++)
		tree->children[i] = ast_clear_tree(tree->children[i]);
	
	free(tree);

	return NULL;
}

/*
 * Agumento: vazio
 * Retorna: vazio
 * Libera a memória de cada elemento da pilha 
 * auxiliar;
 */
void ast_clear_stack(){
	ast_stack_p aux;
	while(treeNodeStack){
		aux = treeNodeStack;
		treeNodeStack = treeNodeStack->next;
		aux->top = ast_clear_tree(aux->top);
		free(aux);
	}
}

/*
 * Argumento: vazio
 * Retorna: nó da árvore sintática
 * Inicializa um nó da árvore para ser preenchido.
 */
ast_p ast_create_node(){
	ast_p new = malloc(sizeof(ast_t));

	new->name = NULL;
	new->type = -1;
	new->token = -1;
	new->typeSpecifier = -1;
	new->value = -1;
	new->id[0] = '\0';
	new->arraySize = -1;
	new->line = -1;
	new->column = -1;
	new->sibling = NULL;
	new->visited = FALSE;
	for(int i=0; i<AST_MAX_CHILDREN; i++)
		new->children[i] = NULL;
	
	return new;
}

/* 
 * Argumento: vazio
 * Retorna: vazio
 * Utilizando o símbolo atual no topo da pilha,
 * preenche o nó dummy para ser inserido na árvore
 */
void set_dummy_data(){
	switch(mainLex.token){
		case ID:
			if(dummyNode->typeSpecifier == -1)
				dummyNode->typeSpecifier = INT;
			dummyNode->token = mainLex.token;
			strcpy(dummyNode->id, mainLex.word);
			dummyNode->line = mainLex.line;
			dummyNode->column = mainLex.column;
			break;
		case NUM:
			if(dummyNode->id[0]){
				dummyNode->arraySize = atoi(mainLex.word);
				break;
			}

			dummyNode->name = "constant";
			dummyNode->type = AST_CONST;
			dummyNode->token = mainLex.token;
			strcpy(dummyNode->id, mainLex.word);
			dummyNode->value = atoi(mainLex.word);
			dummyNode->line = mainLex.line;
			dummyNode->column = mainLex.column;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		case PLUS:
        	case MINUS:
        	case AST:
        	case DASH:
        	case LTHAN:
        	case GTHAN:
        	case DIFF:
		case LEQUAL:
        	case GEQUAL:
        	case EQUAL:
			dummyNode->name = "operand";
			dummyNode->type = AST_OPERAND;
			dummyNode->token = mainLex.token;
			strcpy(dummyNode->id, mainLex.word);
			dummyNode->line = mainLex.line;
			dummyNode->column = mainLex.column;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		case ATT:
			treeNodeStack->top->name = "assignment";
			treeNodeStack->top->type = AST_ASSIGNMENT;
			break;
        	case IF:
			dummyNode->name = "if-statement";
			dummyNode->type = AST_IF;
			dummyNode->token = mainLex.token;
			dummyNode->line = mainLex.line;
			dummyNode->column = mainLex.column;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		case INT:
			dummyNode->typeSpecifier = mainLex.token;
			break;
		case VOID:
			dummyNode->name = "void-param";
			dummyNode->type = AST_VOID;
			dummyNode->token = VOID;
			dummyNode->typeSpecifier = mainLex.token;
			break;
		case RETURN:
			dummyNode->name = "return-statement";
			dummyNode->type = AST_RETURN;
			dummyNode->token = mainLex.token;
			dummyNode->line = mainLex.line;
			dummyNode->column = mainLex.column;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		case WHILE:
			dummyNode->name = "while-statement";
			dummyNode->type = AST_WHILE;
			dummyNode->token = mainLex.token;
			dummyNode->line = mainLex.line;
			dummyNode->column = mainLex.column;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		default:
		break;
	}
}

/* 
 * Argumento: nó da árvore
 * Retorna: vazio
 * Coloca o nó no topo da pilha auxiliar
 */
void ast_push_stack(ast_p node){
	ast_stack_p aux = malloc(sizeof(ast_stack_t));

	aux->top = node;
	aux->next = treeNodeStack;
	treeNodeStack = aux;
	//ast_print_stack();
	//printf("---------------\n");
}

/*
 * Argumento: vazio
 * Retorna: nó da árvore
 * Retira o nó do topo da pilha auxiliar
 * e o retorna.
 */
ast_p ast_pop_stack(){
	ast_p node = treeNodeStack->top;
	ast_stack_p aux = treeNodeStack;
	treeNodeStack = treeNodeStack->next;
	free(aux);
	return node;
}

/*
 * Argumento: void
 * Retorna: void
 * Com base na ação no topo da pilha de derivação
 * organiza os nós da árvore sintática na pilha auxiliar
 */
void build_tree(void){
	switch(currentSymbol){
		case ADD_EXP_CHILD: {
			ast_p child = ast_pop_stack();
			ast_p dad = ast_pop_stack();
			dad->children[EXP_CHILD] = child;
			ast_push_stack(dad);
			break;
		}
		case ADD_STMT_CHILD: {
			ast_p child = ast_pop_stack();
			ast_p dad = ast_pop_stack();
			dad->children[STMT_CHILD] = child;
			ast_push_stack(dad);
			break;
		}
		case BUILD_EXP: {
			ast_p right = ast_pop_stack();
			ast_p dad = ast_pop_stack();
			ast_p left = ast_pop_stack();

			dad->children[LEFT_CHILD] = left;
			dad->children[RIGHT_CHILD] = right;
			
			ast_push_stack(dad);
			break;
		}
		case ADD_PARAM_CHILD: {
			if(treeNodeStack->top->type == AST_SIBLING_STOPPER){
				ast_p aux = ast_pop_stack();
				free(aux);
				break;
			}
			ast_p child = ast_pop_stack();
			ast_p dad = ast_pop_stack();
			dad->children[PARAM_CHILD] = child;
			ast_push_stack(dad);
			break;
		}
		case ADD_SIBLING: {
			if(treeNodeStack->top->type == AST_SIBLING_STOPPER){
				break;
			}
			ast_p rightSibling = ast_pop_stack();
			ast_p leftSibling = ast_pop_stack();
			while(leftSibling->type != AST_SIBLING_STOPPER){
				leftSibling->sibling = rightSibling;
				ast_push_stack(leftSibling);
				rightSibling = ast_pop_stack();
				leftSibling = ast_pop_stack();
			}
			free(leftSibling);
			ast_push_stack(rightSibling);
			break;
		}
		case ADD_ELSE_CHILD: {
			ast_p child = ast_pop_stack();
			ast_p dad = ast_pop_stack();
			dad->children[ELSE_CHILD] = child;
			ast_push_stack(dad);
			break;
		}
		case SET_VAR: {
			dummyNode->name = "variable";
			dummyNode->type = AST_VAR;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		}
		case SET_ARRAY: {
			dummyNode->name = "array";
			dummyNode->type = AST_ARRAY;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		}
		case SET_VAR_PARAM: {
			dummyNode->name = "var-param";
			dummyNode->type = AST_VAR_PARAM;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		}
		case SET_ARRAY_PARAM: {
			dummyNode->name = "arr-param";
			dummyNode->type = AST_ARRAY_PARAM;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		}
		case SET_VAR_DECL: {
			dummyNode->name = "var-decl";
			dummyNode->type = AST_VAR_DECL;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		}
		case SET_ARRAY_DECL: {
			dummyNode->name = "arr-decl";
			dummyNode->type = AST_ARRAY_DECL;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		}
		case SET_FUN_DECL: {
			dummyNode->name = "fun-decl";
			dummyNode->type = AST_FUN_DECL;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		}
		case SET_FUN_CALL: {
			dummyNode->name = "fun-call";
			dummyNode->type = AST_FUN;
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		}
		case SET_VOID_PARAM: {
			ast_push_stack(dummyNode);
			dummyNode = NULL;
			break;
		}
		case ADD_SIBLING_STOPPER: {
			ast_p auxNode = ast_create_node();
			auxNode->name = "sibling-stopper";
			auxNode->type = AST_SIBLING_STOPPER;
			ast_push_stack(auxNode);
			break;
		}
		case ADD_ARRAY_INDEX: {
			ast_p child = ast_pop_stack();
			ast_p dad = ast_pop_stack();
			dad->children[INDEX_CHILD] = child;
			ast_push_stack(dad);
			break;
		}
	}
}