#include"tipoComercio_qry.h"

bool verificacao_ponto(double x, double y, double w, double h, Point p){

    if(getPointX(p) <= x+w && getPointX(p) >= x && getPointY(p) <= y+h && getPointY(p) >= y){
        return true;
    }
    else{
        return false;
    }
}

bool verificacao_ponto_circulo(double x, double y, double r, Point p){

    if(distanciaEuclidiana(x, y, getPointX(p), getPointY(p)) <= r ){
        return true;
    }
    else{
        return false;
    }   
}

bool verificacao_ponto_retangulo(double x, double y, double r, Quadra quadra){
    double xQ, yQ, wQ, hQ;
    bool verificar = true;
    int contador = 0;

    xQ = getXQuadra(quadra);
    yQ = getYQuadra(quadra);
    hQ = getHQuadra(quadra);
    wQ = getWQuadra(quadra);

    Point P1 = createPoint(xQ, yQ);
    Point P2 = createPoint(xQ + wQ, yQ);
    Point P3 = createPoint(xQ, yQ + hQ);
    Point P4 = createPoint(xQ  + wQ, yQ + hQ);

    verificar = verificacao_ponto_circulo(x, y, r, P1);
    if(verificar == true){
        contador++;
    }
    verificar = verificacao_ponto_circulo(x, y, r, P2);
    if(verificar == true){
        contador++;
    }
    verificar = verificacao_ponto_circulo(x, y, r, P3);
    if(verificar == true){
        contador++;
    }
    verificar = verificacao_ponto_circulo(x, y, r, P4);
    if(verificar == true){
        contador++;
    }

    freePoint(P1);
    freePoint(P2);
    freePoint(P3);
    freePoint(P4);

    if(contador == 4){
        return true;
    }
    else{
        return false;
    }
}

void consulta_eplg(FILE *aqrTxt, FILE *arqSvg, char *codt, HashTable comercios, double x, double y, double w, double h){
    FILE *pFile;

    fprintf(aqrTxt, "eplg? Estabelecimentos comerciais do tipo %s inteiramente contidos no poligono:\n", codt);
    Forma ret = criarForma("0", "r", x, y, 0, w, h, "black", "none", "1.0");
    //svg_imprimir_forma(arqSvg, ret);

    for(int i = 0; i < getHashTableSize(comercios); i++){
        ListNode node = getHashNode(comercios, i);
        while(node != NULL){
            Comercio store = getHashNodeElement(node);
            Pessoa owner = getComercioOwner(store);
            TipoComercio sType = getComercioType(store);

            if(!strcmp(codt, "*")){
                Point p  = createPoint(getComercioX(store), getComercioY(store));
                if(verificacao_ponto(x, y, w, h, p)){
                    fprintf(aqrTxt, "-%s:\n\tCNPJ: %s\n\tTipo: %s\n\tProprietário: %s %s\n\tCPF: %s\n\tCEP: %s, Face: %s, Número: %d\n\n", getComercioName(store), getComercioCnpj(store), getTipoComercioCodt(sType),getPessoaName(owner), getPessoaLastName(owner), getPessoaCpf(owner), getComercioCep(store), getComercioFace(store), getComercioNum(store));
                    svg_imprimir_circulo(arqSvg, getComercioX(store), getComercioY(store), 2.5, "black", "red");
                }
                freePoint(p);
            }
            else{
                if(!strcmp(codt, getTipoComercioCodt(getComercioType(store)))){
                    Point p  = createPoint(getComercioX(store), getComercioY(store));
                     if(verificacao_ponto(x, y, w, h, p)){             
                        fprintf(aqrTxt, "-%s:\n\tCNPJ: %s\n\tTipo: %s\n\tProprietário: %s %s\n\tCPF: %s\n\tCEP: %s, Face: %s, Número: %d\n\n", getComercioName(store), getComercioCnpj(store), getTipoComercioCodt(sType),getPessoaName(owner), getPessoaLastName(owner), getPessoaCpf(owner), getComercioCep(store), getComercioFace(store), getComercioNum(store));
                        svg_imprimir_circulo(arqSvg, getComercioX(store), getComercioY(store), 10, "black", "red");
                    }
                    freePoint(p);
                }
            }
            node = getHashNodeNext(node);
        }
    }
}

