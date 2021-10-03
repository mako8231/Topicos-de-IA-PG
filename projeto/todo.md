## Listas de coisas a fazer
1- Testar se o interpretador está funcionando. ✔️

2- Antes de implementar totalmente o mesmo, reestruturar a árvore para suportar strings (assim é possível implementar expressões mais complexas, como estruturas condicionais, etc). ✔️

3- Por enquanto ainda será usada uma arvore binária, entretanto, é melhor já pensar em uma implementação de uma estrutura de arvore mais robusta. 

    3.1 - Na verdade, acredito que árvore binária tem plena capacidade de resolver o problema do corte. 

4- Na stack, adaptar o vetor para a classe std::Vector, considerando que ele já lida com memória alocada dinamicamente e não tem necessidade de usar espaço desnecessário na memória. (a struct stack foi deletada aliás, a ideia era usar a própria como interpretador mas dá pra fazer isso recursivamente sem a necessidade de usar outra estrutura de dados). ✔️

5- Pensar em uma maneira de gerar uma população inicial. Que atenda as restrições do problema do corte unidimensional.

6- Fazer o interpretador reconhecer os terminais (as variáveis no caso). ✔️ 
