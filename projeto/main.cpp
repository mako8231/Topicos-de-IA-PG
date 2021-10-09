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



/** Entradas do problema do corte 
 * estoque_max 
 * largura_da_preça
 * desperdicio[i] sendo i = uma programação de corte diferente
 * demanda[i] 
 * peca
 * **/

int main(){
	int opt;
	bool on = true; 
	//variáveis de entrada
	int niveis, quantidade;
	Funcoes f;
	
	vector<arvoregenes> programas; 

	while (on)
	{
		cout << "Selecione uma opção\n";
		cout << "1- Gerar população incial\n";
		cout << "2- Testar população\n";
		cout << "3- Treinar População (irá gerar uma nova geração)\n";
		cout << "4- Sair\n";

		cout << "======================================================\n";

		cout << "Programas gerados: " << programas.size();

		cin >> opt;

		switch (opt)
		{
		case 1:
			cout << "\nGerando população inicial...\n";
			cout << "\nInsira o número máximo de níveis\n";
			cin >> niveis;
			cout << "\nA quantidade\n";
			cin >> quantidade;
			if (niveis > 0 && quantidade > 0) {
				programas = populacaoInicial(quantidade, niveis);
				cout << "\nforam criados: " << programas.size();
			} else {
				cout << "\nEntrada inválida\n";
			}
			break;
		
		case 2:
			cout << "\nListando cada saída da população\n";
			if (programas.size() > 0) {
				for (int i = 0; i<programas.size(); i++){
					ordem(programas[i]);
					cout << "\n";
				}
			}
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
