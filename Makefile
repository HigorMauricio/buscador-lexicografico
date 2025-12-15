CC = gcc
CRFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/buscaPalavra.c src/listaOrdenada.c 
OBJ = main.o buscaPalavra.o listaOrdenada.o
EXEC = buscadorLexicografico

$(EXEC): $(OBJ)
	$(CC) $(CRFLAGS) -o $(EXEC) $(OBJ)

main.o: src/main.c include/buscaPalavra.h include/listaOrdenada.h
	$(CC) $(CRFLAGS) -c src/main.c -o main.o 

buscaPalavra.o: src/buscaPalavra.c include/buscaPalavra.h
	$(CC) $(CRFLAGS) -c src/buscaPalavra.c -o buscaPalavra.o 

listaOrdenada.o: src/listaOrdenada.c include/listaOrdenada.h
	$(CC) $(CRFLAGS) -c src/listaOrdenada.c -o listaOrdenada.o 

clean:
	rm -f $(OBJ) $(EXEC)