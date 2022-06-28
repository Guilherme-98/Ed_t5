#ifndef _ARGUMENTOS_H_
#define _ARQUMENTOS_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h> 

/*
*   verifica se um arquivo abriu corretamente ou apresentou algum erro na abertura.
*   necessita de um arquivo criado
*   nao retorna nada
*/
void verificarArquivo(FILE *arq, char *nomeArquivo);

/*
*   verifica o nome dos arquivos .geo e .qry
*   necessita de um arquivo .geo ou .qry terem sido identificados
*   retorna o nome do arquivo pós tratamento
*/ 
char *tratarNome(char nomeArq[], char * nomeArqAux);

#endif 