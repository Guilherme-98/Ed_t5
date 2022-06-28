#ifndef QRY_VIA_H
#define QRY_VIA_H

#include <stdio.h>
#include <string.h>
#include "ponto.h"
#include "hashTable.h"
#include "moradores.h"
#include "./elementos/quadra.h"
#include "./elementos/hidrante.h"
#include "./elementos/semaforo.h"
#include "./elementos/radioBase.h"
#include "grafo.h"

/*
 * realiza uma função SET
 * necessita de um ponto
 * cria um registrador
 */
void setRegistrador(Point *registradores, char *reg, Point ponto);

/*
 * realiza uma função GET
 * necessita da criação de um registrador
 * retorna o ponto do registrador
 */
Point getRegisterPoint(Point *registradores, char *reg);

/*
 * realiza a operação @m? do arquivo .qry
 * necessita do comando @m? ter sido chamado
 * nao retorna nada
 */
void tratarRegistradorM(Point *registradores, char *reg, char *cpf, HashTable moradores, FILE *txt_aux);

/*
 * realiza a operação @e? do arquivo .qry
 * necessita do comando @e? ter sido chamado
 * nao retorna nada
 */
void tratarRegistradorE(Point *registradores, char *reg, char *cep, char face, int num, HashTable quadrasTable, FILE *txt_aux);

/*
 * realiza a operação @g? do arquivo .qry
 * necessita do comando @g? ter sido chamado
 * nao retorna nada
 */
void tratarRegistradorG(Point *registradores, char *reg, char *id, HashTable hidrantesTable, HashTable semaforosTable, HashTable radioBasesTable, FILE *txt_aux);

/*
 * realiza a operação p do arquivo .qry
 * necessita do comando p ter sido chamado
 * retorna um número inteiro
 */
int tratarP(FILE *arqSvg, Point *registradores, char r1[32], char r2[32], char corMc[32], char corMr[32], Grafo caminhos, FILE *txt_aux, int contadorId, FILE *txt);

#endif