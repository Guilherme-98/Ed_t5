#ifndef MORADORES__H
#define MORADORES__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pessoa.h"
#include "hashTable.h"

//TAD MORADORES
typedef void *Moradores;

/*
 * Cria um morador com suas devidas informações
 * Necessita de um comando de criação de morador ter sido chamado
 * Retorna um morador
 */
Moradores criarMoradores (char cpf[], char cep[], char face[], char compl[], int num, HashTable pessoas, HashTable quadraTable);

/*
 * Retorna o cep de um morador
 */
char* getMoradoresCep (Moradores r);

/*
 * Retorna o cpf de um morador
 */
char* getMoradoresCpf (Moradores r);

/*
 * Retorna a face de um morador
 */
char* getMoradoresFace (Moradores r);

/*
 * Retorna o compl de um morador
 */
char* getMoradoresCompl (Moradores r);

/*
 * Retorna o numero de um morador
 */
int getMoradoresNum (Moradores r);

/*
 * Retorna a pessoa de um morador
 */
Pessoa getMoradoresPessoa(Moradores r);

/*
 * Retorna o x de um morador
 */
double getMoradoresX(Moradores r);

/*
 * Retorna o y de um morador
 */
double getMoradoresY(Moradores r);

/*
 * Seta o cep de um morador
 */
void setMoradoresCep (Moradores r, char cep[]);

/*
 * Seta a face de um morador
 */
void setMoradoresFace (Moradores r, char face[]);

/*
 * Seta o numero de um morador
 */
void setMoradoresNum (Moradores r, int num);

/*
 * Seta o compl de um morador
 */
void setMoradoresCompl (Moradores r, char compl[]);

/*
 * Seta o cep de um morador
 */
void mudancaMoradoresEndereco(Moradores r, char cep[], char face[], int num, char compl[]);

/*
 * Da free num morador
 */
void destroiMoradores(Moradores r);

#endif