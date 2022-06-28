#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include"./elementos/quadra.h"
#include"./elementos/hidrante.h"
#include"./elementos/semaforo.h"
#include"./elementos/radioBase.h"
#include"./elementos/texto.h"
#include"./elementos/posto.h"
#include"quadTree.h"
#include"lista.h"
#include"svg.h"
#include"util.h"
#include"shell_sort.h"
#include"quick_sort.h"
#include"moradores.h"
#include"comercio.h"
#include"./elementos/casos.h"
#include"./elementos/casosDentro.h"


typedef struct N{
    void *info;
	char tipo[4];
    struct N *anterior;
    struct N *proximo;
} no;

typedef struct L{
    no *primeiro;
    no *ultimo;
    int size;
} list;

Lista create(){
    list* lista = (list*) malloc(sizeof(list));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
	lista->size = 0;
    return lista;
}

void insert(Lista l, Elemento elemento, char tipo[]){
    list* lista = (list*) l;

    no* node = (no*) malloc(sizeof(no));
    node->info = elemento;
	strcpy(node->tipo, tipo);
    if(lista->primeiro == NULL) {
        node->anterior = NULL;
        lista->primeiro = node;
    } else {
        lista->ultimo->proximo = node;
        node->anterior = lista->ultimo;
    }
    lista->size++;
    node->proximo = NULL;
    lista->ultimo = node;
}

void print(FILE*svg, Lista l){
    int i = 1;

    list* lista = (list*) l;
    no* node = lista->primeiro;
    while(node != NULL) {
		if(strcmp(node->tipo, "c") == 0){
			svg_imprimir_forma(svg, node->info);
		}else if(strcmp(node->tipo, "r") == 0){
			svg_imprimir_forma(svg, node->info);
		}else if(strcmp(node->tipo, "q") == 0){
			svg_imprimir_quadra(svg, node->info);
		}else if(strcmp(node->tipo, "h") == 0){
			svg_imprimir_hidrante(svg, node->info);
		}else if(strcmp(node->tipo, "s") == 0){
			svg_imprimir_semaforo(svg, node->info);
		}else if(strcmp(node->tipo, "rb") == 0){
			svg_imprimir_rb(svg, node->info);
		}else if(strcmp(node->tipo, "t") == 0){
			svg_imprimirTexto(svg, node->info);
		}else if(strcmp(node->tipo, "ps") == 0){
			svg_imprimir_posto(svg, node->info);
		}

        node = node->proximo;
        i++;
    }
}
typedef struct stDist{
        Elemento *elemento;
        double dist;
    }*DistImp;

    Dist getDist(Dist distAux){
    DistImp dist = (DistImp) distAux;

        return dist;
    }

	double getDistancia(Dist distAux){
		 DistImp dist = (DistImp) distAux;
		 return dist->dist;
	}

void soc_percorrer(Lista listaPosto, double x, double y, int posto_atendimento, FILE *txt, FILE *aux){
	list* lista = (list*) listaPosto;
	no *node = lista->primeiro;
	DistImp *distPosto = (DistImp *) malloc(lista->size * sizeof(DistImp));
	int cont = 0;
    Elemento posto;

    while(node != NULL) {
		posto = node->info;
        distPosto[cont] = malloc(sizeof(struct stDist));
        distPosto[cont]->elemento = posto;
        distPosto[cont]->dist = distanciaEuclidiana (x, y, getXPosto (posto), getYPosto (posto));
		fprintf(txt, "x:%lf -- y:%lf\n", getXPosto(posto), getYPosto(posto));
		cont++;
        node = node->proximo;
    }
	if(posto_atendimento > cont){
		//printf("ERRO: Quantidade desejada de distâncias é maior que os postos disponíveis.\n");
	}
	int quant_postos = cont;
	shellSort((void *) distPosto, posto_atendimento, quant_postos);
    for(int i = 0;i < quant_postos;i++){
        if(i < posto_atendimento) {
            svg_imprimir_linha_trace(aux, x+11.5/2, y+11.5/2, getXPosto(distPosto[i]->elemento), getYPosto(distPosto[i]->elemento),"black");
        }
    }
	free(distPosto);
}
No get(Lista l, char id[]){
    list* lista = (list*) l;
	no *node = lista->primeiro;
	while(node != NULL){
		if(strcmp(node->info,id) == 0){
			return node->info;
		}
		node = node->proximo;
	}
	return NULL;
}

