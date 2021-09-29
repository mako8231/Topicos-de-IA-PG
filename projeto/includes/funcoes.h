#ifndef FUNCOES 
#define FUNCOES 

#include "arvore.h"

    const char funcset[9][4] = {
        "+", 
        "-",
        "/",
        "*",
        ">=",
        "<=",
        "MOD",
        "OR",
        "AND"
    };

    class Funcoes{
        public:
            //terminais
            float l; //isso pode ser a largura 
            float d; //e essa variavel a demanda dos itens 

            //funcoes
            float soma(float x1, float x2);
            float subtracao(float x1, float x2);
            float multiplicacao(float x1, float x2);
            float divisao(float x1, float x2);
            float resto(float x1, float x2);
            bool menorique(float x1, float x2);
            bool maiorique(float x1, float x2);
            bool AND(bool x1, bool x2);
            bool OR(bool x1, bool x2);
            
            //construtor 
            Funcoes();
            ~Funcoes();
};

#endif