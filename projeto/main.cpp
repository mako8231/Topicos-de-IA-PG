#include "includes/arvore.h"
#include <stdio.h>
#include <iostream>
#include "includes/problema.h"
#include "includes/funcoes.h"
#include <vector>

#define POPMAX 80
#define DEPTH_I 3

using namespace std;
Funcoes f;

//variaveis de decisão 
vector<int> x; //numero de cortes



//Reproduz os genes da população seguinte 
void reproducao(){

}

//Cria uma subárvore aleatória com base no ponto de crossover 
void mutacao(){

}

//A função que irá cruzar um indivíduo com outro
void crossover(){

}

arvoregenes pontoCrossover(arvoregenes programa){
	//50% de chance para o programa ir recursivamente em um dos lados
	arvoregenes ponto;
	arvoregenes alvo; 
	ponto = programa;
	if (geraNum(1) == 0){
		//vai pra esquerda 
		alvo = programa->filhoesquerdo;
	} else {
		//vai para a direita 
		alvo = programa->filhodireito;
	}

	if(alvo == NULL){
		cout << "Não chegamos a fundo";
		return ponto; 
	} else { 
		if (alvo->filhodireito == NULL || alvo->filhoesquerdo == NULL){
			//se uma dessas condições for verdade, estamos pertos dos nós terminais
			cout << "Entramos nos filhos"; 
			return ponto;
		} else {
			pontoCrossover(alvo);
		}
	}
	
}

//a função que vai lidar com o problema em si
//a ideia será fazer o programa gerado pela GP definir o número de cortes em função da largura e demanda definida
void fitness(){
	
}


//cria a população inicial com base em programas aleatórios 
vector<arvoregenes> populacaoInicial(int q, int maxlv){
	//insere as árvores randomicamente geradas de níveis aleatórios (que não passem da profundidade máxima)
	vector<arvoregenes> individuos; 
	for (int i = 0; i<q; i++){
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

float executarPrograma(arvoregenes programa, int indice, float padroes[MAX_L][MAX_C]){
	float t; 
	
	for (int j=0; j<MAX_C; j++){
		saida s = f.eval(programa, peca, d[j].tamanho);
		t += (padroes[indice][j] * d[indice].tamanho) * s.numerico;
	}

	return t;
}



int main(){
	vector<arvoregenes> programas = populacaoInicial(POPMAX, DEPTH_I);
	//if (executarPrograma(programas[0], 0, padroes) >= (d[0].tamanho * d[0].qnt) && (executarPrograma(programas[0], 0, padroes) <= (d[0].tamanho * d[0].qnt) + qnt)){
	//	cout << "yeah";
	//}
	ordem(programas[0]);
	arvoregenes p = pontoCrossover(programas[0]);
	cout << "\n";
	ordem(p);

	return 0;
}
