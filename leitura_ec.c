#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"comercio.h"
#include"tipoComercio.h"
#include"hashTable.h"
#include"./elementos/quadra.h"

void Ler_arquivo_ec(FILE *ec, HashTable tipoComercios, HashTable comercios, HashTable pessoas, HashTable quadraTable){
char operacao[8], codt[32], descricao[128], cnpj[32], cpf [32], cep[32], face[2], nome[32];
int num;
    
    while(1){
        fscanf(ec, "%s", operacao);

        if(feof(ec)){
			break;
		}

        if(strcmp(operacao, "t") == 0){
            fscanf (ec, "%s", codt);
            fscanf (ec, "%s", descricao);
            TipoComercio tipoComercio = criarTipoComercio (codt, descricao);
            insertHashTable(tipoComercios, getTipoComercioCodt(tipoComercio), tipoComercio);
        }
        if(strcmp(operacao, "e") == 0){
            fscanf (ec, "%s", cnpj);
            fscanf (ec, "%s", cpf);
            fscanf (ec, "%s", codt);
            fscanf (ec, "%s", cep);
            fscanf (ec, "%s", face);
            fscanf (ec, "%d", &num);
            fscanf (ec, "%s", nome);

            Quadra quadra = searchHashTable(quadraTable, cep);
           
            Comercio comercio = criarComercio (cnpj, cpf, codt, cep, face, num, nome, tipoComercios, pessoas, quadra);
            insertHashTable(comercios, getComercioCnpj(comercio), comercio);
        }
    }
}