#include "funcs.h"

/*
    Se o caractere não foi utilizado apenas retornamos o mesmo caractere novamente.

    Caso ele tenha sido utilizado, vamos primeiro ver se o buffer precisa ser carregado.
    O buffer precisará ser carregado se o índice de caractere atual (b->next_index - 1) apontar para o caractere \0
    Se o buffer for carregado indicamos que o próximo caractere a ser lido é o do índice 0 no buffer,
    se o buffer não for carregado, chegamos ao fim do arquivo e portanto retornamos EOF.
    Incrementamos o índice do próximo caractere pois agora retornaremos o atual.
    Se o atual for \n incrementamos o valor da próxima linha.

    Assim, sempre que um caractere for "consumido" retornaremos o próximo, caso contrário retornamos o mesmo caractere.
*/
char get_next_char(buffer_p b, FILE* arq){
    if(b->used){
        if(b->buffer[b->index] == '\0'){
            if(fgets(b->buffer, b->size + 1, arq))
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

buffer_p allocate_buffer(int size){
    buffer_p b = (buffer_p) malloc(sizeof(buffer_t));
    if(!b)
        return NULL;

    b->buffer = malloc((size+1)*sizeof(char));
    if(!b->buffer){
        free(b);
        return NULL;
    }
    b->size = size;
    b->used = USED;
    b->index = 0;
    b->buffer[0] = '\0';
    b->line = 1;

    return b;
}

buffer_p deallocate_buffer(buffer_p b){
    free(b->buffer);
    free(b);
    return NULL;
}

void get_lexems(buffer_p b, FILE* arq, lex_p lexem){
    char c = '\0';
    int i = 0;
    // 40 < c < 133 -> [A-Z]
    // 60 < c < 173 -> [a-z]
    while(c != EOF){
        c = get_next_char(b, arq);
        if((64 < c && c < 91) || (96 < c && c < 123)){
            if(i > 64) // wordBuffer overflow
                return;
            lexem->word[i] = c;
            b->used = USED;
            i++;
        }
        else{
            if(i > 0){ // Theres a word to be categorized
                lexem->word[i] = '\0';
                lexem->token = tokenfy_word(lexem->word);
                lexem->line = b->line;
                i = 0;
                print_lex(lexem);
            }

            b->used = USED;
        }
    }
}

void print_lex(lex_p lexem){
    switch(lexem->token){
        case 1:
            printf("Linha: %d, Lexema: %s, Token: ID\n", lexem->line, lexem->word);
        break;
        case 2:
            printf("Linha: %d, Lexema: %s, Token: AUTO\n", lexem->line, lexem->word);
        break;
        case 3:
            printf("Linha: %d, Lexema: %s, Token: ELSE\n", lexem->line, lexem->word);
        break;
        case 4:
            printf("Linha: %d, Lexema: %s, Token: LONG\n", lexem->line, lexem->word);
        break;
        case 5:   
            printf("Linha: %d, Lexema: %s, Token: SWITCH\n", lexem->line, lexem->word);
        break;
        case 6:   
            printf("Linha: %d, Lexema: %s, Token: BREAK\n", lexem->line, lexem->word);
        break;
        case 7:   
            printf("Linha: %d, Lexema: %s, Token: ENUM\n", lexem->line, lexem->word);
        break;
        case 8:   
            printf("Linha: %d, Lexema: %s, Token: REGISTER\n", lexem->line, lexem->word);
        break;
        case 9:   
            printf("Linha: %d, Lexema: %s, Token: TYPEDEF\n", lexem->line, lexem->word);
        break;
        case 10:   
            printf("Linha: %d, Lexema: %s, Token: CASE\n", lexem->line, lexem->word);
        break;
        case 11:   
            printf("Linha: %d, Lexema: %s, Token: EXTERN\n", lexem->line, lexem->word);
        break;
        case 12:   
            printf("Linha: %d, Lexema: %s, Token: RETURN\n", lexem->line, lexem->word);
        break;
        case 13:   
            printf("Linha: %d, Lexema: %s, Token: UNION\n", lexem->line, lexem->word);
        break;
        case 14:   
            printf("Linha: %d, Lexema: %s, Token: CHAR\n", lexem->line, lexem->word);
        break;
        case 15:   
            printf("Linha: %d, Lexema: %s, Token: FLOAT\n", lexem->line, lexem->word);
        break;
        case 16:   
            printf("Linha: %d, Lexema: %s, Token: SHORT\n", lexem->line, lexem->word);
        break;
        case 17:   
            printf("Linha: %d, Lexema: %s, Token: UNSIGNED\n", lexem->line, lexem->word);
        break;
        case 18:   
            printf("Linha: %d, Lexema: %s, Token: CONST\n", lexem->line, lexem->word);;
        break;
        case 19:   
            printf("Linha: %d, Lexema: %s, Token: FOR\n", lexem->line, lexem->word);
        break;
        case 20:   
            printf("Linha: %d, Lexema: %s, Token: SIGNED\n", lexem->line, lexem->word);
        break;
        case 21:   
            printf("Linha: %d, Lexema: %s, Token: VOID\n", lexem->line, lexem->word);
        break;
        case 22:   
            printf("Linha: %d, Lexema: %s, Token: CONTINUE\n", lexem->line, lexem->word);
        break;
        case 23:   
            printf("Linha: %d, Lexema: %s, Token: GOTO\n", lexem->line, lexem->word);
        break;
        case 24:   
            printf("Linha: %d, Lexema: %s, Token: SIZEOF\n", lexem->line, lexem->word);
        break;
        case 25:   
            printf("Linha: %d, Lexema: %s, Token: VOLATILE\n", lexem->line, lexem->word);
        break;
        case 26:   
            printf("Linha: %d, Lexema: %s, Token: DEFAULT\n", lexem->line, lexem->word);
        break;
        case 27:   
            printf("Linha: %d, Lexema: %s, Token: IF\n", lexem->line, lexem->word);
        break;
        case 28:   
            printf("Linha: %d, Lexema: %s, Token: STATIC\n", lexem->line, lexem->word);
        break;
        case 29:   
            printf("Linha: %d, Lexema: %s, Token: WHILE\n", lexem->line, lexem->word);
        break;
        case 30:   
            printf("Linha: %d, Lexema: %s, Token: DO\n", lexem->line, lexem->word);
        break;
        case 31:   
            printf("Linha: %d, Lexema: %s, Token: INT\n", lexem->line, lexem->word);
        break;
        case 32:   
            printf("Linha: %d, Lexema: %s, Token: STRUCT\n", lexem->line, lexem->word);
        break;
        case 33:   
            printf("Linha: %d, Lexema: %s, Token: _PACKED\n", lexem->line, lexem->word);
        break;
        case 34:
            printf("Linha: %d, Lexema: %s, Token: DOUBLE\n", lexem->line, lexem->word);
        break;
    }
}

token_t tokenfy_word(char *word){
    return get_token_index(word);
}

int get_token_index(char* word){
    for(int i = 0; i<33; i++){
        if(!strcmp(word, reserved_words_list[i]))
            return (i+2);
    }
    return 1;
}