#ifndef __texto__
#define __texto__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../ponto.h"

//TAD TEXTO
typedef void *Texto;

/*
*   cria um novo texto na lista
*   necessita do comando t ter sido chamado
*   retorna um novo texto
*/
Texto criarTexto(char id[], char tipo[], double x, double y, char corBorda[], char corPreenchimento[],  char conteudo []);

/*
*   busca o X do texto
*   necessita de um texto criado
*   retorna o X do texto
*/
double getXTexto (Texto texto);

/*
*   busca o Y do texto
*   necessita de um texto criado
*   retorna o Y do texto
*/
double getYTexto (Texto texto);

/*
*   busca a cor de borda do texto
*   necessita de um texto criado
*   retorna a cor de borda do texto
*/
char* getcorBordaTexto (Texto texto);

/*
*   busca a cor de preenchimento do texto
*   necessita de um texto criado
*   retorna a cor de preenchimento do texto
*/
char* getcorPreenchimentoTexto (Texto texto);

/*
*   busca o conteudo do texto
*   necessita de um texto criado
*   retorna o conteudo do texto
*/
char* getConteudoTexto (Texto texto);

/*
*   busca o ID do texto
*   necessita de um texto criado
*   retorna o ID do texto
*/
char* getIdTexto(Texto texto);

/*
*   busca o tipo t do texto
*   necessita de um texto criado
*   retorna o tipo t do texto
*/
char* getTipoTexto (Texto texto);

/*
*   transforma a cor de borda do texto
*   necessita de um texto criado
*   nao retorna nada
*/
void setcorBordaTexto(Texto texto, char corBorda[]);

/*
*   transforma a cor de preenchimento do texto
*   necessita de um texto criado
*   nao retorna nada
*/
void setcorPreenchimentoTexto(Texto texto, char corPreenchimento[]);

/*
*   libera a memoria de um texto criado
*   necessita de um texto criado
*   nao retorna nada
*/
void freeTexto(Texto texto);

/*
* busca a chave de um texto
* necessita de um texto criado 
* nao retorna nada
*/
Point getKeyTexto(Texto texto);

#endif