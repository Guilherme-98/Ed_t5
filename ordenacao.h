#ifndef ORDENACAO_H
#define ORDENACAO_H

#include"pilha.h"
#include"vetor.h"
#include"quadTree.h"
#include"lista.h"
#include"./elementos/quadra.h"
#include"./elementos/hidrante.h"
#include"./elementos/semaforo.h"
#include"./elementos/radioBase.h"

//Função genérica que pega a coordenada de um void*
typedef double (* getCoordenada)(void*);

//Função genérica que calcula a coordenada polar de dois void* e retorna o angulo
typedef double (* calculaCoordenada)(void*,void*);

// Função genérica que compara dois void*
typedef int (* compara)(void*,int,int);

//Função que calcula a orientacao de três pontos, e retorna um inteiro representando o sentido horário, anti-horario ou colinear
typedef int (*orientacao)(void*,void*,void*);

/*
*   Necessita de um vetor, posição de inicio do vetor a ser ordenado, posição do fim do vetor a ser ordenado
*   comparaGenerico: função que compara dois equipamentos urbanos(Quadra,semaforo,etc...)
*/
void quicksort_ordenacao(Vetor vet, int inicio, int fim, compara comparaGenerico);

/*
*   Necessita de um vetor, posição de inicio do vetor a ser ordenado, posição do fim do vetor a ser ordenado
*   comparaGenerico: função que compara dois equipamentos urbanos(Quadra,semaforo,etc...)
*   Faz a troca de elementos do vetor
*/
int swap_ordenacao(Vetor vet, int inicio, int fim, compara comparaGenerico);

/*
*   Necessita de um vetor, uma arvore, nó da arvore 
*   Função que converte uma arvore para vetor
*/
int conversao_arvore_vetor(Vetor v, Tree arv, PosicNo nohArv, getCoordenada getCoordX, getCoordenada getCoordY, int i);

/*
*   Necessita de um vetor
*   calc: Função que retorna o angulo de cada equipamento
*   Função que calcula a coordenada polar de um addElemento
*/
Vetor calculaCoordPolar(Vetor vet, calculaCoordenada calc);

/*
*   Necessita de uma pilha 
*   Função que converte uma pilha para vetor
*/
Vetor converterPilhaParaVetor(Pilha monte, getCoordenada getCoordX, getCoordenada getCoordY, int pts);

/*
*  Calcula o primeiro passo antes do convexHull
*  Necessita de um vetor que será utilizado nos procedimentos,
*  comparaY: Função que compara o Y de varios equipamentos urbanos
*  comparaPolar: Função que compara a coordenada polar de equipamentos urbanos
*  comparaAng: Função que compara o angulo de equipamentos urbanos
*/

Vetor PrimeiroPasso(Vetor vet, compara comparaY, calculaCoordenada comparaPolar, compara comparaAng);

/*
*   Necessita de uma arvore do tipo quadra
*   Realiza o operação de balanceamento para que possa produzir arvores razoavelmente balanceadas do tipo quadra
*   Não retorna nada 
*/
void arvore_quadra_balanceada(Tree arvoreQuadra);

/*
*   Necessita de uma arvore do tipo hidrante
*   Realiza o operação de balanceamento para que possa produzir arvores razoavelmente balanceadas do tipo hidrante
*   Não retorna nada 
*/
void arvore_hidrante_balanceada(Tree arvoreHidrante);

/*
*   Necessita de uma arvore do tipo semaforo
*   Realiza o operação de balanceamento para que possa produzir arvores razoavelmente balanceadas do tipo semaforo
*   Não retorna nada 
*/
void arvore_semaforo_balanceada(Tree arvoreSemaforo);

/*
*   Necessita de uma arvore do tipo radio base
*   Realiza o operação de balanceamento para que possa produzir arvores razoavelmente balanceadas do tipo radio base 
*   Não retorna nada 
*/
void arvore_radioBase_balanceada(Tree arvoreRadioBase);

#endif
