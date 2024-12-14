all: main

main: main.c funcs.o
	gcc -o main main.c funcs.o

funcs.o: funcs.c
	gcc -o funcs.o funcs.c -c

clean:
	rm *.o