#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TEST

#define BSIZE 256

enum reserved_words{
    ID = 1,
    AUTO,
    ELSE,
    LONG,
    SWITCH,
    BREAK,
    ENUM,
    REGISTER,
    TYPEDEF,
    CASE,
    EXTERN,
    RETURN,
    UNION,
    CHAR,
    FLOAT,
    SHORT,
    UNSIGNED,
    CONST,
    FOR,
    SIGNED,
    VOID,
    CONTINUE,
    GOTO,
    SIZEOF,
    VOLATILE,
    DEFAULT,
    IF,
    STATIC,
    WHILE,
    DO,
    INT,
    STRUCT,
    _PACKED,
    DOUBLE
};

typedef enum reserved_words token_t;

char const *reserved_words_list[] = {                    \
"auto",	"else",	"long",	"switch",                   \
"break", "enum", "register",	"typedef",            \
"case",	"extern",	"return",	"union",                \
"char",	"float",	"short",	"unsigned",             \
"const", "for",	"signed",	"void",                   \
"continue",	"goto",	"sizeof",	"volatile",           \
"default", "if", "static", "while",                 \
"do", "int", "struct", "_Packed", "double"          \
};

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
void print_lex(lex_p);
token_t tokenfy_word(char *);
int get_token_index(char *);