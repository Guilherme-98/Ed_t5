#ifndef _LEITURA_PM_H_
#define _LEITURA_PM_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h> 

/*
 * Lê um arquivo .pm
 * Necessita do comando pm ter sido invocado
 * Retorna nada
 */
void Ler_arquivo_pm(FILE *e, HashTable pessoas, HashTable quadraTable, HashTable Moradores);

#endif 