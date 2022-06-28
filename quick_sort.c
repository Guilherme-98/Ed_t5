#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "./elementos/casos.h"
#include <stdbool.h>

int orientation(Casos p, Casos q, Casos r) { 
   
    int val = (getYCasos(q) - getYCasos(p)) *  (getXCasos(r) - getXCasos(q)) - 
              (getXCasos(q) - getXCasos(p)) * (getYCasos(r) - getYCasos(q));
              
    if (val == 0) return 0;  
    return (val > 0)? 1: 2; 
} 

double distSq(Casos c1, Casos c2) 
{ 
    return (getXCasos(c1) - getXCasos(c2))*(getXCasos(c1) - getXCasos(c2)) + 
          (getYCasos(c1) - getYCasos(c2))*(getYCasos(c1) - getYCasos(c2)); 
} 


extern Casos casoInit;
int comparar2( void *caso1,  void *caso2){
    
    int o = orientation(casoInit, caso1, caso2);
    
    if( o == 0)
        return (distSq(casoInit, caso2) >= distSq(casoInit, caso1))? -1 : 1; 

    return (o == 2)? -1: 1;
}
                                                                                    
void quicksort(Casos values[], int began, int end){
                                                                                                                                                                                                                               
    int i, j;   
    Casos pivo, aux;
    i = began;
    j = end;
    pivo = values[(began + end) / 2];
    while(i <= j){

        while(comparar2(values[i],  pivo) < 0 && i <  end ){
            i++;
        }
        while(comparar2(values[j], pivo) > 0 && j > began){
            j--;
        }
        if(i <= j){
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;
            i++;
            j--;
        }
    }
    if(j > began)
        quicksort(values, began, j);
    if(i < end)
        quicksort(values, i, end);
}
