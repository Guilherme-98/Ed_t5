#ifndef COMERCIO_QRY__H
#define COMERCIO_QRY__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "comercio.h"
#include "pessoa.h"
#include "tipoComercio.h"
#include "hashTable.h"

/*
 * Comando informa as informações de um comercio de cnpj dado
 * Necessita do comando de ter sido invocado
 * Retorna nada
 */
void consulta_de(char cnpj[], HashTable comercios, FILE* arq);

#endif