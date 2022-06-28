#include "qry_via.h"
#include "util.h"
#include "svg.h"
#include "./elementos/vertice.h"

void setRegistrador(Point *registradores, char *r, Point ponto){
    if(!strcmp("R0", r))
        registradores[0] = ponto;
    else if(!strcmp("R1", r))
        registradores[1] = ponto;
    else if(!strcmp("R2", r))
        registradores[2] = ponto;
    else if(!strcmp("R3", r))
        registradores[3] = ponto;
    else if(!strcmp("R4", r))
        registradores[4] = ponto;
    else if(!strcmp("R5", r))
        registradores[5] = ponto;
    else if(!strcmp("R6", r))
        registradores[6] = ponto;
    else if(!strcmp("R7", r))
        registradores[7] = ponto;
    else if(!strcmp("R8", r))
        registradores[8] = ponto;
    else if(!strcmp("R9", r))
        registradores[9] = ponto;
    else if(!strcmp("R10", r))
        registradores[10] = ponto;
    else
        printf("Registrador Invalido!\n");
}

Point getRegisterPoint(Point *registradores, char *r){
    if(!strcmp("R0", r))
        return registradores[0];
    else if(!strcmp("R1", r))
        return registradores[1];
    else if(!strcmp("R2", r))
        return registradores[2];
    else if(!strcmp("R3", r))
        return registradores[3];
    else if(!strcmp("R4", r))
        return registradores[4];
    else if(!strcmp("R5", r))
        return registradores[5];
    else if(!strcmp("R6", r))
        return registradores[6];
    else if(!strcmp("R7", r))
        return registradores[7];
    else if(!strcmp("R8", r))
        return registradores[8];
    else if(!strcmp("R9", r))
        return registradores[9];
    else if(!strcmp("R10", r))
        return registradores[10];
    else
        printf("Registrador Invalido!\n");
}

void tratarRegistradorM(Point *registradores, char *reg, char *cpf, HashTable moradores, FILE *txt_aux){
    int verificador = 0;
    Moradores morador;
    Pessoa pessoa;

    for(int i = 0; i < getHashTableSize(moradores); i++){
        ListNode node = getHashNode(moradores, i);
        while(node != NULL){
            morador = getHashNodeElement(node);
            char *cepResident = getMoradoresCep(morador);

            if(!strcmp(cepResident, cpf)){
                pessoa = getMoradoresPessoa(morador);
                verificador = 1;
            }
            
            node = getHashNodeNext(node);
        }
    }

    double x = getMoradoresX(morador);
    double y = getMoradoresY(morador);

    Point ponto = createPoint(x, y);
    svg_imprimir_linha(txt_aux, getMoradoresX(morador), getMoradoresY(morador), getMoradoresX(morador), 0, "black");
    fprintf(txt_aux, "\n\t<text\n\t\tx=\"%lf\"", getMoradoresX(morador) + 10);
    fprintf(txt_aux, "\n\t\ty=\"10\"");
    fprintf(txt_aux, "\n\t\tstroke=\"black\"");
    fprintf(txt_aux, "\n\t\tfill=\"black\">");
    fprintf(txt_aux, "\n\t\tID: %s", reg);
    fprintf(txt_aux, "\n\t</text>\n");

    setRegistrador(registradores, reg, ponto);
}


void tratarRegistradorE(Point *registradores, char *reg, char *cep, char face, int num, HashTable quadrasTable, FILE *txt_aux){
    Quadra quadra = searchHashTable(quadrasTable, cep);
   
    double x, y;
    double xB = getXQuadra(quadra), yB = getYQuadra(quadra), wB = getWQuadra(quadra), hB = getHQuadra(quadra);

    if('N' == face){
        x = xB + num;
        y = yB + yB;
    }
    else if('S' == face){
        x = xB + num;
        y = yB;
    }
    else if('L' == face){
        x = xB;
        y = yB + num;
    }
    else if('O' == face){
        x = xB + wB;
        y = yB + num;
    }

    Point ponto = createPoint(x, y);
    svg_imprimir_linha(txt_aux, getXQuadra(quadra), getYQuadra(quadra), getXQuadra(quadra), 0, "black");
    fprintf(txt_aux, "\n\t<text\n\t\tx=\"%lf\"", getXQuadra(quadra) + 10);
    fprintf(txt_aux, "\n\t\ty=\"10\"");
    fprintf(txt_aux, "\n\t\tstroke=\"black\"");
    fprintf(txt_aux, "\n\t\tfill=\"black\">");
    fprintf(txt_aux, "\n\t\tID: %s", reg);
    fprintf(txt_aux, "\n\t</text>\n");
    
    setRegistrador(registradores, reg, ponto);
}

