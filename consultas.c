#include"consultas.h"
#include"leitura_geo.h"
#include"util.h"
#include"svg.h"
#include"lista.h"
#include"./elementos/forma.h"
#include"./elementos/quadra.h"
#include"./elementos/semaforo.h"
#include"./elementos/hidrante.h"
#include"./elementos/radioBase.h"
#include"./elementos/casos.h"
#include"./elementos/casosDentro.h"
#include"quadTree.h"


void consulta_o(Tree arvoreForma, char j[], char k[], FILE*txt, FILE *aux_txt){
Forma forma1;
Forma forma2;

PosicNo auxForma;
PosicNo auxForma2;

auxForma =  percorrer_Forma_QD(arvoreForma, j, getFirstElementTree(arvoreForma));
auxForma2 = percorrer_Forma_QD(arvoreForma, k, getFirstElementTree(arvoreForma));

forma1 = getElement(arvoreForma, auxForma);
forma2 = getElement(arvoreForma, auxForma2);

    if(forma1 == NULL){
        return;
    }
    if(forma2 == NULL){
        return;
    }
    
    if((strcmp(getTipoForma(forma1), "c") == 0) && (strcmp(getTipoForma(forma2),"c") == 0)){
        if(circulo_circulo(forma1, forma2)){
            fprintf(txt,"o? %s %s\n",j,k);
            fprintf(txt,"%s: circulo %s: circulo SIM\n\n",j,k);
            imprimir_retangulo_delimitador(forma1,forma2,true,aux_txt);

        }
        else{
            fprintf(txt,"o? %s %s\n",j,k);
            fprintf(txt,"%s: circulo %s: circulo NAO\n\n",j,k);
            imprimir_retangulo_delimitador(forma1,forma2,false,aux_txt);
        }          
    }

    else if((strcmp(getTipoForma(forma1), "r") == 0) && (strcmp(getTipoForma(forma2),"r") == 0)){
        if(retangulo_retangulo(forma1, forma2)){
            fprintf(txt,"o? %s %s\n",j,k);
            fprintf(txt,"%s: retangulo %s: retangulo SIM\n\n",j,k);
            imprimir_retangulo_delimitador(forma1,forma2,true,aux_txt);
        }
        else{
            fprintf(txt,"o? %s %s\n",j,k);
            fprintf(txt,"%s: retangulo %s: retangulo NAO\n\n",j,k);
            imprimir_retangulo_delimitador(forma1,forma2,false,aux_txt);
        }          

    }

    else if((strcmp(getTipoForma(forma1), "c") == 0) && (strcmp(getTipoForma(forma2),"r") == 0) || (strcmp(getTipoForma(forma1), "r") == 0) && (strcmp(getTipoForma(forma2),"c") == 0)){
        if(circulo_ou_retangulo(forma1,forma2)){
            if(strcmp(getTipoForma(forma1),"c") == 0){
                fprintf(txt,"o? %s %s\n",j,k);
                fprintf(txt,"%s: circulo %s: retangulo SIM\n\n",j,k);
                imprimir_retangulo_delimitador(forma1,forma2,true,aux_txt);
            }
            else{
                fprintf(txt,"o? %s %s\n",j,k);
                fprintf(txt,"%s: retangulo %s: circulo SIM\n\n",j,k);
                imprimir_retangulo_delimitador(forma1,forma2,true,aux_txt);
            }
            
        }
        else{
            if(strcmp(getTipoForma(forma1),"c") == 0){
                fprintf(txt,"o? %s %s\n",j,k);
                fprintf(txt,"%s: circulo %s: retangulo NAO\n\n",j,k);
                imprimir_retangulo_delimitador(forma1,forma2,false,aux_txt);
            }
            else{
                fprintf(txt,"o? %s %s\n",j,k);
                fprintf(txt,"%s: retangulo %s: circulo NAO\n\n",j,k);
                imprimir_retangulo_delimitador(forma1,forma2,false,aux_txt);
        
            }
        }
    }   
    
}

