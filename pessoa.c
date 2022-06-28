#include"pessoa.h"

typedef struct stPessoa {
    char cpf[32], nome[32], sobrenome[32], sexo[2], nascimento[16];
} *PessoaImp;

Pessoa criarPessoa (char cpf[], char nome[], char sobrenome[], char sexo[], char nascimento[]){
    PessoaImp rPessoa = (PessoaImp) malloc (sizeof(struct stPessoa));

    strcpy (rPessoa->cpf, cpf);
    strcpy (rPessoa->nome, nome);
    strcpy (rPessoa->sobrenome, sobrenome);
    strcpy (rPessoa->sexo, sexo);
    strcpy (rPessoa->nascimento, nascimento);

    return rPessoa;
}

char* getPessoaCpf (Pessoa p){ 
    PessoaImp pessoa = (PessoaImp) p;

    return pessoa->cpf;
}

char* getPessoaName (Pessoa p){ 
    PessoaImp pessoa = (PessoaImp) p;

    return pessoa->nome;
}

char* getPessoaLastName (Pessoa p){ 
    PessoaImp pessoa = (PessoaImp) p;

    return pessoa->sobrenome;
}

char* getPessoaSexo (Pessoa p){ 
    PessoaImp pessoa = (PessoaImp) p;

    return pessoa->sexo;
}

char* getPessoaNascimento (Pessoa p){ 
    PessoaImp pessoa = (PessoaImp) p;

    return pessoa->nascimento;
}

void destroiPessoa(Pessoa p){
    
    free(p);
}