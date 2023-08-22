//
// Created by Felipe Rabelo on 14/08/23.
//

#include "ArvB.h"


int pos_chave(struct NO *no, int valor) {
    int i = 0;
    while (i < no->qtd_chaves && no->chaves[i] < valor) {
        i++;
    }
    return i;
}

int antecessor(struct NO *no, int pos) {
    if (!eFolha(no)) {
        struct NO *aux = no->filhos[pos]; //subárvore esquerda
        while (!eFolha(aux)) {
            aux = aux->filhos[aux->qtd_chaves - 1];
        }
        return aux->chaves[aux->qtd_chaves - 1];
    } else {
        if (pos != 0) {
            return no->chaves[pos - 1];
        } else {
            return no->chaves[pos];
        }
    }
}

int sucessor(struct NO *no, int pos) {
    if (!eFolha(no)) {
        struct NO *aux = no->filhos[pos + 1];
        while (!eFolha(aux)) {
            aux = aux->filhos[0];
        }
        return aux->chaves[0];
    } else {
        if (pos != no->qtd_chaves - 1) {
            return no->chaves[pos + 1];
        } else {
            return no->chaves[pos];
        }
    }
}

void folha_remove(struct NO *no, int pos) {
    for (int i = pos; i < no->qtd_chaves - 1; i++) {
        no->chaves[i] = no->chaves[i + 1];
    }
    no->qtd_chaves--;
}

void concatenar_filhos(struct NO **no_pai, int pos) {
    struct NO *no = *(no_pai);
    struct NO *filho_anterior = no->filhos[pos];
    struct NO *filho_posterior = no->filhos[pos + 1];
    filho_anterior->chaves[filho_anterior->qtd_chaves] = no->chaves[pos];
    filho_anterior->qtd_chaves++;
    for (int i = 0; i < filho_posterior->qtd_chaves; i++) {
        filho_anterior->chaves[filho_anterior->qtd_chaves + i] = filho_posterior->chaves[i];
    }
    if (!eFolha(filho_anterior)) {
        for (int i = 0; i <= filho_posterior->qtd_chaves; i++) {
            filho_anterior->filhos[filho_anterior->qtd_chaves + i] = filho_posterior->filhos[i];
        }
    }
    filho_anterior->qtd_chaves += filho_posterior->qtd_chaves;
    for (int i = pos; i < no->qtd_chaves - 1; i++) {
        no->chaves[i] = no->chaves[i + 1];
        no->filhos[i + 1] = no->filhos[i + 2];
    }
    no->qtd_chaves--;
    free(filho_posterior);
    if (no->qtd_chaves == 0) {
        *no_pai = filho_anterior;
    }
}

void redistribuir_esquerdo(struct NO *no, int pos) {
    struct NO *filho_atual = no->filhos[pos];
    struct NO *irmao_anterior = no->filhos[pos - 1];
    for (int i = filho_atual->qtd_chaves - 1; i >= 0; i--) {
        filho_atual->chaves[i + 1] = filho_atual->chaves[i];
    }
    if (!eFolha(filho_atual)) {
        for (int i = filho_atual->qtd_chaves; i >= 0; i++) {
            filho_atual->filhos[i + 1] = filho_atual->filhos[i];
        }
    }
    filho_atual->qtd_chaves++;
    filho_atual->chaves[0] = no->chaves[pos - 1];
    if (!eFolha(filho_atual)) {
        filho_atual->filhos[0] = irmao_anterior->filhos[irmao_anterior->qtd_chaves - 1];
    }
    no->chaves[pos - 1] = irmao_anterior->chaves[irmao_anterior->qtd_chaves - 1];
    irmao_anterior->qtd_chaves--;
}

void redistribuir_direito(struct NO *no, int pos) {
    struct NO *filho_atual = no->filhos[pos];
    struct NO *irmao_posterior = no->filhos[pos + 1];
    filho_atual->chaves[filho_atual->qtd_chaves] = no->chaves[pos];
    filho_atual->qtd_chaves++;
    if (!eFolha(filho_atual)) {
        filho_atual->filhos[filho_atual->qtd_chaves] = irmao_posterior->filhos[0];
    }
    no->chaves[pos] = irmao_posterior->chaves[0];
    for (int i = 1; i < irmao_posterior->qtd_chaves; i++) {
        irmao_posterior->chaves[i - 1] = irmao_posterior->chaves[i];
    }
    if (!eFolha(irmao_posterior)) {
        for (int i = 0; i <= irmao_posterior->qtd_chaves; i++) {
            irmao_posterior->filhos[i - 1] = irmao_posterior->filhos[i];
        }
    }
    irmao_posterior->qtd_chaves--;
}

