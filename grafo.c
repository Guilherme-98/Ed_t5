#include "grafo.h"
#include"prioridade_fila.h"
#include"elementos/forma.h"

enum {WHITE, GREY, BLACK};
typedef struct gNodeSt *gNodeImp;

typedef struct gVerticeSt{
	char id[32];
	double x, y;
	int color;
	int dist;
	struct gVerticeSt *p;
	gNodeImp node;
} *gVerticeImp;

typedef struct arestaSt{
	gVerticeImp source, destiny;
	char rua[32];
	char lDireito[32];
	char lEsquerto[32];
	double comprimento;
	double velocidade;
} *arestaImp;

typedef struct gNodeSt{
	gVerticeImp vertice;
	arestaImp aresta;
	struct gNodeSt *next;
} *gNodeImp;

typedef struct grafoSt{
	int nVertices;
	gNodeImp *verticees;
	int free;
} *grafoImp;

Grafo criarGrafo(int size){
	grafoImp grafo = (grafoImp) malloc(sizeof(struct grafoSt));

	grafo->nVertices = size;
	grafo->verticees = (gNodeImp*) malloc(size * sizeof(gNodeImp));
	memset(grafo->verticees, 0, size * sizeof(gNodeImp));
	grafo->free = 0;

	return grafo;
}

double getVerticeDistGrafo(GNode n){
	gNodeImp node = (gNodeImp) n;

	return node->vertice->dist;
}

int getFreeGrafo(Grafo g){
	grafoImp grafo = (grafoImp) g;

	return grafo->free;
}

GNode getNodeGrafo(Grafo g, int i){
	grafoImp grafo = (grafoImp) g;

	return grafo->verticees[i];
}

char *getNodeIdGrafo(GNode n){
	gNodeImp node = (gNodeImp) n;

	return node->vertice->id;
}

double getNodeXGrafo(GNode n){
	gNodeImp node = (gNodeImp) n;

	return node->vertice->x;
}

double getNodeYGrafo(GNode n){
	gNodeImp node = (gNodeImp) n;

	return node->vertice->y;
}

GVertice getNodePGrafo(GNode n){
	gNodeImp node = (gNodeImp) n;

	return node->vertice->p;
}

double getVerticeXGrafo(GVertice v){
	gVerticeImp vertice = (gVerticeImp) v;

	return vertice->x;
}

GNode getVerticeNodeGrafo(GVertice v){
	gVerticeImp vertice = (gVerticeImp) v;

	return vertice->node;
}

double getVerticeYGrafo(GVertice v){
	gVerticeImp vertice = (gVerticeImp) v;

	return vertice->y;
}

bool addVertice(Grafo g, char *id, double x, double y){
    grafoImp grafo = (grafoImp) g;

	if(grafo->free >= grafo->nVertices) return false;

	gVerticeImp vertice = (gVerticeImp ) malloc(sizeof(struct gVerticeSt));
	strcpy(vertice->id, id);
	vertice->x = x;
	vertice->y = y;

	gNodeImp node = (gNodeImp) malloc(sizeof(struct gNodeSt));
	node->vertice = vertice;
	node->aresta = NULL;
	node->next = NULL;
	vertice->node = node;

	grafo->verticees[grafo->free] = node;
	grafo->free++;

	return true;
}

bool addAresta(Grafo g, char *id1, char *id2, char *rua, char *bR, char *bL, double comprimento, double velocidade){
    grafoImp grafo = (grafoImp) g;
	gVerticeImp v1 = NULL, v2 = NULL;
	gNodeImp n;

	for(int i = 0; i < grafo->free; i++){
		if(!strcmp(id1, grafo->verticees[i]->vertice->id)){
			n = grafo->verticees[i];
			v1 = n->vertice;
		}
		if(!strcmp(id2, grafo->verticees[i]->vertice->id))
			v2 = grafo->verticees[i]->vertice;

        if(v1 != NULL && v2 != NULL) break;
	}

	if(v1 == NULL || v2 == NULL) return false;

	arestaImp aresta = (arestaImp) malloc(sizeof(struct arestaSt));
	aresta->source = v1;
	aresta->destiny = v2;
	strcpy(aresta->rua, rua);
	strcpy(aresta->lDireito, bR);
	strcpy(aresta->lEsquerto, bL);
	aresta->comprimento = comprimento;
	aresta->velocidade = velocidade;

	gNodeImp newNode = (gNodeImp) malloc(sizeof(struct gNodeSt));
	newNode->vertice = v2;
	newNode->aresta = aresta;
	newNode->next = NULL;

	while(n->next != NULL)
		n = n->next;

	n->next = newNode;

	return true;
}

