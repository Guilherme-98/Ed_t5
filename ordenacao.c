#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"

void quicksort_ordenacao(Vetor vet, int inicio, int fim, compara comparaGenerico){
  int pivo;

  if(fim > inicio){
    pivo = swap_ordenacao(vet, inicio, fim, comparaGenerico);
    quicksort_ordenacao(vet, inicio, pivo-1, comparaGenerico);
    quicksort_ordenacao(vet, pivo+1, fim, comparaGenerico);
  }
}

int swap_ordenacao(Vetor vet, int inicio, int fim, compara comparaGenerico){
  int esq,dir,pivo;

  esq = inicio-1;
  dir = inicio;
  pivo = fim;
  while (dir < fim) {
    if(comparaGenerico(vet,pivo,dir) == 1){
      esq++;
      troca(vet,esq,dir);
    }
    dir++;
  }
  esq++;
  troca(vet,esq,fim);

  return esq;
}

Vetor PrimeiroPasso(Vetor vet, compara comparaY, calculaCoordenada comparaPolar, compara comparaAng){
  int tamanho = getTamanhoVetor(vet);

  quicksort_ordenacao(vet, 0, tamanho-1, comparaY);
  vet = calculaCoordPolar(vet, comparaPolar);
  quicksort_ordenacao(vet, 0, tamanho-1, comparaAng);

  return vet;
}

Pilha calculaEnvoltoria(Vetor vet, orientacao orientation, Pilha finalP, Pilha resto){
  ItemPilha topo, meio, aux;
  int tam, i;

  tam = getTamanhoVetor(vet);

  if (tam > 0) {
    pilhaPush(finalP, getElementVector(vet, 0));
    if (tam > 1) {

      pilhaPush(finalP, getElementVector(vet, 1));

      if (tam >= 3) {
        for (i=2; i<tam; i++) {
          aux = getElementVector(vet, i);
          meio = pilhaPop(finalP);
          topo = pilhaPop(finalP);

          if (orientation(topo, meio, aux) == -1) {
            pilhaPush(finalP, topo);
            pilhaPush(finalP, meio);
            pilhaPush(finalP, aux);
          }
          else {
            pilhaPush(resto, meio);
            pilhaPush(finalP, topo);
            pilhaPush(finalP, aux);

            while(tamanhoPilha(finalP) >= 3) {
              aux = pilhaPop(finalP);
              meio = pilhaPop(finalP);
              topo = pilhaPop(finalP);

              if (orientation(topo, meio, aux) >= 0) {
                pilhaPush(resto, meio);
                pilhaPush(finalP, topo);
                pilhaPush(finalP, aux);
              }
              else {
                pilhaPush(finalP, topo);
                pilhaPush(finalP, meio);
                pilhaPush(finalP, aux);
                break;
              }
            }
          }
        }
      }
    }
  }

  return finalP;
}

Vetor calculaCoordPolar(Vetor vet, calculaCoordenada calc){
  int tam,i;
  void *obj,*aux;
  double ang;

  tam = getTamanhoVetor(vet);
  obj = getElementVector(vet,0);

  for(i=0;i<tam;i++){
    aux = getElementVector(vet,i);
    ang = calc(obj,aux);
    addAng(vet,i,ang);
  }

  return vet;
}

int conversao_arvore_vetor(Vetor v, Tree arv, PosicNo nohArv, getCoordenada getCoordX, getCoordenada getCoordY, int i){

  if(leafNe(arv,nohArv) == 1){
    i = conversao_arvore_vetor(v,arv,getNe(arv,nohArv),getCoordX,getCoordY,i);
  }

  if(leafNw(arv,nohArv) == 1){
    i = conversao_arvore_vetor(v,arv,getNw(arv,nohArv),getCoordX,getCoordY,i);
  }

  if(leafSe(arv,nohArv) == 1){
    i = conversao_arvore_vetor(v,arv,getSe(arv,nohArv),getCoordX,getCoordY,i);
  }

  if(leafSw(arv,nohArv) == 1){
    i = conversao_arvore_vetor(v,arv,getSw(arv,nohArv),getCoordX,getCoordY,i);
  }

  addElementVector(v,i,getElement(arv,nohArv),getCoordX(getElement(arv,nohArv)),getCoordY(getElement(arv,nohArv)));
  i++;

  return i;
}