void Dq_percorrer(Lista quadra, Elemento e, double r, char tipo[], FILE *txt, FILE* svg2, bool verificador){
	list* lista = (list*) quadra;
	no *node = lista->primeiro;
	double x, y;
	if(strcmp(tipo, "h") == 0){
		x = getXHid(e);
		y = getYHid(e);
		fprintf(txt, "Elemento urbano: %s\n", getIDHid(e));
	}else if(strcmp(tipo, "s") == 0){
		x = getXSema(e);
		y = getXSema(e);
		fprintf(txt, "Elemento urbano: %s\n", getIDSema(e));
	}else if(strcmp(tipo, "rb") == 0){
		x = getXRB(e);
		y = getYRB(e);
		fprintf(txt, "Elemento urbano: %s\n", getIDRB(e));
	}
	int cont=0;
	while(node != NULL){
		if(distanciaEuclidiana(x, y, getXQuadra(node->info), getYQuadra(node->info) <= r))
			cont++;
		if (distanciaEuclidiana (x, y, getXQuadra (node->info) + getWQuadra (node->info), getYQuadra (node->info)) <= r) 
            cont++;
        if (distanciaEuclidiana (x, y, getXQuadra (node->info), getYQuadra (node->info) + getHQuadra (node->info)) <= r) 
            cont++;
        if (distanciaEuclidiana (x, y, getXQuadra (node->info) + getWQuadra (node->info), getYQuadra (node->info) + getHQuadra (node->info)) <= r) 
            cont++;
		if (cont == 4){
			fprintf(txt, "Cep removido: %s\n", getCEPQuadra(node->info));
			if(verificador){
				svg_imprimir_quadArrend(svg2, node->info);
				remover(quadra, getCEPQuadra(node->info));
			}else{
				remover(quadra, getCEPQuadra(node->info));
			}
			
		}
		cont=0;
		node = node->proximo;
	}
	fprintf(txt, "\n");
}
double calcularArea(Lista listaPoligono){
    list* pontos = (list*) listaPoligono;
	if(pontos->size < 3){
		return 0;
	}
    no* node = pontos->primeiro;
    double a=0, auxArea;
    void **vetPonto = malloc(pontos->size * sizeof(listaPoligono));
    for(int i = 0;i < pontos->size;i++){
        vetPonto[i] = node->info;
        node = node->proximo;
    }

    for(int j=0;j< pontos->size - 1;j++){
        auxArea = (getXCasosDentro(vetPonto[j]) * getYCasosDentro(vetPonto[j+1])) - (getXCasosDentro(vetPonto[j+1]) * getYCasosDentro(vetPonto[j]));
        a = a+auxArea;
    }
    auxArea = (getXCasosDentro(vetPonto[pontos->size - 1]) * getYCasosDentro(vetPonto[0])) - (getXCasosDentro(vetPonto[0]) * getYCasosDentro(vetPonto[pontos->size - 1]));
    a = a+auxArea;
    a = a/2;
    return a;
}

double ci_percorrer(Lista listaCasos, Lista cd, double x, double y, double raio, FILE *txt){
	list* lista = (list*) listaCasos;
	no* node = lista->primeiro;
	double distancia, contador = 0;
	Casos casos;
    fprintf(txt, "Coordenadas dos casos selecionados pelo círculo:\n");
    while(node != NULL) {
		casos = node->info;
        distancia =  distanciaEuclidiana(x, y, getXCasos(casos), getYCasos(casos));
        if(distancia <= raio){
            insert(cd, casos, "cd");
			contador = contador + getNCasosDentro(node->info);
			fprintf(txt, "x:%.2lf --- y:%.2lf\n", getXCasosDentro(node->info), getYCasosDentro(node->info));
		}
		node = node->proximo;
	}
	fprintf(txt, "O número total de casos dentro do circulo:%.2lf\n", contador);
	return contador;
}

