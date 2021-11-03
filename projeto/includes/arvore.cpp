#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "funcoes.h"

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


arvoregenes crossoverPoint(arvoregenes nodo){
    if (nodo != NULL){
        //obtenha os tamanhos das subárvores e da raiz 
        int tam = profundidade(nodo);
        int tamdir = profundidade(nodo->filhodireito);
        int tames = profundidade(nodo->filhoesquerdo);

        if (tamdir == tames == 0){
            return nodo;
        }

        //pegue um tamanho aleatório
        int random = geraNum(1, tam);

        if(random <= tames){
            return crossoverPoint(nodo->filhoesquerdo);
        } else if(random == (tames + 1)){ 
            return nodo; 
        } else {
            return crossoverPoint(nodo->filhodireito);
        }
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
    //preenche uma das entradas de nó, caso já estejam cheios, simplesmente pare a execução e delete o nodo
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

void substituirFolha(arvoregenes *nodo, arvoregenes novo_nodo){
    arvoregenes alvo; 
    if (geraNum(0,1) == 0){
        //esquerda
        alvo = (*nodo)->filhoesquerdo;
    } else { 
        //direita 
        alvo = (*nodo)->filhodireito;
    }

    if (alvo->filhodireito != NULL && alvo->filhoesquerdo != NULL){
        substituirFolha(&alvo, novo_nodo);
    } else {
        apagaNodo(nodo);
        *nodo = copiaArvore(novo_nodo);
    }
}

int profundidade(arvoregenes nodo){
    if (nodo == NULL){
        return 0; 
    } else {
        //percorra para cada subárvore 
        int eProfundidade = profundidade(nodo->filhoesquerdo);
        int dProfundidade = profundidade(nodo->filhodireito);

        if (eProfundidade > dProfundidade){
            return (eProfundidade + 1);
        } else {
            return (dProfundidade + 1);
        }
    }
}

arvoregenes gerarPopulacao(int nivel, arvoregenes individuo){
    //inserção de subárvores (funções)
    if (nivel > 0){
        int n_nivel = nivel -1;
        //cria árvore 
        individuo = criaArvore((char*)funcset[geraNum(0, FUNC_LINE - 1)]);
        
        //insere os filhos aleatoriamente 
        individuo->filhoesquerdo = gerarPopulacao(geraNum(0, n_nivel), individuo->filhoesquerdo);
        individuo->filhodireito = gerarPopulacao(geraNum(0, n_nivel), individuo->filhodireito);
        return individuo; 
    } 
    //inserção de nós folhas (terminais)
    else if (nivel == 0) {
        //criar nodos a partir da lista de terminais 
        //criar uma probabilidade de entrar uma variável constante aleatória ou uma variável do conjunto de terminais 
        if (geraNum(0, 2) == 0){
            //constante aleatória 
            float constante = randomFloat(0, 10);
            char str_cons[14]; 
            gcvt(constante, 5, str_cons);
            individuo = criaArvore(str_cons);

        } else {
            individuo = criaArvore((char*)terminalset[geraNum(0, TERM_LINE - 1)]);
        }
        //insere as folhas
        individuo->filhoesquerdo = gerarPopulacao(nivel - 1, individuo->filhoesquerdo);
        individuo->filhodireito = gerarPopulacao(nivel - 1, individuo->filhodireito);

        return individuo; 
    }

    return individuo; 
}



