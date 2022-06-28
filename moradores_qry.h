#ifndef MORADORES_QRY__H
#define MORADORES_QRY__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pessoa.h"
#include "moradores.h"
#include "hashTable.h"
#include "svg.h"


/*
 * Realiza a consulta do comando m
 * Necessita do comando m ter sido chamado
 * Retorna nada
 */
void consulta_m (FILE *arqTxt, HashTable residents, char cep[]);

/*
 * Realiza a consulta do comando dm
 * Necessita do comando dm ter sido chamado
 * Retorna nada
 */
void consulta_dm(char *cpf, HashTable moradores, FILE *arqTxt, FILE *arqSvg);

/*
 * Realiza a consulta do comando mud
 * Necessita do comando mud ter sido chamado
 * Retorna nada
 */
void consulta_mud(FILE *arqTxt, FILE *arqSvg, HashTable moradores, char cpf[], char cep[], char face[], int num, char compl[], Tree arvoreQuadra);

#endif