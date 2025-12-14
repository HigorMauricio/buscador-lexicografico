#ifndef BUSCAPALAVRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO 10000

enum Funcionalidades {
    FIM = 0,
    BUSCA = 1
};

enum Estruturas {
    LISTA = 0,
    ARVORE = 1
};

//normalização de palavras
char *normalizaString(char* palavra);

//Lista Sequencial com as linhas
typedef struct {
    char**linhas;
    int tamanho;
    int capacidade;
}ListaDeLinhas;

ListaDeLinhas* criar_lista(int capacidade);
void adicionar_linha(ListaDeLinhas* lista, char* linhaLida);
#endif
