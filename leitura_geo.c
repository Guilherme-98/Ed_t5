#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"leitura_geo.h"
#include"./elementos/forma.h"
#include"./elementos/texto.h"
#include"./elementos/quadra.h"
#include"./elementos/hidrante.h"
#include"./elementos/semaforo.h"
#include"./elementos/radioBase.h"
#include"./elementos/posto.h"
#include"lista.h"
#include"util.h"
#include"quadTree.h"

double densidade;

void Ler_arquivo_geo(FILE *geo, Tree arvoreForma, Tree arvoreTexto, Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase, Tree arvorePosto, HashTable quadraTable, HashTable hidrantesTable, HashTable semaforosTable, HashTable radioBasesTable){
char operacao[8], conteudo[128], corBorda[32], corPreenchimento[32], cep[32],swQuadra[32], swHidrante[32], swSemaforo[32], swRB[32], cw[32],rw[32];
int id,contador = 0;
double x, y, r, w, h, habitantes;
extern double densidadeQuadra;
extern double numQuadrasDentro;
extern double x_dd, y_dd, w_dd, h_dd;
char corQuadra1[32], corQuadra2[32];
char corHidrante1[32], corHidrante2[32];
char corSemaforo1[32], corSemaforo2[32];
char corRB1[32], corRB2[32];
char corPosto1[32], corPosto2[32];
strcpy(corQuadra1,"yellow");
strcpy(corQuadra2,"indigo"); 
strcpy(corHidrante1,"black");
strcpy(corHidrante2,"red");
strcpy(corSemaforo1,"dodgerblue");
strcpy(corSemaforo2,"dimgray");
strcpy(corRB1,"deeppink");
strcpy(corRB2,"indigo");
strcpy(corPosto1, "green");
strcpy(corPosto2,"cadetblue");
strcpy(cw,"1.0px");
strcpy(rw,"1.0px");
strcpy(swQuadra, "1.0px");
strcpy(swHidrante, "1.0px");
strcpy(swSemaforo, "1.0px");
strcpy(swRB, "1.0px");

Forma forma;
Texto texto;
Quadra quadra;
Hidrante hidrante;
Semaforo semaforo;
RadioBase radiobase;
Posto posto;

	while(1){
		fscanf(geo, "%s", operacao);

		if(feof(geo)){
			break;
		}

		if(strcmp (operacao, "c") == 0){
			fscanf(geo, "%s %lf %lf %lf %s %s", cep, &r, &x, &y, corBorda, corPreenchimento);
			forma = criarForma(cep, "c", x, y, r, 0, 0, corBorda, corPreenchimento, cw);
			insereQt(arvoreForma, forma, getXForma(forma), getYForma(forma));
		}

		else if(strcmp(operacao, "r") == 0){
			fscanf(geo, "%s %lf %lf %lf %lf %s %s", cep, &w, &h, &x, &y, corBorda, corPreenchimento);
			forma = criarForma(cep, "r", x, y, 0, w, h, corBorda, corPreenchimento, rw);
			insereQt(arvoreForma, forma, getXForma(forma), getYForma(forma));
		}

		else if(strcmp(operacao, "t") == 0) {
			fscanf(geo, "%s %lf %lf %s %s", cep, &x, &y, corBorda, corPreenchimento);
			fgets(conteudo,128,geo);
			texto = criarTexto(cep, "t", x, y, corBorda, corPreenchimento, conteudo);
			insereQt(arvoreTexto, texto, getXTexto(texto), getYTexto(texto));
		}	

		else if(strcmp(operacao, "q") == 0){
			fscanf(geo, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
			quadra = criaQuadra (cep, "q", x, y, w, h, corQuadra1, corQuadra2, swQuadra);
			insereQt(arvoreQuadra, quadra, getXQuadra(quadra), getYQuadra(quadra));
			insertHashTable(quadraTable, getCEPQuadra(quadra), quadra);
		}

		else if(strcmp(operacao, "h") == 0){
			fscanf(geo, "%s %lf %lf", cep, &x, &y);
			hidrante = criaHidrante(cep, "h", x, y, corHidrante1, corHidrante2, swHidrante);
			insereQt(arvoreHidrante, hidrante, getXHid(hidrante), getYHid(hidrante));
			insertHashTable(hidrantesTable, getIDHid(hidrante), hidrante);
		}

		else if(strcmp(operacao, "s") == 0){
			fscanf(geo, "%s %lf %lf", cep, &x, &y);
			semaforo = criaSemaforo(cep, "s", x, y, corSemaforo1, corSemaforo2, swSemaforo);
			insereQt(arvoreSemaforo, semaforo, getXSema(semaforo), getYSema(semaforo));
			insertHashTable(semaforosTable, getIDSema(semaforo), semaforo);
		}

		else if(strcmp(operacao, "rb") == 0){
			fscanf(geo, "%s %lf %lf", cep, &x, &y);
			radiobase = criaRadioBase(cep,"rb", x, y, corRB1, corRB2, swRB);
			insereQt(arvoreRadioBase, radiobase, getXRB(radiobase), getYRB(radiobase));
			insertHashTable(radioBasesTable, getIDRB(radiobase), radiobase);
		}

		else if(strcmp(operacao, "cq") == 0){
			fscanf(geo, "%s %s %s", swQuadra, corQuadra1, corQuadra2);
		}

		else if(strcmp(operacao,"ch") == 0){
			fscanf(geo, "%s %s %s", swHidrante, corHidrante1, corHidrante2);
		}

		else if(strcmp(operacao,"cs") == 0){
			fscanf(geo, "%s %s %s", swSemaforo, corSemaforo1, corSemaforo2);
		}

		else if(strcmp(operacao,"cr") == 0){
			fscanf(geo, "%s %s %s", swRB, corRB1, corRB2);	
		}

		else if (strcmp(operacao, "sw") == 0){
			fscanf(geo, "%s %s", cw, rw);
		}

		else if (strcmp(operacao,"ps") == 0){
			fscanf(geo, "%lf %lf", &x, &y);
			posto = criarPosto(x,y,corPosto1, corPosto2);
			insereQt(arvorePosto, posto, getXPosto(posto), getYPosto(posto));
		}
		
		else if(strcmp(operacao, "dd") == 0){
            fscanf(geo, "%lf %lf %lf %lf %lf", &x_dd, &y_dd, &w_dd, &h_dd, &habitantes);
            densidade = calculoDensidade(w_dd, h_dd, habitantes);
            percorrer_Quadra_dd(arvoreQuadra, getFirstElementTree(arvoreQuadra), x_dd, w_dd, y_dd, h_dd);
            densidadeQuadra = densidade/numQuadrasDentro;
		}
	} 
}