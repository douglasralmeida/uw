/*
**	TIPO ABASTRATO DE DADOS GRAFO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Cabeçalho e estruturas de grafo implementado com listas de adjacdência usando vetores
**	
**/

#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include "boolutils.h"
#include "list.h"
#include "grafo_item.h"

/* Estrutura da grafo */
typedef struct _TGrafo {
	TLista** Adjacencias;
	size_t NumVertices;
	TListaNo PesquisaProxNo;
} TGrafo;

/* ----------------------------------------------------------------------------
 * funcao:		TGrafo_Criar
 * 			Cria um grafo
 * @param:		Quantidade de vertices do grafo
 * @retorna:		O grafo alocado
 *---------------------------------------------------------------------------*/
TGrafo* TGrafo_Criar(size_t NumVertices);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafo_Destruir
 * 			Destroi o grafo
 * @param:		Grafo
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TGrafo_Destruir(TGrafo** PGrafo);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafo_ArestaInserir
 * 			Adiciona uma aresta a dois vertices do grafo
 * @param:		Grafo
 * @param:		Vertice de origem
 * @param:		Vertice de destino
 * @param:		Peso da aresta
 * @retorna:		True em caso de insercao com sucesso, ou false em caso de falha
 *---------------------------------------------------------------------------*/
bool TGrafo_ArestaInserir(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino, TGrafoPeso Peso);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafo_ArestaExiste
 * 			Verifica a existência de aresta entre dois vertices
 * @param:		Grafo
 * @param:		Vertice de origem
 * @param:		Vertice de destino
 * @retorna:		True em caso positivo, ou false em caso negativo
 *---------------------------------------------------------------------------*/
bool TGrafo_ArestaExiste(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafo_ArestaRemover
 * 			Remove uma aresta entre dois vertices
 * @param:		Grafo
 * @param:		Vertice de origem
 * @param:		Vertice de destino
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TGrafo_ArestaRemover(TGrafo* Grafo, TGrafoVertice VOrigem, TGrafoVertice VDestino);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafo_DistanciaMinima
 * 			Retorna o valor da distancia minima entre dois vertices do grafo
 * @param:		Grafo
 * @param:		Vertice de origem
 * @param:		Vertice de destino
 * @retorna:		Valor da distancia. Retorna -1 em caso de caminho inexistente
 *---------------------------------------------------------------------------*/
int TGrafo_DistanciaMinima(TGrafo* Grafo, TGrafoVertice Origem, TGrafoVertice Destino);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafo_Imprimir
 * 			Imprime um grafo na tela
 * @param:		Grafo
 * @retorna:		(vazio)
 *---------------------------------------------------------------------------*/
void TGrafo_Imprimir(TGrafo* Grafo);

/* funcoes para obter a lista de adjacencias */

/* ----------------------------------------------------------------------------
 * funcao:		TGrafo_ListaAdjVazia
 * 			Verifica se um vertice possui lista de adjacencias
 * @param:		Grafo
 * @retorna:		True em caso de lista vazia, false em caso contrario
 *---------------------------------------------------------------------------*/
bool TGrafo_ListaAdjVazia(TGrafo* Grafo, TGrafoVertice Vertice);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafo_ListaAdjPrimeiro
 * 			Retorna a primeira aresta da lista de adjacencias de um vertice
 * @param:		Grafo
 * @param:		Vertice
 * @retorna:		Aresta
 *---------------------------------------------------------------------------*/
TGrafoAresta* TGrafo_ListaAdjPrimeiro(TGrafo* Grafo, TGrafoVertice Vertice);

/* ----------------------------------------------------------------------------
 * funcao:		TGrafo_ListaAdjProximo
 * 			Retorna a proxima aresta da lista de adjacencias de um vertice
 * @param:		Grafo
 * @param:		Vertice
 * @retorna:		Proxima aresta ou retorna nulo no caso de final da lista
 *---------------------------------------------------------------------------*/
TGrafoAresta* TGrafo_ListaAdjProximo(TGrafo* Grafo, TGrafoVertice Vertice);

#endif
