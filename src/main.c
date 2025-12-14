#include "buscaPalavra.h"

int main(int argc, char ** argv){

	FILE * in;
	char * linha;
	char * quebra_de_linha;
	char * palavra;	
	int contador_linha;

	if(argc == 2) {

		in = fopen(argv[1], "r");

		printf(">>>>> Carregando arquivo...\n");

		contador_linha = 0;
 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char));

        ListaDeLinhas* lista = criar_lista(10);
        if(!lista){
            return 1;
        }

		while(in && fgets(linha, TAMANHO, in)){
            adicionar_linha(lista, linha);
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

			palavra = strtok(linha, " -/");
			while (palavra != NULL) {
				printf("\t\t'%s'\n", normalizaString(palavra));
				palavra = strtok(NULL, " -/");
			}

			contador_linha++;
		}

		printf(">>>>> Arquivo carregado!\n");

        //teste da lista com as linhas
        for(int i=0; i<=lista->tamanho; i++){
            printf("linha %d: %s", i+1, lista->linhas[i]);
        }
		return 0;
	}

	return 1;
}