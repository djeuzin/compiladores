#include "delta_table.h"

// Dado um caractere retorna o índice correspondente na tabela de transição
int get_delta_index(char c){
        switch(c){
                case '+':
                return 2;
                case '-':
                return 3;
                case '*':
                return 4;
                case '/':
                return 5;
                case '<':
                return 6;
                case '>':
                return 7;
                case '=':
                return 8;
                case '!':
                return 9;
                case ';':
                return 10;
                case ',':
                return 11;
                case '(':
                return 12;
                case ')':
                return 13;
                case '[':
                return 14;
                case ']':
                return 15;
                case '{':
                return 16;
                case '}':
                return 17;
                case ' ':
                return 18;
                default:
                if((c > 64 && c <91) || (c > 96 && c < 123)) // letter
                        return 0;
                if(c > 47 && c < 58) // digit
                        return 1;
                return 19;
        }
}