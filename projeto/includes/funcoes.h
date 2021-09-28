#ifndef FUNCOES 
#define FUNCOES 

#include "arvore.h"

    const char listaFunc[] = {'*', '/', '+', '-', '%'};
    const char listaTerm[] = {'x', 'y', '1','2','3','4','5','6','7','8','9','0'};

    class Funcoes{
        public:
            //terminais
            float x; //isso pode ser a largura 
            float y; //e essa variavel a demanda dos itens 

            //funcoes
            float soma(float x1, float x2);
            float subtracao(float x1, float x2);
            float multiplicacao(float x1, float x2);
            float divisao(float x1, float x2);
            float resto(float x1, float x2);

            //interpretador 
            void lerPrograma(arvoregenes programa);

            //construtor 
            Funcoes();
            ~Funcoes();
};


#endif