#ifndef QUADTREE_H
#define QUADTREE_H
#include <stdbool.h>

//TAD arvore
typedef void* Tree;

//Lista de auxilio
typedef void* Lista;

//ItemNode é um item da arvore
typedef void* ItemNode;

//PosicNo nó que aponta para uma determinada posição da arvore
typedef void* PosicNo;

//TAD Ponto
typedef void* Point;

// Pega cordenada X
typedef void(* getCoordX)(void*);

// Pega cordenada Y
typedef void(* getCoordY)(void*);

// Auxilia na impressão do svg
typedef void (* Escrever)(FILE*,void*);

typedef void *ExtraInfo;

typedef void *funcVisita;

// Auxlia para pegar o tipo da chave dos elementos criados inseridos nas arvores
typedef void* funcGetChave(ItemNode);

/*
* Cria uma lista contendo as chaves de ordenação de todas as informações
* cujas coordenas associadas (no momento da inserção) estão dentro do
* retângulo determinado pelo vértices opostos (x1,y1) e (x2,y2).
*/
Lista chavesDentroRetanguloQt(Tree qt, double x1, double y1, double x2, double y2);

/*
* Similar à função chavesDentroRetanguloQt(). Retorna a chave cuja
* coordenada é interna à circunferência de raio r e centro em (x,y).
*/
Lista chavesDentroCirculoQt(Tree qt,double x, double y, double r);

/*
* Similar à função pontosDentroRetanguloQt(). Retorna apontadores para
* nós da árvore contendo informações cuja coordenada está dentro da
* região de busca.
*/
Lista nosDentroRetanguloQt(Tree qt,double x1, double y1,double x2, double y2);

/*
* Similar à função nosDentroRetanguloQt(). Retorna nós internos
* à circunferência de raio r e centro em (x,y).
*/
Lista nosDentroCirculoQt(Tree qt,double x, double y, double r);

/*
* Percorre a árvore em profundidade. Em cada nó visitado invoca
* a função f.
*/
void percorreProfundidadeQt(Tree qt,funcVisita f,ExtraInfo ei);

/*
* Semelhante a percorreProfundidadeQt. Percorre a árvore em largura.
*/
void percorreLarguraQt(Tree qt,funcVisita,ExtraInfo);

/*
* Retorna uma referência ao nó da árvore associado à coordenada (x,y).
* Retorna NULL, caso não exista tal nó.
*/
PosicNo getNoQt(Tree qt, double x, double y);

/*
* Retorna a informação armazenada na árvore no nó referenciiado por pNo.
* "pNo" deve referenciar um nó válido dentro da árvore.
*/
ItemNode getInfoQt(Tree qt, PosicNo pNo);

//Numero de quadras dentro do retangulo passado pelo comando dd no .geo
double numQuadrasDentro;

/*
*   Cria uma Arvore
*   Retorna Tree
*/
Tree createTree(funcGetChave getKey);

/*
*   Necessita de uma arvore
*   Retorna o tamanho da arvore
*/
int sizeTree(Tree arv);

/*
*   Necessita de uma arvore, elemento é um item a ser inserido na arvore, coordenada x e coordenada y do item
*   Insere um item na Arvore
*/
PosicNo insereQt(Tree arv, ItemNode elemento, double x, double y);

/*
*   Necessita de uma arvore, elemento é um item a ser inserido na arvore, coordenada x e coordenada y do item
*   Insere um item no inicio da Arvore
*/
PosicNo insereQtStart(Tree arv, ItemNode elemento, double x, double y);

/*
*   Necessita de uma arvore, elemento é um item a ser inserido na arvore, Nó atual da arvore, coordenada x e coordenada y do item
*   Procura um nó para inserir o item(seja em Ne,Nw,Se ou Sw)
*/
int insereQtAux(Tree arv, ItemNode elemento, PosicNo nohArv, double x, double y);

/*
*   Necessita de uma arvore, elemento é um item a ser inserido na arvore, Nó atual da arvore, coordenada x e coordenada y do item
*   Insere um Item a Ne do nó atual
*/
int insereQtNe(Tree arv, ItemNode elemento, PosicNo nohArv, double x, double y);

/*
*   Necessita de uma arvore, elemento é um item a ser inserido na arvore, Nó atual da arvore, coordenada x e coordenada y do item
*   Insere um Item a Se do nó atual
*/
int insereQtSe(Tree arv, ItemNode elemento, PosicNo nohArv, double x,double y);

/*
*   Necessita de uma arvore, elemento é um item a ser inserido na arvore, Nó atual da arvore, coordenada x e coordenada y do item
*   Insere um Item a Nw do nó atual
*/
int insereQtNw(Tree arv, ItemNode elemento, PosicNo nohArv, double x, double y);

/*
*   Necessita de uma arvore, elemento é um item a ser inserido na arvore, Nó atual da arvore, coordenada x e coordenada y do item
*   Insere um Item a Sw do nó atual
*/
int insereQtSw(Tree arv, ItemNode elemento, PosicNo nohArv, double x, double y);

