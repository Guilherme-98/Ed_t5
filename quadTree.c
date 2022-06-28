#include <stdio.h>
#include <stdlib.h>
#include "quadTree.h"
#include "elementos/quadra.h"
#include "elementos/forma.h"
#include "elementos/texto.h"
#include "elementos/hidrante.h"
#include "elementos/semaforo.h"
#include "elementos/radioBase.h"
#include "elementos/casos.h"
#include "elementos/casosDentro.h"
#include "util.h"
#include "svg.h"
#include "consultas.h"
#include "ponto.h"

typedef struct no{
  ItemNode alvo;
  double x,y;
  struct no *Ne; //Nordeste
  struct no *Nw; //Noroeste
  struct no *Se; //Sudeste
  struct no *Sw; //Sudoeste
}noh;

typedef struct _arvore{
  struct no *inicio;
  int tamanho;
  int comp;
}arvore;

Tree createTree(funcGetChave getKey){
  arvore *arv;
  arv = (arvore *)malloc(sizeof(arvore));
  arv->inicio = NULL;
  arv->tamanho = 0;
  arv->comp=0;

  return (Tree)arv;
}

int sizeTree(Tree arv){
  arvore *a;
  a = (arvore*)arv;
  return a->tamanho;
}

PosicNo insereQt(Tree qt, ItemNode elemento, double x, double y){
  arvore *arv;
  noh *aux;
  PosicNo p;

  arv = (arvore*)qt;
  aux = arv->inicio;

  if(arv->inicio != NULL){
    insereQtAux(qt, elemento, aux, x, y);
  }
  else{
    p = insereQtStart(qt, elemento, x, y);
  }

  return p;
}

int insereQtAux(Tree qt, ItemNode elemento, PosicNo noArvore, double x, double y){
  arvore *arv;
  noh *aux;

  aux = (noh*)noArvore;
  arv = (arvore*)qt;

  if(aux == NULL)
    return 1;

  else if(x <= aux->x && y >= aux->y){
    arv->comp++;
    insereQtNe(arv, elemento, aux, x, y);
    return 0;
  }

  else if(x <= aux->x && y <= aux->y){
    arv->comp++;
    insereQtSe(arv, elemento, aux, x, y);
    return 0;
  }

  else if(x >= aux->x && y >= aux->y){
    arv->comp++;
    insereQtNw(arv, elemento, aux, x, y);
    return 0;
  }

  else if(x >= aux->x && y <= aux->y){
    arv->comp++;
    insereQtSw(arv, elemento, aux, x, y);
    return 0;
  }

}

int insereQtNe(Tree qt, ItemNode elemento, PosicNo noArvore, double x, double y){
  arvore *arv;
  noh *n;
  noh *aux;

  arv = (arvore*)qt;
  n = (noh*)noArvore;

  if(n->Ne == NULL){
    aux = (noh *)malloc(sizeof(noh));
    aux->alvo = elemento;
    aux->x = x;
    aux->y = y;
    aux->Ne = NULL;
    aux->Nw = NULL;
    aux->Se = NULL;
    aux->Sw = NULL;
    n->Ne = aux;
    arv->tamanho++;
    return 1;
  }
  else{
    insereQtAux(qt, elemento, n->Ne, x, y);
  }
}

int insereQtSe(Tree qt, ItemNode elemento, PosicNo noArvore,double x,double y){
  arvore *arv;
  noh *n;
  noh *aux;

  arv = (arvore*)qt;
  n = (noh*)noArvore;

  if(n->Se == NULL){
    aux = (noh *)malloc(sizeof(noh));
    aux->alvo = elemento;
    aux->x = x;
    aux->y = y;
    aux->Ne = NULL;
    aux->Nw = NULL;
    aux->Se = NULL;
    aux->Sw = NULL;
    n->Se = aux;
    arv->tamanho++;
    return 1;
  }
  else{
    insereQtAux(qt, elemento, n->Se, x, y);
  }
}

int insereQtNw(Tree qt, ItemNode elemento, PosicNo noArvore, double x, double y){
  arvore *arv;
  noh *n;
  noh *aux;

  arv = (arvore*)qt;
  n = (noh*)noArvore;
  if(n->Nw == NULL){
    aux = (noh *)malloc(sizeof(noh));
    aux->alvo = elemento;
    aux->x = x;
    aux->y = y;
    aux->Ne = NULL;
    aux->Nw = NULL;
    aux->Se = NULL;
    aux->Sw = NULL;
    n->Nw = aux;
    arv->tamanho++;
    return 1;
  }
  else{
    insereQtAux(qt, elemento, n->Nw, x, y);
  }
}

int insereQtSw(Tree qt, ItemNode elemento, PosicNo noArvore, double x, double y){
  arvore *arv;
  noh *n;
  noh *aux;

  arv = (arvore*)qt;
  n = (noh*)noArvore;
  if(n->Sw == NULL){
    aux = (noh *)malloc(sizeof(noh));
    aux->alvo = elemento;
    aux->x = x;
    aux->y = y;
    aux->Ne = NULL;
    aux->Nw = NULL;
    aux->Se = NULL;
    aux->Sw = NULL;
    n->Sw = aux;
    arv->tamanho++;
    return 1;
  }
  else
    insereQtAux(qt,elemento,n->Sw,x,y);
}
PosicNo insereQtStart(Tree qt,ItemNode elemento, double x, double y){
  arvore *arv;
  noh *n;

  arv = (arvore *)qt;
  n = (noh *)malloc(sizeof(noh));
  n->alvo = elemento;
  n->Ne = NULL;
  n->Nw = NULL;
  n->Se = NULL;
  n->Sw = NULL;
  n->x = x;
  n->y = y;

  arv->inicio = n;
  arv->tamanho++;
  return (PosicNo)n;
}

ItemNode getElement(Tree arv, PosicNo noArvore){
  noh *n;
  ItemNode elemento;
  PosicNo pos;

  pos = noArvore;
  n = (noh*)pos;

  if(n == NULL){
    return NULL;
  }

  elemento = n->alvo;

  return elemento;
}

