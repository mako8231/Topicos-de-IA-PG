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
double Instancia::minimize(double *desperdicio, vector<int> x){
    //variavel do total
    double total = 0; 
    //Percorre todos os elementos 
    for(int i = 0; i<padroes_corte.size(); i++){
        // if(x[i] < 0){
        //     cout << "cortes discrepantes" << x[i] << "\n";
        // }
            
        total += desperdicio[i] * x[i]; 
    }    

    //retorna o desperdício total gerado
    return total; 
}

//cria uma lista de instâncias de problemas 
vector<Instancia> trainingSet(){
    //cria a lista de problemas
    vector<Instancia> problemas; 

    //adicionando o primeiro problema 
    Instancia p1(10, 10);
	
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

    //problema 3 
    Instancia p2(5600, 73);

    p2.adicionarDemanda({1380, 22});
    p2.adicionarDemanda({1520, 25});
    p2.adicionarDemanda({1560, 12});
    p2.adicionarDemanda({1710, 14});
    p2.adicionarDemanda({1820, 18});
    p2.adicionarDemanda({1880, 18});
    p2.adicionarDemanda({1930, 20});
    p2.adicionarDemanda({2000, 10});
    p2.adicionarDemanda({2050, 12});
    p2.adicionarDemanda({2100, 14});
    p2.adicionarDemanda({2140, 16});
    p2.adicionarDemanda({2150, 18});
    p2.adicionarDemanda({2200, 20});

    int padrao3_1[] = {0,    0,    0,     0,    3,    0,    0,    0,    0,    0,    0,    0,    0};
    int padrao3_2[] = {1,    0,    0,     0,    0,    0,    1,    0,    0,    0,    0,    1,    0};
    int padrao3_3[] = {1,    0,    0,     0,    0,    0,    0,    0,    1,    0,    0,    1,    0};
    int padrao3_4[] = {1,    0,    0,     0,    0,    0,    0,    0,    0,    2,    0,    0,    0};
    int padrao3_5[] = {0,    0,    1,     0,    1,    0,    0,    0,    0,    0,    0,    0,    1};
    int padrao3_6[] = {0,    1,    0,     0,    0,    1,    0,    0,    0,    0,    0,    0,    1};
    int padrao3_7[] = {0,    1,    0,     0,    0,    0,    1,    0,    0,    0,    0,    1,    0};
    int padrao3_8[] = {0,    1,    0,     0,    0,    0,    1,    0,    0,    0,    1,    0,    0};
    int padrao3_9[] = {0,    0,    0,     1,    0,    1,    0,    1,    0,    0,    0,    0,    0};
    int padrao3_10[] = {0,    0,    0,     2,    0,    0,    0,    0,    0,    0,    0,    1,    0};

    p2.adicionarPadraoCorte(padrao3_1);
    p2.adicionarPadraoCorte(padrao3_2);
    p2.adicionarPadraoCorte(padrao3_3);
    p2.adicionarPadraoCorte(padrao3_4);
    p2.adicionarPadraoCorte(padrao3_5);
    p2.adicionarPadraoCorte(padrao3_6);
    p2.adicionarPadraoCorte(padrao3_7);
    p2.adicionarPadraoCorte(padrao3_8);
    p2.adicionarPadraoCorte(padrao3_9);
    p2.adicionarPadraoCorte(padrao3_10);

    problemas.push_back(p2);

    //retorna todos os problemas 
    return problemas;

}

//gerar um padrão de corte homogêneo 
void gerarPadraoCorte(Instancia& i){
    for (int item = 0; item < i.demandas.size(); item++){
        //alocar o padrão de corte baseado no tamanho das demandas
        int * padrao;
        padrao = (int *) malloc(i.demandas.size() * sizeof(int));
        for (int j=0; j<i.demandas.size(); j++){
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

//copia os itens de um vetor para outro 
void copiarVetor(vector<int> vetor, vector<int>& destino){
    for (int i = 0; i<vetor.size(); i++){
        //copia o elemento
        destino.push_back(vetor[i]);
    }
}

//imprimir os cortes
void printarCortes(vector<vector<int>> cortes){
    for (int i = 0; i<cortes.size(); i++){
        cout << "===================================" << "\n";
        for (int j=0; j<cortes[i].size(); j++){
            cout << "Problema: " << i + 1 << " Corte do padrão " << j + 1 << ": " << cortes[i][j] << "\n";
        }
        cout << "===================================" << "\n";
    }
}
