/*
**	SERVIDOR DE IMPRESSSAO
**	DOUGLAS RODRIGUES DE ALMEIDA
**
**	Implementacao do TAD Principal do Servidor de Impressao
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hora.h"
#include "list.h"
#include "servidor_arquivo.h"
#include "servidor_relatorio.h"
#include "servidor_usuario.h"
#include "servidor.h"

TServidor* TServidor_Criar(void)
{
	TServidor* NovoServidor;
	TFuncaoDestruir FuncUsuarDestruir;
	TFuncaoIguais FuncUsuarIguais;
	
	FuncUsuarDestruir = &TUsuario_Destruir;
	FuncUsuarIguais = &TUsuario_Iguais;
	NovoServidor = (TServidor*)malloc(sizeof(TServidor));
	NovoServidor->Impressora = NULL;
	NovoServidor->Relatorio = NULL;
	NovoServidor->Usuarios = TLista_Criar(FuncUsuarDestruir, FuncUsuarIguais, NULL);
	
	return NovoServidor;
}

void TServidor_Destruir(TServidor** PServidor)
{
	if ((*PServidor)->Impressora != NULL)
		TImpressora_Destruir(&((*PServidor)->Impressora));
	if ((*PServidor)->Relatorio != NULL)
		TRelatorio_Destruir(&(*PServidor)->Relatorio);
	TLista_Destruir(&(*PServidor)->Usuarios);	
	free(*PServidor);
	PServidor = NULL;
}

bool TServidor_Analisar(TServidor* Servidor)
{
	char buffer[BUFFER_TAMANHO + 1];
	bool encerraanalise;
	
	encerraanalise = false;
	time(&horaatual);
	/* Ler primeira linha com cadastro da impressora */
	if ((fgets(buffer, BUFFER_TAMANHO, Servidor->ArquivoEntrada) != NULL) && (BufferImpressora(Servidor, buffer)))
	{	
		while (!encerraanalise)
		{
			if (fgets(buffer, BUFFER_TAMANHO, Servidor->ArquivoEntrada) != NULL)
			{
				encerraanalise = BufferAnalisar(Servidor, buffer);
				if (Servidor->Impressora->ImpressaoRecebida != NULL)
					TServidor_ProcessarImpressao(Servidor);
			}
		}
		TServidor_FinalizaFila(Servidor);
		TServidor_Relatorio(Servidor);
	}
	else	
	{
		printf("Erro (0x101): Erro ao abrir arquivo de entrada de dados.\n");
		return false;
	}
	
	return true;
}

bool TServidor_CadastrarImpressora(TServidor* Servidor, char* Impressora, int Capacidade, int Escalonador)
{
	Servidor->Impressora = TImpressora_Criar(Capacidade, Escalonador, Impressora);
	if (Servidor->Impressora == NULL)
		return false;
	Servidor->Relatorio = TRelatorio_Criar(Servidor->Impressora->TotalPrioridades);
	
	return true;
}

bool TServidor_ChecarImpressao(TServidor* Servidor, TImpressao* Impressao)
{
	TListaNo* No;
	
	No = TLista_Pesquisar(Servidor->Usuarios, Impressao->Usuario);
	/* somente usuarios cadastrados podem imprimir */
	if (No == NULL)
	{
		Servidor->Relatorio->TotalTarefasRejeitadas++;		
		TImpressao_Destruir((void**)&Impressao);
		
		return false;
	/* prazo estourado, tarefa perdida :( */
	} else if (Impressao->HorarioLimite < horaatual)
	{
		TImpressora_Cancelar(Impressao, Servidor->Relatorio);
		
		return false;
	}
	
	return true;
}

void TServidor_FinalizaFila(TServidor* Servidor)
{
	TImpressao* Impressao;
	
	while (Servidor->Impressora->FilaImpressao->Tamanho > 0)
	{
		Impressao = (TImpressao*)TFilaPrioridade_Desenfileirar(Servidor->Impressora->FilaImpressao);
		if (TServidor_ChecarImpressao(Servidor, Impressao))
		{
			TImpressora_Imprimir(Impressao, Servidor->Relatorio);
			horaatual += (Impressao->Paginas / Servidor->Impressora->Capacidade);
		}
	}
}