void percorrer_poligono_svg (Lista listaPoligono, FILE*aux){
	list* lista = (list*) listaPoligono;
	no* node = lista->primeiro;
	while(node != NULL){
		svg_imprimir_poligono(aux, getXCasosDentro(node->info)+11.5/2, getYCasosDentro(node->info)+11.5/2);
		node = node->proximo;
	}
	
}
Casos casoInit;
int comparar(const void *caso1, const void *caso2){
	Casos *c1 = (Casos*) (*(void **)caso1);
	Casos *c2 = (Casos*) (*(void **)caso2);

    int o = orientation(casoInit, c1, c2);
    if( o == 0)
        return (distSq(casoInit, c2) >= distSq(casoInit, c1))? -1 : 1; 

    return (o == 2)? -1: 1;
	
}


Lista convexHull(Lista ListaCd){
	list* lista = (list*) ListaCd;
	no *node = lista->primeiro;
	void **vetCd = malloc(lista->size * sizeof(ListaCd));
	for(int i = 0;i < lista->size; i++){
		vetCd[i] = node->info;
		node = node->proximo;
	}
	int ymin = getYCasosDentro(vetCd[0]), min = 0; 
   	for (int i = 1; i < lista->size; i++) { 
		int y = getYCasosDentro(vetCd[i]); 
		if ((y < ymin) || (ymin == y && getXCasosDentro(vetCd[i]) < getXCasosDentro(vetCd[min]))) 
        	ymin = getYCasosDentro(vetCd[i]), min = i; 
	}

	vetCd[0] = vetCd[min];
	vetCd[min] = lista->primeiro->info; 
    casoInit = vetCd[0];
	quicksort(&vetCd[1], 0, ((lista->size)-2));                                                                                                                                                                                       qsort(&vetCd[1], (lista->size)-1, sizeof(Casos), comparar);

	int m = 1;
	for (int i = 1; i<lista->size; i++){
		while (i < (lista->size)-1 && orientation(casoInit, vetCd[i], vetCd[i+1]) == 0) 
          i++;

		vetCd[m] = vetCd[i];
		m++;
	}
	
	Lista pontosPoligono = create();
	if(lista->size < 3){
		return pontosPoligono;
	}
	insert(pontosPoligono, vetCd[0], "pl");
	insert(pontosPoligono, vetCd[1], "pl");
	insert(pontosPoligono, vetCd[2], "pl");
	
	for (int i = 3; i < m; i++) {
		list* poligono = (list*) pontosPoligono;
		while(orientation(poligono->ultimo->anterior->info, poligono->ultimo->info, vetCd[i]) != 2)
			pop(poligono);

		insert(pontosPoligono, vetCd[i], "pl");
	}
	free(vetCd);
	return pontosPoligono;
}
void percorrerPontosPoligono(Lista pontosPoligono, FILE *aux){
	list* lista = (list*) pontosPoligono;
	if(lista->size < 3){
		return;
	}

	no *node = lista->primeiro;
	Casos auxiliar, lastLine;
	lastLine = node->info;
	
	
	while(node->proximo != NULL){
		auxiliar = node->info;
		node = node->proximo;
		fprintf(aux, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"5\" />\n",
		getXCasosDentro(node->info)+11.5/2, getYCasosDentro(node->info)+11.5/2, 
		getXCasosDentro(auxiliar)+11.5/2, getYCasosDentro(auxiliar)+11.5/2);
	}
	fprintf(aux, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"5\" />\n", getXCasosDentro(node->info)+11.5/2, getYCasosDentro(node->info)+11.5/2, 
	getXCasosDentro(lastLine)+11.5/2, getYCasosDentro(lastLine)+11.5/2);
}