void interno_remove(struct NO *no, int pos) {
    int aux;
    if (no->filhos[pos]->qtd_chaves > min_ordem - 1) {
        aux = antecessor(no, pos);
        arvB_remove(&no->filhos[pos], aux);
        no->chaves[pos] = aux;
    } else if (no->filhos[pos + 1]->qtd_chaves > min_ordem - 1) {
        aux = sucessor(no, pos);
        arvB_remove(&no->filhos[pos], aux);
        no->chaves[pos] = aux;
    } else {
        aux = no->chaves[pos];
        concatenar_filhos(&no, pos);
        arvB_remove(&no->filhos[pos], aux);
    }
}

int arvB_remove(ArvB *raiz, int valor) {
    struct NO *aux = *raiz;
    int pos = pos_chave(aux, valor);
    if (pos < aux->qtd_chaves && aux->chaves[pos] == valor) {
        if (eFolha(aux)) {
            folha_remove(aux, pos);
        } else {
            interno_remove(aux, pos);
        }
        if(aux->qtd_chaves == 0){
            free(aux);
        }
        return 1;
    }
    if (eFolha(aux)) {
        printf("Não existe a chave requisitada dentro da árvore.\n");
        return 0;
    }
    if (aux->filhos[pos]->qtd_chaves < min_ordem) {
        if (pos > 0 && aux->filhos[pos - 1]->qtd_chaves > min_ordem - 1) {
            redistribuir_esquerdo(aux, pos);
            return arvB_remove(&aux->filhos[pos], valor);
        }
        if (pos < aux->qtd_chaves - 1 && aux->filhos[pos + 1]->qtd_chaves > min_ordem - 1) {
            redistribuir_direito(aux, pos);
            return arvB_remove(&aux->filhos[pos], valor);
        }
        if (pos < aux->qtd_chaves - 1 || aux->qtd_chaves == 1) {
            concatenar_filhos(raiz, pos);
            return arvB_remove(&aux->filhos[pos], valor);
        }
        concatenar_filhos(raiz, pos - 1);
        return arvB_remove(&aux->filhos[pos - 1], valor);
    }
    return arvB_remove(&aux->filhos[pos], valor);
}

void no_imprime(struct NO *no) {
    for (int i = 0; i < no->qtd_chaves; i++) {
        printf("%d ", no->chaves[i]);
    }
    printf("\t\t");
}

void arvB_imprime(ArvB *raiz) {
    if (*raiz == NULL) {
        printf("Árvore vazia. \n");
    }
    Fila *q = cria_Fila();
    insere_Fila(q, *raiz);
    while (!filaVazia(q)) {
        struct NO *no = remove_Fila(q);
        no_imprime(no);
        if (!eFolha(no)) {
            for (int i = 0; i <= no->qtd_chaves; i++) {
                insere_Fila(q, no->filhos[i]);
            }
        }
    }
    printf("\n");
    liberaFila(q);
}

Fila *cria_Fila() {
    Fila *q;
    q = (Fila *) malloc(sizeof(Fila));
    q->inicio = NULL;
    q->fim = NULL;
    q->tam = 0;
    return q;
}

void insere_Fila(Fila *q, struct NO *n) {
    Celula *nova;
    nova = (Celula *) malloc(sizeof(Celula));
    nova->conteudo = n;
    nova->prox = NULL;
    if (q->fim == NULL) {
        q->inicio = nova;
        q->fim = nova;
    } else {
        q->fim->prox = nova;
        q->fim = nova;
    }
    q->tam++;
}

struct NO *remove_Fila(Fila *q) {
    struct NO *no;
    Celula *removida;
    removida = q->inicio;
    no = removida->conteudo;
    q->inicio = removida->prox;
    if (q->inicio == NULL) {
        q->fim = NULL;
    }
    free(removida);
    q->tam--;
    return no;
}

bool filaVazia(Fila *q) {
    return (q->fim == NULL);
}

Fila *liberaFila(Fila *q) {
    Celula *p, *morta;
    p = q->inicio;
    while (p != NULL) {
        morta = p;
        p = p->prox;
        free(morta);
    }
    free(q);
    return NULL;
}


void arvB_destroi (ArvB *raiz) {
    struct NO *aux = *raiz;
    if(aux != NULL){
        for(int i = 0; i<aux->qtd_chaves; i++){
            arvB_destroi(&aux->filhos[i]);
        }
        free(aux);
    }
}

/********/