PosicNo getFirstElementTree(Tree qt){
  arvore *arv;
  PosicNo aux;
  arv = (arvore*)qt;

  if(arv->inicio != NULL){
    return (PosicNo)arv->inicio;
  }

  aux = NULL;
  return aux;
}
Lista chavesDentroRetanguloQt(Tree qt, double x1, double y1, double  x2,  double y2){
  #define max(a,b)  ( (a > b) ? a : b )
  #define min(a,b)  ( (a < b) ? a : b )
  Point P = createPoint(x1, y1);
  Point R = createPoint(x2, y2);
  PosicNo aux;
  aux = getFirstElementTree(qt);
  Element elemento = getElement(qt, aux);
  Point Q = createPoint(getXQuadTree(qt, aux), getYQuadTree(qt, aux));

  Lista listaAux = create();

  if((getPointX(Q) <= max(getPointX(P), getPointX(R))) && (getPointX(Q) >= min(getPointX(P), getPointX(R))) && (getPointY(Q) <= max(getPointY(P), getPointY(R))) && (getPointY(Q)>= min(getPointY(P), getPointY(R)))){
    if(strcmp(getTipoHidrante(elemento),"h") == 0)
    insert(listaAux, getKeyHidrante, "h");
    if(strcmp(getTipoSema(elemento),"s") == 0)
    insert(listaAux, getKeySemaforo, "s");
    if(strcmp(getTipoQuadra(elemento),"q") == 0)
    insert(listaAux, getKeyQuadra, "q");
    if(strcmp(getTipoRB(elemento),"rb") == 0)
    insert(listaAux, getKeyRadioBase, "rb");
    if(strcmp(getTipoTexto(elemento),"t") == 0)
    insert(listaAux, getKeyTexto, "t");
  }
  
  return listaAux;
}

Lista chavesDentroCirculoQt(Tree qt,double x, double y, double r){
  PosicNo aux;
  aux = getFirstElementTree(qt);
  Element elemento = getElement(qt, aux);
  Point Q = createPoint(getXQuadTree(qt, aux), getYQuadTree(qt, aux));
  Lista listaAux = create();

  if(distanciaEuclidiana(x, y, getPointX(Q), getPointY(Q)) <= r ){
    if(strcmp(getTipoHidrante(elemento),"h") == 0)
    insert(listaAux, getKeyHidrante, "h");
    if(strcmp(getTipoSema(elemento),"s") == 0)
    insert(listaAux, getKeySemaforo, "s");
    if(strcmp(getTipoQuadra(elemento),"q") == 0)
    insert(listaAux, getKeyQuadra, "q");
    if(strcmp(getTipoRB(elemento),"rb") == 0)
    insert(listaAux, getKeyRadioBase, "rb");
    if(strcmp(getTipoTexto(elemento),"t") == 0)
    insert(listaAux, getKeyTexto, "t");
  } 

  return listaAux;
}

Lista pontoDentroRetanguloQt(Tree qt, double x1, double y1, double  x2,  double y2){
  #define max(a,b)  ( (a > b) ? a : b )
  #define min(a,b)  ( (a < b) ? a : b )
  Point P = createPoint(x1, y1);
  Point R = createPoint(x2, y2);
  PosicNo aux;
  aux = getFirstElementTree(qt);
  Element elemento = getElement(qt, aux);
  Point Q = createPoint(getXQuadTree(qt, aux), getYQuadTree(qt, aux));
  Lista listaAux = create();
  char tipo [10];

  if((getPointX(Q) <= max(getPointX(P), getPointX(R))) && (getPointX(Q) >= min(getPointX(P), getPointX(R))) && (getPointY(Q) <= max(getPointY(P), getPointY(R))) 
  && (getPointY(Q)>= min(getPointY(P), getPointY(R)))){

    if(strcmp(getTipoHidrante(elemento),"h") == 0){
      strcpy(tipo,"h");
    }

    else if(strcmp(getTipoSema(elemento),"s") == 0){
      strcpy(tipo,"s");
    }

    else if(strcmp(getTipoRB(elemento),"rb") == 0){
      strcpy(tipo,"rb");
    }

    else if(strcmp(getTipoRB(elemento),"q") == 0){
      strcpy(tipo,"q");
    }
    
    insert(listaAux, Q, tipo);
  }
  
  return listaAux;
}

Lista pontoDentroCirculoQt(Tree qt,double x, double y, double r){
  PosicNo aux;
  aux = getFirstElementTree(qt);
  Element elemento = getElement(qt, aux);
  Point Q = createPoint(getXQuadTree(qt, aux), getYQuadTree(qt, aux));
  Lista listaAux = create();
  char tipo [10];

   if(distanciaEuclidiana(x, y, getPointX(Q), getPointY(Q)) <= r ){
    if(strcmp(getTipoHidrante(elemento),"h") == 0){
      strcpy(tipo,"h");
    }

    else if(strcmp(getTipoSema(elemento),"s") == 0){
      strcpy(tipo,"s");
    }

    else if(strcmp(getTipoRB(elemento),"rb") == 0){
      strcpy(tipo,"rb");
    }

    else if(strcmp(getTipoRB(elemento),"q") == 0){
      strcpy(tipo,"q");
    }
      insert(listaAux, Q, tipo);
    } 

  return listaAux;
}

