#ifndef _LEITURA_GRY_H_
#define _LEITURA_GRY_H_
#include"leitura_geo.h"
#include "grafo.h"

/*  
*   realiza toda a leitura do arquivo .qry e chama as funções para cada operacão 
*   necessita de um arquivo .qry, as listas de forma, texto e objetos
*   nao retorna nada
*/
void Ler_arquivo_gry(FILE *qry, FILE *svg2, FILE *txt, Tree arvoreForma, Tree arvoreTexto, Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase, 
                    Tree arvorePosto, Tree arvoreCasos, HashTable pessoas, HashTable quadras, HashTable hidrantes, HashTable semaforos, HashTable radioBase, HashTable moradores, HashTable comercios, 
                     char *diretorioSaida, char *entradaGeoNew, char* entradaQryNew, Grafo caminhos,Lista listaCasoN, Lista listaCasoS, Lista listaCasoL, Lista listaCasoO, int contadorId);

#endif
