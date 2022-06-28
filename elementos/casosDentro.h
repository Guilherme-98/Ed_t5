#ifndef __casosDentro__
#define __casosDentro__

//TAD CASOS DENTRO
typedef void *CasosDentro;

/*
*   cria os casos dentro do circulo
*   necessita de que o comando ci tenha sido chamado
*   retorna o caso dentro criado
*/
CasosDentro criarCasosDentro(double x, double y, double n);

/*
*   busca o X do caso
*   necessita de um caso criado
*   retorna o X do caso
*/
double getXCasosDentro(CasosDentro caso);

/*
*   busca o Y do caso
*   necessita de um caso criado
*   retorna o Y do caso
*/
double getYCasosDentro(CasosDentro caso);

/*
*   busca o N do caso
*   necessita de um caso criado
*   retorna o N do caso
*/
double getNCasosDentro(CasosDentro caso);

/*
*   libera a lista de casos dentro criada
*   necessita de um caso criado
*   nao retorna nada
*/
void freeCasosDentro (CasosDentro caso);

#endif