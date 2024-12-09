#include "lex.h"

// Aloca um buffer dado a quantidade de caracteres que deve ser utilizada 
buffer_p allocate_buffer(){
        buffer_p newBuffer;

        newBuffer = malloc(sizeof(buffer_t));
        if(!newBuffer){
                printf("ERRO: Não foi possível alocar memória para a estrutura do buffer.\n");
                exit(1);
        }

        newBuffer->index = -1;
        newBuffer->buffer[0] = '\0';
        newBuffer->line = 0;
        newBuffer->used = 1;

        return newBuffer;
}

buffer_p deallocate_buffer(buffer_p b){
        free(b->buffer);
        free(b);
        return NULL;
}

// Carrega o buffer se estiver vazio (próximo caractere é \0).
// Se o caractere foi consumido (b->used) incrementa o índice do buffer para apontar para o próximo caractere.
// Rertorna o caractere do índice.
char get_next_char(FILE* arq, buffer_p b){
        if(b->used){
                if(b->buffer[b->index + 1] == '\0'){
                        if(fgets(b->buffer, b->size+1, arq))
                                b->index = -1;
                        else
                                return EOF;
                }

                (b->index)++;

                if(b->buffer[b->index] == '\n')
                        (b->line)++;
        }

        return b->buffer[b->index];
}

lex_t get_next_lexem(FILE* arq, buffer_p b, int debugFlag){
        lex_t newLex;
        int lexIndex = 0;
        char c = get_next_char(arq, b);
        int state = 0, tableIndex;

        while(c != EOF){
                tableIndex = get_delta_index(c);

                if(accepting_table[state]){
                        newLex.lexem[lexIndex] = '\0';
                        newLex.token = tokenfy_lex(newLex.lexem, lexIndex);
                        if(state == 9){
                                printf("ERRO LEXICO: \"%s\" INVALIDO [linha: %d], COLUNA %d.", newLex.lexem, newLex.line, b->index);
                        }
                        else if(debugFlag)
                                print_lexem(newLex)
                        return newLex;
                }

                newLex.lexem[lexIndex] = c;
                lexIndex++;

                state = delta_table[state][tableIndex];
                b->used = consuming_table[state][tableIndex];

                c = get_next_char(arq, b);
        }

        newLex.token = -1;
        return newLex;
}

// Abre o arquivo e seta a flag de debug
FILE* open_source_file(int argc, char* argv[], int* debugFlag){
        if(argc < 2){
                printf("ERRO: Entre com o caminho do arquivo fonte.\n"); 
                exit(1);
        }

        if(argc > 3){
                printf("ERRO: Número de argumentos excedido.\n");
                exit(1);
        }

        if(argc == 3){
                if(argv[2][0] == '-' &&                         \
                (argv[2][1] == 'l' || argv[2][1] == 'L') &&     \
                argv[2][2] == '\0'){
                        *debugFlag = 1;
                }
                else{
                        printf("ERRO: Flag inválida.\n");
                        exit(1);
                }
        }

        FILE* arq = fopen(argv[1], "r");
        if(!arq){
                printf("ERRO: Não foi possível abrir o arquivo.\n");
                exit(1);
        }

        return arq;
}

// Printa o lexema
void print_lexem(lex_t lex){
        switch(lex.token){
                case ELSE:
                printf("<ELSE> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case IF:
                printf("<IF> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case INT:
                printf("<INT> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case RETURN:
                printf("<RETURN> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case VOID:
                printf("<VOID> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case WHILE:
                printf("<WHILE> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case ID:
                printf("<ID> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case NUM:
                printf("<NUM> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case PLUS:
                printf("<PLUS> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case MINUS:
                printf("<MINUS> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case AST:
                printf("<AST> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case DASH:
                printf("<DASH> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break; 
                case LTHAN:
                printf("<LTHAN> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case LEQUAL:
                printf("<LEQUAL> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case GTHAN:
                printf("<GTHAN> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case GEQUAL:
                printf("<GEQUAL> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case EQUAL:
                printf("<EQUAL> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case DIFF:
                printf("<DIFF> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case ATT:
                printf("<ATT> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case SCOL:
                printf("<SCOL> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case COMMA:
                printf("<COMMA> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case OP_PAR:
                printf("<OP_PAR> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case CL_PAR:
                printf("<CL_PAR> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case OP_BRA:
                printf("<OP_BRA> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case CL_BRA:
                printf("<CL_BRA> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case OP_CUR:
                printf("<OP_CUR> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                case CL_CUR:
                printf("<CL_CUR> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
                default:
                printf("<ERR> \"%s\" [linha: %d]", lex.lexem, lex.line);
                break;
        }
}     