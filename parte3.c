#include <stdio.h>
#include "produto.h"
#include "parte2.h"
#include "parte3.h"

#define MAX_PRODUTOS 500

/* Verifica se uma copia esta ordenada crescentemente por codigo. */
static int esta_ordenado_por_codigo(const Produto v[], int n) {
    int i;

    if (v == NULL || n <= 1) {
        return 1;
    }

    for (i = 1; i < n; i++) {
        if (v[i - 1].codigo > v[i].codigo) {
            return 0;
        }
    }

    return 1;
}

/* Encontra um codigo que nao esteja presente no vetor. */
static int gerar_codigo_inexistente(Produto v[], int n) {
    int candidato = 0;
    int encontrou;
    int i;

    do {
        encontrou = 0;
        for (i = 0; i < n; i++) {
            if (v[i].codigo == candidato) {
                encontrou = 1;
                candidato++;
                break;
            }
        }
    } while (encontrou);

    return candidato;
}

/* ============================================================
   TOPICO 9 - ORDENACAO POR PRECO
   ============================================================ */

void ordenar_por_preco(Produto v[], int n, int *ordenado_por_codigo) {
    int i, j, menor;
    Produto aux;

    if (v == NULL || n <= 0) {
        printf("\nNao existem produtos para ordenar.\n");
        return;
    }

    /* Selection Sort por preco, em ordem crescente. */
    for (i = 0; i < n - 1; i++) {
        menor = i;

        for (j = i + 1; j < n; j++) {
            if (v[j].preco < v[menor].preco) {
                menor = j;
            }
        }

        if (menor != i) {
            aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
        }
    }

    if (ordenado_por_codigo != NULL) {
        *ordenado_por_codigo = 0;
    }
    marcar_desordenado_por_codigo();

    printf("\nProdutos ordenados por preco (crescente):\n");
    for (i = 0; i < n; i++) {
        printf("R$ %.2f - %s\n", v[i].preco, v[i].nome);
    }
}

/* ============================================================
   TOPICOS 10 E 11 - COMPARACAO DAS ORDENACOES
   ============================================================ */

void comparar_ordenacoes(Produto v[], int n) {
    Produto selection[MAX_PRODUTOS];
    Produto insertion[MAX_PRODUTOS];
    Produto bubble[MAX_PRODUTOS];
    Produto merge[MAX_PRODUTOS];

    Estatisticas est_selection;
    Estatisticas est_insertion;
    Estatisticas est_bubble;
    Estatisticas est_merge;

    int i;
    int estado_anterior = ordenado_por_codigo;

    if (v == NULL || n <= 0) {
        printf("\nNao existem produtos para comparar.\n");
        return;
    }

    if (n > MAX_PRODUTOS) {
        printf("\nQuantidade de produtos acima do limite.\n");
        return;
    }

    /* Cada algoritmo recebe exatamente a mesma copia inicial. */
    for (i = 0; i < n; i++) {
        selection[i] = v[i];
        insertion[i] = v[i];
        bubble[i] = v[i];
        merge[i] = v[i];
    }

    est_selection = selection_sort(selection, n);
    est_insertion = insertion_sort(insertion, n);
    est_bubble = bubble_sort(bubble, n);
    est_merge = merge_sort(merge, n);

    printf("\n========================================================\n");
    printf("             COMPARACAO DOS ALGORITMOS\n");
    printf("========================================================\n");
    printf("%-15s %-18s %-18s\n", "Algoritmo", "Comparacoes", "Movimentacoes");
    printf("--------------------------------------------------------\n");
    printf("%-15s %-18ld %-18ld\n", "Selection", est_selection.comparacoes, est_selection.movimentacoes);
    printf("%-15s %-18ld %-18ld\n", "Insertion", est_insertion.comparacoes, est_insertion.movimentacoes);
    printf("%-15s %-18ld %-18ld\n", "Bubble", est_bubble.comparacoes, est_bubble.movimentacoes);
    printf("%-15s %-18ld %-18ld\n", "Merge", est_merge.comparacoes, est_merge.movimentacoes);
    printf("========================================================\n");

    /* As ordenacoes foram feitas em copias: restaura o estado real. */
    ordenado_por_codigo = estado_anterior;
}

/* ============================================================
   TOPICO 12 - COMPARACAO ENTRE AS BUSCAS
   ============================================================ */

void comparar_buscas(Produto v[], int n) {
    Produto copia[MAX_PRODUTOS];
    int codigos[3];
    const char *situacoes[3] = {
        "Menor codigo existente",
        "Maior codigo existente",
        "Codigo inexistente"
    };

    int indice_sequencial;
    int indice_binario;
    int i;
    int estado_anterior = ordenado_por_codigo;
    long comp_sequencial;
    long comp_binaria;

    if (v == NULL || n <= 0) {
        printf("\nNao existem produtos para comparar.\n");
        return;
    }

    if (n > MAX_PRODUTOS) {
        printf("\nQuantidade de produtos acima do limite.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        copia[i] = v[i];
    }

    /* Ordena somente a copia, preservando o vetor principal. */
    merge_sort(copia, n);

    if (!esta_ordenado_por_codigo(copia, n)) {
        printf("\nNao foi possivel preparar a copia para a busca binaria.\n");
        ordenado_por_codigo = estado_anterior;
        return;
    }

    codigos[0] = copia[0].codigo;
    codigos[1] = copia[n - 1].codigo;
    codigos[2] = gerar_codigo_inexistente(v, n);

    printf("\n========================================================\n");
    printf("                COMPARACAO ENTRE AS BUSCAS\n");
    printf("========================================================\n");

    for (i = 0; i < 3; i++) {
        comp_sequencial = 0;
        comp_binaria = 0;

        indice_sequencial = busca_sequencial_codigo_com_contagem(
            v, n, codigos[i], &comp_sequencial
        );

        /* A busca binaria trabalha com a copia ordenada. */
        ordenado_por_codigo = 1;
        indice_binario = busca_binaria_codigo(
            copia, n, codigos[i], &comp_binaria
        );

        printf("\n--------------------------------------------------------\n");
        printf("Situacao: %s\n", situacoes[i]);
        printf("Codigo pesquisado: %d\n", codigos[i]);
        printf("Busca sequencial: %s | Comparacoes: %ld\n",
               indice_sequencial != -1 ? "Encontrado" : "Nao encontrado",
               comp_sequencial);
        printf("Busca binaria:    %s | Comparacoes: %ld\n",
               indice_binario != -1 ? "Encontrado" : "Nao encontrado",
               comp_binaria);
    }

    /* Restaura a flag do vetor principal, que nao foi alterado. */
    ordenado_por_codigo = estado_anterior;
}

/* ============================================================
   TOPICO 13 - RELATORIO DE ESTOQUE BAIXO
   ============================================================ */

void listar_estoque_baixo(Produto v[], int n, int limite) {
    int i;
    int encontrou = 0;

    if (v == NULL || n <= 0) {
        printf("\nNao existem produtos cadastrados.\n");
        return;
    }

    printf("\nProdutos com estoque menor que %d:\n", limite);

    for (i = 0; i < n; i++) {
        if (v[i].estoque < limite) {
            printf("%d - %s - %d unidades\n",
                   v[i].codigo, v[i].nome, v[i].estoque);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum produto com estoque baixo.\n");
    }
}
