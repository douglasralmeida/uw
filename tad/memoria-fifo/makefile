#TIPO ABSTRATO DE DADOS MEMORIA
#DOUGLAS RODRIGUES DE ALMEIDA
#
#Makefile do TAD Memoria

PROJECTNAME=test-memoria
ARGS=
CC=gcc

#Flags do compilador
CFLAGS=-c -Wall -Wextra -Wpedantic $(DEFS) -I../core/ -Iinclude/
DBGFLAGS=-ggdb -fno-inline -fno-omit-frame-pointer 
LDFLAGS=

#Diretorios do projeto
BINDIR=bin
OBJDIR=obj
SOURCEDIR=src
TESTDIR=test

#Arquivos do projeto
OBJFILES=memoria.o test-memoria.o
OBJECTS=$(addprefix $(OBJDIR)/, $(OBJFILES))

#Compilar o codigo
$(OBJDIR)/%.o: $(SOURCEDIR)/%.c
	@echo 
	@echo Compilando $<...
	$(CC) $(DBGFLAGS) $(CFLAGS) $< -o $@

#Gerar executavel
$(PROJECTNAME): $(OBJECTS) 
	@echo 
	@echo Gerando executavel...
	$(CC) $(LDFLAGS) -o $(BINDIR)/$@ $^ $(LIBS)

#Regra padrao
.PHONY: all
all:
	$(PROJECTNAME)

#Limpar arquivos
.PHONY: clean
clean:
	@echo 
	@echo Excluindo executavel...
	rm -f $(BINDIR)/$(PROJECTNAME)
	@echo Excluindo objetos...
	rm -f $(OBJECTS)

#Depuracao
.PHONY: debug	
debug:
	gdb --args ./$(BINDIR)/$(PROJECTNAME) $(ARGS)

#Checar vazamentos de memoria
.PHONY: memcheck
memcheck:
	valgrind -v --leak-check=full --track-origins=yes --show-leak-kinds=all $(BINDIR)/$(PROJECTNAME) $(ARGS)

#Executar aplicacao
.PHONY: run
run:
	./$(BINDIR)/$(PROJECTNAME) $(ARGS)
