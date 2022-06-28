#include<math.h>
#include"util.h"
#include"leitura_geo.h"
#include "consultas.h"
#include "lista.h"
#include"elementos/forma.h"

//Função que calcula a distância entre duas formas

double distanciaEuclidiana (double x1, double y1, double x2, double y2){
    return sqrt((pow((x1-x2),2) + pow((y1-y2),2)));
}

//Função que retorna o valor mais proximo

double clamp (double pc, double pmi, double pma){
    if(pc > pma){
        return pma;
    } 
    else if(pc < pmi){ 
       return pmi;
    }
    else{
        return pc;
    }
}

//Função que infroma se dois circulos estão juntos ou não

bool circulo_circulo (Forma forma1, Forma forma2){
   double distancia =  distanciaEuclidiana(getXForma(forma1), getYForma(forma1), getXForma(forma2), getYForma(forma2));
   
    if(distancia <= getRaioForma(forma1) + getRaioForma(forma2)){
        return true;
    }
    else{
        return false;
    }      
}

//Função que informa se dois retangulos estão juntos ou não

bool retangulo_retangulo (Forma forma1, Forma forma2){
    if (getXForma(forma1) <= getXForma(forma2) + getWForma(forma1) && getYForma(forma1) <= getYForma(forma2) + getHForma(forma2) &&  getXForma(forma1) + getWForma(forma1) >= getXForma(forma2) && getYForma(forma1) + getHForma(forma1) >= getYForma(forma2)){
        return true;
    }
    else{
        return false;
    }
}

//Função que informa se um retangulos e um circulo estão juntos ou não

bool circulo_ou_retangulo(Forma forma1, Forma forma2){
double aux1_x, aux1_y, aux1_r, aux1_h, aux1_w, aux2_x, aux2_y, aux2_r, aux2_h, aux2_w;

     if (strcmp(getTipoForma(forma1), "c") == 0){
        aux1_r = getRaioForma(forma1);
        aux1_x = getXForma(forma1);
        aux1_y = getYForma(forma1);
    }
    if (strcmp(getTipoForma(forma1), "r") == 0 ){
        aux2_w = getWForma(forma1);
        aux2_h = getHForma(forma1);
        aux2_x = getXForma(forma1);
        aux2_y = getYForma(forma1);
    }
    if (strcmp(getTipoForma(forma2), "c") == 0){
        aux1_r = getRaioForma(forma2);
        aux1_x = getXForma(forma2);
        aux1_y = getYForma(forma2);
    }
    if (strcmp(getTipoForma(forma2), "r") == 0 ){
        aux2_w = getWForma(forma2);
        aux2_h = getHForma(forma2);
        aux2_x = getXForma(forma2);
        aux2_y = getYForma(forma2);
    }

    double xmp = clamp (aux1_x, aux2_x, aux2_x + aux2_w);
    double ymp = clamp (aux1_y, aux2_y, aux2_y + aux2_h);

    if ((distanciaEuclidiana (aux1_x, aux1_y, xmp, ymp)) <= aux1_r){
        return true;
    }
    else{
         return false;
    }
}


// Função que imprimi o retangulo delimitador no arquivo .svg

