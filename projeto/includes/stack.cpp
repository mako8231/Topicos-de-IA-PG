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

//remove um valor do topo da stack
void Stack::desempilhar(){
    if (tam > 0){
        stack[tam] = NULL; 
        tam -= 1; 
    } else {
        cout << "Stack já está vazio";
    }
}