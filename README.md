# IAC · Trabalho 1: Buscas não informadas

> Inteligência Artificial Computacional, Prof. Alexandre Seidy Ioshisaqui, 2026.
> Prazo final (código no Canvas **e** apresentação em aula prática): **09/10/2026**.
## Estrutura

```
IA-Computacional-Trabalho-1-Buscas-/
├── .vscode/
│   ├── tasks.json              → compilar / compilar e executar (gcc)
│   ├── launch.json             → depurar com gdb (F5)
│   └── c_cpp_properties.json   → IntelliSense apontando para o gcc do sistema
├── src/           → código-fonte .c das três tarefas
├── testes/        → casos de teste e resultados observados
├── apresentacao/  → roteiro e anotações para a apresentação e a arguição
├── build/         → executáveis gerados (criada ao compilar; ignorada pelo git)
├── README.md      → este arquivo
├── guide_github.md → como baixar, trabalhar e enviar alterações pelo GitHub
└── .gitignore
```

### `src/`
Código das três tarefas do enunciado:
1. busca em largura;
2. busca em profundidade limitada (recursiva);
3. busca em profundidade limitada iterativa.

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

## Planejamento
A organização e tarefas foram feitas no Notion.
