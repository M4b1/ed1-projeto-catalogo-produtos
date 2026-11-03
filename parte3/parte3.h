#ifndef PARTE3_H
#define PARTE3_H

#include "../produto.h"

// Topico 9 - Ordenacao por preco
void ordenar_por_preco(Produto v[], int n, int *ordenado_por_codigo);

// Topico 11 - Comparacao das ordenacoes
void comparar_ordenacoes(Produto v[], int n);

// Topico 12 - Comparacao das buscas
void comparar_buscas(Produto v[], int n);

// Topico 13 - Relatorio de estoque baixo
void listar_estoque_baixo(Produto v[], int n, int limite);

#endif