void consulta_i(Tree arvoreForma, char j[], double x, double y, FILE *txt, FILE *aux_txt){
double distancia;
PosicNo auxForma;
Forma forma;

    fprintf(txt,"i? %s %lf %lf\n",j,x,y);
    auxForma = percorrer_Forma_QD(arvoreForma, j, getFirstElementTree(arvoreForma));
    forma = getElement(arvoreForma, auxForma);
    
    if(forma == NULL){
        return;
    }
 
    if(strcmp(getTipoForma(forma), "c" ) == 0){
        distancia =  distanciaEuclidiana(x, y, getXForma(forma), getYForma(forma));
        
        if(distancia <= getRaioForma(forma)){
            fprintf(txt,"%s: circulo INTERNO\n\n",j);
            svg_imprimir_ponto(aux_txt, "blue", x, y);
            svg_imprimir_linha(aux_txt, x, y, getXForma(forma), getYForma(forma),"blue");
        }
        else{
            fprintf(txt,"%s: circulo NAO INTERNO\n\n",j);
            svg_imprimir_ponto(aux_txt, "magenta", x, y);
            svg_imprimir_linha(aux_txt, x, y, getXForma(forma), getYForma(forma),"magenta");
        }
    }

    else if(strcmp(getTipoForma(forma), "r" ) == 0){
        if(x > getXForma(forma) && x < getXForma(forma)  + getWForma(forma) && y > getYForma(forma) && y < getYForma(forma) + getHForma(forma)){    
            fprintf(txt,"%s: retangulo INTERNO\n\n",j);
            svg_imprimir_ponto(aux_txt, "blue", x, y);
            svg_imprimir_linha(aux_txt, x, y, getXForma(forma) + (getWForma(forma) / 2), getYForma(forma) + (getHForma(forma) / 2),"blue");
        }
        else{
            fprintf(txt,"%s: retangulo NAO INTERNO\n\n",j);
            svg_imprimir_ponto(aux_txt, "magenta", x, y);
            svg_imprimir_linha(aux_txt, x, y, getXForma(forma) + (getWForma(forma) / 2),getYForma(forma) + (getHForma(forma) / 2),"magenta");
        }
    }     
}

void consulta_pnt(Tree arvoreForma, Tree arvoreTexto, char j[], char corBorda[], char corPreenchimento[], FILE *txt){
PosicNo auxForma;
PosicNo auxTexto;
Forma forma;
Texto texto;
    
    auxForma = percorrer_Forma_QD(arvoreForma, j, getFirstElementTree(arvoreForma));
    forma = getElement(arvoreForma, auxForma);

    auxTexto = percorrer_Texto_QD(arvoreTexto, j, getFirstElementTree(arvoreTexto));
    texto = getElement(arvoreForma, auxTexto);
   

    fprintf(txt, "pnt j:%s corb:%s corp:%s\n", j, corBorda, corPreenchimento);

    if(forma != NULL){
        if(strcmp(getTipoForma(forma), "c") == 0 ){
            fprintf(txt,"id:%s\n",getIdForma(forma));
            fprintf(txt,"tipo:circulo\n");
            fprintf(txt,"raio:%lf\n",getRaioForma(forma));
            fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXForma(forma),getYForma(forma));
            fprintf(txt,"cor borda:%s\n",getcorBordaForma(forma));
            fprintf(txt,"cor preenchimento:%s\n\n",getcorPreenchimentoForma(forma));
        }
        else if(strcmp(getTipoForma(forma), "r") == 0 ){
            fprintf(txt,"id:%s\n",getIdForma(forma));
            fprintf(txt,"tipo:retangulo\n");
            fprintf(txt,"altura:%lf\n",getHForma(forma));
            fprintf(txt,"comprimento:%lf\n",getWForma(forma));
            fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXForma(forma),getYForma(forma));
            fprintf(txt,"cor borda:%s\n",getcorBordaForma(forma));
            fprintf(txt,"cor preenchimento:%s\n\n",getcorPreenchimentoForma(forma));
        }  
        setcorBordaForma(forma, corBorda);
        setcorPreenchimentoForma(forma, corPreenchimento);
    }
    if(texto != NULL){
        if(strcmp(getTipoTexto(texto), "t") == 0){
            fprintf(txt,"id:%s\n",getIdTexto(texto));
            fprintf(txt,"tipo:texto\n");
            fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXTexto(texto),getYTexto(texto));
            fprintf(txt,"cor borda:%s\n",getcorBordaTexto(texto));
            fprintf(txt,"cor preenchimento:%s\n",getcorPreenchimentoTexto(texto));
            fprintf(txt,"conteudo:%s\n", getConteudoTexto(texto));
            setcorBordaTexto(texto, corBorda);
            setcorPreenchimentoTexto(texto, corPreenchimento);
        } 
    }
}

