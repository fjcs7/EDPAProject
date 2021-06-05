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

char saida[SIZ];
char entrada[SIZ];

int nivelMax;
int altura;
int qtNosUltimoNivel;

arvore cria_no(char, int);
int calcula_altura_max(int);
arvore construa_arvore(arvore, int);
void percurso_em_largura_rec(arvore, int);

int main(int argc, char** argv)
{

	int n;

	while (scanf("%d%*c", &n), n)
	{

		scanf("%[^\n]", entrada);

		k = 0;
		///* Variáveis de acesso global*/	
		altura = calcula_altura_max(n);
		nivelMax = altura - 1;
		qtNosUltimoNivel = numero_nos_folha(altura, n);

		///* Constrói árvore com os nós passados na entrada*/	
		arvore r = construa_arvore(NULL, 0);

		memset(saida, 0, sizeof saida);

		//percurso_em_largura(r);

		percurso_em_largura_rec(r, 1);

		printf("%s\n", saida);

	}

	return 0;

}

int calcula_altura_max(int nrNos) {
	///*Altura de uma arv.bin.quase completa com n nodos internos: teto((log_2(n + 1)) - https://www.inf.ufpr.br/carmem/ci057/apostila.pdf */
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

void percurso_em_largura_rec(arvore r, int posicaoNode) {

	if (r == NULL) {
		return 0;
	}
	saida[posicaoNode-1] = r->chave;

	percurso_em_largura_rec(r->esq, 2 * posicaoNode);
	percurso_em_largura_rec(r->dir, 2 * posicaoNode + 1);
}