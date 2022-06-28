#include "moradores_qry.h"

void consulta_m (FILE *arqTxt, HashTable moradores, char cep[]){
    int verificador = 0;

    fprintf (arqTxt, "m? %s\nMoradores do CEP fornecido: \n", cep);

    for(int i = 0; i < getHashTableSize(moradores); i++){
        ListNode node = getHashNode(moradores, i);
        while(node != NULL){
            Moradores morador = getHashNodeElement(node);
            char *cepResident = getMoradoresCep(morador);

            if(!strcmp(cepResident, cep)){
                Pessoa pessoa = getMoradoresPessoa(morador);
                verificador = 1;
                fprintf (arqTxt, "-%s %s:\n\tCPF: %s\n\tSexo: %s\n\tNascimento: %s\n\tCEP: %s, Face: %s, Número: %d, Complemento: %s\n", 
                getPessoaName (pessoa), getPessoaLastName(pessoa), getPessoaCpf (pessoa), getPessoaSexo (pessoa), getPessoaNascimento(pessoa), getMoradoresCep (morador), getMoradoresFace(morador), getMoradoresNum (morador), getMoradoresCompl (morador));
            }
            
            node = getHashNodeNext(node);
        }
    }

    if(verificador == 0){
        fprintf(arqTxt,"Quadra cuja o cep é %s não encontrado.\n", cep);
    }

    fprintf (arqTxt,"\n");
}

void consulta_dm(char *cpf, HashTable moradores, FILE *arqTxt, FILE *arqSvg){
    bool found = false;

    for(int i = 0; i < getHashTableSize(moradores); i++){
        ListNode node = getHashNode(moradores, i);
        while(node != NULL){
            Moradores morador = getHashNodeElement(node);

            if(!strcmp(cpf, getMoradoresCpf(morador))){
                found = true;
                Pessoa pessoa = getMoradoresPessoa(morador);
                fprintf (arqTxt, "-%s %s:\n\tCPF: %s\n\tSexo: %s\n\tNascimento: %s\n\tCEP: %s, Face: %s, Número: %d, Complemento: %s\n", getPessoaName(pessoa), getPessoaLastName(pessoa), getPessoaCpf(pessoa), getPessoaSexo(pessoa), getPessoaNascimento(pessoa), getMoradoresCep(morador), getMoradoresFace(morador), getMoradoresNum(morador), getMoradoresCompl(morador));
                svg_imprimir_linha(arqSvg, getMoradoresX(morador), getMoradoresY(morador), getMoradoresX(morador), 0, "black");
                fprintf(arqSvg, "\n\t<text\n\t\tx=\"%lf\"", getMoradoresX(morador) + 10);
                fprintf(arqSvg, "\n\t\ty=\"10\"");
                fprintf(arqSvg, "\n\t\tstroke=\"black\"");
                fprintf(arqSvg, "\n\t\tfill=\"black\">");
                fprintf(arqSvg, "\n\t\tCPF: %s",getPessoaCpf(pessoa));
                fprintf(arqSvg, "\n\t</text>\n");
                
                fprintf(arqSvg, "\n\t<text\n\t\tx=\"%lf\"", getMoradoresX(morador) + 10);
                fprintf(arqSvg, "\n\t\ty=\"20\"");
                fprintf(arqSvg, "\n\t\tstroke=\"black\"");
                fprintf(arqSvg, "\n\t\tfill=\"black\">");
                fprintf(arqSvg, "\n\t\t%s",getPessoaName(pessoa));
                fprintf(arqSvg, "\n\t</text>\n");

                fprintf(arqSvg, "\n\t<text\n\t\tx=\"%lf\"", getMoradoresX(morador) + 10);
                fprintf(arqSvg, "\n\t\ty=\"30\"");
                fprintf(arqSvg, "\n\t\tstroke=\"black\"");
                fprintf(arqSvg, "\n\t\tfill=\"black\">");
                fprintf(arqSvg, "\n\t\t%s",getMoradoresCep(morador));
                fprintf(arqSvg, "\n\t</text>\n");

                fprintf(arqSvg, "\n\t<text\n\t\tx=\"%lf\"", getMoradoresX(morador) + 10);
                fprintf(arqSvg, "\n\t\ty=\"40\"");
                fprintf(arqSvg, "\n\t\tstroke=\"black\"");
                fprintf(arqSvg, "\n\t\tfill=\"black\">");
                fprintf(arqSvg, "\n\t\t%s",getMoradoresFace(morador));
                fprintf(arqSvg, "\n\t</text>\n");

                fprintf(arqSvg, "\n\t<text\n\t\tx=\"%lf\"", getMoradoresX(morador) + 10);
                fprintf(arqSvg, "\n\t\ty=\"50\"");
                fprintf(arqSvg, "\n\t\tstroke=\"black\"");
                fprintf(arqSvg, "\n\t\tfill=\"black\">");
                fprintf(arqSvg, "\n\t\t%d",getMoradoresNum(morador));
                fprintf(arqSvg, "\n\t</text>\n");

                fprintf(arqSvg, "\n\t<text\n\t\tx=\"%lf\"", getMoradoresX(morador) + 10);
                fprintf(arqSvg, "\n\t\ty=\"60\"");
                fprintf(arqSvg, "\n\t\tstroke=\"black\"");
                fprintf(arqSvg, "\n\t\tfill=\"black\">");
                fprintf(arqSvg, "\n\t\t%s",getMoradoresCompl(morador));
                fprintf(arqSvg, "\n\t</text>\n");
                break;
            }

            node = getHashNodeNext(node);
        }

        if(found) break;
    }

    if(!found){
       fprintf(arqTxt, "-A pessoa do CPF indicado não é um morador ou não existe!");
    }

}

