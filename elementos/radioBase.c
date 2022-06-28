#include"radioBase.h"
struct StRadioBase {
    char cep[50], tipo[4],corBorda[32],corPreenchimento[32], sw[20];
    double x, y;
    Point ponto;
};

typedef struct StRadioBase *RadioBaseImp;

RadioBase criaRadioBase (char cep[], char tipo[], double x, double y, char corPreenchimento[], char corBorda[], char sw[]){
    RadioBaseImp novo;
    novo = (RadioBaseImp) malloc (sizeof (struct StRadioBase));
    Point ponto = createPoint(x, y);
    strcpy (novo->cep, cep);
    novo->x = x;
    novo->y = y;
    strcpy(novo->tipo,"rb");
    strcpy(novo->corBorda, corBorda);
    strcpy(novo->corPreenchimento, corPreenchimento);
    strcpy(novo->sw, sw);
    return novo;
}

double getXRB (RadioBase radioBase){
    RadioBaseImp rb;
    rb = (RadioBaseImp) radioBase;
    return rb->x; 
}

double getYRB (RadioBase radioBase){
    RadioBaseImp rb;
    rb = (RadioBaseImp) radioBase;
    return rb->y; 
}

char* getIDRB (RadioBase radioBase){
    RadioBaseImp rb;
    rb = (RadioBaseImp) radioBase;
    return rb->cep;
}

char* getTipoRB (RadioBase radioBase){
    RadioBaseImp rb;
    rb = (RadioBaseImp) radioBase;
    return rb->tipo;
}

char* getcorBordaRB (RadioBase radioBase){
    RadioBaseImp rb;
    rb = (RadioBaseImp) radioBase;
    return rb->corBorda;
}

char* getcorPreenchimentoRB (RadioBase radioBase){
    RadioBaseImp rb;
    rb = (RadioBaseImp) radioBase;
    return rb->corPreenchimento;
}

char* getSWRB (RadioBase radioBase){
    RadioBaseImp rb;
    rb = (RadioBaseImp) radioBase;
    return rb->sw;
}
void freeRadioBase (RadioBase radioBase){
    RadioBaseImp rb;
    rb = (RadioBaseImp) radioBase;
    freePoint(rb->ponto);
    free (rb);
}

void getRBInformacao(RadioBase radioBase, char *info, char *posic){
    RadioBaseImp rb;
    rb = (RadioBaseImp) radioBase;
    sprintf(info, "%s", rb->cep);
    sprintf(posic, "(%.2lf, %.2lf)", rb->x, rb->y);
}

double coordPolarRadioBase(RadioBase rb1, RadioBase rb2){
  double x1, x2, y1, y2;
  RadioBaseImp novaRadioBase1, novaRadioBase2;
  
  novaRadioBase1 = (RadioBaseImp) rb1;
  novaRadioBase2 = (RadioBaseImp) rb2;

  x1 = novaRadioBase1->x;
  x2 = novaRadioBase2->x;
  y1 = novaRadioBase1->y;
  y2 = novaRadioBase2->y;

  return atan2((y2-y1),(x2-x1));
}

int orientacaoRadioBase(RadioBase rb1, RadioBase rb2, RadioBase rb3){
  double x1,y1,x2,y2,x3,y3,result;
  RadioBaseImp novaRadioBase1,novaRadioBase2,novaRadioBase3;

  novaRadioBase1 = (RadioBaseImp) rb1;
  novaRadioBase2 = (RadioBaseImp) rb2;
  novaRadioBase3 = (RadioBaseImp) rb3;

  x1 = novaRadioBase1->x;
  x2 = novaRadioBase2->x;
  x3 = novaRadioBase3->x;
  y1 = novaRadioBase1->y;
  y2 = novaRadioBase2->y;
  y3 = novaRadioBase3->y;

  result = (y2-y1)*(x3-x2)-(x2-x1)*(y3-y2);

  if(result > 0)
    return 1;
  else if(result < 0)
    return -1;
  else
    return 0;
}

Point getKeyRadioBase(RadioBase radiobase){
    RadioBaseImp rb;
    rb = (RadioBaseImp) radiobase;
    return rb->ponto;
}