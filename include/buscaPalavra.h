#ifndef BUSCAPALAVRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO 10000
#define TOTALDEAPARICOES 100
#define BOOL int
#define TRUE 1
#define FALSE 0

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

//Lista ordenada com as palavras
typedef struct {
    int* linhas;
    int tamanho;
    int capacidade;
}ListaDeAparicoes;

typedef struct {
    char* palavra;
    int totalDeAparicoes;
    ListaDeAparicoes* linhasDeAparicoes;
}Palavra;

typedef struct {
    Palavra** elementos;
    int tamanho;
    int capacidade;
    int totaldecomparacoes;
}ListaOrdenada;

ListaOrdenada* criar_lista_ordenada(int capacidade);
void registrar_linha(Palavra* palavra, int linhaAtual);
void adiciona_palavra(ListaOrdenada* lista, char* palavra, int linhaAtual);
#endif
