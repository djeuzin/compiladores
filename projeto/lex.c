#include "lex.h"

// Aloca um buffer dado a quantidade de caracteres que deve ser utilizada 
void allocate_buffer(){
        mainBuffer = malloc(sizeof(buffer_t));
        if(!mainBuffer){
                printf("ERRO: Não foi possível alocar memória para a estrutura do buffer.\n");
                exit(1);
        }

        mainBuffer->buffer = malloc((BSIZE+1)*sizeof(char));
        if(!(mainBuffer->buffer)){
                printf("ERRO: Não foi possível alocar memória para o buffer.\n");
                free(mainBuffer);
                exit(1);
        }

        mainBuffer->index = -1;
        mainBuffer->size = BSIZE;
        mainBuffer->buffer[0] = '\0';
        mainBuffer->line = 1;
        mainBuffer->used = 1;
}

void deallocate_buffer(){
        free(mainBuffer->buffer);
        free(mainBuffer);
        mainBuffer = NULL;
}

// Carrega o buffer se estiver vazio (próximo caractere é \0).
// Se o caractere foi consumido (b->used) incrementa o índice do buffer para apontar para o próximo caractere.
// Rertorna o caractere do índice.
char get_next_char(){
    if(mainBuffer->used){
        if(mainBuffer->buffer[mainBuffer->index + 1] == '\0'){
            if(fgets(mainBuffer->buffer, mainBuffer->size + 1, sourceFile))
                mainBuffer->index = -1;
            else
                return EOF;
        }

        (mainBuffer->index)++;

        if(mainBuffer->buffer[mainBuffer->index] == '\n')
            (mainBuffer->line)++;
    }

    return mainBuffer->buffer[mainBuffer->index];
}

// Para cada caractere, percorre a tabela de transição.
// Se chegar em um estado de aceitação, retorna o lexema.
// Caso contrário continua adicionando caracteres à palavra do lexema.
lex_t get_next_lexem(){
        lex_t newLex;
        newLex.last = 0;
        int lexIndex = 0;
        char c = get_next_char();
        mainBuffer->used = 0;
        int state = 0, cTableIndex;

        while(c != EOF){
                if(state == 0)
                        lexIndex = 0;
                cTableIndex = get_delta_index(c);
                mainBuffer->used = used_table[state][cTableIndex];

                if(mainBuffer->used && state != 6 && state != 7){
                        if(lexIndex == 0){
                                newLex.line = mainBuffer->line;
                                newLex.token = cTableIndex;
                        }
                        newLex.word[lexIndex] = c;
                        lexIndex++; 
                }

                state = delta_table[state][cTableIndex];

                if(accepting_table[state]){
                        newLex.word[lexIndex] = '\0';
                        newLex.token = assert_token(newLex, lexIndex);
                        if(newLex.token == ERR)
                                printf("ERRO LEXICO: \"%s\" INVALIDO [linha: %d], COLUNA %d.\n", newLex.word, newLex.line, mainBuffer->index+1);
                        if(debugFlag)
                                print_lexem(newLex);
                        return newLex;
                }
                c = get_next_char();
        }

        // Se houver algum caractere para ser classificado ainda
        // O classificamos e retornamos.
        if(lexIndex){
                newLex.word[lexIndex] = '\0';
                newLex.token = assert_token(newLex, lexIndex);
                if(debugFlag)
                        print_lexem(newLex);
        }
        newLex.last = 1;
        return newLex;
}

// Abre o arquivo e seta a flag de debug
void open_source_file(int argc, char* argv[]){
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
                        debugFlag = 1;
                }
                else{
                        printf("ERRO: Flag inválida.\n");
                        exit(1);
                }
        }

        sourceFile= fopen(argv[1], "r");
        if(!sourceFile){
                printf("ERRO: Não foi possível abrir o arquivo.\n");
                exit(1);
        }
}

void close_source_file(){
        fclose(sourceFile);
}

