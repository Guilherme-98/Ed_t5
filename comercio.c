#include"comercio.h"

typedef struct stStore {
    char cnpj[32], cep[32], face[2], nome[32];
    int num;
    double x, y;
    TipoComercio storeType;
    Pessoa owner;
    Quadra block;
} *StoreImp;

Comercio criarComercio (char cnpj[], char cpf[], char codt[], char cep[], char face[], int num, char nome[], HashTable storeTypes, HashTable persons, Quadra block){
    StoreImp store = (StoreImp) malloc (sizeof (struct stStore));

    double xB = getXQuadra(block), yB = getYQuadra(block), wB = getWQuadra(block), hB = getHQuadra(block);

    if(!strcmp(face, "N")){
        store->x = xB + num;
        store->y = yB + hB;
    }
    else if(!strcmp(face, "S")){
        store->x = xB + num;
        store->y = yB;
    }
    else if(!strcmp(face, "O")){
        store->x = xB + wB;
        store->y = yB + num;
    }
    else if(!strcmp(face, "L")){
        store->x = xB;
        store->y = yB + num;
    }

    strcpy (store->cnpj, cnpj);
    strcpy (store->cep, cep);
    strcpy (store->face, face);
    store->num = num;
    strcpy (store->nome, nome);

    bool found = false;
    for(int i = 0; i < getHashTableSize(storeTypes); i++){
        ListNode node = getHashNode(storeTypes, i);
        while(node != NULL){
            TipoComercio storeType = getHashNodeElement(node);

            if(!strcmp(codt, getTipoComercioCodt(storeType))){
                found = true;
                store->storeType = storeType;
                break;
            }
            node = getHashNodeNext(node);
        }

        if(found) break;
    }

    found = false;
    for(int i = 0; i < getHashTableSize(persons); i++){
        ListNode node = getHashNode(persons, i);

        while(node != NULL){
            Pessoa person = getHashNodeElement(node);
            if(!strcmp(cpf, getPessoaCpf(person))){
                found = true;
                store->owner = person;
                break;
            }
            node = getHashNodeNext(node);
        }

        if(found) break;
    }

    store->block = block;

    return store;
}

char* getComercioCnpj (Comercio s){
   StoreImp comercio = (StoreImp) s;

    return comercio->cnpj;
} 

char* getComercioOwner (Comercio s){
   StoreImp comercio = (StoreImp) s;

    return comercio->owner;
}   

char* getComercioCep (Comercio s){
   StoreImp comercio = (StoreImp) s;

    return comercio->cep;
}  
 
char* getComercioFace (Comercio s){
   StoreImp comercio = (StoreImp) s;

    return comercio->face;
} 

char* getComercioName (Comercio s){
   StoreImp comercio = (StoreImp) s;

    return comercio->nome;
} 

int getComercioNum (Comercio s){
   StoreImp comercio = (StoreImp) s;

    return comercio->num;
}

double getComercioX(Comercio s){
   StoreImp comercio = (StoreImp) s;

    return comercio->x;
}

double getComercioY(Comercio s){
   StoreImp comercio = (StoreImp) s;

    return comercio->y;
}

TipoComercio getComercioType(Comercio s){
   StoreImp comercio = (StoreImp) s;

    return comercio->storeType;
}

Quadra getComercioBloco(Comercio s){
   StoreImp comercio = (StoreImp) s;

    return comercio->block;
}

void destroiComercio(Comercio s){
    
    free(s);
}