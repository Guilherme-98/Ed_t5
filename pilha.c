#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct lista{
    ItemPilha *dado;
    struct lista *prox;
    struct lista *ant;
}listaPilha;

typedef struct Pilha{
    struct lista *topo;
    int tamanho;
}pilha;

Pilha iniciar(){
    pilha *stack;

    stack = (pilha *)malloc(sizeof(pilha));
    stack->topo = NULL;
    stack->tamanho = 0;

    return (Pilha)stack;
}

int tamanhoPilha(Pilha *stack){
    pilha *newStack;

    newStack = (pilha*)stack;

    return newStack->tamanho;
}

int pilhaPush(Pilha *stack, ItemPilha *dado){
    listaPilha *Elemento;
    pilha *novaLista;
    listaPilha *aux;
  
    novaLista = (pilha*) stack;

    Elemento = (listaPilha *)malloc(sizeof(listaPilha));
    Elemento->dado = dado;
    Elemento->prox = NULL;
    Elemento->ant = NULL;

    if(novaLista->tamanho == 0){
        novaLista->topo = Elemento;
    }else{
        aux = novaLista->topo;

        aux->prox = Elemento;
        Elemento->ant = aux;
    }
    novaLista->tamanho++;
    novaLista->topo = Elemento;

  return 1;
}

PosicPilha getTopoPilha(Pilha *stack){
    pilha *newStack;
    PosicPilha *p;

    newStack = (pilha *)stack;
    if(newStack->tamanho == 0){
        p = NULL;
    }
    else
        p = (PosicPilha *)newStack->topo;

    return p;
}

ItemPilha pilhaPop(Pilha *stack){
  ItemPilha *i;
  pilha *newStack;
  listaPilha *elemento,*elemento_aux;

  newStack = (pilha *)stack;
  if(newStack->tamanho == 0){
    //Pilha vazia
  }
  else{
    elemento = newStack->topo;
    if(elemento->ant != NULL){
      i = elemento->dado;
      elemento_aux = elemento->ant;
      elemento_aux->prox = NULL;
      newStack->topo = elemento_aux;
    }
    else{
      i = elemento->dado;
    }
    free(elemento);
    elemento = NULL;
    newStack->tamanho--;
  }
  return i;
}

PosicPilha getAnteriorPilha(Pilha *stack,PosicPilha p){
	pilha *newStack;
	PosicPilha *pos;
	listaPilha *aux;

	newStack = (pilha *)stack;
	pos = p;
	aux = (listaPilha *)pos;

	if(aux->ant == NULL){
		pos = NULL;
	}else{
		aux = aux->ant;
		pos = (PosicPilha *)aux;
	}

	return pos;
}

ItemPilha getElementPilha(Pilha *stack,PosicPilha p){
    pilha *newStack;
    listaPilha *elemento;
    PosicPilha *pos;
    ItemPilha *forma;

    newStack = (pilha *)stack;
    if(p == NULL){
        //NULL
    }

	pos = p;
	elemento = (listaPilha *)pos;
	forma = elemento->dado;

	return forma;
}

void liberaPilha(Pilha *stack){
    pilha *newStack;
    listaPilha *novoElemento;

    newStack = (pilha *)stack;

    if(newStack->tamanho != 0){
        novoElemento = newStack->topo;
        free(novoElemento->dado);
        free(novoElemento);
        newStack->tamanho--;
    }
}
