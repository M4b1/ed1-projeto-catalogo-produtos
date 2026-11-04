#include <stdio.h>
#include "produto.h"
#include "parte1.h"
#include "parte2.h"
#include "parte3.h"

#define MAX_PRODUTOS 500

/* Descarta o restante da linha quando uma entrada e invalida. */
static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta */
    }
}

/* Mostra as metricas retornadas pelos algoritmos de ordenacao. */
static void exibir_estatisticas(Estatisticas est, const char *nome) {
    printf("\n--- %s ---\n", nome);
    printf("Comparacoes: %ld\n", est.comparacoes);
    printf("Movimentacoes: %ld\n", est.movimentacoes);
}

int main(void) {
    Produto produtos[MAX_PRODUTOS];
    int quantidade = 0;
    int opcao = -1;

    /* Carrega os 15 produtos iniciais da Parte 1. */
    carregar_base_inicial(produtos, &quantidade);

    /* A base inicial fornecida nao esta em ordem crescente por codigo. */
    ordenado_por_codigo = 0;

    do {
        printf("\n=========================================\n");
        printf("       SISTEMA DE CATALOGO DE PRODUTOS\n");
        printf("=========================================\n");
        printf("1  - Listar produtos\n");
        printf("2  - Cadastrar produto\n");
        printf("3  - Busca sequencial por codigo\n");
        printf("4  - Busca sequencial por nome (parcial)\n");
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
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Digite um numero.\n");
            limpar_buffer();
            continue;
        }

        switch (opcao) {
            case 1:
                listar_produtos(produtos, quantidade);
                break;

            case 2:
                cadastrar_produto(produtos, &quantidade, &ordenado_por_codigo);
                break;

            case 3: {
                int codigo;
                printf("Digite o codigo para busca sequencial: ");
                if (scanf("%d", &codigo) != 1) {
                    printf("Codigo invalido.\n");
                    limpar_buffer();
                    break;
                }
                (void) busca_sequencial_codigo(produtos, quantidade, codigo);
                break;
            }

            case 4: {
                char nome[60];
                long comparacoes = 0;

                printf("Digite o nome ou parte dele para buscar: ");
                if (scanf(" %59[^\n]", nome) != 1) {
                    printf("Nome invalido.\n");
                    limpar_buffer();
                    break;
                }

                /* Lista todas as correspondencias parciais encontradas. */
                listar_busca_sequencial_nome(
                    produtos, quantidade, nome, &comparacoes
                );
                break;
            }

            case 5: {
                int codigo;
                long comparacoes = 0;

                if (!ordenado_por_codigo) {
                    printf("\nBusca binaria indisponivel.\n");
                    printf("Ordene primeiro o vetor por codigo (opcoes 6 a 9).\n");
                    break;
                }

                printf("Digite o codigo para busca binaria: ");
                if (scanf("%d", &codigo) != 1) {
                    printf("Codigo invalido.\n");
                    limpar_buffer();
                    break;
                }

                (void) busca_binaria_codigo(
                    produtos, quantidade, codigo, &comparacoes
                );
                break;
            }

            case 6: {
                Estatisticas est = selection_sort(produtos, quantidade);
                exibir_estatisticas(est, "SELECTION SORT");
                printf("Vetor ordenado por codigo.\n");
                break;
            }

            case 7: {
                Estatisticas est = insertion_sort(produtos, quantidade);
                exibir_estatisticas(est, "INSERTION SORT");
                printf("Vetor ordenado por codigo.\n");
                break;
            }

            case 8: {
                Estatisticas est = bubble_sort(produtos, quantidade);
                exibir_estatisticas(est, "BUBBLE SORT");
                printf("Vetor ordenado por codigo.\n");
                break;
            }

            case 9: {
                Estatisticas est = merge_sort(produtos, quantidade);
                exibir_estatisticas(est, "MERGE SORT");
                if (ordenado_por_codigo) {
                    printf("Vetor ordenado por codigo.\n");
                } else {
                    printf("Nao foi possivel concluir a ordenacao.\n");
                }
                break;
            }

            case 10:
                ordenar_por_preco(produtos, quantidade, &ordenado_por_codigo);
                break;

            case 11: {
                int limite;
                printf("Informe o limite de estoque: ");
                if (scanf("%d", &limite) != 1) {
                    printf("Limite invalido.\n");
                    limpar_buffer();
                    break;
                }
                listar_estoque_baixo(produtos, quantidade, limite);
                break;
            }

            case 12:
                comparar_ordenacoes(produtos, quantidade);
                break;

            case 13:
                comparar_buscas(produtos, quantidade);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
