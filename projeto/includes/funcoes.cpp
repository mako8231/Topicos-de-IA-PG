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
int Funcoes::soma(int x1, int x2){
    return x1 + x2;
}

//operação de subtração
int Funcoes::subtracao(int x1, int x2){
    return x1 - x2;
}

//operação de multiplicação
int Funcoes::multiplicacao(int x1, int x2){
    return x1 * x2;
}

//operação de divisão
int Funcoes::divisao(int x1, int x2){
    return x1/x2;
}

//operação de resto
int Funcoes::resto(int x1, int x2){
    return x1 % x2;
}

//verifica se x1 é menor que x2 
bool Funcoes::menorique(int x1, int x2){
    return x1 <= x2;
}

//verifica se x1 é maior que x2 
bool Funcoes::maiorique(int x1, int x2){
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
saida Funcoes::eval(arvoregenes programa, int l, int d){
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
        if (strcmp(programa->chave, "l") == 0){
            s.numerico = l;
        } else if(strcmp(programa->chave, "d") == 0){
            s.numerico = d;
        } else {
            s.numerico = atoi(programa->chave);
        }
    }

    //lendo a subárvore da esquerda 
    saida valor_e = eval(programa->filhoesquerdo, l, d);

    //lendo a subárvore da direita 
    saida valor_d = eval(programa->filhodireito, l, d);

    if (strcmp(programa->chave, "+") == 0)
        s.numerico = soma(valor_e.numerico, valor_d.numerico);
    
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
