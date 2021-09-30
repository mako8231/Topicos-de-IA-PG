#include "funcoes.h"
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <string.h>

using namespace std; 


//construtor
Funcoes::~Funcoes(){}

Funcoes::Funcoes(){
    l = 0;
    d = 0; 
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

//verifica se x1 é menor que x2 
bool Funcoes::menorique(float x1, float x2){
    return x1 <= x2;
}

//verifica se x1 é maior que x2 
bool Funcoes::maiorique(float x1, float x2){
    return x1 >= x2;
}

//verifica se x1 E x2 é uma verdade  
bool Funcoes::AND(bool x1, bool x2){
    return x1 && x2;
}

//verifica se x1 OU x2 é uma verdade 
bool Funcoes::OR(bool x1, bool x2){
    return x1 || x2;
}

//Carrega e valida as expressões na árvore 
saida Funcoes::eval(arvoregenes programa){
    saida s; 
    s.binario = false; 
    s.numerico = 0;
    //se for uma árvore vazia, apenas retorne zero
    if (!programa){
        return s; 
    }

    //depois, verifica se os nós são folhas da árvore 
    //pois são as folhas da árvore que são os números, e variáveis, em outras palavras, terminais
    if (!programa->filhodireito && !programa->filhoesquerdo){
        s.numerico = atof(programa->chave);
    }

    //lendo a subárvore da esquerda 
    saida valor_e = eval(programa->filhoesquerdo);

    //lendo a subárvore da direita 
    saida valor_d = eval(programa->filhodireito);

    if (strcmp(programa->chave, "+") == 0)
        s.numerico = (valor_e.numerico, valor_d.numerico);
    
    else if (strcmp(programa->chave, "-") == 0)
        s.numerico = subtracao(valor_e.numerico, valor_d.numerico);
    
    else if (strcmp(programa->chave, "*") == 0)
        s.numerico = multiplicacao(valor_e.numerico, valor_d.numerico);

    else if (strcmp(programa->chave, "/") == 0)
        s.numerico = divisao(valor_e.numerico, valor_d.numerico);

    else if (strcmp(programa->chave, "MOD") == 0)
        s.numerico = resto(valor_e.numerico, valor_d.numerico);

    else if (strcmp(programa->chave, ">=") == 0)
        s.binario = maiorique(valor_e.numerico, valor_d.numerico);

    else if (strcmp(programa->chave, "<=") == 0)
        s.binario = menorique(valor_e.numerico, valor_d.numerico);

    else if (strcmp(programa->chave, "AND") == 0)
        s.binario = AND(valor_e.binario, valor_d.binario);
    
    else if (strcmp(programa->chave, "OR") == 0)
        s.binario = OR(valor_e.binario, valor_d.binario);

    return s; 

    /**
    É possível agora fazer essa função retornar dois valores consecutivos. 
    Usando o registro Saída
    
    saida registro:
        real numerico,
        logico binario
    fim_registro
     **/
}
