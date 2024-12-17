all: lex

lex: lex.yy.c
	gcc -o lex lex.yy.c

lex.yy.c: lexer.l
	flex lexer.l