void consulta_pnt_2(Tree arvoreForma, Tree arvoreTexto,  int j_num, int k_num, char corBorda[32], char corPreenchimento[32], FILE *txt){
int aux;
char j[32], k[32];
PosicNo auxForma;
PosicNo auxTexto;
Forma forma;
Texto texto;
 
 //if reponsalvel por verificar qual variavel é a menor em comparação com a outra
   if(j_num > k_num){
        aux = j_num;
        j_num = k_num;
        k_num = aux;
    }
  

    fprintf(txt,"pnt* j:%d k:%d corb:%s corp:%s\n",j_num,k_num,corBorda,corPreenchimento);
    int aux_j_num = j_num; 

    for(j_num; j_num <= k_num; j_num++){
        sprintf(j, "%d", j_num);

        auxForma = percorrer_Forma_QD(arvoreForma, j, getFirstElementTree(arvoreForma));
        forma = getElement(arvoreForma, auxForma);

        auxTexto = percorrer_Texto_QD(arvoreTexto, j, getFirstElementTree(arvoreTexto));
        texto = getElement(arvoreForma, auxTexto);

        if(forma != NULL){  
            if(strcmp(getTipoForma(forma), "c") == 0 ){
                fprintf(txt,"id:%s\n",getIdForma(forma));
                fprintf(txt,"tipo:circulo\n");
                fprintf(txt,"raio:%lf\n",getRaioForma(forma));
                fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXForma(forma),getYForma(forma));
                fprintf(txt,"cor borda:%s\n",getcorBordaForma(forma));
                fprintf(txt,"cor preenchimento:%s\n\n",getcorPreenchimentoForma(forma));
            }
            else if(strcmp(getTipoForma(forma), "r") == 0 ){
                fprintf(txt,"id:%s\n",getIdForma(forma));
                fprintf(txt,"tipo:retangulo\n");
                fprintf(txt,"altura:%lf\n",getHForma(forma));
                fprintf(txt,"comprimento:%lf\n",getWForma(forma));
                fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXForma(forma),getYForma(forma));
                fprintf(txt,"cor borda:%s\n",getcorBordaForma(forma));
                fprintf(txt,"cor preenchimento:%s\n\n",getcorPreenchimentoForma(forma));
            }  
            setcorBordaForma(forma, corBorda);
            setcorPreenchimentoForma(forma, corPreenchimento);
        }
        if(texto != NULL){
            if(strcmp(getTipoTexto(texto), "t") == 0 ){
                fprintf(txt,"id:%s\n",getIdTexto(texto));
                fprintf(txt,"tipo:texto\n");
                fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXTexto(texto),getYTexto(texto));
                fprintf(txt,"cor borda:%s\n",getcorBordaTexto(texto));
                fprintf(txt,"cor preenchimento:%s\n",getcorPreenchimentoTexto(texto));
                fprintf(txt,"conteudo:%s\n", getConteudoTexto(texto));
                setcorBordaTexto(texto, corBorda);
                setcorPreenchimentoTexto(texto, corPreenchimento);
            }
        }  
    }
}

void consulta_delf(Tree arvoreForma, Tree arvoreTexto, char j[], FILE *txt){
PosicNo auxForma;
PosicNo auxTexto;
Forma forma;
Texto texto;

    auxForma = percorrer_Forma_QD(arvoreForma, j, getFirstElementTree(arvoreForma));
    forma = getElement(arvoreForma, auxForma);

    auxTexto = percorrer_Texto_QD(arvoreTexto, j, getFirstElementTree(arvoreTexto));
    texto = getElement(arvoreForma, auxTexto);
    
    fprintf(txt,"delf j:%s\n",j);

    if(forma != NULL){  
        if(strcmp(getTipoForma(forma), "c") == 0 ){
            fprintf(txt,"id:%s\n",getIdForma(forma));
            fprintf(txt,"tipo:circulo\n");
            fprintf(txt,"raio:%lf\n",getRaioForma(forma));
            fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXForma(forma),getYForma(forma));
            fprintf(txt,"cor borda:%s\n",getcorBordaForma(forma));
            fprintf(txt,"cor preenchimento:%s\n\n",getcorPreenchimentoForma(forma));
        }
        else if(strcmp(getTipoForma(forma), "r") == 0 ){
            fprintf(txt,"id:%s\n",getIdForma(forma));
            fprintf(txt,"tipo:retangulo\n");
            fprintf(txt,"altura:%lf\n",getHForma(forma));
            fprintf(txt,"comprimento:%lf\n",getWForma(forma));
            fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXForma(forma),getYForma(forma));
            fprintf(txt,"cor borda:%s\n",getcorBordaForma(forma));
            fprintf(txt,"cor preenchimento:%s\n\n",getcorPreenchimentoForma(forma));
        }  
        removeNoQt(arvoreForma, auxForma);
    }
    if(texto != NULL){  
        if(strcmp(getTipoTexto(texto), "t") == 0){
        fprintf(txt,"id:%s\n",getIdTexto(texto));
        fprintf(txt,"tipo:texto\n");
        fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXTexto(texto),getYTexto(texto));
        fprintf(txt,"cor borda:%s\n",getcorBordaTexto(texto));
        fprintf(txt,"cor preenchimento:%s\n",getcorPreenchimentoTexto(texto));
        fprintf(txt,"conteudo:%s\n", getConteudoTexto(texto));
        removeNoQt(arvoreTexto, auxTexto);
        }
    } 
}

