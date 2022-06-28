#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "svg_qry.h"

void putSVGNode(FILE *file, double x, int y, char *descricao, char *posicao){
    fprintf(file, "<circle cx=\"%lf\" cy=\"%d\" r=\"%d\" fill=\"black\"/>\n", x, y, TREE_NODE_RADIUS);
    fprintf(file, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-family=\"Arial\" font-size=\"%d\" dominant-baseline=\"middle\" "
                  "text-anchor=\"middle\" style=\"stroke:#000;stroke-width:2.0\">%s</text>\n", 
                  x, y - TREE_TEXT_SIZE / 2.0, TREE_TEXT_SIZE, descricao);
        
        fprintf(file, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-family=\"Arial\" font-size=\"%d\" dominant-baseline=\"middle\" "
                       "text-anchor=\"middle\" style=\"stroke:#000;stroke-width:2.0\">%s</text>\n", 
                       x, y + TREE_TEXT_SIZE / 2.0, TREE_TEXT_SIZE, posicao);
}

static double _generateTreeSVG(Tree arvore, FILE *file, PosicNo node, int height, double xMin, double *x, void (*describe)(Element, char*, char*)){
    char descricao[64];
    char posicao[64];

    if(node == NULL){
        *x = xMin;
        putSVGNode(file, *x, TREE_TOP_MARGIN + height * TREE_Y_SPACING, "", "nil");
        return xMin + TREE_X_SPACING * 2;
    }
    double xNe;
    double xMaxNe = _generateTreeSVG(arvore, file, getNe(arvore, node), height + 1, xMin, &xNe, describe);

    double xNw;
    double xMaxNw = _generateTreeSVG(arvore, file, getNw(arvore, node), height + 1, xMaxNe, &xNw, describe);

    double xSe;
    double xMaxSe = _generateTreeSVG(arvore, file, getSe(arvore, node), height + 1, xMaxNw, &xSe, describe);

    double xSw;
    double xMaxSw = _generateTreeSVG(arvore, file, getSw(arvore, node), height + 1, xMaxSe, &xSw, describe);

    *x = (xNe + xSw) / 2;
    int y = TREE_TOP_MARGIN + height * TREE_Y_SPACING;
    int yChild = y + TREE_Y_SPACING;

    svg_imprimir_linha(file, *x, y, xSw, yChild - TREE_NODE_RADIUS,"blue");
    svg_imprimir_linha(file, *x, y, xSe, yChild - TREE_NODE_RADIUS,"yellow");
    svg_imprimir_linha(file, *x, y, xNw, yChild - TREE_NODE_RADIUS,"red");
    svg_imprimir_linha(file, *x, y, xNe, yChild - TREE_NODE_RADIUS,"green");

    describe(getElement(arvore, node), descricao, posicao);

    putSVGNode(file, *x, y, descricao, posicao);
    
    return xMaxSw + TREE_X_SPACING;
}


void consulta_dmprbt(char t[32], char *sfx, char *diretorioSaida, Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase, FILE* txt, char *entradaGeoNew, char *entradaQryNew){
    char * arqsvg3 = NULL;
    FILE *svg3;
    double x;

    arqsvg3 = criarSvg3(entradaGeoNew, entradaQryNew, sfx, diretorioSaida, arqsvg3);	
    svg3 = fopen(arqsvg3,"w+");
  
    fprintf(svg3, "<svg xmlns=\"http://www.w3.org/2000/svg\" weight=\"10000\" height=\"10000\">\n");
    if(!strcmp (t, "q"))_generateTreeSVG(arvoreQuadra, svg3, getFirstElementTree(arvoreQuadra), 0, TREE_LEFT_MARGIN, &x, getQuadraInformacao);
	if(!strcmp (t, "h"))_generateTreeSVG(arvoreHidrante, svg3, getFirstElementTree(arvoreHidrante), 0, TREE_LEFT_MARGIN, &x, getHidranteInformacao);
    if(!strcmp (t, "s"))_generateTreeSVG(arvoreSemaforo, svg3, getFirstElementTree(arvoreSemaforo), 0, TREE_LEFT_MARGIN, &x, getSemaforoInformacao);
    if(!strcmp (t, "t"))_generateTreeSVG(arvoreRadioBase, svg3, getFirstElementTree(arvoreRadioBase), 0, TREE_LEFT_MARGIN, &x, getRBInformacao);
    fprintf(svg3, "</svg>\n");

    fprintf(txt, "   LEGENDA QUADTREE:\n");
    fprintf(txt, "Coordenada SW cor: azul\n");
    fprintf(txt, "Coordenada SE cor: amarelo\n");
    fprintf(txt, "Coordenada NW cor: vermelha\n");
    fprintf(txt, "Coordenada NE cor: verde\n\n");
    
    free(arqsvg3);
    fclose(svg3);
}