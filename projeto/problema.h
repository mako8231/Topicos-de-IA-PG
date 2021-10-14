#ifndef PROBLEMA
#define PROBLEMA
    //Estrutura das demandas 
    struct demanda
    {
        float tamanho;
        int qnt;
    };
    
    //tamanho da peça 
    float peca = 10;
    //quantidade no estoque 
    int qnt = 7;


    //VARIÁVEIS DE PROBLEMAS 
    //Quantidade de demandas 
    demanda d[] = {{5, 5}, {2.5, 10}, {1.5, 8}};

    //Quantidade de programações de cortes 
    int cortesProg[5][3] = {
    //   5  2.5  1.5
        {2,  0,  0},
        {0,  4,  0},
        {0,  0,  6},
        {1,  2,  0},
        {0,  3,  1},
    };

#endif