#include "instancia.h"
#include <vector>
#include <iostream>

using namespace std;

Instancia::~Instancia(){}
//inicializando o objeto 
Instancia::Instancia(float largura, int est){
    largura_peca = largura;
    estmax = est; 
}

void Instancia::adicionarDemanda(demanda d){
    //adicionar a demanda 
    demandas.push_back(d);
}

void Instancia::adicionarPadraoCorte(float programacao[]){
    //adicione o padrão de corte ao vetor
    float * p = programacao; 
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

float Instancia::tamanhoPorPadrao(int padraoi){
    float tam = 0; 

    //percorre pela matriz de padrões
    for(int j = 0; j<demandas.size(); j++){
        //calcula o total de peças produzidas pelo padrão i
        tam += padroes_corte[padraoi][j] * demandas[j].tamanho; 
    }

    return tam; 
}

//calcula o desperdício para cada padrão de corte 
float * Instancia::desperdicio(float *total){
    float * desp; 
    desp = (float *) malloc(sizeof(float) * padroes_corte.size());

    for (int i = 0; i<padroes_corte.size(); i++){
        desp[i] = 0;
        float corteTotal = 0;  
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
float Instancia::minimize(float *desperdicio, int *x){
    //variavel do total
    float total = 0; 

    //Percorre todos os elementos 
    for(int i = 0; i<padroes_corte.size(); i++){
        total += desperdicio[i] * x[i]; 
    }    

    //retorna o desperdício total gerado
    return total; 
}
