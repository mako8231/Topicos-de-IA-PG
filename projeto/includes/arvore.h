#ifndef ARVORE 
#define ARVORE 
    /**Por enquanto, acredito que uma árvore binária dê conta da situação
     * caso contrário, outros tipos de arvores podem ser testados 
     **/
    struct nodo
    {
        nodo *pai;
        nodo *filhodireito;
        nodo *filhoesquerdo;  
        char chave;  
    };

    typedef nodo *arvoregenes;

    arvoregenes criaArvore(char chave);
    void insiraNodo(arvoregenes nodo, char chave);
    void apagaNodo(arvoregenes nodo);
    
#endif