ArvB *arvB_cria(){
    ArvB* arv = (ArvB*)malloc(sizeof(ArvB));
    //arv->qtd_chaves = 0;  
    if (arv != NULL){
        *arv = NULL;
    }
    return arv;
}


ArvB novo_no(int folha) {
    ArvB no = (ArvB)malloc(sizeof(struct NO));
    if (no != NULL) {
        no->qtd_chaves = 0;
        no->folha = folha;
        for (int i = 0; i < ordem; i++) {
            no->filhos[i] = NULL;
            no->chaves[i] = 0;
        }
    }
    return no;
}





int arvB_busca(struct NO *raiz, int valor){
    if (raiz == NULL){
        return 0;
    }

    int i = 0; 

    while (i < raiz->qtd_chaves && valor > raiz->chaves[i]){
        i++;  
    } 

    if (i < raiz->qtd_chaves && valor == raiz->chaves[i]){
        return 1;
    } else if (raiz->folha){
        return 0; 
    } else {
        return arvB_busca(raiz->filhos[i], valor);
    }
}


int arvB_qtd_nos(struct NO* raiz){
    if (raiz == NULL){
        return 0;
    } 

    int qtd_nos = 1;
    for (int i = 0; i <= raiz->qtd_chaves; i++){
        qtd_nos += arvB_qtd_nos(raiz->filhos[i]);
    }
    return qtd_nos;
}

int arvB_qtd_chaves(struct NO *raiz){
    if (raiz == NULL){
        return 0;
    }

    int qtd_chaves = raiz->qtd_chaves;
    for (int i = 1; i <= qtd_chaves; i++){
        qtd_chaves += arvB_qtd_chaves(raiz->filhos[i]); 
    }
    return qtd_chaves;
}

/**************************/

int arvB_insere(ArvB* raiz, int valor) {

   if (raiz==NULL) {
      return 0;
   }

   struct NO* novo;
   novo = (struct NO*)malloc(sizeof(struct NO));
   novo->chaves[novo->qtd_chaves] = valor;
   novo->qtd_chaves++;

   if (novo==NULL) {
      return 0;
   }

   if (*raiz==NULL) {
      *raiz = novo;
      return 1;
   }

   int posicao = 0;
   struct NO* p = *raiz;

   // a chave sera inserida num no folha, entao procura ele
   if (!eFolha(p)) {
      while (!eFolha(p)) {
         posicao = 0;
         while (p->chaves[posicao]<valor && posicao<p->qtd_chaves) {
            posicao++;
         }
         p = p->filhos[p->filhos[posicao]==NULL ? posicao - 1 : posicao];
      }
   }

   // se o no folha encontrado estiver cheio, ele eh particionado
   if (p->qtd_chaves==ordem-1) {
      split(raiz, p, valor);
   } else {
      // senao, apenas insere a chave
      p->chaves[p->qtd_chaves] = valor;
      p->qtd_chaves++;
      qsort(p->chaves, p->qtd_chaves, sizeof(int), compare);
   }

   return 1;

}

