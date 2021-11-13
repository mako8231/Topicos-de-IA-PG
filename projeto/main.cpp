#include "includes/arvore.h"
#include "includes/funcoes.h"
#include "includes/instancia.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

#define POPMAX 2000
#define DEPTH_I 5
#define GEN_MAX 100

using namespace std;
Funcoes f;
int prof = DEPTH_I;

//gerações
int geracoes = 0;

//resultados finais
vector<arvoregenes> melhores_individuos;
vector<vector<vector<int>>> melhor_solucoes; 


//funções prototipadas
void fitness(arvoregenes individuo, double *fitness_demanda, double *fitness_desp, double *fitness_capacidade, vector<vector<int>>& solucao, vector<Instancia> problemas);
void limparPopulacao(vector<arvoregenes> &pop);

//Reproduz os genes da população seguinte
arvoregenes reproducao(arvoregenes programa)
{
	//simplesmente copia a árvore
	arvoregenes novo_individuo = copiaArvore(programa);
	return novo_individuo;
}

//Cria uma subárvore aleatória com base no ponto de crossover
arvoregenes mutacao(arvoregenes programa)
{

	arvoregenes genes;
	char *chave;

	//criar a chave
	chave = (char *)malloc(strlen(programa->chave) + 1);
	strcpy(chave, programa->chave);

	//mutante criado
	arvoregenes mutante;

	//raiz baseada no pai
	mutante = criaArvore(chave);
	//gera uma ramificação aleatória
	arvoregenes alteracao = gerarPopulacao(DEPTH_I, alteracao);

	if (geraNum(0, 1) == 0)
	{
		//copia a subarvore esquerda
		genes = copiaArvore(programa->filhoesquerdo);
		mutante->filhoesquerdo = genes;
		mutante->filhodireito = alteracao;
	}
	else
	{
		//copia a subarvore direita
		genes = copiaArvore(programa->filhodireito);
		mutante->filhodireito = genes;
		mutante->filhoesquerdo = alteracao;
	}

	return mutante;
}

//Essa função faz com que a subárvore alvo herde os atributos do gene transferido
void herdarGenes(arvoregenes *genes, arvoregenes heranca)
{
	//aloca o tamanho da nova chave na memória
	char *nova_chave;
	nova_chave = (char *)malloc(strlen(heranca->chave) + 1);
	//e copia o conteúdo da chave nova.
	strcpy(nova_chave, heranca->chave);

	//apaga os nodos laterais
	apagaNodo((&(*genes)->filhodireito));
	apagaNodo((&(*genes)->filhoesquerdo));
	//insere a nova chave
	free((*genes)->chave);
	(*genes)->chave = nova_chave;
	//e então copia os genes para as subárvores
	(*genes)->filhodireito = copiaArvore(heranca->filhodireito);
	(*genes)->filhoesquerdo = copiaArvore(heranca->filhoesquerdo);
}

//A função que irá cruzar um indivíduo com outro
void crossover(arvoregenes pai, arvoregenes mae, arvoregenes *prole_1, arvoregenes *prole_2)
{
	//copia os genes dos parentes
	arvoregenes genes_pai = copiaArvore(pai);
	arvoregenes genes_mae = copiaArvore(mae);

	//pega os pontos de crossover
	arvoregenes cp_1 = crossoverPoint(genes_pai->filhodireito);
	arvoregenes cp_2 = crossoverPoint(genes_mae->filhoesquerdo);

	//copia as heranças
	arvoregenes heranca_1 = copiaArvore(cp_1);
	arvoregenes heranca_2 = copiaArvore(cp_2);

	//herda os genes
	herdarGenes(&cp_1, heranca_2);
	herdarGenes(&cp_2, heranca_1);

	//libere a memória
	apagaNodo(&heranca_1);
	apagaNodo(&heranca_2);

	*prole_1 = genes_pai;
	*prole_2 = genes_mae;
}

