/**************************/
/*  Cross: C- Compiler    */
/*  lex.c                 */
/*  Implementações das    */
/*  funções do lexer.     */
/**************************/

#include "lex.h"

// Aloca um buffer para ler os caracteres do arquivo fonte
void allocate_buffer(){
        mainBuffer = malloc(sizeof(buffer_t));
        if(!mainBuffer){
                printf("ERRO: Não foi possível alocar memória para a estrutura do buffer.\n");
                exit(1);
        }

        mainBuffer->buffer = malloc((BUFFER_SIZE+1)*sizeof(char));
        if(!(mainBuffer->buffer)){
                printf("ERRO: Não foi possível alocar memória para o buffer.\n");
                free(mainBuffer);
                exit(1);
        }

        mainBuffer->index = -1;
        mainBuffer->size = BUFFER_SIZE;
        mainBuffer->buffer[0] = '\0';
        mainBuffer->line = 1;
        mainBuffer->used = 1;
}

// Libera a memória utilizada pelo buffer
void deallocate_buffer(){
        free(mainBuffer->buffer);
        free(mainBuffer);
        mainBuffer = NULL;
}

// Carrega o buffer se estiver vazio (próximo caractare é \0)
// Se o caractere foi utilizado incrementa o índice
// Retorna o caractere do índice
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
void get_next_lexem(){
        char c = get_next_char();
        mainBuffer->used = 0;
        
        int state = 0;
        int cTableIndex;

        mainLex.token = OMTM;
        mainLex.size = 0;

        while(c != EOF){
                if(state == 0)
                        mainLex.size = 0;
                cTableIndex = get_delta_index(c);
                mainBuffer->used = usedTable[state][cTableIndex];

                // Se o caractere foi utilizado e não estamos em um comentário
                // adicionamos o caractere à palavra do lexema.
                if(mainBuffer->used && state != 6 && state != 7){
                        if(mainLex.size == 0){
                                mainLex.line = mainBuffer->line;
                                mainLex.token = cTableIndex;
                        }
                        mainLex.word[mainLex.size] = c;
                        mainLex.size++; 
                }

                state = deltaTable[state][cTableIndex];

                if(acceptingTable[state]){
                        wrap_lexem();
                        return;
                }
                c = get_next_char();
        }

        // Se EOF for retornado e houverem caracteres no 
        // lexema, o classificamos e retornamos.
        if(mainLex.size)
                wrap_lexem();
        return;
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

// Fecha o arquivo fonte
void close_source_file(){
        fclose(sourceFile);
}

// Verifica se o token da palavra está correto e retorna
// Se for um identificador verificamos se é uma palavra chave
token_t assert_token(){
        if(mainLex.token == ID)
                return check_keyword();

        if(mainLex.size == 1 && mainLex.word[0] == '!')
                return ERR;

        if(mainLex.size == 2){
                switch(mainLex.word[0]){
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

        return mainLex.token;
}

// Checa se o identificador é uma palavra chave por meio de hashing
token_t check_keyword(){
    if(mainLex.size < MIN_KEYWORD_LENGTH || mainLex.size > MAX_KEYWORD_LENGTH)
        return ID;

    // Como o range é fixo no tamanho da menor e da maior palavra chave,
    // essa função de hash funciona atribuindo peso 2*(i+1) para cada caractere
    // na posição i. Removendo as letras maiúsculas e digitos obtemos uma função
    // que checa se a palavra é palavra-chave em O(n) para n = tamanho da palavra
    unsigned int hash = 0;
    int i = 0, c = mainLex.word[i];

    while(c){
        if(c < 96) // c é letra maiúscula ou digito => word não é palavra-chave
            return ID;
        hash += c*(i+1)*2;
        i++;
        c = mainLex.word[i];
    }
    
    switch(hash){
        case 2132:
        return ELSE;
        case 618:
        return IF;
        case 1346:
        return INT;
        case 4724:
        return RETURN;
        case 2110:
        return VOID;
        case 3158:
        return WHILE;
        default:
        return ID;
    }
}

// Embrulha o lexema para a utilização do parser
void wrap_lexem(){
        mainLex.word[mainLex.size] = '\0';
        mainLex.token = assert_token();
        if(mainLex.token == ERR)
                printf("ERRO LEXICO: \"%s\" INVALIDO [linha: %d], COLUNA %d.\n", mainLex.word, mainLex.line, mainBuffer->index+1);
        if(debugFlag)
                print_lexem(mainLex);
}

// Dado um caractere retorna o índice correspondente na tabela de transição.
// Além de ser o índicde na tabela de transição, o valor retornado também corresponde 
// a definição enum de cada marca. Assim, ao obter o índice na tablea de transição para 
// percorrer o DFA, o aproveitamos para classificar o lexema durante a leitura.
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