bool flagPointInside(Lista pontosPoligono, Lista postos){
    double xMin, yMin, xMax, yMax, auxX, auxY;
    list* pontos = (list*) pontosPoligono;
    no *node = pontos->primeiro;
    xMin = getXCasosDentro(node->info);
    xMax = getXCasosDentro(node->info);
    yMin = getYCasosDentro(node->info);
    yMax = getYCasosDentro(node->info);
    while(node->proximo != NULL){
        node = node->proximo;
        if(getXCasosDentro(node->info) < xMin){
            xMin = getXCasosDentro(node->info);
        }
        if(getYCasosDentro(node->info) < yMin){
            yMin = getYCasosDentro(node->info);
        }
        if(getXCasosDentro(node->info) > xMax){
            xMax = getXCasosDentro(node->info);
        }
        if(getYCasosDentro(node->info) > yMax){
            yMax = getYCasosDentro(node->info);
        }
    }
    list* p = (list*) postos;
    int cont = 0;
    node = p->primeiro;
    while(node != NULL){
        Elemento posto = node->info;
        if(getXPosto(posto) < xMin || getXPosto(posto) > xMax
           || getYPosto(posto) < yMin || getYPosto(posto) > yMax) {
            cont++;
        }
        node = node->proximo;
    }
    if(cont == p->size){
        return false;
    }else if(cont < p->size){
        return true;
    }
}

void centroide(Lista listaPoligono, double area, FILE *aux){
    list* pontos = (list*) listaPoligono;
    no *node = pontos->primeiro;
    double cx = 0, cy = 0;
    double xAux, yAux;
    void **vetPonto = malloc(pontos->size * sizeof(listaPoligono));
    for(int i = 0;i < pontos->size;i++){
        vetPonto[i] = node->info;
        node = node->proximo;
    }
    for(int i = 0;i < pontos->size - 1;i++){
        xAux = (getXCasosDentro(vetPonto[i]) + getXCasosDentro(vetPonto[i+1])) *
                (getXCasosDentro(vetPonto[i]) * getYCasosDentro(vetPonto[i+1]) -
                getXCasosDentro(vetPonto[i+1]) * getYCasosDentro(vetPonto[i]));
        cx = cx+xAux;
    }
    xAux = (getXCasosDentro(vetPonto[pontos->size-1]) + getXCasosDentro(vetPonto[0])) *
           (getXCasosDentro(vetPonto[pontos->size-1]) * getYCasosDentro(vetPonto[0]) -
            getXCasosDentro(vetPonto[0]) * getYCasosDentro(vetPonto[pontos->size-1]));
    cx = cx+xAux;
    cx = cx/(6*area);
    for(int i = 0;i < pontos->size - 1;i++) {
        yAux = (getYCasosDentro(vetPonto[i]) + getYCasosDentro(vetPonto[i+1])) *
             (getXCasosDentro(vetPonto[i]) * getYCasosDentro(vetPonto[i+1]) -
              getXCasosDentro(vetPonto[i+1]) * getYCasosDentro(vetPonto[i]));
        cy = cy+yAux;
    }
    yAux = (getYCasosDentro(vetPonto[pontos->size-1]) + getYCasosDentro(vetPonto[0])) *
           (getXCasosDentro(vetPonto[pontos->size-1]) * getYCasosDentro(vetPonto[0]) -
            getXCasosDentro(vetPonto[0]) * getYCasosDentro(vetPonto[pontos->size-1]));
    cy = cy+yAux;
    cy = cy/(6*area);
    svg_imprimir_ponto(aux, "green",cx, cy);
    fprintf(aux, "\n/>");
    free(vetPonto);
}


void cbqFunction(Lista quadra, FILE* txt, FILE* svg2, double x, double y, double r, char CorBorda[]){
	list* lista = (list*) quadra;
	no *node = lista->primeiro;

	int cont=0;
	while(node != NULL){
		if(distanciaEuclidiana(x, y, getXQuadra(node->info), getYQuadra(node->info) <= r))
			cont++;
		if (distanciaEuclidiana (x, y, getXQuadra (node->info) + getWQuadra (node->info), getYQuadra (node->info)) <= r) 
			cont++;
		if (distanciaEuclidiana (x, y, getXQuadra (node->info), getYQuadra (node->info) + getHQuadra (node->info)) <= r) 
			cont++;
		if (distanciaEuclidiana (x, y, getXQuadra (node->info) + getWQuadra (node->info), getYQuadra (node->info) + getHQuadra (node->info)) <= r) 
			cont++;
		if (cont == 4){
			setcorBordaQuadra(node->info, CorBorda);
			fprintf(txt, "Cep da quadra alterada: %s\n", getCEPQuadra(node->info));
		}
		cont=0;
		node = node->proximo;
	}
	fprintf(txt, "\n");
}

