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
int prof = DEPTH_I; 

struct fout 
{
	float desperdicio; 
	bool demanda_atendida;
	bool capacidade_mantida;
};


//variaveis de decisão 
vector<int> x; //numero de cortes
vector<vector<arvoregenes>> geracoes; 

//gerações
int gens = 100;


//Reproduz os genes da população seguinte 
void reproducao(){
	
}

//Cria uma subárvore aleatória com base no ponto de crossover 
arvoregenes mutacao(arvoregenes programa){
	
	arvoregenes genes;  
	char *chave; 

	//criar a chave 
	chave = (char *) malloc(strlen(programa->chave)+1);
	strcpy(chave, programa->chave);

	//mutante criado 
	arvoregenes mutante; 

	//raiz baseada no pai 
	mutante = criaArvore(chave);
	//gera uma ramificação aleatória
	arvoregenes alteracao = gerarPopulacao(DEPTH_I, alteracao);

	if(geraNum(0, 1) == 0){
		//copia a subarvore esquerda
		genes = copiaArvore(programa->filhoesquerdo);
		mutante->filhoesquerdo = genes; 
		mutante->filhodireito = alteracao;
	} else {
		//copia a subarvore direita 
		genes = copiaArvore(programa->filhodireito);
		mutante->filhodireito = genes; 
		mutante->filhoesquerdo = alteracao; 
	}

	return mutante; 

}


//A função que irá cruzar um indivíduo com outro
arvoregenes crossover(arvoregenes pai, arvoregenes mae){
	char * chave; 
	//genes dos pais 
	arvoregenes pai_genes;
	arvoregenes mae_genes; 
	 //a árvore que será a junção dos pais 
	arvoregenes filho; 
	
	//copia lateralmente as árvores pais 
	pai_genes = copiaArvore(pai->filhodireito);
	mae_genes = copiaArvore (mae->filhoesquerdo);

	//se o pai for apenas um terminal
	
	chave = (char *) malloc(strlen(pai->chave)+1);
	strcpy(chave, pai->chave);
	

	//cria a raiz baseada no pai
	filho = criaArvore(chave);

	//insere os novos nodos nas laterais do filho
	filho->filhodireito = pai_genes;
	filho->filhoesquerdo = mae_genes;

	return filho;

}

//a função que vai lidar com o problema em si
//a ideia será fazer o programa gerado pela GP definir o número de cortes em função da largura e demanda definida
int fitness(vector<vector<arvoregenes>>& geracoes, int index){
	//Se for maior que zero, logo a solução 
	//está aceitavel e será enviada para a próxima geração
	int medida = 0;
	saida s;

	//executar cada programa individualmente e verificar se sua saída corresponde com as condições impostas 
	//à solução do problema 
	for(int i = 0; i<geracoes[index].size(); i++){
		for (int j=0; i<MAX_L; i++){
			float total = processarCortes(geracoes[index][i], j, padroes);
		}
		
	}
}


//cria a população inicial com base em programas aleatórios 
vector<arvoregenes> populacaoInicial(int q, int maxlv){
	//insere as árvores randomicamente geradas de níveis aleatórios (que não passem da profundidade máxima)
	vector<arvoregenes> individuos; 
	for (int i = 0; i<q; i++){
		//individuos[i] = gerarPopulacao(geraNum(maxlv), individuos[i]);
		arvoregenes programa = gerarPopulacao(geraNum(1, maxlv), programa);
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

float processarCortes(arvoregenes programa, int indice, float padroes[MAX_L][MAX_C]){
	float t; 
	
	for (int j=0; j<MAX_C; j++){
		saida s = f.eval(programa, peca, d[j].tamanho);
		t += (padroes[indice][j] * d[indice].tamanho) * (int)s.numerico;
	}

	return t;
}



int main(){
	//população inicial
	vector<arvoregenes> programas = populacaoInicial(POPMAX, DEPTH_I);
	geracoes.push_back(programas);

	for (int i = 0; i<gens; i++){
		fitness(geracoes, i);
	}

	return 0;
}
