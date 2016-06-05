#ifndef SERVIDOR_ARQUIVO_H
#define SERVIDOR_ARQUIVO_H

#include <stdlib.h>
#include "servidor.h"

#define CMD_USUARIONOVO 1
#define CMD_USUARIOEXCLUIR 2
#define CMD_RELATORIO 3
#define CMD_IMPRIMIR 4
#define CMD_SAIR 5

int BufferAnalisar(TServidor* Servidor, char* Buffer);

bool BufferImpressora(TServidor* Servidor, char* Buffer);

#endif