void tratarRegistradorG(Point *registradores, char *reg, char *id, HashTable hidrantesTable, HashTable semaforosTable, HashTable rabioBsesTable, FILE *txt_aux){
    double x, y;

    Element elemento = searchHashTable(hidrantesTable, id);
    if(elemento == NULL){
        elemento = searchHashTable(semaforosTable, id);
        
        if(elemento == NULL){
            elemento = searchHashTable(rabioBsesTable, id);
            x = getXRB(elemento);
            y = getYRB(elemento);
        }
        else{
            x = getXSema(elemento);
            y = getYSema(elemento);
        }
    }
    else{
        x = getXHid(elemento);
        y = getYHid(elemento);
    }

    Point ponto = createPoint(x, y);
    if(strcmp(getTipoHidrante(elemento),"h") == 0){
        svg_imprimir_linha(txt_aux, getXHid(elemento), getYHid(elemento), getXHid(elemento), 0, "black");
        fprintf(txt_aux, "\n\t<text\n\t\tx=\"%lf\"", getXHid(elemento) + 10);
        fprintf(txt_aux, "\n\t\ty=\"10\"");
        fprintf(txt_aux, "\n\t\tstroke=\"black\"");
        fprintf(txt_aux, "\n\t\tfill=\"black\">");
        fprintf(txt_aux, "\n\t\tID: %s", reg);
        fprintf(txt_aux, "\n\t</text>\n");       
    }
    else if(strcmp(getTipoSema(elemento),"s") == 0){
        svg_imprimir_linha(txt_aux, getXSema(elemento), getYSema(elemento), getXSema(elemento), 0, "black");
        fprintf(txt_aux, "\n\t<text\n\t\tx=\"%lf\"", getXSema(elemento) + 10);
        fprintf(txt_aux, "\n\t\ty=\"10\"");
        fprintf(txt_aux, "\n\t\tstroke=\"black\"");
        fprintf(txt_aux, "\n\t\tfill=\"black\">");
        fprintf(txt_aux, "\n\t\tID: %s", reg);
        fprintf(txt_aux, "\n\t</text>\n");       
    }
    else if(strcmp(getTipoRB(elemento),"rb") == 0){
        svg_imprimir_linha(txt_aux, getXRB(elemento), getYRB(elemento), getXRB(elemento), 0, "black");
        fprintf(txt_aux, "\n\t<text\n\t\tx=\"%lf\"", getXRB(elemento) + 10);
        fprintf(txt_aux, "\n\t\ty=\"10\"");
        fprintf(txt_aux, "\n\t\tstroke=\"black\"");
        fprintf(txt_aux, "\n\t\tfill=\"black\">");
        fprintf(txt_aux, "\n\t\tID: %s", reg);
        fprintf(txt_aux, "\n\t</text>\n");           
    }
    else if(strcmp(getTipoQuadra(elemento),"q") == 0){
        svg_imprimir_linha(txt_aux, getXQuadra(elemento), getYQuadra(elemento), getXQuadra(elemento), 0, "black");
        fprintf(txt_aux, "\n\t<text\n\t\tx=\"%lf\"", getXQuadra(elemento) + 10);
        fprintf(txt_aux, "\n\t\ty=\"10\"");
        fprintf(txt_aux, "\n\t\tstroke=\"black\"");
        fprintf(txt_aux, "\n\t\tfill=\"black\">");
        fprintf(txt_aux, "\n\t\tID: %s", reg);
        fprintf(txt_aux, "\n\t</text>\n");            
    }

    setRegistrador(registradores, reg, ponto);
}