void* catac_quadra(FILE *arqTxt, double x, double y, double r, PosicNo aux, Tree arvoreQuadra, Lista removerQuadra){
    Quadra quadra;
    quadra = getElement(arvoreQuadra, aux);
    if(verificacao_ponto_retangulo(x, y, r, quadra)){
        insert(removerQuadra, quadra, "h");
        fprintf(arqTxt, "\t-quadra removido: %s\n", getCEPQuadra(quadra));
    }

    ItemNode resposta = NULL;

    if(leafNe(arvoreQuadra,aux) == 1)
        resposta = catac_quadra(arqTxt, x, y, r, getNe(arvoreQuadra,aux), arvoreQuadra, removerQuadra);

    if(resposta != NULL){
        return resposta;
    }

    if(leafNw((arvoreQuadra),aux) == 1)
        resposta = catac_quadra(arqTxt, x, y, r, getNw(arvoreQuadra,aux), arvoreQuadra, removerQuadra);

    if(resposta != NULL){
        return resposta;
    }

    if(leafSe((arvoreQuadra),aux) == 1)
        resposta = catac_quadra(arqTxt, x, y,r, getSe(arvoreQuadra,aux), arvoreQuadra, removerQuadra);

    if(resposta != NULL){
        return resposta;
    }

    if(leafSw((arvoreQuadra),aux) == 1)
        resposta = catac_quadra(arqTxt, x,y,r, getSw(arvoreQuadra,aux), arvoreQuadra, removerQuadra);

    if(resposta != NULL){
        return resposta;
    }

    return NULL;

}

void* catac_hidrante(FILE *arqTxt, double x, double y, double r, PosicNo aux, Tree arvoreHidrante, Lista removerHidrante){
    Hidrante hidrante;
    hidrante = getElement(arvoreHidrante, aux);
    Point p = createPoint(getXHid(hidrante), getYHid(hidrante));
    if(verificacao_ponto_circulo(x, y, r, p)){
        insert(removerHidrante, hidrante, "h");
        fprintf(arqTxt, "\t-Hidrante removido: %s\n", getIDHid(hidrante));
    }
    freePoint(p);

    ItemNode resposta = NULL;

    if(leafNe(arvoreHidrante,aux) == 1)
        resposta = catac_hidrante(arqTxt, x, y, r, getNe(arvoreHidrante,aux), arvoreHidrante, removerHidrante);

    if(resposta != NULL){
        return resposta;
    }

    if(leafNw((arvoreHidrante),aux) == 1)
        resposta = catac_hidrante(arqTxt, x, y, r, getNw(arvoreHidrante,aux), arvoreHidrante, removerHidrante);

    if(resposta != NULL){
        return resposta;
    }

    if(leafSe((arvoreHidrante),aux) == 1)
        resposta = catac_hidrante(arqTxt, x, y,r, getSe(arvoreHidrante,aux), arvoreHidrante, removerHidrante);

    if(resposta != NULL){
        return resposta;
    }

    if(leafSw((arvoreHidrante),aux) == 1)
        resposta = catac_hidrante(arqTxt, x,y,r, getSw(arvoreHidrante,aux), arvoreHidrante, removerHidrante);

    if(resposta != NULL){
        return resposta;
    }

    return NULL;
}

