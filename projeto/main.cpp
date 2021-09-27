#include "includes/arvore.h"
#include <stdio.h>
#include <string>

using namespace std;
int main(){
	arvoregenes teste = criaArvore('t');
	insiraNodo(teste, 'a');
	insiraNodo(teste, 'b');
	prefixa(teste);
	//printf("%c\n",teste->chave);
	//comentário 
	return 0;
}
