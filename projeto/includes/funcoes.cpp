#include "funcoes.h"
#include "stack.h"
#include <stdlib.h>
#include <iostream>

using namespace std; 


//construtor
Funcoes::~Funcoes(){}

Funcoes::Funcoes(){
    x = 0;
    y = 0; 
}


//operação de soma 
float Funcoes::soma(float x1, float x2){
    return x1 + x2;
}

//operação de subtração
float Funcoes::subtracao(float x1, float x2){
    return x1 - x2;
}

//operação de multiplicação
float Funcoes::multiplicacao(float x1, float x2){
    return x1 * x2;
}

//operação de divisão
float Funcoes::divisao(float x1, float x2){
    return x1/x2;
}

//operação de resto
float Funcoes::resto(float x1, float x2){
    return (int)x1 % (int)x2;
}

void Funcoes::lerPrograma(arvoregenes programa){
    //carregar o programa na stack
    Stack pc; //contador de programa, basicamente a stack que vai guardar as expressões
    Stack memoria; 
    empilharexpressao(programa, &pc);

    //estrutura de repetição para ler o programa:
    for (int i=0; i<pc.tam; i++){
        //aqui vai ter uma implementação real assim que eu reformular a árvore
        cout << "oi.";
    }
}


void empilharexpressao(arvoregenes programa, Stack *pilha){
    //exibição em pos ordem  
    if (programa != NULL){
        empilharexpressao(programa->filhoesquerdo, pilha);
        pilha->empilhar(programa->chave);
        empilharexpressao(programa->filhodireito, pilha);
    }
}