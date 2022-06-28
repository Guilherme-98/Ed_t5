#ifndef HASHTABLE__H
#define HASHTABLE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//TAD HASTABLE
typedef void *HashTable;
//TAD LISTA DE NÓS
typedef void *ListNode;
//TAD COM ELEMENTOS
typedef void *Element;

/*
 * Retorna o tamanho da hashtable
 * Necessita de uma hashtable criada
 */
int getHashTableSize(HashTable h);

/*
 * Retorna o node de uma hashtable
 * Necessita de uma hashtable criada
 */
ListNode getHashNode(HashTable h, int i);

/*
 * Retorna o proximo node de uma hastable
 * Necessita de uma hastable criada
 */
ListNode getHashNodeNext(ListNode n);

/*
 * Retorna o elemento de um node da hastable
 * Necessita de uma hastable criada
 */
Element getHashNodeElement(ListNode n);

/* Cria e retorna uma tabela de espalhamento
 * Necessita do tamanho da hashtable
 */
HashTable createHashTable(int size, void (*destroy)(Element));

/*Insere element na tabela h com a chave key. Retorna true caso insira, false caso contrario*/
bool insertHashTable(HashTable h, char *key, Element element);

/*Remove o no que tenha a chave key da tabela h. Retorna 1 caso remova, false caso contrario*/
bool removeHashTable(HashTable h, char *key);

/*Busca e retorna o elemento armazenado na tabela h cuja chave seja key*/
Element searchHashTable(HashTable h, char *key);

/*Libera a memoria usada pela tabela de espalhamento*/
void destroiHashTable(HashTable h);

#endif