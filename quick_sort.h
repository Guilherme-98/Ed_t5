#ifndef __quick_sort__
#define __quick_sort__

/*
 * orienta os casos para mudar identificar onde esta o pivo no quicksort
 * necessita de uma lista de casos ligada, e de pelo menos 2 casos
 * retorna o resultado de uma comparação
 */
int orientation(Casos casosInit, Casos c1, Casos c2); 

/*
 * calcula a distancia entre casos
 * necessita de 2 casos
 * retorna o valor da distancia
 */
double distSq(Casos c1, Casos c2);

/*
 * ordena os pontos que estão dentro do circulo
 * necessita de uma lista de pontos, o indece do começo da lista e o indece do final da lista 
 * retorna nada apenas ordena a lista
 */                             
void quicksort(Casos values[], int began, int end);

#endif
