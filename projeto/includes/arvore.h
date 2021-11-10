#ifndef ARVORE 
#define ARVORE 

#include <string>
#include <vector>

using namespace std;
    /**Por enquanto, acredito que uma árvore binária dê conta da situação
     * caso contrário, outros tipos de arvores podem ser testados 
     * 
     * condição da satisfação da demanda:
     * Somatorio(programacao[i] * cortes[i]) <= demanda + estmax
     * 
     **/
    struct nodo
    {
        double fo; 
        nodo *filhodireito;
        nodo *filhoesquerdo;  
        char *chave;  
    };

    typedef nodo *arvoregenes;
    //métodos 
    arvoregenes criaArvore(char *chave);
    arvoregenes copiaArvore(arvoregenes nodo);
    arvoregenes crossoverPoint(arvoregenes nodo);
    int profundidade(arvoregenes nodo);
    void insiraNodo(arvoregenes *alvo, char *chave);
    void apagaNodo(arvoregenes *nodo);
    void preordem(arvoregenes nodo);
    void posordem(arvoregenes nodo);
    void ordem(arvoregenes nodo);
    void substituirFolha(arvoregenes *nodo, arvoregenes novo_nodo);
    

    //geração da população 
    arvoregenes gerarPopulacao(int nivel, arvoregenes individuo);
#endif