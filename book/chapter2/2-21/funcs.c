#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

char const *reserved_words[] = {                    \
"auto",	"else",	"long",	"switch",                   \
"break", "enum",	"register",	"typedef",            \
"case",	"extern",	"return",	"union",                \
"char",	"float",	"short",	"unsigned",             \
"const", "for",	"signed",	"void",                   \
"continue",	"goto",	"sizeof",	"volatile",           \
"default", "if", "static", "while",                 \
"do", "int", "struct", "_Packed", "double"          \
};

// Confere se a palavra é reservada (está na lista). Caso seja, coloca a palavra em caixa alta
int check_and_replace(char* word, int size){
  for(int i = 0; i<33; i++){
    if(!strcmp(word, reserved_words[i])){
      for(int j = 0; j<size; j++){
        word[j] = toupper(word[j]);
      }
      return 1;
    }
  }
  return 0;
}

int is_alphanumeric(char c){
  return ((c <= 90 && c >= 65) || (c >= 48 && c <= 57) || (c >= 97 && c <= 122) || c ==  95) ? 1 : 0;
}

void upper_reserved_words(FILE *arq){
  char buffer[50], c;                   //Buffer armazena cada palavra, c para percorrer cada caractere do arquivo
  int bIndex = 0, state = 0;            //state controla se o ponteiro do arquivo está em um comentário ou não e bIndex o tamanho da palavra no buffer

  while((c = getc(arq)) != EOF){
    fseek(arq, -1, SEEK_CUR);
    c = getc(arq);
    fseek(arq, 0, SEEK_CUR);
    state = delta(state, c);

    if(state != 2 && state != 4){
      if(is_alphanumeric(c)){
        buffer[bIndex] = c;
        bIndex++;
      }
      else{
        buffer[bIndex] = '\0';
        check_and_replace(buffer, bIndex);
        if(bIndex){  
          fseek(arq, -bIndex-1, SEEK_CUR);
          for(int i=0; i<bIndex; i++){
            fputc(buffer[i], arq);
            fseek(arq, 0, SEEK_CUR);
          }
          bIndex = 0;
        }
      }
    }
  }
}