Vetor converterPilhaParaVetor(Pilha monte, getCoordenada getCoordX, getCoordenada getCoordY, int pts){
  Vetor vet;
  PosicPilha *p;
  int tamanhoP,i;

  p = getTopoPilha(monte);
  tamanhoP = tamanhoPilha(monte);
  vet = createVector(tamanhoP*pts);

  for(i=0;i<tamanhoP;i++){
    addElementVector(vet,i,getElementPilha(monte,p),getCoordX(getElementPilha(monte,p)),getCoordY(getElementPilha(monte,p)));
    p = getAnteriorPilha(monte,p);
  }
  return vet;
}

void arvore_quadra_balanceada(Tree arvoreQuadra){
  Pilha heap,resto;
  PosicNo n;
  PosicPilha p;
  Vetor q;
  ItemPilha info;
  Element elemento;
  int tam=0,i;

  n = getFirstElementTree(arvoreQuadra);
  elemento = getElement(arvoreQuadra, n);

  if(n != NULL){
    q = createVector(sizeTree(arvoreQuadra));
    conversao_arvore_vetor(q, arvoreQuadra,n,getXQuadra,getYQuadra,0);
    q = PrimeiroPasso(q,comparaY,coordPolarQuadra,comparaAng);
    heap = iniciar();
    resto = iniciar();
    heap = calculaEnvoltoria(q,orientacaoQuadra,heap,resto);

    while(tamanhoPilha(resto)>=3){
      q = converterPilhaParaVetor(resto,getXQuadra,getYQuadra,1);
      q = PrimeiroPasso(q,comparaY,coordPolarQuadra,comparaAng);
      resto = iniciar();
      heap = calculaEnvoltoria(q,orientacaoQuadra,heap,resto);
    }

    tam = tamanhoPilha(resto);

    for(i=0;i<tam;i++){
      info = pilhaPop(resto);
      pilhaPush(heap,info);
    }

    p = getTopoPilha(heap);

    for(i=0;i<tamanhoPilha(heap);i++){
      insereQt(arvoreQuadra,getElementPilha(heap,p),getXQuadra(getElementPilha(heap,p)),getYQuadra(getElementPilha(heap,p)));
      p = getAnteriorPilha(heap,p);
    }

    tam = tamanhoPilha(heap);

    for(i=0;i<tam;i++){
      info = pilhaPop(heap);
    }
  }

  free(resto);
}

void arvore_hidrante_balanceada(Tree arvoreHidrante){
  Pilha heap,resto;
  PosicNo n;
  PosicPilha p;
  Vetor q;
  ItemPilha info;
  Element elemento;
  int tam=0,i;

  n = getFirstElementTree(arvoreHidrante);
  elemento = getElement(arvoreHidrante, n);

  if(n != NULL){
    q = createVector(sizeTree(arvoreHidrante));
    conversao_arvore_vetor(q, arvoreHidrante,n,getXHid,getYHid,0);
    q = PrimeiroPasso(q,comparaY,coordPolarHidrante,comparaAng);
    heap = iniciar();
    resto = iniciar();
    heap = calculaEnvoltoria(q,orientacaoHidrante,heap,resto);

    while(tamanhoPilha(resto)>=3){
      q = converterPilhaParaVetor(resto,getXHid,getYHid,1);
      q = PrimeiroPasso(q,comparaY,coordPolarHidrante,comparaAng);
      resto = iniciar();
      heap = calculaEnvoltoria(q,orientacaoHidrante,heap,resto);
    }

    tam = tamanhoPilha(resto);

    for(i=0;i<tam;i++){
      info = pilhaPop(resto);
      pilhaPush(heap,info);
    }

    p = getTopoPilha(heap);

    for(i=0;i<tamanhoPilha(heap);i++){
      insereQt(arvoreHidrante,getElementPilha(heap,p),getXHid(getElementPilha(heap,p)),getYHid(getElementPilha(heap,p)));
      p = getAnteriorPilha(heap,p);
    }

    tam = tamanhoPilha(heap);

    for(i=0;i<tam;i++){
      info = pilhaPop(heap);
    }
  }

  free(resto);
}

