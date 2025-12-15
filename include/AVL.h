#define FALSE 0
#define TRUE 1

#define INDEFINIDO -1
#define ESQUERDO 0
#define DIREITO 1

typedef struct info_palavras {
	char* palavra;
	int repeticoes;
	int* ocorrencias;
} Elemento;

typedef int Boolean;

typedef struct _no_arvore_ {

	Elemento valor;
	int h;

	struct _no_arvore_ * esq;
	struct _no_arvore_ * dir;

} No;

typedef struct {

	int qtdpalavras;
	No * raiz;

} Arvore_AVL;

Arvore_AVL * cria_arvore();
void imprime(Arvore_AVL * arvore, char** linhas);

No * busca_AVL(Arvore_AVL * arvore, char* palavra, int* contador);
Boolean insere_AVL(Arvore_AVL * arvore, char* palavra, int linha, int* contador);