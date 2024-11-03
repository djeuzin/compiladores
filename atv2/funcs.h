#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define USED 1
#define UNUSED 0

typedef struct{
    unsigned int size,            /* Tamanho do buffer */                           \
                 next_index,      /* Índice do próximo caractere a ser lido */      \
                 next_line,       /* Número da linha do próximo caractere */        \
                 used;            /* Flag para indicar se o caractere foi usado */  
    char* buffer;
}tBuffer;

int allocate_buffer(int, tBuffer*);
int deallocate_buffer(tBuffer*);
void fill_buffer(tBuffer*, FILE*);
char get_next_char(tBuffer*, FILE*);