CC = gcc
CRFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/buscaPalavra.c 
OBJ = main.o buscaPalavra.o 
EXEC = buscadorLexicografico

$(EXEC): $(OBJ)
	$(CC) $(CRFLAGS) -o $(EXEC) $(OBJ)

main.o: src/main.c include/buscaPalavra.h
	$(CC) $(CRFLAGS) -c src/main.c -o main.o 

buscaPalavra.o: src/buscaPalavra.c include/buscaPalavra.h
	$(CC) $(CRFLAGS) -c src/buscaPalavra.c -o buscaPalavra.o 

clean:
	rm -f $(OBJ) $(EXEC)