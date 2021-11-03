#include "includes/arvore.h"
#include "includes/problema.h"
#include "includes/funcoes.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>

#define POPMAX 1000
#define DEPTH_I 10
#define GEN_MAX 100


using namespace std;
Funcoes f;
int prof = DEPTH_I; 

struct fout 
{
	float desperdicio; 
	int demandas_atendidas;
	int capacidades_mantidas;
	bool solucao_valida;   
};

fout melhor_resultado = {1000,0,0,true};
int problema_resolvido = 0; 

arvoregenes melhor_individuo;

//gerações
int geracoes = 0;
fout fitness(arvoregenes individuo);
void limparPopulacao(vector<arvoregenes>& pop);

void printarResultado(fout resultado){
	cout << "Capacidades mantidas: " << resultado.capacidades_mantidas << "\n";
	cout << "Demandas atendidas: " << resultado.demandas_atendidas << "\n";
	cout << "Desperdício: " << resultado.desperdicio << "\n";
}


//Reproduz os genes da população seguinte 
arvoregenes reproducao(arvoregenes programa){
	//simplesmente copia a árvore 
	arvoregenes novo_individuo = copiaArvore(programa);
	return novo_individuo;
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

//Essa função faz com que a subárvore alvo herde os atributos do gene transferido
void herdarGenes(arvoregenes * genes, arvoregenes heranca){
	//aloca o tamanho da nova chave na memória 
	char * nova_chave; 
	nova_chave = (char *) malloc(strlen(heranca->chave)+1);
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
void crossover(arvoregenes pai, arvoregenes mae, arvoregenes * prole_1, arvoregenes * prole_2){
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
	*prole_1 = genes_pai; *prole_2 = genes_mae;

}

void atualizarParametros(fout novos_parametros, fout *parametros){
	if (novos_parametros.capacidades_mantidas > (*parametros).capacidades_mantidas){
		(*parametros).capacidades_mantidas = novos_parametros.capacidades_mantidas;
	} 

	if (novos_parametros.demandas_atendidas > (*parametros).demandas_atendidas){
		(*parametros).demandas_atendidas = novos_parametros.demandas_atendidas;
	} 

	if (novos_parametros.desperdicio < (*parametros).desperdicio){
		(*parametros).desperdicio = novos_parametros.desperdicio;
	} 
}

bool solucionado(fout parametros){
	return (parametros.capacidades_mantidas >= MAX_DEMANDA && parametros.demandas_atendidas >= MAX_DEMANDA && parametros.desperdicio >= 0);
}

void PG(vector<arvoregenes>& individuos){
	//  //Parâmetros de GP
	//  vector<arvoregenes> nova_geracao; 
	//  arvoregenes prole; 

	//  float mutacao_prob = 0.04;
	//  float crossover_prob = 0.7;
	//  float reproducao_prob = 1 - (crossover_prob + mutacao_prob);

	//  float rolls = randomFloat(0, 1);

	//  for (int i=0; i<individuos.size(); i++){

	// 	fout resultado = fitness(individuos[i]);
		

	// 	if(resultado.capacidades_mantidas >= melhor_resultado.capacidades_mantidas || resultado.demandas_atendidas >= melhor_resultado.demandas_atendidas || (resultado.desperdicio <= melhor_resultado.desperdicio && resultado.desperdicio >= 0)){
	// 		atualizarParametros(resultado, &melhor_resultado);
	// 		if (solucionado(resultado)){
	// 			problema_resolvido += 1; 
	// 			//melhor_individuo = copiaArvore(individuos[i]);
	// 		}
	// 		//se o indivíduo selecionado parcialmente resolve o problema (ou totalmente), reproduza-o para a geração seguinte 
	// 		nova_geracao.push_back(copiaArvore(individuos[i]));	
	// 		}
			
	// 	}


	// 	if (nova_geracao.size() > 0 && nova_geracao.size() < POPMAX){

	// 		//começar a procriação 
	// 		//rolls é a probabilidade dos eventos de procriação acontecer
	// 		//rolls <= 0.0x = mutação
	// 		//rolls <= 0.x = crossover 
	// 		//rolls <= 1 - (mutação + crossover) = reprodução normal
	// 		while(nova_geracao.size() < POPMAX){
	// 			int pai_indice = geraNum(0, (nova_geracao.size() -1));
	// 			int mae_indice = geraNum(0, (nova_geracao.size() -1)); 

	// 			if (rolls <= mutacao_prob){
	// 				prole = mutacao(nova_geracao[pai_indice]);
	// 			} else if(rolls <= crossover_prob) {
	// 				//aqui deve ser verificado se há outros indivíduos dentro do vetor da nova geração
	// 				//caso contrário, apenas reproduza o indivíduo para a geração seguinte
	// 				prole = crossover(nova_geracao[pai_indice], nova_geracao[mae_indice]);
	// 			} else {
	// 				//caso nenhuma dessas probabilidades acontecer, reproduza o indivíduo
	// 				prole = copiaArvore(nova_geracao[pai_indice]);
	// 			}
	// 			//insira o indivíduo selecionado para a geração seguinte 
	// 			nova_geracao.push_back(prole);
	// 		}
			
	// 	}
	
	//  limparPopulacao(individuos);
	 
	//  geracoes += 1; 
	//  individuos = nova_geracao;
 }


void gerarCortes(arvoregenes individuo, int *cortes){

	for (int i = 0; i<MAX_L; i++){
		for (int j=0; j<MAX_C; j++){
			saida s = f.eval(individuo, peca, padroes[i][j] * d[j].tamanho);
			cortes[i] = (int)s.numerico; 
		}	
			
	}
}

//a função que vai lidar com o problema em si
//a ideia será fazer o programa gerado pela GP definir o número de cortes em função da largura e demanda definida
fout fitness(arvoregenes individuo){

	//variáveis de decisão
	int cortes[MAX_L]; 
	float cortes_padrao[MAX_DEMANDA];

	//medida de validação
	fout medida = {0,0,0,false}; 
	//calcular os disperdícios 
	float * desp;
	//desp(i) sendo i itens de cada padrão de corte
	desp = desperdicio(padroes, d);
	
	//gerar as variáveis de decisão com base na demanda e largura da peça 
	gerarCortes(individuo, cortes);
	
	//armazena os cortes padrões para cada demanda 
	
	for (int i = 0; i<MAX_DEMANDA; i++){
		cortes_padrao[i] = cortePorPadrao(padroes, i, cortes);
		
		//Primeira restrição, ser um inteiro positivo 
		if (cortes[i] > 0){
			medida.solucao_valida = true; 
		}
		//Segunda restrição, atender a demanda
		if (cortes_padrao[i] >= (d[i].qnt)){
			medida.demandas_atendidas += 1; 
		}
		//Terceira restrição, não ultrapassar o estoque 
		if (cortes_padrao[i] <= (d[i].qnt) + qnt){
			medida.capacidades_mantidas += 1; 
		}
		
	}

	//calcular o total de desperdicio
	
	medida.desperdicio = minimize(desp, cortes);
	free(desp);

	return medida; 
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
		for (int i=0; i<pop.size(); i++)
			//deleta o nodo da memória para evitar memory leak
			apagaNodo(&pop[i]);
		//limpa todos os elementos do vetor
		pop.clear();
	}
}


int main(){
	//população inicial
	vector<arvoregenes> programas = populacaoInicial(POPMAX, DEPTH_I);
	arvoregenes prole_1; 
	arvoregenes prole_2;
	crossover(programas[0], programas[1], &prole_1, &prole_2);
	


	// while (geracoes < GEN_MAX)
	// {
	// 	PG(programas);
	// }
	
	// cout << "Problemas Resolvidos: " << problema_resolvido;
	
	return 0;
}
