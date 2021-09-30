#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

arvoregenes criaArvore(char *chave){
    arvoregenes arv;
    //Aloca a árvore na memória 
    arv = (arvoregenes) malloc(sizeof(nodo));
    //não faça o nodo apontar para nada, por agora
    arv->pai = NULL;
    arv->filhodireito = NULL;
    arv->filhoesquerdo = NULL;
    //arv->chave = chave; 
    arv->chave = (char *) malloc(strlen(chave)+1);
    strcpy(arv->chave, chave);
    return arv;
}

arvoregenes copiaArvore(arvoregenes nodo){
    arvoregenes cp; 
    if (nodo != NULL){
        char *nome; 
        //aloca a string e a insere 
        nome = (char *) malloc(strlen(nodo->chave)+1);
        strcpy(nome, nodo->chave);
        cp = criaArvore(nome);
        //insere nas subárvores recursivamente 
        cp->filhoesquerdo = copiaArvore(nodo->filhoesquerdo);
        cp->filhodireito = copiaArvore(nodo->filhodireito);
        return cp; 
    } else {
        return NULL; 
    }
}

void preordem(arvoregenes nodo){
    //ordem de exibição: (R, E, D)
    if (nodo != NULL){
        printf("%s ", nodo->chave);
        preordem(nodo->filhoesquerdo);
        preordem(nodo->filhodireito);
    }
}

void ordem(arvoregenes nodo){
    //ordem de exibição: (E, R, D)
    if (nodo != NULL){
        ordem(nodo->filhoesquerdo);
        printf("%s ", nodo->chave);
        ordem(nodo->filhodireito);
    }
}

void posordem(arvoregenes nodo){
    //ordem de exibição: (E, D, R)
    if (nodo != NULL){
        posordem(nodo->filhoesquerdo);
        posordem(nodo->filhodireito);
        printf("%s ", nodo->chave);
    }
}

void insiraNodo(arvoregenes *alvo,  char *chave){
    arvoregenes filho; 
    filho = criaArvore(chave);
    //preenche uma das entradas de nó, caso já estejam cheios, simplismente pare a execução e delete o nodo
    if (*alvo == NULL){
        *alvo = filho; 
    } else {
        cout << "\nJá existe."; 
        //apaga o filho que não vai ser usado e libera a memória 
        apagaNodo(&filho);
    }
}

//garbage collector 
void apagaNodo(arvoregenes *nodo){
    if (*nodo != NULL){
        apagaNodo(&(*nodo)->filhodireito);
        apagaNodo(&(*nodo)->filhoesquerdo);
        //libera a memória 
        free(*nodo);
        *nodo = NULL; 
    }
}