void consulta_delf_2 (Tree arvoreForma, Tree arvoreTexto, int j_num, int k_num,  FILE *txt){
int id_j, id_k, aux;
char j[32];
PosicNo auxForma;
PosicNo auxTexto;
Forma forma;
Texto texto;

   if(j_num > k_num){
        aux = j_num;
        j_num = k_num;
        k_num = aux;
    }

    fprintf(txt,"delf* j:%d k:%d\n",j_num, k_num);
    int id_j_aux = id_j;

    for(j_num; j_num <= k_num; j_num++){
        sprintf(j, "%d", j_num);

        auxForma = percorrer_Forma_QD(arvoreForma, j, getFirstElementTree(arvoreForma));
        forma = getElement(arvoreForma, auxForma);

        auxTexto = percorrer_Texto_QD(arvoreTexto, j, getFirstElementTree(arvoreTexto));
        texto = getElement(arvoreForma, auxTexto);

        if(forma != NULL){
            if(strcmp(getTipoForma(forma), "c") == 0 ){
                fprintf(txt,"id:%s\n",getIdForma(forma));
                fprintf(txt,"tipo:circulo\n");
                fprintf(txt,"raio:%lf\n",getRaioForma(forma));

                fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXForma(forma),getYForma(forma));
                fprintf(txt,"cor borda:%s\n",getcorBordaForma(forma));
                fprintf(txt,"cor preenchimento:%s\n\n",getcorPreenchimentoForma(forma));
            }
            else if(strcmp(getTipoForma(forma), "r") == 0 ){
                fprintf(txt,"id:%s\n",getIdForma(forma));
                fprintf(txt,"tipo:retangulo\n");
                fprintf(txt,"altura:%lf\n",getHForma(forma));
                fprintf(txt,"comprimento:%lf\n",getWForma(forma));
                fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXForma(forma),getYForma(forma));
                fprintf(txt,"cor borda:%s\n",getcorBordaForma(forma));
                fprintf(txt,"cor preenchimento:%s\n\n",getcorPreenchimentoForma(forma));
            }  
            removeNoQt(arvoreForma, auxForma);
        }
        if(texto != NULL){
            if(strcmp(getTipoTexto(texto), "t") == 0 ){
                fprintf(txt,"id:%s\n",getIdTexto(texto));
                fprintf(txt,"tipo:texto\n");
                fprintf(txt,"(X,Y) = (%lf,%lf)\n",getXTexto(texto),getYTexto(texto));
                fprintf(txt,"cor borda:%s\n",getcorBordaTexto(texto));
                fprintf(txt,"cor preenchimento:%s\n",getcorPreenchimentoTexto(texto));
                fprintf(txt,"conteudo:%s\n", getConteudoTexto(texto));
            }
            removeNoQt(arvoreTexto, auxTexto);
        }
    }
}

