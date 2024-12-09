#include "funcs.c"

int main(int argc, char* argv[]){

    if(argc != 2)
        return 1;

    FILE *arq;

    arq = fopen(argv[1], "r");
    if(!arq)
        return 1;

    buffer_p b;
    lex_t lex;

    b = allocate_buffer(256);

    lex = get_lex(b, arq);
    while(lex.line > 0){
        print_lex(lex);
        lex = get_lex(b, arq);
    }

    if(!(fgets(b->buffer, b->size + 1, arq)))
        printf("testse");

    b = deallocate_buffer(b);

    fclose(arq);

    return 0;
}