#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TEST

#define is_letter(c) (                                   \
    ((64 < c && c < 91) || (96 < c && c < 123)) ? 1 : 0  \
)

#define is_number(c) (                                   \
    (47 < c && c < 58) ? 1 : 0                           \
)

#define BSIZE 256

enum reserved_words{
    ID,
    IF, 
    THEN, 
    ELSE, 
    END, 
    REPEAT, 
    UNTIL, 
    READ, 
    WRITE,
    PSIGN,
    MSIGN,
    SSIGN,
    SLASH,
    EQUAL,
    LTHAN,
    OP_PAR,
    CL_PAR,
    ATT,  //:=
    SEMICOLLON,
    NUM 
};

typedef enum reserved_words token_t;

char const *reserved_words_list[] = {"if", "then", "else", "end", "repeat", "until", "read", "write"};

#define USED   1
#define UNUSED 0

typedef struct{
    unsigned int size;            /* Tamanho do buffer */                           
    unsigned int index;           /* Índice do caractere a ser lido */      
    unsigned int line;            /* Número da linha do caractere */        
    unsigned int used;            /* Flag para indicar se o caractere foi usado */  
    char* buffer;                 /* String buffer */
}buffer_t;

typedef buffer_t* buffer_p;

typedef struct{
    token_t token;
    unsigned int line; 
    char word[64];
} lex_t;

typedef lex_t* lex_p;

buffer_p allocate_buffer(int);
buffer_p deallocate_buffer(buffer_p);
void fill_buffer(buffer_p, FILE*);
char get_next_char(buffer_p, FILE*);
void get_lexems(buffer_p, FILE*, lex_p);
void print_lex(lex_t);
token_t tokenfy_word(char *);
int get_token_index(char *);
lex_t get_lex(buffer_p, FILE*);
void print_lex(lex_t);