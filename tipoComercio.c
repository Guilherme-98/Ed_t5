#include "tipoComercio.h"

typedef struct codtComercio {
    char codt[32], descricao[128];
} *CodtComercioImp;

TipoComercio criarTipoComercio (char codt[], char descricao[]){
    CodtComercioImp rCodtComercio = (CodtComercioImp) malloc (sizeof (struct codtComercio));

    strcpy (rCodtComercio->codt, codt);
    strcpy (rCodtComercio->descricao, descricao);

    return rCodtComercio;
}

char* getTipoComercioCodt (TipoComercio sTipo){
    CodtComercioImp TipoComercio = (CodtComercioImp) sTipo;

    return TipoComercio->codt;
}

char* getTipoComercioDesc (TipoComercio sTipo){
    CodtComercioImp TipoComercio = (CodtComercioImp) sTipo;

    return TipoComercio->descricao;
}