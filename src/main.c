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
		int posicao = busca_binaria_ord(listaOrdenada, "algorithm", 0, listaOrdenada->tamanho);
		printf("Palavra: %s, Quantidade de repeticao: %d ", listaOrdenada->elementos[posicao]->palavra, listaOrdenada->elementos[posicao]->totalDeAparicoes);
		printf("linhas que aparecem: ");
		for(int i=0; i< listaOrdenada->elementos[posicao]->totalDeAparicoes; i++){
			printf("%d ", listaOrdenada->elementos[posicao]->linhasDeAparicoes->linhas[i] + 1);
		}
		printf("\n");
		for(int i=0; i< listaOrdenada->elementos[posicao]->totalDeAparicoes; i++){
			printf("linha %d: %s", listaOrdenada->elementos[posicao]->linhasDeAparicoes->linhas[i] + 1, lista->linhas[listaOrdenada->elementos[posicao]->linhasDeAparicoes->linhas[i]]);
		}
		
		return 0;
	}

	return 1;
}