void consulta_dq(char aux[], char j[], double r, bool verificador, FILE *svg2, FILE* txt, FILE *txt_aux,
                Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase){
    char id[32];
    char resposta[4];
    double raio, x, y;

    Elemento elementoAux;

    if(verificador){
        strcpy(id, j);
        raio = r;
    }else{
        strcpy(id, aux);
        raio = r;
    }

    elementoAux = encontrarElementoArvores(id, arvoreQuadra, arvoreHidrante, arvoreSemaforo, arvoreRadioBase);

    if(strcmp(getTipoHidrante(elementoAux),"h") == 0){
       strcpy(resposta,"h");
    }

    if(strcmp(getTipoSema(elementoAux),"s") == 0){
        strcpy(resposta,"s");
    }

    if(strcmp(getTipoRB(elementoAux),"rb") == 0){
        strcpy(resposta,"rb");
    }

    if(strcmp(aux,"#") == 0){
        fprintf(txt, "dq: # cep:%s raio:%lf\n",id, raio);
    }
    else{
        fprintf(txt, "dq: cep:%s raio:%lf\n",id, raio);
    }

    Lista listaQuadra_2 = create();

    if(strcmp(resposta, "h") == 0){
        x = getXHid(elementoAux);
        y = getYHid(elementoAux);
        fprintf(txt, "Elemento urbano: %s\n", getIDHid(elementoAux));
    }else if(strcmp(resposta, "s") == 0){
        x = getXSema(elementoAux);
        y = getXSema(elementoAux);
        fprintf(txt, "Elemento urbano: %s\n", getIDSema(elementoAux));
    }else if(strcmp(resposta, "rb") == 0){
        x = getXRB(elementoAux);
        y = getYRB(elementoAux);
        fprintf(txt, "Elemento urbano: %s\n", getIDRB(elementoAux));
    }

    dq_percorrer_arvore(arvoreQuadra, x, y , raio, txt, svg2, verificador, getFirstElementTree(arvoreQuadra), listaQuadra_2);
    dq_quadra_remover(listaQuadra_2, arvoreQuadra);

    anelGrosso(svg2, elementoAux,resposta);
    anelDq(txt_aux, elementoAux, resposta, r);
    fprintf(txt,"\n\n");
}

void consulta_del(FILE* aux, Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase, char id[], FILE *svg2, FILE *txt){
    Elemento elementoAux;
    double x, y;
    PosicNo excluir;

    elementoAux = encontrarElementoArvores(id, arvoreQuadra, arvoreHidrante, arvoreSemaforo, arvoreRadioBase);

    fprintf(txt,"del: cep|id:%s\n",id);
    if(elementoAux != NULL){
        if(strcmp(getTipoHidrante(elementoAux),"h") == 0){
            excluir = percorrer_Hidrante_QD(arvoreHidrante, id, getFirstElementTree(arvoreHidrante));
            fprintf (txt, "Hidrante x = %lf y = %lf\n", getXHid (elementoAux), getYHid(elementoAux));
            removeNoQt(arvoreHidrante, excluir);
            svg_imprimir_linha(aux, getXHid(elementoAux), getYHid(elementoAux), getXHid(elementoAux), 0, "black");
            fprintf(svg2, "\n\t<text\n\t\tx=\"%lf\"", getXHid(elementoAux) + 10);
            fprintf(svg2, "\n\t\ty=\"0\"");
            fprintf(svg2, "\n\t\tstroke=\"black\"");
            fprintf(svg2, "\n\t\tfill=\"black\">");
            fprintf(svg2, "\n\t\t%s", id);
            fprintf(svg2, "\n\t</text>\n");
        }

        else if(strcmp(getTipoSema(elementoAux),"s") == 0){
            excluir = percorrer_Semaforo_QD(arvoreSemaforo, id, getFirstElementTree(arvoreSemaforo));
            fprintf (txt, "Semaforo x = %lf y = %lf\n", getXSema (elementoAux), getYSema(elementoAux));
            removeNoQt(arvoreSemaforo, excluir);
            svg_imprimir_linha(aux, getXSema(elementoAux), getYSema(elementoAux), getXSema(elementoAux), 0, "black");
            fprintf(svg2, "\n\t<text\n\t\tx=\"%lf\"", getXSema(elementoAux) + 10);
            fprintf(svg2, "\n\t\ty=\"0\"");
            fprintf(svg2, "\n\t\tstroke=\"black\"");
            fprintf(svg2, "\n\t\tfill=\"black\">");
            fprintf(svg2, "\n\t\t%s", id);
            fprintf(svg2, "\n\t</text>\n");
        }

        else if(strcmp(getTipoRB(elementoAux),"rb") == 0){
            excluir = percorrer_RB_QD(arvoreRadioBase, id, getFirstElementTree(arvoreRadioBase));
            fprintf (txt, "Radio base x = %lf y = %lf\n", getXRB (elementoAux), getYRB(elementoAux));
            removeNoQt(arvoreRadioBase, excluir);
            svg_imprimir_linha(aux, getXRB(elementoAux), getYRB(elementoAux), getXRB(elementoAux), 0, "black");
            fprintf(svg2, "\n\t<text\n\t\tx=\"%lf\"", getXRB(elementoAux) + 10);
            fprintf(svg2, "\n\t\ty=\"0\"");
            fprintf(svg2, "\n\t\tstroke=\"black\"");
            fprintf(svg2, "\n\t\tfill=\"black\">");
            fprintf(svg2, "\n\t\t%s", id);
            fprintf(svg2, "\n\t</text>\n");
        }

        else if(strcmp(getTipoQuadra(elementoAux),"q") == 0){
            excluir = percorrer_Quadra_QD(arvoreQuadra, id, getFirstElementTree(arvoreQuadra));
            x = getXQuadra(elementoAux) + getWQuadra(elementoAux)/2;
            y = getYQuadra(elementoAux) + getHQuadra(elementoAux)/2;
            fprintf (txt, "Quadra x = %lf y = %lf w = %lf h = %lf\n", getXQuadra (elementoAux), getYQuadra (elementoAux), getWQuadra (elementoAux), getHQuadra (elementoAux));
            removeNoQt(arvoreQuadra, excluir);
            svg_imprimir_linha(aux, x, y, x, 0, "black");
            fprintf(svg2, "\n\t<text\n\t\tx=\"%lf\"", x + 10);
            fprintf(svg2, "\n\t\ty=\"0\"");
            fprintf(svg2, "\n\t\tstroke=\"black\"");
            fprintf(svg2, "\n\t\tfill=\"black\">");
            fprintf(svg2, "\n\t\t%s", id);
            fprintf(svg2, "\n\t</text>\n");
        }

    }
    else{
        fprintf (txt, "Elemento nao encontrado!\n\n");
    }
}

