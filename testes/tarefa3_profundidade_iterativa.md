# Tarefa 3 · Busca em profundidade limitada iterativa

Arquivo testado: `src/____.c` · compilado com `gcc -Wall -Wextra`
Rodado em: __/__/2026

**Como preencher:** escreva o **Esperado** *antes* de rodar e só depois o **Obtido**.
Saídas completas (opcional) vão em `saidas/` com o nome `t3_tam<TAM>_n<entrada>.txt`.

O enunciado pede: a profundidade máxima **começa em 1** e é incrementada até encontrar uma solução, reaproveitando a Tarefa 2.

**Constantes usadas** (preencher com os nomes do código):

| `#define` | Para que serve | Valor inicial |
|---|---|---|
| | limite de profundidade (para não rodar para sempre) | |
| | tamanho do vetor `caminho` | |
| | | |

---

## Casos

| # | Caso | Tam. caminho | Entrada | Esperado | Obtido (primo) | Profundidade em que achou | Rodadas feitas | Aviso de transição? | Aviso de estouro? | OK? |
|---|---|---|---|---|---|---|---|---|---|---|
| 1 | estado inicial já é primo | | 2 | | | | | | | |
| 2 | borda inferior | | 1 | | | | | | | |
| 3 | borda superior | | 100 | | | | | | | |
| 4 | caso intermediário | | 10 | | | | | | | |
| 5 | vetor `caminho` menor que a profundidade necessária | | | | | | | | | |
| 6 | entrada inválida | | `abc`, `0`, `101` | | | | | | | |
| 7 | varredura | | 1 a 100 | | | | | | | |
| 8 | | | | | | | | | | |

---

## Comparação entre as três buscas

| Entrada | BFS (Tarefa 1) | Prof. limitada (Tarefa 2) | Iterativa (Tarefa 3) | Profundidade da iterativa | Observação |
|---|---|---|---|---|---|
| 10 | 13 | | | | |
| 100 | 97 | | | | |
| 1 | 11 | | | | |
| | | | | | |

Perguntas para a arguição:
- A iterativa encontra o mesmo primo que a BFS? Por quê?
- Quantas vezes o estado inicial é visitado no total? Isso é desperdício?
