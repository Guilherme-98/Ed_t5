#ifndef FORMAH
#define FORMAH
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../ponto.h"

//TAD FORMA
typedef void* Forma;

/*
*   cria a forma circulo/retangulo
*   necessita de que o comando c/r tenha sido chamado
*   retorna a forma criada
*/
Forma criarForma (char id[],char tipo[], double x, double y, double r, double w,double h, char corBorda[], char corPreenchimento[], char sw[]);

/*
*   busca o X da forma
*   necessita do comando c/r ter sido chamado
*   retorna o X da forma
*/
double getXForma (Forma forma);

/*
*   busca o Y da forma
*   necessita do comando c/r ter sido chamado
*   retorna o Y da forma
*/
double getYForma (Forma forma);

/*
*   busca o raio da forma
*   necessita do comando c/r ter sido chamado
*   retorna o raio da forma
*/
double getRaioForma (Forma forma);

/*
*   busca a largura da forma
*   necessita do comando c/r ter sido chamado
*   retorna a largura da forma
*/
double getWForma (Forma forma);

/*
*   busca a altura da forma
*   necessita do comando c/r ter sido chamado
*   retorna a altura da forma
*/
double getHForma (Forma forma);

/*
*   busca a cor de borda da forma
*   necessita do comando c/r ter sido chamado
*   retorna a cor de borda da forma
*/
char* getcorBordaForma (Forma forma);

/*
*   busca a cor de preenchimento da forma
*   necessita do comando c/r ter sido chamado
*   retorna a cor de preenchimento da forma
*/
char* getcorPreenchimentoForma (Forma forma);

/*
*   busca o tipo da forma
*   necessita do comando c/r ter sido chamado
*   retorna o tipo da forma
*/
char* getTipoForma (Forma forma);

/*
*   busca o sw da forma
*   necessita do comando c/r ter sido chamado
*   retorna o sw da forma
*/
char* getSWForma (Forma forma);

/*
*   busca o id da forma
*   necessita do comando c/r ter sido chamado
*   retorna o id da forma
*/
char* getIdForma(Forma forma);

/*
*   da free na forma
*   necessita do comando c/r ter sido chamado
*   nao retorna nada
*/
void freeForma (Forma forma);

/*
*   muda a cor de preenchimento da forma
*   necessita do comando c/r ter sido chamado
*   nao retorna nada
*/
void setcorPreenchimentoForma(Forma forma, char corPreenchimento[]);

/*
*   muda a cor de borda da forma
*   necessita do comando c/r ter sido chamado
*   retorna o X da forma
*/
void setcorBordaForma(Forma forma, char corBorda[]);

/*
* busca a chave da forma
* necessita de uma forma criado 
* nao retorna nada
*/
Point getKeyForma(Forma forma);

#endif