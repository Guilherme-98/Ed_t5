#ifndef QUADRA__H
#define QUADRA__H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../hashTable.h"
#include <math.h>
#include"../ponto.h"

//TAD QUADRA
typedef void* Quadra;

/*
*   cria uma quadra
*   necessita do comando q ter sido chamado
*   retorna uma quadra criada
*/
Quadra criaQuadra (char cep[],char tipo[], double x, double y, double w, double h, char corBorda[], char corPreenchimento[], char sw[]);

/*
*   busca o cep de uma quadra
*   necessita do comando q ter sido chamado
*   retorna o cep de quadra
*/
char* getCEPQuadra (Quadra quadra);

/*
*   busca o X de uma quadra
*   necessita do comando q ter sido chamado
*   retorna o X de quadra
*/
double getXQuadra (Quadra quadra);

/*
*   busca o Y de uma quadra
*   necessita do comando q ter sido chamado
*   retorna o Y de quadra
*/
double getYQuadra (Quadra quadra);

/*
*   busca a largura de uma quadra
*   necessita do comando q ter sido chamado
*   retorna a largura de quadra
*/
double getWQuadra (Quadra quadra);

/*
*   busca a altura de uma quadra
*   necessita do comando q ter sido chamado
*   retorna a altura de quadra
*/
double getHQuadra (Quadra quadra);

/*
*   busca o sw de uma quadra
*   necessita do comando q ter sido chamado
*   retorna o sw de quadra
*/
char* getSWQuadra (Quadra quadra);

/*
*   busca a cor de borda de uma quadra
*   necessita do comando q ter sido chamado
*   retorna a cor de borda de quadra
*/
char* getcorBordaQuadra (Quadra quadra);

/*
*   busca a cor de preenchimento de uma quadra
*   necessita do comando q ter sido chamado
*   retorna a cor de preenchimento de quadra
*/
char* getcorPreenchimentoQuadra (Quadra quadra);

/*
*   muda a cor de borda de uma quadra
*   necessita do comando q ter sido chamado
*   nao retorna nada
*/
void setcorBordaQuadra(Quadra quadra, char corBorda[]);

/*
*   da free na lista de quadra
*   necessita do comando q ter sido chamado
*   nao retorna nada
*/
void freeQuadra (Quadra quadra);

/*
*   Retorna o tipo de uma quadra ("q")
*   Necessita de uma quadra criada
*/
char* getTipoQuadra (Quadra quadra);

/*
*   Retorna os moradores de uma quadra na hashtable
*   Necessita de uma hashtable, quadra e moradores criados
*/
HashTable getQuadraMoradores(Quadra b);

/*
*   Retorna as informações de uma quadra
*/
void getQuadraInformacao(Quadra b, char *info, char *posic);

/*
*   Calcula a coordenada polar de duas quadras
*   Necessita de duas quadras criadas 
*/
double coordPolarQuadra(Quadra q1,Quadra q2);

/*
*   Retorna a orientação de tres quadras (horario, anti-horario ou colinear)
*   Necessita de tres quadras criadas 
*/
int orientacaoQuadra(Quadra q1,Quadra q2,Quadra q3);

/*
* busca a chave de uma quadra
* necessita de uma quadra criada
* nao retorna nada
*/
Point getKeyQuadra(Quadra quadra);

#endif