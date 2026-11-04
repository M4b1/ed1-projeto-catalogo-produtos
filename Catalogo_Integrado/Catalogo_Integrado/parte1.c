#include <stdio.h>
#include <string.h>
#include "produto.h"
#include "parte1.h"

#define MAX_PRODUTOS 500

/* Descarta os caracteres restantes da linha de entrada. */
static void limpar_linha_entrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        /* descarta */
    }
}

/* Carrega os 15 produtos iniciais fornecidos pelo grupo. */
void carregar_base_inicial(Produto v[], int *quantidade) {
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

    int total = (int)(sizeof(base) / sizeof(base[0]));
    int i;

    if (v == NULL || quantidade == NULL) {
        return;
    }

    for (i = 0; i < total; i++) {
        v[i] = base[i];
    }

    *quantidade = total;
}

/* Verifica se o codigo ja esta cadastrado. */
int codigo_ja_existe(Produto v[], int quantidade, int codigo) {
    int i;

    if (v == NULL || quantidade <= 0) {
        return 0;
    }

    for (i = 0; i < quantidade; i++) {
        if (v[i].codigo == codigo) {
            return 1;
        }
    }

    return 0;
}

/* Exibe todos os produtos cadastrados. */
void listar_produtos(Produto v[], int quantidade) {
    int i;

    if (v == NULL || quantidade <= 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\nCODIGO  %-25s %-18s %10s %8s\n",
           "NOME", "CATEGORIA", "PRECO", "ESTOQUE");
    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < quantidade; i++) {
        printf("%-7d %-25.25s %-18.18s R$ %7.2f %8d\n",
               v[i].codigo,
               v[i].nome,
               v[i].categoria,
               v[i].preco,
               v[i].estoque);
    }
}

/* Cadastra um produto novo no final do vetor. */
void cadastrar_produto(Produto v[], int *quantidade, int *ordenado_por_codigo) {
    int codigo;
    Produto novo;

    if (v == NULL || quantidade == NULL) {
        printf("\nErro interno: vetor ou quantidade invalida.\n");
        return;
    }

    if (*quantidade >= MAX_PRODUTOS) {
        printf("\nERRO: capacidade maxima de %d produtos atingida.\n", MAX_PRODUTOS);
        return;
    }

    printf("\nCodigo: ");
    if (scanf("%d", &codigo) != 1) {
        printf("Codigo invalido. Cadastro cancelado.\n");
        limpar_linha_entrada();
        return;
    }

    if (codigo_ja_existe(v, *quantidade, codigo)) {
        printf("Esse codigo ja esta cadastrado.\n");
        limpar_linha_entrada();
        return;
    }

    novo.codigo = codigo;

    /* Limpa o ENTER deixado pelo scanf do codigo. */
    limpar_linha_entrada();

    printf("Nome: ");
    if (fgets(novo.nome, sizeof(novo.nome), stdin) == NULL) {
        printf("Erro na leitura do nome. Cadastro cancelado.\n");
        return;
    }
    if (strchr(novo.nome, '\n') == NULL) {
        limpar_linha_entrada();
    }
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Categoria: ");
    if (fgets(novo.categoria, sizeof(novo.categoria), stdin) == NULL) {
        printf("Erro na leitura da categoria. Cadastro cancelado.\n");
        return;
    }
    if (strchr(novo.categoria, '\n') == NULL) {
        limpar_linha_entrada();
    }
    novo.categoria[strcspn(novo.categoria, "\n")] = '\0';

    printf("Preco: ");
    if (scanf("%f", &novo.preco) != 1 || novo.preco < 0.0f) {
        printf("Preco invalido. Cadastro cancelado.\n");
        limpar_linha_entrada();
        return;
    }

    printf("Estoque: ");
    if (scanf("%d", &novo.estoque) != 1 || novo.estoque < 0) {
        printf("Estoque invalido. Cadastro cancelado.\n");
        limpar_linha_entrada();
        return;
    }

    v[*quantidade] = novo;
    (*quantidade)++;

    /* Inserir no final nao garante ordem crescente por codigo. */
    if (ordenado_por_codigo != NULL) {
        *ordenado_por_codigo = 0;
    }

    printf("\nProduto cadastrado com sucesso!\n");
}
