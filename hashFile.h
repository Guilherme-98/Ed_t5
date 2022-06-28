#ifndef __HASHFILE__
#define __HASHFILE__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "lista.h"

//TAD Hashfile
typedef void *Hashfile;

#define NUM_BALDES 10           // deve ser proximo da quantidade de registros
#define MAX_REGS_BALDE 4    // deve ser o maximo que cabe em um bloco de FS
#define SIZE_TRASH 16             // deve completar o balde para ficar do tamanho do bloco

/*
*   Cria um novo arquivo segundo o path "nome"
*   Abre arquivo existente para escrita e leitura.
*/
Hashfile fcreateHF(char * fileName);

/*
*   Escreve o registro no arquivo.
*   A key do registro deve estar no início 
*   Retorna 0, se ok;
*/
int  fwriteRec(char * fileName, int key, int value);

/*
*   Retorna o registro cuja key é "key"
*   Deve ter a capacidade especificada na criação do arquivo
*   Retorna 0, se o registro foi encontrado e lido
*/
int freadHF(char * fileName, int key, int limit, Lista **resultList);

#endif