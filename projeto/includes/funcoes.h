#ifndef FUNCOES 
#define FUNCOES 

#include "arvore.h"

    //estrutura para processar a saída da leitura do programa
    struct saida
    {
	    float numerico;
	    bool binario; 
    };

#define LOGIC_LINE 2

#define FUNC_LINE 5
#define FUNC_COL 4

#define TERM_LINE 2
    const char logic_set[LOGIC_LINE][3] = {
        ">=",
        "<=",
    };

    const char funcset[FUNC_LINE][FUNC_COL] = {
        "+", 
        "-",
        "/",
        "*",
        "SIN",
        //">=",
        //"<=",
        //"MOD",
        //"OR",
        //"AND"
    };

    const char terminalset[TERM_LINE][TERM_LINE] = {
        "l",
        "d",
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
            float sen(float x1, float x2);
            bool menorique(float x1, float x2);
            bool maiorique(float x1, float x2);
            bool AND(bool x1, bool x2);
            bool OR(bool x1, bool x2);

            //floaterpretador 
            saida eval(arvoregenes programa, float l, float d);
            
            //construtor 
            Funcoes();
            ~Funcoes();
};

int geraNum(int min, int max);
float randomFloat(float min, float max);

#endif