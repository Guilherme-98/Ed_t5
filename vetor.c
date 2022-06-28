#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"

typedef struct reg{
    void *obj;
    double ang, x, y;
    int tamanho;
}vetor;

Vetor createVector(int qtd){
    vetor *vet;
    vet = malloc(qtd*sizeof(vetor));
    vet->tamanho = 0;

    return(Vetor *) vet;
}

void addElementVector(Vetor vet, int i, void *forma, double x, double y){
    vetor *v;
    v = (vetor *) vet;
    v->tamanho++;
    v[i].obj = (vetor *) forma;
    v[i].x = x;
    v[i].y = y;
}

Vetor *getElementVector(Vetor vet, int i){
    vetor *v;
    v = (vetor*)vet;

    return v[i].obj;
}

int getTamanhoVetor(Vetor vet){
    vetor *v;
    v = (vetor*)vet;

    return v->tamanho;
}

double getAng(Vetor vet, int i){
    vetor *v;
    v = (vetor*)vet;

    return v[i].ang;
}

double getXVector(Vetor vet, int i){
    vetor *v;
    v = (vetor*)vet;

    return v[i].x;
}

double getYVector(Vetor vet, int i){
    vetor *v;
    v = (vetor*)vet;

    return v[i].y;
}

void addAng(Vetor vet, int i, double angulo){
    vetor *v;
    v = (vetor*)vet;

    v[i].ang = angulo;
}

int comparaY(Vetor vet, int i, int j){
  vetor *v;
  v = (vetor*)vet;
  if(v[i].y < v[j].y)
    return -1;
  else if(v[i].y > v[j].y)
    return 1;
  else
    return 0;
}

int comparaX(Vetor vet, int i, int j){
    vetor *v;
    v = (vetor*)vet;

    if(v[i].x < v[j].x)
        return -1;
    else if(v[i].x > v[j].x)
        return 1;
    else
        return 0;

}

int comparaAng(Vetor vet, int i, int j){
    vetor *v;
    v = (vetor*)vet;

    if(v[i].ang < v[j].ang){
        return -1;
    }
    else if(v[i].ang > v[j].ang){
        return 1;
    }
    else
        return 0;
}

void troca(Vetor vet, int i, int j){
    vetor *v;
    void *info;
    double xAux,yAux,angulo;

    v = (vetor*)vet;

    xAux = v[i].x;
    yAux = v[i].y;
    angulo = v[i].ang;
    info = v[i].obj;
    v[i].x = v[j].x;
    v[i].y  = v[j].y;
    v[i].ang = v[j].ang;
    v[i].obj = v[j].obj;
    v[j].x = xAux;
    v[j].y = yAux;
    v[j].ang = angulo;
    v[j].obj = info;
}