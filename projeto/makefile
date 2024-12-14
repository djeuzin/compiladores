all: cmenos

cmenos : main.c lex.o
	gcc -o cmenos main.c lex.o

lex.o: lex.c
	gcc -o lex.o lex.c -c