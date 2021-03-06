/*
**	BIBLIOTECA DO FILIPE
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Estrutura de dados das consultas do sistema
*/

#ifndef SISTEMA_CONSULTA_H
#define SISTEMA_CONSULTA_H

typedef struct _TSistemaConsulta {
	char Conteudo[51];
} TSistemaConsulta;

TSistemaConsulta* TSistemaConsulta_Criar(char* Consulta);

void TSistemaConsulta_Destruir(void** PConsulta);

void TSistemaConsulta_SalvarNoArquivo(TSistemaConsulta* Consulta);

#endif
