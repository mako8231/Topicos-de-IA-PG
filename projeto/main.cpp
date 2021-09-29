#include "includes/arvore.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "includes/funcoes.h"

using namespace std;

void empilharPrograma(arvoregenes programa, vector<char*> pilha){
	
}

int main(){

	arvoregenes teste = criaArvore("*");
	insiraNodo(teste, "-");
	insiraNodo(teste, "*");
	insiraNodo(teste->filhoesquerdo, "3");
	insiraNodo(teste->filhoesquerdo, "1");
	insiraNodo(teste->filhodireito, "5");
	insiraNodo(teste->filhodireito, "2");

	posordem(teste);
	cout << "\n";
	ordem(teste);
	cout << "\n";
	preordem(teste);
	cout << "\n";

	Funcoes f; 
	float resultado = f.eval(teste);
	cout << resultado; 

	//printf("%c\n",teste->chave);
	//comentário 
	return 0;
}
