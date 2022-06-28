#include"forma.h"
struct StForma{
    char id[32];
    double x, y, r, w, h;
    char corBorda[32], corPreenchimento[32], tipo[4], sw[10];
    Point ponto;
};
typedef struct StForma *FormaImp;

Forma criarForma (char id[],char tipo[], double x, double y, double r, double w,double h, char corBorda[], char corPreenchimento[], char sw[]){
    FormaImp novo;
    novo = (FormaImp)malloc (sizeof (struct StForma));
    Point ponto = createPoint(x, y);
    novo->ponto = ponto;
    strcpy (novo->id,id);
    novo->x = x;
    novo->y = y;
    novo->r = r;
    novo->w = w;
    novo->h = h;
    strcpy (novo->tipo,tipo);
    strcpy (novo->corBorda, corBorda);
    strcpy (novo->corPreenchimento, corPreenchimento);
    strcpy (novo->sw, sw);

    return novo;
}

double getXForma (Forma forma){
    FormaImp f;
    f =  (FormaImp) forma;
    return f->x; 
}

double getYForma (Forma forma){
    FormaImp f;
    f =  (FormaImp) forma;
    return f->y; 
}

char* getSWForma (Forma forma){
    FormaImp f;
    f =  (FormaImp) forma;
    return f->sw;
}

void freeForma (Forma forma){
    FormaImp f;
    f = (FormaImp) forma;
    freePoint(f->ponto);
    free (f);
}

char* getTipoForma (Forma forma){
    FormaImp f;
    f = (FormaImp) forma;
    return f->tipo;
}
char* getIdForma(Forma forma){
    FormaImp f;
    f = (FormaImp) forma;
    return f->id;
}
double getRaioForma (Forma forma){
    FormaImp f;
    f = (FormaImp) forma;
    return f->r;
}

double getWForma (Forma forma){
    FormaImp f;
    f =  (FormaImp) forma;
    return f->w; 
}

double getHForma (Forma forma){
    FormaImp f;
    f =  (FormaImp) forma;
    return f->h; 
}

char* getcorBordaForma (Forma forma){
    FormaImp f;
    f =  (FormaImp) forma;
    return f->corBorda; 
}

char* getcorPreenchimentoForma (Forma forma){
    FormaImp f;
    f =  (FormaImp) forma;
    return f->corPreenchimento; 
}
void setcorPreenchimentoForma(Forma forma, char corPreenchimento[]){
    FormaImp f;
    f = (FormaImp) forma;
    strcpy(f->corPreenchimento, corPreenchimento);
}

void setcorBordaForma(Forma forma, char corBorda[]){
    FormaImp f;
    f = (FormaImp) forma;
    strcpy(f->corBorda, corBorda);
}

Point getKeyForma(Forma forma){
    FormaImp p;
    p = (FormaImp) forma;
    return p->ponto;
}
