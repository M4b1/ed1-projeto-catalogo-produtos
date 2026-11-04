
#ifndef PARTE2_H
#define PARTE2_H

#include "produto.h"

/* Estatisticas dos algoritmos de ordenacao */
typedef struct {
    long comparacoes;
    long movimentacoes;
} Estatisticas;

/*
 * Estado compartilhado do vetor:
 * 0 = nao esta garantidamente ordenado por codigo
 * 1 = esta ordenado por codigo
 */
extern int ordenado_por_codigo;


/* ============================================================
   BUSCA SEQUENCIAL
   ============================================================ */

int busca_sequencial_codigo(
    Produto v[],
    int n,
    int codigo
);

int busca_sequencial_codigo_com_contagem(
    Produto v[],
    int n,
    int codigo,
    long *comparacoes
);

int busca_sequencial_nome(
    Produto v[],
    int n,
    char nome[]
);

int busca_sequencial_nome_com_contagem(
    Produto v[],
    int n,
    char nome[],
    long *comparacoes
);

int listar_busca_sequencial_nome(
    Produto v[],
    int n,
    char nome[],
    long *comparacoes
);


/* ============================================================
   ALGORITMOS DE ORDENACAO
   ============================================================ */

Estatisticas selection_sort(Produto v[], int n);

Estatisticas insertion_sort(Produto v[], int n);

Estatisticas bubble_sort(Produto v[], int n);

Estatisticas merge_sort(Produto v[], int n);


/* ============================================================
   FUNCOES AUXILIARES DO MERGE SORT
   ============================================================ */

void merge(
    Produto v[],
    Produto tmp[],
    int inicio,
    int meio,
    int fim,
    Estatisticas *est
);

void merge_sort_rec(
    Produto v[],
    Produto tmp[],
    int inicio,
    int fim,
    Estatisticas *est
);


/* ============================================================
   BUSCA BINARIA
   ============================================================ */

int busca_binaria_codigo(
    Produto v[],
    int n,
    int codigo,
    long *comparacoes
);


/* Atualiza o estado quando o vetor deixa de estar
   garantidamente ordenado por codigo. */
void marcar_desordenado_por_codigo(void);

#endif
