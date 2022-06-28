#ifndef _CONSULTAS_H_
#define _CONSULTAS_H_
#include"leitura_geo.h"

//TAD ELEMENTO

typedef void* Elemento;

/*
*   realiza a operação do o? do arquivo .qry
*   necessita do comando o? ter sido chamado
*   nao retorna nada
*/
void consulta_o(Tree arvoreForma, char j[], char k[], FILE*txt, FILE *aux_txt);

/*
*   realiza a operação do i? do arquivo .qry
*   necessita do comando i? ter sido chamado
*   nao retorna nada
*/
void consulta_i(Tree arvoreForma, char j[], double x, double y, FILE *txt, FILE *aux_txt);

/*
*   realiza a operação do pnt do arquivo .qry
*   necessita do comando pnt ter sido chamado
*   nao retorna nada
*/
void consulta_pnt(Tree arvoreForma, Tree arvoreTexto, char j[], char corBorda[], char corPreenchimento[], FILE *txt);

/*
*   realiza a operação do pnt* do arquivo .qry
*   necessita do comando pnt* ter sido chamado
*   nao retorna nada
*/
void consulta_pnt_2(Tree arvoreForma, Tree arvoreTexto, int j_num, int k_num, char corBorda[], char corPreenchimento[], FILE *txt);

/*
*   realiza a operação do delf do arquivo .qry
*   necessita do comando delf ter sido chamado
*   nao retorna nada
*/
void consulta_delf(Tree arvoreForma, Tree arvoreTexto, char j[], FILE *txt);

/*
*   realiza a operação do delf* do arquivo .qry
*   necessita do comando delf* ter sido chamado
*   nao retorna nada
*/
void consulta_delf_2(Tree arvoreForma, Tree arvoreTexto, int j_num, int k_num, FILE *txt);

/*
*   realiza a operação dq do arquivo .qry
*   necessita do comando dq ter sido chamado
*   nao retorna nada
*/
void consulta_dq(char aux[], char j[], double r, bool verificador, FILE* svg2, FILE* txt, FILE* txt_aux, Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase);

/*
*   realiza a operação del do arquivo .qry
*   necessita do comando del ter sido chamado
*   nao retorna nada
*/
void consulta_del(FILE* aux, Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase, char id[], FILE *svg2, FILE *txt);

/*
*   realiza a operação crd do arquivo .qry
*   necessita do comando crd ter sido chamado
*   nao retorna nada
*/
void consulta_crd(Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase, char id[], FILE *txt);

/*
*   realiza a operação cbq do arquivo .qry
*   necessita do comando cbq ter sido chamado
*   nao retorna nada
*/
void consulta_cbq(Tree arvoreQuadra, FILE* svg2, FILE *txt, double x, double y, double r, char corB[]);

/*
*   realiza a operação car do arquivo .qry
*   necessita do comando car ter sido chamado
*   nao retorna nada
*/
void consulta_car(FILE* aux, Tree arvoreQuadra, FILE* txt, double x, double y, double w, double h);

/*
 * realiza a operação cv do arquivo .qry
 * necessita do comando cv ter sido chamado
 * nao retorna nada
*/
void consulta_cv(Tree arvoreQuadra, Tree arvoreCasos, double casos, char cep[32], char face, double num, FILE* txt_aux, Lista listaCasoN, Lista listaCasoS, Lista listaCasoL, Lista listaCasoO);

/*
 * realiza a operação soc do arquivo .qry
 * necessita do comando soc ter sido chamado
 * nao retorna nada
 */
void consulta_soc(Tree arvoreQuadra, Tree arvorePosto, int posto_atendimento, char cep[32], char face, double num, FILE* txt_aux, FILE* txt);

/*
 * realiza a operação ci do arquivo .qry
 * necessita do comando ci ter sido chamado
 * nao retorna nada
 */
void consulta_ci(double x, double y, double r, FILE *aux, FILE *txt, Tree arvorePosto, Tree arvoreCasos);

/*
 * realiza a operação bf do arquivo .qry
 * necessita do comando bf ter sido chamado
 * nao retorna nada
 */
void tratarBf(double max, Tree arvoreQuadra, Lista listaCasoN, Lista listaCasoS, Lista listaCasoL, Lista listaCasoO, FILE *svg, FILE *txt);

#endif