#include "includes/arvore.h"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
int main(){
	arvoregenes teste = criaArvore('4');
	insiraNodo(teste, '6');
	insiraNodo(teste, '2');
	insiraNodo(teste->filhoesquerdo, '3');
	insiraNodo(teste->filhoesquerdo, '1');
	insiraNodo(teste->filhodireito, '7');
	insiraNodo(teste->filhodireito, '5');
	

	preordem(teste);
	cout << "\n";
	ordem(teste);
	cout << "\n";
	posordem(teste);

	//printf("%c\n",teste->chave);
	//comentário 
	return 0;
}