void TServidor_Finalizar(TServidor* Servidor)
{
	fclose(Servidor->ArquivoEntrada);
	fclose(Servidor->ArquivoSaida);
}

bool TServidor_Preparar(TServidor* Servidor, const char* NomeArquivoEntrada, const char* NomeArquivoSaida)
{
	Servidor->ArquivoEntrada = fopen(NomeArquivoEntrada , "rt");
	Servidor->ArquivoSaida = fopen(NomeArquivoSaida , "wt");
	
	return ((Servidor->ArquivoEntrada != NULL) && (Servidor->ArquivoSaida != NULL));
}

void TServidor_ProcessarImpressao(TServidor* Servidor)
{
	TImpressao* Impressao;
	
	/* as tarefas que chegaram enquando a impressora estava ocupada sao enfileiradas */
	if (Servidor->Impressora->ImpressaoRecebida->HorarioChegada < horaatual)
	{
		TFilaPrioridade_Enfileirar(Servidor->Impressora->FilaImpressao, Servidor->Impressora->ImpressaoRecebida);
		Servidor->Impressora->ImpressaoRecebida = NULL;
	}
	else
	{
		/* enquanto nao chega tarefa nova, vai desenfileirando a fila */
		while ((Servidor->Impressora->ImpressaoRecebida->HorarioChegada > horaatual) && (Servidor->Impressora->FilaImpressao->Tamanho > 0))
		{
			Impressao = (TImpressao*)TFilaPrioridade_Desenfileirar(Servidor->Impressora->FilaImpressao);
			if (TServidor_ChecarImpressao(Servidor, Impressao))
			{				
				TImpressora_Imprimir(Impressao, Servidor->Relatorio);
				/* imprimiu, entao o tempo anda: tempo gasto para imprimir */
				horaatual += (Impressao->Paginas / Servidor->Impressora->Capacidade);
			}
		}
		/* tarefa que chegou enquanto a impressora estava ocupada sera enfileirada */
		if (Servidor->Impressora->ImpressaoRecebida->HorarioChegada < horaatual)
		{
			TFilaPrioridade_Enfileirar(Servidor->Impressora->FilaImpressao, Servidor->Impressora->ImpressaoRecebida);
			Servidor->Impressora->ImpressaoRecebida = NULL;
		}
		else
		{
			/* a fila estava vazia, entao a impresssora ficara ociosa ate chegar nova tarefa */
			Impressao = Servidor->Impressora->ImpressaoRecebida;
			if (TServidor_ChecarImpressao(Servidor, Impressao))
			{
				/* chegou uma tarefa, hora atual sera a hora da chegada da tarefa */
				horaatual = Impressao->HorarioChegada;
				TImpressora_Imprimir(Impressao, Servidor->Relatorio);
				/* imprimiu, entao o tempo anda: tempo gasto para imprimir */
				horaatual += (Impressao->Paginas / Servidor->Impressora->Capacidade);
			}
			Servidor->Impressora->ImpressaoRecebida = NULL;
		}
	}	
}

void TServidor_RecebeImpressao(TServidor* Servidor, TImpressao* Impressao)
{
	Servidor->Impressora->ImpressaoRecebida = Impressao;
}

void TServidor_Relatorio(TServidor* Servidor)
{
	TRelatorio_Emitir(Servidor->Relatorio, Servidor->ArquivoSaida);		
}

void TServidor_UsuarioExcluir(TServidor* Servidor, const char* Nome)
{
	TListaNo* No;
	TUsuario* Usuario;
	
	Usuario = TUsuario_Criar(Nome, 0);
	No = TLista_Pesquisar(Servidor->Usuarios, Usuario);
	if (No != NULL)
	{
		TLista_Remover(Servidor->Usuarios, No);
		TUsuario_Destruir((void**)&Usuario);
		Servidor->Relatorio->TotalUsuariosRemovidos++;
	}
}

void TServidor_UsuarioNovo(TServidor* Servidor, const char* Nome, const int Prioridade)
{
	TUsuario* Usuario;
	
	Usuario = TUsuario_Criar(Nome, Prioridade);
	if (TLista_Posicao(Servidor->Usuarios, Usuario) == 0)
	{
		TLista_Adicionar(Servidor->Usuarios, Usuario);
		Servidor->Relatorio->TotalUsuariosInseridos++;
	}
}
