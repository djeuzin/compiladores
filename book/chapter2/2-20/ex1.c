/*2.20 Escreva um programa para colocar 
em caixa alta todos os comentários de um programa em C.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Definir a função de transição para o DFA. 

Quando o DFA está nos estado 2 ou 4, estamos dentro de um comentário
*/
#define delta(q, c) (                     \
  (q == 0 && c == '/') ? 1 :              \
  (q == 1 && c == '/') ? 4 :              \
  (q == 1 && c == '*') ? 2 :              \
  (q == 1 && c != '/') ? 0 :              \
  (q == 2 && c == '*') ? 3 :              \
  (q == 3 && c == '/') ? 0 :              \
  (q == 3 && c == '*') ? 3 :              \
  (q == 3 && c != '/') ? 2 :              \
  (q == 4 && c == '\n') ? 0 :             \
  q                                       \
) 

int main(int argc, char *argv[]) {

  int state = 0;
  FILE *file;
  char c;

  file = fopen(argv[1], "r+");
  if(file == NULL){
    printf("Erro ao abrir arquivo.\n");
    return 1;
  }

  while((c = fgetc(file)) != EOF){
    //fputc() adds a '\n' at the end apparently. It makes no sense
    state = delta(state, c);

    if(c != '\n'){
      if(state == 2 || state == 4)
        c = toupper(c);

      fseek(file, -1, SEEK_CUR);
      fputc(c, file);
      fseek(file, 0, SEEK_CUR);
    }
  }

  fclose(file);

  return 0;
}