#include "funcs.h"

char get_next_char(tBuffer* b, FILE* arq){
    char c;

    if(!(b->loaded)){
        if(fgets(b->buffer, b->size, arq) != NULL){
            b->next_index = 1;
            b->loaded = 1;
            b->used = UNUSED;
        }
        else
            return EOF;
    }

    // Se foi usado, resetar a flag e incrementar o buffer
    if(b->used == USED){
        b->used = UNUSED;
        c = b->buffer[b->next_index];
        (b->next_index)++;
    }
    else{
        c = b->buffer[b->next_index - 1];
    }

    // Incrementar a linha do próximo caractere do buffer e resetar a flag loaded
    if(c == '\n'){
        (b->next_line)++;
        b->loaded = 0;
    }

    if(b->next_index >= b->size){
        b->loaded = 0;
    }
    
    return c;
}

int allocate_buffer(int size, tBuffer* b){
    b->buffer = malloc(size*sizeof(char));
    if(!b->buffer)
        return 0;
    b->size = size;
    b->loaded = 0;
    b->used = UNUSED;
    b->next_index = 1;
    b->next_line = 1;

    return 1;
}

int deallocate_buffer(tBuffer* b){
    free(b->buffer);
}

void testing_fgets(tBuffer *b, FILE *arq){
    fgets(b->buffer, b->size, arq);
}

