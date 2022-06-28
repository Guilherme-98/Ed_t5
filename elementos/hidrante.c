#include"hidrante.h"
struct StHidrante {
    char id[50], tipo[4],corBorda[32],corPreenchimento[32], sw[32];
    double x, y;
    Point ponto;
};
typedef struct StHidrante *HidranteImp;

Hidrante criaHidrante (char id[], char tipo[], double x, double y, char corPreenchimento[], char corBorda[], char sw[]){
    HidranteImp novo;
    novo = (HidranteImp)malloc(sizeof(struct StHidrante));
    Point ponto = createPoint(x, y);
    strcpy (novo->id, id);
    novo->x = x;
    novo->y = y;
    strcpy(novo->tipo,"h");
    strcpy (novo->corBorda, corBorda);
    strcpy (novo->corPreenchimento, corPreenchimento);
    strcpy (novo->sw, sw);
    return novo;
}

double getXHid (Hidrante hidrante){
    HidranteImp h;
    h = (HidranteImp) hidrante;
    return h->x; 
}

double getYHid (Hidrante hidrante){
    HidranteImp h;
    h = (HidranteImp) hidrante;
    return h->y; 
}

char* getIDHid (Hidrante hidrante){
    HidranteImp h;
    h = (HidranteImp) hidrante;
    return h->id;
}
char* getTipoHidrante (Hidrante hidrante){
    HidranteImp h;
    h = (HidranteImp) hidrante;
    return h->tipo;
}

char* getcorBordaHid (Hidrante hidrante){
    HidranteImp h;
    h = (HidranteImp) hidrante;
    return h->corBorda;
}

char* getcorPreenchimentoHid (Hidrante hidrante){
    HidranteImp h;
    h = (HidranteImp) hidrante;
    return h->corPreenchimento;
}
char* getSWHid (Hidrante hidrante){
    HidranteImp h;
    h = (HidranteImp) hidrante;
    return h->sw;
}

void freeHidrante (Hidrante hidrante){
    HidranteImp h;
    h = (HidranteImp) hidrante;
    freePoint(h->ponto);
    free (h);
}

void getHidranteInformacao(Hidrante hidrante, char *info, char *posic){
    HidranteImp h;
    h = (HidranteImp) hidrante;
    sprintf(info, "%s", h->id);
    sprintf(posic, "(%.2lf, %.2lf)", h->x, h->y);
}

double coordPolarHidrante(Hidrante h1,Hidrante h2){
  double x1, x2, y1, y2;
  HidranteImp novaHidrante1, novaHidrante2;
  
  novaHidrante1 = (HidranteImp) h1;
  novaHidrante2 = (HidranteImp) h2;

  x1 = novaHidrante1->x;
  x2 = novaHidrante2->x;
  y1 = novaHidrante1->y;
  y2 = novaHidrante2->y;

  return atan2((y2-y1),(x2-x1));
}

int orientacaoHidrante(Hidrante q1,Hidrante q2,Hidrante q3){
  double x1,y1,x2,y2,x3,y3,result;
  HidranteImp novaHidrante1,novaHidrante2,novaHidrante3;

  novaHidrante1 = (HidranteImp) q1;
  novaHidrante2 = (HidranteImp) q2;
  novaHidrante3 = (HidranteImp) q3;

  x1 = novaHidrante1->x;
  x2 = novaHidrante2->x;
  x3 = novaHidrante3->x;
  y1 = novaHidrante1->y;
  y2 = novaHidrante2->y;
  y3 = novaHidrante3->y;

  result = (y2-y1)*(x3-x2)-(x2-x1)*(y3-y2);

  if(result > 0)
    return 1;
  else if(result < 0)
    return -1;
  else
    return 0;
}

Point getKeyHidrante(Hidrante hidrante){
    HidranteImp h;
    h = (HidranteImp) hidrante;
    return h->ponto;
}
