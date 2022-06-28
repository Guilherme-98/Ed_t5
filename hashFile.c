#include "hashFile.h"

static int hashFunc(int key) {
	return ((int)pow(key, 2)) % NUM_BALDES;
}

typedef struct Item{
    int key;
    long int value;
}Item;

typedef struct Balde {
    int quatRegBalde;
    Item items[MAX_REGS_BALDE];
    char trash[SIZE_TRASH];
    long int posCont;
}Balde;

Hashfile fcreateHF(char *fileName) {
    Balde balde;
    balde.quatRegBalde = 0;
    balde.posCont = -1;

    FILE *file;
    file = fopen(fileName, "wb");

    for(int i=0; i<NUM_BALDES; i++){
        fwrite(&balde, sizeof(Balde), 1, file);
    }
    fclose(file);
}

int fwriteRec(char * fileName, int key, int value){
    FILE *file = fopen(fileName, "r+b");
    int position = hashFunc(key);

    fseek(file, position*sizeof(Balde), SEEK_SET);

    long int posBaldeInsercao = ftell(file);

    Balde balde;
    fread(&balde, sizeof(Balde), 1, file);

    while(balde.quatRegBalde == MAX_REGS_BALDE){
        if(balde.posCont == -1){ 
            fseek(file, -sizeof(Balde), SEEK_CUR);  
            long int posAnterior = ftell(file);      

            fseek(file, 0, SEEK_END);               
            posBaldeInsercao = ftell(file);    

            balde.posCont = posBaldeInsercao;   

            fseek(file, posAnterior, SEEK_SET);     
            fwrite(&balde, sizeof(Balde), 1, file);  

            balde.quatRegBalde =  0;  
            balde.posCont = -1;      

        }else{  
            fseek(file, balde.posCont, SEEK_SET);
            posBaldeInsercao = ftell(file);             
            fread(&balde, sizeof(Balde), 1, file);     
        }
    }

    balde.items[balde.quatRegBalde].key = key;
    balde.items[balde.quatRegBalde].value = value;
    balde.quatRegBalde++;

    fseek(file, posBaldeInsercao, SEEK_SET);
    fwrite(&balde, sizeof(Balde), 1, file);

    fclose(file);
    return 0;
}

int freadHF(char * fileName, int key, int limit, Lista **resultList) {
    FILE * file = fopen(fileName, "rb");
    int position = hashFunc(key);

    fseek(file, position*sizeof(Balde), SEEK_SET);

    int find = 0;
    int finished = 0;
    while (!finished){
        Balde balde;
        fread(&balde, sizeof(Balde), 1, file);

        for(int i=0; i<balde.quatRegBalde && find < limit; i++) {
            if (key == balde.items[i].key){
                find++;
                addToResultList(resultList, balde.items[i].value, -1);
            }
        }
        if(balde.posCont == -1 || find >= limit)
            finished = 1;
        else
            fseek(file, balde.posCont, SEEK_SET);
    }
    fclose(file);
    return find;
}