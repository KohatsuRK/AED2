#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct nohArvore {
  int dado;
  int senha;
  struct nohArvore *arvEsq;
  struct nohArvore *arvDir;
};
typedef struct nohArvore TipoNohArvore;
typedef TipoNohArvore *TipoArvore;


TipoAVL* removeMaior(TipoAVL* raiz) {
    if (raiz == NULL) {
        return raiz;
    }

    TipoAVL* pai = NULL;
    TipoAVL* atual = raiz;

    while (atual->direita != NULL) {
        pai = atual;
        atual = atual->direita;
    }

    if (pai == NULL) {
        TipoAVL* temp = raiz;
        raiz = raiz->esquerda;
        free(temp);
    } else {
        pai->direita = atual->esquerda;
        free(atual);
    }

    if (pai != NULL) {
        pai->altura = 1 + max(altura(pai->esquerda), altura(pai->direita));
    }
    int balance = (pai == NULL) ? 0 : balanceamento(pai);

    if (balance > 1) {
        if (balanceamento(pai->esquerda) < 0) {
            pai->esquerda = rotacionaEsquerda(pai->esquerda);
        }
        return rotacionaDireita(pai);
    }

    
    if (balance < -1) {
        if (balanceamento(pai->direita) > 0) {
            pai->direita = rotacionaDireita(pai->direita);
        }
        
        return rotacionaEsquerda(pai);
    }

 
    return raiz;
}
int arvoreVazia(TipoArvore avr) { 
    return avr == NULL; 
}

TipoArvore instancia(int dado, int senha) {
  TipoArvore avr;
  avr = (TipoArvore)malloc(sizeof(TipoNohArvore));
  avr->dado = dado;
  avr->senha = senha;
  avr->arvEsq = NULL;
  avr->arvDir = NULL;
  return avr;
}

TipoArvore inicializaArvore() { return NULL; }

TipoArvore destroi(TipoArvore avr) {
  if (!arvoreVazia(avr)) {
    destroi(avr->arvEsq);
    destroi(avr->arvDir);
    free(avr);
  }
  return NULL;
}

TipoArvore insere(TipoArvore avr, int dado, int senha) {
  if (!arvoreVazia(avr)) {
    if (avr->dado > dado) {
      avr->arvEsq = insere(avr->arvEsq, dado, senha);
    } else {
      if (avr->dado < dado) {
        avr->arvDir = insere(avr->arvDir, dado, senha);
      }
    }
  } else {
    avr = instancia(dado, senha);
  }
  return avr;
}

// TipoArvore removeMaior(TipoArvore avr) {
//   if (arvoreVazia(avr)) {
//     return avr;
//   }

//   if (avr->arvDir != NULL) {
//     avr->arvDir = removeMaior(avr->arvDir);
//     return avr;
//   }

//   if (avr->arvEsq == NULL) {
//     free(avr);
//     return NULL;
//   }

//   TipoArvore aux = avr->arvEsq;
//   free(avr);
//   return aux;
// }

TipoArvore removeMaiorPorChave(TipoArvore avr) {
  TipoArvore pai = NULL;
  TipoArvore atual = avr;
  if (arvoreVazia(avr)) {
    return avr; // Árvore vazia
  }
  
  while (atual->arvDir != NULL) {
    pai = atual;
    atual = atual->arvDir;  
  }
  // if (pai->dado == atual->dado){
  //   atual->arvEsq = pai->arvDir; 
  //   free(pai);
  //   return avr;
  // } 
    if (pai != NULL) {
      pai->arvDir = atual->arvEsq;
      free(atual);
    } else {
      avr = atual->arvEsq;
      free(atual);
    }
  return avr;
}

// TipoArvore buscaNaArvore(TipoArvore avr, int dado) {
//   if (!arvoreVazia(avr)) {
//     if (avr->dado > dado) {
//       return buscaNaArvore(avr->arvEsq, dado);
//     } else {
//       if (avr->dado < dado) {
//         return buscaNaArvore(avr->arvDir, dado);
//       } else
//         return avr;
//     }
//   }
//   return NULL;
// }

int buscaMaior(TipoArvore avr){
    while (avr->arvDir != NULL){
        avr = avr->arvDir;
    }
    return avr->senha;
}

int main() {
  TipoArvore avr = inicializaArvore();
  int valor, senha, maior;
  senha = 1;
  char acao;
  
  while (true) {
    scanf(" %c", &acao);
    if (acao == 'c') {
      scanf("%d", &valor);
      avr = insere(avr, valor, senha);
      senha++;
    } else if (acao == 'v') {
        if(avr!=NULL){
            maior = buscaMaior(avr);
            avr = removeMaiorPorChave(avr);
            printf("%d\n",maior);
        }else{
            printf("0\n");
        }
    }
    if (acao == 'f') {
      break;
    }
  }

  //destroi(avr);

  return 0;
}
