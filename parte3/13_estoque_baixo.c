#include <stdio.h>
#include "parte3.h"

void listar_estoque_baixo(Produto v[], int n, int limite) {

    int i;
    int encontrou = 0;

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
