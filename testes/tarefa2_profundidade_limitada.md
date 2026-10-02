# Tarefa 2 · Busca em profundidade limitada (recursiva)

Arquivo testado: `src/____.c` · compilado com `gcc -Wall -Wextra`
Rodado em: __/__/2026

**Como preencher:** escreva o **Esperado** *antes* de rodar e só depois o **Obtido**.
Saídas completas (opcional) vão em `saidas/` com o nome `t2_prof<P>_tam<TAM>_n<entrada>.txt`.

O enunciado pede: funções `caminho_visitado()` e `busca_profundidade()`; `main()` chama `busca_profundidade()` **uma vez**; todas as constantes em `#define`; verificação de memória e validação de transição.

**Constantes usadas** (preencher com os nomes do código):

| `#define` | Para que serve | Valor inicial |
|---|---|---|
| | profundidade máxima | |
| | tamanho do vetor `caminho` | |
| | | |

---

## Casos

| # | Caso | Prof. máx. | Tam. caminho | Entrada | Esperado | Obtido (primo / −1) | Caminho impresso | Aviso de transição? | Aviso de estouro? | OK? |
|---|---|---|---|---|---|---|---|---|---|---|
| 1 | estado inicial já é primo | | | 2 | | | | | | |
| 2 | borda inferior | | | 1 | | | | | | |
| 3 | borda superior | | | 100 | | | | | | |
| 4 | caso intermediário (comparar com a BFS) | | | 10 | | | | | | |
| 5 | profundidade insuficiente: não acha | 1 | | | | | | | | |
| 6 | profundidade suficiente: acha | | | | | | | | | |
| 7 | ciclo evitado por `caminho_visitado()` | | | | | | | | | |
| 8 | profundidade máxima maior que o vetor `caminho` | | | | | | | | | |
| 9 | entrada inválida | | | `abc`, `0`, `101` | | | | | | |
| 10 | varredura | | | 1 a 100 | | | | | | |
| 11 | | | | | | | | | | |

---

## Comparação com a BFS (Tarefa 1)

| Entrada | Primo da BFS | Primo da profundidade limitada | Iguais? | Por quê? |
|---|---|---|---|---|
| 10 | 13 | | | |
| 100 | 97 | | | |
| | | | | |

Perguntas para a arguição:
- Por que aqui só se verifica o **caminho**, e não a fronteira?
- O que a recursão faz com o caminho quando uma chamada retorna −1?
