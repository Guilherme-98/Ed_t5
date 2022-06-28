#ifndef __lista__
#define __lista__
#include<stdbool.h>
#include"quadTree.h"
#include"hashTable.h"


//TADS
typedef void* No;
typedef void* Lista;
typedef void* Elemento;
typedef void* Dist;
typedef void* Casos;

/*
*   cria uma lista vazia
*   sem requerimentos
*   retorna uma lista vazia
*/
Lista create();

/*
*   insere um elemento na lista
*   necessita de uma lista iniciada
*   nao retorna nada
*/
void insert(Lista l, Elemento elemento, char tipo[]);

/*
*   imprime todos os elementos da lista
*   uma lista com pelo menos um elemento
*   nao retorna nada
*/
void print(FILE* svg, Lista l);

/*
*   procura o elemento na lista
*   necessita de uma lista iniciada
*   retorna o elemento especificado
*/
No get(Lista l, char id[]);

/*
*   procura o tipo do elemento na lista
*   necessita de uma lista iniciada
*   retorna o tipo do elemento especificado
*/
char* getTipo(Lista l, char id[]);

/*
*   remove um elemento especificado
*   necessita de pelo menos 1 elemento na lista
*   nao retorna nada
*/
void remover (Lista l, char id[]);

/*
*    insere um elemento antes do id inserido
*    necessita uma lista iniciada
*    nao retornada nada
*/

void pop(Lista l);

/*
*    retira o elemento do topo da lista
*    necessita uma lista iniciada
*    nao retornada nada
*/

void insertBefore(Lista l, Elemento elemento, char id[], char *tipo);

/*
*    insere um elemento depois do id inserido
*    necessita uma lista iniciada
*    nao retornada nada
*/
void insertAfter(Lista l, Elemento elemento, char id[], char *tipo);

/*
*   pega o primeiro elemento da lista
*   necessita uma lista com pelo menos 1 elemento
*   retorna o primeiro elemento
*/
No getFirst(Lista l);

/*
*   pega o ultimo elemento da lista
*   necessita uma lista com pelo menos 1 elemento
*   retorna o ultimo elemento
*/
No getLast(Lista l);

/*
*   pega o elemento seguinte do id inserido
*   necessita de uma lista com pelo menos mais de 1 elemento
*   retorna o proximo elemento do id inserido
*/
No getNext(Lista l, char id[]);

/*
*   pega o elemento anterior do id inserido
*   necessita de pelo menos uma lista com mais de 1 elemento
*   retorna o elemento anterior do id inserido
*/  
No getPrevious(Lista l, char id[]);

/*
*   percorre as listas para efetuar o comando qry dq
*   necessita do comando dq ter sido chamado
*   nao retorna nada
*/
void Dq_percorrer(Lista quadra, Elemento e, double r, char tipo[], FILE *txt, FILE* svg2, bool verificador);

/*
*   percorre as quadras para mudar as cores dos respectivos ceps lidos
*   necessita do comando cbq ter sido chamado
*   nao retorna nada
*/
void cbqFunction(Lista quadra, FILE* txt, FILE* svg2, double x, double y, double r, char CorBorda[]);

/*
*   percorre as quadras para realizar os devidos calculos
*   necessita do comando car ter sido chamado
*   retorna a area total calculada
*/
double carFunction(FILE* aux, FILE* txt, Lista listaQuadra, Lista listaHidrante, Lista listaSemaforo, Lista listaRadioBase, double x, double y, double h, double w);

/*
*   percorre as listas para buscar os elementos que existem
*   necessita de elementos inseridos na lista
*   retorna o elemento existente
*/
No encontrarElementoListas(char id[], Lista listaQuadra, Lista listaHidrante, Lista listaSemaforo, Lista listaRadioBase);


/*
*   da free nas listas e nos elementos
*   necessita de uma lista com pelo menos 1 elemento
*   nao retorna nada
*/
void freeMem(Lista lista, void *freeElemento);

/*
*   percorre as listas para identificar o tipo do elemento desejado
*   necessita de uma lista com pelo menos 1 elemento
*   retorna o tipo do elemento encontrado
*/
char* encontrarTipo (char id[], Lista listaQuadra, Lista listaHidrante, Lista listaSemaforo, Lista listaRadioBase);

/*
 * percorre a lista de postos para poder usa-los no comando e orderna-los com o shellsort
 * necessita de postos criados pelo arquivo .geo
 * nao retorna nada
 */