void PG(vector<arvoregenes> &individuos, vector<Instancia> problemas, double * melhor_fo, arvoregenes * melhor_individuo, vector<vector<int>>& melhor_solucao)
{
	

	//novo vetor de geração
	vector<arvoregenes> nova_geracao; 

	//"melhor" fo
	double fo_padrao = -10000;

	double prob_crossover = 0.8;
	double prob_mutacao = 0.1; 

	double val = randomdouble(0, 1); 

	//itera pelo vetor de indivíduos 
	for (int i = 0; i<individuos.size(); i++){
		//variaveis de fitness
		double fitness_demanda = 0; 
		double fitness_desp = 0;
		double fitness_cap = 0;
		

		vector<vector<int>> solucao; 
		//avalia o indivíduo
		fitness(individuos[i], &fitness_demanda, &fitness_desp, &fitness_cap, solucao, problemas);

		
		//fo é a nota final do fitness 
		double fo = ((fitness_demanda * 0.5) + (fitness_cap * 0.5)) - fitness_desp; 
		//cout << fo << "\n";

		//se é um indivíduo bom
		if (fo_padrao < fo){ 
			fo_padrao = fo; 
			individuos[i]->fo = fo; 
			//seleciona o indivíduo e copia para a nova geração
			//seleciona o par de melhores indivíduos
			if (nova_geracao.size() < 2){
				nova_geracao.push_back(copiaArvore(individuos[i]));
			} else {
				//se o vetor já estiver cheio (máx 2), remova o elemento do topo
				nova_geracao.erase(nova_geracao.begin());
				nova_geracao.push_back(copiaArvore(individuos[i]));
			}

			//pega o melhor indivíduo e a melhor solução
			if (melhor_solucao.size() > 0){
				
				//limpar a matriz de soluções
				for (int i = 0; i<melhor_solucao.size(); i++){
					melhor_solucao[i].clear();
				}
				melhor_solucao.clear();

				melhor_solucao = solucao;
				
			} else {
				melhor_solucao = solucao;
			}

			//armazena no relatorio os melhores indivíduos
			if (*melhor_fo < fo){
				//atualiza os parâmetros
				*melhor_fo = fo; 
				melhor_solucoes.push_back(solucao);
				melhores_individuos.push_back(copiaArvore(individuos[i]));
			}		 


			if ((*melhor_individuo) != NULL ){
				apagaNodo(&(*melhor_individuo));
				*melhor_individuo = copiaArvore(individuos[i]);
			} else {
				*melhor_individuo = copiaArvore(individuos[i]);
			}
		}
	}

	for (int i = 0; i<individuos.size(); i++){
		//aplicar as probabilidades definidas
		if (nova_geracao.size() < POPMAX){
			if (val <= prob_crossover){
				//crossover com o melhor indivíduo e um aleatório da geração atual
				arvoregenes prole1, prole2; 
				//se houver um indivíduo bom selecionado:
				if (nova_geracao.size() > 0){
					crossover(nova_geracao[geraNum(0, (nova_geracao.size() -1))], individuos[i], &prole1, &prole2);
				} else {
					//cruza com um outro indivíduo aleatorio
					crossover(individuos[i], individuos[geraNum(0, individuos.size()- 1)], &prole1, &prole2);
				}
				//com a procriação feita, joga no vetor da nova geração
				nova_geracao.push_back(prole1);
				nova_geracao.push_back(prole2);
			} else if (val <= prob_mutacao){
				//mutacao
				arvoregenes mutante = mutacao(individuos[i]);
				nova_geracao.push_back(mutante);
			} else {
				//reproducao
				arvoregenes prole = copiaArvore(individuos[i]);
				nova_geracao.push_back(prole);
		  	}
		} else {
			break;
		}
	}
	
	//limpa a geração original
	limparPopulacao(individuos);
	individuos = nova_geracao;

}

