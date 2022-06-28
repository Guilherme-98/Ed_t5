#ifndef HIDRANTE__H
#define HIDRANTE__H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include"../ponto.h"

//TAD HIDRANTE
typedef void* Hidrante;

/*  
*   cria um objeto hidrante
*   necessita que o comando h tenha sido chamado
*   retorna um hidrante criado
*/
Hidrante criaHidrante (char id[], char tipo[], double x, double y, char cor1[], char cor2[], char sw[]);

/*
*   busca o X do hidrante
*   necessita de um hidrante criado
*   retorna o X do hidrante
*/
double getXHid (Hidrante hidrante);

/*
*   busca o Y do hidrante
*   necessita de um hidrante criado
*   retorna o Y do hidrante
*/
double getYHid (Hidrante hidrante);

/*
*   busca o ID/CEP do hidrante
*   necessita de um hidrante criado
*   retorna o ID do hidrante
*/
char* getIDHid (Hidrante hidrante);

/*  
*   busca a cor de borda do hidrante
*   necessita de um hidrante criado
*   retorna a cor de borda do hidrante
*/
char* getcorBordaHid (Hidrante hidrante);

/*
*   busca a cor de preenchimento de um hidrante
*   necessita de um hidrante criado
*   retorna a cor de preenchimento do hidrante
*/
char* getcorPreenchimentoHid (Hidrante hidrante);

/*
*   busca o SW do hidrante
*   necessita de um hidrante criado
*   retorna o SW do hidrante
*/
char* getSWHid (Hidrante hidrante);

/*
*   libera um objeto hidrante da memoria  
*   necessita de um hidrante criado
*   nao retorna nada
*/
void freeHidrante (Hidrante hidrante);

/*
*   Retorna o tipo do elemento hidrante ("h")
*   Necessita de um hidrante criado
*/
char* getTipoHidrante (Hidrante hidrante);

/*
*   Retorna as informações de um hidrante
*   Necessita de um hidrante criado
*/
void getHidranteInformacao(Hidrante hidrante, char *info, char *posic);

/*
*   Calcula a coordenada polar de dois hidrantes
*   Necessita de dois hidrantes criados 
*/
double coordPolarHidrante(Hidrante h1,Hidrante h2);

/*
*   Retorna a orientação de tres hidrantes (horario, anti-horario ou colinear)
*   Necessita de tres hidrantes criados 
*/
int orientacaoHidrante(Hidrante q1,Hidrante q2,Hidrante q3);

/*
* busca a chave do hidrante
* necessita de um hidrante criado 
* nao retorna nada
*/
Point getKeyHidrante(Hidrante hidrante);

#endif