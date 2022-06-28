#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "grafo.h"

void Ler_arquivo_via(FILE *via, Grafo caminhos){  
    char id[32], operacao[8], id1[32], id2[32], ladoDireito[32], ladoEsquerdo[32], rua[32];
    double x, y, comprimento, velocidade;
   

    if(via != NULL){
       
        while(1){
            fscanf(via, "%s", operacao);

            if(feof(via))
                break;

            if(strcmp(operacao, "v") == 0){
                fscanf(via, "%s", id);
                fscanf(via, "%lf", &x);
                fscanf(via, "%lf", &y);

                addVertice(caminhos, id, x, y);
                
            }

            if(strcmp(operacao, "e") == 0){
                fscanf(via, "%s", id1);
                fscanf(via, "%s", id2);
                fscanf(via, "%s", ladoDireito);
                fscanf(via, "%s", ladoEsquerdo);
                fscanf(via, "%lf", &comprimento);
                fscanf(via, "%lf", &velocidade);
                fscanf(via, "%s", rua);

                addAresta(caminhos, id1, id2, rua, ladoDireito, ladoEsquerdo, comprimento, velocidade);
                

            }
        }
    }
}
