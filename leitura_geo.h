#ifndef _LEITURA_GEO_H_
#define _LEITURA_GEO_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h> 
#include"lista.h"
#include"quadTree.h"
#include"hashTable.h"

double densidadeQuadra;
double x_dd, y_dd, w_dd, h_dd;
/*
*   Função que realiza a leitura do arquivo .geo 
*   necessita de um arquivo .geo, e das arvores de objetos, formas e texto
*   nao retorna nada
*/
void Ler_arquivo_geo(FILE *geo, Tree arvoreForma, Tree arvoreTexto, Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase, Tree arvorePosto,
                    HashTable quadraTable, HashTable hidranteTable, HashTable semaforosTable, HashTable radioBasesTable);

#endif 