double carFunction(FILE* aux, FILE* txt, Lista listaQuadra, Lista listaHidrante, Lista listaSemaforo, Lista listaRadioBase, double x, double y, double h, double w){
	double areaQuadra = 0, areaHid = 0, areaSema = 0, areaRB = 0;
	double areaTotal=0;
	int cont = 0;
	char aq[32];
	list* lista;
	no *node;
	lista = (list*) listaQuadra;
	node = lista->primeiro;


	while(node != NULL){
		if (getXQuadra (node->info) > x && getXQuadra (node->info) < x + w && getYQuadra (node->info) > y && getYQuadra (node->info) < y + h)
			cont++;
		if (getXQuadra (node->info) + getWQuadra (node->info) > x && getXQuadra (node->info) + getWQuadra (node->info) < x + w && getYQuadra (node->info) > y && getYQuadra (node->info) < y + h)
			cont++;
		if (getXQuadra (node->info) > x && getXQuadra (node->info) < x + w && getYQuadra (node->info) + getHQuadra (node->info) > y && getYQuadra (node->info) + getHQuadra (node->info) < y + h)
			cont++;
		if (getXQuadra (node->info) + getWQuadra (node->info) > x && getXQuadra (node->info) + getWQuadra (node->info) < x + w && getYQuadra (node->info) + getHQuadra (node->info) > y && getYQuadra (node->info) + getHQuadra (node->info) < y + h)
			cont++;
		if(cont == 4){
			areaQuadra = getHQuadra(node->info) * getWQuadra(node->info);
			areaTotal = areaTotal + areaQuadra;
			sprintf(aq, "%.2lf", areaQuadra);
			Texto text = criarTexto("0", "t", (getXQuadra(node->info) + getWQuadra(node->info)/2), 
			(getYQuadra(node->info) + getHQuadra(node->info)/2), "white", "black", aq);
			svg_imprimirTexto(aux, text);
			fprintf(txt, "cep quadra:%s, area: %lf\n", getCEPQuadra(node->info), areaQuadra);
			freeTexto(text);
		}
		cont = 0; 
		node = node->proximo;
	}
	fprintf(txt, "Area total: %lf\n\n", areaTotal);
	return areaTotal;
}


char* getTipo(Lista l, char id[]){
    list* lista = (list*) l;
	no *node = lista->primeiro;
	while(node != NULL){
		if(strcmp(node->info,id) == 0){
			return node->tipo;
		}
		node = node->proximo;
	}
	return NULL;
}

void remover (Lista l, char id[]){
	char aux1[32];
    list* lista = (list*) l;
	no *aux = lista->primeiro;
	no *aux_ant = NULL;
	int cont = 0;

	while(aux != NULL && (strcmp(aux->info, id) != 0)){
		cont++;
		aux_ant = aux;
		aux = aux->proximo;
	}
	if(aux == NULL){
		return;
	}
	if(aux_ant == NULL){
		lista->primeiro = aux->proximo;
		if(aux->proximo != NULL){
			aux->proximo->anterior = NULL;
		}else{
			lista->ultimo = NULL;
		}
		free(aux);
	}else if(aux->proximo == NULL){
		aux->anterior->proximo = NULL;
		lista->ultimo = aux->anterior;
		free(aux);
	}else{
		aux_ant->proximo = aux->proximo;
		aux->proximo->anterior = aux_ant;
		free(aux);
	}
	lista->size--;
}

void pop(Lista l){
	list* lista = (list*) l;
	no *node = lista->ultimo->anterior;
	free(lista->ultimo);
	lista->ultimo = node;
	node->proximo = NULL;	
	lista->size--;
}

