#include "includes/arvore.h"
#include <stdio.h>
#include <iostream>
#include "includes/funcoes.h"

using namespace std;


int main(){

	arvoregenes teste = criaArvore("+");
	insiraNodo(&teste->filhoesquerdo, "-");
	insiraNodo(&teste->filhodireito, "*");
	insiraNodo(&teste->filhoesquerdo->filhoesquerdo, "3");
	insiraNodo(&teste->filhoesquerdo->filhodireito, "1");
	insiraNodo(&teste->filhodireito->filhoesquerdo, "5");
	insiraNodo(&teste->filhodireito->filhodireito, "d");

	posordem(teste);
	cout << "\n";
	ordem(teste);
	cout << "\n";
	preordem(teste);
	cout << "\n";

	Funcoes f; 
	saida resultado = f.eval(teste, 3, 2);
	cout << resultado.numerico;

	cout << "\n";

	arvoregenes copia;
	copia = copiaArvore(teste);
	ordem(copia);


	//printf("%c\n",teste->chave);
	//comentário 
	return 0;
}
