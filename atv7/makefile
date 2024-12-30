all: main

main: main.o parser.o
	gcc -o main main.o parser.o

main.o: main.c
	gcc -o main.o main.c -c

parser.o: parser.c
	gcc -o parser.o parser.c -c