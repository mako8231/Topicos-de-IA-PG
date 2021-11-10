#include "instancia.h"
#include <vector>
#include <iostream>

using namespace std;

Instancia::~Instancia(){}
//inicializando o objeto 
Instancia::Instancia(double largura, int est){
    largura_peca = largura;
    estmax = est; 
}

void Instancia::adicionarDemanda(demanda d){
    //adicionar a demanda 
    demandas.push_back(d);
}

void Instancia::adicionarPadraoCorte(int programacao[]){
    //adicione o padrão de corte ao vetor
    int * p;
    p = (int *)malloc(demandas.size() * sizeof(int));

    for (int i = 0; i<demandas.size(); i++){
        p[i] = programacao[i];
    } 

    padroes_corte.push_back(p);
}

void Instancia::printarDemandas(){
    if (demandas.size() == 0){
        //se não há demandas, não faça nada 
        return;
    } 
    for(int i = 0; i<demandas.size(); i++){
        cout << demandas[i].qnt << " peças de tamanho: " << demandas[i].tamanho << "\n"; 
    }
}

void Instancia::printarPadroesCorte(){
    //percorre o padrão i
    if (demandas.size() == 0 && padroes_corte.size() == 0){
        //se não há nem demandas ou padrões de corte, não faça nada
        return; 
    }
    for(int i = 0; i<padroes_corte.size(); i++){
        //para a demanda j
        for (int j = 0; j<demandas.size(); j++){
            cout << padroes_corte[i][j] << " ";
        }
        cout << "\n";
    }
}

double Instancia::tamanhoPorPadrao(int padraoi){
    double tam = 0; 

    //percorre pela matriz de padrões
    for(int j = 0; j<demandas.size(); j++){
        //calcula o total de peças produzidas pelo padrão i
        tam += padroes_corte[padraoi][j] * demandas[j].tamanho; 
    }

    return tam; 
}

//calcula o desperdício para cada padrão de corte 
double * Instancia::desperdicio(double *total){
    double * desp; 
    desp = (double *) malloc(sizeof(double) * padroes_corte.size());

    for (int i = 0; i<padroes_corte.size(); i++){
        desp[i] = 0;
        double corteTotal = 0;  
        for(int j=0; j<demandas.size(); j++){
            corteTotal += padroes_corte[i][j] * demandas[j].tamanho;        
        }
        //armazena os desperdícios para cada padrão de corte
        desp[i] = largura_peca - corteTotal;
        //e também salva o desperdício máximo 
        *total += desp[i];
    } 
    return desp; 
}

//calcula o desperdício para o modelo de solução proposto
double Instancia::minimize(double *desperdicio, int *x){
    //variavel do total
    double total = 0; 
    //Percorre todos os elementos 
    for(int i = 0; i<padroes_corte.size(); i++){
        total += desperdicio[i] * x[i]; 
    }    

    //retorna o desperdício total gerado
    return total; 
}

int * Instancia::inicializarCortes(){
    //alocar o vetor de cortes na memória
    int * cortes = (int *)malloc(padroes_corte.size() * sizeof(int));

    for (int i = 0; i<padroes_corte.size(); i++){
        cortes[i] = 0;
    }

    return cortes;
}

