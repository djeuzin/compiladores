#include "funcs.h"

int main(int argc, char* argv[]){
    if(argc==3){
        FILE* arq = fopen(argv[1], "r");
        tBuffer b;

        if(arq){
            allocate_buffer(atoi(argv[2]), &b);
            replace_print(arq, &b);
            deallocate_buffer(&b);
            fclose(arq);
        }
    }
    return 0;
}