/*
 * IAC · Trabalho 1: Buscas não informadas
 *
 * Problema: a partir de um estado inicial entre 1 e 100, encontrar um número primo
 * usando as ações "andar duas casas à esquerda" (-2) e "andar cinco casas à direita" (+5).
 *
 * Tarefa 1: busca em largura (fila + visitados)
 * Tarefa 2: busca em profundidade limitada (recursiva, verifica só o caminho)
 * Tarefa 3: busca em profundidade limitada iterativa (limite começa em 1 e vai aumentando)
 *
 * Sem variáveis globais: o que a recursão precisa compartilhar (caminho, limite e avisos)
 * fica na struct BuscaProfundidade, criada por quem inicia a busca e passada por ponteiro.
 */

#include <stdio.h>

#ifdef _WIN32
#include <windows.h> // SetConsoleOutputCP: exibe a moldura do menu corretamente no Windows
#endif

// ===== Constantes do problema =====
#define ESTADO_MIN 1 // menor estado válido
#define ESTADO_MAX 100 // maior estado válido
#define PASSO_ESQUERDA 2 // ação "andar duas casas à esquerda" (-2)
#define PASSO_DIREITA 5 // ação "andar cinco casas à direita" (+5)
#define QTD_FILHOS 2 // cada estado gera no máximo 2 filhos
#define QTD_PRIMOS 25 // quantidade de primos entre 1 e 100
#define NAO_ENCONTRADO -1 // retorno da busca em profundidade quando não acha primo

// ===== Tarefa 1 =====
// Tamanho dos vetores da busca em largura (fila e visitados).
// Comece com 5 para comparar com a versão feita em aula.
#define TAM_VETOR 5

// ===== Tarefas 2 e 3 =====
// Profundidade máxima da Tarefa 2 (o estado inicial está na profundidade 0).
#define LIMITE_PROFUNDIDADE 5
// Tamanho do vetor 'caminho'. Para caber a busca inteira, precisa de LIMITE_PROFUNDIDADE + 1.
// Deixe menor que isso para testar o aviso de estouro de memória.
#define TAM_CAMINHO 6
// Tarefa 3: maior limite tentado antes de desistir (evita rodar para sempre)
#define LIMITE_ITERATIVO_MAX 20

// ===================== Funções auxiliares =====================

int eh_primo(int numero)
{
    // Tabela vale para o intervalo ESTADO_MIN..ESTADO_MAX (1 a 100)
    int primos[QTD_PRIMOS] = { 2, 3, 5, 7, 11, 13,
        17, 19, 23, 29, 31, 37,
        41, 43, 47, 53, 59, 61,
        67, 71, 73, 79, 83, 89,
        97 };

    for (int i = 0; i < QTD_PRIMOS; i++) {
        if (primos[i] == numero) {
            return 1; // é primo
        }
    }

    return 0; // não é primo
}

// Validação de transição: estado está dentro do intervalo permitido
int estado_valido(int estado)
{
    return estado >= ESTADO_MIN && estado <= ESTADO_MAX;
}

// Ver se uma variável está no vetor ou nao.
int esta_no_vetor(const int vetor[], int qtd, int valor)
{
    for (int i = 0; i < qtd; i++) {
        if (vetor[i] == valor) {
            return 1;
        }
    }
    return 0;
}

void imprime_vetor(const char* nome, const int vetor[], int qtd)
{
    printf("%s: [", nome);
    for (int i = 0; i < qtd; i++) {
        printf(i == 0 ? "%d" : " %d", vetor[i]);
    }
    printf("]\n");
}

// Avisos finais pedidos no enunciado (comuns às três buscas)
void imprime_avisos(int saiu_do_intervalo, int estourou_memoria)
{
    if (saiu_do_intervalo) {
        printf("Aviso: A busca tentou gerar estados fora do intervalo %d a %d.\n", ESTADO_MIN, ESTADO_MAX);
    }
    if (estourou_memoria) {
        printf("Aviso: Houve estouro de memoria (vetor cheio). Alguns nos foram descartados.\n");
    }
}

// Lê o estado inicial, repetindo enquanto a entrada for inválida (texto ou fora de 1..100).
// Retorna 1 se leu um estado válido, 0 se a entrada acabou (EOF).
int ler_estado_inicial(int* estado) //estado inicial é o primeiro número e o estado é o número atual
{
    int lidos, c;

    while (1) {
        printf("Defina um numero de %d a %d: ", ESTADO_MIN, ESTADO_MAX);
        lidos = scanf("%d", estado);

        if (lidos == 1 && estado_valido(*estado)) {
            return 1;
        }
        printf("Entrada invalida.\n");
    }
}

// ===================== Tarefa 1: busca em largura =====================