void* catac_semaforo(FILE *arqTxt, double x, double y, double r, PosicNo aux, Tree arvoreSemaforo, Lista removerSemaforo){
    Semaforo semaforo;
    semaforo = getElement(arvoreSemaforo, aux);
    Point p = createPoint(getXSema(semaforo), getYSema(semaforo));
    if(verificacao_ponto_circulo(x, y, r, p)){
        insert(removerSemaforo, semaforo, "h");
        fprintf(arqTxt, "\t-semaforo removido: %s\n", getIDSema(semaforo));
    }
    freePoint(p);

    ItemNode resposta = NULL;

    if(leafNe(arvoreSemaforo,aux) == 1)
        resposta = catac_semaforo(arqTxt, x, y, r, getNe(arvoreSemaforo,aux), arvoreSemaforo, removerSemaforo);

    if(resposta != NULL){
        return resposta;
    }

    if(leafNw((arvoreSemaforo),aux) == 1)
        resposta = catac_semaforo(arqTxt, x, y, r, getNw(arvoreSemaforo,aux), arvoreSemaforo, removerSemaforo);

    if(resposta != NULL){
        return resposta;
    }

    if(leafSe((arvoreSemaforo),aux) == 1)
        resposta = catac_semaforo(arqTxt, x, y,r, getSe(arvoreSemaforo,aux), arvoreSemaforo, removerSemaforo);

    if(resposta != NULL){
        return resposta;
    }

    if(leafSw((arvoreSemaforo),aux) == 1)
        resposta = catac_semaforo(arqTxt, x,y,r, getSw(arvoreSemaforo,aux), arvoreSemaforo, removerSemaforo);

    if(resposta != NULL){
        return resposta;
    }

    return NULL;
}

void* catac_radioBase(FILE *arqTxt, double x, double y, double r, PosicNo aux, Tree arvoreRadioBase, Lista removerRadioBase){
    RadioBase radiobase;
    radiobase = getElement(arvoreRadioBase, aux);
    Point p = createPoint(getXRB(radiobase), getYRB(radiobase));
    if(verificacao_ponto_circulo(x, y, r, p)){
        insert(removerRadioBase, radiobase, "h");
        fprintf(arqTxt, "\t-radio-base removido: %s\n", getIDRB(radiobase));
    }
    freePoint(p);

    ItemNode resposta = NULL;

    if(leafNe(arvoreRadioBase,aux) == 1)
        resposta = catac_radioBase(arqTxt, x, y, r, getNe(arvoreRadioBase,aux), arvoreRadioBase, removerRadioBase);

    if(resposta != NULL){
        return resposta;
    }

    if(leafNw((arvoreRadioBase),aux) == 1)
        resposta = catac_radioBase(arqTxt, x, y, r, getNw(arvoreRadioBase,aux), arvoreRadioBase, removerRadioBase);

    if(resposta != NULL){
        return resposta;
    }

    if(leafSe((arvoreRadioBase),aux) == 1)
        resposta = catac_radioBase(arqTxt, x, y,r, getSe(arvoreRadioBase,aux), arvoreRadioBase, removerRadioBase);

    if(resposta != NULL){
        return resposta;
    }

    if(leafSw((arvoreRadioBase),aux) == 1)
        resposta = catac_radioBase(arqTxt, x,y,r, getSw(arvoreRadioBase,aux), arvoreRadioBase, removerRadioBase);

    if(resposta != NULL){
        return resposta;
    }

    return NULL;
}

void catac_morador(FILE *aqrTxt, double x, double y, double r, HashTable moradores, Lista removerMorador, FILE *arqSvg){
    for(int i = 0; i < getHashTableSize(moradores); i++){
        ListNode node = getHashNode(moradores, i);
        while(node != NULL){
            Moradores morador = getHashNodeElement(node);
            Point p  = createPoint(getMoradoresX(morador), getMoradoresY(morador));
            Pessoa pessoa = getMoradoresPessoa(morador);
        
                if(verificacao_ponto_circulo(x, y, r, p)){
                    Pessoa pessoa = getMoradoresPessoa(morador);
                    insert(removerMorador, morador, "morador");
                    //svg_imprimir_circulo(arqSvg, getMoradoresX(morador), getMoradoresY(morador), 2.5, "white", "red");
                    fprintf (aqrTxt, "Morador excluido:%s %s:\n\tCPF: %s\n\tSexo: %s\n\tNascimento: %s\n\tCEP: %s, Face: %s, Número: %d, Complemento: %s\n", getPessoaName(pessoa), getPessoaLastName(pessoa), getPessoaCpf(pessoa), getPessoaSexo(pessoa), getPessoaNascimento(pessoa), getMoradoresCep(morador), getMoradoresFace(morador), getMoradoresNum(morador), getMoradoresCompl(morador));
                }
                freePoint(p);
            node = getHashNodeNext(node);
        }
    }
}

