#ifndef TIPOCOMERCIO_H
#define TIPOCOMERCIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TAD TIPO DE COMERCIO
typedef void *TipoComercio;

/*
*   Cria uma entidade tipo de comercio com os parametros passados
*   Necessita do comando de criar um tipo de comercio ter sido invocado
*   Retorna um tipo de comercio
*/
TipoComercio criarTipoComercio (char codt[], char descricao[]);

/*
*   Retorna o codt do tipo de um comercio
*/
char* getTipoComercioCodt (TipoComercio sType);

/*
*   Retorna a descrição de um tipo de comercio
*/
char* getTipoComercioDesc (TipoComercio sType);

#endif