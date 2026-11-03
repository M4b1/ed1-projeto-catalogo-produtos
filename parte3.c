
#include <stdio.h>
#include "produto.h"
#include "parte2.h"
#include "parte3.h"

#define MAX_PRODUTOS 500


// TOPICO 9 - ORDENACAO POR PRECO

void ordenar_por_preco(Produto v[], int n, int *ordenado_por_codigo) {

    int i;
    int j;
    int menor;
    Produto aux;

    if (v == NULL || n <= 0) {
        printf("\nNao existem produtos para ordenar.\n");
        return;
    }

    // Procura o produto com menor preco
    for (i = 0; i < n - 1; i++) {

        menor = i;

        for (j = i + 1; j < n; j++) {

            if (v[j].preco < v[menor].preco) {
                menor = j;
            }
        }

        // Troca os produtos de posicao
        if (menor != i) {

            aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
        }
    }

    // O vetor agora esta ordenado por preco, nao por codigo
    if (ordenado_por_codigo != NULL) {
        *ordenado_por_codigo = 0;
    }

    marcar_desordenado_por_codigo();

    printf("\nProdutos ordenados por preco:\n");

    for (i = 0; i < n; i++) {
        printf("R$ %.2f - %s\n", v[i].preco, v[i].nome);
    }
}


// TOPICO 10 E 11 - ESTATISTICAS E COMPARACAO DAS ORDENACOES

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

    // Todos os algoritmos recebem os mesmos produtos
    for (i = 0; i < n; i++) {

        selection[i] = v[i];
        insertion[i] = v[i];
        bubble[i] = v[i];
        merge[i] = v[i];
    }

    // Executa os quatro algoritmos
    est_selection = selection_sort(selection, n);
    est_insertion = insertion_sort(insertion, n);
    est_bubble = bubble_sort(bubble, n);
    est_merge = merge_sort(merge, n);

    // Mostra os resultados
    printf("\n============================================\n");
    printf("     COMPARACAO DOS ALGORITMOS\n");
    printf("============================================\n");

    printf("%-15s %-15s %-15s\n",
           "Algoritmo", "Comparacoes", "Movimentacoes");

    printf("--------------------------------------------\n");

    printf("%-15s %-15ld %-15ld\n",
           "Selection", est_selection.comparacoes,
           est_selection.movimentacoes);

    printf("%-15s %-15ld %-15ld\n",
           "Insertion", est_insertion.comparacoes,
           est_insertion.movimentacoes);

    printf("%-15s %-15ld %-15ld\n",
           "Bubble", est_bubble.comparacoes,
           est_bubble.movimentacoes);

    printf("%-15s %-15ld %-15ld\n",
           "Merge", est_merge.comparacoes,
           est_merge.movimentacoes);

    printf("============================================\n");

    // Restaura a situacao original do vetor principal
    ordenado_por_codigo = estado_anterior;
}


// TOPICO 12 - COMPARACAO ENTRE AS BUSCAS

void comparar_buscas(Produto v[], int n) {

    Produto copia[MAX_PRODUTOS];

    int codigos[3];
    int indice_sequencial;
    int indice_binario;
    int i;

    long comp_sequencial;
    long comp_binaria;

    int estado_anterior = ordenado_por_codigo;

    const char *situacoes[3] = {
        "Produto proximo ao inicio",
        "Produto proximo ao final",
        "Produto inexistente"
    };

    if (v == NULL || n <= 0) {
        printf("\nNao existem produtos para pesquisar.\n");
        return;
    }

    if (n > MAX_PRODUTOS) {
        printf("\nQuantidade de produtos acima do limite.\n");
        return;
    }

    // Faz uma copia dos produtos
    for (i = 0; i < n; i++) {
        copia[i] = v[i];
    }

    // Ordena a copia para permitir a busca binaria
    merge_sort(copia, n);

    // Escolhe os tres codigos para os testes
    codigos[0] = copia[0].codigo;
    codigos[1] = copia[n - 1].codigo;
    codigos[2] = 9999;

    printf("\n============================================\n");
    printf("       COMPARACAO ENTRE AS BUSCAS\n");
    printf("============================================\n");

    for (i = 0; i < 3; i++) {

        comp_sequencial = 0;
        comp_binaria = 0;

        // Executa a busca sequencial
        indice_sequencial = busca_sequencial_codigo_com_contagem(
            v, n, codigos[i], &comp_sequencial
        );

        // Libera a busca binaria, pois a copia esta ordenada
        ordenado_por_codigo = 1;

        // Executa a busca binaria
        indice_binario = busca_binaria_codigo(
            copia, n, codigos[i], &comp_binaria
        );

        printf("\n--------------------------------------------\n");
        printf("Situacao: %s\n", situacoes[i]);
        printf("Codigo pesquisado: %d\n", codigos[i]);

        printf("\nBusca sequencial:\n");
        printf("Encontrado: %s\n",
               indice_sequencial != -1 ? "SIM" : "NAO");
        printf("Comparacoes: %ld\n", comp_sequencial);

        printf("\nBusca binaria:\n");
        printf("Encontrado: %s\n",
               indice_binario != -1 ? "SIM" : "NAO");
        printf("Comparacoes: %ld\n", comp_binaria);
    }

    // Restaura o estado anterior
    ordenado_por_codigo = estado_anterior;
}


// TOPICO 13 - RELATORIO DE ESTOQUE BAIXO

void listar_estoque_baixo(Produto v[], int n, int limite) {

    int i;
    int encontrou = 0;

    if (v == NULL || n <= 0) {
        printf("\nNao existem produtos cadastrados.\n");
        return;
    }

    printf("\nProdutos com estoque baixo:\n");

    for (i = 0; i < n; i++) {

        if (v[i].estoque < limite) {

            printf("%d - %s - %d unidades\n",
                   v[i].codigo,
                   v[i].nome,
                   v[i].estoque);

            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhum produto com estoque baixo.\n");
    }
}
