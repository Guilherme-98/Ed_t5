#include <stdio.h>
#include <stdlib.h>
#include "casosDentro.h"

struct StCasosDentro{
    double x, y;
    int n;
};
typedef struct StCasosDentro *CasosDentroImp;

CasosDentro criarCasosDentro(double x, double y, double n){
    CasosDentroImp novo;
    novo = (CasosDentroImp)malloc (sizeof (struct StCasosDentro));

    novo->x = x;
    novo->y = y;
    novo->n = n;

    return novo;
}

double getXCasosDentro(CasosDentro caso){
    CasosDentroImp c;
    c =  (CasosDentroImp) caso;
    return c->x; 
}


double getYCasosDentro(CasosDentro caso){
    CasosDentroImp c;
    c =  (CasosDentroImp) caso;
    return c->y; 
}


double getNCasosDentro(CasosDentro caso){
    CasosDentroImp c;
    c =  (CasosDentroImp) caso;
    return c->n; 
}

void freeCasosDentro (CasosDentro caso){
    CasosDentroImp c;
    c = (CasosDentroImp) caso;
    free (c);
}