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
    int state = 0;
    
    while(c != EOF){
        c = get_next_char(b, arq);
        switch (state){
            case 0:
                if(is_letter(c)){
                    state = 1;
                    lexem->word[i] = c;
                    lexem->line = b->line;
                    i++;
                }
                if(is_number(c)){
                    state = 2;
                    lexem->word[i] = c;
                    i++;
                    lexem->line = b->line;
                }        
                b->used = USED;
            break;
            case 1:
                if(!is_letter(c)){
                    lexem->word[i] = '\0';
                    lexem->token = tokenfy_word(lexem->word);
                    i = 0;
                    print_lex(lexem);
                    state = 0;
                    b->used = UNUSED;
                }
                else{
                    lexem->word[i] = c;
                    i++;
                    b->used = USED;
                }
            break;
            case 2:
                if(!is_number(c)){
                    lexem->word[i] = '\0';
                    lexem->token = NUM;
                    i = 0;
                    print_lex(lexem);
                    state = 0;
                    b->used = UNUSED;
                }
                else{
                    lexem->word[i] = c;
                    i++;
                    b->used = USED;
                }
            break;
        }
    }
}

void print_lex(lex_p lexem){
    switch(lexem->token){
        case ID:
            printf("Linha: %d, Lexema: %s, Token: ID\n", lexem->line, lexem->word);
        break;
        case AUTO:
            printf("Linha: %d, Lexema: %s, Token: AUTO\n", lexem->line, lexem->word);
        break;
        case ELSE:
            printf("Linha: %d, Lexema: %s, Token: ELSE\n", lexem->line, lexem->word);
        break;
        case LONG:
            printf("Linha: %d, Lexema: %s, Token: LONG\n", lexem->line, lexem->word);
        break;
        case SWITCH:   
            printf("Linha: %d, Lexema: %s, Token: SWITCH\n", lexem->line, lexem->word);
        break;
        case BREAK:   
            printf("Linha: %d, Lexema: %s, Token: BREAK\n", lexem->line, lexem->word);
        break;
        case ENUM:   
            printf("Linha: %d, Lexema: %s, Token: ENUM\n", lexem->line, lexem->word);
        break;
        case REGISTER:   
            printf("Linha: %d, Lexema: %s, Token: REGISTER\n", lexem->line, lexem->word);
        break;
        case TYPEDEF:   
            printf("Linha: %d, Lexema: %s, Token: TYPEDEF\n", lexem->line, lexem->word);
        break;
        case CASE:   
            printf("Linha: %d, Lexema: %s, Token: CASE\n", lexem->line, lexem->word);
        break;
        case EXTERN:   
            printf("Linha: %d, Lexema: %s, Token: EXTERN\n", lexem->line, lexem->word);
        break;
        case RETURN:   
            printf("Linha: %d, Lexema: %s, Token: RETURN\n", lexem->line, lexem->word);
        break;
        case UNION:   
            printf("Linha: %d, Lexema: %s, Token: UNION\n", lexem->line, lexem->word);
        break;
        case CHAR:   
            printf("Linha: %d, Lexema: %s, Token: CHAR\n", lexem->line, lexem->word);
        break;
        case FLOAT:   
            printf("Linha: %d, Lexema: %s, Token: FLOAT\n", lexem->line, lexem->word);
        break;
        case SHORT:   
            printf("Linha: %d, Lexema: %s, Token: SHORT\n", lexem->line, lexem->word);
        break;
        case UNSIGNED:   
            printf("Linha: %d, Lexema: %s, Token: UNSIGNED\n", lexem->line, lexem->word);
        break;
        case CONST:   
            printf("Linha: %d, Lexema: %s, Token: CONST\n", lexem->line, lexem->word);;
        break;
        case FOR:   
            printf("Linha: %d, Lexema: %s, Token: FOR\n", lexem->line, lexem->word);
        break;
        case SIGNED:   
            printf("Linha: %d, Lexema: %s, Token: SIGNED\n", lexem->line, lexem->word);
        break;
        case VOID:   
            printf("Linha: %d, Lexema: %s, Token: VOID\n", lexem->line, lexem->word);
        break;
        case CONTINUE:   
            printf("Linha: %d, Lexema: %s, Token: CONTINUE\n", lexem->line, lexem->word);
        break;
        case GOTO:   
            printf("Linha: %d, Lexema: %s, Token: GOTO\n", lexem->line, lexem->word);
        break;
        case SIZEOF:   
            printf("Linha: %d, Lexema: %s, Token: SIZEOF\n", lexem->line, lexem->word);
        break;
        case VOLATILE:   
            printf("Linha: %d, Lexema: %s, Token: VOLATILE\n", lexem->line, lexem->word);
        break;
        case DEFAULT:   
            printf("Linha: %d, Lexema: %s, Token: DEFAULT\n", lexem->line, lexem->word);
        break;
        case IF:   
            printf("Linha: %d, Lexema: %s, Token: IF\n", lexem->line, lexem->word);
        break;
        case STATIC:   
            printf("Linha: %d, Lexema: %s, Token: STATIC\n", lexem->line, lexem->word);
        break;
        case WHILE:   
            printf("Linha: %d, Lexema: %s, Token: WHILE\n", lexem->line, lexem->word);
        break;
        case DO:   
            printf("Linha: %d, Lexema: %s, Token: DO\n", lexem->line, lexem->word);
        break;
        case INT:   
            printf("Linha: %d, Lexema: %s, Token: INT\n", lexem->line, lexem->word);
        break;
        case STRUCT:   
            printf("Linha: %d, Lexema: %s, Token: STRUCT\n", lexem->line, lexem->word);
        break;
        case _PACKED:   
            printf("Linha: %d, Lexema: %s, Token: _PACKED\n", lexem->line, lexem->word);
        break;
        case DOUBLE:
            printf("Linha: %d, Lexema: %s, Token: DOUBLE\n", lexem->line, lexem->word);
        break;
        case NUM:
            printf("Linha: %d, Lexema: %s, Token: NUM\n", lexem->line, lexem->word);
        break;
    }
}

token_t tokenfy_word(char *word){
    return get_token_index(word);
}

int get_token_index(char* word){
    for(int i = 0; i<33; i++){
        if(!strcmp(word, reserved_words_list[i]))
            return (i+1);
    }
    return 0;
}