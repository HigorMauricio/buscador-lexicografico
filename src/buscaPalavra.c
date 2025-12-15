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

ListaOrdenada* criar_lista_ordenada(int capacidade){
    ListaOrdenada* listaOrdenada = (ListaOrdenada*)malloc(sizeof(ListaOrdenada));
    if(!listaOrdenada) return NULL;

    listaOrdenada->tamanho = 0;
    listaOrdenada->totaldecomparacoes = 0;
    listaOrdenada->capacidade = capacidade;
    listaOrdenada->elementos = (Palavra**)malloc(capacidade * sizeof(Palavra*));
    if(!listaOrdenada->elementos) return NULL;

    return listaOrdenada;
}

void registrar_linha(Palavra* palavra, int linhaAtual){
    ListaDeAparicoes* lista = palavra->linhasDeAparicoes;
    if(lista->tamanho == lista->capacidade){
        lista->capacidade += 10;
        int* nova_lista = (int*)realloc(lista->linhas, lista->capacidade * sizeof(int));
        if(!nova_lista) return;
        lista->linhas = nova_lista;
    }

    lista->linhas[lista->tamanho] = linhaAtual;
    lista->tamanho ++;
}


void adiciona_palavra(ListaOrdenada* lista, char* palavraLida, int linhaAtual){
    if(lista->tamanho == lista->capacidade){
        lista->capacidade *= 2;
        Palavra** novo_elementos = (Palavra**)realloc(lista->elementos, lista->capacidade * sizeof(Palavra*));
        if(!novo_elementos) return;
        lista->elementos = novo_elementos;
    }

    int i;
    for(i=0; i<lista->tamanho; i++){
        lista->totaldecomparacoes ++;
        Palavra* palavraAtual = lista->elementos[i];
        int comparacao = strcmp(palavraAtual->palavra, palavraLida);
        if(comparacao == 0){
            palavraAtual->totalDeAparicoes ++;
            //adição na lista com as linhas
            registrar_linha(palavraAtual, linhaAtual);
            return;
        }

        if(comparacao > 0){
            break;
        }
    }

    for(int j=lista->tamanho; j>i; j--){
        lista->elementos[j] = lista->elementos[j-1];

    }

    Palavra* novaPalavra = (Palavra*)malloc(sizeof(Palavra));

    char* copiaPalavraLida = (char*)malloc(strlen(palavraLida) + 1);
    if(copiaPalavraLida){
        strcpy(copiaPalavraLida, palavraLida);
    }
    if(!copiaPalavraLida) return;
    novaPalavra->palavra = copiaPalavraLida;
    novaPalavra->totalDeAparicoes = 1;

    novaPalavra->linhasDeAparicoes = (ListaDeAparicoes*)malloc(sizeof(ListaDeAparicoes));
    novaPalavra->linhasDeAparicoes->tamanho = 0;
    novaPalavra->linhasDeAparicoes->capacidade = 10;
    novaPalavra->linhasDeAparicoes->linhas = (int*)malloc(novaPalavra->linhasDeAparicoes->capacidade * sizeof(int));
    registrar_linha(novaPalavra, linhaAtual);

    lista->elementos[i] = novaPalavra;
    lista->tamanho ++;
}

int busca_binaria_ord(ListaOrdenada* lista, char* palavraBuscada, int inicio, int fim, int *comparacoes){
    if(inicio <= fim){
        int meio = (inicio + fim)/2;
        if(strcmp(palavraBuscada, lista->elementos[meio]->palavra) == 0){
            (*comparacoes) ++;
            return meio;
        }else if(strcmp(palavraBuscada, lista->elementos[meio]->palavra) > 0){
            inicio = meio + 1;
            (*comparacoes) ++;
            return busca_binaria_ord(lista, palavraBuscada, inicio, fim, comparacoes);
        }else if(strcmp(palavraBuscada, lista->elementos[meio]->palavra) < 0){
            fim = meio -1;
            (*comparacoes)++;
            return busca_binaria_ord(lista, palavraBuscada, inicio, fim, comparacoes);
        }
    }

    return -1;
    
}
