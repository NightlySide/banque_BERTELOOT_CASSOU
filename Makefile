
default: clean main

clean:
	rm -f main *.o

main:
	gcc -g -Wall main.c -o main
