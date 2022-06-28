#ifndef POSTO__H
#define POSTO__H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../ponto.h"

//TAD HIDRANTE
typedef void* Posto;

/*  
*   cria um objeto posto
*   necessita que o comando h tenha sido chamado
*   retorna um posto criado
*/

Posto criarPosto(double x, double y, char corPreenchimento[], char corBorda[]);

/*
*   busca o X do posto
*   necessita de um posto criado
*   retorna o X do posto
*/
double getXPosto (Posto posto);

/*
*   busca o Y do posto
*   necessita de um posto criado
*   retorna o Y do posto
*/
double getYPosto (Posto posto);

/*  
*   busca a cor de borda do posto
*   necessita de um posto criado
*   retorna a cor de borda do posto
*/
char* getcorBordaPosto (Posto posto);

/*
*   busca a cor de preenchimento de um posto
*   necessita de um posto criado
*   retorna a cor de preenchimento do posto
*/
char* getcorPreenchimentoPosto (Posto posto);

/*
*   libera um objeto posto da memoria  
*   necessita de um posto criado
*   nao retorna nada
*/
void freePosto (Posto posto);

/*
* busca a chave do caso
* necessita de um caso criado 
* nao retorna nada
*/
Point getKeyPosto(Posto posto);

#endif