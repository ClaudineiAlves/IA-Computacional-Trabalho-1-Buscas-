#include <stdio.h>

// Tamanho de todos os vetores (fila e visitados).
// Comece com 5 para comparar com a versão feita em aula.
#define TAM_VETOR 5

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

// Retorna 1 se 'valor' está nas 'qtd' primeiras posições de 'vetor'
int esta_no_vetor(int vetor[], int qtd, int valor)
{
    for (int i = 0; i < qtd; i++) {
        if (vetor[i] == valor) {
            return 1;
        }
    }
    return 0;
}

void imprime_vetor(const char* nome, int vetor[], int qtd)
{
    printf("%s: [", nome);
    for (int i = 0; i < qtd; i++) {
        printf(i == 0 ? "%d" : " %d", vetor[i]);
    }
    printf("]\n");
}

int main()
{
    int estado_inicial = -1, atual, esq, dir;
    int fila[TAM_VETOR]; // fronteira (FIFO): o próximo a visitar é sempre fila[0]
    int qtd_fila = 0;
    int visitados[TAM_VETOR]; // histórico dos nós já expandidos
    int qtd_visitados = 0;
    int encontrou = 0;

    // Definir o estado inicial (repete enquanto estiver fora de 1..100)
    do {
        printf("Defina um numero de 1 a 100: ");
        if (scanf("%d", &estado_inicial) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { } // descarta entrada não numérica
            if (c == EOF) {
                return 1;
            }
            estado_inicial = -1;
        }
    } while (estado_inicial < 1 || estado_inicial > 100);

    fila[qtd_fila++] = estado_inicial;

    while (qtd_fila > 0) {
        atual = fila[0];
        printf("\nVisitando %d\n", atual);

        // Teste de objetivo quando o nó chega na frente da fila (como em sala)
        if (eh_primo(atual)) {
            encontrou = 1;
            break;
        }

        // Remover o nó visitado da fila: desloca todos uma posição para a frente
        for (int i = 0; i < qtd_fila - 1; i++) {
            fila[i] = fila[i + 1];
        }
        qtd_fila--;

        // Guardar no histórico (sem escrever além do fim do vetor)
        if (qtd_visitados < TAM_VETOR) {
            visitados[qtd_visitados++] = atual;
        }

        // Produzir nós filhos
        esq = atual - 2;
        dir = atual + 5;
        int filhos[2] = { esq, dir };

        // Verificar fronteira e histórico; colocar na fila se houver espaço
        for (int i = 0; i < 2; i++) {
            int filho = filhos[i];
            if (esta_no_vetor(fila, qtd_fila, filho) || esta_no_vetor(visitados, qtd_visitados, filho)) {
                printf("  %d ignorado (ja esta na fila ou nos visitados)\n", filho);
            }
            else if (filho<1 || filho>100){
                printf(" %d ignorado (ultrapassou o limite inferior/superior)\n",filho);
            }
            else if(qtd_fila >= TAM_VETOR){
                printf(" %d ignorado (estourou o tamanho da fila)\n",filho);
            }
            else if (qtd_fila < TAM_VETOR) {
                fila[qtd_fila++] = filho;
            }
        }

        imprime_vetor("  Fila", fila, qtd_fila);
        imprime_vetor("  Visitados", visitados, qtd_visitados);
    }

    if (encontrou) {
        printf("\nPrimo encontrado: %d\n", atual);
    } else {
        printf("\nFila vazia: nenhum primo encontrado.\n");
    }

    return 0;
}
