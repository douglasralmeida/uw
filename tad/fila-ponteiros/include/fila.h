/*
 *	TIPO ABSTRATO DE DADOS FILA
 *	DOUGLAS RODRIGUES DE ALMEIDA
 *
 *	Cabecalho e estruturas de uma fila
 */

#ifndef FILA_H
#define FILA_H

#include "core.h"

/* Estrutura do no da fila */
typedef struct _TFilaNo TFilaNo;

struct _TFilaNo {
	void* Item;		/* Guarda o item da fila */
	TFilaNo* Proximo;	/* Aponta para o prox. no da fila */
};

/* Estrutura da fila */
typedef struct _TFila {
	TFilaNo* Frente;	/* Primeiro no da fila */
	size_t Tamanho;		/* Tamanho da fila */
	TFilaNo* Tras;		/* Ultimo no da fila */
} TFila;

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Criar
 * 			Cria uma fila vazia
 * @param:		(vazio)
 * @retorna:		A fila alocada
 *---------------------------------------------------------------------------*/ 
TFila* TFila_Criar();

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Destruir
 * 			Destroi a fila
 * @param:		Fila
 * @param:		Funcao que destroi um item da fila
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TFila_Destruir(TFila** PFila, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Desenfileirar
 * 			Remove e retorna o proximo item da fila
 * @param:		Fila
 * @retorna:		O item removido
 *---------------------------------------------------------------------------*/ 
void* TFila_Desenfileirar(TFila* Fila);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Enfileirar
 * 			Insere um item no final da fila
 * @param:		Fila
 * @param:		Item a ser inserido
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
bool TFila_Enfileirar(TFila* Fila, void* Item);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Imprimir
 * 			Imprime a fila na tela
 * @param:		Fila
 * @param:		Funcao que imprime um item da fila
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TFila_Imprimir(TFila* Fila, TFuncaoImprimir FuncaoImprimir);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Limpar
 * 			Remove todos os itens da fila
 * @param:		Fila
 * @param:		Funcao que destroi um item da fila
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/ 
void TFila_Limpar(TFila* Fila, TFuncaoDestruir FuncaoDestruir);

/* ----------------------------------------------------------------------------
 * funcao:		TFila_Tamanho
 * 			Retorna o quantidade de itens da fila
 * @param:		Fila
 * @retorna:		Inteiro com o tamanho
 *---------------------------------------------------------------------------*/ 
size_t TFila_Tamanho(TFila* Fila);

#endif