void catac_comercio(FILE *aqrTxt, double x, double y, double r, HashTable comercios, Lista removerComercio, FILE *arqSvg){
    for(int i = 0; i < getHashTableSize(comercios); i++){
        ListNode node = getHashNode(comercios, i);
        while(node != NULL){
            Comercio store = getHashNodeElement(node);
            Pessoa owner = getComercioOwner(store);
            TipoComercio sType = getComercioType(store);
            Point p  = createPoint(getComercioX(store), getComercioY(store));
                if(verificacao_ponto_circulo(x, y, r, p)){
                    insert(removerComercio, store, "comercio");
                    //svg_imprimir_circulo(arqSvg, getComercioX(store), getComercioY(store), 2.5, "yellow", "blue");
                    fprintf(aqrTxt, "Comercio excluido:-%s:\n\tCNPJ: %s\n\tTipo: %s\n\tProprietário: %s %s\n\tCPF: %s\n\tCEP: %s, Face: %s, Número: %d\n\n", getComercioName(store), getComercioCnpj(store), getTipoComercioCodt(sType),getPessoaName(owner), getPessoaLastName(owner), getPessoaCpf(owner), getComercioCep(store), getComercioFace(store), getComercioNum(store));
                }
                freePoint(p);
            node = getHashNodeNext(node);
        }
    }
}

void consulta_catac(FILE *arqTxt, FILE *arqSvg, double x, double y, double r, Tree arvoreQuadra, Tree arvoreHidrante, Tree arvoreSemaforo, Tree arvoreRadioBase, HashTable moradores, HashTable comercios){
    fprintf(arqTxt, "Catac %lf %lf %lf\n", x, y, r);
    svg_imprimir_circulo_transparente(arqSvg, x, y, r, "#6C6753", "#CCFF00");

    Lista removerQuadra = create();
    catac_quadra(arqTxt, x, y, r, getFirstElementTree(arvoreQuadra), arvoreQuadra, removerQuadra);
    catac_quadra_remover(removerQuadra, arvoreQuadra);
    //freeMem(removerQuadra, freeQuadra);

    Lista removerHidrante = create();
    catac_hidrante(arqTxt, x, y, r, getFirstElementTree(arvoreHidrante), arvoreHidrante, removerHidrante);
    catac_hidrante_remover(removerHidrante, arvoreHidrante);
    //freeMem(removerHidrante, freeHidrante);

    Lista removerSemaforo = create();
    catac_semaforo(arqTxt, x, y, r, getFirstElementTree(arvoreSemaforo), arvoreSemaforo, removerSemaforo);
    catac_semaforo_remover(removerSemaforo, arvoreSemaforo);
    //freeMem(removerSemaforo, freeSemaforo);

    Lista removerRadioBase = create();
    catac_radioBase(arqTxt, x, y, r, getFirstElementTree(arvoreRadioBase), arvoreRadioBase, removerRadioBase);
    catac_radioBase_remover(removerRadioBase, arvoreRadioBase);
    //freeMem(removerRadioBase, freeRadioBase);

    Lista removerMorador = create();
    catac_morador(arqTxt, x, y, r, moradores, removerMorador, arqSvg);
    catac_morador_remover(removerMorador, moradores);
    //freeMem(removerMorador, destroiMoradores);

    Lista removerComercio = create();
    catac_comercio(arqTxt, x, y, r, comercios, removerComercio, arqSvg);
    catac_comercio_remover(removerComercio, comercios);
    //freeMem(removerComercio, destroiComercio);
}