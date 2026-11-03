
#include "parte2.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/* ============================================================
   VARIAVEL GLOBAL DE CONTROLE
   ============================================================ */

/*
 * Definida somente neste arquivo.
 *
 * Os demais arquivos acessam essa variavel por meio
 * da declaracao extern presente em parte2.h.
 */
int ordenado_por_codigo = 0;


/* ============================================================
   FUNCOES AUXILIARES
   ============================================================ */

/*
 * Verifica se um texto contem determinado trecho.
 *
 * A busca nao diferencia letras maiusculas de minusculas.
 *
 * Exemplo:
 * Nome cadastrado: "Adaptador USB-C"
 * Pesquisa: "usb"
 * Resultado: encontrado.
 */
static int contem_substring(
    const char *texto,
    const char *trecho
) {
    int i;
    int j;

    if (texto == NULL || trecho == NULL || trecho[0] == '\0') {
        return 0;
    }

    for (i = 0; texto[i] != '\0'; i++) {

        j = 0;

        while (
            texto[i + j] != '\0' &&
            trecho[j] != '\0' &&
            tolower((unsigned char) texto[i + j]) ==
            tolower((unsigned char) trecho[j])
        ) {
            j++;
        }

        if (trecho[j] == '\0') {
            return 1;
        }
    }

    return 0;
}


/*
 * Marca o vetor como nao ordenado por codigo.
 *
 * Deve ser chamada quando uma operacao altera a organizacao
 * do vetor sem preservar a ordem crescente dos codigos.
 */
void marcar_desordenado_por_codigo(void) {

    ordenado_por_codigo = 0;
}


/* ============================================================
   1. BUSCA SEQUENCIAL POR CODIGO
   ============================================================ */

/*
 * Busca um produto pelo seu codigo, percorrendo
 * o vetor do inicio ao fim.
 *
 * Retorno:
 * Indice do produto encontrado ou -1 caso nao exista.
 *
 * Contagem:
 * Cada verificacao de igualdade entre codigos
 * representa uma comparacao.
 */
int busca_sequencial_codigo_com_contagem(
    Produto v[],
    int n,
    int codigo,
    long *comparacoes
) {
    int i;

    if (comparacoes != NULL) {
        *comparacoes = 0;
    }

    if (v == NULL || n <= 0) {
        return -1;
    }

    for (i = 0; i < n; i++) {

        if (comparacoes != NULL) {
            (*comparacoes)++;
        }

        if (v[i].codigo == codigo) {
            return i;
        }
    }

    return -1;
}


/*
 * Funcao principal da busca sequencial por codigo.
 *
 * Exibe o resultado e a quantidade de comparacoes.
 */
int busca_sequencial_codigo(
    Produto v[],
    int n,
    int codigo
) {
    long comparacoes = 0;

    int indice = busca_sequencial_codigo_com_contagem(
        v,
        n,
        codigo,
        &comparacoes
    );

    printf("\n=========================================\n");
    printf("       BUSCA SEQUENCIAL POR CODIGO\n");
    printf("=========================================\n");

    if (indice != -1) {

        printf("Produto encontrado!\n");
        printf("Indice no vetor: %d\n", indice);
        printf("Codigo: %d\n", v[indice].codigo);
        printf("Nome: %s\n", v[indice].nome);

    } else {

        printf("Produto com codigo %d nao encontrado.\n", codigo);
    }

    printf("Comparacoes realizadas: %ld\n", comparacoes);

    return indice;
}


/* ============================================================
   2. BUSCA SEQUENCIAL POR NOME
   ============================================================ */

/*
 * Procura um trecho do nome dos produtos.
 *
 * A pesquisa pode localizar palavras ou partes de palavras.
 *
 * Retorno:
 * Indice da primeira ocorrencia ou -1 se nao encontrar.
 *
 * Contagem:
 * Cada produto examinado representa uma comparacao.
 * As comparacoes individuais entre caracteres da substring
 * nao sao contabilizadas separadamente.
 */
