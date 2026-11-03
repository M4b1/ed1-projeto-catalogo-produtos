#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int codigo;
    char nome[60];
    char categoria[30];
    float preco;
    int estoque;
} Produto;

#endif
