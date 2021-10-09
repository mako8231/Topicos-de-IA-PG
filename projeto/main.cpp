#include "includes/arvore.h"
#include <stdio.h>
#include <iostream>
#include "includes/funcoes.h"
#include <vector>
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
void reproducao(){

}


void mutacao(){

}


void crossover(){

}

//a função que vai lidar com o problema em si
//a ideia será fazer o programa gerado pela GP definir o número de cortes em função da largura e demanda definida
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
	int opt;
	bool on = true; 

	while (on)
	{
		cout << "Selecione uma opção\n";
		cout << "1- Gerar população incial\n";
		cout << "2- Testar população\n";
		cout << "3- Treinar População (irá gerar uma nova geração)\n";
		cout << "4- Sair\n";

		cin >> opt;

		switch (opt)
		{
		case 1:
			cout << "\nGerando população inicial...\n";
			break;
		
		case 2:
			cout << "\nListando cada saída do problema da população\n";
			break;
		
		case 3:
			cout << "\nTreinando População\n";
			break;

		case 4:
			cout << "\nSaindo...\n";
			on = false; 
			break;

		default:
			cout << "\nopção incorreta, por favor digite o que está solicitado no menu.\n";
			break;
		}

	}
	 

	return 0;
}
