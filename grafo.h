#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//TAD VERTICE
typedef void *GVertice;

//TAD NÓ
typedef void *GNode;

//TAD GRAFO
typedef void *Grafo;

/*  
*  Cria um grafo
*  Necessita de um tamanho
*  Retorna um grafo criado 
*/
Grafo criarGrafo(int size);

/*
* Pega a distância de um vértice de um grafo
* Necessita de um nó
* Retorna a distância de um vértice de um grafo
*/
double getVerticeDistGrafo(GNode n);

/*
* Da free num grafo
* Necessita de um grafo
* Não retorna nada
*/
int getFreeGrafo(Grafo g);

/*
* Pega o nó de um Grafo
* Necessita de um Grafo e seu tamanho
* Retorna o nó de um grafo
*/
GNode getNodeGrafo(Grafo g, int i);

/*
* Pega o id de um nó de um grafo
* Necessita de um nó
* Retorna o id de um nó de um grafo
*/
char *getNodeIdGrafo(GNode n);

/*
* Pega a posição X de um nó de um grafo
* Necessita de um nó
* Retorna a posição X de um nó de um grafo
*/
double getNodeXGrafo(GNode n);

/*
* Pega a posição Y de um nó de um grafo
* Necessita de um nó
* Retorna a posição Y de um nó de um grafo
*/
double getNodeYGrafo(GNode n);

/*
* Pega o P de um nó de um grafo
* Necessita de um nó
* Retorna o P de um nó de um grafo
*/
GVertice getNodePGrafo(GNode n);

/*
* Pega a posição X de um vértice de um grafo
* Necessita de um vértice 
* Retorna a posição X de um vértice de um grafo
*/
double getVerticeXGrafo(GVertice v);

/*
* Pega a posição Y de um vértice de um grafo
* Necessita de um vértice 
* Retorna a posição Y de um vértice de um grafo
*/
double getVerticeYGrafo(GVertice v);

/*
* Pega o nó de um vértice de um grafo
* Necessita de um vértice 
* Retorna o nó de um vértice de um grafo
*/
GNode getVerticeNodeGrafo(GVertice v);

/*
* Adiciona um vértice a um grafo
* Necessita de um grafo, seu id e posição x,y 
* Não retorna nada
*/
bool addVertice(Grafo g, char *id, double x, double y);

/*
* Adiciona uma aresta a um grafo
* Necessita de um grafo, seu id e posição x,y e outras características
* Não retorna nada
*/
bool addAresta(Grafo g, char *id1, char *id2, char *rua, char *bR, char *bL, double comprimento, double velocidade);

/*
* Realiza uma busca do tipo profunda num grafo
* Necessita de um grafo e seu id 
* Não retorna nada
*/
bool depthSearch(Grafo g, char *id);

/*
* Realiza uma busca em largura num grafo
* Necessita de um grafo e seu id 
* Não retorna nada
*/
bool widthSearch(Grafo g, char *id);

/*
* Busca o menor caminho de um trajeto a partir do algoritmo de Dijkstra
* Necessita de um grafo e seu id
* Não retorna nada
*/
bool shortestWat_Dijkstra(Grafo g, char *id, bool itsSpeed);

/*
* Da free num grafo
* Necessita de um grafo
* Não retorna nada
*/
void destroiGrafo(Grafo g);

#endif