void arvore_semaforo_balanceada(Tree arvoreSemaforo){
  Pilha heap,resto;
  PosicNo n;
  PosicPilha p;
  Vetor q;
  ItemPilha info;
  Element elemento;
  int tam=0,i;

  n = getFirstElementTree(arvoreSemaforo);
  elemento = getElement(arvoreSemaforo, n);

  if(n != NULL){
    q = createVector(sizeTree(arvoreSemaforo));
    conversao_arvore_vetor(q, arvoreSemaforo,n,getXSema,getYSema,0);
    q = PrimeiroPasso(q,comparaY,coordPolarSemaforo,comparaAng);
    heap = iniciar();
    resto = iniciar();
    heap = calculaEnvoltoria(q,orientacaoSemaforo,heap,resto);

    while(tamanhoPilha(resto)>=3){
      q = converterPilhaParaVetor(resto,getXSema,getYSema,1);
      q = PrimeiroPasso(q,comparaY,coordPolarSemaforo,comparaAng);
      resto = iniciar();
      heap = calculaEnvoltoria(q,orientacaoSemaforo,heap,resto);
    }

    tam = tamanhoPilha(resto);

    for(i=0;i<tam;i++){
      info = pilhaPop(resto);
      pilhaPush(heap,info);
    }

    p = getTopoPilha(heap);

    for(i=0;i<tamanhoPilha(heap);i++){
      insereQt(arvoreSemaforo,getElementPilha(heap,p),getXSema(getElementPilha(heap,p)),getYSema(getElementPilha(heap,p)));
      p = getAnteriorPilha(heap,p);
    }

    tam = tamanhoPilha(heap);

    for(i=0;i<tam;i++){
      info = pilhaPop(heap);
    }
  }

  free(resto);
}

void arvore_radioBase_balanceada(Tree arvoreRadioBase){
  Pilha heap,resto;
  PosicNo n;
  PosicPilha p;
  Vetor q;
  ItemPilha info;
  Element elemento;
  int tam=0,i;

  n = getFirstElementTree(arvoreRadioBase);
  elemento = getElement(arvoreRadioBase, n);

  if(n != NULL){
    q = createVector(sizeTree(arvoreRadioBase));
    conversao_arvore_vetor(q, arvoreRadioBase,n,getXRB,getYRB,0);
    q = PrimeiroPasso(q,comparaY,coordPolarRadioBase,comparaAng);
    heap = iniciar();
    resto = iniciar();
    heap = calculaEnvoltoria(q,orientacaoRadioBase,heap,resto);

    while(tamanhoPilha(resto)>=3){
      q = converterPilhaParaVetor(resto,getXSema,getYSema,1);
      q = PrimeiroPasso(q,comparaY,coordPolarRadioBase,comparaAng);
      resto = iniciar();
      heap = calculaEnvoltoria(q,orientacaoRadioBase,heap,resto);
    }

    tam = tamanhoPilha(resto);

    for(i=0;i<tam;i++){
      info = pilhaPop(resto);
      pilhaPush(heap,info);
    }

    p = getTopoPilha(heap);

    for(i=0;i<tamanhoPilha(heap);i++){
      insereQt(arvoreRadioBase,getElementPilha(heap,p),getXRB(getElementPilha(heap,p)),getYRB(getElementPilha(heap,p)));
      p = getAnteriorPilha(heap,p);
    }

    tam = tamanhoPilha(heap);

    for(i=0;i<tam;i++){
      info = pilhaPop(heap);
    }
  }

  free(resto);
}