void consulta_crd(Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase, char id[], FILE *txt){
    Elemento elementoAux;
    elementoAux = encontrarElementoArvores(id, arvoreQuadra, arvoreHidrante, arvoreSemaforo, arvoreRadioBase);

    fprintf(txt,"crd: cep|id:%s\n", id);

    if(elementoAux != NULL){
        if(strcmp(getTipoHidrante(elementoAux),"h") == 0){
            fprintf(txt, "Coordenadas do equipamento: x:%lf,  y:%lf\n", getXHid(elementoAux), getYHid(elementoAux));
            fprintf(txt, "Tipo do equip. urbano: Hidrante\n");
        }
        else if(strcmp(getTipoSema(elementoAux),"s") == 0){
            fprintf(txt, "Coordenadas do equipamento: x:%lf,  y:%lf\n", getXSema(elementoAux), getYSema(elementoAux));
            fprintf(txt, "Tipo do equip. urbano: Semaforo\n");
        }
        else if(strcmp(getTipoRB(elementoAux),"rb") == 0){
            fprintf(txt, "Coordenadas do equipamento: x:%lf,  y:%lf\n", getXRB(elementoAux), getYRB(elementoAux));
            fprintf(txt, "Tipo do equip. urbano: Radio base\n");
        }
        else if(strcmp(getTipoQuadra(elementoAux),"q") == 0){
            fprintf(txt, "Coordenadas do equipamento: x:%lf,  y:%lf\n", getXQuadra(elementoAux), getYQuadra(elementoAux));
            fprintf(txt, "Tipo: Quadra\n");
        }
    }else{
        fprintf(txt, "Elemento nao encontrado!\n");
    }
}

void consulta_cbq(Tree arvoreQuadra, FILE* svg2, FILE *txt, double x, double y, double r, char corB[]){
    fprintf(txt, "cbq: - x:%lf - y:%lf - r:%lf - cor da borda:%s\n", x, y, r, corB);
    percorrer_CBQ(arvoreQuadra, x, y, r, corB, txt, svg2, getFirstElementTree(arvoreQuadra));

}

void consulta_car(FILE* aux, Tree arvoreQuadra, FILE* txt, double x, double y, double w, double h){
    double areaFinal;
    char a[32];
    Texto text;

    fprintf(txt,"car: retangulo: - x:%lf - y:%lf - w:%lf - h:%lf\n",x, y, w, h);
    Forma ret = criarForma("0", "r", x, y, 0, w, h, "black", "none", "1.0");

    Lista listaQuadra_aux = create();

    percorrer_CAR(aux, txt, arvoreQuadra, getFirstElementTree(arvoreQuadra), x, y, h ,w, listaQuadra_aux);


    areaFinal = car_quadra_percorrer(listaQuadra_aux);
    svg_imprimir_forma(aux, ret);
    svg_imprimir_linha(aux, x, y, x, 0, "black");

    fprintf(txt, "Area total: %lf\n\n", areaFinal);
    sprintf(a, "%lf", areaFinal);
    text = criarTexto("0", "t", x, 0, "white", "black", a);
    svg_imprimirTexto(aux, text);

    freeForma(ret);
    freeTexto(text);
}

