#include "funcs.c"

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Erro.\n");
        return 1;
    }

    FILE* arq;
    buffer_p buffer;
    lex_t lexem;

    arq = fopen(argv[1], "r");

    buffer = allocate_buffer(BSIZE);
    if(!buffer)
        return 1;

    get_lexems(buffer, arq, &lexem);

    buffer = deallocate_buffer(buffer);
    fclose(arq);
}