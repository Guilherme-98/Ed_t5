#ifndef _LEITURA_EC_H_
#define _LEITURA_EC_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h> 

/*
 * Lê um arquivo .ec
 * Necessita do comando ec ter sido invocado
 * Retorna nada
 */
void Ler_arquivo_ec(FILE *ec, HashTable tipoComercio, HashTable comercios, HashTable pessoas, HashTable quadraTable);

#endif 