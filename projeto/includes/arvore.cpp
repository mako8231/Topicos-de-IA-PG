#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

arvoregenes criaArvore(char chave){
    arvoregenes arv;
    arv = (arvoregenes) malloc(sizeof(nodo));
    arv->pai = NULL;
    arv->filhodireito = NULL;
    arv->filhoesquerdo = NULL; 
    arv->chave = chave; 
    return arv;
}

void prefixa(arvoregenes nodo){
    if (nodo != NULL){
        cout << nodo->chave << " ";
        prefixa(nodo->filhoesquerdo);
        prefixa(nodo->filhodireito);
    }
}

void insiraNodo(arvoregenes nodo, char chave){
    arvoregenes filho; 
    filho = criaArvore(chave);
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

