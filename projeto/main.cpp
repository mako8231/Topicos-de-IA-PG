#include "includes/arvore.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
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


arvoregenes pegarGene(arvoregenes programa){
	
}


//A função que irá cruzar um indivíduo com outro
arvoregenes crossover(arvoregenes pai, arvoregenes mae){
	char * chave; 
	arvoregenes pai_genes;
	arvoregenes mae_genes; 
	arvoregenes filho; 
	
	pai_genes = copiaArvore(pai->filhodireito);
	mae_genes = copiaArvore (mae->filhoesquerdo);

	//se o pai for apenas um terminal
	if (profundidade(pai) == 1){
		int pos = geraNum(FUNC_LINE - 1);
		chave = (char *) malloc(strlen(funcset[pos]));
		strcpy(chave, funcset[pos]);
	} else {
		chave = (char *) malloc(strlen(pai->chave)+1);
		strcpy(chave, pai->chave);
	}


	filho = criaArvore(chave);

	filho->filhodireito = pai_genes;
	filho->filhoesquerdo = mae_genes;

	return filho;

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
	cout << ":Pai" << "\n";
	ordem(programas[1]);
	cout << ":Mae\n";
	//arvoregenes * p = pontoCrossover(programas[0]);
	arvoregenes p = crossover(programas[0], programas[1]);
	saida s =  f.eval(p, 2, 2);
	cout << (int)s.numerico;

	return 0;
}
