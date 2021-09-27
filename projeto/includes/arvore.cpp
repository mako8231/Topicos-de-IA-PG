#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

arvoregenes criaArvore(char chave){
    arvoregenes arv;
    //Aloca a árvore na memória 
    arv = (arvoregenes) malloc(sizeof(nodo));
    //não faça o nodo apontar para nada, por agora
    arv->pai = NULL;
    arv->filhodireito = NULL;
    arv->filhoesquerdo = NULL; 
    arv->chave = chave; 
    return arv;
}

void preordem(arvoregenes nodo){
    //ordem de exibição: (R, E, D)
    if (nodo != NULL){
        cout << nodo->chave << " ";
        preordem(nodo->filhoesquerdo);
        preordem(nodo->filhodireito);
    }
}

void ordem(arvoregenes nodo){
    //ordem de exibição: (E, R, D)
    if (nodo != NULL){
        ordem(nodo->filhoesquerdo);
        cout << nodo->chave << " ";
        ordem(nodo->filhodireito);
    }
}

void posordem(arvoregenes nodo){
    //ordem de exibição: (E, D, R)
    if (nodo != NULL){
        posordem(nodo->filhoesquerdo);
        posordem(nodo->filhodireito);
        cout << nodo->chave << " ";
    }
}

void insiraNodo(arvoregenes nodo, char chave){
    arvoregenes filho; 
    filho = criaArvore(chave);
    //preenche uma das entradas de nó, caso já estejam cheios, simplismente pare a execução e delete o nodo
    if (nodo->filhodireito == NULL){
        nodo->filhodireito = filho;
    } else if (nodo->filhoesquerdo == NULL){
        nodo->filhoesquerdo = filho; 
    } else {
        cout << "A árvore já está cheia";
        //apaga o filho que não vai ser usado e libera a memória 
        free(filho);
        return; 
    }
    filho->pai = nodo;
}

void apagaNodo(arvoregenes *nodo){
    if (*nodo != NULL){
        apagaNodo(&(*nodo)->filhodireito);
        apagaNodo(&(*nodo)->filhoesquerdo);
        //libera a memória 
        free(*nodo);
        *nodo = NULL; 
    }
}

