#ifndef _SVG_H_
#define _SVG_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h> 
#include"leitura_geo.h"
#include"./elementos/quadra.h"
#include"./elementos/forma.h"
#include"./elementos/texto.h"
#include"./elementos/hidrante.h"
#include"./elementos/semaforo.h"
#include"./elementos/radioBase.h"
#include"./elementos/posto.h"





/*
*   imprime as formas no formato svg
*   necessita de um arquivo svg e de uma lista de formas
*   nao retorna nada
*/
void svg_imprimir_forma(FILE *arqsvg, Forma forma);

/*
*   imprime um quadrado no formato svg
*   necessita de um arquivo svg e de parametros (x,y) de um quadrado
*   nao retorna nada
*/
void svg_imprimir_quadrado(FILE *arqsvg, double x, double y, char corPreenchimento[32], char corBorda[32]);

/*
*   imprime as quadras no formato svg
*   necessita de um arquivo svg e de uma lista de quadras
*   nao retorna nada
*/
void svg_imprimir_quadra(FILE *arqsvg, Quadra quadra);

/*
*   imprime os hidrantes no formato svg
*   necessita de um arquivo svg e de uma lista de hidrantes
*   nao retorna nada
*/
void svg_imprimir_hidrante(FILE *arqsvg, Hidrante hidrante);

/*
*   imprime os semaforos no formato svg
*   necessita de um arquivo svg e de uma lista de semaforos
*   nao retorna nada
*/
void svg_imprimir_semaforo(FILE *arqsvg, Semaforo semaforo);

/*
*   imprime os radio bases no formato svg
*   necessita de um arquivo svg e de uma lista de radio bases
*   nao retorna nada
*/
void svg_imprimir_rb(FILE *arqsvg, RadioBase radiobase);

/*
*   imprime um ponto no formato svg
*   necessita de um arquivo svg e de coordenadas dadas
*   nao retorna nada
*/
void svg_imprimir_ponto(FILE *arqsvg, char cor[], double x, double y);

/*
*   imprime os textos no formato svg
*   necessita de um arquivo svg e de uma lista de textos
*   nao retorna nada
*/
void svg_imprimirTexto(FILE *arqtxt, Texto texto);

/*
*   imprime uma linha no formato svg
*   necessita de um arquivo svg, coordenadas e cor para a linha
*   nao retorna nada
*/
void svg_imprimir_linha (FILE *svg, double x1, double y1, double x2, double y2, char cor[]);

/*
*   imprime uma linha tracejada no formato svg
*   necessita de um arquivo svg, coordenadas e cor para a linha
*   nao retorna nada
*/
void svg_imprimir_linha_trace (FILE *svg, double x1, double y1, double x2, double y2, char cor[]);

/*
*   imprime os postos no formato svg
*   necessita de um arquivo svg e de uma lista de postos
*   nao retorna nada
*/
void svg_imprimir_posto(FILE *arqsvg, Posto posto);

/*
*   imprime uma quadra arredondada no formato svg, quando o comando dq for chamado
*   necessita de um arquivo svg e de uma lista de quadras
*   nao retorna nada
*/
void svg_imprimir_quadArrend(FILE *arqsvg, Quadra quadra);

/*
*   imprime um anel no formato svg, quando o comando dq for chamado
*   necessita de um arquivo svg, de um elemento e seu tipo
*   nao retorna nada
*/
void anelGrosso(FILE *arqsvg, Elemento e, char tipo[]);

/*
* imprime um poligono convexo
* necessita de uma lista de casos de covid na região interior ao circulo
*  nao retorna nada
*/
void svg_imprimir_poligono(FILE *arqsvg, double x, double y);

/*
*  imprime um circulo no raio especificado e em volta do objeto especificado pelo comando dq
*  necessita de um objeto e o raio passados pela entrada do comando
*  nao retorna nada
*/
void anelDq(FILE *arqsvg, Elemento e, char tipo[], double r);

/*
* Imprime um circulo no svg
* Nao retorna nada
*/
void svg_imprimir_circulo(FILE *arqsvg, double x, double y, double r, char corBorda[32], char corPreenchimento[32]);

/*
* Imprime um circulo transparente no svg
* Nao retorna nada
*/
void svg_imprimir_circulo_transparente(FILE *arqsvg, double x, double y, double r, char corBorda[32], char corPreenchimento[32]);

/*
* Insere sombras no svg a partir de um retangulo passado
* nao retorna nada
*/
void svg_drop_shadow(FILE *arqsvg, double x, double y, double w, double h, char corSombra[32], char corBorda[32], char corPreench[32]);

/*
* Imprime um segmento de reta para realizar o tracejado de um caminho 
* nao retorna nada
*/
void printCaminho(FILE *arqsvg, double x1, double y1, double x2, double y2, char *color, int sw);

/*
* Abre o comando resposavel pela animação do arquivo svg
* Imprime um segmento de reta para realizar a animação do caminho
* nao retorna nada
*/
void animationPath(FILE *arqsvg, double x, double y, int contador);

/*
* fecha o comando resposavel pela animação do arquivo svg
* nao retorna nada
*/
void fecharPath(FILE *arqsvg, int contadorId);

#endif
