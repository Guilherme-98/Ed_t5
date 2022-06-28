#include <stdio.h>
#include <stdlib.h>
#include"lista.h"

int shellSort(Dist  distancia[], int k, int quant_posto){
    Dist temp;
    int i, j, h;
    for(h = 1; h < quant_posto; h = 3*h+1);

    while(h>0){
        h = (h-1)/3;
        for(i = h; i < quant_posto; i++){
            temp = getDist(distancia[i]);
            j = i;
            while (getDistancia(distancia[j-h]) > getDistancia(temp)){
                distancia[j] = distancia[j-h];
                j -= h;
                if(j < h){
                    break;
                }
            }
            distancia[j] = temp;
        }
    }
    return 0;
}