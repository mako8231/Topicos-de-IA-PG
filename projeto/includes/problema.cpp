#include "problema.h"


//pega um vetor de n elementos e soma todos eles 
float minimize(float *elementos, int *x){
    //variavel do total
    float total = 0; 

    //Percorre todos os elementos 
    for(int i = 0; i<MAX_C; i++){
        total += elementos[i] * x[i]; 
    }

    return total; 
}