// Printa o lexema
void print_lexem(lex_t lex){
        switch(lex.token){
                case ELSE:
                printf("<ELSE> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case IF:
                printf("<IF> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case INT:
                printf("<INT> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case RETURN:
                printf("<RETURN> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case VOID:
                printf("<VOID> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case WHILE:
                printf("<WHILE> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case ID:
                printf("<ID> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case NUM:
                printf("<NUM> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case PLUS:
                printf("<PLUS> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case MINUS:
                printf("<MINUS> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case AST:
                printf("<AST> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case DASH:
                printf("<DASH> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break; 
                case LTHAN:
                printf("<LTHAN> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case LEQUAL:
                printf("<LEQUAL> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case GTHAN:
                printf("<GTHAN> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case GEQUAL:
                printf("<GEQUAL> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case EQUAL:
                printf("<EQUAL> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case DIFF:
                printf("<DIFF> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case ATT:
                printf("<ATT> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case SCOL:
                printf("<SCOL> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case COMMA:
                printf("<COMMA> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case OP_PAR:
                printf("<OP_PAR> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case CL_PAR:
                printf("<CL_PAR> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case OP_BRA:
                printf("<OP_BRA> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case CL_BRA:
                printf("<CL_BRA> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case OP_CUR:
                printf("<OP_CUR> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                case CL_CUR:
                printf("<CL_CUR> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
                default:
                printf("<ERR> \"%s\" [linha: %d]\n", lex.word, lex.line);
                break;
        }
}     

// Verifica se o token da palavra está correto e retorna
// Se for um identificador verificamos se é uma palavra chave
token_t assert_token(lex_t lex, int size){
        if(lex.token == ID){
                return check_keyword(lex.word, size);
        }

        if(lex.word[0] == '!' && size == 1)
                return ERR;

        if(size == 1 || lex.token == NUM)
                return lex.token;

        if(size == 2){
                switch(lex.word[0]){
                        case '<':
                        return LEQUAL;
                        case '>':
                        return GEQUAL;
                        case '!':
                        return DIFF;
                        case '=':
                        return EQUAL;
                }
        }

        return lex.token;
}

// Checa se o identificador é uma palavra chave por meio de hashing
token_t check_keyword(char word[], int size){
    // Se a palavra for menor que a menor palavra chave ou maior que a maior palavra chave
    // apenas retornamos o identificador.
    if(size < MIN_KEYWORD_LENGTH || size > MAX_KEYWORD_LENGTH)
        return ID;

    // Caso contrário calculamos o hash da palavra recebida
    int m = 1e9+9;
    int p = 31;
    long int p_pow = 1;
    long int hash = 0;
    for(int i = 0; i<size; i++){
        hash = (hash + (word[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    // Checamos se casa com os hashs conhecidos das palavras chave
    switch(hash){
        case 167591:
        return ELSE;
        case 195:
        return IF;
        case 19663:
        return INT;
        case 418076496:
        return RETURN;
        case 128300:
        return VOID;
        case 4984017:
        return WHILE;
        default:
        return ID;
    }
}

// Dado um caractere retorna o índice correspondente na tabela de transição
int get_delta_index(char c){
        switch(c){
                case '+':
                return 2;
                case '-':
                return 3;
                case '*':
                return 4;
                case '/':
                return 5;
                case '<':
                return 6;
                case '>':
                return 7;
                case '=':
                return 8;
                case '!':
                return 9;
                case ';':
                return 10;
                case ',':
                return 11;
                case '(':
                return 12;
                case ')':
                return 13;
                case '[':
                return 14;
                case ']':
                return 15;
                case '{':
                return 16;
                case '}':
                return 17;
                case ' ':
                case '\n':
                return 19;
                default:
                if((c > 64 && c <91) || (c > 96 && c < 123)) // letter
                        return 0;
                if(c > 47 && c < 58) // digit
                        return 1;
        }
        return 18;
}