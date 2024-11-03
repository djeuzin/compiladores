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

    char c = get_next_char(&b, arq);
    int n = 1;
    while(c != EOF){
        b.used = USED;
        if(n % 5 == 0)
            b.used = UNUSED;
        printf("%c", c);
        c = get_next_char(&b, arq);
        n++;
    }

    printf("%d", b.next_line);

    deallocate_buffer(&b);

    fclose(arq);

    return 0;
}