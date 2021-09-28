#include "funcoes.h"
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
  
}

