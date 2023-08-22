//
// Created by Felipe Rabelo on 14/08/23.
//

#ifndef ORITRABALHO_ARVB_H
#define ORITRABALHO_ARVB_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ordem 8
#define min_ordem (ordem/2) + (ordem%2)

typedef struct fila Fila;
typedef struct celula Celula;
typedef struct NO *ArvB;

struct NO {
    int qtd_chaves;
    int chaves[ordem - 1];
    struct NO *filhos[ordem];
    int folha;
};

struct celula {
    struct NO *conteudo;
    struct celula *prox;
};

struct fila {
    Celula *inicio;
    Celula *fim;
    int tam;
};

ArvB novo_no(int folha);

void arvB_destroi(ArvB *raiz);

int arvB_insere(ArvB* raiz, int valor);

void split(ArvB *raiz, ArvB filho, int ch);

int compare(const void *a, const void *b);

ArvB* arvB_cria();

void arvB_destroi(ArvB *raiz);

int arvB_busca(struct NO *raiz, int valor);

int arvB_qtd_nos(struct NO *raiz);

int arvB_qtd_chaves(struct NO *raiz);

Fila *cria_Fila();

void insere_Fila(Fila *q, struct NO *n);

struct NO *remove_Fila(Fila *q);

bool filaVazia(Fila *q);

Fila *liberaFila(Fila *q);

void concatenar_filhos(struct NO **no_pai, int pos);

void no_imprime(struct NO *no);

void arvB_imprime(ArvB *raiz);

void redistribuir_esquerdo(struct NO *no, int pos);

void redistribuir_direito(struct NO *no, int pos);

int arvB_remove(ArvB *raiz, int valor);

int pos_chave(struct NO *no, int valor);

void interno_remove(struct NO *no, int pos);

void folha_remove(struct NO *no, int pos);

int antecessor(struct NO *no, int pos);

int sucessor(struct NO *no, int pos);

void interno_remove(struct NO *no, int pos);

bool eFolha(struct NO* no);

void arvB_destroi(ArvB *raiz);

#endif //ORITRABALHO_ARVB_H