void imprimir_retangulo_delimitador(Forma forma1, Forma forma2, bool sobrepoem, FILE *svg2){
double mx, mxr, mex, mexr, my, myr, mey, meyr, x, y, h, w;
double hm, wm, xmin, xmax, ymin, ymax;
double aux1_x, aux1_y, aux1_r, aux1_h, aux1_w, aux2_x, aux2_y, aux2_r, aux2_h, aux2_w;
    if((strcmp(getTipoForma(forma1), "c") == 0) && (strcmp(getTipoForma(forma2),"c") == 0)){

        if(getXForma(forma1) > getXForma(forma2)){
            mx = getXForma(forma1);
            mxr = getRaioForma(forma1);
            mex = getXForma(forma2);
            mexr = getRaioForma(forma2);
        }
        else{
            mx = getXForma(forma2);
            mxr = getRaioForma(forma2);
            mex = getXForma(forma1);
            mexr = getRaioForma(forma1);
        }

        if(getYForma(forma1) > getYForma(forma2)){
            my = getYForma(forma1);
            myr = getRaioForma(forma1);
            mey = getYForma(forma2);
            meyr = getRaioForma(forma2);
        }
        else{
            my = getYForma(forma2);
            myr = getRaioForma(forma2);
            mey = getYForma(forma1);
            meyr = getRaioForma(forma1);
        }

        //Define a largura, altura, x e y do retangulo delimitador

        w = (mx + mxr) - (mex - mexr);
        h = (my + myr) - (mey - meyr);
        x = mex - mexr;
        y = mey - meyr;
    }

    if((strcmp(getTipoForma(forma1), "r") == 0) && (strcmp(getTipoForma(forma2),"r") == 0)){
        if (getXForma(forma1) > getXForma(forma2)){
            mx = getXForma(forma1);
            mex = getXForma(forma2);
        }
        else{
            mx = getXForma(forma2);
            mex = getXForma(forma1);
        }
        
        if (getYForma(forma1) > getYForma(forma2)){
            my = getYForma(forma1);
            mey = getYForma(forma2);
        }
        else{
            my = getYForma(forma2);
            mey = getYForma(forma1);
        }

        if (getWForma(forma1) > getWForma(forma2)){
            wm = getWForma(forma1);
        }
        else{
            wm = getWForma(forma2);
        }
        if(getHForma(forma1) > getHForma(forma2)){
            hm = getHForma(forma1);
        }
        else{
            hm = getHForma(forma2);
        }
        
        //Define a largura, altura, x e y do retangulo delimitador

        w = mx + wm - mex;
        h = my + hm - mey;
        x = mex;
        y = mey;
    }

    if((strcmp(getTipoForma(forma1), "c") == 0) && (strcmp(getTipoForma(forma2),"r") == 0) || (strcmp(getTipoForma(forma1), "r") == 0) && (strcmp(getTipoForma(forma2),"c") == 0)){
         
        if(strcmp(getTipoForma(forma1), "c") == 0 ){
            aux1_r = getRaioForma(forma1);
            aux1_x = getXForma(forma1);
            aux1_y = getYForma(forma1);
        }
        if(strcmp(getTipoForma(forma1), "r") == 0 ){
            aux2_w = getWForma(forma1);
            aux2_h = getHForma(forma1);
            aux2_x = getXForma(forma1);
            aux2_y = getYForma(forma1);
        }
        if(strcmp(getTipoForma(forma2), "c") == 0 ){
            aux1_r = getRaioForma(forma2);
            aux1_x = getXForma(forma2);
            aux1_y = getYForma(forma2);
        }
        if(strcmp(getTipoForma(forma2), "r") == 0 ){
            aux2_w = getWForma(forma2);
            aux2_h = getHForma(forma2);
            aux2_x = getXForma(forma2);
            aux2_y = getYForma(forma2);
        }

        //Define x e y maximo e x e y minimo

        if((aux1_x - aux1_r) < aux2_x){
            xmin = aux1_x - aux1_r; 
        }   
        else{
             xmin = aux2_x;
        } 
        if((aux1_x + aux1_r) > (aux2_x + aux2_w)){
            xmax = aux1_x + aux1_r;
        }
        else{
            xmax = aux2_x + aux2_w;
        }
        if((aux1_y - aux1_r) < aux2_y){
            ymin = aux1_y - aux1_r;
        } 
        else{
            ymin = aux2_y;
        }
        if((aux1_y + aux1_r) > (aux2_y + aux2_h)){
            ymax = aux1_y + aux1_r;
        }
        else{
            ymax = aux2_y + aux2_h;
        }

        //Define a largura e altura do retangulo delimitador   
                    
        w = xmax - xmin;
        h = ymax - ymin;

        //Define o x mais proximo e y mais proximo
        double xmp = clamp (aux1_x, aux2_x, aux2_x + aux2_w);
        double ymp = clamp (aux1_y, aux2_y, aux2_y + aux2_h);

        x = xmin;
        y = ymin;    
    }

    if(sobrepoem){
        fprintf (svg2, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" stroke=\"black\"/>\n",x, y, w, h);
    }
    else{
        fprintf (svg2, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" stroke=\"black\" stroke-dasharray=\"5\"/>\n",x, y, w, h);
    }
}

double calculoDensidade(double w, double h, double habitantes){
    double areaRetangulo;
    double densidadeFinal; 

    areaRetangulo = w * h;

    areaRetangulo = areaRetangulo / 1000000;
    densidadeFinal = (habitantes / areaRetangulo); 
    

    return densidadeFinal;
}



