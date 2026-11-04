
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "produto.h"
#include "parte2.h"

#define MAX_PRODUTOS 500

/* ============================================================
   PROTOTIPOS DAS FUNCOES DAS OUTRAS INTEGRANTES
   ============================================================ */

void listar_produtos(Produto v[], int quantidade);

int cadastrar_produto(
    Produto v[],
    int *quantidade,
    int *ordenado_por_codigo
);

void ordenar_por_preco(
    Produto v[],
    int n,
    int *ordenado_por_codigo
);

void listar_estoque_baixo(Produto v[], int n, int limite);

void comparar_ordenacoes(Produto v[], int n);

void comparar_buscas(Produto v[], int n);


/* ============================================================
   FUNCOES AUXILIARES
   ============================================================ */

/*
 * Limpa os caracteres restantes no buffer de entrada.
 */
void limpar_buffer(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        /* Continua limpando */
    }
}


/*
 * Verifica se o vetor esta efetivamente ordenado por codigo.
 *
 * Essa verificacao tambem protege o estado compartilhado
 * caso alguma funcao de comparacao utilize copias do vetor
 * e execute algoritmos de ordenacao nessas copias.
 */
int verificar_ordenacao_codigo(Produto v[], int n) {
    int i;

    if (n <= 1) {
        return 1;
    }

    for (i = 1; i < n; i++) {
        if (v[i - 1].codigo > v[i].codigo) {
            return 0;
        }
    }

    return 1;
}


/*
 * Exibe os resultados dos algoritmos de ordenacao.
 */
void exibir_estatisticas(
    Estatisticas est,
    const char *nome_algoritmo
) {
    printf("\n=========================================\n");
    printf("RESULTADOS: %s\n", nome_algoritmo);
    printf("=========================================\n");

    printf("Comparacoes: %ld\n", est.comparacoes);
    printf("Movimentacoes: %ld\n", est.movimentacoes);

    printf("=========================================\n");
}


/* ============================================================
   FUNCAO PRINCIPAL
   ============================================================ */

