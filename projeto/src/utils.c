/*****************************/
/*  Cross: C- Compiler       */
/*  utils.c                  */
/*  Contém as implementações */
/*  de funções utilitárias   */
/*****************************/

#include "utils.h"

/*
 * Argumento: string
 * Retorna: vazio
 * Exibe a string passada na cor azul.
 */
void print_b(char* str) { 
        printf("\033[0;34m"); 
        printf("%s", str);
        printf("\033[0m");
}

/*
 * Argumento: string
 * Retorna: vazio
 * Exibe a string passada na cor vermelha.
 */
void print_r(char* str) { 
        printf("\033[0;31m");
        printf("%s", str);
        printf("\033[0m");
}

/*
 * Argumento: vazio
 * Retorna: vazio
 * Configura para que os próximos caracteres exibidos
 * sejam exibidos na cor vermelha.
 */
void red_text() { printf("\033[0;31m"); }

/*
 * Argumento: vazio
 * Retorna: vazio
 * Configura para que os próximos caracteres exibidos
 * sejam exibidos na cor padrão.
 */
void default_color_text() { printf("\033[0m"); }

/*
 * Argumento: vazio
 * Retorna: vazio
 * Exibe as opções do programa.
 */
void display_help(){
        printf("Cross C- compiler\nOpcoes:\n");
        
        print_b("--help");
        printf("\t\tExibe opcoes.\n");

        print_b("-l, -L");
        printf("\t\tExibe os lexemas classificados.\n");

        print_b("-p, -P");
        printf("\t\tExibe a arvore abstrata gerada pelo parser.\n");

        print_b("-o, -O");
        printf("\t\tRealiza apenas a analise lexica.\n");

        exit(0);
}

/*
 * Argumento: contador de argumentos e array de argumentos
 * Retorna: vazio
 * Abre o arquivo fonte e seta as flags solicitadas.
 * Em caso de erro, exibe uma mensagem apropriada.
 */
void open_source_file(int argc, char* argv[]){
        if(argc < 2){
                red_text();
                fprintf(stderr, "ERRO: Entre com o caminho do arquivo fonte.\n"); 
                default_color_text();
                exit(1);
        }

        int fileOpened = FALSE;
        for(int i=1; i<argc; i++){
                if(argv[i][0] == '-'){
                        if(                             \
                                argv[i][1] == '-' &&    \
                                argv[i][2] == 'h' &&    \
                                argv[i][3] == 'e' &&    \
                                argv[i][4] == 'l' &&    \
                                argv[i][5] == 'p' &&    \
                                argv[i][6] == '\0'      \
                        ){
                                if(fileOpened)
                                        close_source_file();
                                display_help();
                        }

                        if(argv[i][2] != '\0'){
                                red_text();
                                fprintf(stderr, "ERRO: Comando invalido.\n");
                                default_color_text();
                                if(fileOpened)
                                        close_source_file();
                                exit(1);
                        }

                        switch(argv[i][1]){
                                case 'l':
                                case 'L':
                                lexFlag = TRUE;
                                break;
                                case 'p':
                                case 'P':
                                parserFlag = TRUE;
                                break;
                                case 'o':
                                case 'O':
                                lexOnly = TRUE;
                                break;
                                case 's':
                                case 'S':
                                semanticFlag = TRUE;
                                break;
                                default:
                                red_text();
                                fprintf(stderr, "ERRO: Comando %s invalido.\n", argv[i]);
                                default_color_text();
                                if(fileOpened)
                                        close_source_file();
                                exit(1);
                        }
                }
                else{
                        if(fileOpened){
                                red_text();
                                fprintf(stderr, "ERRO: Comando invalido.\n");
                                default_color_text();
                                close_source_file();
                                exit(1);
                        }

                        sourceFile = fopen(argv[i], "r");
                        if(!sourceFile){
                                red_text();
                                fprintf(stderr, "ERRO: Nao foi possivel abrir o arquivo.\n");
                                default_color_text();
                                exit(1);
                        }
                        fileOpened = TRUE;
                }
        }
}

/*
 * Argumento: vazio
 * Retorna: vazio
 * Fecha o arquivo fonte.
 */
void close_source_file(){
        fclose(sourceFile);
}

/*
 * Argumento: vazio
 * Retorna: vazio
 * Função auxiliar do lexer para exibir os lexemas
 * classificados quando a flag for acionada.
 */
void print_lexem(){
        switch(mainLex.token){
                case ELSE:
                printf("<ELSE> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case IF:
                printf("<IF> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case INT:
                printf("<INT> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case RETURN:
                printf("<RETURN> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case VOID:
                printf("<VOID> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case WHILE:
                printf("<WHILE> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case ID:
                printf("<ID> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case NUM:
                printf("<NUM> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case PLUS:
                printf("<PLUS> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case MINUS:
                printf("<MINUS> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case AST:
                printf("<AST> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case DASH:
                printf("<DASH> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case LTHAN:
                printf("<LTHAN> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case LEQUAL:
                printf("<LEQUAL> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case GTHAN:
                printf("<GTHAN> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case GEQUAL:
                printf("<GEQUAL> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case EQUAL:
                printf("<EQUAL> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case DIFF:
                printf("<DIFF> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case ATT:
                printf("<ATT> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case SCOL:
                printf("<SCOL> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case COMMA:
                printf("<COMMA> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case OP_PAR:
                printf("<OP_PAR> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case CL_PAR:
                printf("<CL_PAR> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case OP_BRA:
                printf("<OP_BRA> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case CL_BRA:
                printf("<CL_BRA> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case OP_CUR:
                printf("<OP_CUR> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case CL_CUR:
                printf("<CL_CUR> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                default:
                printf("<ERR> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
        }
}

/*
 * Argumento: nó da árvore
 * Retorna: verdadeiro ou falso
 * Dado um nó retorna veradeiro se ele tiver filhos
 * ou falso caso não tenha nenhum filho.
 */
int hasChildren(ast_p node){
	for(int i=0; i<AST_MAX_CHILDREN; i++)
		if(node->children[i])
			return TRUE;
	return FALSE;
}

/*
 * Argumento: raiz da árvore e profundidade
 * Retorna:vazio
 * Exibe os nós da árvore sintáica construída
 * utilizando a profundidade para identar durante a exibição
 */
void print_ast(ast_p root, int depth){
	if(root == NULL)
		return;

	for(int i=1; i<depth; i++)
		printf("    ");
	
	print_b("<");
	printf("%s", root->name);

	if(root->id[0] != '\0')
		printf(" (%s)", root->id);
	
	print_b(">");

	if(hasChildren(root))
		print_r("(\n");
	
	for(int i=0; i<AST_MAX_CHILDREN; i++){
		print_ast(root->children[i], depth+1);
	}
	
	if(hasChildren(root)){
		for(int i=1; i<depth; i++)
			printf("    ");
		print_r(")");
	}
	
	if(root->sibling)
		print_b(",");
	
	printf("\n");

	print_ast(root->sibling, depth);
}

/*
 * Argumento: vazio
 * Retorna: vazio
 * Imprime a tabela de símbolos construída
 */
void print_symbol_table(){
        printf("# TABELA DE SIMBOLOS\n");
        printf("Nome_ID;Escopo;Tipo_ID;Tipo_dado;Linhas\n");

        for(int i = 0; i<SYMBOL_TABLE_SIZE; i++);
}