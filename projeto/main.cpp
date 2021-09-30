#include "includes/arvore.h"
#include <stdio.h>
#include <iostream>
#include "includes/funcoes.h"

using namespace std;




int main(){

	arvoregenes teste = criaArvore(">=");
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
	saida resultado = f.eval(teste);
	cout << resultado.binario; 

	//printf("%c\n",teste->chave);
	//comentário 
	return 0;
}
