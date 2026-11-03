#include <stdio.h>
#include <string.h>
#include "produto.h" // Inclui a struct e definições compartilhadas

#define MAX_PRODUTOS 500

// Protótipos das funções implementadas pelas integrantes (ajuste os nomes conforme necessário)
void listar_produtos(Produto v[], int quantidade);
int cadastrar_produto(Produto v[], int *quantidade, int *ordenado_por_codigo);
int busca_sequencial_codigo(Produto v[], int n, int codigo);
int busca_sequencial_nome(Produto v[], int n, char nome[]);
int busca_binaria_codigo(Produto v[], int n, int codigo);
void selection_sort(Produto v[], int n);
void insertion_sort(Produto v[], int n);
void bubble_sort(Produto v[], int n);
void merge_sort(Produto v[], int n);
void ordenar_por_preco(Produto v[], int n, int *ordenado_por_codigo);
void listar_estoque_baixo(Produto v[], int n, int limite);
void comparar_ordenacoes(Produto v[], int n);
void comparar_buscas(Produto v[], int n);

int main() {
    Produto produtos[MAX_PRODUTOS];
    int quantidade = 0;
    int ordenado_por_codigo = 0; // Controla se o vetor está ordenado por código (0 = não, 1 = sim)
    int opcao;

    // 1. Inicializar a base com os 15 produtos padrão exigidos pelo projeto
    // (Você pode preencher o vetor aqui ou chamar uma função de inicialização)
    
    do {
        printf("\n=========================================\n");
        printf("SISTEMA DE CATALOGO DE PRODUTOS\n");
        printf("=========================================\n");
        printf("1 - Listar produtos\n");
        printf("2 - Cadastrar produto\n");
        printf("3 - Busca sequencial por codigo\n");
        printf("4 - Busca sequencial por nome\n");
        printf("5 - Busca binaria por codigo\n");
        printf("6 - Ordenar por codigo (Selection Sort)\n");
        printf("7 - Ordenar por codigo (Insertion Sort)\n");
        printf("8 - Ordenar por codigo (Bubble Sort)\n");
        printf("9 - Ordenar por codigo (Merge Sort)\n");
        printf("10 - Ordenar produtos por preco\n");
        printf("11 - Exibir produtos com estoque baixo\n");
        printf("12 - Comparar algoritmos de ordenacao\n");
        printf("13 - Comparar metodos de busca\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            while (getchar() != '\n'); // Limpa o buffer
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
                scanf("%d", &codigo);
                busca_sequencial_codigo(produtos, quantidade, codigo);
                break;
            }
            case 4: {
                char nome[60];
                printf("Digite o nome (ou parte dele) para busca: ");
                scanf(" %[^\n]", nome);
                busca_sequencial_nome(produtos, quantidade, nome);
                break;
            }
            case 5: {
                // Validação obrigatória da pré-condição da busca binária[cite: 7]
                if (!ordenado_por_codigo) {
                    printf("Busca binaria indisponivel. O vetor precisa estar ordenado por codigo.\n");
                } else {
                    int codigo;
                    printf("Digite o codigo para busca binaria: ");
                    scanf("%d", &codigo);
                    busca_binaria_codigo(produtos, quantidade, codigo);
                }
                break;
            }
            case 6:
                selection_sort(produtos, quantidade);
                ordenado_por_codigo = 1; // Atualiza a flag de ordenação
                printf("Vetor ordenado por Selection Sort com sucesso!\n");
                break;
            case 7:
                insertion_sort(produtos, quantidade);
                ordenado_por_codigo = 1;
                printf("Vetor ordenado por Insertion Sort com sucesso!\n");
                break;
            case 8:
                bubble_sort(produtos, quantidade);
                ordenado_por_codigo = 1;
                printf("Vetor ordenado por Bubble Sort com sucesso!\n");
                break;
            case 9:
                merge_sort(produtos, quantidade);
                ordenado_por_codigo = 1;
                printf("Vetor ordenado por Merge Sort com sucesso!\n");
                break;
            case 10:
                ordenar_por_preco(produtos, quantidade, &ordenado_por_codigo);
                break;
            case 11: {
                int limite;
                printf("Informe o estoque maximo para alerta: ");
                scanf("%d", &limite);
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
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
