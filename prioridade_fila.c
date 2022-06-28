#include "prioridade_fila.h"

typedef struct qNodeSt{
	Element element;
	struct qNodeSt *next;
} *qNodeImp;

typedef struct queueSt{
	qNodeImp first;
	qNodeImp last;
	int size;
} *queueImp;

Queue criarFilaPrioridade(){
	queueImp queue = (queueImp) malloc(sizeof(struct queueSt));
	queue->first = NULL;
	queue->last = NULL;
	queue->size = 0;

	return queue;
}

int getTamanhoFilaPrioridade(Queue q){
    queueImp queue = (queueImp) q;

    return queue->size;
}

void inserirFilaPrioridade(Queue q, Element element){
    queueImp queue = (queueImp) q;

	qNodeImp node = (qNodeImp) malloc(sizeof(struct qNodeSt));
	node->element = element;
	node->next = NULL;

	if(queue->size == 0){
		queue->first = node;
		queue->last = node;
	}
	else{
		queue->last->next = node;
		queue->last = node;
	}

	queue->size++;
}

Element removerFilaPrioridade(Queue q){
    queueImp queue = (queueImp) q;

	if(queue->size == 0) return NULL;

	qNodeImp aux = queue->first;

	Element element = queue->first->element;
	queue->first = queue->first->next;
	queue->size--;

	free(aux);

	return element;
}

void inserirPrioridade(Queue q, Element element){
    queueImp queue = (queueImp) q;

	qNodeImp node = (qNodeImp) malloc(sizeof(struct qNodeSt));
	node->element = element;
	node->next = NULL;

	if(queue->size == 0){
		queue->first = node;
		queue->last = node;
	}
	else{
		qNodeImp aux = queue->first;
		qNodeImp auxAnt = NULL;

		while(aux != NULL && getVerticeDistGrafo(aux->element) <= getVerticeDistGrafo(element)){
			auxAnt = aux;
			aux = aux->next;
		}

		if(auxAnt == NULL){
			node->next = queue->first;
			queue->first = node;
		}
		else if(queue->last == aux){
			queue->last->next = node;
			queue->last = node;
		}
		else{
			auxAnt->next = node;
			node->next = aux;
		}
	}

	queue->size++;
}

Element removerPrioridade(Queue q){
    queueImp queue = (queueImp) q;

	if(queue->size == 0) return NULL;

	qNodeImp aux = queue->first;
	qNodeImp auxAnt = NULL;
	qNodeImp menor = queue->first;
	Element element;

	while(aux != NULL){
		if(getVerticeDistGrafo(menor->element) <= getVerticeDistGrafo(aux->element))
			menor = aux;
		aux = aux->next;
	}

	aux = queue->first;
	while(aux != menor){
		auxAnt = aux;
		aux = aux->next;
	}

	if(menor == queue->first){
		element = queue->first->element;
		queue->first = queue->first->next;
	}
	else if(menor == queue->last){
		element = queue->last->element;
		queue->last = auxAnt;
		auxAnt->next = NULL;
	}
	else{
		element = menor->element;
		auxAnt->next = aux->next;
	}

	queue->size--;
	free(aux);

	return element;
}