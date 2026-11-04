#ifndef PARTE1_H
#define PARTE1_H

#include "produto.h"

void carregar_base_inicial(Produto v[], int *quantidade);
void listar_produtos(Produto v[], int quantidade);
int codigo_ja_existe(Produto v[], int quantidade, int codigo);
void cadastrar_produto(Produto v[], int *quantidade, int *ordenado_por_codigo);

#endif
