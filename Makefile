
SRC=$(wildcard *.c)
default: clean main

run: clean main
	./main

clean:
	rm -f main *.o

main:$(SRC)
	gcc -o main $^ -Wall 