void consulta_cv(Tree arvoreQuadra, Tree arvoreCasos, double n, char cep[32], char face, double num, FILE* aux, Lista listaCasoN, Lista listaCasoS, Lista listaCasoL, Lista listaCasoO){
    double xQ, yQ, wQ, hQ, x, y;
    char a[32];
    char face2[32];

    Texto text;
    PosicNo quadraNo = percorrer_Quadra_QD(arvoreQuadra, cep, getFirstElementTree(arvoreQuadra));
    Quadra quadra = getElement(arvoreQuadra, quadraNo);
    Casos casos, casosAux;

    xQ = getXQuadra(quadra);
    yQ = getYQuadra(quadra);
    hQ = getHQuadra(quadra);
    wQ = getWQuadra(quadra);

    if (face == 'N'){
		x = xQ + num;
		y = yQ + hQ - 11.5;
        strcpy(face2, "N");
        casosAux = criarCasos(x, y, n, cep, face2);
        insert(listaCasoN, casosAux, "N");
        
        svg_imprimir_quadrado(aux, x, y, "orange", "orange");

	}
	else if (face == 'S'){
		x = xQ + num;
		y = yQ;
        strcpy(face2, "S");
        casosAux = criarCasos(x, y, n, cep, face2);
        insert(listaCasoS, casosAux, "S");

        svg_imprimir_quadrado(aux, x, y, "orange", "orange");

	}
	else if (face == 'L'){
		x = xQ;
		y = yQ + num;
        strcpy(face2, "L");
        casosAux = criarCasos(x, y, n, cep, face2);
        insert(listaCasoL, casosAux, "L");

        svg_imprimir_quadrado(aux, x, y, "orange", "orange");

	}
	else if (face == 'O'){
		x = xQ + wQ -11.5;
		y = yQ + num;
        strcpy(face2, "O");
        casosAux = criarCasos(x, y, n, cep, face2);
        insert(listaCasoO, casosAux, "O");

        svg_imprimir_quadrado(aux, x, y, "orange", "orange");

	}

    casos = criarCasos(x, y, n, cep, face2);
    insereQt(arvoreCasos, casos, getXCasos(casos), getYCasos(casos));

    sprintf(a, "%.0lf", n);
    x = x + (4.3 / 2.0);
    y = y + (17.0 / 2.0);

    text = criarTexto("0", "t", x, y, "white", "white", a);
    svg_imprimirTexto(aux, text);
    //freeTexto(text);
}

void consulta_soc(Tree arvoreQuadra, Tree arvorePosto, int posto_atendimento, char cep[32], char face, double num, FILE* aux, FILE* txt){
    double xQ, yQ, wQ, hQ, x,y;  

    PosicNo quadraNo = percorrer_Quadra_QD(arvoreQuadra, cep, getFirstElementTree(arvoreQuadra));
    Quadra quadra = getElement(arvoreQuadra, quadraNo);

    fprintf(txt, "soc: k:%d - cep:%s - face:%c - num:%lf\n", posto_atendimento, cep, face, num);
    xQ = getXQuadra(quadra);
    yQ = getYQuadra(quadra);
    hQ = getHQuadra(quadra);
    wQ = getWQuadra(quadra);

    if (face == 'N'){
		x = xQ + num;
		y = yQ + hQ - 11.5; 
        svg_imprimir_quadrado(aux, x, y, "blue", "white");

	}
	else if (face == 'S'){
		x = xQ + num;
		y = yQ;
        svg_imprimir_quadrado(aux, x, y, "blue", "white");

	}
	else if (face == 'L'){
		x = xQ;
		y = yQ + num;
        svg_imprimir_quadrado(aux, x, y, "blue", "white");

	}
	else if (face == 'O'){
		x = xQ + wQ - 11.5;
		y = yQ + num;
        svg_imprimir_quadrado(aux, x, y, "blue", "white");

	}

    Lista listaPosto = create();
    soc_posto_conversao(arvorePosto, getFirstElementTree(arvorePosto), listaPosto);
    soc_percorrer(listaPosto, x, y, posto_atendimento, txt, aux);

}

