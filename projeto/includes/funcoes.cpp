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
float Funcoes::eval(arvoregenes programa){
    //se for uma árvore vazia, apenas retorne zero
    if (!programa){
        return 0; 
    }

    //depois, verifica se os nós são folhas da árvore 
    //pois são as folhas da árvore que são os números, e variáveis, em outras palavras, terminais
    if (!programa->filhodireito && !programa->filhoesquerdo){
        return atof(programa->chave);
    }

    //lendo a subárvore da esquerda 
    float valor_e = eval(programa->filhoesquerdo);

    //lendo a subárvore da direita 
    float valor_d = eval(programa->filhodireito);

    if (strcmp(programa->chave, "+") == 0){
        return soma(valor_e, valor_d);
    }

    if (strcmp(programa->chave, "-") == 0){
        return subtracao(valor_e, valor_d);
    }

    if (strcmp(programa->chave, "*") == 0){
        return multiplicacao(valor_e, valor_d);
    }

    if (strcmp(programa->chave, "/") == 0){
        return divisao(valor_e, valor_d);
    }

    return 0; 

    /**por enquanto, apenas expressões aritiméticas, já penso numa solução  
     caso for lidar com mais de um tipo de dados, por exemplo, uma bool, uma solução interessante seria
     retornar uma struct que suporte esses dois tipos, por exemplo:

    saida registro:
        real numerico,
        logico binario
    fim_registro

     **/
}
