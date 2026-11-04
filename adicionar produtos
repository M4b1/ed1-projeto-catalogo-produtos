#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 500

typedef struct {
    int codigo;
    char nome[60];
    char categoria[30];
    float preco;
    int estoque;
} Produto;


int codigo_ja_existe(Produto v[], int n, int codigo) {
    for (int i = 0; i < n; i++) {
        if (v[i].codigo == codigo) {
            return 1; 
        }
    }
    return 0; 
}


void carregar_base_inicial(Produto v[], int *n) {
    Produto base[] = {
        {1042, "Teclado Mecanico", "Perifericos", 249.90f, 12},
        {1007, "Mouse Sem Fio", "Perifericos", 119.50f, 31},
        {1078, "Monitor 24", "Monitores", 899.00f, 8},
        {1015, "Cabo HDMI", "Cabos", 39.90f, 55},
        {1091, "SSD 1TB", "Armazenamento", 449.00f, 14},
        {1033, "Webcam Full HD", "Video", 189.90f, 9},
        {1064, "Headset USB", "Audio", 159.90f, 23},
        {1021, "Hub USB", "Acessorios", 89.90f, 17},
        {1085, "Memoria 16GB", "Memoria", 279.00f, 26},
        {1056, "Suporte Notebook", "Acessorios", 79.90f, 35},
        {1103, "Fonte 650W", "Energia", 389.00f, 7},
        {1011, "Adaptador Bluetooth", "Acessorios", 54.90f, 42},
        {1071, "HD Externo 2TB", "Armazenamento", 529.90f, 11},
        {1048, "Microfone USB", "Audio", 299.00f, 6},
        {1097, "Notebook Stand Pro", "Acessorios", 139.90f, 19}
    };

    *n = sizeof(base) / sizeof(base[0]);
    for (int i = 0; i < *n; i++) {
        v[i] = base[i];
    }
}


void listar_produtos(Produto v[], int n) {
    if (n == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\nCODIGO  %-25s %10s  %s\n", "NOME", "PRECO", "ESTOQUE");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-7d %-25.25s %10.2f  %7d\n",
               v[i].codigo, v[i].nome, v[i].preco, v[i].estoque);
    }
}


void cadastrar_produto(Produto v[], int *n, int *ordenado_por_codigo) {
    if (*n >= MAX_PRODUTOS) {
        printf("\nERRO: Capacidade maxima do catalogo atingida (%d produtos).\n", MAX_PRODUTOS);
        return;
    }

    int codigo;
    printf("\nCodigo: ");
    scanf("%d", &codigo);

    // Valida se o codigo ja existe
    if (codigo_ja_existe(v, *n, codigo)) {
        printf("ERRO: codigo de produto ja cadastrado.\n");
        return;
    }

    v[*n].codigo = codigo;

    printf("Nome: ");
    getchar(); // Limpa o buffer do teclado deixado pelo scanf anterior
    fgets(v[*n].nome, sizeof(v[*n].nome), stdin);
    v[*n].nome[strcspn(v[*n].nome, "\n")] = '\0'; 

    printf("Categoria: ");
    fgets(v[*n].categoria, sizeof(v[*n].categoria), stdin);
    v[*n].categoria[strcspn(v[*n].categoria, "\n")] = '\0';

    printf("Preco: ");
    scanf("%f", &v[*n].preco);

    printf("Estoque: ");
    scanf("%d", &v[*n].estoque);

    (*n)++;
    *ordenado_por_codigo = 0;
    printf("Produto cadastrado com sucesso!\n");
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int quantidade = 0;
    int ordenado_por_codigo = 0;
    int opcao = -1;

   
    carregar_base_inicial(produtos, &quantidade);

   
    while (opcao != 0) {
        printf("\n=========================================\n");
        printf("     SISTEMA DE CATALOGO DE PRODUTOS     \n");
        printf("=========================================\n");
        printf("1  - Listar produtos\n");
        printf("2  - Cadastrar produto\n");
        printf("3  - Busca sequencial por codigo\n");
        printf("4  - Busca sequencial por nome\n");
        printf("5  - Busca binaria por codigo\n");
        printf("6  - Ordenar por codigo - Selection Sort\n");
        printf("7  - Ordenar por codigo - Insertion Sort\n");
        printf("8  - Ordenar por codigo - Bubble Sort\n");
        printf("9  - Ordenar por codigo - Merge Sort\n");
        printf("10 - Ordenar produtos por preco\n");
        printf("11 - Exibir produtos com estoque baixo\n");
        printf("12 - Comparar algoritmos de ordenacao\n");
        printf("13 - Comparar metodos de busca\n");
        printf("0  - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listar_produtos(produtos, quantidade);
                break;

            case 2:
                cadastrar_produto(produtos, &quantidade, &ordenado_por_codigo);
                break;

            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                printf("\n[Funcionalidade em desenvolvimento pelo grupo]\n");
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    }

    return 0;
}
