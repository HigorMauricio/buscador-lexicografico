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

void adicionar_linha(ListaDeLinhas* lista, char* linhaLida){
    if(lista->tamanho == lista->capacidade){
        lista->capacidade *= 2;
        char** nova_linhas = (char**)realloc(lista->linhas, lista->capacidade * sizeof(char*));
        if(!nova_linhas) return;
        lista->linhas = nova_linhas;
    }

    //criando uma copia da linha para armezana-la
    char* copiaLinhaLida = (char*)malloc(strlen(linhaLida) + 1);
    if(copiaLinhaLida){
        strcpy(copiaLinhaLida, linhaLida);
    }
    if(!copiaLinhaLida) return;

    lista->linhas[lista->tamanho] = copiaLinhaLida;
    lista->tamanho ++;
}