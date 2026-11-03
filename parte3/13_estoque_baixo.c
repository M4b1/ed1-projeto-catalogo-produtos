#include <stdio.h>
#include "parte3.h"

void listar_estoque_baixo(Produto produtos[], int quantidade, int limite) {

    int i;
    int encontrou = 0;

    printf("\nProdutos com estoque baixo:\n");

    for (i = 0; i < quantidade; i++) {

        if (produtos[i].estoque < limite) {

            printf("%d - %s - %d unidades\n",
                   produtos[i].codigo,
                   produtos[i].nome,
                   produtos[i].estoque);

            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhum produto com estoque baixo.\n");
    }
}