/*
*   Necessita de uma arvore, Nó em que está o item
*   Retorna o item desejado
*/
ItemNode getElement(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore
*   Retorna o primeiro elemento da QuadTree
*/
PosicNo getFirstElementTree(Tree arv);

/*
*   Necessita de uma arvore, Nó em que está o item
*   Retorna a coordenada X do nó nohArv
*/
double getXQuadTree(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore, Nó em que está o item
*   Retorna a coordenada Y do nó nohArv
*/
double getYQuadTree(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore, Nó pai e Nó a ser observado
*   Retorna o quadrante em que está o nohArv2
*/
int getQuadrante(Tree arv, PosicNo nohArv, PosicNo nohArv2);

/*
*   Necessita de uma arvore, Nó em que está o item
*   Remove um item da Arvore
*/
ItemNode removeNoQt(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore, provavel Nó pai, Nó a ser comparado
*   Procura o nó Pai de um determinado nó
*/
PosicNo find(Tree arv, PosicNo inicio, PosicNo nohArv);

/*
*   Necessita de uma arvore, e de dois Nó
*   Função que após a remoção de um determinado elemento, faz a reinserção na QuadTree
*/
void connect(Tree arv, PosicNo nohArv, PosicNo nohArv2);

/*
*   Necessita de uma arvore e do Nó atual
*   Retorna o nó a Ne
*/
PosicNo getNe(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore e do Nó atual
*   Retorna o nó a Nw
*/
PosicNo getNw(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore e do Nó atual
*   Retorna o nó a Se
*/
PosicNo getSe(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore e do Nó atual
*   Retorna o nó a Sw
*/
PosicNo getSw(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore e do Nó atual
*   Função que verifica se o nó é uma folha
*/
int isLeaf(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore e do Nó atual
*   Verifica se existe nó a Ne
*/
int leafNe(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore e do Nó atual
*   Verifica se existe nó a Nw
*/
int leafNw(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore e do Nó atual
*   Verifica se existe nó a Se
*/
int leafSe(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore e do Nó atual
*   Verifica se existe nó a Sw
*/
int leafSw(Tree arv, PosicNo nohArv);

/*
*   Necessita de uma arvore
*   Função que desaloca a QuadTree
*/
void desalocaQt(Tree arv);

/*
*   Necessita de uma arvore e do Nó atual a ser desalocado
*   Desaloca um determinado nó
*/
void freeTree(Tree arv, PosicNo nohArv);

/*
 * Processa uma arvore, lendo suas informações e as colocando no svg
 * Necessita das informações necessárias terem sido passsadas
 */
int processarTree(Tree arv, PosicNo nohArv, Escrever escreverEquip, FILE *arq);

/*
 * Percorre a arvore de quadras
 * Nao retorna nada
 */
void* percorrer_Quadra_QD(Tree arvoreAux, char id[], PosicNo n);

/*
 * Percorre a arvore de formas(circulo ou retangulo)
 * Nao retorna nada
 */
void* percorrer_Forma_QD(Tree arvoreAux, char id[], PosicNo n);

/*
 * Percorre a arvore de textos
 * Nao retorna nada
 */
void* percorrer_Texto_QD(Tree arvoreAux, char id[], PosicNo n);

/*
 * Percorre a arvore de hidrantes
 * Nao retorna nada
 */
void* percorrer_Hidrante_QD(Tree arvoreAux, char id[], PosicNo n);

/*
 * Percorre a arvore de semaforos
 * Nao retorna nada
 */
void* percorrer_Semaforo_QD(Tree arvoreAux, char id[], PosicNo n);

/*
 * Percorre a arvore de radio-base
 * Nao retorna nada
 */
void* percorrer_RB_QD(Tree arvoreAux, char id[], PosicNo n);

/*
 * Percorre as arvores e encontra o elemento desejado
 * Nao retorna nada
 */
void* encontrarElementoArvores (char id[], Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase);

/*
 * Percorre a arvore de quadras a partir do comando dq do .qry
 * Nao retorna nada
 */
void* dq_percorrer_arvore(Tree arvoreQuadra, double x, double y, double r, FILE *txt, FILE* svg2, bool verificador, PosicNo aux, Lista listaPosicNo);

/*
 * Percorre a arvore de quadras a partir do comando cbq do .qry
 * Nao retorna nada
 */
void* percorrer_CBQ(Tree arvoreQuadra, double x, double y, double r, char corBorda[], FILE *txt, FILE* svg2, PosicNo aux);

/*
 * Percorre a arvore de quadras a partir do comando car do .qry
 * Nao retorna nada
 */
void* percorrer_CAR(FILE* aux, FILE* txt, Tree arvoreQuadra, PosicNo noh, double x, double y, double h, double w, Lista listaQuadra);

/*
 * Percorre a arvore de posto a partir do comando soc do .qry
 * Nao retorna nada
 */
void* soc_posto_conversao(Tree arvorePosto, PosicNo aux, Lista listaPosto);

/*
 * Percorre a arvore de quadras a partir do comando ci do .qry
 * Nao retorna nada
 */
void* ci_casos_conversao(Tree arvoreCasos, PosicNo aux, Lista listaCasos);

/*
 * Percorre a arvore de quadras a partir do comando dd do .geo
 * Nao retorna nada
 */
void* percorrer_Quadra_dd(Tree arvoreQuadra, PosicNo aux, double x, double w, double y, double h);

/*
 * Percorre a arvore de quadras a partir do comando dd do .geo
 * Insere sombras nas quadras que estão dentro do retangulo dado
 * Nao retorna nada
 */
void* inputSombraQuadras(Tree arvoreQuadra, PosicNo aux, FILE* svg, double densidadeQuadra, double x, double y, double w, double h);

/*
 * Percorre a arvore de quadra a partir do comando soc do .qry
 * Nao retorna nada
 */
void* bf_quadra_conversao(Tree arvoreQuadra, PosicNo aux, Lista listaQuadra);

#endif