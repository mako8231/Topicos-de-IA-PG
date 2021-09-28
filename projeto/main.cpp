#include "includes/arvore.h"
#include <stdio.h>
#include <iostream>

using namespace std;
int main(){

	arvoregenes teste = criaArvore("sin");
	insiraNodo(teste, "-");
	insiraNodo(teste, "*");
	insiraNodo(teste->filhoesquerdo, "3");
	insiraNodo(teste->filhoesquerdo, "1");
	insiraNodo(teste->filhodireito, "7");
	insiraNodo(teste->filhodireito, "5");

	posordem(teste);
	cout << "\n";
	ordem(teste);
	cout << "\n";
	preordem(teste);

	//printf("%c\n",teste->chave);
	//comentário 
	return 0;
}
