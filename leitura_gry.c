#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"leitura_gry.h"
#include"leitura_geo.h"
#include"consultas.h"
#include"svg.h"
#include"lista.h"
#include"moradores_qry.h"
#include"comercio_qry.h"
#include"tipoComercio_qry.h"
#include"svg_qry.h"
#include"qry_via.h"

char nomeAux[32];  

void Ler_arquivo_gry(FILE *qry, FILE *svg2, FILE *txt, Tree arvoreForma, Tree arvoreTexto, Tree arvoreQuadra, Tree arvoreHidrante, 
                    Tree arvoreSemaforo, Tree arvoreRadioBase, Tree arvorePosto, Tree arvoreCasos, 
                    HashTable pessoas, HashTable quadrasTable, 
                    HashTable hidrantesTable, HashTable semaforosTable, HashTable radioBaseTable,
                    HashTable moradores, HashTable comercios, char *diretorioSaida, char *entradaGeoNew, char *entradaQryNew, Grafo caminhos, Lista listaCasoN, Lista listaCasoS, Lista listaCasoL, Lista listaCasoO, int contadorId){

char operacao[8],corBorda[32],corPreenchimento[32], linha_txt[1024], aux[32];
char j[32], k[32], face, cep[32], cpf[32], cnpj[32], compl[32], face2[2], tp[32], t[32], sfx[32], id1[32], id2[32], reg[32], cor[32], cor2[32], faceReg[32];
int j_num, k_num, n, posto_atendimento, contadorIdAux;;
double x, y, r, w, h, num, casos, max;
bool verificador;

    //Registradores [R0 - R10]
    Point *registrador = (Point) calloc(11, sizeof(Point));

    FILE *txt_aux;

    txt_aux = fopen("aux.txt","w+");    

    while(1){
        fscanf(qry, "%s", operacao);

        if(feof(qry)){
            break;
        }

        if(strcmp(operacao, "o?") == 0){
            fscanf(qry,"%s", j);
            fscanf(qry,"%s", k);
            consulta_o(arvoreForma, j ,k, txt, txt_aux);
        }

        else if(strcmp(operacao, "i?") == 0 ){
            fscanf(qry,"%s",  j);
            fscanf(qry,"%lf", &x);
            fscanf(qry,"%lf", &y);
            consulta_i(arvoreForma, j, x, y, txt, txt_aux);
        } 

        else if(strcmp(operacao, "pnt") == 0){
            fscanf(qry,"%s", j);
            fscanf(qry,"%s", corBorda);
            fscanf(qry,"%s",corPreenchimento);
            consulta_pnt(arvoreForma, arvoreTexto, j,corBorda,corPreenchimento, txt);
        }

        else if(strcmp(operacao, "pnt*") == 0){
            fscanf(qry,"%d", &j_num);
            fscanf(qry,"%d", &k_num);
            fscanf(qry,"%s",corBorda);
            fscanf(qry,"%s",corPreenchimento);
            consulta_pnt_2(arvoreForma, arvoreTexto, j_num, k_num, corBorda, corPreenchimento, txt);
        }

        else if(strcmp(operacao, "delf") == 0){
            fscanf(qry,"%s", j);
            consulta_delf(arvoreForma, arvoreTexto, j, txt);
        }

        else if(strcmp(operacao, "delf*") == 0){
            fscanf(qry,"%d", &j_num);
            fscanf(qry,"%d", &k_num);
            consulta_delf_2(arvoreForma, arvoreTexto, j_num, k_num, txt);
        }

        else if(strcmp(operacao, "dq") == 0){
            fscanf(qry, "%s", aux);
            if(strcmp(aux, "#") == 0){
                fscanf(qry, "%s %lf", j, &r);
                verificador = true;
            }else{
                fscanf(qry,"%lf", &r);
                verificador = false;
            }
            consulta_dq(aux, j, r, verificador, svg2, txt, txt_aux, arvoreQuadra, arvoreHidrante, arvoreSemaforo, arvoreRadioBase);
        }

        else if(strcmp(operacao, "del") == 0){
            fscanf(qry, "%s", j);
            consulta_del(txt_aux, arvoreQuadra, arvoreHidrante, arvoreSemaforo, arvoreRadioBase, j, svg2, txt);
        }

        else if(strcmp(operacao, "crd?") == 0){
            fscanf(qry, "%s", j);
            consulta_crd(arvoreQuadra, arvoreHidrante, arvoreSemaforo, arvoreRadioBase, j, txt);
        }

        else if(strcmp(operacao, "cbq") == 0){
            fscanf(qry, "%lf %lf %lf %s", &x, &y, &r, corBorda);
            consulta_cbq(arvoreQuadra, svg2, txt, x, y, r, corBorda);
        }
        
        else if(strcmp(operacao, "car") == 0){
            fscanf(qry, "%lf %lf %lf %lf", &x, &y, &w, &h);
            consulta_car(txt_aux, arvoreQuadra, txt, x, y, w, h);
        }

        else if(strcmp(operacao, "cv") == 0){
            fscanf(qry, "%lf %s %c %lf", &casos, cep, &face, &num);
            consulta_cv(arvoreQuadra, arvoreCasos, casos, cep, face, num, txt_aux, listaCasoN, listaCasoS, listaCasoL, listaCasoO);
        }

        else if(strcmp(operacao, "soc") == 0){
            fscanf(qry, "%d %s %c %lf", &posto_atendimento, cep, &face, &num); 
            consulta_soc(arvoreQuadra, arvorePosto, posto_atendimento, cep, face, num, txt_aux,txt);
        }

        else if(strcmp(operacao, "ci") == 0){
            fscanf(qry, "%lf %lf %lf", &x, &y, &r);
            consulta_ci(x, y, r, txt_aux, txt, arvorePosto, arvoreCasos);
        }

		else if (strcmp(operacao, "m?") == 0){
			fscanf(qry, "%s", cep);
			consulta_m(txt, moradores, cep);
		}

        else if(strcmp(operacao, "dm?") == 0){
			fscanf(qry, "%s", cpf);
			fprintf(txt,"dm? %s\n", cpf);
            consulta_dm (cpf, moradores, txt, txt_aux);
            fprintf(txt, "\n");
		}

        else if(strcmp(operacao, "de?") == 0){
			fscanf(qry, "%s", cnpj);
            fprintf(txt,"de? %s\n", cnpj);
            consulta_de(cnpj, comercios, txt);
            fprintf(txt, "\n");
		}

        else if(strcmp(operacao, "mud") == 0){
            fscanf(qry, "%s", cpf);
            fscanf(qry, "%s", cep);
            fscanf(qry, "%s", face2);
            fscanf(qry, "%d", &n);
            fscanf(qry, "%s", compl);
            fprintf(txt, "mud %s %s %s %d %s\n", cpf, cep, face2, n, compl);
            consulta_mud(txt, txt_aux, moradores, cpf, cep, face2, n, compl, arvoreQuadra);
        }

        else if(strcmp(operacao, "eplg?") == 0){
            fscanf(qry, "%s %lf %lf %lf %lf",  tp, &x, &y, &w, &h);
            consulta_eplg(txt, txt_aux, tp, comercios, x, y, w, h);
        }

        else if(strcmp(operacao, "catac") == 0 ){
            fscanf(qry, "%lf %lf %lf", &x, &y, &r);
            consulta_catac(txt, txt_aux, x, y, r, arvoreQuadra, arvoreHidrante, arvoreSemaforo, arvoreRadioBase, moradores, comercios);
        }

        else if(strcmp(operacao, "dmprbt") == 0){
            fscanf(qry, "%s %s", t, sfx);
            consulta_dmprbt(t, sfx, diretorioSaida, arvoreQuadra, arvoreHidrante, arvoreSemaforo, arvoreRadioBase, txt, entradaGeoNew, entradaQryNew);
        } 
        
        else if(strcmp(operacao, "@m?") == 0){
            fscanf(qry, "%s %s", reg, cpf);
            tratarRegistradorM(registrador, reg, cpf, moradores, txt_aux);

            
        }else if(strcmp(operacao, "@e?") == 0){
            fscanf(qry, "%s %s %c %lf", reg, cep, &face, &num);
            tratarRegistradorE(registrador, reg, cep, face, num, quadrasTable, txt_aux);
        }
        
        else if(strcmp(operacao, "@g?") == 0){
            fscanf(qry, "%s %s", reg, id1);
            tratarRegistradorG(registrador, reg, id1, hidrantesTable, semaforosTable, radioBaseTable, txt_aux);
        }

        else if(strcmp(operacao, "@xy") == 0){
            fscanf(qry, "%s ¨%lf %lf", reg, &x, &y);
            Point ponto  = createPoint(x,y);
            setRegistrador(registrador, reg, ponto);
            svg_imprimir_linha(txt_aux, x, y, x, 0, "black");
            fprintf(txt_aux, "\n\t<text\n\t\tx=\"%lf\"", x + 10);
            fprintf(txt_aux, "\n\t\ty=\"10\"");
            fprintf(txt_aux, "\n\t\tstroke=\"black\"");
            fprintf(txt_aux, "\n\t\tfill=\"black\">");
            fprintf(txt_aux, "\n\t\tID: %s", reg);
            fprintf(txt_aux, "\n\t</text>\n");
        }

        else if(strcmp(operacao, "ccv") == 0){
            fscanf(qry, "%s", sfx);
            //Comando não foi realizado
        }

        else if(strcmp(operacao, "p?") == 0){
            fscanf(qry, "%s", sfx);
            fscanf(qry, "%s", id1);
            fscanf(qry, "%s", id2);
            fscanf(qry, "%s", cor);
            fscanf(qry, "%s", cor2);
          

            char * arqsvg4 = NULL;
            FILE *svg4;
        
           if(strcmp(sfx, "-") == 0){
                arqsvg4 = criarSvg3(entradaGeoNew, entradaQryNew, nomeAux, diretorioSaida, arqsvg4);
                svg4 = fopen(arqsvg4,"r+");	
                fseek(svg4, -7, SEEK_END);
           }else{
                arqsvg4 = criarSvg3(entradaGeoNew, entradaQryNew, sfx, diretorioSaida, arqsvg4);
                strcpy(nomeAux,sfx);	
                svg4 = fopen(arqsvg4,"w+");
                fprintf(svg4, "<svg  xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");

                inputSombraQuadras(arvoreQuadra, getFirstElementTree(arvoreQuadra), svg4, densidadeQuadra, x_dd, y_dd, w_dd, h_dd);
                processarTree(arvoreForma,getFirstElementTree(arvoreForma),svg_imprimir_forma,svg4);
                processarTree(arvoreQuadra,getFirstElementTree(arvoreQuadra),svg_imprimir_quadra,svg4);
                processarTree(arvoreHidrante,getFirstElementTree(arvoreHidrante),svg_imprimir_hidrante,svg4);
                processarTree(arvoreSemaforo,getFirstElementTree(arvoreSemaforo),svg_imprimir_semaforo,svg4);
                processarTree(arvoreRadioBase,getFirstElementTree(arvoreRadioBase),svg_imprimir_rb,svg4);
                processarTree(arvoreTexto,getFirstElementTree(arvoreTexto),svg_imprimirTexto,svg4);
                processarTree(arvorePosto,getFirstElementTree(arvorePosto),svg_imprimir_posto,svg4);
            }
            contadorIdAux = tratarP(svg4, registrador, id1, id2, cor, cor2, caminhos, txt_aux, contadorId, txt);
            contadorId = contadorIdAux;
            fprintf(svg4, "\n</svg>");
            free(arqsvg4);
            fclose(svg4);
        }

        else if(strcmp(operacao, "bf") == 0){
            fscanf(qry, "%lf", &max);
            tratarBf(max, arvoreQuadra, listaCasoN, listaCasoS, listaCasoL, listaCasoO, txt_aux, txt);
        }

        else if(strcmp(operacao, "sp?") == 0){
            fscanf(qry, "%s", sfx);
            fscanf(qry, "%s", id1);
            fscanf(qry, "%s", id2);
            fscanf(qry, "%s", cor);
            fscanf(qry, "%s", cor2);
            //Comando não foi realizado
        }

        else if(strcmp(operacao, "pb?") == 0){
            fscanf(qry, "%s", sfx);
            fscanf(qry, "%s", id1);
            fscanf(qry, "%s", id2);
            fscanf(qry, "%s", cor);
            //Comando não foi realizado
        }
    }

    inputSombraQuadras(arvoreQuadra, getFirstElementTree(arvoreQuadra), svg2, densidadeQuadra, x_dd, y_dd, w_dd, h_dd);
    processarTree(arvoreForma,getFirstElementTree(arvoreForma),svg_imprimir_forma,svg2);
    processarTree(arvoreQuadra,getFirstElementTree(arvoreQuadra),svg_imprimir_quadra,svg2);
    processarTree(arvoreHidrante,getFirstElementTree(arvoreHidrante),svg_imprimir_hidrante,svg2);
    processarTree(arvoreSemaforo,getFirstElementTree(arvoreSemaforo),svg_imprimir_semaforo,svg2);
    processarTree(arvoreRadioBase,getFirstElementTree(arvoreRadioBase),svg_imprimir_rb,svg2);
    processarTree(arvoreTexto,getFirstElementTree(arvoreTexto),svg_imprimirTexto,svg2);
    processarTree(arvorePosto,getFirstElementTree(arvorePosto),svg_imprimir_posto,svg2);
    
    rewind(txt_aux);
    while(1){
        fgets(linha_txt,1024,txt_aux);
            if(feof(txt_aux))
                break;
        fprintf(svg2,"%s",linha_txt);
    }
    fclose(txt_aux);
    remove("aux.txt");  
}        