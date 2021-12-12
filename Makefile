
SRC=$(wildcard *.c)
default: clean main

clean:
	rm -f main *.o

main:$(SRC)
	gcc -o main $^ -Wall 