void freeMem(Lista l, void *freeElemento){
    list* lista = (list*) l;
	if(l == NULL){
	}
	no *node  = lista->primeiro;
	void (*auxFree) (Elemento elemento) = freeElemento;

    if (node == NULL){
        free(lista);
        return;
    }

    while (1){
        if (node->proximo == NULL){
            auxFree (node->info);
            free (node);
            break;
        }
       	else {
			auxFree (node->info);
            node = node->proximo;
			if(node->anterior != NULL){
				free(node->anterior);
			}
        }	
    }
	free(lista);
}

void insertBefore(Lista l, Elemento elemento, char id[], char *tipo){
int aux;
    list* lista = (list*) l;
	if(id == 0){
		insert(lista, elemento, tipo);
	}else{
		no *atual = get(lista, id);
		if(atual != NULL){
			sprintf(id,"%d",aux);
			no *anterior = get(lista, id - 1);
			no *novono = (no *) malloc(sizeof(no));
			novono->info = elemento;
			anterior->proximo = novono;
			novono->proximo = atual;
			lista->size++;
		}
	}
}

void insertAfter(Lista l, Elemento elemento, char id[], char *tipo){
int aux;
    list* lista = (list*) l;
	if(id == 0){
		insert(lista, elemento, tipo);
	}else{
		no *atual = get(lista, id);
		if(atual != NULL){
			sprintf(id,"%d",aux);
			no *posterior = get(lista, id + 1);
			no *novono = (no *) malloc(sizeof(no));
			novono->info = elemento;
			atual->proximo = novono;
			novono->proximo = posterior;
			lista->size++;
		}
	}
}

No getFirst(Lista l){
    list* lista = (list*) l;
	if(lista->size > 0){
		no *node = lista->primeiro;
		return node;		
	}
    else{
	    return NULL;
    }
}

No getLast(Lista l){
    list* lista = (list*) l;
	if(lista->size != 0){
		no *node = lista->primeiro;
		while(node->proximo != NULL){
			node = node->proximo;
		}
		return node;
	}
	return NULL;
}

No getNext(Lista l, char id[]){
	int aux;
    list* lista = (list*) l;
	sprintf(id, "%d", aux);
	if(aux >= 0 && aux < lista->size){
		no *node = lista->primeiro;
		int acr = aux+1;
		for(int i = 0; i < acr; i++){
			node = node->proximo;
			if(node->proximo == NULL){
				return NULL;
			}
		return node;
		}
	}
	return NULL;
}

No getPrevious(Lista l, char id[]){
    list* lista = (list*) l;
	int aux;
	sprintf(id, "%d", aux);
	if(aux >= 0 && aux < lista->size){
		no *node = lista->primeiro;
		if(aux == 0){
			return NULL;
		}
		int acr = aux-1;
		int i = 0;
		while(i < acr){
			node = node->proximo;
			i++;
		}
		return node->info;
	}
	return NULL;
}

void dq_quadra_remover(Lista listaQuadra, Tree arvoreQuadra){
    list* lista = (list*) listaQuadra;
    no *node = lista->primeiro;
    PosicNo aux;
    while(node != NULL){
        aux = percorrer_Quadra_QD(arvoreQuadra, getCEPQuadra(node->info), getFirstElementTree(arvoreQuadra));
        removeNoQt(arvoreQuadra, aux);
        node = node->proximo;
    }
}

double car_quadra_percorrer(Lista listaQuadra){
	list* lista = (list*) listaQuadra;
    no *node = lista->primeiro;
	double areaQudra = 0, areaFinal = 0;
	while(node != NULL){
		areaQudra = getHQuadra(node->info) * getWQuadra(node->info);
		areaFinal = areaQudra + areaFinal;
		node = node->proximo;
	}
	return areaFinal;
}

void catac_quadra_remover(Lista removerQuadra, Tree arvoreQuadra){
	list* lista = (list*) removerQuadra;
	no *node = lista->primeiro;
	PosicNo aux;
	while(node != NULL){
		aux = percorrer_Quadra_QD(arvoreQuadra, getCEPQuadra(node->info), getFirstElementTree(arvoreQuadra));
		removeNoQt(arvoreQuadra, aux);
		node = node->proximo;
	}
}