//a função que vai lidar com o problema em si
//a ideia será fazer o programa gerado pela GP definir o número de cortes em função da largura e demanda definida
//fitness(programa, nota, solução, desperdício)
void fitness(arvoregenes individuo, double *fitness_demanda, double *fitness_desp, double *fitness_capacidade, vector<vector<int>>& solucao, vector<Instancia> problemas)
{

	//testa o indivíduo para todas as instâncias
	for (int pr = 0; pr < problemas.size(); pr++){
		//seleciona a instancia atual
		Instancia instancia = problemas[pr];
		//cria o vetor de cortes 
		vector<int> cortes;
		int demandas_max = instancia.demandas.size();
		double total_cortes = 0;

		//demandas atendidas 
		int demandas_atendidas = 0;

		//capacidades mantidas
		int capacidades_mantidas = 0;  

		//calcular os desperdicios 
		double * desp; 
		double total_desp = 0; 
		desp = instancia.desperdicio(&total_desp);

		//calcular a solução 
		for (int i = 0; i<instancia.padroes_corte.size(); i++){
			int total_cortes = 0;
			for(int j = 0; j<instancia.demandas.size(); j++){
				//gera a peça produzida pelo padrão de corte
				double peca_tam = instancia.tamanhoPorPadrao(i);
				
				saida resultado = f.eval(individuo, peca_tam, instancia.demandas[j].qnt * instancia.demandas[i].tamanho);

				//às vezes é gerado um inteiro negativo por conta do real positivo ser grande demais
				int corte_gerado = (int)round(resultado.numerico);
				if (corte_gerado < 0){
					corte_gerado = 10000000; 
				}
					//considerando que é impossível uma solução ter um número de cortes alto demais, deixe normalizado para zero
				total_cortes += corte_gerado; 
				if (total_cortes < 0){
					total_cortes = 10000000; 
				} 
			}		
			//adicionar a quantidade de cortes 
			cortes.push_back(total_cortes);
		}

		//copia a solução para o vetor 
		vector<int> sol; 
		copiarVetor(cortes, sol);
		solucao.push_back(sol);

		double desp_solucao = instancia.minimize(desp, cortes);
		*fitness_desp += desp_solucao/(instancia.largura_peca * instancia.estmax); 

		//iterar pelas demandas 
		for (int i = 0; i<instancia.demandas.size(); i++){
			double qnt = 0; 

			//calcula a peça produzida na demanda i 
			for (int j = 0; j<instancia.padroes_corte.size(); j++){
				qnt += cortes[j] * instancia.demandas[i].tamanho;
			}

			if (qnt >= (instancia.demandas[i].qnt * instancia.demandas[i].tamanho)){
				demandas_atendidas += 1; 
			}
		}

		//iterar pelos cortes
		for (int i = 0; i<instancia.padroes_corte.size(); i++){
			//soma todos os cortes 
			total_cortes += cortes[i];
		}

		if (total_cortes == instancia.estmax){
			capacidades_mantidas += 1; 
		}

		//calcular o fitness da demanda 
		*fitness_demanda += (demandas_atendidas/demandas_max);
		//calcular o fitness dos cortes 
		*fitness_capacidade += capacidades_mantidas; 

	}

	*fitness_capacidade = *fitness_capacidade/problemas.size();
	*fitness_demanda = *fitness_demanda/problemas.size();
	*fitness_desp = *fitness_desp/problemas.size();

	// cout << *fitness_desp << "\n";
	// cout << *fitness_demanda << "\n";
	// cout << *fitness_demanda - *fitness_desp << "\n";
	
}

//cria a população inicial com base em programas aleatórios
vector<arvoregenes> populacaoInicial(int q, int maxlv)
{
	//insere as árvores randomicamente geradas de níveis aleatórios (que não passem da profundidade máxima)
	vector<arvoregenes> individuos;
	for (int i = 0; i < q; i++)
	{
		//individuos[i] = gerarPopulacao(geraNum(maxlv), individuos[i]);
		//a raiz consistirá nos operadores de >= e <=
		arvoregenes programa = criaArvore((char *)logic_set[geraNum(0, LOGIC_LINE - 1)]);
		programa->filhoesquerdo = gerarPopulacao(geraNum(1, maxlv), programa->filhoesquerdo);
		programa->filhodireito = gerarPopulacao(geraNum(1, maxlv), programa->filhodireito);
		individuos.push_back(programa);
	}
	return individuos;
}

//Limpa a população de programas
void limparPopulacao(vector<arvoregenes> &pop)
{
	if (pop.size() > 0)
	{
		for (int i = 0; i < pop.size(); i++)
			//deleta o nodo da memória para evitar memory leak
			apagaNodo(&pop[i]);
		//limpa todos os elementos do vetor
		pop.clear();
	}
}

void printarPopulacao(vector <arvoregenes> pop){
	for (int i = 0; i<pop.size(); i++){
		 ordem(pop[i]);
		 cout << "\n";
	}
}

int main()
{
	//população inicial
	vector<arvoregenes> programas = populacaoInicial(POPMAX, DEPTH_I);
	double demandas = 0;
	double desperdicio = 0;
	double melhor_fo = -100000000000; 

	arvoregenes melhor_individuo = NULL;

	vector<Instancia> problemas = trainingSet();
	vector<vector<int>> melhor_solucao;  


	for (int i = 0; i<GEN_MAX; i++){
		PG(programas, problemas, &melhor_fo, &melhor_individuo, melhor_solucao);
		cout << "Geracao: " << i + 1 << "\n";
		cout << melhor_fo << "\n";
		cout << programas.size() << "\n";
		//ordem(melhor_individuo);
		// cout << melhor_solucao.size() << "\n";
		//printarCortes(melhor_solucao); 
		cout << "\n";
	}

	for (int i=0; i<melhor_solucoes.size(); i++){
		ordem(melhores_individuos[i]);
		cout << "\n";
		printarCortes(melhor_solucoes[i]);
	}
	

	// cout << "Problemas Resolvidos: " << problema_resolvido;

	return 0;
}
