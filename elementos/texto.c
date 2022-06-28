#include"texto.h"
struct StTexto{
	char id[32];
	double x, y;
	char corBorda[32], corPreenchimento[32], tipo[4],conteudo[128];
    Point ponto;
};

typedef struct StTexto *TextoImp;

Texto criarTexto(char id[], char tipo[], double x, double y, char corBorda[], char corPreenchimento[], char conteudo []){
    TextoImp novo;
    Point ponto = createPoint(x, y);
    novo = (TextoImp) malloc (sizeof (struct StTexto));
    strcpy(novo->id, id);
    novo->x = x;
    novo->y = y;
    strcpy (novo->tipo,tipo);
    strcpy (novo->corBorda, corBorda);
    strcpy (novo->corPreenchimento, corPreenchimento);
    strcpy (novo->conteudo, conteudo);

    return novo;
}
double getXTexto (Texto texto){
    TextoImp t;
    t =  (TextoImp) texto;
    return t->x; 
}
double getYTexto (Texto texto){
    TextoImp t;
    t =  (TextoImp) texto;
    return t->y; 
}
char* getcorBordaTexto (Texto texto){
    TextoImp t;
    t =  (TextoImp) texto;
    return t->corBorda; 
}
char* getcorPreenchimentoTexto (Texto texto){
    TextoImp t;
    t =  (TextoImp) texto;
    return t->corPreenchimento; 
}
char* getConteudoTexto (Texto texto){
    TextoImp t;
    t =  (TextoImp) texto;
    return t->conteudo; 
}

char* getIdTexto(Texto texto){
    TextoImp t;
    t =  (TextoImp) texto;
    return t->id; 
}

char* getTipoTexto (Texto texto){
    TextoImp t;
    t = (TextoImp) texto;
    return t->tipo;
}

void setcorBordaTexto(Texto texto, char corBorda[]){
    TextoImp t;
    t = (TextoImp) texto;
    strcpy(t->corBorda, corBorda);
}

void setcorPreenchimentoTexto(Texto texto, char corPreenchimento[]){
    TextoImp t;
    t = (TextoImp) texto;
    strcpy(t->corPreenchimento, corPreenchimento);
}

void freeTexto(Texto texto){
    TextoImp t;
    t = (TextoImp) texto;
    freePoint(t->ponto);
    free(t);
}

Point getKeyTexto(Texto texto){
    TextoImp t;
    t = (TextoImp) texto;
    return t->ponto;
}