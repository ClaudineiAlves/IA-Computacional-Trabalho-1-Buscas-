#include <stdio.h>
#include <windows.h> // Para a tabela de menu

// Tamanho de todos os vetores (fila e visitados).
// Comece com 5 para comparar com a versão feita em aula.
#define TAM_VETOR 5

// Profundidade máxima da busca (P). Teste com valores diferentes.
#define LIMITE_PROFUNDIDADE 5
// Tamanho do vetor 'caminho'.
// Precisa de LIMITE_PROFUNDIDADE + 1 posições (a posição 0 é o estado inicial).
#define TAM_CAMINHO 6


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

int busca_largura()
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

//PARTE DO BRENO! (BUSCA EM PROFUNDIDADE LIMITADA):
// Retorna 1 se 'estado' já está no caminho (posições 0 até 'profundidade' - 1).
// Retorna 0 caso contrário.
// Só olha o caminho (os ancestrais), nunca a fronteira.

// Variáveis globais da busca em profundidade (a recursão precisa enxergá-las)
int caminho[TAM_CAMINHO];      // caminho[p] = estado visitado na profundidade p
int profundidade_solucao = -1; // profundidade em que o primo foi achado
int saiu_do_intervalo = 0;     // avisa no final se tentou gerar nós fora de 1..100
int estourou_memoria = 0;      // avisa no final se o caminho não coube no vetor
int atingiu_limite = 0;        // avisa no final se bateu no limite de profundidade

int encontrou = 0;
// 0 = ainda não achou nenhum primo (valor inicial; também vale se a busca falhar)
// 1 = achou um primo (a busca para de explorar os outros ramos)

int caminho_visitado(int estado, int profundidade)
{
    for (int i = 0; i < profundidade; i++) {
        if (caminho[i] == estado) {
            return 1;
        }
    }
    return 0;
}

// Busca em profundidade limitada (recursiva).
// Retorna o estado primo encontrado, ou -1 se não achou nada a partir deste nó.

void busca_profundidade(int estado, int profundidade)
{
    // Caso base 1: o caminho não cabe mais no vetor (estouro de memória)
    if (profundidade >= TAM_CAMINHO) {
        printf("%d descartado (estourou o tamanho do caminho)\n", profundidade * 2, "", estado);
        estourou_memoria = 1;
    }
    else {
        // Adiciona o estado ao caminho
        caminho[profundidade] = estado;
        printf("Visitando %d (profundidade %d)\n", estado, profundidade);

        // Caso base 2: o estado é primo (objetivo)
        if (eh_primo(estado)) {
            profundidade_solucao = profundidade;
            encontrou = 1;
        }
        // Caso base 3: bateu a profundidade máxima
        // [ALTERADO] antes: return -1;  -> agora 'encontrou' continua 0
        else if (profundidade >= LIMITE_PROFUNDIDADE) {
            atingiu_limite = 1;
        }
        else {
            // Produzir nós filhos
            int esq = estado - 2;
            int dir = estado + 5;
            int filhos[2] = { esq, dir };

            // Chamar a recursão para um filho de cada vez
            for (int i = 0; i < 2 && encontrou == 0; i++) {
                int filho = filhos[i];

                if (filho < 1 || filho > 100) {
                    printf("%d ignorado (fora do intervalo 1 a 100)\n", (profundidade + 1) * 2, "", filho);
                    saiu_do_intervalo = 1;
                }
                else if (caminho_visitado(filho, profundidade + 1)) {
                    printf("%d ignorado (ja esta no caminho)\n", (profundidade + 1) * 2, "", filho);
                }
                else {
                    busca_profundidade(filho, profundidade + 1);
                }
            }
            //se nenhum filho achou, 'encontrou' continua 0
        }
    }
}

// Le o estado inicial, chama a busca uma única vez e imprime os avisos
int executa_profundidade()
{
    int estado_inicial = -1;

    // Definir o estado inicial (repete enquanto estiver fora de 1 a 100)
    do {
        printf("Defina um numero de 1 a 100: ");
        scanf("%d", &estado_inicial);
    } while (estado_inicial < 1 || estado_inicial > 100);

    printf("\nLimite de profundidade: %d\n\n", LIMITE_PROFUNDIDADE);

    // Uma única chamada, como pede o enunciado
    busca_profundidade(estado_inicial, 0);

    if (encontrou == 1) {
        printf("\nPrimo encontrado: %d\n", caminho[profundidade_solucao]); // antes: resultado
        imprime_vetor("Caminho", caminho, profundidade_solucao + 1);
    } else {
        printf("\nNenhum primo encontrado dentro do limite de profundidade.\n");
    }

    // Avisos finais pedidos no enunciado
    if (atingiu_limite) {
        printf("Aviso: A busca atingiu o limite de profundidade.\n");
    }
    if (saiu_do_intervalo) {
        printf("Aviso: A busca tentou gerar estados fora do intervalo 1 a 100.\n");
    }
    if (estourou_memoria) {
        printf("Aviso: Houve estouro de memoria (caminho cheio). Alguns nos foram descartados.\n");
    }

    return 0;
}

