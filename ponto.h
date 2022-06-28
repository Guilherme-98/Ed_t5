#ifndef PONTO_H
#define PONTO_H

#include <stdio.h>
#include <stdlib.h>


//TAD PONTO
typedef void *Point;

/*
*   Necessita de dois double
*   Cria um ponto
*/
Point createPoint(double x, double y);

/*
* Compara 2 pontos
*/
int comparatorPoint(Point p1, Point p2);

/*
* Necessita de um ponto
* Retorno o X desse ponto
*/
double getPointX(Point p);

/*
* Necessita de um ponto
* Retorno o Y desse ponto
*/
double getPointY(Point p);

/*
*   Libera memoria de um ponto p
*/
void freePoint(Point p);

#endif