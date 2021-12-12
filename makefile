default : projetC/V2/main

main :	projetC/V2/main.c projetC/V2
	gcc -g -Wall projetC/V2/main.c -o projetC/V2/main
	
date : projetC/V2/date.c projetC/V2
	gcc -g -Wall projetC/V2/date.c -o projetC/V2/date