int busca_sequencial_nome_com_contagem(
    Produto v[],
    int n,
    char nome[],
    long *comparacoes
) {
    int i;

    if (comparacoes != NULL) {
        *comparacoes = 0;
    }

    if (
        v == NULL ||
        n <= 0 ||
        nome == NULL ||
        nome[0] == '\0'
    ) {
        return -1;
    }

    for (i = 0; i < n; i++) {

        if (comparacoes != NULL) {
            (*comparacoes)++;
        }

        if (contem_substring(v[i].nome, nome)) {
            return i;
        }
    }

    return -1;
}


/*
 * Funcao principal da busca sequencial por nome.
 *
 * Retorna o indice do primeiro produto encontrado.
 */
int busca_sequencial_nome(
    Produto v[],
    int n,
    char nome[]
) {
    long comparacoes = 0;

    int indice;

    if (nome == NULL || nome[0] == '\0') {

        printf("\nNome de pesquisa invalido!\n");

        return -1;
    }

    indice = busca_sequencial_nome_com_contagem(
        v,
        n,
        nome,
        &comparacoes
    );

    printf("\n=========================================\n");
    printf("        BUSCA SEQUENCIAL POR NOME\n");
    printf("=========================================\n");

    if (indice != -1) {

        printf("Produto encontrado!\n");
        printf("Indice no vetor: %d\n", indice);
        printf("Codigo: %d\n", v[indice].codigo);
        printf("Nome: %s\n", v[indice].nome);
        printf("Categoria: %s\n", v[indice].categoria);
        printf("Preco: R$ %.2f\n", v[indice].preco);
        printf("Estoque: %d\n", v[indice].estoque);

    } else {

        printf("Nenhum produto encontrado com o trecho \"%s\".\n", nome);
    }

    printf("Comparacoes realizadas: %ld\n", comparacoes);

    return indice;
}


/*
 * Funcao complementar para listar TODAS as ocorrencias
 * de um determinado trecho no nome dos produtos.
 *
 * Retorno:
 * Quantidade de produtos encontrados.
 *
 * Diferentemente da busca principal, esta funcao
 * percorre todo o vetor.
 */
