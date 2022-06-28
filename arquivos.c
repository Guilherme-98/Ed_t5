#include"arquivos.h"

//Função que cria o arquivo .svg no diretório de saída

char * criarSvg(char entradaGeoNew[], char diretorioSaida[], char *arqsvg){
int i = 0;

char *entradaSvg = (char *)malloc((strlen(entradaGeoNew) + 1) * sizeof(char));

    while(entradaGeoNew[i] != '.'){
		entradaSvg[i] = entradaGeoNew[i];
		i++;
    }

    entradaSvg[i] = '\0';
    strcat(entradaSvg,".svg");

    if(diretorioSaida[strlen(diretorioSaida) - 1] == '/'){
        arqsvg = (char *) malloc ((strlen(entradaSvg) + strlen(diretorioSaida) + 1) * sizeof(char));
        sprintf(arqsvg, "%s%s", diretorioSaida, entradaSvg);
    
    }
    else{
        arqsvg = (char *) malloc ((strlen(entradaSvg) + strlen(diretorioSaida) + 2) * sizeof(char));
        sprintf(arqsvg, "%s/%s", diretorioSaida, entradaSvg);
    }

    free(entradaSvg);
    
return arqsvg; 
}

//Funcao que cria um segundo arquivo .svg no diretorio de saida 

char * criarSvg2(char entradaGeoNew[], char entradaQryNew[], char diretorioSaida[], char *arqsvg2){
int i = 0,j = 0;
char *entradaSvg2 = NULL;

entradaSvg2 = (char *)malloc((strlen(entradaGeoNew) + strlen(entradaQryNew) + 1) * sizeof(char));

    while(entradaGeoNew[i] != '.'){
		entradaSvg2[i] = entradaGeoNew[i];
		i++;
    }
    
    entradaSvg2[i] = '\0';

    strcat(entradaSvg2, "-");
	i = i +1;

	while(entradaQryNew[j] != '.'){
		entradaSvg2[i] = entradaQryNew[j];
		j++;
		i++;
	}
    entradaSvg2[i] = '\0';

    strcat(entradaSvg2,".svg");

    if(diretorioSaida[strlen(diretorioSaida) - 1] == '/'){
        arqsvg2 = (char *) malloc ((strlen(entradaSvg2) + strlen(diretorioSaida) + 1) * sizeof(char));
        sprintf(arqsvg2, "%s%s", diretorioSaida, entradaSvg2);
    
    }
    else{
        arqsvg2 = (char *) malloc ((strlen(entradaSvg2) + strlen(diretorioSaida) + 2) * sizeof(char));
        sprintf(arqsvg2, "%s/%s", diretorioSaida, entradaSvg2);
    }

    free(entradaSvg2);

return arqsvg2; 
}

//Funcao que cria um terceiro arquivo .svg no diretorio de saida no comando dmprbt 

char * criarSvg3(char entradaGeoNew[], char entradaQryNew[], char entradaSfx[], char diretorioSaida[], char *arqsvg){
int i = 0, j = 0, k=0;
char *entradaSvg3 = NULL;

entradaSvg3 = (char *)malloc((strlen(entradaGeoNew) + strlen(entradaQryNew) + strlen(entradaSfx)) * sizeof(char));

    while(entradaGeoNew[i] != '.'){
		entradaSvg3[i] = entradaGeoNew[i];
		i++;
    }
    
    entradaSvg3[i] = '\0';

    strcat(entradaSvg3, "-");
	i = i +1;

	while(entradaQryNew[j] != '.'){
		entradaSvg3[i] = entradaQryNew[j];
		j++;
		i++;
	}

    entradaSvg3[i] = '\0';

    strcat(entradaSvg3, "-");
	i = i +1;

    while(entradaSfx[k] != '\0'){
		entradaSvg3[i] = entradaSfx[k];
        k++;
		i++;
    }
    
    entradaSvg3[i] = '\0';

    strcat(entradaSvg3,".svg");

    if(diretorioSaida[strlen(diretorioSaida) - 1] == '/'){
        arqsvg = (char *) malloc ((strlen(entradaSvg3) + strlen(diretorioSaida) + 1) * sizeof(char));
        sprintf(arqsvg, "%s%s", diretorioSaida, entradaSvg3);
    }
    else{
        arqsvg = (char *) malloc ((strlen(entradaSvg3) + strlen(diretorioSaida) + 2) * sizeof(char));
        sprintf(arqsvg, "%s/%s", diretorioSaida, entradaSvg3);
    }
    free(entradaSvg3);

return arqsvg; 

}

//Funcao que cria o .txt no diretório de saída

char * criarTxt(char entradaGeoNew[], char entradaQryNew[],char diretorioSaida[], char *arqtxt){
char * entradaTxt = NULL;
int i = 0, j = 0;
entradaTxt = (char*) malloc ((strlen(entradaGeoNew) + strlen(entradaQryNew) + 1) * sizeof(char));

	while (entradaGeoNew[i] != '.'){
		entradaTxt[i] = entradaGeoNew[i];
		i++;
	}

    entradaTxt[i] = '\0';
	
	strcat(entradaTxt, "-");	
	i = i+1;

	while (entradaQryNew[j] != '.'){
		entradaTxt[i] = entradaQryNew[j];
		j++;
		i++;
        
	}

    entradaTxt[i]='\0';
	strcat(entradaTxt, ".txt");

    if(diretorioSaida[strlen(diretorioSaida) - 1] == '/'){
        arqtxt = (char *) malloc ((strlen(entradaTxt) + strlen(diretorioSaida) + 1) * sizeof(char));
        sprintf(arqtxt, "%s%s", diretorioSaida, entradaTxt);
    
    }
    else{
        arqtxt = (char *) malloc ((strlen(entradaTxt) + strlen(diretorioSaida) + 2) * sizeof(char));
        sprintf(arqtxt, "%s/%s", diretorioSaida, entradaTxt);
    }
    free(entradaTxt);
    return arqtxt;
}