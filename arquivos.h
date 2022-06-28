#ifndef _ARQUIVOS_H_
#define _ARQUIVOS_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

/*
*   cria o arquivo .svg no diretório de saída
*   necessita de um arquivo .geo ter sido identificado na entrada
*   retorna o nome do arquivo svg
*/
char * criarSvg(char entradaGeoNew[], char diretorioSaida[], char *arqsvg);

/*
*   cria um segundo arquivo .svg no diretorio de saida
*   necessita de um arquivo .geo e .qry terem sido identificados na entrada
*   retorna o nome do arquivo svg final
*/ 
char * criarSvg2(char entradaGeoNew[], char entradaQryNew[], char diretorioSaida[], char *arqsvg2);

/*
*   cria o .txt no diretório de saída
*   necessita de um arquivo .geo e .qry terem sido identificados na entrada
*   retorna o nome do arquivo de texto final
*/
char * criarTxt(char entradaGeoNew [], char entradaQryNew[],char diretorioSaida[], char *arqtxt);

/*
 * cria e concatena o svg para o comando dmprbt, descrevendo visualmente a arvore
 * necessita do comando dmprbt ter sido invocado
 * retorna um arquivo svg
 */
char * criarSvg3(char entradaGeoNew[], char entradaQryNew[], char entradaSfx[], char diretorioSaida[], char *arqsvg);

#endif 