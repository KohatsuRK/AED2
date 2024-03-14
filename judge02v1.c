#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Noh {
    int valor;
    int senha;
    int altura;
    struct Noh* esquerda;
    struct Noh* direita;
}TipoAVL;



int max(int a, int b) {
    return (a > b) ? a : b;
}


int altura(TipoAVL *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return raiz->altura;
}


int balanceamento(TipoAVL *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return altura(raiz->esquerda) - altura(raiz->direita);
}


TipoAVL* novoNo(int valor, int senha) {
    TipoAVL *raiz = (TipoAVL*)malloc(sizeof(TipoAVL));
    raiz->valor = valor;
    raiz->esquerda = NULL;
    raiz->direita = NULL;
    raiz->altura = 1;
    raiz->senha = senha;
    return raiz;
}


TipoAVL* rotacionaDireita(TipoAVL* y) {
    TipoAVL *x = y->esquerda;
    TipoAVL *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}


TipoAVL* rotacionaEsquerda(TipoAVL* x) {
    TipoAVL *y = x->direita;
    TipoAVL *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}


TipoAVL* insereAVL(TipoAVL* raiz, int valor, int senha) {
    if (raiz == NULL) {
        return novoNo(valor, senha);
    }

    if (valor <= raiz->valor) {
        raiz->esquerda = insereAVL(raiz->esquerda, valor, senha);
    } else if (valor >= raiz->valor) {
        raiz->direita = insereAVL(raiz->direita, valor, senha);
    } else {
        return raiz;
    }

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));
    int balance = balanceamento(raiz);

    if (balance > 1 && valor < raiz->esquerda->valor) {
        return rotacionaDireita(raiz);
    }
    if (balance < -1 && valor > raiz->direita->valor) {
        return rotacionaEsquerda(raiz);
    }
    if (balance > 1 && valor > raiz->esquerda->valor) {
        raiz->esquerda = rotacionaEsquerda(raiz->esquerda);
        return rotacionaDireita(raiz);
    }
    if (balance < -1 && valor < raiz->direita->valor) {
        raiz->direita = rotacionaDireita(raiz->direita);
        return rotacionaEsquerda(raiz);
    }

    return raiz;
}


TipoAVL* removeMaior(TipoAVL* raiz) {
    if (raiz == NULL) {
        return raiz;
    }

    TipoAVL* pai = NULL;
    TipoAVL* atual = raiz;
    TipoAVL* maior = NULL;
    TipoAVL* paiMaior = NULL;

    while (atual->direita != NULL) {
        pai = atual;
        atual = atual->direita;

        if (maior == NULL || atual->valor > maior->valor || (atual->valor == maior->valor && atual->senha < maior->senha)) {
            maior = atual;
            paiMaior = pai;
        }
    }
    printf("\n%i",maior->senha);
    if (paiMaior == NULL) {
        raiz = raiz->esquerda;
        
        free(maior);
    } else {
        paiMaior->direita = maior->esquerda;
        
        free(maior);
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


int main() {
    TipoAVL *raiz = NULL;
    char acao;
    int senha=0, valor;
    while(true){
        scanf(" %c", &acao);
        if(acao == 'c'){
            scanf("%i",&valor);
            raiz = insereAVL(raiz,valor,senha);
            senha++;
        } else if(acao == 'v'){
            if(!(raiz == NULL))
                printf("\n0");
            else 
                raiz = removeMaior(raiz);
        }
        if(acao == 'f') break;
    }

    return 0;
}
