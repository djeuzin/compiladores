/*Escreva um programa para colocar em caixa 
alta todas as palavras reservadas fora dos 
comentários de um programa em C. */

#include "funcs.c"

int main(int argc, char* argv[]){
  FILE* arq;
  
  arq = fopen(argv[1], "r+");
  if(arq == NULL){
    printf("Erro ao abrir arquivo.\n");
    return 1;
  }
  
  upper_reserved_words(arq);

  fclose(arq);

  return 0;
}