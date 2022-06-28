#ifndef VETOR_H
#define VETOR_H

//TAD vetor
typedef void* Vetor;

/*
*   Cria um veto
*   Necessita de um int para ser o tamanho do vetor
*/
Vetor createVector(int qtd);

/*
*   Adiciona um elemento ao vetor
*   Necessita de um vetor, indice do vetor, elemento, x e y 
*   Não retorna nada
*/
void addElementVector(Vetor vet, int i, void *forma, double x, double y);

/*
* Necessita de um vetor e do indece
* Retorna o elemento presente no indice mandado como parâmetro
*/
Vetor *getElementVector(Vetor vet, int i);

/*
*   Necissita de um vetor e um indice
*   Retorna o angulo de um elemento presente no indice 
*/
double getAng(Vetor vet, int i);

/*
*  Necessita de um vetor e um indice
*  Retorna o ponto X de um elemento presente no indice
*/
double getXVector(Vetor vet, int i);

/*
*  Necessita de um vetor e um indice
*  Retorna o ponto Y de um elemento presente no indice
*/
double getYVector(Vetor vet, int i);

/*
*  Necessita de um vetor, indice e angulo
*  Adiciona um angulo a determinado elemento
*/
void addAng(Vetor vet, int i, double angulo);

/*
*   Necessita de um vetor e dois indices
*   Compara a coordenada Y de dois elementos e retorna a maior ou menor
*/
int comparaY(Vetor vet, int i, int j);

/*
*   Necessita de um vetor e dois indices
*   Compara a coordenada X de dois elementos e retorna a maior ou menor
*/
int comparaX(Vetor vet, int i, int j);

/*
*  Necissita de um vetor e dois indices
*  Compara o angulo de dois elementos e retorna o maior ou menor 
*/
int comparaAng(Vetor vet, int i, int j);

/*
*   Necessita de um vetor e dois indices
*   Troca dois elementos de posição dentro do vetor 
*/
void troca(Vetor vet, int i, int j);

/*
*   Necessita de um vetor  
*   Retorna o tamanho desse vetor
*/
int getTamanhoVetor(Vetor vet);

#endif