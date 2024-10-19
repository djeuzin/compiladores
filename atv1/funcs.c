#include "funcs.h"

// Aloca o buffer dado o tamanho da palavra e o ponteiro do buffer
int allocate_buffer(int size, tBuffer* b){
    b->buffer = malloc(size*sizeof(char));
    if(!b->buffer)
        return 0;
    b->size = size;

    return 1;
}

void replace_print(FILE* arq, tBuffer* b){
    while(fgets(b->buffer, b->size, arq)){    
        for(int i=0; i<b->size; i++){
            b->buffer[i] = check_and_replace(b->buffer[i]);
        }
        printf("%s", b->buffer);
    }
}

int deallocate_buffer(tBuffer* b){
    free(b->buffer);
}

char check_and_replace(char c){
    switch(c){
        case 'a':
            return 'A';
        break;
        case 'A':
            return 'a';
        break;
        case 'e':
            return 'E';
        break;
        case 'E':
            return 'e';
        break;
        case 'i':
            return 'I';
        break;
        case 'I':
            return 'i';
        break;
        case 'o':
            return 'O';
        break;
        case 'O':
            return 'o';
        break;
        case 'u':
            return 'U';
        break;
        case 'U':
            return 'u';
        break;
    }

    return c;
}