int tratarP(FILE *arqSvg, Point *registradores, char r1[32], char r2[32], char corMc[32], char corMr[32], Grafo caminhos, FILE *txt_aux, int contadorId, FILE *txt){
    Point p1 = getRegisterPoint(registradores, r2);
    Point p2 = getRegisterPoint(registradores, r1);
    GNode v1 = getNodeGrafo(caminhos, 0);
    GNode v2 = getNodeGrafo(caminhos, 0);



    for(int i = 0; i < getFreeGrafo(caminhos); i++){
        GNode aux = getNodeGrafo(caminhos, i);

        if(distanciaEuclidiana(getPointX(p1), getPointY(p1), getNodeXGrafo(aux), getNodeYGrafo(aux)) < 
        distanciaEuclidiana(getPointX(p1), getPointY(p1), getNodeXGrafo(v1), getNodeYGrafo(v1))){
            v1 = aux;
        }

        if(distanciaEuclidiana(getPointX(p2), getPointY(p2), getNodeXGrafo(aux), getNodeYGrafo(aux)) < 
        distanciaEuclidiana(getPointX(p2), getPointY(p2), getNodeXGrafo(v2), getNodeYGrafo(v2))){
            v2 = aux;
        }
    }

    
    //Caminho mais rápido
    shortestWat_Dijkstra(caminhos, getNodeIdGrafo(v1), true);
    GNode aux = v2;

    double x1 = getNodeXGrafo(aux);
    double y1 = getNodeYGrafo(aux);
    svg_imprimir_circulo(arqSvg, x1+20, y1-18, 10, "red", "black");
    Texto palavraI = criarTexto("t5", "palavra", x1+18, y1-15.5, "white", "white", "I");
    svg_imprimirTexto(arqSvg, palavraI);
   
    while(aux != v1){
        double x1 = getNodeXGrafo(aux);
        double y1 = getNodeYGrafo(aux);

        Vertex vAux = getNodePGrafo(aux);
        if(vAux == NULL){
            printf("Nao existe via para o distino selecionado!\n");
            exit(1);
        }
        aux = getVerticeNodeGrafo(vAux);

        double x2 = getNodeXGrafo(aux);
        double y2 = getNodeYGrafo(aux);

        printCaminho(arqSvg, x1, y1, x2, y2, corMr, 7);
    }

    fprintf(txt, "\n");
   
    double x2 = getNodeXGrafo(aux);
    double y2 = getNodeYGrafo(aux);
    svg_imprimir_circulo(arqSvg, x2, y2+18, 10, "red", "black");
    Texto palavraF = criarTexto("t5", "palavra", x2-2, y2+20.5, "white", "white", "F");
    svg_imprimirTexto(arqSvg, palavraF);

    //Caminho mais curto
    shortestWat_Dijkstra(caminhos, getNodeIdGrafo(v1), false);

    aux = v2;
    while(aux != v1){
        double x1 = getNodeXGrafo(aux);
        double y1 = getNodeYGrafo(aux);

        Vertex vAux = getNodePGrafo(aux);
        if(vAux == NULL){
            printf("Nao existe via para o distino selecionado!\n");
            exit(1);
        }
        aux = getVerticeNodeGrafo(vAux);

        double x2 = getNodeXGrafo(aux);
        double y2 = getNodeYGrafo(aux);

        printCaminho(arqSvg, x1, y1, x2, y2, corMc, 4);
    }

    x2 = getNodeXGrafo(aux);
    y2 = getNodeYGrafo(aux);

    //Caminho mais curto animação
    contadorId++;
    shortestWat_Dijkstra(caminhos, getNodeIdGrafo(v1), false);

    aux = v2;
    int contador = 0;
    while(aux != v1){
        x1 = getNodeXGrafo(aux);
        y1 = getNodeYGrafo(aux);

        Vertex vAux = getNodePGrafo(aux);
        if(vAux == NULL){
            printf("Nao existe via para o distino selecionado!\n");
            exit(1);
        }
        aux = getVerticeNodeGrafo(vAux);

        x2 = getNodeXGrafo(aux);
        y2 = getNodeYGrafo(aux);

        animationPath(arqSvg, x1, y1, contador);
        contador++;
        animationPath(arqSvg, x2, y2, contador);  
    }
    fecharPath(arqSvg, contadorId);

    //Caminho mais rápido animação
    contadorId++;
    shortestWat_Dijkstra(caminhos, getNodeIdGrafo(v1), true);
    aux = v2;
    int contador2 = 0;

    x1 = getNodeXGrafo(aux);
    y1 = getNodeYGrafo(aux);
   
    while(aux != v1){
        x1 = getNodeXGrafo(aux);
        y1 = getNodeYGrafo(aux);

        Vertex vAux = getNodePGrafo(aux);
        if(vAux == NULL){
            printf("Nao existe via para o distino selecionado!\n");
            exit(1);
        }
        aux = getVerticeNodeGrafo(vAux);

        x2 = getNodeXGrafo(aux);
        y2 = getNodeYGrafo(aux);

        animationPath(arqSvg, x1, y1, contador2);
        contador2++;
        animationPath(arqSvg, x2, y2, contador2); 
    }
    fecharPath(arqSvg, contadorId);

    return contadorId;
}