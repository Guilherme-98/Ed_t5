#ifndef RADIOBASE__H
#define RADIOBASE__H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include "../ponto.h"

//TAD RADIO BASE
typedef void* RadioBase;

/*
*   cria um novo objeto radio base
*   necessita do comando rb ter sido chamado
*   retorna um novo objeto radio base
*/
RadioBase criaRadioBase (char cep[], char tipo[], double x, double y, char corBorda[], char corPreenchimento[], char sw[]);

/*
*   busca o X do radio base
*   necessita de um objeto radio base ter sido criado
*   retorna o X do radio base
*/
double getXRB (RadioBase radioBase);

/*
*   busca o Y do radio base
*   necessita de um objeto radio base ter sido criado
*   retorna o Y do radio base
*/
double getYRB (RadioBase radioBase);

/*
*   busca o ID/CEP do radio base
*   necessita de um objeto radio base ter sido criado
*   retorna o ID/CEP do radio base
*/
char* getIDRB (RadioBase radioBase);

/*
*   busca a cor de borda do radio base
*   necessita de um objeto radio base ter sido criado
*   retorna a cor de borda do radio base
*/
char* getcorBordaRB (RadioBase radioBase);

/*
*   busca a cor de preenchimento do radio base
*   necessita de um objeto radio base ter sido criado
*   retorna a cor de preenchimento do radio base
*/
char* getcorPreenchimentoRB (RadioBase radioBase);

/*
*   busca o SW do radio base
*   necessita de um objeto radio base ter sido criado
*   retorna o SW do radio base
*/
char* getSWRB (RadioBase radioBase);

/*
*   libera a memoria do objeto radio base
*   necessita de um objeto radio base ter sido criado
*   nao retorna nada
*/
void freeRadioBase (RadioBase radioBase);

/*
*   Retorna o tipo de um radio base ("rb")
*   Necessita de um radio base criado
*/
char* getTipoRB (RadioBase radioBase);

/*
*   Retorna as informações de um radio base
*/
void getRBInformacao(RadioBase radioBase, char *info, char *posic);

/*
 *  Calcula a coordenada polar de dois radios bases
 *  Necessita de dois radios bases criados 
*/
double coordPolarRadioBase(RadioBase rb1, RadioBase rb2);

/*
*   Retorna a orientação de tres radios bases (horario, anti-horario ou colinear)
*   Necessita de tres radios bases criados 
*/
int orientacaoRadioBase(RadioBase rb1, RadioBase rb2, RadioBase rb3);

/*
* busca a chave de um radio base
* necessita de um radio base criado 
* nao retorna nada
*/
Point getKeyRadioBase(RadioBase radiobase);

#endif