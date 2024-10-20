/*Studyin the behavior of the fseek function to read characters on a file

  The way the file pointer works is still a bit foggy
*/

#include <stdio.h>

int main(){
  FILE* arq = fopen("text.txt", "r");
  char c, next;

  while((c = getc(arq)) != -1){
    next = getc(arq);
    if(next == EOF)
      fseek(arq, 0, SEEK_END);
    else
      fseek(arq, -1, SEEK_CUR);
    printf("%c-", c);
    printf("%c\n", next);
  }

  /*
    for a file:
      123

    the file pointer at the execution works as follows:
    1. 123 (c = getc(arq))
       ^
    2. 123 (next = getc(arq))
        ^
    3. 123 (fseek(arq, -1, 1))
       ^
    4. 123 (c = getc(arq))
        ^
    5. 123 (next = getc(arq))
         ^
    6. 123 (fseek(arq, -1, 1))
        ^
    7. 123 (c = getc(arq))
         ^
    8. 123 (next = getc(arq))
          ^
    9. 123 (fseek(arq, -1, 1))
         ^
    10. 123 (c = getc(arq)) -> here the function was expected to move the pointer to the end of the file and then the while loop would break, but that doesn't happen. It's like the pointer decreases two positions in step 9
          ^
    11. 123 (next = getc(arq))
           ^
    ...

    To work around this problem then I decided to put a conditional.
    Basically, when the next character is EOF, we move the pointer to SEEK_END.
    This way we avoid the weird behavior of the fseek when the pointer is already in EOF...
    even though the code looks less clean.
  */

  fclose(arq);

  return 0;
}