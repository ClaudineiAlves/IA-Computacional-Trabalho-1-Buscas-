#include <stdio.h>
// #include <stdlib.h>

int eh_primo(int numero)
{
    int primos[25] = { 2, 3, 5, 7, 11, 13,
        17, 19, 23, 29, 31, 37,
        41, 43, 47, 53, 59, 61,
        67, 71, 73, 79, 83, 89,
        97 };

    for (int i = 0; i < 25; i++) {
        if (primos[i] == numero) {
            return 1; // é primo
        }
    }

    return 0; // não é primo
}

int main()
{
    int Estado_inicial, dir, esq;
    int v0 = -1, v1 = -1, v2 = -1, v3 = -1, v4 = -1;
    // Definir o estado inicial
    printf("Defina um numero de 0 a 100: ");
    scanf("%d", &Estado_inicial);
    v0 = Estado_inicial;

    // verifica se condiz c/ objeto]
    while (eh_primo(v0) == 0) {
        // produzir nós filhos
        esq = v0 - 2;
        dir = v0 + 5;

        // verificar fronteira e historico

        // remover o nó visitado da fila + Gerenciar fila
        v0 = v1;
        v1 = v2;
        v2 = v3;
        v3 = v4;
        v4 = -1;

        // verificar fronteira E HISTORICO

        // colocar na fila
        //  cenario vetor não inicializado
        if (v0 == -1) {
            v0 = esq;
            v1 = dir;
        } else if (v1 == -1) {
            v1 = esq;
            v2 = dir;
        } else if (v2 == -1) {
            v2 = esq;
            v3 = dir;
        } else if (v3 == -1) {
            v3 = esq;
            v4 = dir;
        } else if (v4 == -1) {
            v4 = esq;
            // flag
        } else {
            // flag
        }
    }

    // Se sim, acabou
    printf(" %d %d %d %d %d", v0, v1, v2, v3, v4);
}