void soc_percorrer(Lista listaPosto, double x, double y, int posto_atendimeneto, FILE *txt, FILE *svg2);

/*
 * percorre a lista de casos para poder identificar quais casos estao dentro da regiao especificada pelo circulo
 * necessita de casos criados
 * retorna o numero total de casos identificados
 */
double ci_percorrer(Lista listaCasos, Lista cd, double x, double y, double raio, FILE *txt);

/*
 * algoritmo que ordena os pontos de casos para formar um poligono convexo
 * necessita de uma lista de casos dentro da regiao do circulo
 * retorna a lista de pontos de casos ordenados atraves de quicksort
 */
Lista convexHull(Lista ListaCd);

/*
 * percorre os pontos do poligono convexo
 * necessita de pontos de casos formando um poligono
 * nao retorna nada
 */
void percorrerPontosPoligono(Lista pontosPoligono, FILE *aux);

/*
 * comparar 2 casos para utilização no convexhull
 * necessita de pelo menos 2 casos para comparação
 * retorna um inteiro em relação ao resultado da comparação
 */
int comparar(const void *caso1, const void *caso2);

/* retorna uma distancia atraves de uma struct de uma lista de distancias entre postos de saude
 * necessita de um posto de saude
 * retorna uma distancia
 */
Dist getDist(Dist distAux);

/*
 * retorna uma distancia de posto de saude atraves de uma lista ordenada por shellsort
 * necessita de um posto de saude
 * retorna uma distancia
 */
double getDistancia(Dist distAux);

/*
 * calcula a area de um poligono convexo
 * necessita de um poligono convexo no mapa
 * retorna sua area
 */
double calcularArea(Lista listaPoligno);

/*
 * percorre uma lista casos, para poder printar as linhas laterais do poligono
 * necessita de uma lista de casos ordenada
 * nao retorna nada
 */
void percorrer_poligono_svg (Lista listaPoligono, FILE*aux);

/*
 * verifica se ha algum posto de saude num poligono de pior categoria (categoria E)
 * necessita de um poligono convexo e a lista de postos de saude
 * retorna uma verificação entre true ou false
 */
bool flagPointInside(Lista pontosPoligono, Lista postos);

/*
 * calcula e desenha o ponto centroide de um poligono convexo para inserir um posto de saude
 * necessita do poligono convexo, e de sua area
 * nao retorna nada
 */
void centroide(Lista listaPoligono, double area, FILE *aux);

/*
 * Remove as quadras pelo comando dq
 * Necessita do comando dq ter sido invocado
 * Nao retorna nada
 */
void dq_quadra_remover(Lista listaQuadra, Tree arvoreQuadra);

/*
 * Percorre uma lista temporaria pelo comando car para calcular a area
 * Necessita de uma lista criada e do comando car ter sido invocado
 * Retorna a area final
 */
double car_quadra_percorrer(Lista listaQuadra);

/*
 * Remove uma quadra pelo comando catac
 * Necessita do comando cata ter sido chamado
 * Retorna nada
 */
void catac_quadra_remover(Lista removerQuadra, Tree arvoreQuadra);

/*
 * Remove um hidrante pelo comando catac
 * Necessita do comando cata ter sido chamado
 * Retorna nada
 */
void catac_hidrante_remover(Lista removerHidrante, Tree arvoreHidrante);

/*
 * Remove um semaforo pelo comando catac
 * Necessita do comando cata ter sido chamado
 * Retorna nada
 */
void catac_semaforo_remover(Lista removerSemaforo, Tree arvoreSemaforo);

/*
 * Remove uma radio base pelo comando catac
 * Necessita do comando cata ter sido chamado
 * Retorna nada
 */
void catac_radioBase_remover(Lista removerRadioBase, Tree arvoreRadioBase);

/*
 * Remove um morador pelo comando catac
 * Necessita do comando cata ter sido chamado
 * Retorna nada
 */
void catac_morador_remover(Lista removerMorador, HashTable moradores);

/*
 * Remove um comercio pelo comando catac
 * Necessita do comando catac ter sido chamado
 * Retorna nada
 */
void catac_comercio_remover(Lista removerComercio, HashTable comercio);

/*
 * Percorre e faz comparacôes para o comando bf
 * Necessita do comando bf ter sido chamado
 * Retorna nada
 */
void Bf_percorrer(Lista listaQuadra, Lista listaCasoAux, double max, FILE *svg, FILE *txt);

void addToResultList(Lista l, long int pos, int key);

#endif
