#include "includes/arvore.h"
#include <stdio.h>
#include <iostream>
#include "includes/funcoes.h"
#include <vector>
#include <time.h>
#include <random>

using namespace std;
Funcoes f;


//Reproduz os genes da população seguinte 
void reproducao(){

}

//Cria uma subárvore aleatória com base no ponto de crossover 
void mutacao(){

}

//A função que irá cruzar um indivíduo com outro
void crossover(){

}

//a função que vai lidar com o problema em si
//a ideia será fazer o programa gerado pela GP definir o número de cortes em função da largura e demanda definida
void fitness(){

}

float somatorio(vector<float>& numeros){
	float n; 
	for (int i = 0; i<numeros.size(); i++)
		n += numeros[i];
	return n; 
}


float randomFloat(float max){
	std::random_device rd; 
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distr(0, max);
	return distr(eng);
}

//cria a população inicial com base em programas aleatórios 
vector<arvoregenes> populacaoInicial(int qnt, int maxlv){
	//insere as árvores randomicamente geradas de níveis aleatórios (que não passem da profundidade máxima)
	vector<arvoregenes> individuos; 
	for (int i = 0; i<qnt; i++){
		//individuos[i] = gerarPopulacao(geraNum(maxlv), individuos[i]);
		arvoregenes programa = gerarPopulacao(geraNum(maxlv), programa);
		individuos.push_back(programa);
	}
	return individuos;
}

//Limpa a população de programas 
void limparPopulacao(vector<arvoregenes>& pop){
	if (pop.size() > 0){
		for (int i=pop.size(); i>=0; i--)
			//deleta o nodo da memória para evitar memory leak
			apagaNodo(&pop[i]);
		//limpa todos os elementos do vetor
		pop.clear();
	}
}



int main(){
	
	return 0;
}
