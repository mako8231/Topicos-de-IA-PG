#include "problema.h"
#include <stdlib.h>

//socorro
#include <iostream>

using namespace std; 

//pega um vetor de n elementos e soma todos eles 
float minimize(float *desperdicio, int *x){
    //variavel do total
    float total = 0; 

    //Percorre todos os elementos 
    for(int i = 0; i<MAX_L; i++){
        total += desperdicio[i] * x[i]; 
    }    

    
    return total; 
}

float * desperdicio(float p[MAX_L][MAX_C], demanda d[MAX_DEMANDA]){
    float * desp; 
    desp = (float *) malloc(sizeof(float) * MAX_L);

    for (int i = 0; i<MAX_L; i++){
        desp[i] = 0;
        float corteTotal = 0;  
        for(int j=0; j<MAX_C; j++){
            corteTotal += padroes[i][j] * d[j].tamanho;
        }
        desp[i] = peca - corteTotal;
    } 


    return desp; 
}

float tamanhoPorPadrao(int padraoi){
    float tam = 0; 

    //percorre pela matriz de padrões
    for(int j = 0; j<MAX_C; j++){
        tam += padroes[padraoi][j] * d[j].tamanho; 
    }

    return tam; 
}

float cortePorPadrao(float padroes[MAX_L][MAX_C], int demanda, int cortes[MAX_L]){
    float total = 0; 
    for (int i=0; i<MAX_L; i++){
        total += padroes[i][demanda] * cortes[i];
    }

    return total; 
}


