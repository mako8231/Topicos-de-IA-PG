#ifndef FUNCOES 
#define FUNCOES 

#include "arvore.h"

    //estrutura para processar a saída da leitura do programa
    struct saida
    {
	    double numerico;
	    bool binario; 
    };

#define LOGIC_LINE 2

#define FUNC_LINE 6
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
        ">=",
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
            double l; //isso pode ser a largura 
            double d; //e essa variavel a demanda dos itens 

            //funcoes
            double soma(double x1, double x2);
            double subtracao(double x1, double x2);
            double multiplicacao(double x1, double x2);
            double divisao(double x1, double x2);
            double resto(double x1, double x2);
            double sen(double x1, double x2);
            bool menorique(double x1, double x2);
            bool maiorique(double x1, double x2);
            bool AND(bool x1, bool x2);
            bool OR(bool x1, bool x2);

            //doubleerpretador 
            saida eval(arvoregenes programa, double l, double d);
            
            //construtor 
            Funcoes();
            ~Funcoes();
};

int geraNum(int min, int max);
double randomdouble(double min, double max);

#endif