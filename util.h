#ifndef _UTIL_H_
#define _UTIL_H_
#include<math.h>
#include"leitura_geo.h"
#include"./elementos/forma.h"


/*
*   calcula a distância entre duas formas
*   necessita de coordenadas p/ serem passadas
*   retorna a distancia euclidiana
*/
double distanciaEuclidiana (double x1, double y1, double x2, double y2);   

/*
*   informa se dois circulos estão juntos ou não
*   necessita de 2 formas passadas
*   retorna se um circulo sobrepõe o outro ou não
*/
bool circulo_circulo (Forma forma1, Forma forma2);

/*
*   informa se dois retangulos estão juntos ou não
*   necessita de 2 formas passadas
*   retorna se um retangulo sobrepõe o outro ou não
*/
bool retangulo_retangulo (Forma forma1, Forma forma2);

/*
*   informa se um retangulo e um circulo estão juntos ou não
*   necessita de 2 formas passadas
*   retorna se uma forma sobrepõe a outra ou não
*/
bool circulo_ou_retangulo(Forma forma1, Forma forma2);

/*
*   imprimi o retangulo delimitador no arquivo .svg
*   necessita de 2 formas passadas, e 1 arquivo svg final
*   nao retorna nada
*/
void imprimir_retangulo_delimitador(Forma forma1, Forma forma2, bool sobrepoem, FILE *svg2);

/*
 *  faz o calculo da densidade da população na area especificada
 *  necessita de uma area(retangulo), e do numero de habitantes
 *  retorna a densidade
 */
double calculoDensidade(double w, double h, double habitantes);

#endif
