#ifndef ARVORE 
#define ARVORE 

#include <string>
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

    arvoregenes criaArvore(const char *chave);
    void insiraNodo(arvoregenes nodo, const char *chave);
    void apagaNodo(arvoregenes *nodo);
    void preordem(arvoregenes nodo);
    void posordem(arvoregenes nodo);
    void ordem(arvoregenes nodo);

#endif