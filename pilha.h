#ifndef PILHA_H
#define PILHA_H
#include "lista.h"

//TAD pilha
typedef void* Pilha;

// ItemPilha é um item da pilha
typedef void* ItemPilha;

//PosicPilha é um nó que aponta para uma determinada posição da pilha
typedef void* PosicPilha;

/*
*   Não necessita de nada
*   Inicializa uma pilha
*/
Pilha iniciar();

/*
*   Necessita de uma pilha e de um elemento que sera colocado na pilha
*   Adciona um eleemnto na pilha 
*   Retorna 1 caso tenha adcionado com sucesso na pilha
*/
int pilhaPush(Pilha *stack, Elemento *dado);

/*
*   Necessita de uma pilha 
*   Retorna o elemento que estiver no topo da pilha
*/
PosicPilha getTopoPilha(Pilha *stack);

/*
*   Necessita de uma pilha 
*   Remove o elemento da pilha 
*/
PosicPilha pilhaPop(Pilha *stack);

/*
*   Necessita de uma pilha e de um nó que aponta para uma determinada posição da pilha
*   Retorna o elemento anterior do nó passado como paramentro ns função
*/
PosicPilha getAnteriorPilha(Pilha *stack, PosicPilha p);

/*
*   Necessita de uma pilha e de um nó que aponta para uma determinada posição da pilha
*   Retorna o elemento passado como paramentro ns função
*/
ItemPilha getElementPilha(Pilha *stack, PosicPilha p);

/*
*   Necessita de uma pilha 
*   Libera toda a memoria utilizada pela pilha
*/
void liberaPilha(Pilha *stack);

/*
*   Necessita de uma pilha 
*   Retorna o tamanho atual da pilha
*/
int tamanhoPilha(Pilha *stack);

#endif
