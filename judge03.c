#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
  int Numcandidato;
  int votos; //guardar qtd de votos de cada candidato
}Candidatos;

typedef struct {
    Candidatos *candidato;
    int tamanho;
} MaxHeap;//é interessante usar max heap pois ele consegue manipular parecendo arvore, mas passando porcada candidato


MaxHeap *inicializarMaxH(int C) {
    MaxHeap *maxHeap = (MaxHeap *)malloc(sizeof(MaxHeap));
    maxHeap->candidato = (Candidatos *)malloc(sizeof(Candidatos) * (C + 1));
    maxHeap->tamanho = 0;
    return maxHeap;
}



void inserirMaxH(MaxHeap *maxHeap, Candidatos candidato) {
    int i;
    maxHeap->tamanho++;
    i = maxHeap->tamanho;

    while (i > 1 && (candidato.votos > maxHeap->candidato[i / 2].votos || (candidato.votos == maxHeap->candidato[i / 2].votos && candidato.Numcandidato < maxHeap->candidato[i / 2].Numcandidato))) {
        maxHeap->candidato[i] = maxHeap->candidato[i / 2];
        i /= 2;
    }

    maxHeap->candidato[i] = candidato;
}


void maxHeapify(MaxHeap *maxHeap, int i) {
    int esq = 2 * i;
    int dir = 2 * i + 1;
    int maior = i;

    if (esq <= maxHeap->tamanho && (maxHeap->candidato[esq].votos > maxHeap->candidato[i].votos || (maxHeap->candidato[esq].votos == maxHeap->candidato[i].votos && maxHeap->candidato[esq].Numcandidato < maxHeap->candidato[i].Numcandidato))) {
        maior = esq;
    }

    if (dir <= maxHeap->tamanho && (maxHeap->candidato[dir].votos > maxHeap->candidato[maior].votos || (maxHeap->candidato[dir].votos == maxHeap->candidato[maior].votos && maxHeap->candidato[dir].Numcandidato < maxHeap->candidato[maior].Numcandidato))) {
        maior = dir;
    }

    if (maior != i) {
        // Troca os candidatos
        Candidatos temp = maxHeap->candidato[i];
        maxHeap->candidato[i] = maxHeap->candidato[maior];
        maxHeap->candidato[maior] = temp;

        // Chama maxHeapify recursivamente no candidato trocado
        maxHeapify(maxHeap, maior);
    }
}

Candidatos obterMaxVotos(MaxHeap *maxHeap) {
    return maxHeap->candidato[1]; 
}

void apuracaoSegundo(int **eleitores,MaxHeap *max ,Candidatos *candidato, int V,int votos1, int C, int *elegivel){
    int i =0, j;
   
    for(j=0;j<V;j++){//faz as contagens de novo, mas, diferernte da primeira vez, ela entra na stack na onde não voltou
        if((eleitores[j][i] != elegivel[0] && eleitores[j][i] != elegivel[1])){
            candidato[eleitores[j][i] - 1].votos++;
        }else if(eleitores[j][i+1]!= elegivel[0] && eleitores[j][i+1]!= elegivel[1]){
            candidato[eleitores[j][i+1] - 1].votos++; 
        }else if(eleitores[j][i+2]!= elegivel[0] && eleitores[j][i+2]!= elegivel[1]){
            candidato[eleitores[j][i+2] - 1].votos++;
        }
    }

    //free(max);

    for(int l = 0; l < C; l++) {
        inserirMaxH(max, candidato[elegivel[l]]);
    }
    i=0;
    // while (i<2) {
            Candidatos maisVotado = obterMaxVotos(max);
            float percent = (float) (maisVotado.votos *100 )/ (float)(maisVotado.votos+votos1);
            printf("%i  %.2f\n", maisVotado.Numcandidato,percent);
            max->candidato[1] = max->candidato[max->tamanho];
            max->tamanho--;
            maxHeapify(max, 1);
            i++;
        //}

    return;
}


int main(void) {
    int V,C,i,j; //V eleitores, C candidatos  
    scanf("%i %i",&V,&C);
    float perCent;
    int votos1[2];
    int **eleitoresV = (int**) malloc(V * sizeof(int*)); 
    Candidatos *candidato = malloc(C * sizeof(Candidatos));
    MaxHeap *max = inicializarMaxH(C);

    for (i = 0; i < C; i++) {
        candidato[i].Numcandidato = i + 1;
        candidato[i].votos = 0;
    }

    for(i=0;i<V;i++)
        eleitoresV[i] = (int*)malloc(3* sizeof(int));
   
    for (i = 0; i < V; i++) {//armazena os votos
        for ( j = 0; j < 3; j++) {
            scanf("%i", &eleitoresV[i][j]);
            if (eleitoresV[i][j] < 1 || eleitoresV[i][j] > C){
                eleitoresV[i][j] = 0;
            }    
        }
    }
    
    // for (i = 0; i < V; i++) {
    //     for ( j = 0; j < 3; j++) {
    //         candidato[eleitoresV[i][j] - 1].votos++;
    //     }
    // }
    //primeiro turno
    int votanteValido = V;

    for (i = 0; i < V; i++) {
        candidato[eleitoresV[i][0] - 1].votos++;
        if(eleitoresV[i][0]==0)
            votanteValido--;
    }

    for (int i = 0; i < C; i++) {
        inserirMaxH(max, candidato[i]);
    }

    perCent = (float)max->candidato[1].votos/votanteValido *100;
    int *disputa = (int*)malloc(2*sizeof(int));   
    
    if(candidato[1].votos==0){
        printf("0\n");
       return 0;
    }else if(perCent<50){ 
        i = 0;
        printf("%i  %.2f\n", candidato[0].Numcandidato, perCent);
        while (2>i) {
            Candidatos maisVotado = obterMaxVotos(max);
            //printf("Número do candidato: %d, Votos: %d\n", maisVotado.Numcandidato, maisVotado.votos);
            votos1[i] = maisVotado.votos; 
            max->candidato[1] = max->candidato[max->tamanho];
            max->tamanho--;
            maxHeapify(max, 1);
            disputa[i] = maisVotado.Numcandidato;
            i++;
        }
        
        //printf("\nVotos: %i\n",votos1[0]);
        apuracaoSegundo(eleitoresV,max,candidato,V,votos1[0],C,disputa);

    }else if(perCent>50){
        printf("%i  %.2f\n",max->candidato[1].Numcandidato, perCent);
    }

    // for(int i=0;i<V;i++){
    //     printf("\n");
    //     for(int j=0;j<3;j++){
    //         printf("\t%i",eleitoresV[i][j]);
    //     }
    // }

    free(candidato);
    free(eleitoresV);
    free(max);
    return 0;
}