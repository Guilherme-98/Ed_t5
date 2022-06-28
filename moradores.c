#include "moradores.h"
#include "./elementos/quadra.h"

typedef struct stMoradores {
    char cep[32], face[2], compl[16];
    int num;
    Pessoa pessoa;
    double x, y;
} *MoradoresImp;

Moradores criarMoradores (char cpf[], char cep[], char face[], char compl[], int num, HashTable pessoas, HashTable QuadrasTable){
    MoradoresImp moradores = (MoradoresImp) malloc (sizeof (struct stMoradores));

    strcpy (moradores->cep, cep);
    strcpy (moradores->face, face);
    strcpy (moradores->compl, compl);
    moradores->num = num;

    Pessoa pessoa = NULL;
    bool found = false;
    for(int i = 0; i < getHashTableSize(pessoas); i++){
        ListNode node = getHashNode(pessoas, i);
        while(node != NULL){
            pessoa = getHashNodeElement(node);
            if(!strcmp(getPessoaCpf(pessoa), cpf)){
                found = true;
                break;
            }

            node = getHashNodeNext(node);
        }

        if(found) break;
    }

    moradores->pessoa = pessoa;
    char key[64];
    char n[8];
    sprintf(n, "%d", moradores->num);
    strcpy(key, moradores->cep);
    strcat(key, moradores->face);
    strcat(key, n);


    Quadra quadra = searchHashTable(QuadrasTable, cep);

    if(quadra != NULL){
        insertHashTable(getQuadraMoradores(quadra), getPessoaCpf(pessoa), moradores);

        double xB = getXQuadra(quadra), yB = getYQuadra(quadra), wB = getWQuadra(quadra), hB = getHQuadra(quadra);
        if(!strcmp(face, "N")){
            moradores->x = xB + num;
            moradores->y = yB + hB;
        }
        else if(!strcmp(face, "S")){
            moradores->x = xB + num;
            moradores->y = yB;
        }
        else if(!strcmp(face, "O")){
            moradores->x = xB + wB;
            moradores->y = yB + num;
        }
        else if(!strcmp(face, "L")){
            moradores->x = xB;
            moradores->y = yB + num;
        }
    }

    return moradores;
}

char* getMoradoresCpf (Moradores r){
    MoradoresImp moradores = (MoradoresImp) r;

    return getPessoaCpf(moradores->pessoa);
}
char* getMoradoresCep (Moradores r){
    MoradoresImp moradores = (MoradoresImp) r;

    return moradores->cep;
}
char* getMoradoresFace (Moradores r){
    MoradoresImp moradores = (MoradoresImp) r;

    return moradores->face;
}
char* getMoradoresCompl (Moradores r){
    MoradoresImp moradores = (MoradoresImp) r;

    return moradores->compl;
}

int getMoradoresNum (Moradores r){
    MoradoresImp moradores = (MoradoresImp) r;

    return moradores->num;
}

Pessoa getMoradoresPessoa(Moradores r){
    MoradoresImp moradores = (MoradoresImp) r;

    return moradores->pessoa;
}


double getMoradoresX(Moradores r){
    MoradoresImp moradores = (MoradoresImp) r;

    return moradores->x;
}

double getMoradoresY(Moradores r){
    MoradoresImp moradores = (MoradoresImp) r;

    return moradores->y;
}

void setMoradoresCep (Moradores r, char cep[]){
    MoradoresImp moradores = (MoradoresImp) r;

    strcpy (moradores->cep, cep);
}

void setMoradoresFace (Moradores r, char face[]){
    MoradoresImp moradores = (MoradoresImp) r;

    strcpy (moradores->face, face);
}

void setMoradoresNum (Moradores r, int num){
    MoradoresImp moradores = (MoradoresImp) r;

    moradores->num = num;
}

void setMoradoresCompl (Moradores r, char compl[]){
    MoradoresImp moradores = (MoradoresImp) r;

    strcpy (moradores->compl, compl);
}

void mudancaMoradoresEndereco(Moradores r, char cep[], char face[], int num, char compl[]){
    setMoradoresCep (r, cep);
    setMoradoresFace (r, face);
    setMoradoresNum (r, num);
    setMoradoresCompl (r, compl);
}

void destroiMoradores(Moradores r){
    
    free(r);
}


