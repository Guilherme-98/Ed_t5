#include"comercio_qry.h"

void consulta_de(char cnpj[], HashTable comercios, FILE* arq){
    Comercio comercio;
    TipoComercio tipocomercio;
    Pessoa dono;

    bool found = false;
    for(int i = 0; i < getHashTableSize(comercios); i++){
        ListNode node = getHashNode(comercios, i);
        while(node != NULL){
            comercio = getHashNodeElement(node);

            if(!strcmp(cnpj, getComercioCnpj(comercio))){
                found = true;
                break;
            }
            node = getHashNodeNext(node);  
        }

        if(found) break;
    }
    tipocomercio = getComercioType(comercio);
    dono = getComercioOwner(comercio);


    fprintf(arq, "-%s:\n\tCODT: %s\n\tDescrição: %s\n\tCNPJ: %s\n\tCEP: %s, Face: %s, Numero: %d\n\tNome do proprietário: %s %s, CPF: %s\n", getComercioName(comercio), getTipoComercioCodt(tipocomercio), getTipoComercioDesc(tipocomercio), getComercioCnpj(comercio), getComercioCep(comercio), getComercioFace(comercio), getComercioNum(comercio), getPessoaName(dono), getPessoaLastName(dono), getPessoaCpf (dono));

}
