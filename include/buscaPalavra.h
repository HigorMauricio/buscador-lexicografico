#ifndef BUSCAPALAVRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO 10000

enum Funcionalidades {
    fim = 0,
    busca = 1
};

enum Estruturas {
    lista = 0,
    arvore = 1
};

//normalização de palavras:
char *normalizaString(char* palavra);
#endif