int listar_busca_sequencial_nome(
    Produto v[],
    int n,
    char nome[],
    long *comparacoes
) {
    int i;
    int encontrados = 0;

    if (comparacoes != NULL) {
        *comparacoes = 0;
    }

    if (
        v == NULL ||
        n <= 0 ||
        nome == NULL ||
        nome[0] == '\0'
    ) {
        return 0;
    }

    printf("\n=========================================\n");
    printf("      RESULTADOS DA BUSCA POR NOME\n");
    printf("=========================================\n");

    for (i = 0; i < n; i++) {

        if (comparacoes != NULL) {
            (*comparacoes)++;
        }

        if (contem_substring(v[i].nome, nome)) {

            printf("\nProduto %d:\n", encontrados + 1);
            printf("Indice: %d\n", i);
            printf("Codigo: %d\n", v[i].codigo);
            printf("Nome: %s\n", v[i].nome);
            printf("Categoria: %s\n", v[i].categoria);
            printf("Preco: R$ %.2f\n", v[i].preco);
            printf("Estoque: %d\n", v[i].estoque);

            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum produto encontrado.\n");
    }

    printf("\nTotal de produtos encontrados: %d\n", encontrados);

    if (comparacoes != NULL) {
        printf("Comparacoes realizadas: %ld\n", *comparacoes);
    }

    return encontrados;
}


/* ============================================================
   3. SELECTION SORT
   ============================================================ */

/*
 * Ordena os produtos em ordem crescente de codigo.
 *
 * Funcionamento:
 * 1. Percorre o vetor procurando o menor codigo.
 * 2. Identifica a posicao do menor elemento.
 * 3. Troca esse elemento com o primeiro elemento
 *    da parte ainda nao ordenada.
 * 4. Repete o processo ate ordenar todo o vetor.
 *
 * Contagem de comparacoes:
 * Cada comparacao entre dois codigos e contabilizada.
 *
 * Contagem de movimentacoes:
 * Cada troca utiliza uma variavel auxiliar e equivale
 * a tres atribuicoes de registros.
 */
Estatisticas selection_sort(
    Produto v[],
    int n
) {
    Estatisticas est = {0, 0};

    int i;
    int j;
    int menor;

    Produto aux;

    if (n < 0 || (n > 0 && v == NULL)) {
        return est;
    }

    if (n <= 1) {
        ordenado_por_codigo = 1;
        return est;
    }

    for (i = 0; i < n - 1; i++) {

        menor = i;

        for (j = i + 1; j < n; j++) {

            est.comparacoes++;

            if (v[j].codigo < v[menor].codigo) {
                menor = j;
            }
        }

        /*
         * Troca somente quando o menor elemento
         * nao estiver na posicao correta.
         */
        if (menor != i) {

            aux = v[i];
            est.movimentacoes++;

            v[i] = v[menor];
            est.movimentacoes++;

            v[menor] = aux;
            est.movimentacoes++;
        }
    }

    ordenado_por_codigo = 1;

    return est;
}


/* ============================================================
   4. INSERTION SORT
   ============================================================ */

/*
 * Ordena os produtos em ordem crescente de codigo.
 *
 * Funcionamento:
 * 1. Considera o primeiro elemento como ordenado.
 * 2. Seleciona o proximo produto como chave.
 * 3. Desloca para a direita os produtos com codigos
 *    maiores que o codigo da chave.
 * 4. Insere a chave na posicao correta.
 *
 * Contagem de comparacoes:
 * Cada verificacao entre o codigo da chave e o codigo
 * do elemento anterior e contabilizada.
 *
 * Contagem de movimentacoes:
 * - Copia da chave para a variavel auxiliar;
 * - Deslocamentos dos produtos;
 * - Insercao da chave na posicao correta.
 */
Estatisticas insertion_sort(
    Produto v[],
    int n
) {
    Estatisticas est = {0, 0};

    int i;
    int j;

    Produto chave;

    if (n < 0 || (n > 0 && v == NULL)) {
        return est;
    }

    if (n <= 1) {
        ordenado_por_codigo = 1;
        return est;
    }

    for (i = 1; i < n; i++) {

        /*
         * Armazena o produto que sera inserido.
         */
        chave = v[i];
        est.movimentacoes++;

        j = i - 1;

        /*
         * Desloca os produtos maiores que a chave.
         */
        while (j >= 0) {

            est.comparacoes++;

            if (v[j].codigo > chave.codigo) {

                v[j + 1] = v[j];
                est.movimentacoes++;

                j--;

            } else {

                break;
            }
        }

        /*
         * Insere a chave na posicao correta.
         */
        v[j + 1] = chave;
        est.movimentacoes++;
    }

    ordenado_por_codigo = 1;

    return est;
}


/* ============================================================
   5. BUBBLE SORT
   ============================================================ */

/*
 * Ordena os produtos em ordem crescente de codigo.
 *
 * Funcionamento:
 * Compara elementos adjacentes e troca suas posicoes
 * quando estao fora de ordem.
 *
 * Otimizacao obrigatoria:
 * Se uma passagem completa nao realizar nenhuma troca,
 * significa que o vetor ja esta ordenado.
 * Nesse caso, o algoritmo encerra antecipadamente.
 *
 * Contagem de movimentacoes:
 * Cada troca equivale a tres atribuicoes.
 */
Estatisticas bubble_sort(
    Produto v[],
    int n
) {
    Estatisticas est = {0, 0};

    int i;
    int j;
    int trocou;

    Produto aux;

    if (n < 0 || (n > 0 && v == NULL)) {
        return est;
    }

    if (n <= 1) {
        ordenado_por_codigo = 1;
        return est;
    }

    trocou = 1;

    for (i = 0; i < n - 1 && trocou; i++) {

        trocou = 0;

        for (j = 0; j < n - 1 - i; j++) {

            est.comparacoes++;

            if (v[j].codigo > v[j + 1].codigo) {

                /*
                 * Primeira movimentacao:
                 * copia o primeiro produto para aux.
                 */
                aux = v[j];
                est.movimentacoes++;

                /*
                 * Segunda movimentacao:
                 * coloca o segundo produto na primeira posicao.
                 */
                v[j] = v[j + 1];
                est.movimentacoes++;

                /*
                 * Terceira movimentacao:
                 * coloca aux na segunda posicao.
                 */
                v[j + 1] = aux;
                est.movimentacoes++;

                trocou = 1;
            }
        }

        /*
         * Se trocou continuar igual a zero,
         * o laco externo sera encerrado.
         */
    }

    ordenado_por_codigo = 1;

    return est;
}


/* ============================================================
   6. MERGE SORT
   ============================================================ */

/*
 * Intercala duas partes do vetor que ja estao ordenadas.
 *
 * Primeira parte:
 * inicio ate meio.
 *
 * Segunda parte:
 * meio + 1 ate fim.
 *
 * Os elementos sao comparados e copiados para o vetor
 * temporario. Depois, retornam ao vetor original.
 *
 * Comparacoes:
 * Cada comparacao entre os codigos dos dois trechos.
 *
 * Movimentacoes:
 * Cada atribuicao de um Produto ao vetor temporario
 * e cada copia de volta ao vetor original.
 */
void merge(
    Produto v[],
    Produto tmp[],
    int inicio,
    int meio,
    int fim,
    Estatisticas *est
) {
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    /*
     * Intercala os dois trechos enquanto ambos
     * ainda possuirem elementos.
     */
    while (i <= meio && j <= fim) {

        est->comparacoes++;

        /*
         * Utiliza <= para preservar a estabilidade
         * do algoritmo quando os codigos forem iguais.
         */
        if (v[i].codigo <= v[j].codigo) {

            tmp[k] = v[i];
            i++;

        } else {

            tmp[k] = v[j];
            j++;
        }

        est->movimentacoes++;

        k++;
    }

    /*
     * Copia os elementos restantes da primeira metade.
     */
    while (i <= meio) {

        tmp[k] = v[i];

        est->movimentacoes++;

        i++;
        k++;
    }

    /*
     * Copia os elementos restantes da segunda metade.
     */
    while (j <= fim) {

        tmp[k] = v[j];

        est->movimentacoes++;

        j++;
        k++;
    }

    /*
     * Transfere os elementos intercalados
     * novamente para o vetor original.
     */
    for (i = inicio; i <= fim; i++) {

        v[i] = tmp[i];

        est->movimentacoes++;
    }
}


/*
 * Funcao recursiva do Merge Sort.
 *
 * Divide o vetor em duas metades ate que cada parte
 * possua apenas um elemento.
 *
 * Depois, utiliza merge() para intercalar as partes
 * em ordem crescente de codigo.
 */
void merge_sort_rec(
    Produto v[],
    Produto tmp[],
    int inicio,
    int fim,
    Estatisticas *est
) {
    int meio;

    if (inicio < fim) {

        meio = inicio + (fim - inicio) / 2;

        /*
         * Ordena a primeira metade.
         */
        merge_sort_rec(
            v,
            tmp,
            inicio,
            meio,
            est
        );

        /*
         * Ordena a segunda metade.
         */
        merge_sort_rec(
            v,
            tmp,
            meio + 1,
            fim,
            est
        );

        /*
         * Intercala as duas metades ordenadas.
         */
        merge(
            v,
            tmp,
            inicio,
            meio,
            fim,
            est
        );
    }
}


/*
 * Funcao principal do Merge Sort.
 *
 * Reserva memoria para um vetor temporario,
 * executa o algoritmo recursivo e libera a memoria.
 */
Estatisticas merge_sort(
    Produto v[],
    int n
) {
    Estatisticas est = {0, 0};

    Produto *tmp;

    if (n < 0 || (n > 0 && v == NULL)) {
        return est;
    }

    if (n <= 1) {
        ordenado_por_codigo = 1;
        return est;
    }

    /*
     * Aloca memoria para o vetor temporario.
     */
    tmp = (Produto *) malloc((size_t)n * sizeof(Produto));

    if (tmp == NULL) {

        fprintf(
            stderr,
            "\nErro: nao foi possivel alocar memoria para o Merge Sort.\n"
        );

        return est;
    }

    /*
     * Executa a ordenacao recursiva.
     */
    merge_sort_rec(
        v,
        tmp,
        0,
        n - 1,
        &est
    );

    /*
     * Libera a memoria utilizada.
     */
    free(tmp);

    /*
     * A ordenacao foi concluida com sucesso.
     */
    ordenado_por_codigo = 1;

    return est;
}


/* ============================================================
   7. BUSCA BINARIA POR CODIGO
   ============================================================ */

/*
 * Busca um produto por codigo utilizando busca binaria.
 *
 * Pre-condicao obrigatoria:
 * O vetor precisa estar ordenado em ordem crescente
 * de codigo.
 *
 * A verificacao e realizada por meio da variavel
 * ordenado_por_codigo.
 *
 * Retorno:
 * Indice do produto encontrado ou -1 se nao for encontrado
 * ou se a busca estiver indisponivel.
 *
 * Contagem:
 * Cada comparacao relacional entre codigos e contabilizada.
 *
 * Sao contabilizadas separadamente:
 * - Comparacao de igualdade;
 * - Comparacao de menor que.
 */
int busca_binaria_codigo(
    Produto v[],
    int n,
    int codigo,
    long *comparacoes
) {
    int inicio = 0;
    int fim = n - 1;
    int meio;

    long total_comparacoes = 0;

    if (comparacoes != NULL) {
        *comparacoes = 0;
    }

    /*
     * Verifica se a busca binaria esta liberada.
     */
    if (ordenado_por_codigo != 1) {

        printf("\n=========================================\n");
        printf("       BUSCA BINARIA INDISPONIVEL\n");
        printf("=========================================\n");

        printf(
            "O vetor nao esta ordenado por codigo.\n"
        );

        printf(
            "Execute uma ordenacao por codigo antes da busca.\n"
        );

        return -1;
    }

    if (v == NULL || n <= 0) {

        printf("\nNao existem produtos para pesquisar.\n");

        return -1;
    }

    /*
     * Executa a busca binaria.
     */
    while (inicio <= fim) {

        meio = inicio + (fim - inicio) / 2;

        /*
         * Primeira comparacao:
         * verifica se o codigo do meio e igual
         * ao codigo procurado.
         */
        total_comparacoes++;

        if (v[meio].codigo == codigo) {

            if (comparacoes != NULL) {
                *comparacoes = total_comparacoes;
            }

            printf("\n=========================================\n");
            printf("          BUSCA BINARIA\n");
            printf("=========================================\n");

            printf("Produto encontrado!\n");
            printf("Indice: %d\n", meio);
            printf("Codigo: %d\n", v[meio].codigo);
            printf("Nome: %s\n", v[meio].nome);
            printf("Categoria: %s\n", v[meio].categoria);
            printf("Preco: R$ %.2f\n", v[meio].preco);
            printf("Estoque: %d\n", v[meio].estoque);

            printf(
                "Comparacoes realizadas: %ld\n",
                total_comparacoes
            );

            return meio;
        }

        /*
         * Segunda comparacao:
         * verifica se o codigo do meio e menor
         * que o codigo procurado.
         */
        total_comparacoes++;

        if (v[meio].codigo < codigo) {

            inicio = meio + 1;

        } else {

            fim = meio - 1;
        }
    }

    /*
     * Produto nao encontrado.
     */
    if (comparacoes != NULL) {
        *comparacoes = total_comparacoes;
    }

    printf("\n=========================================\n");
    printf("          BUSCA BINARIA\n");
    printf("=========================================\n");

    printf("Produto com codigo %d nao encontrado.\n", codigo);

    printf(
        "Comparacoes realizadas: %ld\n",
        total_comparacoes
    );

    return -1;
}
