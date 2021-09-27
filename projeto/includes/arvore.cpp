#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>

arvoregenes criaArvore(){
    arvoregenes arv;
    arv = (arvoregenes) malloc(sizeof(nodo));
    arv->pai = NULL;
    arv->filhodireito = NULL;
    arv->filhoesquerdo = NULL; 
    arv->chave = NULL; 
    return arv;
}


void insiraNodo(arvoregenes nodo){
    arvoregenes filho; 
    filho = criaArvore();
    if (nodo->filhodireito == NULL){
        nodo->filhodireito = filho;
    } else if (nodo->filhoesquerdo == NULL){
        nodo->filhoesquerdo = filho; 
    } else {
        printf("A árvore já está cheia");
        return; 
    }
    filho->pai = nodo;
}

