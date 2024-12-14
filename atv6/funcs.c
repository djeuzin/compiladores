#include "funcs.h"

char* get_token(lexem mainLex){
    switch(mainLex.token){
        case ID:
            return "ID";
        break;
        case IF:
            return "IF";
        break; 
        case THEN:
            return "THEN";
        break;
        case ELSE:
            return "ELSE";
        break; 
        case END:
            return "END";
        break; 
        case REPEAT:
            return "REPEAT";
        break;
        case UNTIL:
            return "UNTIL";
        break;
        case READ:
            return "READ";
        break; 
        case WRITE:
            return "WRITE";
        break;
        case PLUS:
            return "PSIGN";
        break;
        case MINUS:
            return "MSIGN";
        break;
        case TIMES:
            return "SSIGN";
        break;
        case DASH:
            return "SLASH";
        break;
        case EQ:
            return "EQUAL";
        break;
        case LTHAN:
            return "LTHAN";
        break;
        case LPAR:
            return "OP_PAR";
        break;
        case RPAR:
            return "CL_PAR";
        break;
        case ATT:
            return "ATT";
        break;
        case SCOL:
            return "SEMICOLLON";
        break;
        case NUM:
            return "NUM";
        break; 
    }
}

void print_lex(lexem mainLex){
    char* t = get_token(mainLex);
    printf("LEXEMA: <%s>, TOKEN: %s, LINE: %d\n", mainLex.word, t, mainLex.line);
}