#ifndef LEITURA_VIA__H
#define LEITURA_VIA__H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "grafo.h"

/*  
*   realiza toda a leitura do arquivo .via
*   necessita de um arquivo .via
*   nao retorna nada
*/
void Ler_arquivo_via(FILE *via, Grafo caminhos);

#endif