void consulta_mud(FILE *arqTxt, FILE *arqSvg, HashTable moradores, char cpf[], char cep[], char face[], int num, char compl[], Tree arvoreQuadra){
    double x, y, xQ, yQ, hQ, wQ, xAux, yAux;
    Moradores morador;

    bool found = false;
    for(int i = 0; i < getHashTableSize(moradores); i++){
        ListNode node = getHashNode(moradores, i);
        while(node != NULL){
            morador = getHashNodeElement(node);
            if(!strcmp(cpf, getMoradoresCpf(morador))){
                found = true;
                break;
            }

            node = getHashNodeNext(node);
        }
        
        if(found) break;
    }

    Pessoa pessoa = getMoradoresPessoa(morador);

    fprintf (arqTxt, "-%s %s:\n\tCPF: %s\n\tSexo: %s\n\tNascimento: %s\n", getPessoaName(pessoa), getPessoaLastName(pessoa), getPessoaCpf(pessoa), getPessoaSexo(pessoa), getPessoaNascimento(pessoa));
    fprintf (arqTxt, "\tEndereço antigo:\n");
    fprintf(arqTxt, "\t-CEP: %s, Face: %s, Número: %d, Complemento: %s\n", getMoradoresCep(morador), getMoradoresFace(morador), getMoradoresNum(morador), getMoradoresCompl(morador));

    PosicNo quadraNo = percorrer_Quadra_QD(arvoreQuadra, getMoradoresCep(morador), getFirstElementTree(arvoreQuadra));
    Quadra quadra = getElement(arvoreQuadra, quadraNo);

    xQ = getXQuadra(quadra);
    yQ = getYQuadra(quadra);
    hQ = getHQuadra(quadra);
    wQ = getWQuadra(quadra);

    if(*face == 'N'){
		x = xQ + num;
		y = yQ + hQ; 
	}
	else if(*face == 'S'){
		x = xQ + num;
		y = yQ;
	}
	else if(*face == 'L'){
		x = xQ;
		y = yQ + num;
	}
	else if(*face == 'O'){
		x = xQ + wQ;
		y = yQ + num;
	}

    mudancaMoradoresEndereco(morador, cep, face, num, compl);

    fprintf (arqTxt, "\tEndereço novo: \n");
    fprintf(arqTxt, "\t-CEP: %s, Face: %s, Número: %d, Complemento: %s\n", getMoradoresCep(morador), getMoradoresFace(morador), getMoradoresNum(morador), getMoradoresCompl(morador));

    quadraNo = percorrer_Quadra_QD(arvoreQuadra, cep, getFirstElementTree(arvoreQuadra));
    quadra = getElement(arvoreQuadra, quadraNo);

    xQ = getXQuadra(quadra);
    yQ = getYQuadra(quadra);
    hQ = getHQuadra(quadra);
    wQ = getWQuadra(quadra);

    if(*face == 'N'){
		xAux = xQ + num;
		yAux = yQ + hQ; 
	}
	else if(*face == 'S'){
		xAux = xQ + num;
		yAux = yQ;
	}
	else if(*face == 'L'){
		xAux = xQ;
		yAux = yQ + num;
	}
	else if(*face == 'O'){
		xAux = xQ + wQ;
		yAux = yQ + num;
	}

    svg_imprimir_linha(arqSvg, x, y, xAux, yAux, "red");
    svg_imprimir_circulo(arqSvg, x, y, 2.5, "white", "red");
    svg_imprimir_circulo(arqSvg, xAux, yAux, 2.5, "white", "blue");

}