Lista nosDentroRetanguloQt(Tree qt, double x1, double y1, double  x2,  double y2){
  #define max(a,b)  ( (a > b) ? a : b )
  #define min(a,b)  ( (a < b) ? a : b )
  Point P = createPoint(x1, y1);
  Point R = createPoint(x2, y2);
  PosicNo aux;
  aux = getFirstElementTree(qt);
  Element elemento = getElement(qt, aux);
  Point Q = createPoint(getXQuadTree(qt, aux), getYQuadTree(qt, aux));
  Lista listaAux = create();
  char tipo [10];

  if((getPointX(Q) <= max(getPointX(P), getPointX(R))) && (getPointX(Q) >= min(getPointX(P), getPointX(R))) && (getPointY(Q) <= max(getPointY(P), getPointY(R))) 
  && (getPointY(Q)>= min(getPointY(P), getPointY(R)))){

    if(strcmp(getTipoHidrante(elemento),"h") == 0){
      strcpy(tipo,"h");
    }

    else if(strcmp(getTipoSema(elemento),"s") == 0){
      strcpy(tipo,"s");
    }

    else if(strcmp(getTipoRB(elemento),"rb") == 0){
      strcpy(tipo,"rb");
    }

    else if(strcmp(getTipoRB(elemento),"q") == 0){
      strcpy(tipo,"q");
    }

    insert(listaAux, aux, tipo);

  }
  return listaAux;
}

Lista nosDentroCirculoQt(Tree qt,double x, double y, double r){
  PosicNo aux;
  aux = getFirstElementTree(qt);
  Element elemento = getElement(qt, aux);
  Point Q = createPoint(getXQuadTree(qt, aux), getYQuadTree(qt, aux));
  Lista listaAux = create();
  char tipo [10];

   if(distanciaEuclidiana(x, y, getPointX(Q), getPointY(Q)) <= r ){
    if(strcmp(getTipoHidrante(elemento),"h") == 0){
      strcpy(tipo,"h");
    }

    else if(strcmp(getTipoSema(elemento),"s") == 0){
      strcpy(tipo,"s");
    }

    else if(strcmp(getTipoRB(elemento),"rb") == 0){
      strcpy(tipo,"rb");
    }

    else if(strcmp(getTipoRB(elemento),"q") == 0){
      strcpy(tipo,"q");
    }

      insert(listaAux, aux, tipo);
    } 

  return listaAux;
}

PosicNo getNoQt(Tree qt, double x, double y){
  PosicNo aux;
  aux = getFirstElementTree(qt);
  Element elemento = getElement(qt, aux);
  Point Q = createPoint(getXQuadTree(qt, aux), getYQuadTree(qt, aux));
  
  if(getPointX(Q) == x && getPointY(Q) ==  y){
    return aux;
  }
  return NULL;
}

Element getInfoQt(Tree qt, PosicNo pNo){
  PosicNo aux;
  aux = getFirstElementTree(qt);
  Element elemento = getElement(qt, aux);
  Element elemento2 = getElement(qt, pNo);
  Point Q = createPoint(getXQuadTree(qt, aux), getYQuadTree(qt, aux));

   if(strcmp(getTipoHidrante(elemento),"h") == 0){
      if(strcmp(getIDHid(elemento), getIDHid(elemento2)) == 0 ){
        return elemento;
      }
    }

    else if(strcmp(getTipoSema(elemento),"s") == 0){
      if(strcmp(getIDSema(elemento), getIDSema(elemento2)) == 0 ){
        return elemento;
      }
    }

    else if(strcmp(getTipoRB(elemento),"rb") == 0){
      if(strcmp(getIDRB(elemento), getIDRB(elemento2)) == 0 ){
        return elemento;
      }
    }

    else if(strcmp(getTipoRB(elemento),"q") == 0){
      if(strcmp(getCEPQuadra(elemento), getCEPQuadra(elemento2)) == 0 ){
        return elemento;
      }
    }

  return NULL;
} 

double getXQuadTree(Tree qt, PosicNo noArvore){
  arvore *arv;
  noh *n;
  arv = (arvore*)qt; 
  n = (noh*)noArvore;
  if(arv->inicio == NULL){
    return 0;
  }
  else{
    return n->x;
  }
}

double getYQuadTree(Tree qt, PosicNo noArvore){
  arvore *arv;
  noh *n;
  arv = (arvore*)qt;
  n = (noh*)noArvore;
  if(arv->inicio == NULL){
    return 0;
  }
  else{
    return n->y;
  }
}

int getQuadrante(Tree qt, PosicNo noArvore, PosicNo noArvore2){
  arvore *arv;
  noh *n1,*n2;
  n1 = (noh*)noArvore;
  n2 = (noh*)noArvore2;

  if(n1 == NULL)
    return 0;
  if(n1->Ne == n2)
    return 1;
  else if(n1->Nw == n2)
    return 2;
  else if(n1->Se == n2)
    return 3;
  else if(n1->Sw == n2)
    return 4;
}

ItemNode removeNoQt(Tree qt, PosicNo noArvore){
  int quadrante;
  arvore *arv;
  noh *p=NULL, *n, *aux;

  ItemNode elemento = getElement(qt, noArvore);

  arv = (arvore*)qt;
  aux = arv->inicio;
  n = (noh*)noArvore;

  if(aux != n){
    p = find(qt, aux, noArvore);
  
    quadrante = getQuadrante(qt, p, n);
   
    if(quadrante == 1)
      p->Ne = NULL;
    else if(quadrante == 2)
      p->Nw = NULL;
    else if(quadrante == 3)
      p->Se = NULL;
    else if(quadrante == 4)
      p->Sw = NULL;
  }
  else{
    arv->inicio = NULL;
    arv->tamanho--;
  }

  connect(arv, n, noArvore);
  n = NULL;
  return elemento;
}

PosicNo find(Tree qt, PosicNo inicio, PosicNo noArvore){
  noh *aux=NULL;

  if(leafNe(qt, inicio) == 1){
    if(getNe(qt, inicio) == noArvore){
      aux = inicio;
      return aux;
    }
    if(aux == NULL)
      aux = find(qt, getNe(qt, inicio), noArvore);
  }

  if(leafNw(qt, inicio) == 1){
    if(getNw(qt, inicio) == noArvore){
      aux = inicio;
      return aux;
    }
    if(aux == NULL)
      aux = find(qt, getNw(qt, inicio), noArvore);
  }

  if(leafSe(qt, inicio) == 1){
    if(getSe(qt, inicio) == noArvore){
      aux = inicio;
      return aux;
    }
    if(aux == NULL)
      aux = find(qt, getSe(qt, inicio), noArvore);
  }

  if(leafSw(qt, inicio) == 1){
    if(getSw(qt, inicio) == noArvore){
      aux = inicio;
      return aux;
    }
    if(aux == NULL)
      aux = find(qt, getSw(qt, inicio), noArvore);
  }
  return aux;

}

