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

		ListaOrdenada* listaOrdenada = criar_lista_ordenada(100);

		while(in && fgets(linha, TAMANHO, in)){
            adicionar_linha(lista, linha);
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

			palavra = strtok(linha, " -/");

			while (palavra != NULL) {
				char* palavraNormalizada = normalizaString(palavra);
				if(palavraNormalizada && strlen(palavraNormalizada) > 0) {
        			adiciona_palavra(listaOrdenada, palavraNormalizada, contador_linha);
    			}

				palavra = strtok(NULL, " -/");
			}

			contador_linha++;
		}

		printf(">>>>> Arquivo carregado!\n");

        //teste da lista com as linhas
		for(int i=0; i<listaOrdenada->tamanho; i++){
			printf("%s ", listaOrdenada->elementos[i]->palavra);
		}

		printf("\n total: %d", listaOrdenada->tamanho);


		printf("\n Aparicoes de %s: %d", listaOrdenada->elementos[0]->palavra,listaOrdenada->elementos[0]->totalDeAparicoes);
		return 0;
	}

	return 1;
}