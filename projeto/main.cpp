#include "includes/arvore.h"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
int main(){
	arvoregenes teste = criaArvore('+');
	insiraNodo(teste, '-');
	insiraNodo(teste, '*');
	insiraNodo(teste->filhoesquerdo, '3');
	insiraNodo(teste->filhoesquerdo, '1');
	insiraNodo(teste->filhodireito, '7');
	insiraNodo(teste->filhodireito, '5');
	

	//printf("%c\n",teste->chave);
	//comentário 
	return 0;
}
