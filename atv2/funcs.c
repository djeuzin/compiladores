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
char get_next_char(tBuffer* b, FILE* arq){
    if(b->used){
        if(b->buffer[b->next_index-1] == '\0'){
            if(fgets(b->buffer, b->size + 1, arq))
                b->next_index = 0;
            else
                return EOF;
        }

        (b->next_index)++;

        if(b->buffer[b->next_index-1] == '\n')
            (b->next_line)++;
    }

    return b->buffer[b->next_index - 1];
}

int allocate_buffer(int size, tBuffer* b){
    b->buffer = malloc((size+1)*sizeof(char));
    if(!b->buffer)
        return 0;
    b->size = size;
    b->used = USED;
    b->next_index = 1;
    b->buffer[0] = '\0';
    b->next_line = 1;

    return 1;
}

int deallocate_buffer(tBuffer* b){
    free(b->buffer);
}