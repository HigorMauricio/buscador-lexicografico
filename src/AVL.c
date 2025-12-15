#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "AVL.h"


Arvore_AVL * cria_arvore(){

	Arvore_AVL * arvore = (Arvore_AVL *) malloc (sizeof(Arvore_AVL));
	arvore->qtdpalavras = 0;
	arvore->raiz = NULL;
	return arvore;
}

void imprime_rec(No * no, char** linhas){

	if(no){
		imprime_rec(no->esq, linhas);
		printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s): \n", no->valor.repeticoes, no->valor.palavra);
		for(int i=0; i<no->valor.repeticoes; i++){
			printf("%05d: %s", no->valor.ocorrencias[i], linhas[no->valor.ocorrencias[i]-1]);
		}
		imprime_rec(no->dir, linhas);
	}
}

void imprime(Arvore_AVL * arvore, char** linhas){

	printf("Elementos na arvore:");
	imprime_rec(arvore->raiz, linhas);
	printf("\n");
	printf("Quantidade de palavras distintas: %d\n", arvore->qtdpalavras);
}

No * busca_AVL_rec(No * no, char* palavra, int* contador){

	if(contador) (*contador) ++;

	if(no){

		if(strcmp(no->valor.palavra, palavra) == 0) return no;
		if(strcmp(palavra, no->valor.palavra) < 0) return busca_AVL_rec(no->esq, palavra, contador);
		return busca_AVL_rec(no->dir, palavra, contador);
	}

	return NULL;
}

No * busca_AVL(Arvore_AVL * arvore, char* palavra, int* contador){

	return busca_AVL_rec(arvore->raiz, palavra, contador);
}

int max(int a, int b){
	return a > b ? a : b;
}

int balanco(No * no){
	if(no->esq && no->dir) return (no->dir->h) - (no->esq->h);
	if(no->esq) return -1 * (no->esq->h + 1);
	if(no->dir) return no->dir->h + 1;
	return 0;
}

void atualiza_altura(No * no){

	// assuminos que todos os nós na (sub)arvore definida por 'no' já estão com suas alturas atualizadas.

	if(no->esq && no->dir) no->h = max(no->esq->h, no->dir->h) + 1;
	else if(no->dir) no->h = no->dir->h + 1;
	else if(no->esq) no->h = no->esq->h + 1;
	else no->h = 0;
}

No * rotacaoL(No * p){

	No * v;
	No * u = p->esq;

	if(balanco(u) == -1) { // rotação LL

		p->esq = u->dir;
		u->dir = p;
		p->h -= 2;
		return u;
	}
	else if(balanco(u) == 1) { // rotação LR

		v = u->dir;

		u->dir = v->esq;
		v->esq = u;
		p->esq = v->dir;
		v->dir = p;

		p->h -= 2;
		u->h -= 1;
		v->h += 1;

		return v;
	}

	return NULL;
}

No * rotacaoR(No * p){

	No * v;
	No * u = p->dir;

	if(balanco(u) == 1) { // rotação RR

		p->dir = u->esq;
		u->esq = p;
		p->h -= 2;
		return u;
	}
	else if(balanco(u) == -1) { // rotação RL

		v = u->esq;

		u->esq = v->dir;
		v->dir = u;
		p->dir = v->esq;
		v->esq = p;

		p->h -= 2;
		u->h -= 1;
		v->h += 1;

		return v;
	}

	return NULL;
}

Boolean insere_AVL_rec(Arvore_AVL * arvore, No * raiz, No * pai, No * novo, int* contador){

	Boolean r;
	No * rot;

	(*contador)++;
  int cmp = strcmp(novo->valor.palavra, raiz->valor.palavra);

	if(cmp){
		if(cmp < 0){

			if(raiz->esq){

				r = insere_AVL_rec(arvore, raiz->esq, raiz, novo, contador);
				atualiza_altura(raiz);

				if(abs(balanco(raiz)) >= 2) {

					rot = rotacaoL(raiz);

					if(pai){
						if(pai->esq == raiz) pai->esq = rot;
						if(pai->dir == raiz) pai->dir = rot;
					}
					else arvore->raiz = rot;
				}

				return r;
			}
			else {
				raiz->esq = novo;
				if(!raiz->dir) raiz->h = 1;
			}
		}
		else{
			if(raiz->dir){

				r = insere_AVL_rec(arvore, raiz->dir, raiz, novo, contador);
				atualiza_altura(raiz);

				if(abs(balanco(raiz)) >= 2){

					rot = rotacaoR(raiz);

					if(pai){
						if(pai->esq == raiz) pai->esq = rot;
						if(pai->dir == raiz) pai->dir = rot;
					}
					else arvore->raiz = rot;
				}

				return r;
			}
			else {
				raiz->dir = novo;
				if(!raiz->esq) raiz->h = 1;
			}
		}

		return TRUE;
	}

	return FALSE;
}

Boolean insere_AVL(Arvore_AVL * arvore, char* palavra, int linha, int* contador){

	No * novo = (No *) malloc(sizeof(No));

	novo->valor.palavra = malloc(strlen(palavra) + 1);
	novo->valor.ocorrencias = malloc(sizeof(int));

	strcpy(novo->valor.palavra, palavra);
	novo->valor.repeticoes = 1;
	novo->valor.ocorrencias[0] = linha;
	novo->esq = novo->dir = NULL;
	novo->h = 0;

	No * aux = busca_AVL(arvore, palavra, contador);
	if(aux){
		aux->valor.repeticoes++;
		aux->valor.ocorrencias = realloc(aux->valor.ocorrencias, aux->valor.repeticoes * sizeof(int));
		aux->valor.ocorrencias[aux->valor.repeticoes - 1] = linha;
		free(novo->valor.palavra);
		free(novo);
		return TRUE;
	}
	arvore->qtdpalavras++;
	if(arvore->raiz) return insere_AVL_rec(arvore, arvore->raiz, NULL, novo, contador);

	arvore->raiz = novo;
	return TRUE;
}