void connect(Tree qt, PosicNo noArvore, PosicNo noArvore2){
  arvore *arv;
  noh *n;
  ItemNode elemento;
  double x,y;
  
  arv = (arvore*)qt;
  n = (noh*)noArvore;

  if(leafSe(qt, noArvore) == 1){
    connect(qt, n->Se, noArvore2);
  }

  if(leafNw(qt, noArvore) == 1){
    connect(qt, n->Nw, noArvore2);
  }
  if(leafNe(qt, noArvore) == 1){
    connect(qt, n->Ne, noArvore2);
  }

  if(leafSw(qt, noArvore) == 1){
    connect(qt, n->Sw, noArvore2);
  }

  if(n != (noh*)noArvore2){
    elemento = n->alvo;
    x = n->x;
    y = n->y;
    insereQt(qt, elemento, x, y);
  }

  free(n);
  arv->tamanho--;
}

PosicNo getNe(Tree qt, PosicNo noArvore){
  noh *n;
  PosicNo pos;
  pos = noArvore;
  n = (noh*)pos;

  if(n->Ne == NULL){
    pos = NULL;
  }
  else{
    n = n->Ne;
    pos = (PosicNo)n;
  }
  return pos;
}

PosicNo getNw(Tree qt, PosicNo noArvore){
  noh *n;
  PosicNo pos;
  pos = noArvore;
  n = (noh*)pos;

  if(n->Nw == NULL){
    pos = NULL;
  }
  else{
    n = n->Nw;
    pos = (PosicNo)n;
  }
  return pos;
}

PosicNo getSe(Tree qt, PosicNo noArvore){
  noh *n;
  PosicNo pos;
  pos = noArvore;
  n = (noh*)pos;

  if(n->Se == NULL){
    pos = NULL;
  }
  else{
    n = n->Se;
    pos = (PosicNo)n;
  }
  return pos;
}

PosicNo getSw(Tree qt, PosicNo noArvore){
  noh *n;
  PosicNo pos;
  pos = noArvore;
  n = (noh*)pos;

  if(n->Sw == NULL){
    pos = NULL;
  }
  else{
    n = n->Sw;
    pos = (PosicNo)n;
  }
  return pos;
}

int isLeaf(Tree qt, PosicNo noArvore){
  noh *n;

  n = (noh*)noArvore;
  if(n->Ne == NULL && n->Nw == NULL && n->Se == NULL && n->Sw){
    return 1;
  }
  else{
    return 0;
  }
}

int leafNe(Tree qt, PosicNo noArvore){
  noh *n;

  n = (noh*)noArvore;
  if(n == NULL){

    return 0;
  }
  else if(n->Ne == NULL){

    return 0;
  }
  else{
    return 1;
  }
}

int leafNw(Tree qt, PosicNo noArvore){
  noh *n;

  n = (noh*)noArvore;
  if(n == NULL){
    return 0;
  }
  else if(n->Nw == NULL){
    return 0;
  }
  else{
    return 1;
  }
}

int leafSe(Tree qt, PosicNo noArvore){
  noh *n;

  n = (noh*)noArvore;
  if(n == NULL){
    return 0;
  }
  else if(n->Se == NULL){
    return 0;
  }
  else{
    return 1;
  }
}

int leafSw(Tree qt, PosicNo noArvore){
  noh *n;

  n = (noh*)noArvore;
  if(n == NULL){
    return 0;
  }
  else if(n->Sw == NULL){
    return 0;
  }
  else{
    return 1;
  }
}

void desalocaQt(Tree arv){
  arvore *a;
  noh *n;
  a = (arvore*)arv;
  n = a->inicio;
  freeTree(a,n);
}

void freeTree(Tree arv, PosicNo noArvore){
  noh *n;
  n = (noh*)noArvore;

  if(leafNe(arv,n) == 1){
    freeTree(arv,n->Ne);
  }

  if(leafNw(arv,n) == 1){
    freeTree(arv,n->Nw);
  }

  if(leafSe(arv,n) == 1){
    freeTree(arv,n->Se);
  }

  if(leafSw(arv,n) == 1){
    freeTree(arv,n->Sw);
  }
  free(n);
  n = NULL;

}

int processarTree(Tree arv, PosicNo noArvore, Escrever escreverEquip, FILE *arq){
  ItemNode info;

  if(noArvore == NULL){
    return 0;
  }

  if(leafNe(arv,noArvore) == 1){
    processarTree(arv, getNe(arv, noArvore), escreverEquip, arq);
  }

  if(leafNw(arv, noArvore) == 1){
    processarTree(arv, getNw(arv, noArvore), escreverEquip, arq);
  }

  if(leafSe(arv, noArvore) == 1){
    processarTree(arv, getSe(arv, noArvore), escreverEquip, arq);
  }

  if(leafSw(arv, noArvore) == 1){
    processarTree(arv, getSw(arv, noArvore), escreverEquip, arq);
  }

  info = getElement(arv,noArvore);
  escreverEquip(arq,info);
}

void* percorrer_Quadra_QD(Tree arvoreAux,char id[],PosicNo n){

  if(strcmp(id,getCEPQuadra(getElement(arvoreAux,n)))==0){
    return n;
  }
    
  ItemNode resposta = NULL;

  if(leafNe(arvoreAux,n) == 1)
    resposta = percorrer_Quadra_QD(arvoreAux,id,getNe(arvoreAux,n));

    if(resposta != NULL){
      return resposta;
    }

    if(leafNw((arvoreAux),n) == 1)
    resposta = percorrer_Quadra_QD(arvoreAux,id,getNw(arvoreAux,n));

    if(resposta != NULL){
      return resposta;
    }

  if(leafSe((arvoreAux),n) == 1)
    resposta = percorrer_Quadra_QD(arvoreAux,id,getSe(arvoreAux,n));

    if(resposta != NULL){
      return resposta;
    }

  if(leafSw((arvoreAux),n) == 1)
    resposta = percorrer_Quadra_QD(arvoreAux,id,getSw(arvoreAux,n));

    if(resposta != NULL){
      return resposta;
    }

    return NULL;
}

