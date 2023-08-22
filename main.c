#include <stdio.h>
#include "ArvB.h"

char posicao_alfabeto(char letra){
    return (letra-'a'+1);
}

int main() {

   
  char vetor1[] = {'o', 'k', 'i'};
  char vetor2[] = {'g', 'r', 'y'};   
  char vetor3[] = {'p', 'x', 'w', 'e', 'l', 'd', 'b'};
  char vetor4[] = {'j', 't'};
  char vetor5[] = {'m', 'v', 'z', 'h', 's', 'c'};
  char vetor6[] = {'q', 'u', 'n', 'f', 'a'};

  ArvB *arvore1 = arvB_cria();
  (*arvore1)->qtd_chaves = 1; //Não está sendo atribuido devido ao erro "member reference base type 'ArvB' (aka 'struct NO *') is not a structure or union"
  struct NO no1; 
  no1.qtd_chaves = 3;
  no1.chaves[0] = vetor3[0];
  no1.chaves[1] = vetor3[1];
  no1.chaves[2] = vetor3[2];

  //*arvore1 = &no1;


  /*for (int i = 0; i <= sizeof(vetor6); i++){
    arvB_insere(arvore1, posicao_alfabeto(vetor6[i]));
  }*/


  arvB_insere(arvore1, posicao_alfabeto(vetor3[0]));
  arvB_insere(arvore1, posicao_alfabeto(vetor3[1]));
  arvB_insere(arvore1, posicao_alfabeto(vetor3[2]));
  arvB_insere(arvore1, posicao_alfabeto(vetor3[3]));
  arvB_insere(arvore1, posicao_alfabeto(vetor3[4]));
  arvB_insere(arvore1, posicao_alfabeto(vetor3[5]));
  arvB_insere(arvore1, posicao_alfabeto(vetor3[6]));

    
    printf("Árvore B 1: \n");
    arvB_imprime(arvore1);
  
  
  printf("\nQuantidade de nós: %d\n", arvB_qtd_nos(*arvore1));
  printf("\nQuantidade de chaves: %d\n", arvB_qtd_chaves(*arvore1));
  
  int valorBuscado = posicao_alfabeto('l');
  
  if(arvB_busca(*arvore1, valorBuscado)){
    printf("\nO valor %d se encontra na árvore!\n", valorBuscado);
  } else {
    printf("\nO valor %d não se encontra na árvore!\n", valorBuscado);
  }


  if(arvB_remove(arvore1, valorBuscado)){
    printf("\nO valor %d foi removido da árvore!\n", valorBuscado);
    } else {
    printf("\nO valor %d não foi removido pois não foi encontrado na árvore!\n", valorBuscado);
  }

   if(arvB_busca(*arvore1, valorBuscado)){
    printf("\nO valor %d se encontra na árvore!\n", valorBuscado);
  } else {
    printf("\nO valor %d não se encontra na árvore!\n", valorBuscado);
  }

  printf("\nQuantidade de nós: %d\n", arvB_qtd_nos(*arvore1));
  printf("\nQuantidade de chaves: %d\n", arvB_qtd_chaves(*arvore1));

  printf("\nÁrvore B final 1: \n");
  arvB_imprime(arvore1);
  
  arvB_destroi(arvore1);

}