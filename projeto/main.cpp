#include "includes/arvore.h"
#include "includes/problema.h"
#include "includes/funcoes.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>

#define POPMAX 1000
#define DEPTH_I 15



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


//gerações
int geracoes = 0;
fout fitness(arvoregenes individuo);
void limparPopulacao(vector<arvoregenes>& pop);

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

void PG(vector<arvoregenes>& individuos){
	 //Parâmetros de GP
	 vector<arvoregenes> nova_geracao; 
	 arvoregenes individuo_selecionado; 

	 float mutacao_prob = 0.50;
	 float crossover_prob = 0.2;
	 float reproducao_prob = 1 - (crossover_prob + mutacao_prob);

	float rolls = randomFloat(0, 1);

	 //Selecionar os indivíduos com solução válida 
	 for (int i=0; i<individuos.size(); i++){
		 fout resultado = fitness(individuos[i]);

		if(resultado.capacidades_mantidas >= melhor_resultado.capacidades_mantidas || resultado.demandas_atendidas >= melhor_resultado.demandas_atendidas || resultado.desperdicio <= melhor_resultado.desperdicio){
			atualizarParametros(resultado, &melhor_resultado);
			
			
			//rolls é a probabilidade dos eventos de procriação acontecer
			//rolls <= 0.0x = mutação
			//rolls <= 0.x = crossover 
			//rolls <= 1 - (mutação + crossover) = reprodução normal
			if (rolls <= mutacao_prob){
				individuo_selecionado = mutacao(individuos[i]);
			} else if(rolls <= crossover_prob) {
				//aqui deve ser verificado se há outros indivíduos dentro do vetor da nova geração
				//caso contrário, apenas reproduza o indivíduo para a geração seguinte
				if (nova_geracao.size() > 0){
					//seleciona uma mãe aleatoriamente
					arvoregenes mae = nova_geracao[geraNum(0, nova_geracao.size() - 1)];
					individuo_selecionado = crossover(individuos[i], mae);
				} else {
					//apenas inclui o individuo selecionado ao vetor de gerações novas
					individuo_selecionado = copiaArvore(individuos[i]);
				}
			} else {
				//caso nenhuma dessas probabilidades acontecer, reproduza o indivíduo
				individuo_selecionado = copiaArvore(individuos[i]);
			}
			//insira o indivíduo selecionado para a geração seguinte 
			nova_geracao.push_back(individuo_selecionado);
		 }
	 }
	 limparPopulacao(individuos);
	 geracoes += 1; 
	 individuos = nova_geracao;
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
	for (int i = 0; i<MAX_L; i++){
		for (int j=0; j<MAX_C; j++){
			saida s = f.eval(individuo, peca, padroes[i][j] * d[j].tamanho);
			cortes[i] = (int)s.numerico; 
		}	
	}
	
	//armazena os cortes padrões para cada demanda 
	
	for (int i = 0; i<MAX_DEMANDA; i++){
		cortes_padrao[i] = cortePorPadrao(padroes, i, cortes);
		//Primeira restrição, ser um inteiro positivo 
		if (cortes[i] > 0){
			medida.solucao_valida = true; 
		}
		//Segunda restrição, atender a demanda
		if (cortes_padrao[i] >= (d[i].tamanho * d[i].qnt)){
			medida.demandas_atendidas += 1; 
		}
		//Terceira restrição, não ultrapassar o estoque 
		if (cortes_padrao[i] <= (d[i].tamanho * d[i].qnt) + qnt){
			medida.capacidades_mantidas += 1; 
		}
	}

	//calcular o total de desperdicio
	medida.desperdicio = minimize(desp, cortes);

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
		for (int i=pop.size(); i>=0; i--)
			//deleta o nodo da memória para evitar memory leak
			apagaNodo(&pop[i]);
		//limpa todos os elementos do vetor
		pop.clear();
	}
}

int main(){
	//população inicial
	vector<arvoregenes> programas = populacaoInicial(POPMAX, DEPTH_I);
	ordem(programas[0]);
	cout << " " << programas.size();
	cout << "\n";
	PG(programas);
	ordem(programas[0]);
	cout << " " << programas.size();
	PG(programas);
	cout << "\n";
	ordem(programas[0]);
	cout << " " << programas.size();
	cout << "\n";
	PG(programas);
	ordem(programas[0]);
	cout << " " << programas.size();
	cout << "\n";
	PG(programas);
	ordem(programas[0]);
	cout << " " << programas.size();

	cout << "\n";
	cout << melhor_resultado.capacidades_mantidas << "\n";
	cout << melhor_resultado.demandas_atendidas << "\n";
	cout << melhor_resultado.desperdicio << "\n";

	return 0;
}