void busca_largura(int estado_inicial)
{
    int fila[TAM_VETOR]; // fronteira (FIFO): o próximo a visitar é sempre fila[0]
    int qtd_fila = 0;
    int visitados[TAM_VETOR]; // histórico dos nós já expandidos
    int qtd_visitados = 0;
    int atual = estado_inicial;
    int encontrou = 0;
    int saiu_do_intervalo = 0;
    int estourou_memoria = 0;

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
        } else {
            printf("  %d nao guardado (vetor de visitados cheio)\n", atual);
            estourou_memoria = 1;
        }

        // Produzir nós filhos
        int filhos[QTD_FILHOS] = { atual - PASSO_ESQUERDA, atual + PASSO_DIREITA };

        // Validar transição, verificar fronteira e histórico, e colocar na fila se houver espaço
        for (int i = 0; i < QTD_FILHOS; i++) {
            int filho = filhos[i];

            if (!estado_valido(filho)) {
                printf("  %d ignorado (fora do intervalo %d a %d)\n", filho, ESTADO_MIN, ESTADO_MAX);
                saiu_do_intervalo = 1;
            } else if (esta_no_vetor(fila, qtd_fila, filho) || esta_no_vetor(visitados, qtd_visitados, filho)) {
                printf("  %d ignorado (ja esta na fila ou nos visitados)\n", filho);
            } else if (qtd_fila >= TAM_VETOR) {
                printf("  %d descartado (fila cheia)\n", filho);
                estourou_memoria = 1;
            } else {
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

    imprime_avisos(saiu_do_intervalo, estourou_memoria);
}

// ===================== Tarefas 2 e 3: busca em profundidade =====================

// Isso substui todas as variavel globais. Cada chamada recursiva tem suas variáveis locais.
// É um "bloco" de código onde agrupa tudo o que a recursão precisa compartilhar:
typedef struct {
    int caminho[TAM_CAMINHO]; // é o estado visitado na profundidade
    int limite; // até que profundidade a busca pode descer.
    int profundidade_solucao; // a profundidade que o primo foi encontrado
    int saiu_do_intervalo; // vira 1 se algum filho saiu de 1 a 100.
    int estourou_memoria; // vira 1 se algum estado não coube no vetor 'caminho'
    int atingiu_limite; // vira 1 se algum ramo foi cortado pelo limite de profundidade
} BuscaProfundidade; // usa esse nome para chamar todas essas informações

void inicia_busca(BuscaProfundidade* busca, int limite)
{
    busca->limite = limite;
    //(*busca).limite = limite;
    busca->profundidade_solucao = NAO_ENCONTRADO;
    busca->saiu_do_intervalo = 0;
    busca->estourou_memoria = 0;
    busca->atingiu_limite = 0;
}

// Retorna 1 se 'estado' já está no caminho (posições 0 até 'profundidade' - 1), 0 caso contrário.
// Só olha o caminho (os ancestrais), nunca a fronteira.
int caminho_visitado(const int caminho[], int estado, int profundidade)
{
    for (int i = 0; i < profundidade; i++) {
        if (caminho[i] == estado) {
            return 1;
        }
    }
    return 0;
}

// Busca em profundidade limitada (recursiva).
// A pilha da busca é a própria pilha de chamadas da recursão.

//Recebe a struct compartilhada, o estado a visitar e o nível em que ele está. Devolve o primo encontrado ou -1("NAO ENCONTRADO").
int busca_profundidade(BuscaProfundidade* busca, int estado, int profundidade) //"busca" é um ponteiro para uma "BuscaProfundidade"
{
    // Verificação de memória: Se o nível já não cabe no vetor, ela não escreve nada (evitando estourar a memória)
    if (profundidade >= TAM_CAMINHO) {
        printf("%d descartado (vetor caminho cheio)\n", estado);
        busca->estourou_memoria = 1; //"vá até a struct que está no endereço "busca", pegue o campo "estourou_memoria" e coloque 1 nele"
        return NAO_ENCONTRADO;
    }

    // Registra a visita/caminho
    busca->caminho[profundidade] = estado;
    printf("Visitando %d (profundidade %d)\n", estado, profundidade);

    // Objetivo: o estado é primo
    if (eh_primo(estado)) {
        busca->profundidade_solucao = profundidade;//grava a profundidade e devolve o próprio estado.
        return estado; //encerra na hora, sem gerar filhos
    }

    // Bateu a profundidade máxima: nó é visitado, porém não é expandido
    if (profundidade >= busca->limite) {
        busca->atingiu_limite = 1;
        return NAO_ENCONTRADO;
    }

    // Produzir nós filhos: Os dois filhos são o estado -2 e o estado +5. A ordem importa: o da esquerda é sempre tentado primeiro.
    int filhos[QTD_FILHOS] = { estado - PASSO_ESQUERDA, estado + PASSO_DIREITA };

    // Chamar a recursão para um filho de cada vez
    for (int i = 0; i < QTD_FILHOS; i++) {
        int filho = filhos[i];

        if (!estado_valido(filho)) { // "caso o estado filho NÃO seja válido" //o filho é descartado, mas o laço continua para o outro filho.
            printf("%d ignorado (fora do intervalo %d a %d)\n", filho, ESTADO_MIN, ESTADO_MAX);
            busca->saiu_do_intervalo = 1;
        } else if (caminho_visitado(busca->caminho, filho, profundidade + 1)) { //conferimos se o filho já está no caminho, olhando só os ancestrais
            printf("%d ignorado (ja esta no caminho)\n", filho);
        } else { //há a recursão: a função chama a si mesma com o filho
            int resultado = busca_profundidade(busca, filho, profundidade + 1); //"resultado" devolve primo encontrado ou NAO_ENCONTRADO (-1).
            if (resultado != NAO_ENCONTRADO) {
                return resultado; // achou no ramo do filho: repassa o primo para cima
            }
        }
    }

    // Nenhum filho achou: volta para o pai (backtracking).
    // Não precisa apagar caminho[profundidade]: o próximo ramo sobrescreve essa posição.
    return NAO_ENCONTRADO;
}

void imprime_resultado_profundidade(const BuscaProfundidade* busca, int resultado)
{
    if (resultado != NAO_ENCONTRADO) {
        printf("\nPrimo encontrado: %d (profundidade %d)\n", resultado, busca->profundidade_solucao);
        imprime_vetor("Caminho", busca->caminho, busca->profundidade_solucao + 1);
    } else {
        printf("\nNenhum primo encontrado dentro do limite de profundidade %d.\n", busca->limite);
    }
}

// Tarefa 3: reaproveita busca_profundidade() da Tarefa 2, aumentando o limite a cada rodada
void busca_profundidade_iterativa(int estado_inicial)
{
    BuscaProfundidade busca;
    int resultado = NAO_ENCONTRADO;
    int saiu_do_intervalo = 0;
    int estourou_memoria = 0;
    int limite;

    for (limite = 1; limite <= LIMITE_ITERATIVO_MAX; limite++) {
        printf("\n--- Rodada %d: limite de profundidade %d ---\n", limite, limite);

        inicia_busca(&busca, limite);
        resultado = busca_profundidade(&busca, estado_inicial, 0);

        // Os avisos valem para a busca toda, então acumulam entre as rodadas
        saiu_do_intervalo = saiu_do_intervalo || busca.saiu_do_intervalo;
        estourou_memoria = estourou_memoria || busca.estourou_memoria;

        if (resultado != NAO_ENCONTRADO) {
            break;
        }

        // Se nenhum ramo foi cortado pelo limite, aumentar o limite não muda nada
        // (acontece quando os ramos param por estouro do 'caminho', intervalo ou ciclo)
        if (!busca.atingiu_limite) {
            printf("Nenhum ramo foi cortado pelo limite: aumentar o limite nao ajuda.\n");
            break;
        }

        printf("Nenhum primo com limite %d.\n", limite);
    }

    imprime_resultado_profundidade(&busca, resultado);

    if (resultado == NAO_ENCONTRADO && limite > LIMITE_ITERATIVO_MAX) {
        printf("Aviso: A busca parou no limite maximo de %d.\n", LIMITE_ITERATIVO_MAX);
    }
    imprime_avisos(saiu_do_intervalo, estourou_memoria);
}

// ===================== Menu =====================

int main()
{
    int opcao = -1;
    int estado_inicial;
    int resultado;
    BuscaProfundidade busca;

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Para a exibição correta do menu
#endif

    printf("╔════════════════════════════════════╗\n");
    printf("║  ESCOLHA O TIPO DE BUSCA DESEJADA  ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║ [1] Busca em largura               ║\n");
    printf("║ [2] Busca em profundidade limitada ║\n");
    printf("║ [3] Busca em prof. lim. iterativa  ║\n");
    printf("║ [0] Sair                           ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║  Escolha:                          ║\r"); // \r: o cursor volta ao início da linha
    printf("║  Escolha: "); // reescreve o começo e deixa o cursor depois do "Escolha: "
    if (scanf("%d", &opcao) != 1) {
        opcao = -1;
    }
    printf("╚════════════════════════════════════╝\n");

    if (opcao < 0 || opcao > 3) {
        printf("Opcao invalida.\n");
        return 1;
    }

    if (!ler_estado_inicial(&estado_inicial)) {
        return 1;
    }

    switch (opcao) {
    case 1:
        busca_largura(estado_inicial);
        break;
    case 2:
        printf("\nLimite de profundidade: %d\n\n", LIMITE_PROFUNDIDADE);
        inicia_busca(&busca, LIMITE_PROFUNDIDADE);
        resultado = busca_profundidade(&busca, estado_inicial, 0); // uma única chamada, como pede o enunciado
        imprime_resultado_profundidade(&busca, resultado);
        if (busca.atingiu_limite) {
            printf("Aviso: A busca atingiu o limite de profundidade.\n");
        }
        imprime_avisos(busca.saiu_do_intervalo, busca.estourou_memoria);
        break;
    case 3:
        busca_profundidade_iterativa(estado_inicial);
        break;
    }

    return 0;
}