//cria uma lista de instâncias de problemas 
vector<Instancia> trainingSet(){
    //cria a lista de problemas
    vector<Instancia> problemas; 

    //adicionando o primeiro problema 
    Instancia p1(10, 7);
	
    //adiciona as demandas
	p1.adicionarDemanda({5, 5});
	p1.adicionarDemanda({2.5, 10});
	p1.adicionarDemanda({1.5, 8});

    //adiciona os padrões de corte
	int padrao1[] = {2, 0, 0};
	int padrao2[] = {0, 4, 0};
	int padrao3[] = {1, 2, 0};
	int padrao4[] = {0, 3, 1};
	int padrao5[] = {0, 0, 6};

	p1.adicionarPadraoCorte(padrao1);
	p1.adicionarPadraoCorte(padrao2);
	p1.adicionarPadraoCorte(padrao3);
	p1.adicionarPadraoCorte(padrao4);
	p1.adicionarPadraoCorte(padrao5);

    //põe o problema no vetor 
    problemas.push_back(p1);

    //adicionando o segundo problema
    Instancia p2(10000, 57);

    p2.adicionarDemanda({4964, 3});
    p2.adicionarDemanda({4950, 1});
    p2.adicionarDemanda({4826, 1});
    p2.adicionarDemanda({4816, 1});
    p2.adicionarDemanda({4808, 1});
    p2.adicionarDemanda({4682, 1});
    p2.adicionarDemanda({4663, 4});
    p2.adicionarDemanda({4631, 1});
    p2.adicionarDemanda({4451, 1});
    p2.adicionarDemanda({4387, 2});
    p2.adicionarDemanda({4233, 1});
    p2.adicionarDemanda({4127, 1});
    p2.adicionarDemanda({3992, 2});
    p2.adicionarDemanda({3968, 1});
    p2.adicionarDemanda({3858, 1});
    p2.adicionarDemanda({3698, 2});
    p2.adicionarDemanda({3672, 4});
    p2.adicionarDemanda({3565, 1});
    p2.adicionarDemanda({3387, 3});
    p2.adicionarDemanda({3336, 3});
    p2.adicionarDemanda({3309, 1});
    p2.adicionarDemanda({3118, 3});
    p2.adicionarDemanda({3078, 4});
    p2.adicionarDemanda({2988, 1});
    p2.adicionarDemanda({2870, 1});
    p2.adicionarDemanda({2862, 2});
    p2.adicionarDemanda({2847, 2});
    p2.adicionarDemanda({2735, 2});
    p2.adicionarDemanda({2716, 3}); 
    p2.adicionarDemanda({2652, 1});
    p2.adicionarDemanda({2631, 3});
    p2.adicionarDemanda({2553, 2});
    p2.adicionarDemanda({2496, 3});
    p2.adicionarDemanda({2406, 1});
    p2.adicionarDemanda({2125, 2});
    p2.adicionarDemanda({2017, 1});
    p2.adicionarDemanda({1939, 3});
    p2.adicionarDemanda({1848, 4});
    p2.adicionarDemanda({1832, 1});
    p2.adicionarDemanda({1672, 2});
    p2.adicionarDemanda({1624, 1});
    p2.adicionarDemanda({1593, 1});
    p2.adicionarDemanda({1436, 4});
    p2.adicionarDemanda({1225, 2});
    p2.adicionarDemanda({1212, 3});
    p2.adicionarDemanda({1060, 4});
    p2.adicionarDemanda({943, 2});
    p2.adicionarDemanda({763, 1});
    p2.adicionarDemanda({733, 4});
    p2.adicionarDemanda({583, 1});
    p2.adicionarDemanda({476, 1});
    p2.adicionarDemanda({462, 2});
    p2.adicionarDemanda({278, 3});
    p2.adicionarDemanda({246, 1});
    p2.adicionarDemanda({80, 1});
    p2.adicionarDemanda({74, 2});
    p2.adicionarDemanda({40, 2});

    //gerar padrões de cortes homogêneos
    gerarPadraoCorte(p2);
    problemas.push_back(p2);

    //retorna todos os problemas 
    return problemas;

}

//gerar um padrão de corte homogêneo 
void gerarPadraoCorte(Instancia& i){
    for (int item = 0; item <= i.demandas.size(); item++){
        //alocar o padrão de corte baseado no tamanho das demandas
        int * padrao;
        padrao = (int *) malloc(i.demandas.size() * sizeof(int));
        for (int j=0; j<=i.demandas.size(); j++){
            padrao[j] = 0;
            //inserir os valores homogêneos
            if(j == item){
                //adiciona um valor fixo correspondente a demanda atual
                padrao[j] = 1; 
            }
        }
        i.padroes_corte.push_back(padrao);
    }
}