#Compilation générique avec makefile 

CC=gcc

Jeu_Tente:		main.o fonction_tente.o fonction_tente.h
		$(CC) main.o fonction_tente.o -o Jeu_tente -lm

main.o:		main.c fonction_tente.c

fonction_tente.o:		fonction_tente.c fonction_tente.h

clean:
	@rm -f *.o
	@rm -f core
	@rm -f *~
