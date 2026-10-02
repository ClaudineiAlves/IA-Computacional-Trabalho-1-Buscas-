# Tarefa 1 · Busca em largura

Arquivo testado: `src/main.c` · compilado com `gcc -Wall -Wextra`

**Como preencher:** escreva o **Esperado** *antes* de rodar e só depois o **Obtido**. Diferenças entre os dois são assunto para a arguição.
Saídas completas (opcional) vão em `saidas/` com o nome `t1_tam<TAM>_n<entrada>.txt`, por exemplo:

```bash
echo 10 | ./build/main > testes/saidas/t1_tam5_n10.txt
```

---

## Parte 1: BFS com vetores e `#define`

Rodado em 01/10/2026.

| # | Caso | TAM_VETOR | Entrada | Esperado | Obtido | OK? |
|---|---|---|---|---|---|---|
| 1 | estado inicial já é primo | 5 | 2 | | 2, na 1ª visita | ✅ |
| 2 | borda inferior | 5 | 1 | | 11, 6 visitas | ✅ |
| 3 | borda superior | 5 | 99 | | 97, 2 visitas | ✅ |
| 4 | borda superior | 5 | 100 | | 97, 17 visitas | ✅ |
| 5 | caso intermediário | 5 | 10 | | 13, 5 visitas (10 → 8 → 15 → 6 → 13); o 13 repetido foi ignorado | ✅ |
| 6 | entradas inválidas | 5 | `abc`, `0`, `-3`, `101`, depois `4` | | pediu o número 4 vezes e depois buscou a partir de 4 | ✅ |
| 7 | comparação com a versão de sala | 5 | 1 a 100 | | mesmo primo da versão de sala nos 100 casos | ✅ |
| 8 | varredura | 2 | 1 a 100 | | encontrou primo em 100/100 | ✅ |
| 9 | varredura | 10 | 1 a 100 | | encontrou primo em 100/100 | ✅ |
| 10 | varredura | 50 | 1 a 100 | | encontrou primo em 100/100 | ✅ |
| 11 | fila mínima | 1 | 1 | | **não termina**: visita 1, −1, −3, −5, … | ❌ → resolver na Parte 2 |
| 12 | fila mínima, demais estados | 1 | 2 a 100 | | encontrou primo nos 99 | ✅ |

**Por que o caso 11 falha:** com um só espaço na fila, só o filho da esquerda (−2) entra, e nada impede a busca de sair do intervalo 1–100. A validação de transição da Parte 2 deve fazer o −1 ser barrado, a fila esvaziar e o programa terminar com "nenhum primo encontrado". Rodar de novo depois da Parte 2 e atualizar esta linha.

**Previsão do grupo para o tamanho 5** (anotar antes de rodar, como pede a tarefa):

>

---

## Parte 2: validação de transição e aviso de estouro

Rodado em: __/__/2026

| # | Caso | TAM_VETOR | Entrada | Esperado | Obtido | Aviso de transição? | Aviso de estouro? | OK? |
|---|---|---|---|---|---|---|---|---|
| 1 | filho abaixo de 1 | 5 | 1 | | | | | |
| 2 | filho abaixo de 1 | 5 | 2 | | | | | |
| 3 | filho acima de 100 | 5 | 96 | | | | | |
| 4 | filho acima de 100 | 5 | 100 | | | | | |
| 5 | caso 11 da Parte 1 refeito | 1 | 1 | | | | | |
| 6 | fila pequena | 2 | 100 | | | | | |
| 7 | fila pequena | 3 | 100 | | | | | |
| 8 | candidato a estouro | 5 | 90 | | | | | |
| 9 | candidato a estouro | 5 | 98 | | | | | |
| 10 | fila grande, sem estouro | 20 | 100 | | | | | |
| 11 | varredura | 5 | 1 a 100 | | | | | |
| 12 | | | | | | | | |

Perguntas para fechar a Parte 2:
- O aviso aparece **no final**, como pede o enunciado, mesmo quando um primo foi encontrado?
- O visitados também pode encher. O grupo considera isso estouro de memória? Registrar a decisão aqui.
