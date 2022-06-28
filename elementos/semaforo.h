#ifndef SEMAFORO__H
#define SEMAFORO__H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include "../ponto.h"


//TAD SEMAFORO
typedef void* Semaforo;

/*
*   cria um objeto semaforo
*   necessita do comando s ter sido chamado
*   retorna um novo objeto semaforo criado
*/
Semaforo criaSemaforo (char id[], char tipo[],double x, double y, char cor1[], char cor2[], char sw[]);

/*  
*   busca o X do semaforo
*   necessita de um semaforo criado
*   retorna o X do semaforo
*/
double getXSema (Semaforo semaforo);

/*
*   busca o Y do semaforo
*   necessita de um semaforo criado
*   retorna o Y do semaforo
*/
double getYSema (Semaforo semaforo);

/*
*   busca o ID/CEP do semaforo
*   necessita de um semaforo criado
*   retorna o ID/CEP do semaforo
*/
char* getIDSema (Semaforo semaforo);

/*
*   busca a cor de borda do semaforo
*   necessita de um semaforo criado
*   retorna a cor de borda do semaforo
*/
char* getcorBordaSema (Semaforo semaforo);

/*
*   busca a cor de preenchimento do semaforo
*   necessita de um semaforo criado
*   retorna a cor de preenchimento do semaforo
*/
char* getcorPreenchimentoSema (Semaforo semaforo);

/*
*   busca o SW do semaforo
*   necessita de um semaforo criado
*   retorna o SW do semaforo
*/
char* getSWSema (Semaforo semaforo);

/*
*   libera a memoria do objeto semaforo
*   necessita de um semaforo criado
*   nao retorna nada
*/
void freeSemaforo (Semaforo semaforo);

/*
*   Retorna o tipo de um semaforo ("s")
*   Necessita de um semaforo criado
*/
char* getTipoSema(Semaforo semaforo);

/*
*   Retorna as informações de um semaforo
*/
void getSemaforoInformacao(Semaforo semaforo, char *info, char *posic);

/*
*   Calcula a coordenada polar de dois semaforos
*   Necessita de dois semaforos criados 
*/
double coordPolarSemaforo(Semaforo s1, Semaforo s2);

/*
*   Retorna a orientação de tres semaforos (horario, anti-horario ou colinear)
*   Necessita de tres semaforos criados 
*/
int orientacaoSemaforo(Semaforo s1, Semaforo s2, Semaforo s3);

/*
* busca a chave de um semaforo
* necessita de um semaforo criado 
* nao retorna nada
*/
Point getKeySemaforo(Semaforo semaforo);

#endif