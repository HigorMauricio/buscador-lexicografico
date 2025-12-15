#ifndef LISTAORDENADA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
int busca_binaria_ord(ListaOrdenada* lista, char* palavraBuscada, int inicio, int fim, int *comparacoes);

#endif