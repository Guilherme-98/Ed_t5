#include"posto.h"
struct StPosto {
    char tipo[4],corBorda[32],corPreenchimento[32];
    Point ponto;
};

typedef struct StPosto *PostoImp;

Posto criarPosto(double x, double y, char corPreenchimento[], char corBorda[]){
    PostoImp novo;
    Point ponto = createPoint(x, y);
    novo = (PostoImp) malloc (sizeof (struct StPosto));
    novo->ponto = ponto;
    strcpy(novo->tipo,"sp");
    strcpy (novo->corBorda, corBorda);
    strcpy (novo->corPreenchimento, corPreenchimento);
    return novo;
}

double getXPosto (Posto posto){
    PostoImp p;
    p = (PostoImp) posto;
    return getPointX(p->ponto); 
}

double getYPosto (Posto posto){
    PostoImp p;
    p = (PostoImp) posto;
    return getPointY(p->ponto); 
}

char* getcorBordaPosto (Posto posto){
    PostoImp p;
    p = (PostoImp) posto;
    return p->corBorda;
}
char* getcorPreenchimentoPosto (Posto posto){
    PostoImp p;
    p = (PostoImp) posto;
    return p->corPreenchimento;
}


void freePosto (Posto posto){
    PostoImp p;
    p = (PostoImp) posto;
    freePoint(p->ponto);
    free (p);
}

Point getKeyPosto(Posto posto){
    PostoImp p;
    p = (PostoImp) posto;
    return p->ponto;
}
