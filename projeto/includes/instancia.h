#ifndef INSTANCIA
#define INSTANCIA 

#include <vector>  

using namespace std; 

//uma instância é o modelo de um problema diferente
//a ideia é armazenar várias instâncias que serão testadas para cada indivíduo
struct demanda
{
    float tamanho;
    float qnt; 
};

class Instancia {
    public: 
        //variaveis de problema
        vector<demanda> demandas;  
        float largura_peca; 
        //estoque máximo de peças 
        float estmax; 
        //vetor de vetores (matrizes) correspondente ao padrão de cortes 
        //ex: 
        /**   
        5  2.5  1.5
        {2,  0,  0}, //0
        {0,  4,  0}, //0
        {0,  0,  6}, //1
        {1,  2,  0}, //0
        {0,  3,  1}, //1
        };**/
        vector<int*> padroes_corte; 
    
        //métodos
        void adicionarPadraoCorte(int programacao[]);
        void adicionarDemanda(demanda d); 
        void printarPadroesCorte();
        void printarDemandas();
        //esses são copias dos métodos do antigo "problema.h"
        float tamanhoPorPadrao(int padraoi);
        float * desperdicio(float *total);
        float minimize(float *desperdicio, int *x);

        //construtor
        Instancia(float largura, int est);
        ~Instancia();

};

vector<Instancia> trainingSet();
void gerarPadraoCorte(Instancia& i);

#endif