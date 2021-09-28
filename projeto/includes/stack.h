#ifndef STACK
#define STACK 

const int TAM = 1000;

class Stack{
    public:
        int tam; //tamanho 
        char stack[TAM]; 

        void empilhar(char val);
        void desempilhar();
        void printar();
        int tamanho();
        Stack();
        ~Stack();
};

#endif