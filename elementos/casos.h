#ifndef __casos__
#define __casos__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../ponto.h"

//TAD CASOS
typedef void *Casos;

/*
*   cria uma lista de casos
*   necessita de que o comando ci tenha sido chamado
*   retorna o caso dentro criado
*/
Casos criarCasos(double x, double y, double n, char cep[32], char face[32]);

/*
*   busca o CEP de caso
*   necessita de um caso criado
*   retorna o CEP do caso
*/
char* getCepCasos(Casos caso);

/*
*   busca o FACE de caso
*   necessita de um caso criado
*   retorna o FACE do caso
*/
char* getFaceCasos(Casos caso);

/*
*   busca o X do caso
*   necessita de um caso criado
*   retorna o X do caso
*/
double getXCasos(Casos caso);

/*
*   busca o Y do caso
*   necessita de um caso criado
*   retorna o Y do caso
*/
double getYCasos(Casos caso);

/*
*   busca o N do caso
*   necessita de um caso criado
*   retorna o N do caso
*/
double getNCasos(Casos caso);

/*
*   libera um objeto caso da memoria  
*   necessita de um caso criado
*   nao retorna nada
*/
void freeCasos (Casos caso);

/*
* busca a chave do caso
* necessita de um caso criado 
* nao retorna nada
*/
Point getKeyCasos(Casos caso);

#endif