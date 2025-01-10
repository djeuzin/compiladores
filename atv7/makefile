all: main

main: main.o parser.o
	gcc -o main main.o parser.o

main.o: main.c lex.yy.c
	gcc -o main.o main.c -c

parser.o: parser2.c
	gcc -o parser.o parser2.c -c