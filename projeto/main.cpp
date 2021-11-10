#include "includes/arvore.h"
#include "includes/funcoes.h"
#include "includes/instancia.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>

#define POPMAX 1000
#define DEPTH_I 4
#define GEN_MAX 100

using namespace std;
Funcoes f;
int prof = DEPTH_I;

//gerações
int geracoes = 0;

//funções prototipadas
void fitness(arvoregenes individuo, double *nota, double *fitness_demanda, double *fitness_desp, vector<Instancia> problemas);
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

void PG(vector<arvoregenes> &individuos, vector<Instancia> problemas, double * melhor_fo)
{
	//variaveis de fitness
	double fitness_demanda = 0; 
	double fitness_desp = 0;
	double nota = 0; 

	//novo vetor de geração
	vector<arvoregenes> nova_geracao; 

	//melhor fo

	double prob_crossover = 0.4;
	double prob_mutacao = 0.1; 

	double val = randomdouble(0, 1); 

	//itera pelo vetor de indivíduos 
	for (int i = 0; i<individuos.size(); i++){
		//avalia o indivíduo
		fitness(individuos[i], &nota, &fitness_demanda, &fitness_desp, problemas);
		
		//fo é a nota final do fitness 
		double fo = fitness_demanda - fitness_desp; 

		//se é um indivíduo bom
		if (*melhor_fo < fo){
			*melhor_fo = fo; 
			//seleciona o indivíduo e copia para a nova geração
			nova_geracao.push_back(copiaArvore(individuos[i]));
			ordem(individuos[i]);
			cout << "\n";
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
void fitness(arvoregenes individuo, double *nota, double *fitness_demanda, double *fitness_desp, vector<Instancia> problemas)
{

	//testa o indivíduo para todas as instâncias
	for (int pr = 0; pr < problemas.size(); pr++)
	{
		//variáveis de decisão
		Instancia problema = problemas[pr];
		int *cortes;
		//variáveis de demanda
		//demandas totais (em quantidade)
		double max_demandas = problema.demandas.size();

		//demandas atendidas
		double demandas_atendidas = 0; 
		//criar o vetor de cortes
		cortes = problema.inicializarCortes();

		//calcular os desperdícios
		double *desp;
		double total_desperdicios = 0;
		//desp(i) sendo i itens de cada padrão de corte
		desp = problema.desperdicio(&total_desperdicios);

		//variaveis de notas
		double media_demanda = 0;
		double media_cortes = 0;

		//para cada padrão de corte testar o programa
		for (int j = 0; j < problema.padroes_corte.size(); j++)
		{
			//essa variável é criada por conta do C não dar um valor 0 para um vetor inicializado
			//assim o resultado não mostra algum número gigante sem lógica alguma ao invés de um simples zero
			for (int i = 0; i < problema.demandas.size(); i++)
			{
				//peças cortadas para cada padrão de corte
				double peca_tam = problema.tamanhoPorPadrao(j);
				//testa o programa com base no tamanho da peça e da demanda
				saida out = f.eval(individuo, peca_tam, (problema.demandas[i].tamanho));
				//se a equação for verdadeira
				//aloca como se fosse um corte para esse padrão
				if (out.binario)
				{	
					cortes[j] += (int)out.numerico;
				}
			}
		}


		//pega o total de desperdício
		double desp_solucao = problema.minimize(desp, cortes); 
		
		//isso contudo, deve ser executado em várias instâncias ou seja, será acumulado valores proporcionais
		//o objetivo é minimizar os desperdícios, então a meta é a porcentagem desses desperdícios sempre serem menores
		*fitness_desp += (desp_solucao / (problema.estmax * problema.largura_peca));
		
		for (int i = 0; i<problema.demandas.size(); i++){
			
			double qnt = 0;
			double total_cortes = 0;
			demandas_atendidas = 0; 
			media_cortes = 0;
			media_demanda = 0;

			for (int j = 0; j<problema.padroes_corte.size(); j++){
				qnt += cortes[j] * (problema.demandas[i].tamanho);	
				total_cortes += cortes[j];
				//primeira condição: se a demanda está sendo atendida
				//verificar se a quantidade produzida das peças de demanda(i) atende ou supera as demandas
			}
			if (qnt >= (problema.demandas[i].qnt * problema.demandas[i].tamanho)){
					demandas_atendidas += 1; 
					media_demanda += 1; 
				} else {
					media_demanda -= 1; 
				}


				//segunda condição: se os cortes estão ultrapassando o estoque
				if (total_cortes > problema.estmax){
					media_cortes -= 1; 
				} else {
					media_cortes += 1; 
				}
				//gera a média das demandas
				media_demanda = media_demanda/problema.demandas.size();
				media_cortes = media_cortes/problema.padroes_corte.size();

				*nota += (media_demanda + media_cortes)/2;
		}

		//calcular o fitness da demanda
		*fitness_demanda += (demandas_atendidas/max_demandas);

		
		// //[DEBUG] printar a solução gerada
	    // for (int i = 0; i < problema.padroes_corte.size(); i++)
		//   {
		//   	cout << cortes[i] << "\n";
		//   }

		//garbage colector 
		free(cortes);
		free(desp);
	}

	*fitness_demanda = *fitness_demanda/problemas.size();
	*fitness_desp = *fitness_desp/problemas.size();
	// cout << *fitness_demanda;
	// cout << "\n";
	//cout << *fitness_desp << "\n";
	// cout << "\n";
	
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
	double nota = 0;
	double demandas = 0;
	double desperdicio = 0;
	double melhor_fo = -100000000000; 

	arvoregenes melhor_individuo;

	vector<Instancia> problemas = trainingSet();
	 
	for (int i = 0; i<GEN_MAX; i++){
		PG(programas, problemas, &melhor_fo);
		cout << melhor_fo << "\n"; 
	}
	

	// cout << "Problemas Resolvidos: " << problema_resolvido;

	return 0;
}
