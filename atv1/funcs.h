#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct{
    int size;
    char* buffer;
}tBuffer;

int allocate_buffer(int, tBuffer*);
void replace_print(FILE*, tBuffer*);
int deallocate_buffer(tBuffer*);
char check_and_replace(char);