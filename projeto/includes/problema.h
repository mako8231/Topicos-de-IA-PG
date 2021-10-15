#ifndef PROBLEMA
#define PROBLEMA

#define MAX_L 5
#define MAX_C 3

    //Estrutura das demandas 
    struct demanda
    {
        float tamanho;
        int qnt;
    };
    
    //tamanho da peça 
    static float peca = 10;
    //quantidade no estoque 
    static int qnt = 7;


    //VARIÁVEIS DE PROBLEMAS 
    //Quantidade de demandas 
    static demanda d[] = {{5, 5}, {2.5, 10}, {1.5, 8}};

    //Quantidade de programações de cortes 
    static float padroes[MAX_L][MAX_C] = {
    //   5  2.5  1.5
        {2,  0,  0}, //0
        {0,  4,  0}, //0
        {0,  0,  6}, //1
        {1,  2,  0}, //0
        {0,  3,  1}, //1
    };

    float minimize(float *elementos, int *x);


#endif