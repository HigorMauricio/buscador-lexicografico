#include "buscaPalavra.h"

char *normalizaString(char* palavra){
    if(!palavra){
        return NULL;
    }

    int fim = 0;
    for(int i=0; palavra[i]!='\0'; i++){
        if(isalnum(palavra[i])){
            palavra[i] = tolower(palavra[i]);
            fim ++;
        }
    }
    palavra[fim] = '\0';

    return palavra;
}

ListaDeLinhas* criar_lista(int capacidade){

    ListaDeLinhas* lista = (ListaDeLinhas*)malloc(sizeof(ListaDeLinhas));
    if(!lista){
        free(lista);
        return NULL;
    }

    lista->tamanho = 0;
    lista->capacidade = capacidade;
    lista->linhas = (char**)malloc(lista->capacidade * sizeof(char*));
    if(!lista->linhas){
        free(lista);
        return NULL;
    }

    return lista;
}