void depthSearch_Aux(grafoImp grafo, gNodeImp u, int cont){
	u->vertice->color = GREY;
	u->vertice->dist = cont;

	for(gNodeImp v = u->next; v != NULL; v = v->next){
		if(v->vertice->color == WHITE){
			v->vertice->p = u->vertice;
			depthSearch_Aux(grafo, v->vertice->node, cont + 1);
		}
	}

	u->vertice->color = BLACK;
}

bool depthSearch(Grafo g, char *id){
	grafoImp grafo = (grafoImp) g;
	gNodeImp start = NULL;

	for(int i = 0; i < grafo->free; i++){
		if(!strcmp(grafo->verticees[i]->vertice->id, id)){
			start = grafo->verticees[i];
			break;
		}
	}

	if(start == NULL) return false;

	for(int i = 0; i < grafo->free; i++){
		grafo->verticees[i]->vertice->color = WHITE;
		grafo->verticees[i]->vertice->dist = -1;
		grafo->verticees[i]->vertice->p = NULL;

	}

	int cont = 0;
	depthSearch_Aux(grafo, start, cont);

	return true;
}

bool widthSearch(Grafo g, char *id){
	grafoImp grafo = (grafoImp) g;
	gNodeImp start = NULL;

	for(int i = 0; i < grafo->free; i++){
		if(!strcmp(grafo->verticees[i]->vertice->id, id)){
			start = grafo->verticees[i];
			break;
		}
	}

	if(start == NULL) return false;

	for(int i = 0; i < grafo->free; i++){
		grafo->verticees[i]->vertice->color = WHITE;
		grafo->verticees[i]->vertice->p = NULL;
		grafo->verticees[i]->vertice->dist = -1;
	}

	start->vertice->color = BLACK;
	start->vertice->dist = 0;
	start->vertice->p = NULL;

	Queue queue = criarFilaPrioridade();
	inserirFilaPrioridade(queue, start);

	while(getTamanhoFilaPrioridade(queue) != 0){
		gNodeImp u = removerFilaPrioridade(queue);

		for(gNodeImp v = u->next; v != NULL; v = v->next){
			if(v->vertice->color == WHITE){
				v->vertice->color = BLACK;
				v->vertice->dist = u->vertice->dist + 1;
				v->vertice->p = u->vertice;
				inserirFilaPrioridade(queue, v->vertice->node);
			}
		}
	}
}

void relax_Dijkstra(gNodeImp u, gNodeImp v, bool itsSpeed){
	double arestaWeight;

	if(itsSpeed)
		arestaWeight = v->aresta->velocidade;
	else
		arestaWeight = v->aresta->comprimento;

	if(v->vertice->dist < 0){
		v->vertice->dist = u->vertice->dist + arestaWeight;
		v->vertice->p = u->vertice;
	}
	else{
		if(v->vertice->dist > u->vertice->dist + arestaWeight){
			v->vertice->dist = u->vertice->dist + arestaWeight;
			v->vertice->p = u->vertice;
		}
	}
}

bool shortestWat_Dijkstra(Grafo g, char *id, bool itsSpeed){
	grafoImp grafo = (grafoImp) g;

	gNodeImp start = NULL;
	for(int i = 0; i < grafo->free; i++){
		if(!strcmp(grafo->verticees[i]->vertice->id, id)){
			start = grafo->verticees[i];
			break;
		}
	}

	if(start == NULL) return false;

	Queue priorQueue = criarFilaPrioridade();

	for(int i = 0; i < grafo->free; i++){
		grafo->verticees[i]->vertice->dist = -1;
		grafo->verticees[i]->vertice->p = NULL;
		inserirFilaPrioridade(priorQueue, grafo->verticees[i]);
	}
	start->vertice->dist = 0;

	while(getTamanhoFilaPrioridade(priorQueue) != 0){
		gNodeImp u = removerPrioridade(priorQueue);

		for(gNodeImp v = u->next; v != NULL; v = v->next){
			relax_Dijkstra(u, v, itsSpeed);
		}
	}

	return true;
}

void destroiGrafo(Grafo g){
	grafoImp grafo = (grafoImp) g;

	for(int i = 0; i < grafo->free; i++){
		gNodeImp node = grafo->verticees[i];

		free(node->vertice);
		while(node != NULL){
			free(node->aresta);

			gNodeImp nextNode = node->next;
			free(node);
			node = nextNode;
		}
	}
	free(grafo->verticees);
	free(grafo);
}