CC = gcc
COMPILER_FLAGS = -std=c99 -fstack-protector-all -g
LINKER_FLAGS = -lm 
EXEC_NAME = siguel
OBJECTS = main.o argumentos.o arquivos.o leitura_geo.o svg.o leitura_gry.o consultas.o util.o elementos/quadra.o lista.o  elementos/texto.o  elementos/hidrante.o elementos/semaforo.o elementos/radioBase.o elementos/forma.o elementos/posto.o elementos/casos.o elementos/casosDentro.o elementos/vertice.o shell_sort.o quick_sort.o quadTree.o pessoa.o comercio.o hashTable.o tipoComercio.o moradores.o leitura_ec.o leitura_pm.o moradores_qry.o comercio_qry.o ponto.o tipoComercio_qry.o svg_qry.o pilha.o vetor.o ordenacao.o grafo.o prioridade_fila.o leitura_via.o qry_via.o hashFile.o

all: $(EXEC_NAME)
$(OBJECTS): %.o : %.c
		gcc -g -c $< -o $@

siguel: $(OBJECTS) 
		$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

clean:
		rm -rf *.o siguel 
		rm -rf saida/*.txt
		rm -rf saida/*.svg
