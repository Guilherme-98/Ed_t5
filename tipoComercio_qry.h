#ifndef TIPOCOMERCIO_QRY_H
#define TIPOCOMERCIO_QRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pessoa.h"
#include "moradores.h"
#include "tipoComercio.h"
#include "hashTable.h"
#include "comercio.h"
#include "ponto.h"
#include "svg.h"
#include "util.h"
#include "lista.h"
#include  "./elementos/quadra.h"

/*
*   Realiza a consulta do comando eplg do .qry
*   Necessita do comando eplg ter sido chamado na leitura do .qry
*   Nao retorna nada
*/
void consulta_eplg(FILE *aqrTxt, FILE *arqSvg, char *codt, HashTable comercios,double x, double y, double w, double h);

/*
*   Verifica a distancia de um ponto Point
*   Retorna true ou false
*/
bool verificacao_ponto(double x, double y, double w, double h, Point p);

/*
*   Verifica se um ponto Point está dentro de um circulo
*   Retorna true ou false
*/
bool verificacao_ponto_circulo(double x, double y, double r, Point p);

/*
*   Realiza a consulta do comando catac na leitura do .qry
*   Nao retorna nada
*/
void consulta_catac(FILE *arqTxt, FILE *arqSvg, double x, double y, double r, Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoroSemaforo, Tree arvoreRadioBase, HashTable moradores, HashTable comercios);

/*
*   Percorre uma arvore de hidrantes e exclui os hidrantes dentro da região especificada
*   Nao retorna nada
*/
void* catac_hidrante(FILE *arqTxt, double x, double y, double r, PosicNo aux, Tree arvoreHidrante, Lista removerHidrante);

/*
*   Percorre uma arvore de semaforos e exclui os semaforos dentro da região especificada
*   Nao retorna nada
*/
void* catac_semaforo(FILE *arqTxt, double x, double y, double r, PosicNo aux, Tree arvoreSemaforo, Lista removerSemaforo);

/*
*   Percorre uma arvore de radio base e os exclui de dentro da região especificada
*   Nao retorna nada
*/
void* catac_radioBase(FILE *arqTxt, double x, double y, double r, PosicNo aux, Tree arvoreRadioBase, Lista removerRadioBase);

/*
*   Percorre uma arvore de quadras e as exclui de dentro da região especificada
*   Nao retorna nada
*/
void* catac_quadra(FILE *arqTxt, double x, double y, double r, PosicNo aux, Tree arvoreQuadra, Lista removerQuadra);

/*
*   Percorre uma arvore de moradores e os exclui de dentro da região especificada
*   Nao retorna nada
*/
void catac_morador(FILE *aqrTxt, double x, double y, double r, HashTable moradores, Lista removerMorador, FILE *arqSvg);

/*
*   Percorre uma arvore de comercios e os exclui de dentro da região especificada
*   Nao retorna nada
*/
void catac_comercio(FILE *aqrTxt, double x, double y, double r, HashTable comercios, Lista removerComercio, FILE *arqSvg);

/*
*   Verifica se um ponto Point está dentro de um retangulo
*   Retorna true ou false
*/
bool verificacao_ponto_retangulo(double x, double y, double r, Quadra quadra);

#endif