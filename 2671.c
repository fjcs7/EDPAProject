#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct reg {
	char chave;
	int nivel;
	struct reg* esq;
	struct reg* dir;
} celula;

typedef celula* arvore;

#define true 1
#define false 0
#define SIZ 250

int k;
int a;
int tamanhoAtual;
int proxFila;
char saida[SIZ];
char entrada[SIZ];
int nivelMax;
int qtNosUltimoNivel;

arvore cria_no(char, int);
int calcula_altura_max(int);
arvore construa_arvore(arvore, int);
void percurso_em_largura(arvore);

int main(int argc, char** argv)
{

	int n;
	nivelMax = 0;

	while (scanf("%d%*c", &n), n)
	{

		scanf("%[^\n]", entrada);

		k = 0;
		nivelMax = calcula_altura_max(n);
		qtNosUltimoNivel = numero_nos_folha(nivelMax, n);
		arvore r = construa_arvore(NULL, 0);

		percurso_em_largura(r);

		printf("%s\n", saida);

	}

	return 0;

}

int calcula_altura_max(int nrNos) {
	return ceil(log2(nrNos));
}

int numero_nos_folha(int altura, int nrNos) {

	int nivelAnterior = 0;
	if (altura > 0) {
		nivelAnterior = altura - 1;
	}

	return nrNos - (pow(2, altura) - 1);
}

arvore cria_no(char chave, int nivel) {
	arvore no = (arvore)malloc(sizeof(celula));
	no->chave = chave;
	no->nivel = nivel;
	no->esq = NULL;
	no->dir = NULL;
	return no;
}

arvore construa_arvore(arvore _no, int nivel) {

	arvore no = _no;
	if (nivel > nivelMax || nivel == nivelMax && qtNosUltimoNivel == 0) {
		return NULL;
	}

	if (nivel == nivelMax) {
		qtNosUltimoNivel--;
	}

	if (no == NULL) {
		no = cria_no(NULL, nivel);
	}

	if (no->esq == NULL) {
		no->esq = construa_arvore(no->esq, nivel + 1);
	}

	if (no->chave == NULL) {
		no->chave = entrada[k++];
	}

	if (no->dir == NULL) {
		no->dir = construa_arvore(no->dir, nivel + 1);
	}

	return no;
}

void iniciar_fila(arvore* f) {
	tamanhoAtual = 0;
	proxFila = 0;
	f = (arvore)malloc(sizeof(celula)*(k+1));
}

void enfileirar(arvore* fila, arvore no) {
	if (no == NULL) {
		return;
	}
	fila[tamanhoAtual++] = no;
}

int fila_vazia(arvore* fila) {
	return proxFila == tamanhoAtual;
}

arvore desenfileirar(arvore* fila) {
	arvore no = fila[proxFila];
	//fila[proxFila] = NULL;
	proxFila++;
	return no;
}

void percurso_em_largura(arvore r) {
	arvore* f;
	iniciar_fila(&f);
	enfileirar(&f, r);
	a = 0;
	
	while (!fila_vazia(f)) {
		r = desenfileirar(&f);
		if (r) {
			enfileirar(&f, r->esq);
			enfileirar(&f, r->dir);
			saida[a++] = r->chave; /* visita raiz */
		}
	}
}