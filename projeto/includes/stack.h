#ifndef STACK
#define STACK 

const int TAM = 1000;

class Stack{
    public:
        int tam; //tamanho 
        char stack[TAM]; 

        void empilhar(char val);
        void desempilhar();
        Stack();
        ~Stack();
};

#endif