/*
 *	TIPO ABSTRATO DE DADOS ARVORE B
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabeçalhos e estruturas de uma arvore b
 */

#ifndef ARVOREB_H
#define ARVOREB_H

#include "core.h"

/* Estrutura do nó da arvore */
typedef struct _TArvoreBNo* TArvoreBNo;

struct _TArvoreBNo {
	unsigned short Contador;
	void** Itens;
	TArvoreBNo* Subarvores;
};

typedef struct _TArvoreB {
	TFuncaoComparar FuncaoComparar;
	TFuncaoIguais FuncaoIguais;
	unsigned short Ordem;
	TArvoreBNo Raiz;
} TArvoreB;

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreB_Criar
 * 			Cria uma arvore vazia
 * @param:		Ordem da arvora a ser criada
 * @retorna:		A arvore alocada
 *---------------------------------------------------------------------------*/ 
TArvoreB* TArvoreB_Criar(unsigned short Ordem);

/* ----------------------------------------------------------------------------
 * funcao:		TArvoreB_Destruir
 * 			Destroi a arvore
 * @param:		Arvore
 * @param:		Funcao que destroi cada item da folha da árvore
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TArvoreB_Destruir(TArvoreB** PArvore, TFuncaoDestruir FuncaoDestruir);

void TArvoreB_Inserir(TArvoreB* Arvore, void* Item);

void TArvoreB_Imprimir(TArvoreB* Arvore, TFuncaoImprimir FuncaoImprimir);

void* TArvoreB_Pesquisar(TArvoreB* Arvore, void* Item);
#endif
