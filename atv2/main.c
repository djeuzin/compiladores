#include "funcs.c"

int main(int argc, char* argv[]){

    if(argc != 2)
        return 1;

    FILE *arq;

    arq = fopen(argv[1], "r");
    if(!arq)
        return 1;

    tBuffer b;

    allocate_buffer(256, &b);

    char c;
    int n = 1;
    while(1){
        c = get_next_char(&b, arq);
        printf("%c", c);
        b.used = USED;
        if(n % 5 == 0)
            b.used = UNUSED;
        n++;
        if(c == 0)
            break;
    }

    deallocate_buffer(&b);

    fclose(arq);

    return 0;
}