void catac_hidrante_remover(Lista removerHidrante, Tree arvoreHidrante){
	list* lista = (list*) removerHidrante;
	no *node = lista->primeiro;
	PosicNo aux;
	while(node != NULL){
		aux = percorrer_Hidrante_QD(arvoreHidrante, getIDHid(node->info), getFirstElementTree(arvoreHidrante));
		removeNoQt(arvoreHidrante, aux);
		node = node->proximo;
	}
}

void catac_semaforo_remover(Lista removerSemaforo, Tree arvoreSemaforo){
	list* lista = (list*) removerSemaforo;
	no *node = lista->primeiro;
	PosicNo aux;
	while(node != NULL){
		aux = percorrer_Semaforo_QD(arvoreSemaforo, getIDSema(node->info), getFirstElementTree(arvoreSemaforo));
		removeNoQt(arvoreSemaforo, aux);
		node = node->proximo;
	}
}

void catac_radioBase_remover(Lista removerRadioBase, Tree arvoreRadioBase){
	list* lista = (list*) removerRadioBase;
	no *node = lista->primeiro;
	PosicNo aux;
	while(node != NULL){
		aux = percorrer_RB_QD(arvoreRadioBase, getIDSema(node->info), getFirstElementTree(arvoreRadioBase));
		removeNoQt(arvoreRadioBase, aux);
		node = node->proximo;
	}
}

void catac_morador_remover(Lista removerMorador, HashTable moradores){
	list* lista = (list*) removerMorador;
	no *node = lista->primeiro;
	while(node != NULL){
		removeHashTable(moradores, getMoradoresCpf(node->info));
		node = node->proximo;
	}
}

void catac_comercio_remover(Lista removerComercio, HashTable comercios){
	list* lista = (list*) removerComercio;
	no *node = lista->primeiro;
	PosicNo aux;
	while(node != NULL){
		removeHashTable(comercios, getComercioCnpj(node->info));
		node = node->proximo;
	}
}


void Bf_percorrer(Lista listaQuadra, Lista listaCasoAux, double max, FILE *svg, FILE *txt){
	char face[32];
	list* lista = (list*) listaQuadra;
	no *node = lista->primeiro;

	while(node != NULL){
		float resultado = 0;
		list* listaCaso = (list*) listaCasoAux;
		no *node2 = listaCaso->primeiro;

		while(node2 != NULL){
			strcpy(face, getFaceCasos(node2->info));
			if(strcmp(getCEPQuadra(node->info), getCepCasos(node2->info)) == 0){
				resultado = resultado + getNCasos(node2->info);
			}
			node2 = node2->proximo;
		}

		if(resultado > max){
			fprintf(txt, "CEP:%s FACE:%s Número total de casos:%.0lf\n", getCEPQuadra(node->info), face, resultado);
			if(strcmp(face, "N") == 0){
				printCaminho(svg, getXQuadra(node->info), getYQuadra(node->info)+getHQuadra(node->info), getXQuadra(node->info) + getWQuadra(node->info), getYQuadra(node->info)+getHQuadra(node->info), "red", 7);
			}

			if(strcmp(face, "S") == 0){
				printCaminho(svg, getXQuadra(node->info), getYQuadra(node->info), getXQuadra(node->info) + getWQuadra(node->info), getYQuadra(node->info), "red", 7);
			}

			if(strcmp(face, "O") == 0){
				printCaminho(svg, getXQuadra(node->info) + getWQuadra(node->info), getYQuadra(node->info), getXQuadra(node->info) + getWQuadra(node->info), getYQuadra(node->info) + getHQuadra(node->info), "red", 7);
			}

			if(strcmp(face, "L") == 0){
				printCaminho(svg, getXQuadra(node->info), getYQuadra(node->info), getXQuadra(node->info), getYQuadra(node->info) + getHQuadra(node->info), "red", 7);
			}
		}
		node = node->proximo;
	}
}

void addToResultList(Lista l, long int pos, int key){
	list* lista = (list*) l;
    no *node = lista->primeiro;
}

