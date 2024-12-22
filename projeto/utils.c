/*****************************/
/*  Cross: C- Compiler       */
/*  utils.c                  */
/*  Contém as implementações */
/*  de funções utilitárias   */
/*****************************/

#include "utils.h"

// Printa o lexema
void print_lexem(){
        switch(mainLex.token){
                case ELSE:
                printf("<ELSE> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case IF:
                printf("<IF> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case INT:
                printf("<INT> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case RETURN:
                printf("<RETURN> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case VOID:
                printf("<VOID> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case WHILE:
                printf("<WHILE> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case ID:
                printf("<ID> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case NUM:
                printf("<NUM> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case PLUS:
                printf("<PLUS> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case MINUS:
                printf("<MINUS> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case AST:
                printf("<AST> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case DASH:
                printf("<DASH> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break; 
                case LTHAN:
                printf("<LTHAN> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case LEQUAL:
                printf("<LEQUAL> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case GTHAN:
                printf("<GTHAN> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case GEQUAL:
                printf("<GEQUAL> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case EQUAL:
                printf("<EQUAL> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case DIFF:
                printf("<DIFF> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case ATT:
                printf("<ATT> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case SCOL:
                printf("<SCOL> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case COMMA:
                printf("<COMMA> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case OP_PAR:
                printf("<OP_PAR> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case CL_PAR:
                printf("<CL_PAR> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case OP_BRA:
                printf("<OP_BRA> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case CL_BRA:
                printf("<CL_BRA> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case OP_CUR:
                printf("<OP_CUR> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                case CL_CUR:
                printf("<CL_CUR> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
                default:
                printf("<ERR> \"%s\" [linha: %d]\n", mainLex.word, mainLex.line);
                break;
        }
}     