#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_ANOS 50
 
typedef struct node {
  char nome[15];
  long int* anos; 
  long int num_anos; 
  long int h; 
  struct node* left;
  struct node* right;
} Typenode;
 
Typenode* novoNode(char nome[], long int ano) { 
  Typenode* noh = (Typenode*)malloc(sizeof(Typenode));
  strcpy(noh->nome, nome);
  noh->anos = (long int*)malloc(MAX_ANOS * sizeof(long int)); 
  noh->anos[0] = ano;
  noh->num_anos = 1;
  noh->h = 1;
  noh->left = NULL;
  noh->right = NULL;
  return noh;
}
 
long int max(long int Hx, long int Hy) { 
  return (Hx > Hy) ? Hx : Hy;
}
 
Typenode* esqRotacao(Typenode* avl) {
  Typenode* root = avl->right;
  avl->right = root->left;
  root->left = avl;
  avl->h = 1 + max((avl->left ? avl->left->h : 0), (avl->right ? avl->right->h : 0));
  root->h = 1 + max((root->left ? root->left->h : 0), (root->right ? root->right->h : 0));
  return root;
}
 
Typenode* dirRotacao(Typenode* avl) {
  Typenode* root = avl->left;
  avl->left = root->right;
  root->right = avl;
  avl->h = 1 + max((avl->left ? avl->left->h : 0), (avl->right ? avl->right->h : 0));
  root->h = 1 + max((root->left ? root->left->h : 0), (root->right ? root->right->h : 0));
  return root;
}
 
Typenode* inserir(Typenode* avl, char nome[], long int ano) { 
  if (avl == NULL)
    return novoNode(nome, ano);
  if (strcmp(nome, avl->nome) < 0) {
    avl->left = inserir(avl->left, nome, ano);
  } else if (strcmp(nome, avl->nome) > 0) {
    avl->right = inserir(avl->right, nome, ano);
  } else {
    if (avl->num_anos < MAX_ANOS) {
      avl->anos[avl->num_anos] = ano;
      avl->num_anos++;
    }
  }
  avl->h = 1 + max((avl->left ? avl->left->h : 0), (avl->right ? avl->right->h : 0));
  long int balanceamento = (avl->left ? avl->left->h : 0) - (avl->right ? avl->right->h : 0);
  if (balanceamento > 1 && strcmp(nome, avl->left->nome) < 0) {
    return dirRotacao(avl);
  } else if (balanceamento < -1 && strcmp(nome, avl->right->nome) > 0) {
    return esqRotacao(avl);
  } else if (balanceamento > 1 && strcmp(nome, avl->left->nome) > 0) {
    avl->left = esqRotacao(avl->left);
    return dirRotacao(avl);
  } else if (balanceamento < -1 && strcmp(nome, avl->right->nome) < 0) {
    avl->right = dirRotacao(avl->right);
    return esqRotacao(avl);
  }
  return avl;
}
 
void buscaNaAVL(Typenode* avl, char nome[], long int anos[], long int* total, long int* altura) { 
  if (avl == NULL)
    return;
 
  int cmp = strcmp(nome, avl->nome);
  if (cmp == 0) {
    for (long int i = 0; i < avl->num_anos; i++) {
      anos[(*total)] = avl->anos[i];
      (*total) += 1;
    }
    if (avl->h > *altura) {
      *altura = avl->h;
    }
  } else if (cmp < 0) {
    buscaNaAVL(avl->left, nome, anos, total, altura);
  } else {
    buscaNaAVL(avl->right, nome, anos, total, altura);
  }
}
 
void liberarAVL(Typenode* avl) {
  if (avl == NULL)
    return;
  liberarAVL(avl->left);
  liberarAVL(avl->right);
  free(avl->anos);
  free(avl);
}
 
int main() {
  Typenode* avl = NULL;
  int c;
  long int ano; 
  char nome[15];
  long int anos[MAX_ANOS]; 
  long int total = 0; 
  long int altura = 0; 
 
  while (1) {
    scanf("%d", &c);
 
    if (c == 0) {
      break;
    }
 
    if (c == 1) {
      scanf("%s %ld", nome, &ano); 
      avl = inserir(avl, nome, ano);
    } else if (c == 2) {
      scanf("%s", nome);
      buscaNaAVL(avl, nome, anos, &total, &altura);
      // printf("Total de anos: %ld\n", total); 
      printf("%ld ", altura); 
 
      if (total > 0) {
        for (long int i = 0; i < total; i++) {
          printf("%ld ", anos[i]); 
        }
        printf("\n");
        total = 0;
        altura = 0;
      } else {
        printf("\n");
      }
    }
  }
  liberarAVL(avl);
  return 0;
}
