#include"argumentos.h"
#include"arquivos.h"
#include"svg.h"
#include"leitura_gry.h"
#include"leitura_geo.h"
#include"leitura_ec.h"
#include"leitura_pm.h"
#include"leitura_via.h"
#include"lista.h"
#include"elementos/casos.h"
#include"elementos/casosDentro.h"
#include"quadTree.h"
#include"pessoa.h"
#include"comercio.h"
#include"moradores.h"
#include"ordenacao.h"
#include"grafo.h"

int main (int argc, char *argv[]){
    int i = 1, contadorId = 0;

    extern double x_dd, y_dd, w_dd ,h_dd;
    extern double densidadeQuadra;
    Grafo caminhos;

    //Criação dos argumentos
    char * diretorioEntrada = NULL;
    char * diretorioSaida = NULL;
	char * entradaGeo = NULL;
	char * entradaQry = NULL;
    char * entradaSvg = NULL;
    char * entradaSvg2 = NULL;
    char * entradaTxt = NULL;
    char * entradaEc = NULL;
    char * entradaPm =  NULL;
    char * entradaVia = NULL;
    char * entradaGeoNew = NULL;
    char * entradaQryNew = NULL;
    char * entradaEcNew = NULL;
    char * entradaPmNew = NULL;
    char * entradaViaNew = NULL;
    char * arqgeo = NULL;
    char * arqqry = NULL;
    char * arqsvg = NULL;
    char * arqsvg2 = NULL;
    char * arqtxt = NULL;
    char * arqec = NULL;
    char * arqpm = NULL;
    char * arqvia = NULL;

    //Declaração de arquivo 
    FILE *geo;
    FILE *qry;
    FILE *svg;
    FILE *svg2;
    FILE *txt;
    FILE *ec;
    FILE *pm;
    FILE *via;

    //Loop dos arqumentos
    while(i < argc){
        if(strcmp("-e", argv[i]) == 0){
            i++;
            diretorioEntrada = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(diretorioEntrada, argv[i]);
        }
        else if(strcmp("-f", argv[i]) == 0){
            i++;
            entradaGeo = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(entradaGeo, argv[i]);
            entradaGeoNew = tratarNome(entradaGeo, entradaGeoNew);
        }
        else if(strcmp("-q", argv[i]) == 0){
            i++;
            entradaQry = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(entradaQry, argv[i]);
            entradaQryNew = tratarNome(entradaQry, entradaQryNew);   
        }
        else if(strcmp("-o", argv[i]) == 0){
            i++;
            diretorioSaida = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(diretorioSaida, argv[i]);
        }
        else if(strcmp("-ec", argv[i]) == 0){
            i++;
            entradaEc = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(entradaEc, argv[i]);
            entradaEcNew = tratarNome(entradaEc, entradaEcNew);
        }
        else if(strcmp("-pm", argv[i]) == 0){
            i++;
            entradaPm = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(entradaPm, argv[i]);
            entradaPmNew = tratarNome(entradaPm, entradaPmNew);
        }
        else if(strcmp("-v", argv[i]) == 0){
            i++;
            entradaVia = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(entradaVia, argv[i]);
            entradaViaNew = tratarNome(entradaVia, entradaViaNew);
        }
        i++;
    }

    //Concatenação do .geo
    if(diretorioEntrada != NULL){
        if(diretorioEntrada[strlen(diretorioEntrada) - 1] == '/'){
            arqgeo = (char *) malloc ((strlen(entradaGeo)+strlen(diretorioEntrada) + 1)*sizeof(char));
            sprintf(arqgeo, "%s%s", diretorioEntrada, entradaGeo);
        }
        else{
            arqgeo = (char*) malloc ((strlen(entradaGeo)+strlen(diretorioEntrada) + 2)*sizeof(char));
            sprintf(arqgeo,"%s/%s", diretorioEntrada, entradaGeo);
        }
        geo = fopen(arqgeo, "r");
        verificarArquivo(geo, entradaGeo);
    }
    else{
        geo = fopen(entradaGeo, "r");
        verificarArquivo(geo, entradaGeo);
    }

    //Concatenação do .qry caso ele exista
    if(entradaQry != NULL){
        if(diretorioEntrada != NULL){
            if(diretorioEntrada[strlen(diretorioEntrada) - 1] == '/'){
                arqqry = (char *) malloc ((strlen(entradaQry)+strlen(diretorioEntrada) + 1)*sizeof(char));
                sprintf(arqqry, "%s%s", diretorioEntrada, entradaQry);
            }
            else{
                arqqry = (char *) malloc ((strlen(entradaQry)+strlen(diretorioEntrada) + 2)*sizeof(char));
                sprintf(arqqry, "%s/%s", diretorioEntrada, entradaQry);
            }
            qry = fopen(arqqry, "r");
            verificarArquivo(qry, entradaQry);
        }
        else{
            qry = fopen(entradaQry, "r");
            verificarArquivo(qry, entradaQry);
        }
    }

    //Concatenação do .ec caso ele exista
     if(entradaEc != NULL){
        if(diretorioEntrada != NULL){
            if(diretorioEntrada[strlen(diretorioEntrada) - 1] == '/'){
                arqec = (char *) malloc ((strlen(entradaEc)+strlen(diretorioEntrada) + 1)*sizeof(char));
                sprintf(arqec, "%s%s", diretorioEntrada, entradaEc);
            }
            else{
                arqec = (char *) malloc ((strlen(entradaEc)+strlen(diretorioEntrada) + 2)*sizeof(char));
                sprintf(arqec, "%s/%s", diretorioEntrada, entradaEc);
            }
            ec = fopen(arqec, "r");
            verificarArquivo(ec, entradaEc);
        }
        else{
            ec = fopen(entradaEc, "r");
            verificarArquivo(ec, entradaEc);
        }
    }

    //Concatenação do .pm caso ele exista 
    if(entradaPm != NULL){
        if(diretorioEntrada != NULL){
            if(diretorioEntrada[strlen(diretorioEntrada) - 1] == '/'){
                arqpm = (char *) malloc ((strlen(entradaPm)+strlen(diretorioEntrada) + 1)*sizeof(char));
                sprintf(arqpm, "%s%s", diretorioEntrada, entradaPm);
            }
            else{
                arqpm = (char *) malloc ((strlen(entradaPm)+strlen(diretorioEntrada) + 2)*sizeof(char));
                sprintf(arqpm, "%s/%s", diretorioEntrada, entradaPm);
            }
            pm = fopen(arqpm, "r");
            verificarArquivo(pm, entradaPm);
        }
        else{
            pm = fopen(entradaPm, "r");
            verificarArquivo(pm, entradaPm);
        }
    }

    //Concatenação do .via caso ele exista
    if(entradaVia != NULL){
        if(diretorioEntrada != NULL){
            if(diretorioEntrada[strlen(diretorioEntrada) - 1] == '/'){
                arqvia = (char *) malloc ((strlen(entradaVia)+strlen(diretorioEntrada) + 1)*sizeof(char));
                sprintf(arqvia, "%s%s", diretorioEntrada, entradaVia);
            }
            else{
                arqvia = (char *) malloc ((strlen(entradaVia)+strlen(diretorioEntrada) + 2)*sizeof(char));
                sprintf(arqvia, "%s/%s", diretorioEntrada, entradaVia);
            }
            via = fopen(arqvia, "r");
            verificarArquivo(pm, entradaVia);
        }
        else{
            via = fopen(entradaVia, "r");
            verificarArquivo(via, entradaVia);
        }
    }
   
    //Concatenação e criação do .svg 
    arqsvg = criarSvg(entradaGeoNew, diretorioSaida, arqsvg);	
    svg = fopen(arqsvg,"w+");

    Lista listaCasoN = create();
    Lista listaCasoS = create();
    Lista listaCasoL = create();
    Lista listaCasoO = create();

    //Criação das arvores 
    Tree arvoreForma = createTree(getKeyForma);
    Tree arvoreTexto = createTree(getKeyTexto);
    Tree arvoreQuadra = createTree(getKeyQuadra);
    Tree arvoreHidrante = createTree(getKeyHidrante);
    Tree arvoreSemaforo = createTree(getKeySemaforo);
    Tree arvoreRadioBase = createTree(getKeyRadioBase);
    Tree arvorePosto = createTree(getKeyPosto);
    Tree arvoreCasos = createTree(getKeyCasos);

    //Criação HahTable
    HashTable quadraTable = createHashTable(1000, NULL);
    HashTable hidranteTable = createHashTable(1000, NULL);
    HashTable semaforoTable = createHashTable(1000, NULL);
    HashTable radioBaseTable = createHashTable(1000, NULL);
    HashTable comercios = createHashTable(1000, destroiComercio);
    HashTable tipoComercio = createHashTable(1000, destroiComercio);
    HashTable pessoas = createHashTable(1000, destroiPessoa);
    HashTable moradores = createHashTable(1000, destroiMoradores);
    
    //Lendo arquivo .geo
    Ler_arquivo_geo(geo, arvoreForma, arvoreTexto, arvoreQuadra, arvoreHidrante, arvoreSemaforo, arvoreRadioBase, arvorePosto, quadraTable, hidranteTable, semaforoTable, radioBaseTable);

    //Ordenação das arvores
    arvore_quadra_balanceada(arvoreQuadra);
    arvore_semaforo_balanceada(arvoreSemaforo);
	arvore_hidrante_balanceada(arvoreHidrante);
	arvore_radioBase_balanceada(arvoreRadioBase);

    //Lendo arquivo .pm
    if(entradaPm != NULL){
        Ler_arquivo_pm(pm, pessoas, quadraTable, moradores);
    }

    //Lendo arquivo .ec
    if(entradaEc != NULL){
        Ler_arquivo_ec(ec, tipoComercio, comercios, pessoas, quadraTable);
    }

    //Lendo arquivo .via
    if(entradaVia != NULL){  
        caminhos = criarGrafo(10000);
        Ler_arquivo_via(via, caminhos);
    }


    //Imprimindo no arquivo svg a partir das informações do arquivo .geo
    fprintf(svg, "<svg>\n");
    inputSombraQuadras(arvoreQuadra, getFirstElementTree(arvoreQuadra), svg, densidadeQuadra, x_dd, y_dd, w_dd, h_dd);
    processarTree(arvoreForma,getFirstElementTree(arvoreForma),svg_imprimir_forma,svg);
    processarTree(arvoreQuadra,getFirstElementTree(arvoreQuadra),svg_imprimir_quadra,svg);
    processarTree(arvoreHidrante,getFirstElementTree(arvoreHidrante),svg_imprimir_hidrante,svg);
    processarTree(arvoreSemaforo,getFirstElementTree(arvoreSemaforo),svg_imprimir_semaforo,svg);
    processarTree(arvoreRadioBase,getFirstElementTree(arvoreRadioBase),svg_imprimir_rb,svg);
    processarTree(arvoreTexto,getFirstElementTree(arvoreTexto),svg_imprimirTexto,svg);
    processarTree(arvorePosto,getFirstElementTree(arvorePosto),svg_imprimir_posto,svg);
    fprintf(svg, "\n</svg>");

    if(entradaQry != NULL){
        //Concatenação e criação do .txt
        arqtxt = criarTxt(entradaGeoNew,entradaQryNew, diretorioSaida, arqtxt);
        txt = fopen(arqtxt,"w+");
        //Concatenação e criação do .svg a partir das informações do arquivo .qry
        arqsvg2 = criarSvg2(entradaGeoNew,entradaQryNew, diretorioSaida, arqsvg2);
        svg2 = fopen(arqsvg2,"w+");
        rewind(qry);
        //Lendo arquivo .qry
        fprintf(svg2, "<svg>\n");
        Ler_arquivo_gry(qry, svg2, txt, arvoreForma, arvoreTexto, arvoreQuadra, arvoreHidrante, arvoreSemaforo, arvoreRadioBase, arvorePosto, arvoreCasos, 
                        pessoas, quadraTable, hidranteTable, semaforoTable, radioBaseTable, moradores, comercios,
                        diretorioSaida, entradaGeoNew, entradaQryNew, caminhos, listaCasoN, listaCasoS, listaCasoL, listaCasoO, contadorId);
        fprintf(svg2, "\n</svg>");  
    }

    //free e fclose
    free(entradaGeo);
    free(entradaGeoNew);
    free(entradaSvg);
    free(diretorioSaida);

    if(diretorioEntrada != NULL){
        free(diretorioEntrada);
    }

    if(entradaQry != NULL){
        free(entradaQry);
        free(entradaQryNew);
        free(entradaTxt);
        free(entradaSvg2);
        free(entradaEc);
        free(entradaPm);
        free(entradaVia);
        free(arqqry); 
        free(arqsvg2);
        free(arqtxt);
        free(arqec);
        free(arqpm);
        free(arqvia);
        fclose(qry);
        fclose(svg2);
        fclose(txt);
    }

    //free nas arvores 
    desalocaQt(arvoreForma);
    desalocaQt(arvoreTexto);
    desalocaQt(arvoreQuadra);
    desalocaQt(arvoreHidrante);
    desalocaQt(arvoreSemaforo);
    desalocaQt(arvoreRadioBase);
    desalocaQt(arvorePosto);
    desalocaQt(arvoreCasos);

    //free nas hashtable
    destroiHashTable(quadraTable);
    destroiHashTable(comercios);
    destroiHashTable(pessoas);
    destroiHashTable(moradores);
    destroiHashTable(tipoComercio);
    destroiHashTable(semaforoTable);
    destroiHashTable(hidranteTable);
    destroiHashTable(radioBaseTable);
    
    fclose(svg);
    free(arqgeo);
    free(arqsvg);
    fclose(geo);

    if(entradaEc != NULL){
        fclose(ec);
    }
 
    if(entradaPm != NULL){
        fclose(pm);
    }

    if(entradaVia != NULL){
        fclose(via);
    }
  
    return 0;
}