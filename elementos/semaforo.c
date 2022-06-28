#include"semaforo.h"
struct StSemaforo {
    char  id[50], tipo[4], corBorda[32],corPreenchimento[32], sw[20];
    double x, y;
    Point ponto;
    
};

typedef struct StSemaforo *SemaforoImp;

Semaforo criaSemaforo (char id[], char tipo[], double x, double y, char corPreenchimento[], char corBorda[], char sw[]){
    SemaforoImp novo;
    novo = (SemaforoImp) malloc (sizeof (struct StSemaforo));
    Point ponto = createPoint(x, y);
    strcpy (novo->id, id);
    novo->x = x;
    novo->y = y;
    strcpy(novo->tipo,"s");
    strcpy (novo->corBorda, corBorda);
    strcpy (novo->corPreenchimento, corPreenchimento);
    strcpy (novo->sw, sw);
    return novo;
}

double getXSema(Semaforo semaforo){
    SemaforoImp s;
    s = (SemaforoImp) semaforo;
    return s->x; 
}

double getYSema(Semaforo semaforo){
    SemaforoImp s;
    s = (SemaforoImp) semaforo;
    return s->y; 
}

char* getIDSema(Semaforo semaforo){
    SemaforoImp s;
    s = (SemaforoImp) semaforo;
    return s->id;
}

char* getTipoSema(Semaforo semaforo){
    SemaforoImp s;
    s = (SemaforoImp) semaforo;
    return s->tipo;
}

char* getcorBordaSema(Semaforo semaforo){
    SemaforoImp s;
    s = (SemaforoImp) semaforo;
    return s->corBorda;
}

char* getcorPreenchimentoSema(Semaforo semaforo){
    SemaforoImp s;
    s = (SemaforoImp) semaforo;
    return s->corPreenchimento;
}

char* getSWSema(Semaforo semaforo){
    SemaforoImp s;
    s = (SemaforoImp) semaforo;
    return s->sw;
}

void freeSemaforo(Semaforo semaforo){
    SemaforoImp s;
    s = (SemaforoImp) semaforo;
    freePoint(s->ponto);
    free (s);
}

void getSemaforoInformacao(Semaforo semaforo, char *info, char *posic){
    SemaforoImp s;
    s = (SemaforoImp) semaforo;
    sprintf(info, "%s", s->id);
    sprintf(posic, "(%.2lf, %.2lf)", s->x, s->y);
}


double coordPolarSemaforo(Semaforo s1, Semaforo s2){
  double x1, x2, y1, y2;
  SemaforoImp novaSemaforo1, novaSemaforo2;
  
  novaSemaforo1 = (SemaforoImp) s1;
  novaSemaforo2 = (SemaforoImp) s2;

  x1 = novaSemaforo1->x;
  x2 = novaSemaforo2->x;
  y1 = novaSemaforo1->y;
  y2 = novaSemaforo2->y;

  return atan2((y2-y1),(x2-x1));
}

int orientacaoSemaforo(Semaforo s1, Semaforo s2, Semaforo s3){
  double x1,y1,x2,y2,x3,y3,result;
  SemaforoImp novaSemaforo1,novaSemaforo2,novaSemaforo3;

  novaSemaforo1 = (SemaforoImp) s1;
  novaSemaforo2 = (SemaforoImp) s2;
  novaSemaforo3 = (SemaforoImp) s3;

  x1 = novaSemaforo1->x;
  x2 = novaSemaforo2->x;
  x3 = novaSemaforo3->x;
  y1 = novaSemaforo1->y;
  y2 = novaSemaforo2->y;
  y3 = novaSemaforo3->y;

  result = (y2-y1)*(x3-x2)-(x2-x1)*(y3-y2);

  if(result > 0)
    return 1;
  else if(result < 0)
    return -1;
  else
    return 0;
}

Point getKeySemaforo(Semaforo semaforo){
    SemaforoImp s;
    s = (SemaforoImp) semaforo;
    return s->ponto;
}

