# IAC · Trabalho 1: Buscas não informadas

> ⚠️ **Conteúdo avaliado.** Inteligência Artificial Computacional, Prof. Alexandre Seidy Ioshisaqui, 2026.
> Enunciado: [`../trabalho-IA-01.pdf`](../trabalho-IA-01.pdf)
> Prazo final (código no Canvas **e** apresentação em aula prática): **09/10/2026**. Grupos de até 3 pessoas. Atraso desconta 0,5 pt por semana.

> 👥 **Integrantes do grupo:** para baixar o projeto e enviar alterações, leia o [`COMO_USAR_GITHUB.md`](COMO_USAR_GITHUB.md).

## Estrutura

```
trabalho_1_buscas/
├── .vscode/
│   ├── tasks.json              → compilar / compilar e executar (gcc)
│   ├── launch.json             → depurar com gdb (F5)
│   └── c_cpp_properties.json   → IntelliSense apontando para o gcc do sistema
├── src/           → código-fonte .c das três tarefas
├── testes/        → casos de teste e resultados observados
├── apresentacao/  → roteiro e anotações para a apresentação e a arguição
├── build/         → executáveis gerados (criada ao compilar; ignorada pelo git)
└── .gitignore
```

### `src/`
Código das três tarefas do enunciado:
1. busca em largura;
2. busca em profundidade limitada (recursiva);
3. busca em profundidade limitada iterativa.

⚠️ **Confirmar com o professor** se a entrega é um arquivo com as três buscas ou um arquivo por tarefa. Os dois formatos funcionam aqui, porque as tasks compilam o arquivo que estiver aberto.

### `testes/`
Casos para conferir o programa e mostrar na apresentação. Aguentar mudanças de parâmetros sem erro vale 2 pts. Casos que vale cobrir:
- diferentes tamanhos de vetor no `#define` (começando em 5);
- estados iniciais nas bordas (1, 2, 99, 100);
- estado inicial que já é primo;
- entradas inválidas;
- diferentes profundidades máximas.

Anote o que cada caso produziu, incluindo os avisos de estouro e de transição inválida.

### `apresentacao/`
Material de apoio para a apresentação, que vale 6 pts: roteiro, pontos que cada integrante precisa saber explicar e a lista de parâmetros que vocês vão alterar ao vivo.

## Como usar no VSCodium

```bash
codium 2_second_semester/computational_ai/projetos/trabalho_1_buscas
```

| Ação | Atalho |
|---|---|
| Compilar o `.c` aberto | `Ctrl+Shift+B` |
| Compilar e executar (terminal interativo, `scanf` funciona) | Terminal → Run Task → *Compilar e executar arquivo atual* |
| Depurar com breakpoints (bom para acompanhar a recursão) | `F5` |

O programa é compilado com `gcc -Wall -Wextra -g`. Trate os avisos (*warnings*) como erros a corrigir.

## Entrega (checklist)
- [ ] Grupo registrado no Canvas
- [ ] Código comentado e organizado, enviado no Canvas
- [ ] Apresentação feita em aula prática até 09/10

## Planejamento
As tarefas estão no Notion, no Projects Tracker, no projeto **IA Computacional — Trabalho 1 (Buscas)**.
