#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int particiona(int *ArrayN, int inicio, int fim) {
    int i = inicio, j = fim;
    int pivo = ArrayN[inicio];
    int count = 0;

    for (int k = inicio + 1; k <= fim; k++) {
        if (ArrayN[k] <= pivo)
            count++;
    }

    int pivoIndice = inicio + count;
    swap(&ArrayN[pivoIndice], &ArrayN[inicio]);

    while (i < pivoIndice && j > pivoIndice) {
        while (ArrayN[i] <= pivo) {
            i++;
        }
        while (ArrayN[j] > pivo) {
            j--;
        }
        if (i < pivoIndice && j > pivoIndice) {
            swap(&ArrayN[i++], &ArrayN[j--]);
        }
    }

    return pivoIndice;
}

void quickSort(int *ArrayN, int inicio, int fim) {
    int pivo;
    if (fim > inicio) {
        pivo = particiona(ArrayN, inicio, fim);
        quickSort(ArrayN, inicio, pivo - 1);
        quickSort(ArrayN, pivo + 1, fim);
    }
}
int main(){
    int *array;
    int N, S,soma;//N é o intero que queremos sua soma e S o tamanho da Array e "a" faz parte de s
    int count=0;
    int i, j;

    scanf("%i%i",&S, &N); //recebendo S e recebedo N valor que iremos compara com a soma de alguns pares
    array = (int *) malloc(S * sizeof(array));

    for(i=0; i<S; i++){
        scanf("%i",&array[i]);
    }    
    quickSort(array,0,S-1);
    // for(i=0; i<S; i++)
    //     printf("%i\t",array[i]);

    // for(i=0; i<S; i++){
    //    int complemento = N - array[i];
    //    for(j=i+1; j<S; j++){
    //         if(complemento>=array[j]){
    //             if(array[i]+array[j]==N)
    //                 count++;
    //         }else{
    //             break;
    //         }
    //    }
    // } //esse deu time limeted
    i = 0; 
    j = S-1;// e se usasemos dois indices que "apontariam para onde anda", parecido com a ideia de ordenação dos N^2, mas, dentro de um while e fizesse todas as comparações possiveis ali
    while(i<j){
       soma = array[i]+array[j];
       if(soma == N){
            count++;
            i++;
            j--;
        }else if(soma<N){
            i++;
        }else{
            j--;    
        }
    }

    printf("%i", count);
    free(array);
    return 0;
}