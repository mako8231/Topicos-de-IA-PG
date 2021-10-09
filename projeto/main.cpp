#include "includes/arvore.h"
#include <stdio.h>
#include <iostream>
#include "includes/funcoes.h"

#include <time.h>

using namespace std;

struct demanda
{
	int largura;
	int quantidade;
}; 

struct peca
{
	int largura; 
	int estoque; 
};

void crossover(){

}

void fitness(){

}

arvoregenes * populacaoInicial(int qnt, int maxlv){
	//aloca o vetor da população inicial na memória 
	arvoregenes *individuos = (arvoregenes*) malloc(sizeof(arvoregenes) * qnt);
	//insere as árvores randomicamente geradas de níveis aleatórios (que não passem da profundidade máxima)
	for (int i = 0; i<qnt; i++){
		individuos[i] = gerarPopulacao(geraNum(maxlv), individuos[i]);
	}

	return individuos;
}



/** Entradas do problema do corte 
 * estoque_max 
 * largura_da_preça
 * desperdicio[i] sendo i = uma programação de corte diferente
 * demanda[i] 
 * peca
 * **/

arvoregenes individuos[40]; 

int main(){
	saida out; 
	Funcoes f; 
	
	arvoregenes * teste; 
	teste = populacaoInicial(7, 3);
	cout << "\n";

	return 0;
}
