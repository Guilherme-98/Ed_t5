#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"pessoa.h"
#include"hashTable.h"
#include"moradores.h"

void Ler_arquivo_pm(FILE *pm, HashTable pessoas, HashTable quadraTable, HashTable moradores){
char operacao[8], cpf[32], nome[32], sobrenome[32], sexo[2], nascimento[16], cep[32], face[2], compl[16];
int num;

    while(1){
        fscanf(pm, "%s", operacao);

        if(feof(pm)){
			break;
		}

        if(strcmp(operacao, "p") == 0){
            fscanf (pm, "%s", cpf);
            fscanf (pm, "%s", nome);
            fscanf (pm, "%s", sobrenome);
            fscanf (pm, "%s", sexo);
            fscanf (pm, "%s", nascimento);

            Pessoa pessoa = criarPessoa (cpf, nome, sobrenome, sexo, nascimento);
            insertHashTable(pessoas, getPessoaCpf(pessoa), pessoa);
        }

        if(strcmp(operacao, "m") == 0){
            fscanf (pm, "%s", cpf);
            fscanf (pm, "%s", cep);
            fscanf (pm, "%s", face);
            fscanf (pm, "%d", &num);
            fscanf (pm, "%s", compl);

            Moradores morador = criarMoradores (cpf, cep, face, compl, num, pessoas, quadraTable);
            insertHashTable(moradores, getMoradoresCpf(morador), morador);
        }
    }

}