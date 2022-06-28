#ifndef PESSOA__H
#define PESSOA__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TAD PESSOA
typedef void *Pessoa;

/*
 * Cria um elemento pessoa
 * Necessita do comando para criar uma pessoa ter sido chamado
 * Retorna uma entidade pessoa
 */
Pessoa criarPessoa (char cpf[], char nome[], char sobrenome[], char sexo[], char nascimento[]);

/*
 * Retorna o cpf de uma pessoa
 */
char* getPessoaCpf (Pessoa p);

/*
 * Retorna o nome de uma pessoa
 */
char* getPessoaName (Pessoa p);

/*
 * Retorna o ultimo nome de uma pessoa
 */
char* getPessoaLastName (Pessoa p);

/*
 * Retorna o sexo de uma pessoa
 */
char* getPessoaSexo (Pessoa p);

/*
 * Retorna o cpf de uma pessoa
 */
char* getPessoaNascimento (Pessoa p);

/*
 * Libera uma entidade pessoa da memória
 */
void destroiPessoa(Pessoa p);

#endif