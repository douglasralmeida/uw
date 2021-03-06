/*
**	ITEM DE UM TAD LISTA
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao do item do TAD Lista para lista de inteiros
**	
**/

#include "item.h"

void TListaItem_Imprimir(TListaItem* Item)
{
	printf("%d", Item->Valor);
}

bool TListaItem_SalvarNoArquivo(TListaItem* Item, FILE* Arquivo)
{
	return (fprintf(Arquivo, "%d", Item->Valor) >= 0);
}
