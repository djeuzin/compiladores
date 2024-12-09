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
        if(b->buffer[b->index + 1] == '\0'){
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
    b->index = -1;
    b->buffer[0] = '\0';
    b->line = 1;

    return b;
}

buffer_p deallocate_buffer(buffer_p b){
    free(b->buffer);
    free(b);
    return NULL;
}

token_t tokenfy_word(char *word){
    if(!strcmp(word, "if"))
        return IF;
    if(!strcmp(word, "then"))
        return THEN;
    if(!strcmp(word, "else"))
        return ELSE;
    if(!strcmp(word, "end"))
        return END;
    if(!strcmp(word, "repeat"))
        return REPEAT;
    if(!strcmp(word, "until"))
        return UNTIL;
    if(!strcmp(word, "read"))
        return READ; 
    if(!strcmp(word, "write"))
        return WRITE; 
    return ID;
}

lex_t get_lex(buffer_p b, FILE* arq){
    char c = get_next_char(b, arq);
    int state = 0;
    lex_t newLex;
    int lexIndex = 0;

    while(c!=EOF){
        switch(state){
            case 0:
                switch(c){
                    break;
                    case '{':
                        state = 4;
                        b->used = USED;
                    break;
                    case ';':
                        state = 0;
                        newLex.word[lexIndex] = c;
                        lexIndex++;
                        newLex.word[lexIndex] = '\0';
                        b->used = USED;
                        newLex.line = b->line;
                        newLex.token = SEMICOLLON;
                        return newLex;
                    break;
                    case '+':
                        state = 0;
                        newLex.word[lexIndex] = c;
                        lexIndex++;
                        newLex.word[lexIndex] = '\0';
                        b->used = USED;
                        newLex.line = b->line;
                        newLex.token = PSIGN;
                        return newLex;
                    break;
                    case '-':
                        state = 0;
                        newLex.word[lexIndex] = c;
                        lexIndex++;
                        newLex.word[lexIndex] = '\0';
                        b->used = USED;
                        newLex.line = b->line;
                        newLex.token = MSIGN;
                        return newLex;
                    break;
                    case '/':
                        state = 0;
                        newLex.word[lexIndex] = c;
                        lexIndex++;
                        newLex.word[lexIndex] = '\0';
                        b->used = USED;
                        newLex.line = b->line;
                        newLex.token = SLASH;
                        return newLex;
                    break;
                    case '*':
                        state = 0;
                        newLex.word[lexIndex] = c;
                        lexIndex++;
                        newLex.word[lexIndex] = '\0';
                        b->used = USED;
                        newLex.line = b->line;
                        newLex.token = SSIGN;
                        return newLex;
                    break;
                    case '(':
                        state = 0;
                        newLex.word[lexIndex] = c;
                        lexIndex++;
                        newLex.word[lexIndex] = '\0';
                        b->used = USED;
                        newLex.line = b->line;
                        newLex.token = OP_PAR;
                        return newLex;
                    break;
                    case ')':
                        state = 0;
                        newLex.word[lexIndex] = c;
                        lexIndex++;
                        newLex.word[lexIndex] = '\0';
                        b->used = USED;
                        newLex.line = b->line;
                        newLex.token = CL_PAR;
                        return newLex;
                    break;
                    case '=':
                        state = 0;
                        newLex.word[lexIndex] = c;
                        lexIndex++;
                        newLex.word[lexIndex] = '\0';
                        b->used = USED;
                        newLex.line = b->line;
                        newLex.token = EQUAL;
                        return newLex;
                    break;
                    case '<':
                        state = 0;
                        newLex.word[lexIndex] = c;
                        lexIndex++;
                        newLex.word[lexIndex] = '\0';
                        b->used = USED;
                        newLex.line = b->line;
                        newLex.token = LTHAN;
                        return newLex;
                    break;
                    case ':':
                        state = 3;
                        newLex.word[lexIndex] = c;
                        lexIndex++;
                        b->used = USED;
                        newLex.line = b->line;
                    break;
                    case ' ':
                    //case '\0':
                        b->used = USED;
                    break;
                    case '\n':
                        b->used = USED;
                        c = get_next_char(b, arq);
                    break;
                    default:
                        if((c>64 && c<91) || (c>96 && c<123)){
                            state = 1;
                            b->used = USED;
                            newLex.word[lexIndex] = c;
                            lexIndex++;
                            newLex.line = b->line;
                        }
                        else if(c > 47 && c < 58){
                            state = 2;
                            b->used = USED;
                            newLex.word[lexIndex] = c;
                            lexIndex++;
                            newLex.line = b->line;
                        }
                        else{
                            b = deallocate_buffer(b);
                            exit(1);
                        }
                    break;
                }
            break;
            case 1:
                if((c>64 && c<91) || (c>96 && c<123)){
                    b->used = USED;
                    newLex.word[lexIndex] = c;
                    lexIndex++;
                }
                else{
                    newLex.word[lexIndex] = '\0';
                    newLex.token = tokenfy_word(newLex.word);
                    b->used = UNUSED;
                    return newLex;
                }
            break;
            case 2:
                if(c > 47 && c < 58){
                    b->used = USED;
                    newLex.word[lexIndex] = c;
                    lexIndex++;
                }
                else{
                    b->used = UNUSED;
                    newLex.word[lexIndex] = '\0';
                    newLex.token = NUM;
                    return newLex;
                } 
            break;
            case 3:
                if(c == '='){
                    newLex.word[lexIndex] = c;
                    lexIndex++;
                    newLex.word[lexIndex] = '\0';
                    newLex.token = ATT;
                    return newLex;
                }
                printf("Erro: caractere inválido\n");
                b = deallocate_buffer(b);
                exit(1);
            break;
            case 4:
                switch(c){
                    case '{':
                        printf("Erro: comentário aninhado. Inválido\n");
                        b = deallocate_buffer(b);
                        exit(1);
                    break;
                    case '}':
                        b->used = USED;

                        state = 0;
                    break;
                    default:
                        b->used = USED;

                    break;
                }
            break;
        }
        c = get_next_char(b, arq);
    }
    newLex.line = -1;
    return newLex;
}

char* get_token(token_t token){
    switch(token){
        case ID:
            return "ID";
        break;
        case IF:
            return "IF";
        break; 
        case THEN:
            return "THEN";
        break;
        case ELSE:
            return "ELSE";
        break; 
        case END:
            return "END";
        break; 
        case REPEAT:
            return "REPEAT";
        break;
        case UNTIL:
            return "UNTIL";
        break;
        case READ:
            return "READ";
        break; 
        case WRITE:
            return "WRITE";
        break;
        case PSIGN:
            return "PSIGN";
        break;
        case MSIGN:
            return "MSIGN";
        break;
        case SSIGN:
            return "SSIGN";
        break;
        case SLASH:
            return "SLASH";
        break;
        case EQUAL:
            return "EQUAL";
        break;
        case LTHAN:
            return "LTHAN";
        break;
        case OP_PAR:
            return "OP_PAR";
        break;
        case CL_PAR:
            return "CL_PAR";
        break;
        case ATT:
            return "ATT";
        break;
        case SEMICOLLON:
            return "SEMICOLLON";
        break;
        case NUM:
            return "NUM";
        break; 
    }
}

void print_lex(lex_t lex){
    char* t = get_token(lex.token);
    printf("LEXEMA: <%s>, TOKEN: %s, LINE: %d\n", lex.word, t, lex.line);
}