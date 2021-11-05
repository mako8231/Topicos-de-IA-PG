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

arvoregenes melhor_individuo;

//gerações
int geracoes = 0;

//funções prototipadas
void fitness(arvoregenes individuo, int * nota, int ** solucao, float * w);
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
	
	ordem(cp_1);

	//libere a memória 
	apagaNodo(&heranca_1);
	apagaNodo(&heranca_2);


	*prole_1 = genes_pai; *prole_2 = genes_mae;

}


void PG(vector<arvoregenes>& individuos){
	
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
//fitness(programa, nota, solução, desperdício) 
void fitness(arvoregenes individuo, int * nota, int ** solucao, float * w){

	//variáveis de decisão
	nota = 0; 
	int cortes[MAX_L]; 
	float cortes_padrao[MAX_DEMANDA];
	//calcular os desperdícios 
	float * desp;
	//desp(i) sendo i itens de cada padrão de corte
	desp = desperdicio(padroes, d);
	
	//para cada padrão de corte testar o programa 
	for (int j = 0; j<MAX_L; j++){	
		//essa variável é criada por conta do C não dar um valor 0 para um vetor inicializado
		//assim o resultado não mostra algum número gigante sem lógica alguma ao invés de um simples zero
		int temp_cortes = 0;	
		for (int i = 0; i<MAX_C; i++){ 
			//peças cortadas para cada padrão de corte 
			float peca_tam = tamanhoPorPadrao(i);
			//testa o programa com base no tamanho da peça e da demanda 
			saida out = f.eval(individuo, peca_tam, (d[j].qnt * d[j].tamanho));
			//se a equação for verdadeira
			if (out.binario){
				temp_cortes += 1; 
				cortes[j] = temp_cortes;
			} else {
				cortes[j] = temp_cortes;
			}
		}
	}



	// //[DEBUG] printar a solução gerada
	// for (int i = 0; i<MAX_L; i++){
	// 	cout << cortes[i] << "\n";
	// }
		
}



//cria a população inicial com base em programas aleatórios 
vector<arvoregenes> populacaoInicial(int q, int maxlv){
	//insere as árvores randomicamente geradas de níveis aleatórios (que não passem da profundidade máxima)
	vector<arvoregenes> individuos; 
	for (int i = 0; i<q; i++){
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
	int nota;
	int * solucao;
	float desperdicio; 
	
	fitness(programas[0], &nota, &solucao, &desperdicio);


	// while (geracoes < GEN_MAX)
	// {
	// 	PG(programas);
	// }
	
	// cout << "Problemas Resolvidos: " << problema_resolvido;
	
	return 0;
}
