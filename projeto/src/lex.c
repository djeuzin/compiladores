/**************************/
/*  Cross: C- Compiler    */
/*  lex.c                 */
/*  Implementações das    */
/*  funções do lexer.     */
/**************************/

#include "lex.h"

/* Variáveis globais do lexer */
// Buffer do arquivo fonte
buffer_t mainBuffer;

// Lexema que será enviado ao parser
lex_t mainLex;

// Definição dos arrays que armazenam as palavras chaves e os respectivos hashs
char keywords[NUM_KEYWORDS][30] = {"else", "if", "int", "return", "void", "while"};
token_t keywordsTokens[NUM_KEYWORDS] = {ELSE, IF, INT, RETURN, VOID, WHILE};
unsigned int keywordsHash[NUM_KEYWORDS] = {0};

/*
 * Argumentos: vazio
 * Rertona: vazio
 * Aloca um vetor de caracteres na estrutura mainBuffer
 * onde será armazenado o fluxo de caracteres do arquivo fonte.
 */
void allocate_buffer(){
        mainBuffer.buffer = malloc((BUFFER_SIZE+1)*sizeof(char));
        if(!(mainBuffer.buffer)){
                printf("ERRO: Não foi possível alocar memória para o buffer.\n");
                free(mainBuffer.buffer);
                exit(1);
        }

        mainBuffer.index = -1;
        mainBuffer.buffer[0] = '\0';
        mainBuffer.line = 1;
        mainBuffer.column = 0;
        mainBuffer.used = 1;
}

/*
 * Argumentos: vazio
 * Retorna: vazio
 * Libera a memória alocada para o buffer.
 */
void deallocate_buffer(){
        free(mainBuffer.buffer);
        mainBuffer.buffer = NULL;
}

/*
 * Argumentos: vazio
 * Retorna: caractere
 * Checa se o buffer está vazio e se o caractere foi consumido.
 * Caso o buffer esteja vazio, preenche ele ou retorna EOF.
 * Caso o caractere tenha sido consumido, aumenta o índice do buffer.
 * Retorna o caractere apontado pelo índice.
 */
char get_next_char(){
    if(mainBuffer.used){
        if(mainBuffer.buffer[mainBuffer.index + 1] == '\0'){
            if(fgets(mainBuffer.buffer, BUFFER_SIZE + 1, sourceFile))
                mainBuffer.index = -1;
            else
                return EOF;
        }

        (mainBuffer.index)++;
        (mainBuffer.column)++;

        if(mainBuffer.buffer[mainBuffer.index] == '\n'){
            (mainBuffer.line)++;
            (mainBuffer.column) = 0;
        }
    }

    return mainBuffer.buffer[mainBuffer.index];
}

/*
 * Argumentos: vazio
 * Retorna: vazio
 * A partir de cada caractere do fluxo do arquivo fonte
 * percorre o DFA do analisador léxico e classifica os lexemas
 * na estrutura mainLex.
 */
void get_next_lexem(){
        char c = get_next_char();
        mainBuffer.used = 0;
        
        int state = 0;
        int cTableIndex;

        // Se c == EOF, chamadas subsequentes de get_next_lexem() manterão o token do lexema como de
        // fim de arquivo
        mainLex.token = ENDFILE;
        mainLex.size = 0;

        while(c != EOF){
                if(state == 0)
                        mainLex.size = 0;

                cTableIndex = get_delta_index(c);
                mainBuffer.used = usedTable[state][cTableIndex];
                state = deltaTable[state][cTableIndex];
        
                // Se o caractere foi utilizado e o DFA não está em um estado que deve
                // ser ignorado, adicionamos o caractere à palavra do lexema.
                if(mainBuffer.used){
                        if(!is_ignored_state(state)){
                                if(mainLex.size == 0){
                                        mainLex.line = mainBuffer.line;
                                        mainLex.column = mainBuffer.column;
                                        mainLex.token = cTableIndex;
                                }
                                if(state == 2)
                                        mainLex.token = ERR;
                                mainLex.word[mainLex.size] = c;
                                mainLex.size++; 
                        }
                        else{
                                mainLex.token = ENDFILE;
                                mainLex.size = 0;
                        }
                }

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
}

/*
 * Argumento: vazio
 * Retorna: token_t (int)
 * Assegura que o token do lexema está correto
 * checando se é palavra chave ou se é um token de erro.
 * Retorna o token correto.
 */
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

/*
 * Argumentos: vazio 
 * Retorna: token_t (int)
 * Checa se o token do lexema é uma palavra chave
 * por meio de hashing.
 */
token_t check_keyword(){
    if(mainLex.size < MIN_KEYWORD_LENGTH || mainLex.size > MAX_KEYWORD_LENGTH)
        return ID;

    // Gera os hashs das palavras-chave na primeira ativação da função
    if(!keywordsHash[0])
        generate_keywords_hash();

    unsigned int hash = hash_function(mainLex.word);
    
    if(hash == ID)
        return ID;

    // A ideia original era utilizar um switch case com os hashs das palavras-chave já calculado
    // e inserido manualmente no código. Utilizar o array de palavras-chave e dos hashes torna
    // o código bem mais flexível, porém há a necessidade de um loop com complexidade O(NUM_KEYWORDS).
    for(int i=0; i<NUM_KEYWORDS; i++)
        if(hash == keywordsHash[i])
            return keywordsTokens[i];

    return ID;
}

/*
 * Argumentos: vazio
 * Retorna: vazio
 * Prepara o lexema para o parser e indica
 * se é um token de erro. 
 */
void wrap_lexem(){
        mainLex.word[mainLex.size] = '\0';
        mainLex.token = assert_token();
        if(mainLex.token == ERR)
                printf("ERRO LEXICO: \"%s\" INVALIDO [linha: %d], COLUNA %d.\n", mainLex.word, mainLex.line, mainLex.column);
        if(lexFlag)
                print_lexem(mainLex);
}

/*
 * Argumento: caractere
 * Retorna: inteiro
 * Retorna o índice correspondente do caractere
 * na tabela de transição do DFA. O índice também
 * corresponde ao token.
 */
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
                case '\t':
                case '\r':
                return 19;
                default:
                if((c > 64 && c <91) || (c > 96 && c < 123)) // letter
                        return 0;
                if(c > 47 && c < 58) // digit
                        return 1;
        }
        return 18;
}

/*
 * Argumento: string
 * Retorna: chave hash
 * Calcula o hash da palavra lida pelo lexer.
 * Se houver uma letra maiúscula ou digito 
 * na palavra, retorna o token ID.
 */
int hash_function(char *word){
    unsigned int hash = 0;
    int i = 0, c = word[i];

    // Como o range é fixo no tamanho da menor e da maior palavra chave,
    // essa função de hash funciona atribuindo peso 2*(i+1) para cada caractere
    // na posição i.
    while(c){
        if(c < 96) // c é letra maiúscula ou digito => word não é palavra-chave
            return ID;
        hash += c*(i+1)*2;
        i++;
        c = word[i];
    }

    return hash;
}

/*
 * Argumento: vazio
 * Retorna: vazio
 * Gera os hashs das palavras-chave e armazena-os
 * no vetor keywordsHash
 */
void generate_keywords_hash(){
    for(int i=0; i<NUM_KEYWORDS; i++)
        keywordsHash[i] = hash_function(keywords[i]);
}
