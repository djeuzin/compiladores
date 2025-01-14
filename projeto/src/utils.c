/*****************************/
/*  Cross: C- Compiler       */
/*  utils.c                  */
/*  Contém as implementações */
/*  de funções utilitárias   */
/*****************************/

#include "utils.h"

void blue_text() { printf("\033[0;34m"); }
void default_color_text() { printf("\033[0m"); }
void red_text() { printf("\033[0;31m"); }

void display_help(){
        printf("Cross C- compiler\nOpcoes:\n");
        
        blue_text();
        printf("--help");
        default_color_text();
        printf("\t\tExibe opcoes.\n");

        blue_text();
        printf("-l, -L");
        default_color_text();
        printf("\t\tExibe os lexemas classificados.\n");

        blue_text();
        printf("-p, -P");
        default_color_text();
        printf("\t\tExibe a arvore abstrata gerada pelo parser.\n");

        blue_text();
        printf("-o, -O");
        default_color_text();
        printf("\t\tRealiza apenas a analise lexica.\n");

        exit(0);
}

// Abre o arquivo e seta a flag de debug
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

// Fecha o arquivo fonte
void close_source_file(){
        fclose(sourceFile);
}

// Printa o lexema
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