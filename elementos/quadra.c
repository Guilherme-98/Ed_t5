#include"quadra.h"

struct StQuadra {
    char  cep[50], corBorda[32], corPreenchimento[32], tipo[4], sw[32];
    double x, y, w, h;
    Point ponto;
    HashTable moradores;
};

typedef struct StQuadra *QuadraImp;

Quadra criaQuadra (char cep[], char tipo[], double x, double y, double w, double h, char corPreenchimento[], char corBorda[], char sw[]){
    QuadraImp novo;
    novo = (QuadraImp)malloc(sizeof(struct StQuadra));
    Point ponto = createPoint(x, y);
    strcpy(novo->cep, cep);
    novo->x = x;
    novo->y = y;
    novo->w = w;
    novo->h = h;
    strcpy(novo->tipo,"q");
    strcpy(novo->corBorda, corBorda);
    strcpy(novo->corPreenchimento, corPreenchimento);
    strcpy(novo->sw, sw );

    novo->moradores = createHashTable(10000, NULL);


    return novo;
}

char* getcorBordaQuadra (Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    return q->corBorda;
}

char* getcorPreenchimentoQuadra (Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    return q->corPreenchimento;
}

char* getCEPQuadra (Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    return q->cep;
}

char* getTipoQuadra (Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    return q->tipo;
}

double getXQuadra (Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    return q->x; 
}

double getYQuadra (Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    return q->y; 
}

double getWQuadra (Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    return q->w; 
}

double getHQuadra (Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    return q->h; 
}

char* getSWQuadra (Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    return q->sw;
}

void setcorBordaQuadra(Quadra quadra, char corBorda[]){
    QuadraImp q;
    q = (QuadraImp) quadra;
    strcpy(q->corBorda, corBorda);
}


void freeQuadra (Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    freePoint(q->ponto);
    free (q);
}

HashTable getQuadraMoradores(Quadra b){
    QuadraImp quadra = (QuadraImp) b;

    return quadra->moradores;
}

void getQuadraInformacao(Quadra b, char *info, char *posic){
    QuadraImp quadra = (QuadraImp) b;
    sprintf(info, "%s", quadra->cep);
    sprintf(posic, "(%.2lf, %.2lf)", quadra->x, quadra->y);
} 

double coordPolarQuadra(Quadra q1,Quadra q2){
  double x1,x2,y1,y2;
  QuadraImp novaQuadra1,novaQuadra2;
  novaQuadra1 = (QuadraImp)q1;
  novaQuadra2 = (QuadraImp)q2;

  x1 = novaQuadra1->x;
  x2 = novaQuadra2->x;
  y1 = novaQuadra1->y;
  y2 = novaQuadra2->y;

  return atan2((y2-y1),(x2-x1));
}

int orientacaoQuadra(Quadra q1,Quadra q2,Quadra q3){
  double x1,y1,x2,y2,x3,y3,result;
  QuadraImp novaQuadra1,novaQuadra2,novaQuadra3;

  novaQuadra1 = (QuadraImp)q1;
  novaQuadra2 = (QuadraImp)q2;
  novaQuadra3 = (QuadraImp)q3;
  x1 = novaQuadra1->x;
  x2 = novaQuadra2->x;
  x3 = novaQuadra3->x;
  y1 = novaQuadra1->y;
  y2 = novaQuadra2->y;
  y3 = novaQuadra3->y;

  result = (y2-y1)*(x3-x2)-(x2-x1)*(y3-y2);

  if(result > 0)
    return 1;
  else if(result < 0)
    return -1;
  else
    return 0;
}

Point getKeyQuadra(Quadra quadra){
    QuadraImp q;
    q = (QuadraImp) quadra;
    return q->ponto;
}
