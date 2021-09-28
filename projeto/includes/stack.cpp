#include "stack.h"
#include <iostream>

using namespace std;

Stack::~Stack(){}

Stack::Stack(){
    tam = 0;
}

//insere um valor no topo da stack
void Stack::empilhar(char val){
    if ((tam + 1) < TAM) {
        stack[tam] = val;
        tam += 1;
    } else {
        cout << "Stack overflow";
    }
}

//escreva os valores na stack
void Stack::printar(){
    for(int i = 0; i< tam; i++){
        cout << stack[i];
    }
}

//remove um valor do topo da stack
void Stack::desempilhar(){
    if (tam > 0){
        stack[tam - 1] = ' '; 
        tam -= 1; 
    } else {
        cout << "Stack já está vazio";
    }
}

int Stack::tamanho(){
    return tam; 
}