void consulta_ci(double x, double y, double r, FILE *aux, FILE *txt, Tree arvorePosto, Tree arvoreCasos){
    double area, densidadePoligono, casosTotal, categoriaDensidade;
    extern double densidade;
    fprintf (aux, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"none\" stroke=\"green\" stroke-width=\"8\" />\n", x, y, r);
    Lista pontosPoligono;
    fprintf(txt, "ci: X:%.2lf y:%.2lf r:%.2lf\n", x, y, r);

    Lista listaCasos = create();
    Lista listaCasosDentro = create();
    

    ci_casos_conversao(arvoreCasos, getFirstElementTree(arvoreCasos),listaCasos);
    casosTotal = ci_percorrer(listaCasos, listaCasosDentro, x, y, r, txt);
    pontosPoligono = convexHull(listaCasosDentro);
    percorrerPontosPoligono(pontosPoligono, aux);
    area = calcularArea(pontosPoligono);

    if(area == 0){
        fprintf(txt,"Não foi possivel a criação do poligno, quantidade de pontos menor do que 3.\n");
        return;
    }
    densidadePoligono = densidade * (area/1000000);
    categoriaDensidade = (casosTotal / densidadePoligono) * 100000;

    Lista listaPosto_ci = create();
    soc_posto_conversao(arvorePosto, getFirstElementTree(arvorePosto), listaPosto_ci);
    
    fprintf(txt, "A área dentro da envoltória convexa:%.2lf metros quadrados.\n",area);

    if(categoriaDensidade < 0.1){
        fprintf(aux, "\n\t<polygon points=\n\t\t");
        fprintf(aux,"\"");
        percorrer_poligono_svg (pontosPoligono, aux);
        fprintf(aux,"\"");
        fprintf(aux, "\n\t\tstroke=\"none\"");
        fprintf(aux, "\n\t\tfill=\"%s\"", "cyan");
        fprintf(aux, "\n\t\topacity=\"0.5\"");
        fprintf(aux, "\n\t/>\n");
        fprintf(txt, "A categoria de incidência:A\n");
    }

    else if(categoriaDensidade < 5.0){
        fprintf(aux, "\n\t<polygon points=\n\t\t");
        fprintf(aux,"\"");
        percorrer_poligono_svg (pontosPoligono, aux);
        fprintf(aux,"\"");
        fprintf(aux, "\n\t\tstroke=\"none\"");
        fprintf(aux, "\n\t\tfill=\"%s\"", "teal");
        fprintf(aux, "\n\t\topacity=\"0.5\"");
        fprintf(aux, "\n\t/>\n");
        fprintf(txt, "A categoria de incidência:B\n");
    }

    else if(categoriaDensidade < 10.0){
        fprintf(aux, "\n\t<polygon points=\n\t\t");
        fprintf(aux,"\"");
        percorrer_poligono_svg (pontosPoligono, aux);
        fprintf(aux,"\"");
        fprintf(aux, "\n\t\tstroke=\"none\"");
        fprintf(aux, "\n\t\tfill=\"%s\"", "yellow");
        fprintf(aux, "\n\t\topacity=\"0.5\"");
        fprintf(aux, "\n\t/>\n");
        fprintf(txt, "A categoria de incidência:C\n");
    }

    else if(categoriaDensidade < 20.0){
        fprintf(aux, "\n\t<polygon points=\n\t\t");
        fprintf(aux,"\"");
        percorrer_poligono_svg (pontosPoligono, aux);
        fprintf(aux,"\"");
        fprintf(aux, "\n\t\tstroke=\"none\"");
        fprintf(aux, "\n\t\tfill=\"%s\"", "red");
        fprintf(aux, "\n\t\topacity=\"0.5\"");
        fprintf(aux, "\n\t/>\n");
        fprintf(txt, "A categoria de incidência:D\n");
    }

    else if(categoriaDensidade >= 20.0) {
        fprintf(aux, "\n\t<polygon points=\n\t\t");
        fprintf(aux, "\"");
        percorrer_poligono_svg(pontosPoligono, aux);
        fprintf(aux, "\"");
        fprintf(aux, "\n\t\tstroke=\"none\"");
        fprintf(aux, "\n\t\tfill=\"%s\"", "purple");
        fprintf(aux, "\n\t\topacity=\"0.5\"");
        fprintf(aux, "\n\t/>\n");
        fprintf(txt, "A categoria de incidência:E\n");

        if (flagPointInside(pontosPoligono, listaPosto_ci) == false){
            centroide(pontosPoligono, area, aux);
        }
    }
}

void tratarBf(double max, Tree arvoreQuadra, Lista listaCasoN, Lista listaCasoS, Lista listaCasoL, Lista listaCasoO, FILE *svg, FILE *txt){
    Lista listaQuadra = create();
    bf_quadra_conversao(arvoreQuadra, getFirstElementTree(arvoreQuadra), listaQuadra);
    Bf_percorrer(listaQuadra, listaCasoN, max, svg, txt);
    Bf_percorrer(listaQuadra, listaCasoS, max, svg, txt);
    Bf_percorrer(listaQuadra, listaCasoL, max, svg, txt);
    Bf_percorrer(listaQuadra, listaCasoO, max, svg, txt);

}