void* percorrer_Forma_QD(Tree arvoreAux,char id[],PosicNo n){

  if(getElement(arvoreAux,n) == NULL ){
    return NULL;
  }

  if(strcmp(id,getIdForma(getElement(arvoreAux,n)))==0){
    return n;
  }

  ItemNode resposta = NULL;

  if(leafNe(arvoreAux,n) == 1)
    resposta = percorrer_Forma_QD(arvoreAux,id,getNe(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafNw((arvoreAux),n) == 1)
    resposta = percorrer_Forma_QD(arvoreAux,id,getNw(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSe((arvoreAux),n) == 1)
    resposta = percorrer_Forma_QD(arvoreAux,id,getSe(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSw((arvoreAux),n) == 1)
    resposta = percorrer_Forma_QD(arvoreAux,id,getSw(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  return NULL;
}

void* percorrer_Texto_QD(Tree arvoreAux,char id[],PosicNo n){

  if(getElement(arvoreAux,n) == NULL ){
    return NULL;
  }
   
  if(strcmp(id,getIdForma(getElement(arvoreAux,n)))==0){
    return n;
  }

  ItemNode resposta = NULL;

  if(leafNe(arvoreAux,n) == 1)
    resposta = percorrer_Texto_QD(arvoreAux,id,getNe(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafNw((arvoreAux),n) == 1)
    resposta = percorrer_Texto_QD(arvoreAux,id,getNw(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSe((arvoreAux),n) == 1)
    resposta = percorrer_Texto_QD(arvoreAux,id,getSe(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSw((arvoreAux),n) == 1)
    resposta = percorrer_Texto_QD(arvoreAux,id,getSw(arvoreAux,n));

  if(resposta != NULL){
    return resposta;

  } 
  return NULL;
}

void* percorrer_Hidrante_QD(Tree arvoreAux,char id[],PosicNo n){

  if(strcmp(id,getIDHid(getElement(arvoreAux,n)))==0){
    return n;
  }

  ItemNode resposta = NULL;

  if(leafNe(arvoreAux,n) == 1)
    resposta = percorrer_Hidrante_QD(arvoreAux,id,getNe(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafNw((arvoreAux),n) == 1)
      resposta = percorrer_Hidrante_QD(arvoreAux,id,getNw(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSe((arvoreAux),n) == 1)
    resposta = percorrer_Hidrante_QD(arvoreAux,id,getSe(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSw((arvoreAux),n) == 1)
    resposta = percorrer_Hidrante_QD(arvoreAux,id,getSw(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }
  
  return NULL;
}

void* percorrer_Semaforo_QD(Tree arvoreAux,char id[],PosicNo n){

  if(strcmp(id,getIDSema(getElement(arvoreAux,n)))==0){
    return n;
  }

  ItemNode resposta = NULL;

  if(leafNe(arvoreAux,n) == 1)
    resposta = percorrer_Semaforo_QD(arvoreAux,id,getNe(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafNw((arvoreAux),n) == 1)
    resposta = percorrer_Semaforo_QD(arvoreAux,id,getNw(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSe((arvoreAux),n) == 1)
    resposta = percorrer_Semaforo_QD(arvoreAux,id,getSe(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSw((arvoreAux),n) == 1)
    resposta = percorrer_Semaforo_QD(arvoreAux,id,getSw(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  return NULL;
}

void* percorrer_RB_QD(Tree arvoreAux,char id[],PosicNo n){

  if(strcmp(id,getIDRB(getElement(arvoreAux,n)))==0){
    return n;
  }

  ItemNode resposta = NULL;

  if(leafNe(arvoreAux,n) == 1)
    resposta = percorrer_RB_QD(arvoreAux,id,getNe(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafNw((arvoreAux),n) == 1)
    resposta = percorrer_RB_QD(arvoreAux,id,getNw(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSe((arvoreAux),n) == 1)
    resposta = percorrer_RB_QD(arvoreAux,id,getSe(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }
  if(leafSw((arvoreAux),n) == 1)
    resposta = percorrer_RB_QD(arvoreAux,id,getSw(arvoreAux,n));

  if(resposta != NULL){
    return resposta;
  }

  return NULL;
}

void* encontrarElementoArvores(char id[], Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase){
  PosicNo elemento;

  elemento = percorrer_Quadra_QD(arvoreQuadra, id, getFirstElementTree(arvoreQuadra));
  if(elemento == NULL){
    elemento = percorrer_Hidrante_QD(arvoreHidrante, id, getFirstElementTree(arvoreHidrante));

  }
  else {
    return getElement(arvoreQuadra, elemento);
  }
  if(elemento == NULL){
    elemento = percorrer_Semaforo_QD(arvoreSemaforo, id, getFirstElementTree(arvoreSemaforo));
  }
  else  {
    return getElement(arvoreHidrante, elemento);
    
  }

  if(elemento ==NULL){
    elemento = percorrer_RB_QD(arvoreRadioBase, id, getFirstElementTree(arvoreRadioBase));
  }
  else {
    return getElement(arvoreSemaforo, elemento);
  }
  return getElement(arvoreRadioBase, elemento);
}

void* dq_percorrer_arvore(Tree arvoreAux, double x, double y, double r, FILE *txt, FILE* svg2, bool verificador, PosicNo aux, Lista listaQuadra_2){
  Quadra quadra;
  quadra = getElement(arvoreAux, aux);

  int cont=0;

  if(true){
    if(distanciaEuclidiana(x, y, getXQuadra(quadra), getYQuadra(quadra)) <= r){
      cont++;
    }
    if(distanciaEuclidiana (x, y, getXQuadra(quadra) + getWQuadra(quadra), getYQuadra(quadra)) <= r){
      cont++;
    }
    if(distanciaEuclidiana (x, y, getXQuadra (quadra), getYQuadra (quadra) + getHQuadra (quadra)) <= r){
      cont++;
    }
    if(distanciaEuclidiana (x, y, getXQuadra (quadra) + getWQuadra (quadra), getYQuadra (quadra) + getHQuadra (quadra)) <= r){
      cont++;
    }
    if(cont == 4){
      fprintf(txt, "Cep removido: %s\n", getCEPQuadra(quadra));
      insert(listaQuadra_2, quadra, "q");
      if(verificador){
        svg_imprimir_quadArrend(svg2, quadra);
      }
    }
  }
  cont=0;

  ItemNode resposta = NULL;

  if(leafNe(arvoreAux,aux) == 1)
    resposta = dq_percorrer_arvore(arvoreAux,x, y ,r, txt, svg2,verificador, getNe(arvoreAux,aux), listaQuadra_2);

  if(resposta != NULL){
    return resposta;
  }

  if(leafNw((arvoreAux),aux) == 1)
    resposta = dq_percorrer_arvore(arvoreAux, x, y, r, txt, svg2,verificador, getNw(arvoreAux,aux), listaQuadra_2);

  if(resposta != NULL){
    return resposta;
  }

  if(leafSe((arvoreAux),aux) == 1)
    resposta = dq_percorrer_arvore(arvoreAux,x, y,r, txt, svg2,verificador, getSe(arvoreAux,aux), listaQuadra_2);

  if(resposta != NULL){
    return resposta;
  }

  if(leafSw((arvoreAux),aux) == 1)
    resposta = dq_percorrer_arvore(arvoreAux,x,y,r, txt, svg2,verificador, getSw(arvoreAux,aux), listaQuadra_2);

  if(resposta != NULL){
    return resposta;
  }

  return NULL;
}

void* percorrer_CBQ(Tree arvoreQuadra, double x, double y, double r, char corBorda[], FILE *txt, FILE* svg2, PosicNo aux){
  Quadra quadra;
  quadra = getElement(arvoreQuadra, aux);
  int cont=0;

  if(true){
    if(distanciaEuclidiana(x, y, getXQuadra(quadra), getYQuadra(quadra)) <= r){
      cont++;
    }
    if(distanciaEuclidiana (x, y, getXQuadra(quadra) + getWQuadra(quadra), getYQuadra(quadra)) <= r){
      cont++;
    }
    if(distanciaEuclidiana (x, y, getXQuadra (quadra), getYQuadra (quadra) + getHQuadra (quadra)) <= r){
      cont++;
    }
    if(distanciaEuclidiana (x, y, getXQuadra (quadra) + getWQuadra (quadra), getYQuadra (quadra) + getHQuadra (quadra)) <= r){
      cont++;
    }
    if (cont == 4){
      setcorBordaQuadra(quadra, corBorda);
      fprintf(txt, "Cep da quadra alterada: %s\n", getCEPQuadra(quadra));
    }
  }
  cont=0;

  ItemNode resposta = NULL;

  if(leafNe(arvoreQuadra,aux) == 1)
    resposta = percorrer_CBQ(arvoreQuadra,x, y ,r, corBorda, txt, svg2, getNe(arvoreQuadra,aux));

  if(resposta != NULL){
    return resposta;
  }

  if(leafNw((arvoreQuadra),aux) == 1)
    resposta = percorrer_CBQ(arvoreQuadra, x, y, r, corBorda, txt, svg2, getNw(arvoreQuadra,aux));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSe((arvoreQuadra),aux) == 1)
    resposta = percorrer_CBQ(arvoreQuadra,x, y, r, corBorda, txt, svg2, getSe(arvoreQuadra,aux));

  if(resposta != NULL){
    return resposta;
  }

  if(leafSw((arvoreQuadra),aux) == 1)
    resposta = percorrer_CBQ(arvoreQuadra,x, y, r, corBorda, txt, svg2, getSw(arvoreQuadra,aux));

  if(resposta != NULL){
    return resposta;
  }

  return NULL;
}

void* percorrer_CAR(FILE* aux_txt, FILE* txt, Tree arvoreQuadra, PosicNo aux, double x, double y, double h, double w, Lista listaQuadra){
  double areaQuadra = 0;
  int cont = 0;
  char aq[32], a[32];
  Quadra quadra;

  quadra = getElement(arvoreQuadra, aux);
  Forma ret = criarForma("0", "r", x, y, 0, w, h, "black", "none", "1.0");

  if(true){
    if(getXQuadra (quadra) > x && getXQuadra (quadra) < x + w && getYQuadra (quadra) > y && getYQuadra (quadra) < y + h){
      cont++;
    }
    if(getXQuadra (quadra) + getWQuadra (quadra) > x && getXQuadra (quadra) + getWQuadra (quadra) < x + w && getYQuadra (quadra) > y && getYQuadra (quadra) < y + h){
      cont++;
    }
    if(getXQuadra (quadra) > x && getXQuadra (quadra) < x + w && getYQuadra (quadra) + getHQuadra (quadra) > y && getYQuadra (quadra) + getHQuadra (quadra) < y + h){
      cont++;
    }
    if(getXQuadra (quadra) + getWQuadra (quadra) > x && getXQuadra (quadra) + getWQuadra (quadra) < x + w && getYQuadra (quadra) + getHQuadra (quadra) > y && getYQuadra (quadra) + getHQuadra (quadra) < y + h){
      cont++;
    }
    if(cont == 4) {
      insert(listaQuadra, quadra, "q");
      areaQuadra = getHQuadra(quadra) * getWQuadra(quadra);
      sprintf(aq, "%.2lf", areaQuadra);
      Texto text = criarTexto("0", "t", (getXQuadra(quadra) + getWQuadra(quadra)/2), 
      (getYQuadra(quadra) + getHQuadra(quadra)/2), "white", "black", aq);
      svg_imprimirTexto(aux_txt, text);
      fprintf(txt, "cep quadra:%s, area: %lf\n", getCEPQuadra(quadra), areaQuadra);
      freeTexto(text);
    }
  }
  cont = 0;

  ItemNode resposta = NULL;

  if(leafNe(arvoreQuadra, aux) == 1)
    resposta = percorrer_CAR(aux_txt, txt, arvoreQuadra, getNe(arvoreQuadra, aux), x, y, h, w, listaQuadra);

  if(resposta != NULL) {
    return resposta;
  }

  if(leafNw((arvoreQuadra), aux) == 1)
    resposta = percorrer_CAR(aux_txt, txt, arvoreQuadra, getNw(arvoreQuadra, aux), x, y, h, w, listaQuadra);

  if(resposta != NULL) {
    return resposta;
  }

  if(leafSe((arvoreQuadra), aux) == 1)
    resposta = percorrer_CAR(aux_txt, txt, arvoreQuadra, getSe(arvoreQuadra, aux), x, y, h, w, listaQuadra);

  if(resposta != NULL) {
    return resposta;
  }

  if(leafSw((arvoreQuadra), aux) == 1)
    resposta = percorrer_CAR(aux_txt, txt, arvoreQuadra, getSw(arvoreQuadra, aux), x, y, h, w, listaQuadra);
      
  if(resposta != NULL) {
    return resposta;
  }

  return  NULL;
}

void* soc_posto_conversao(Tree arvorePosto,PosicNo aux,Lista listaPosto){
  Posto posto;
  posto = getElement(arvorePosto, aux);

  if(posto == NULL){
    return NULL;
  }
  insert(listaPosto, posto, "ps");

  ItemNode resposta = NULL;

  if(leafNe(arvorePosto,aux) == 1)
    resposta = soc_posto_conversao(arvorePosto, getNe(arvorePosto,aux), listaPosto);

  if(resposta != NULL){
    return resposta;
  }

  if(leafNw((arvorePosto),aux) == 1)
    resposta = soc_posto_conversao(arvorePosto, getNw(arvorePosto,aux), listaPosto);


  if(resposta != NULL){
    return resposta;
  }

  if(leafSe((arvorePosto),aux) == 1)
    resposta = soc_posto_conversao(arvorePosto, getSe(arvorePosto,aux), listaPosto);

  if(resposta != NULL){
    return resposta;
  }

  if(leafSw((arvorePosto),aux) == 1)
    resposta = soc_posto_conversao(arvorePosto, getSw(arvorePosto,aux), listaPosto);

  if(resposta != NULL){
    return resposta;
  }

  return NULL;
}

void* ci_casos_conversao(Tree arvoreCasos,PosicNo aux,Lista listaCasos){
  Posto posto;
  posto = getElement(arvoreCasos, aux);
  insert(listaCasos, posto, "ca");

  ItemNode resposta = NULL;

  if(leafNe(arvoreCasos,aux) == 1)
    resposta = ci_casos_conversao(arvoreCasos, getNe(arvoreCasos,aux), listaCasos);

  if(resposta != NULL){
    return resposta;
  }

  if(leafNw((arvoreCasos),aux) == 1)
    resposta = ci_casos_conversao(arvoreCasos, getNw(arvoreCasos,aux), listaCasos);


  if(resposta != NULL){
    return resposta;
  }

  if(leafSe((arvoreCasos),aux) == 1)
    resposta = ci_casos_conversao(arvoreCasos, getSe(arvoreCasos,aux), listaCasos);

  if(resposta != NULL){
    return resposta;
  }

  if(leafSw((arvoreCasos),aux) == 1)
    resposta = ci_casos_conversao(arvoreCasos, getSw(arvoreCasos,aux), listaCasos);

  if(resposta != NULL){
    return resposta;
  }

  return NULL;
}

void* percorrer_Quadra_dd(Tree arvoreQuadra, PosicNo aux, double x, double w, double y, double h) {
  Forma retangulo = criarForma("0", "r", x, y, 0, w, h, "black", "white", "1.0");
  Quadra quadra = getElement(arvoreQuadra, aux);
  extern double numQuadrasDentro;
  int cont = 0;

    if(true){
      if(getXQuadra (quadra) >= x && getXQuadra (quadra) <= x + w && getYQuadra (quadra) >= y && getYQuadra (quadra) <= y + h){
        cont++;
      }
      if(getXQuadra (quadra) + getWQuadra (quadra) >= x && getXQuadra (quadra) + getWQuadra (quadra) <= x + w && getYQuadra (quadra) >= y && getYQuadra (quadra) <= y + h){
        cont++;
      }
      if(getXQuadra (quadra) >= x && getXQuadra (quadra) <= x + w && getYQuadra (quadra) + getHQuadra (quadra) >= y && getYQuadra (quadra) + getHQuadra (quadra) <= y + h){
        cont++;
      }
      if(getXQuadra (quadra) + getWQuadra (quadra) >= x && getXQuadra (quadra) + getWQuadra (quadra) <= x + w && getYQuadra (quadra) + getHQuadra (quadra) >= y && getYQuadra (quadra) + getHQuadra (quadra) <= y + h){
        cont++;
      }

      if(cont == 4){
        numQuadrasDentro++;
      }

    }
    ItemNode resposta = NULL;

    if(leafNe(arvoreQuadra, aux) == 1)
      resposta = percorrer_Quadra_dd(arvoreQuadra, getNe(arvoreQuadra, aux), x, w, y, h);

    if(resposta != NULL) {
      return resposta;
    }

    if(leafNw(arvoreQuadra, aux) == 1)
      resposta = percorrer_Quadra_dd(arvoreQuadra, getNw(arvoreQuadra, aux), x, w, y, h);

    if(resposta != NULL) {
      return resposta;
    }

    if(leafSe(arvoreQuadra, aux) == 1)
      resposta = percorrer_Quadra_dd(arvoreQuadra, getSe(arvoreQuadra, aux), x, w, y, h);

    if(resposta != NULL) {
      return resposta;
    }

    if(leafSw(arvoreQuadra, aux) == 1)
      resposta = percorrer_Quadra_dd(arvoreQuadra, getSw(arvoreQuadra, aux), x, w, y, h);

    if(resposta != NULL) {
      return resposta;
    }

  return NULL;
}

void* inputSombraQuadras(Tree arvoreQuadra, PosicNo aux, FILE* svg, double densidadeQuadra, double x, double y, double w, double h){
  int cont = 0;
  Quadra quadra = getElement(arvoreQuadra, aux);

  if(true){
    if(getXQuadra (quadra) >= x && getXQuadra (quadra) <= x + w && getYQuadra (quadra) >= y && getYQuadra (quadra) <= y + h){
    cont++;
    }

    if(getXQuadra (quadra) + getWQuadra (quadra) >= x && getXQuadra (quadra) + getWQuadra (quadra) <= x + w && getYQuadra (quadra) >= y && getYQuadra (quadra) <= y + h){
      cont++;
    }

    if(getXQuadra (quadra) >= x && getXQuadra (quadra) <= x + w && getYQuadra (quadra) + getHQuadra (quadra) >= y && getYQuadra (quadra) + getHQuadra (quadra) <= y + h){
      cont++;
    }

    if(getXQuadra (quadra) + getWQuadra (quadra) >= x && getXQuadra (quadra) + getWQuadra (quadra) <= x + w && getYQuadra (quadra) + getHQuadra (quadra) >= y && getYQuadra (quadra) + getHQuadra (quadra) <= y + h){
      cont++;
    }

    if(cont == 4){
      if(densidadeQuadra >= 10 && densidadeQuadra < 500){
      svg_drop_shadow(svg, getXQuadra(quadra)+5, getYQuadra(quadra)+5, getWQuadra(quadra), getHQuadra(quadra), "#FFFF00", "#FFFF00", "#FFFF00");
      }

      if(densidadeQuadra >= 500 && densidadeQuadra < 1500){
        svg_drop_shadow(svg, getXQuadra(quadra)+5, getYQuadra(quadra)+5, getWQuadra(quadra), getHQuadra(quadra), "#FF9955", "#FF9955", "#FF9955");
      }

      if(densidadeQuadra >= 1500 && densidadeQuadra < 3000){
        svg_drop_shadow(svg, getXQuadra(quadra)+5, getYQuadra(quadra)+5, getWQuadra(quadra), getHQuadra(quadra), "#FF0000", "#FF0000", "#FF0000");
      }

      if(densidadeQuadra >= 3000 && densidadeQuadra < 4500){
        svg_drop_shadow(svg, getXQuadra(quadra)+5, getYQuadra(quadra)+5, getWQuadra(quadra), getHQuadra(quadra), "#FF00CC", "#FF00CC", "#FF00CC");
      }

      if(densidadeQuadra >= 4500 && densidadeQuadra < 6000){
        svg_drop_shadow(svg, getXQuadra(quadra)+5, getYQuadra(quadra)+5, getWQuadra(quadra), getHQuadra(quadra), "#6600FF", "#6600FF", "#6600FF");
      }
      
      if(densidadeQuadra >= 6000){
        svg_drop_shadow(svg, getXQuadra(quadra)+5, getYQuadra(quadra)+5, getWQuadra(quadra), getHQuadra(quadra), "#A02C5A", "#A02C5A", "#A02C5A");
      }

    }

  }

  cont = 0;
  ItemNode resposta = NULL;

  if(leafNe(arvoreQuadra, aux) == 1)
    resposta = inputSombraQuadras(arvoreQuadra, getNe(arvoreQuadra, aux), svg, densidadeQuadra, x, y, w, h);

  if(resposta != NULL) {
    return resposta;
  }

  if(leafNw(arvoreQuadra, aux) == 1)
    resposta = inputSombraQuadras(arvoreQuadra, getNw(arvoreQuadra, aux), svg, densidadeQuadra, x, y, w, h);

  if(resposta != NULL) {
    return resposta;
  }

  if(leafSe(arvoreQuadra, aux) == 1)
    resposta = inputSombraQuadras(arvoreQuadra, getSe(arvoreQuadra, aux), svg, densidadeQuadra, x, y, w, h);


  if(resposta != NULL) {
    return resposta;
  }

  if(leafSw(arvoreQuadra, aux) == 1)
    resposta = inputSombraQuadras(arvoreQuadra, getSw(arvoreQuadra, aux),svg, densidadeQuadra, x, y, w, h);

  if(resposta != NULL) {
    return resposta;
  }

  return NULL;
}


void* bf_quadra_conversao(Tree arvoreQuadra, PosicNo aux, Lista listaQuadra){
  Quadra quadra;
  quadra = getElement(arvoreQuadra, aux);

  if(quadra == NULL){
    return NULL;
  }
  insert(listaQuadra, quadra, "ps");

  ItemNode resposta = NULL;

  if(leafNe(arvoreQuadra,aux) == 1)
    resposta = bf_quadra_conversao(arvoreQuadra, getNe(arvoreQuadra,aux), listaQuadra);

  if(resposta != NULL){
    return resposta;
  }

  if(leafNw((arvoreQuadra),aux) == 1)
    resposta = bf_quadra_conversao(arvoreQuadra, getNw(arvoreQuadra,aux), listaQuadra);


  if(resposta != NULL){
    return resposta;
  }

  if(leafSe((arvoreQuadra),aux) == 1)
    resposta = bf_quadra_conversao(arvoreQuadra, getSe(arvoreQuadra,aux), listaQuadra);

  if(resposta != NULL){
    return resposta;
  }

  if(leafSw((arvoreQuadra),aux) == 1)
    resposta = bf_quadra_conversao(arvoreQuadra, getSw(arvoreQuadra,aux), listaQuadra);

  if(resposta != NULL){
    return resposta;
  }

  return NULL;
}