void busca_profundidade_iterativa(int estado, int profundidade, int limite)
{ //quando a aux aumentar, o programa ira avisar que houve um aumento no limite

    if (profundidade >= TAM_CAMINHO) {
    printf("%d descartado (estourou o tamanho do caminho)\n", profundidade * 2, "", estado);
    estourou_memoria = 1;
    }

    else {  //vai decidir o que fazer agora sabendo que ainda tem memória
            // Adiciona o estado ao caminho
        caminho[profundidade] = estado;
        printf("Visitando %d (profundidade %d)\n", estado, profundidade + 1);

        // Caso base 2: o estado é primo (objetivo)
        if (eh_primo(estado)) {
            profundidade_solucao = profundidade;
            encontrou = 1;
            return;
        }
        else {
            // Produzir nós filhos
            if(profundidade < limite){
            int esq = estado - 2;
            int dir = estado + 5;
            int filhos[2] = { esq, dir };

            // Chamar a recursão para um filho de cada vez
            for (int i = 0; i < 2 && encontrou == 0; i++) {
                int filho = filhos[i];

                if (filho < 1 || filho > 100) {
                    printf("%d ignorado (fora do intervalo 1 a 100)\n", (limite + 1) * 2, "", filho);
                    saiu_do_intervalo = 1;
                }
                else if (caminho_visitado(filho, profundidade + 1)) {
                    printf("%d ignorado (ja esta no caminho)\n", (limite + 1) * 2, "", filho);
                }
                else {
                    busca_profundidade_iterativa(filho, profundidade + 1, limite);
                }
            }
            //se nenhum filho achou, 'encontrou' continua 0
            }
        }
    }
}

int executa_profundidade_iterativa()
{
    int estado_inicial = -1, limite = 1;

    // Definir o estado inicial (repete enquanto estiver fora de 1 a 100)
    do {
        printf("Defina um numero de 1 a 100: ");
        scanf("%d", &estado_inicial);
    } while (estado_inicial < 1 || estado_inicial > 100);

    while(limite <= 10 && encontrou == 0){
    printf("\nLimite de profundidade: %d\n\n", limite + 1);
    busca_profundidade_iterativa(estado_inicial, 0, limite);
    limite++; //limite aumentando for
    }

    if (encontrou == 1) {
        printf("\nPrimo encontrado: %d\n", caminho[profundidade_solucao]); // antes: resultado
        imprime_vetor("Caminho", caminho, profundidade_solucao + 1);
    } else {
        printf("\nNenhum primo encontrado dentro do limite de profundidade. Aumentando o limite em 1(um) nivel\n");
    }

    // Avisos finais pedidos no enunciado
    if (atingiu_limite) {
        printf("Aviso: A busca atingiu o limite de profundidade, aumentando o limite em um nivel.\n");
    }
    if (saiu_do_intervalo) {
        printf("Aviso: A busca tentou gerar estados fora do intervalo 1 a 100.\n");
    }
    if (estourou_memoria) {
        printf("Aviso: Houve estouro de memoria (caminho cheio). Alguns nos foram descartados.\n");
    }

    return 0;
}

// Parte que o usuário irá escolher a busca desejada
int main()
{
    int opcao = 0;

    SetConsoleOutputCP(CP_UTF8); //Para a exibição correta do menu

printf("╔════════════════════════════════════╗\n");
printf("║  ESCOLHA O TIPO DE BUSCA DESEJADA  ║\n");
printf("╠════════════════════════════════════╣\n");
printf("║ [1] Busca em largura               ║\n");
printf("║ [2] Busca em profundidade limitada ║\n");
printf("║ [3] Busca em prof. lim. iterativa  ║\n");
printf("╠════════════════════════════════════╣\n");
printf("║  Escolha:                          ║\r");   // \r em vez de \n: o cursor volta ao início da linha
printf("║  Escolha: ");                               // reescreve o começo e deixa o cursor depois do "Escolha: "
scanf("%d", &opcao);
printf("╚════════════════════════════════════╝\n");

    switch (opcao) {
        case 1:
            return busca_largura();
        case 2:
            return executa_profundidade();
        case 3:
            return executa_profundidade_iterativa();
        default:
            printf("Opcao invalida.\n");
            return 1;
    }
}
