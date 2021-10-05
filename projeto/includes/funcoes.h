#ifndef FUNCOES 
#define FUNCOES 

#include "arvore.h"

    //estrutura para processar a saída da leitura do programa
    struct saida
    {
	    int numerico;
	    bool binario; 
    };

#define FUNC_LINE 9 
#define FUNC_ROW 4

#define TERM_LINE 2

    const char funcset[FUNC_LINE][FUNC_ROW] = {
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

    const char terminalset[TERM_LINE][TERM_LINE] = {
        "l",
        "d"
    };

    class Funcoes{
        public:
            //terminais
            int l; //isso pode ser a largura 
            int d; //e essa variavel a demanda dos itens 

            //funcoes
            int soma(int x1, int x2);
            int subtracao(int x1, int x2);
            int multiplicacao(int x1, int x2);
            int divisao(int x1, int x2);
            int resto(int x1, int x2);
            bool menorique(int x1, int x2);
            bool maiorique(int x1, int x2);
            bool AND(bool x1, bool x2);
            bool OR(bool x1, bool x2);

            //interpretador 
            saida eval(arvoregenes programa, int l, int d);
            
            //construtor 
            Funcoes();
            ~Funcoes();
};

#endif