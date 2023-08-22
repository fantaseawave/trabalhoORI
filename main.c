#include <stdio.h>
#include "ArvB.h"

int main() {

  ArvB* arvore = arvB_cria();

  
    arvB_insere(arvore, 13);
    arvB_insere(arvore, 26);
    arvB_insere(arvore, 74);
    arvB_insere(arvore, 19);
    arvB_insere(arvore, 12);
    arvB_insere(arvore, 75);
    arvB_insere(arvore, 86);
    arvB_insere(arvore, 31);
    arvB_insere(arvore, 64);
    arvB_insere(arvore, 47);
    arvB_insere(arvore, 77);
    arvB_insere(arvore, 94);
    arvB_insere(arvore, 53);
    arvB_insere(arvore, 69);
    arvB_insere(arvore, 20);
    arvB_insere(arvore, 30);
    arvB_insere(arvore, 10);
    arvB_insere(arvore, 92);
    arvB_insere(arvore, 22);
    arvB_insere(arvore, 29);
    arvB_insere(arvore, 71);
    arvB_insere(arvore, 15);
    arvB_insere(arvore, 35);
    arvB_insere(arvore, 60);
    arvB_insere(arvore, 64);
    arvB_insere(arvore, 67);
  

  printf("Árvore B: \n");
  arvB_imprime(arvore);

  
  printf("\nQuantidade de nós: %d\n", arvB_qtd_nos(*arvore));
  printf("\nQuantidade de chaves: %d\n", arvB_qtd_chaves(*arvore));
  
  int valorBuscado = 29;

  
  if(arvB_busca(*arvore, valorBuscado)){
    printf("\nO valor %d se encontra na árvore!\n", valorBuscado);
  } else {
    printf("\nO valor %d não se encontra na árvore!\n", valorBuscado);
  }

  if(arvB_remove(arvore, valorBuscado)){
    printf("\nO valor %d foi removido da árvore!\n", valorBuscado);
    } else {
    printf("\nO valor %d não foi removido pois não foi encontrado na árvore!\n", valorBuscado);
  }

   if(arvB_busca(*arvore, valorBuscado)){
    printf("\nO valor %d se encontra na árvore!\n", valorBuscado);
  } else {
    printf("\nO valor %d não se encontra na árvore!\n", valorBuscado);
  }

  printf("\nQuantidade de nós: %d\n", arvB_qtd_nos(*arvore));
  printf("\nQuantidade de chaves: %d\n", arvB_qtd_chaves(*arvore));

  printf("\nÁrvore B final: \n");
  arvB_imprime(arvore);
  
  arvB_destroi(arvore);

  
}
