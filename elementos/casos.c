#include <stdio.h>
#include <stdlib.h>
#include "casos.h"

struct StCasos{
    double x, y;
    int n;
    char cep[32], face[32];
    Point ponto;
};
typedef struct StCasos *CasosImp;

Casos criarCasos(double x, double y, double n, char cep[32], char face[32]){
    CasosImp novo;
    novo = (CasosImp)malloc (sizeof (struct StCasos));
    Point ponto = createPoint(x, y);
    novo->x = x;
    novo->y = y;
    novo->n = n;
    strcpy(novo->cep, cep);
    strcpy(novo->face,face);

    return novo;
}

char* getCepCasos(Casos caso){
    CasosImp c;
    c =  (CasosImp) caso;
    return c->cep;
}

char* getFaceCasos(Casos caso){
    CasosImp c;
    c =  (CasosImp) caso;
    return c->face; 
}

double getXCasos(Casos caso){
    CasosImp c;
    c =  (CasosImp) caso;
    return c->x; 
}

double getYCasos(Casos caso){
    CasosImp c;
    c =  (CasosImp) caso;
    return c->y; 
}

double getNCasos(Casos caso){
    CasosImp c;
    c =  (CasosImp) caso;
    return c->n; 
}

void freeCasos (Casos caso){
    CasosImp c;
    c = (CasosImp) caso;
    freePoint(c->ponto);
    free (c);
}

Point getKeyCasos(Casos caso){
    CasosImp c;
    c = (CasosImp) caso;
    return c->ponto;
}