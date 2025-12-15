#include "buscaPalavra.c"
#include "AVL.c"
#include "listaOrdenada.c"

void buscarPalavraAVL(Arvore_AVL* arvore, char** linhas, char* palavra){
	int contador = 0;
	No * resultado = busca_AVL(arvore, normalizaString(palavra), &contador);

	if(resultado){
		printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s): \n", resultado->valor.repeticoes, resultado->valor.palavra);
		for(int i=0; i<resultado->valor.repeticoes; i++){
			printf("%05d: %s", resultado->valor.ocorrencias[i], linhas[resultado->valor.ocorrencias[i]-1]);
		}
		printf("Numero de comparacoes: %d\n", contador);
	}else
	{
		printf("Palavra '%s' nao encontrada\n", palavra);
		printf("Numero de comparacoes: %d\n", contador);
	}
}


void main_loopAVL(Arvore_AVL* arvore, char** linhas) {
    char comando[100];
    char *funcao;
    char *parametro;

    while (1) {
        printf("> ");
        fgets(comando, sizeof(comando), stdin);

        funcao = strtok(comando, " \t\n");
        parametro = strtok(NULL, " \t\n");

        if (!funcao) continue;

        if (strcmp(funcao, "fim") == 0) {
            break;
        }

        if (strcmp(funcao, "busca") == 0) {
            if (parametro) {
                buscarPalavraAVL(arvore, linhas, parametro);
            } else {
                printf("Parametro invalido!\n");
            }
        } else {
            printf("Opcao invalida!\n");
        }
    }
}

void buscarPalavraLista(ListaOrdenada* lista, char** linhas, char* palavra){
    int contador = 0;
    int indice = busca_binaria_ord(lista, normalizaString(palavra), 0, lista->tamanho, &contador);

	if(indice != -1){
        Palavra* resultado = lista->elementos[indice];
		printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s): \n", resultado->totalDeAparicoes, resultado->palavra);
		for(int i=0; i<resultado->totalDeAparicoes; i++){
			printf("%05d: %s", resultado->linhasDeAparicoes->linhas[i], linhas[resultado->linhasDeAparicoes->linhas[i]-1]);
		}
		printf("Numero de comparacoes: %d\n", contador);
	}else
	{
		printf("Palavra '%s' nao encontrada\n", palavra);
		printf("Numero de comparacoes: %d\n", contador);
	}
}

void main_loopLista(ListaOrdenada* lista, char** linhas) {
    char comando[100];
    char *funcao;
    char *parametro;

    while (1) {
        printf("> ");
        fgets(comando, sizeof(comando), stdin);

        funcao = strtok(comando, " \t\n");
        parametro = strtok(NULL, " \t\n");

        if (!funcao) continue;

        if (strcmp(funcao, "fim") == 0) {
            break;
        }

        if (strcmp(funcao, "busca") == 0) {
            if (parametro) {
                buscarPalavraLista(lista, linhas, parametro);
            } else {
                printf("Parametro invalido!\n");
            }
        } else {
            printf("Opcao invalida!\n");
        }
    }
}

int main(int argc, char ** argv){

	FILE * in;
	char * linha;
	char * quebra_de_linha;
	char * palavra;
	int contador_linha;

	if(argc == 3 && (strcmp(argv[2], "lista") == 0 || strcmp(argv[2], "arvore") == 0) ){

		in = fopen(argv[1], "r");
		contador_linha = 0;
 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char));

        ListaDeLinhas* lista = criar_lista(10);
        if(!lista){
        return 1;
        }

        if(strcmp(argv[2], "lista") == 0){
            ListaOrdenada* listaOrdenada = criar_lista_ordenada(1);

            while (in && fgets(linha, TAMANHO, in)) {
                size_t len = strlen(linha);
                // GARANTE que a linha termine com '\n'
                if (len > 0 && linha[len - 1] != '\n') {
                    linha[len] = '\n';
                    linha[len + 1] = '\0';
                }

                adicionar_linha(lista, linha);  // salva com '\n'

                if ((quebra_de_linha = strrchr(linha, '\n'))) *quebra_de_linha = '\0';

                palavra = strtok(linha, " -/");
                while (palavra != NULL) {
                    adiciona_palavra(listaOrdenada, normalizaString(palavra), contador_linha + 1);
                    palavra = strtok(NULL, " -/");
                }

                contador_linha++;
            }

            fclose(in);
            free(linha);

            printf("Arquivo: '%s'\n", argv[1] + 2);
            printf("Tipo de indice: '%s'\n", argv[2]);
            printf("Total de linhas no arquivo: %d\n", contador_linha);
            printf("Total de palavras unicas indexadas: %d\n", listaOrdenada->tamanho);
            printf("Numero de comparacoes realizadas para a construcao do indice: %d\n", listaOrdenada->totaldecomparacoes);

            main_loopLista(listaOrdenada, lista->linhas);

        }else {

            Arvore_AVL * arvore = cria_arvore();
            int contador = 0;

            while (in && fgets(linha, TAMANHO, in)) {

                size_t len = strlen(linha);

                // GARANTE que a linha termine com '\n'
                if (len > 0 && linha[len - 1] != '\n') {
                    linha[len] = '\n';
                    linha[len + 1] = '\0';
                }

                adicionar_linha(lista, linha);  // salva com '\n'

                if ((quebra_de_linha = strrchr(linha, '\n'))) *quebra_de_linha = '\0';

                palavra = strtok(linha, " -/");
                while (palavra != NULL) {
                    insere_AVL(arvore, normalizaString(palavra), contador_linha + 1, &contador);
                    palavra = strtok(NULL, " -/");
                }

                contador_linha++;
            }


            fclose(in);
            free(linha);

            printf("Arquivo: '%s'\n", argv[1] + 2);
            printf("Tipo de indice: '%s'\n", argv[2]);
            printf("Total de linhas no arquivo: %d\n", contador_linha);
            printf("Total de palavras unicas indexadas: %d\n", arvore->qtdpalavras);
            printf("Altura da arvore: %d\n", arvore->raiz->h);
            printf("Numero de comparacoes realizadas para a construcao do indice: %d\n", contador);

            main_loopAVL(arvore, lista->linhas);
        }

		return 0;
	}
	printf("Uso: %s arquivo.txt lista||arvore\n", argv[0]);
	return 1;
}