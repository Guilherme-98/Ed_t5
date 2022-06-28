#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"

typedef void *Element;
typedef void *Queue;

Queue criarFilaPrioridade();

int getTamanhoFilaPrioridade(Queue q);

void inserirFilaPrioridade(Queue q, Element element);

Element removerFilaPrioridade(Queue q);

void inserirPrioridade(Queue q, Element element);

Element removerPrioridade(Queue q);

#endif