#include "includes/arvore.h"
#include <stdio.h>
#include <iostream>
#include "includes/funcoes.h"
#include <vector>
#include <time.h>
#include <cmath>
#include <random>

using namespace std;
Funcoes f;

struct demanda
{
	float largura;
	int quantidade;
}; 

struct peca
{
	float largura; 
	int estoque; 
};


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

//somatório(desp[i] * x[i]), sendo x o número de cortes
int min(){
	return 0;
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

//retorna uma struct de demanda, útil para passagem de parâmetros 
demanda novaDemanda(float l, int qnt){
	demanda nova = {l, qnt};
	return nova;
}

//recebe o valor recomendável das demandas 
float estoqueRecomendavel(vector<demanda> d, int larguraTotal){
	int total = 0; 
	for (int i = 0; i<d.size(); i++){
		total += d[i].largura * d[i].quantidade;
	}
	return total/larguraTotal;
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
	//definir o tamanho incial da peça 
	peca p;
	p.estoque = 0;
	p.largura = 0;

	//definir as demandas 
	vector<demanda> demandas;
	int qnt_d = 0; 

	//programas para a solução do problema 
	vector<arvoregenes> programas; 


	while (on)
	{
		cout << "Selecione uma opção\n";
		cout << "1- Gerar população incial\n";
		cout << "2- Testar população\n";
		cout << "3- Definir o tamanho da peça\n";
		cout << "4- Gerar demanda\n";
		cout << "5- Listar demandas\n";
		cout << "6- Treinar População (irá gerar uma nova geração)\n";
		cout << "7- Apagar população\n";
		cout << "8- Sair\n";

		cout << "======================================================\n";

		cout << "Programas gerados: " << programas.size() << "\n";
		cout << "Largura da peça: " << p.largura << "\n";
		cout << "Estoque: " << p.estoque << "\n";

		//exibir o estoque recomendável
		if (demandas.size() > 0 && p.largura > 0){
			cout << "Estoque recomendável: " << lround(estoqueRecomendavel(demandas, p.largura)) << "\n";
		}

		cout << "======================================================\n";

		cout << "Quantidade de demandas:" << demandas.size() <<"\n";

		cin >> opt;

		switch (opt)
		{
		//criar uma população de programas 
		case 1:
			if (programas.size() > 0){
				cout << "\nJá existe uma população\n";
				break;		
			}

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
		//Listando cada saída em ordem das árvores
		case 2:
			cout << "\nListando cada saída da população\n";
			if (programas.size() > 0) {
				for (int i = 0; i<programas.size(); i++){
					ordem(programas[i]);
					cout << "\n";
				}
			}
			break;

		//criar a peça 
		case 3:
			cout << "\nInsira a quantidade de estoque\n";
			cin >> p.estoque;
			cout << "\nInsira o tamanho de cada peça\n";
			cin >> p.largura;
			break; 	
		
		case 4:
			cout << "gerando demanda \n";
			//verifica se a peça existe
			if (p.largura > 0){
				float l = (float)randomFloat(p.largura -1);
				int q = geraNum(p.estoque); 
				if (p.largura > 0){
					demandas.push_back(novaDemanda(l, q));
				} else {
					cout << "Demanda de tamanho 0\n";
				}
			} else {
				cout << "Não há tamanho definido ainda\n";
			}

			//reajustar o tamanho de estoques 
			if (p.estoque < estoqueRecomendavel(demandas, p.largura)){
				p.estoque = estoqueRecomendavel(demandas, p.largura) + 1;
			}
			break;
		
		case 5:
			//verifica se há alguma demanda
			if (demandas.size() > 0){
				for (int i = 0; i<demandas.size(); i++){
					cout << "Largura: " << demandas[i].largura << "\n";
					cout << "Quantidade: " << demandas[i].quantidade << "\n";
				}
			} else {
				cout << "Não há demandas\n";
			}
			break;


		//Aonde a PG será aplicada
		case 6:
			cout << "\nTreinando População\n";
			break;

		//Limpar a população da memória 
		case 7: 
			if (programas.size() > 0){
				cout << "\nDeletando a população...\n";
				limparPopulacao(programas);
			} else {
				cout << "\nNão há população\n";
			}
			
			break;
		
		//fechar o programa 
		case 8:
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
