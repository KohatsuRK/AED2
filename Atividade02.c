#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define maximo 10

struct No{
    int dado;
    int fila;
    struct No *subArvEsq;
    struct No *SubArvDir;
};

typedef struct No TipoNoArvore;

typedef TipoNoArvore *TipoArvore;

TipoArvore inicializaArvore(){
    return NULL;
}

int ArvoreVazia(TipoArvore raiz){
    return raiz==NULL;
}

TipoArvore instanciaArvore(int num,int fila){
    TipoArvore arvore = (TipoArvore)malloc(sizeof(TipoNoArvore));
    arvore->dado = num;
    arvore->fila = fila;
    arvore->subArvEsq = NULL;
    arvore->SubArvDir = NULL;
    return arvore;
}

TipoArvore adicionaNaArvore(TipoArvore raiz,int num,int f){
    if(ArvoreVazia(raiz)){
        return instanciaArvore(num,f);
    }
    if(num > raiz->dado){
        raiz->SubArvDir = adicionaNaArvore(raiz->SubArvDir,num,f);
    } else{
        raiz->subArvEsq = adicionaNaArvore(raiz->subArvEsq,num,f);
    }
    return raiz;
}

TipoArvore removeDaArvore(TipoArvore arvore/*,int num*/){
    if (arvore->SubArvDir == NULL){
        TipoArvore tmp = arvore->subArvEsq;
        free(arvore);
        return tmp;
    }
    arvore->SubArvDir = removeDaArvore(arvore->SubArvDir);

    return arvore;
}

int achaMaior(TipoArvore raiz){
    while (raiz->SubArvDir != NULL){
        raiz = raiz->SubArvDir;
    }
    return raiz->fila;
}

int main(){
    TipoArvore raiz;
    int n,f=1;
    char comando;
    raiz = NULL;

    while(1==1){
        scanf(" %c",&comando);
        if(comando == 'c'){
            scanf("%d",&n);
            raiz = adicionaNaArvore(raiz,n,f);
            f++;
        }
        if(comando == 'v'){
            if(!ArvoreVazia(raiz)){
                int maior = achaMaior(raiz);
                raiz = removeDaArvore(raiz);
                printf("%d\n",maior);
            }else{
                printf("0\n");
            }
        }
        if(comando == 'f'){
            break;
        }
    }
    while (raiz != NULL){
        TipoArvore tmp = raiz;
        raiz = raiz->subArvEsq;
        free(tmp);
    }
    

}