#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char nome[15];
  int* anos;
  int num_anos;
  int h; // altura
  struct node* left;
  struct node* right;
} Typenode;

Typenode* novoNode(char nome[], int ano, int max_anos) {
  Typenode* noh = (Typenode*)malloc(sizeof(Typenode));
  strcpy(noh->nome, nome);
  noh->anos = (int*)malloc(max_anos * sizeof(int));
  noh->anos[0] = ano;
  noh->num_anos = 1;
  noh->h = 1;
  noh->left = NULL;
  noh->right = NULL;
  return noh;
}

int max(int Hx, int Hy) {
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

Typenode* inserir(Typenode* avl, char nome[], int ano, int max_anos) {
  if (avl == NULL)
    return novoNode(nome, ano, max_anos);
  if (strcmp(nome, avl->nome) < 0) {
    avl->left = inserir(avl->left, nome, ano, max_anos);
  } else if (strcmp(nome, avl->nome) > 0) {
    avl->right = inserir(avl->right, nome, ano, max_anos);
  } else {
    if (avl->num_anos < max_anos) {
      avl->anos[avl->num_anos] = ano;
      avl->num_anos++;
    }
  }
  avl->h = 1 + max((avl->left ? avl->left->h : 0), (avl->right ? avl->right->h : 0));
  int balanceamento = (avl->left ? avl->left->h : 0) - (avl->right ? avl->right->h : 0);
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

void buscaNaAVL(Typenode* avl, char nome[], int anos[], int* total, int* altura) {
  if (avl == NULL)
    return;

  int cmp = strcmp(nome, avl->nome);
  if (cmp == 0) {
    for (int i = 0; i < avl->num_anos; i++) {
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
  int max_anos = 100;
  Typenode* avl = NULL;
  int c, ano;
  char nome[15];
  int* anos = (int*)malloc(max_anos * sizeof(int));
  int total = 0;
  int altura = 0;

  while (1) {
    scanf("%d", &c);

    if (c == 0) {
      break;
    }

    if (c == 1) {
      scanf("%s %d", nome, &ano);
      avl = inserir(avl, nome, ano, max_anos);
    } else if (c == 2) {
      scanf("%s", nome);
      buscaNaAVL(avl, nome, anos, &total, &altura);
      // printf("Total de anos: %d\n", total);
      printf("%d ", altura);

      if (total > 0) {
        for (int i = 0; i < total; i++) {
          printf("%d ", anos[i]);
        }
        printf("\n");
        total = 0;
        altura = 0;
      } else {
        printf("\n");
      }
    }
  }
  free(anos); 
  liberarAVL(avl);
  return 0;
}