int main(void) {

    Produto produtos[MAX_PRODUTOS];

    int quantidade = 0;
    int opcao;

    /*
     * A variavel ordenado_por_codigo NAO e declarada novamente
     * aqui, pois ja esta definida globalmente em parte2.c.
     *
     * Ela e acessada por meio do extern declarado em parte2.h.
     */


    /* ========================================================
       INICIALIZACAO DOS PRODUTOS
       ======================================================== */

    /*
     * Inicialize aqui os 15 produtos padrao exigidos pelo
     * projeto, conforme os campos existentes em produto.h.
     *
     * Exemplo:
     *
     * produtos[0].codigo = 101;
     * strcpy(produtos[0].nome, "Teclado");
     *
     * Continue preenchendo os demais campos e produtos.
     *
     * Ao terminar a inicializacao, atualize:
     *
     * quantidade = 15;
     *
     * Se os produtos ja estiverem ordenados por codigo:
     *
     * ordenado_por_codigo = 1;
     *
     * Caso contrario:
     *
     * ordenado_por_codigo = 0;
     */


    /* ========================================================
       MENU PRINCIPAL
       ======================================================== */

    do {

        printf("\n=========================================\n");
        printf("       SISTEMA DE CATALOGO DE PRODUTOS\n");
        printf("=========================================\n");

        printf("1  - Listar produtos\n");
        printf("2  - Cadastrar produto\n");
        printf("3  - Busca sequencial por codigo\n");
        printf("4  - Busca sequencial por nome\n");
        printf("5  - Busca binaria por codigo\n");
        printf("6  - Ordenar por codigo (Selection Sort)\n");
        printf("7  - Ordenar por codigo (Insertion Sort)\n");
        printf("8  - Ordenar por codigo (Bubble Sort)\n");
        printf("9  - Ordenar por codigo (Merge Sort)\n");
        printf("10 - Ordenar produtos por preco\n");
        printf("11 - Exibir produtos com estoque baixo\n");
        printf("12 - Comparar algoritmos de ordenacao\n");
        printf("13 - Comparar metodos de busca\n");
        printf("0  - Sair\n");

        printf("\nOpcao: ");

        if (scanf("%d", &opcao) != 1) {

            printf("\nEntrada invalida! Digite um numero.\n");

            limpar_buffer();

            continue;
        }


        /* ====================================================
           PROCESSAMENTO DAS OPCOES
           ==================================================== */

        switch (opcao) {


            /* -----------------------------------------------
               OPCAO 1 - LISTAR PRODUTOS
               ----------------------------------------------- */

            case 1:

                listar_produtos(produtos, quantidade);

                break;


            /* -----------------------------------------------
               OPCAO 2 - CADASTRAR PRODUTO
               ----------------------------------------------- */

            case 2:

                if (quantidade >= MAX_PRODUTOS) {

                    printf("\nLimite maximo de produtos atingido!\n");

                } else {

                    /*
                     * Passa o endereco da variavel global
                     * para que a funcao de cadastro possa
                     * atualizar o estado da ordenacao.
                     */
                    cadastrar_produto(
                        produtos,
                        &quantidade,
                        &ordenado_por_codigo
                    );
                }

                break;


            /* -----------------------------------------------
               OPCAO 3 - BUSCA SEQUENCIAL POR CODIGO
               ----------------------------------------------- */

            case 3: {

                int codigo;
                int indice;

                printf("\nDigite o codigo para busca sequencial: ");

                if (scanf("%d", &codigo) != 1) {

                    printf("Codigo invalido!\n");

                    limpar_buffer();

                    break;
                }

                indice = busca_sequencial_codigo(
                    produtos,
                    quantidade,
                    codigo
                );

                break;
            }


            /* -----------------------------------------------
               OPCAO 4 - BUSCA SEQUENCIAL POR NOME
               ----------------------------------------------- */

            case 4: {

                char nome[60];
                int indice;

                printf("\nDigite o nome ou parte dele para busca: ");

                if (scanf(" %59[^\n]", nome) != 1) {

                    printf("Nome invalido!\n");

                    limpar_buffer();

                    break;
                }

                indice = busca_sequencial_nome(
                    produtos,
                    quantidade,
                    nome
                );

                break;
            }


            /* -----------------------------------------------
               OPCAO 5 - BUSCA BINARIA POR CODIGO
               ----------------------------------------------- */

            case 5: {

                int codigo;
                int indice;
                long comparacoes = 0;

                printf("\nDigite o codigo para busca binaria: ");

                if (scanf("%d", &codigo) != 1) {

                    printf("Codigo invalido!\n");

                    limpar_buffer();

                    break;
                }

                /*
                 * A propria funcao verifica se o vetor
                 * esta ordenado por codigo antes de executar.
                 *
                 * Se nao estiver, a busca sera bloqueada.
                 */
                indice = busca_binaria_codigo(
                    produtos,
                    quantidade,
                    codigo,
                    &comparacoes
                );

                break;
            }


            /* -----------------------------------------------
               OPCAO 6 - SELECTION SORT
               ----------------------------------------------- */

            case 6: {

                Estatisticas est;

                est = selection_sort(
                    produtos,
                    quantidade
                );

                exibir_estatisticas(
                    est,
                    "SELECTION SORT"
                );

                printf("\nVetor ordenado por codigo com sucesso!\n");

                break;
            }


            /* -----------------------------------------------
               OPCAO 7 - INSERTION SORT
               ----------------------------------------------- */

            case 7: {

                Estatisticas est;

                est = insertion_sort(
                    produtos,
                    quantidade
                );

                exibir_estatisticas(
                    est,
                    "INSERTION SORT"
                );

                printf("\nVetor ordenado por codigo com sucesso!\n");

                break;
            }


            /* -----------------------------------------------
               OPCAO 8 - BUBBLE SORT
               ----------------------------------------------- */

            case 8: {

                Estatisticas est;

                est = bubble_sort(
                    produtos,
                    quantidade
                );

                exibir_estatisticas(
                    est,
                    "BUBBLE SORT"
                );

                printf("\nVetor ordenado por codigo com sucesso!\n");

                break;
            }


            /* -----------------------------------------------
               OPCAO 9 - MERGE SORT
               ----------------------------------------------- */

            case 9: {

                Estatisticas est;

                est = merge_sort(
                    produtos,
                    quantidade
                );

                exibir_estatisticas(
                    est,
                    "MERGE SORT"
                );

                printf("\nVetor ordenado por codigo com sucesso!\n");

                break;
            }


            /* -----------------------------------------------
               OPCAO 10 - ORDENAR POR PRECO
               ----------------------------------------------- */

            case 10:

                ordenar_por_preco(
                    produtos,
                    quantidade,
                    &ordenado_por_codigo
                );

                /*
                 * Como o vetor foi organizado por preco,
                 * nao podemos garantir que continue ordenado
                 * por codigo.
                 */
                ordenado_por_codigo = 0;

                printf(
                    "\nEstado de ordenacao por codigo atualizado.\n"
                );

                break;


            /* -----------------------------------------------
               OPCAO 11 - PRODUTOS COM ESTOQUE BAIXO
               ----------------------------------------------- */

            case 11: {

                int limite;

                printf("\nInforme o estoque maximo para alerta: ");

                if (scanf("%d", &limite) != 1) {

                    printf("Limite invalido!\n");

                    limpar_buffer();

                    break;
                }

                listar_estoque_baixo(
                    produtos,
                    quantidade,
                    limite
                );

                break;
            }


            /* -----------------------------------------------
               OPCAO 12 - COMPARAR ALGORITMOS DE ORDENACAO
               ----------------------------------------------- */

            case 12: {

                comparar_ordenacoes(
                    produtos,
                    quantidade
                );

                /*
                 * Reconfere o vetor original.
                 *
                 * Isso evita que a ordenacao de copias
                 * utilizadas na comparacao altere
                 * incorretamente o estado global.
                 */
                ordenado_por_codigo =
                    verificar_ordenacao_codigo(
                        produtos,
                        quantidade
                    );

                break;
            }


            /* -----------------------------------------------
               OPCAO 13 - COMPARAR METODOS DE BUSCA
               ----------------------------------------------- */

            case 13: {

                comparar_buscas(
                    produtos,
                    quantidade
                );

                /*
                 * Garante que o estado global corresponda
                 * a organizacao real do vetor principal.
                 */
                ordenado_por_codigo =
                    verificar_ordenacao_codigo(
                        produtos,
                        quantidade
                    );

                break;
            }


            /* -----------------------------------------------
               OPCAO 0 - SAIR
               ----------------------------------------------- */

            case 0:

                printf("\nEncerrando o programa...\n");

                break;


            /* -----------------------------------------------
               OPCAO INVALIDA
               ----------------------------------------------- */

            default:

                printf("\nOpcao invalida! Tente novamente.\n");

                break;

        }

    } while (opcao != 0);


    return 0;
}