void split(ArvB *raiz, ArvB filho, int ch) {

   bool encontrou = false;
   struct NO *novo1, *novo2, *p = *raiz;
   int posicaoFilho, posicaoNovo, posicaoNovosFilhos, posicaoP, posicaoPai, separador;

   novo1 = (struct NO*)malloc(sizeof(struct NO));
   novo2 = (struct NO*)malloc(sizeof(struct NO));

   // problema na alocacao dos novos nos
   if (novo1==NULL || novo2==NULL) {
      return;
   }

   novo1->qtd_chaves = 0;
   novo2->qtd_chaves = 0;

   // separa as chaves do no filho:
   // a primeira metade vai pra novo1
   for (int i=0, j=0; i<=(filho->qtd_chaves)/2; i++, j++) {
      novo1->chaves[j] = filho->chaves[i];
      novo1->qtd_chaves++;
   }
   // e a segunda metade vai pra novo2
   for (int j=0, i = (filho->qtd_chaves)/2+1; i<filho->qtd_chaves; i++, j++) {
      novo2->chaves[j] = filho->chaves[i];
      novo2->qtd_chaves++;
   }

   posicaoNovo = 0;
   // insere a nova chave ch no novo1 se ela for menor que a menor chave de novo2
   if (ch<novo1->chaves[novo1->qtd_chaves-1]) {
      novo1->chaves[novo1->qtd_chaves] = ch;
      novo1->qtd_chaves++;
      qsort(novo1->chaves, novo1->qtd_chaves, sizeof(int), compare);
   } else {
      // insere a nova chave ch no novo2 se ela for maior ou igual que a menor chave de novo2
      novo2->chaves[novo2->qtd_chaves] = ch;
      novo2->qtd_chaves++;
      qsort(novo2->chaves, novo2->qtd_chaves, sizeof(int), compare);
   }

   // define o separador e remove ele do no escolhido, dependendendo da quantidade de chaves dos novos nos
   if (novo1->qtd_chaves<novo2->qtd_chaves) {
      separador = novo2->chaves[0];
      novo2->chaves[0] = novo2->chaves[novo2->qtd_chaves-1];
      novo2->chaves[novo2->qtd_chaves-1] = 0;
      novo2->qtd_chaves--;
      qsort(novo2->chaves, novo2->qtd_chaves, sizeof(int), compare);
   } else {
      separador = novo1->chaves[novo1->qtd_chaves-1];
      novo1->chaves[novo1->qtd_chaves-1] = 0;
      novo1->qtd_chaves--;
   }

   // atualiza os filhos dos novos nos
   posicaoNovosFilhos=0;
   if (!eFolha(filho)) {
      for (int j=0; j<=novo1->qtd_chaves; j++, posicaoNovosFilhos++) {
         novo1->filhos[j] = filho->filhos[posicaoNovosFilhos];
      }
      for (int j=0; j<=novo2->qtd_chaves; j++, posicaoNovosFilhos++) {
         novo2->filhos[j] = filho->filhos[posicaoNovosFilhos];
      }
   }

   // procura o pai do no filho
   if (*raiz!=filho) {
      while (!encontrou) {
         for (posicaoPai=0; posicaoPai<=p->qtd_chaves && !encontrou && filho->chaves[0]>p->chaves[posicaoPai]; posicaoPai++) {
            if (p->filhos[posicaoPai]==filho) {
               encontrou = true;
            }
         }
         if (posicaoPai<p->qtd_chaves) {
            if (p->filhos[posicaoPai]==filho) {
               encontrou = true;
            }
         }
         if (!encontrou) {
            p = p->filhos[p->qtd_chaves>0 ? posicaoPai : posicaoPai - 1];
         }
      }
   }

   // o no a ser particionado eh a propria raiz
   if (*raiz==filho) {
      for (int i=0; i<p->qtd_chaves; i++) {
         p->chaves[i] = 0;
      }
      for (int i=0; i<ordem; i++) {
         p->filhos[i] = NULL;
      }
      p->qtd_chaves = 0;
   }

   // o no pai do no particionado tambem esta cheio e tambem precisa ser particionado
   if (p->qtd_chaves==ordem-1 && *raiz!=filho) {
      split(raiz, p, separador);
      struct NO *p = *raiz;
      encontrou = false;
      // procura o novo no particionado
      while (!encontrou) {
         for (posicaoP=0; posicaoP<p->qtd_chaves && !encontrou && separador>=p->chaves[posicaoP]; posicaoP++) {
            if (p->chaves[posicaoP]==separador) {
               encontrou = true;
            }
         }
         if (posicaoP<p->qtd_chaves) {
            if (p->chaves[posicaoP]==separador) {
               encontrou = true;
            }
         }
         if (!encontrou) {
            p = p->filhos[p->qtd_chaves>0 ? posicaoP : posicaoP - 1];
         }
      }
      // atualiza os filhos do novo no particionado e o atributo 'folha'
      int aux = p->qtd_chaves;
      while (aux>posicaoP) {
         p->filhos[aux] = p->filhos[aux-1];
         aux--;
      }
      p->filhos[aux] = novo2;
      p->filhos[aux-1] = novo1;
      for (int i=p->qtd_chaves+1; i<ordem; i++) {
         p->filhos[i] = NULL;
      }
   } else {
      // o no pai do no particionado nao esta cheio, entao so adiciona o separador e atualiza os filhos e o atributo 'folha'
      int aux1, aux2 = p->qtd_chaves;
      while (aux2>posicaoPai) {
         p->chaves[aux2] = p->chaves[aux2-1];
         p->filhos[aux2+1] = p->filhos[aux2];
         aux2--;
      }
      p->chaves[aux2] = separador;
      p->filhos[aux2+1] = novo2;
      p->filhos[aux2] = novo1;
      p->qtd_chaves++;
      for (int i=p->qtd_chaves+1; i<ordem; i++) {
         p->filhos[i] = NULL;
      }
   }

   return;

}

// funcao que determina se um no eh folha ou nao
bool eFolha(struct NO *no) {
   return (no->filhos[0] == NULL);
}

// funcao comparadora para qsort
int compare(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}