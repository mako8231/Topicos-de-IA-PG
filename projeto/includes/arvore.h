#ifndef ARVORE 
#define ARVORE 

#include <string>
#include <vector>

using namespace std;
    /**Por enquanto, acredito que uma árvore binária dê conta da situação
     * caso contrário, outros tipos de arvores podem ser testados 
     **/
    struct nodo
    {
        nodo *pai;
        nodo *filhodireito;
        nodo *filhoesquerdo;  
        char *chave;  
    };

    typedef nodo *arvoregenes;
    //métodos 
    arvoregenes criaArvore(char *chave);
    arvoregenes copiaArvore(arvoregenes nodo);
    int geraNum(int max);
    void insiraNodo(arvoregenes *alvo, char *chave);
    void apagaNodo(arvoregenes *nodo);
    void preordem(arvoregenes nodo);
    void posordem(arvoregenes nodo);
    void ordem(arvoregenes nodo);
    //geração da população 
     
    arvoregenes gerarPopulacao(int nivel);
#endif