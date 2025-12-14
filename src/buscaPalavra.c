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