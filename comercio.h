#ifndef COMERCIO__H
#define COMERCIO__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashTable.h"
#include "./elementos/quadra.h"
#include "tipoComercio.h"
#include "pessoa.h"

//TAD COMERCIO
typedef void *Comercio;

/*
 * Cria a estrutura comercio
 * Necessita do comando de comercio ser invocado
 * Retorna um comercio
 */
Comercio criarComercio (char cnpj[], char cpf[], char codt[], char cep[], char face[], int num, char nome[], HashTable tipoLoja, HashTable pessoas, Quadra quadra);

/*
 * Retorna o cnpj de um comercio
 * Necessita de um comercio existente
 * Retorna o cnpj de um comercio
 */
char* getComercioCnpj (Comercio s);

/*
 * Retorna o dono de um comercio
 * Necessita de um comercio existente
 * Retorna o dono de um comercio
 */
char* getComercioOwner (Comercio s);

/*
 * Retorna o cep de um comercio
 * Necessita de um comercio existente
 * Retorna o cep de um comercio
 */
char* getComercioCep (Comercio s);

/*
 * Retorna a face de um comercio
 * Necessita de um comercio existente
 * Retorna a face de um comercio
 */
char* getComercioFace (Comercio s);

/*
 * Retorna o nome de um comercio
 * Necessita de um comercio existente
 * Retorna o nome de um comercio
 */
char* getComercioName (Comercio s);

/*
 * Retorna o numero de um comercio
 * Necessita de um comercio existente
 * Retorna o numero de um comercio
 */
int getComercioNum (Comercio s);

/*
 * Retorna o codt de um comercio
 * Necessita de um comercio existente
 * Retorna o codt de um comercio
 */
char* getComercioCodt (Comercio s);

/*
 * Retorna o x de um comercio
 * Necessita de um comercio existente
 * Retorna o x de um comercio
 */
double getComercioX(Comercio s);

/*
 * Retorna o y de um comercio
 * Necessita de um comercio existente
 * Retorna o y de um comercio
 */
double getComercioY(Comercio s);

/*
 * Retorna o tipo de um comercio
 * Necessita de um comercio existente
 * Retorna o tipo de um comercio
 */
TipoComercio getComercioType(Comercio s);

/*
 * Da free num comercio
 * Necessita de um comercio existente
 * Retorna nada
 */
void destroiComercio(Comercio s);

#endif