#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct reg {
	char chave;
	int nivel;
	struct reg* esq;
	struct reg* dir;
	struct reg* irmao;
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
int altura;
int qtNosUltimoNivel;

arvore cria_no(char, int);
int calcula_altura_max(int);
arvore construa_arvore(arvore, int);
int percurso_em_largura(arvore);

int main(int argc, char** argv)
{

	int n;
	nivelMax = 0;
	altura = 0;

	while (scanf("%d%*c", &n), n)
	{

		scanf("%[^\n]", entrada);

		k = 0;
		altura = calcula_altura_max(n);
		nivelMax = altura - 1;
		qtNosUltimoNivel = numero_nos_folha(altura, n);
		arvore r = construa_arvore(NULL, 0);

		memset(saida, 0, sizeof saida);

		percurso_em_largura(r);

		printf("%s\n", saida);

	}

	return 0;

}

int calcula_altura_max(int nrNos) {
	//Altura de uma arv.bin.quase completa com n nodos internos: teto((log_2(n + 1)) - https://www.inf.ufpr.br/carmem/ci057/apostila.pdf
	return ceil(log2(nrNos+1));
}

int numero_nos_folha(int altura, int nrNos) {

	int numeroNos = nrNos - (pow(2, altura) - 1);
	if (numeroNos <= 0) {
		numeroNos = nrNos - (pow(2, (altura -1)) - 1);
	}

	return numeroNos;
}

arvore cria_no(char chave, int nivel) {
	arvore no = (arvore)malloc(sizeof(celula));
	no->chave = chave;
	no->nivel = nivel;
	no->esq = NULL;
	no->dir = NULL;
	no->irmao = NULL;
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

void iniciar_fila(arvore *f) {
	*f = cria_no(NULL, -1);
}

void insere_no_irmao(arvore *r, arvore no) {
	arvore _r = *r;
	if (_r == NULL) {
		*r = no;
		return;
	}
	else if (_r -> irmao == NULL) {
		_r->irmao = no;
		*r = _r;
		return;
	}
	_r = _r->irmao;
	insere_no_irmao(&_r,no);
}

void enfileirar(arvore *fila, arvore no) {
	if (no == NULL) {
		return fila;
	}
	arvore _fila = *fila;
	insere_no_irmao(&_fila, no);
	*fila = _fila;

}

int fila_vazia(arvore fila) {
	return fila == NULL;
}

arvore desenfileirar(arvore * fila) {
	arvore no = *fila;
	//no = no->irmao;
	*fila = no->irmao;
	return no;
}

int percurso_em_largura(arvore r) {
	arvore f = NULL;
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
	free(f);
	return 0;
}