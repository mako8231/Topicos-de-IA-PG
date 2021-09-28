#include "funcoes.h"
#include "stack.h"
#include <stdlib.h>

//Pilha responsável por guardar a expressão do programa
Stack pilha;

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

}

void empilharexpressao(arvoregenes programa){
    //exibição em pos ordem  
    if (programa != NULL){
        empilharexpressao(programa->filhoesquerdo);
        pilha.empilhar(programa->chave);
        empilharexpressao(programa->filhodireito);
    }
}